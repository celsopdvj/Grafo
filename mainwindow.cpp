#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    grafo(0)
{
    ui->setupUi(this);


    // Alinha a janela no centro da tela
    this->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,Qt::AlignCenter,this->size(),qApp->desktop()->availableGeometry()
                    )
                );


    // deixa os botoes de operacoes bloqueados ate que o grafo seja criado
    habilitarBotoes(false);

    // adiciona a mascara de numeros para a line edit de tamanho do grafo
    QRegExp regra("[0-9]*");
    QRegExpValidator *validator = new QRegExpValidator(regra);
    ui->lineEditTamanho->setValidator(validator);

    // coloca o programa na pagina 0
    ui->stackedWidget->setCurrentIndex(0);
    // conecta o combo box para trocar de paginas
    connect(ui->comboBoxPagina,SIGNAL(currentIndexChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    // bloqueia o tamanho da tela para o tamanho atual
    this->setMaximumWidth(this->width());
    this->setMaximumHeight(this->height());
    this->setMinimumHeight(this->height());
    this->setMinimumWidth(this->width());

    // esconde o endereco do arquivo na tela
    ui->lineEditArquivo->setVisible(false);
    ui->labelArquivo->setVisible(false);

    // esconde o header da tabela de status
    ui->tableWidgetStatus->horizontalHeader()->hide();
}

MainWindow::~MainWindow()
{
    if(grafo) delete grafo;
    delete ui;
}

void MainWindow::on_pushButtonCriar_clicked()
{
    try{
        // cria o grafo
        grafo = new ED2::Grafo(ui->lineEditTamanho->text().toInt());

        // desbloqueia os botoes de operacoes
        habilitarBotoes(true);

        //mensagem de sucesso e troca para pagina 2
        QMessageBox::about(this,"Sucesso","Grafo cadastrado com sucesso!");
        ui->comboBoxPagina->setCurrentIndex(1);

        statusGrafo();

    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }catch(std::bad_alloc&){
        QMessageBox::critical(this,"Erro","Maquina sem memoria");
    }
}

void MainWindow::on_pushButtonInserir_clicked()
{
    try{
        if(ui->lineEditDescricao->text().isEmpty())
            throw QString("Descricao invalida");
        ED2::Vertice *novo = new ED2::Vertice();
        if(grafo->existeVertice(ui->lineEditDescricao->text())) throw QString("Vertice ja existe");
        novo->setDescricao(ui->lineEditDescricao->text());
        grafo->incluirVertice(novo);
        listarVertices();
        statusGrafo();
        if(grafo->isFull())
        {
            ui->lineEditDescricao->setEnabled(0);
            ui->pushButtonInserir->setEnabled(0);
        }
        ui->lineEditDescricao->clear();
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

void MainWindow::listarVertices()
{
    ED2::Vertice **lista = grafo->getListaVertices();
    ui->comboBoxPartida->clear();
    ui->comboBoxDestino->clear();
    for(int i=0;i<grafo->getVerticesOcupados();i++)
    {
        ui->comboBoxPartida->addItem(lista[i]->getDescricao());
        ui->comboBoxDestino->addItem(lista[i]->getDescricao());
    }
}

void MainWindow::listarArestas()
{
    try{
        std::vector<ED2::Aresta*> *arestas = grafo->getArestas();
        ui->textEditArestas->clear();
        QString saida="";
        for(std::vector<ED2::Aresta*>::iterator i = arestas->begin(); i!=arestas->end(); i++) {
            ED2::Aresta *aux  = *i;
            saida += "<p>"+aux->getOrigem()->getDescricao() + " ---> "+aux->getDestino()->getDescricao()+"</p>\n";
        }
        ui->textEditArestas->setText(saida);
    }catch(QString &erro){
        throw erro;
    }
}

void MainWindow::statusGrafo()
{
    try{
        limparStatus();
        ui->tableWidgetStatus->setColumnCount(1);
        ui->tableWidgetStatus->setItem(0,0,new QTableWidgetItem(QString::number(grafo->getVerticesOcupados())));
        ui->tableWidgetStatus->setItem(1,0,new QTableWidgetItem(QString::number(grafo->getQuantidadeArestas())));
        ui->tableWidgetStatus->setItem(2,0,new QTableWidgetItem(grafo->direcionado()?"Sim":"Não"));
        ui->tableWidgetStatus->setItem(3,0,new QTableWidgetItem(grafo->conexo()?"Sim":"Não"));
    }catch(std::bad_alloc&){
        throw QString("Maquina sem memoria");
    }catch(QString &erro){
        throw erro;
    }
}

void MainWindow::limparStatus()
{
    for(int i=0; i< ui->tableWidgetStatus->rowCount();i++)
        if(ui->tableWidgetStatus->item(i,0)) delete ui->tableWidgetStatus->item(i,0);
}

void MainWindow::habilitarBotoes(bool habilita)
{
    ui->lineEditAdjA->setEnabled(habilita);
    ui->lineEditAdjB->setEnabled(habilita);
    ui->pushButtonAdjancente->setEnabled(habilita);
    ui->lineEditTamanho->setEnabled(!habilita);
    ui->pushButtonCriar->setEnabled(!habilita);
    ui->lineEditDescricao->setEnabled(habilita);
    ui->pushButtonInserir->setEnabled(habilita);
    ui->pushButtonRemoverAdj->setEnabled(habilita);
    ui->checkBoxDirecionada->setEnabled(habilita);
    ui->pushButtonBfs->setEnabled(habilita);
    ui->comboBoxPartida->setEnabled(habilita);
    ui->comboBoxDestino->setEnabled(habilita);
    ui->textEditArestas->setEnabled(habilita);
}

void MainWindow::on_pushButtonAdjancente_clicked()
{
    try{
        ED2::Vertice *verticeA = grafo->getVertice(ui->lineEditAdjA->text());
        ED2::Vertice *verticeB = grafo->getVertice(ui->lineEditAdjB->text());

        /*          METODO PARA INSERIR ARESTA E ADJACENCIA
         *          -> CHECKBOX MARCADA - ARESTA DIRECIONADA:
         *              1- SE NAO EXISTIR A ARESTA A--B, CRIE
         *              2- SE EXISTIR, LANCE EXCECAO
         *
         *          -> CHECKBOX - ARESTA NAO DIRECIONADA:
         *              1- SE NAO EXISTIR A--B E NAO EXISTIR B-A, CRIE A-B E B-A
         *              2- SE EXISTIR A--B E NAO EXISTIR B--A, CRIE B--A
         *              3- SE NAO EXISTIR A--B E EXISTIR B--A, CRIE A--B
         *              4- SE EXITIR A--B E EXISTIR B--A, LANCE EXCECAO
         */

        // Aresta nao e direcionada
        if(!ui->checkBoxDirecionada->isChecked())
        {
            // nao direcionada, ja existe a--b e b--a
            if(grafo->existeAresta(verticeA,verticeB) && grafo->existeAresta(verticeB,verticeA))
            {
                throw QString("Aresta já existe");
            }

            // nao direcionada, nao existe b--a
            if(!grafo->existeAresta(verticeB,verticeA))
            {
                verticeB->inserirAdjacente(verticeA);
                grafo->incluirAdjacencia(verticeB,verticeA);
                grafo->incluirAresta(verticeB,verticeA);
            }
        }

        // nao existe a--b
        if(!grafo->existeAresta(verticeA,verticeB))
        {
            verticeA->inserirAdjacente(verticeB);
            grafo->incluirAdjacencia(verticeA,verticeB);
            grafo->incluirAresta(verticeA,verticeB);
        }
        else
        {
            // direcionada, existe a--b
            if(ui->checkBoxDirecionada->isChecked())
            {
                throw QString("Aresta já existe");
            }
        }

        listarVertices();
        listarArestas();
        statusGrafo();

        ui->lineEditAdjA->clear();
        ui->lineEditAdjB->clear();

    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

void MainWindow::on_pushButtonRemoverAdj_clicked()
{
    try{
        ED2::Vertice *verticeA = grafo->getVertice(ui->lineEditAdjA->text());
        ED2::Vertice *verticeB = grafo->getVertice(ui->lineEditAdjB->text());
        verticeA->removerAdjancente(verticeB);
        grafo->excluirAdjacencia(verticeA,verticeB);
        grafo->removerAresta(verticeA,verticeB);
        listarVertices();
        listarArestas();
        statusGrafo();
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

void MainWindow::on_pushButtonBfs_clicked()
{
    try{
        if(grafo)
        {
            ED2::Vertice *partida = grafo->getVertice(ui->comboBoxPartida->currentText());
            ED2::Vertice *destino = grafo->getVertice(ui->comboBoxDestino->currentText());
            grafo->BuscaEmLargura(partida);
            ui->textEditBfs->setText(grafo->printPath(partida,destino));
        }
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

void MainWindow::on_pushButtonCarregar_clicked()
{
    try{
        QString endereco = QFileDialog::getOpenFileName(this,"Arquivo",QDir::homePath(),"Arquivo texto (*.txt)");
        ED2::Grafo *aux = ED2::PersistenciaGrafo::carregarGrafo(endereco);
        if(grafo) delete grafo;
        grafo = aux;
        habilitarBotoes(true);
        listarArestas();
        listarVertices();
        statusGrafo();
        ui->lineEditArquivo->setText(endereco);
        ui->lineEditArquivo->setVisible(true);
        ui->labelArquivo->setVisible(true);
        if(grafo->isFull())
        {
            ui->pushButtonInserir->setEnabled(0);
            ui->lineEditDescricao->setEnabled(0);
        }

        // mensagem de sucesso e troca de pagina do programa
        QMessageBox::about(this,"Sucesso","Grafo cadastrado com sucesso!");
        ui->comboBoxPagina->setCurrentIndex(1);

    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

void MainWindow::on_pushButtonSalvar_clicked()
{
    try{
        if(!grafo) throw QString("Grafo nao preenchido");
        QString endereco = QFileDialog::getSaveFileName(this,"Arquivo",QDir::homePath(),"Arquivo texto (*.txt)");
        ED2::PersistenciaGrafo::salvarGrafo(grafo,endereco);

        QMessageBox::about(this,"Sucesso","Salvo com sucesso!");
    }catch(QString &erro){
        QMessageBox::critical(this,"Erro",erro);
    }
}

void MainWindow::on_pushButtonHelp_clicked()
{
    TelaAjuda ajuda;
    ajuda.setModal(true);
    ajuda.exec();
}

void MainWindow::on_pushButtonLista_clicked()
{
    TelaLista listagem;
    listagem.setModal(true);
    listagem.listar(grafo);
    listagem.exec();
}

void MainWindow::on_pushButtonMatriz_clicked()
{
    TelaMatriz listagem;
    listagem.setModal(true);
    listagem.listarMatriz(grafo);
    listagem.exec();
}
