#include "PersistenciaGrafo.h"

namespace ED2
{

PersistenciaGrafo::PersistenciaGrafo()
{

}

Grafo *PersistenciaGrafo::carregarGrafo(QString nomeDoArquivo)
{
    try{

        // arquivo para leitura
        std::ifstream arquivo;

        // abre o arquivo e verifica se houve sucesso
        arquivo.open(nomeDoArquivo.toStdString().c_str());
        if(!arquivo.is_open()) throw QString("Arquivo nao pode ser aberto");
        std::string linha;

        // le a primeira linha do arquivo
        getline(arquivo,linha);
        if(arquivo.eof()) throw QString("Arquivo incompleto");

        // conversao de string para inteiro, primeira linha para quantidade de vertices
        Grafo *saida = new Grafo(std::stoi(linha));

        // le a segunda linha, que contem a descricao dos vertices
        getline(arquivo,linha);
        if(arquivo.eof()) throw QString("Arquivo incompleto");
        QString linhaAux = QString::fromStdString(linha);

        // separa a segunda linha por ';', montando uma lista de strings
        QStringList verticesString = linhaAux.split(';');
        verticesString.pop_back();
        if(verticesString.size()!=saida->getTamanho()) throw QString("Arquivo incompleto");

        // para cada item da lista, monta um vertice caso tenha a descricao valida
        for(int i=0;i<verticesString.size();i++)
        {
            if(!verticesString.at(i).isEmpty())
            {
                Vertice *novoVertice = new Vertice();
                novoVertice->setDescricao(verticesString.at(i));
                saida->incluirVertice(novoVertice);
            }
        }

        // a partir da terceira linha o arquivo contem a matriz
        // aloca a matriz e a preenche
        int **matriz = new int*[saida->getTamanho()];
        for(int i=0;i<saida->getTamanho();i++)
        {
            // aloca a coluna 'i' da matriz
            matriz[i] = new int[saida->getTamanho()];

            // le a linha
            getline(arquivo,linha);
            if(arquivo.eof()) throw QString("Arquivo incompleto");

            // separa as adjacencias por ';'
            linhaAux = QString::fromStdString(linha);
            QStringList matrizString = linhaAux.split(';');
            matrizString.pop_back();

            for(int j=0;j<saida->getTamanho();j++)
            {
                matriz[i][j] = matrizString[j].toInt();

                // caso o elemento seja 1, atribui a adjacencia
                if(matriz[i][j]==1)
                {
                    Vertice *origem = saida->getVerticePorPosicao(i);
                    Vertice *destino= saida->getVerticePorPosicao(j);
                    saida->incluirAresta(origem,destino);
                    origem->inserirAdjacente(destino);
                }

                // caso tenha um numero diferente de 1 ou 0, lanca ecxessao
                else if(matriz[i][j]!=0)
                {
                    throw QString("Matriz com adjacencia nao permitida");
                }
            }
        }
        // atribui a nova matriz
        saida->setMatrizAdjacencia(matriz);
        return saida;

    }catch(std::bad_alloc&){
        throw QString("Maquina sem memoria");
    }catch(QString &erro){
        throw erro;
    }
}

void PersistenciaGrafo::salvarGrafo(Grafo *grafo, QString nomeDoArquivo)
{
    try{
        // arquivo de escrita
        std::ofstream arquivo;

        // abre o arquivo e verfica se houve sucesso
        arquivo.open(nomeDoArquivo.toStdString().c_str());
        if(!arquivo.is_open()) throw QString("Arquivo nao pode ser aberto");

        // escreve a primeira linha, quantidade de vertices
        arquivo << grafo->getTamanho() << '\n';

        Vertice ** listaVertices = grafo->getListaVertices();

        // para cada elemento da lista de vertices, escreve sua descricao na segunda linha do arquivo
        for(int i=0;i<grafo->getTamanho();i++)
        {
            // se a posicao esta ocupada, o vertice existe. Escreve sua descricao no arquivo
            if(i<grafo->getVerticesOcupados())
                arquivo << listaVertices[i]->getDescricao().toStdString();
            arquivo << ';';
        }
        arquivo << '\n';

        // a partir da terceira linha escreve a matriz de adjacencia. Cada linha do arquivo, uma linha da matriz
        int ** matriz = grafo->getMatrizAdjacencia();
        for(int i=0;i<grafo->getTamanho();i++)
        {
            for(int j=0;j<grafo->getTamanho();j++)
            {
                arquivo << matriz[i][j] << ';' ;
            }
            arquivo << '\n';
        }
        arquivo.close();
    }catch(QString &erro){
        throw erro;
    }
}

}
