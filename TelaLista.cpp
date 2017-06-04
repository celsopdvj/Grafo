#include "TelaLista.h"
#include "ui_TelaLista.h"

TelaLista::TelaLista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaLista)
{
    ui->setupUi(this);
}

TelaLista::~TelaLista()
{
    delete ui;
}

void TelaLista::listar(ED2::Grafo *grafo)
{
    ED2::Vertice **lista = grafo->getListaVertices();
    ui->textEditAdjacente->clear();
    QString saida="";
    for(int i=0;i<grafo->getVerticesOcupados();i++)
    {
        saida += "<p>"+lista[i]->getDescricao()+" ( "+lista[i]->getAdjacentes()+"  )</p>\n";
    }
    ui->textEditAdjacente->setText(saida);
}
