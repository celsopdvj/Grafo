#include "TelaMatriz.h"
#include "ui_TelaMatriz.h"

TelaMatriz::TelaMatriz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaMatriz)
{
    ui->setupUi(this);
}

TelaMatriz::~TelaMatriz()
{
    delete ui;
}

void TelaMatriz::listarMatriz(ED2::Grafo *grafo)
{
    QString str_matriz="",header="\t";
    int **matriz = grafo->getMatrizAdjacencia();
    ui->textEditMatriz->clear();
    for(int i=0;i<grafo->getTamanho();i++)
    {
        if(i<grafo->getVerticesOcupados())
        {
            ED2::Vertice *aux = grafo->getVerticePorPosicao(i);
            header += aux->getDescricao()+'\t';
            str_matriz += aux->getDescricao()+'\t';
        }
        else
        {
           header += "?\t";
           str_matriz += "?\t";
        }
        for(int j=0;j<grafo->getTamanho();j++)
        {
            str_matriz += QString::number(matriz[i][j])+'\t';
        }
        str_matriz += '\n';
    }
    ui->textEditMatriz->setText(header+'\n'+str_matriz);
}
