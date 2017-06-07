#include "TelaArestas.h"
#include "ui_TelaArestas.h"

TelaArestas::TelaArestas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaArestas)
{
    ui->setupUi(this);
}

TelaArestas::~TelaArestas()
{
    delete ui;
}

void TelaArestas::listarArestas(ED2::Grafo *grafo)
{
    if(!grafo) throw QString("Grafo vazio");
    try{
        std::vector<ED2::Aresta*> *arestas = grafo->getArestas();
        ui->textEditArestas->clear();
        QString saida="";
        for(std::vector<ED2::Aresta*>::iterator i = arestas->begin(); i!=arestas->end(); i++) {
            ED2::Aresta *aux  = *i;
            saida += aux->getOrigem()->getDescricao() +
                    " -- |<font color='red'>"+ QString::number(aux->getPeso())
                    +"</font>| --> "+aux->getDestino()->getDescricao()+"<br>";
        }
        ui->textEditArestas->setText(saida);
    }catch(QString &erro){
        throw erro;
    }
}
