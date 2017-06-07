#include "Vertice.h"

namespace ED2
{

QString Vertice::getDescricao() const
{
    return descricao;
}

void Vertice::setDescricao(const QString &value)
{
    descricao = value;
}

Cor Vertice::getCor() const
{
    return cor;
}

void Vertice::setCor(const Cor &value)
{
    cor = value;
}

int Vertice::getDistancia() const
{
    return distancia;
}

void Vertice::setDistancia(int value)
{
    distancia = value;
}

Vertice *Vertice::getPai() const
{
    return pai;
}

void Vertice::setPai(Vertice *value)
{
    pai = value;
}

std::list<Vertice *> Vertice::getListaAdjacencia() const
{
    return listaAdjacencia;
}

Vertice::Vertice() :
    descricao(""),
    cor(Branco),
    distancia(0),
    pai(0)
{

}

Vertice::~Vertice()
{

}

Vertice::Vertice(QString descricao,std::list<Vertice *> listaAdjacencia):
    descricao(descricao)
{
    this->listaAdjacencia = listaAdjacencia;
}

void Vertice::inserirAdjacente(Vertice *adjacente)
{
    if(!adjacente) throw QString("Parametro vazio");
    listaAdjacencia.push_front(adjacente);
}

void Vertice::removerAdjancente(Vertice *adjacente)
{
    if(!adjacente) throw QString("Parametro vazio");
    int tamAntigo = listaAdjacencia.size();
    listaAdjacencia.remove(adjacente);
    if(tamAntigo==int(listaAdjacencia.size()))
        throw QString(adjacente->getDescricao()+" nao adjacente a "+this->getDescricao());
}

bool Vertice::operator ==(Vertice *segundo)
{
    return this->descricao==segundo->descricao;
}

QString Vertice::getAdjacentes()
{
    QString saida = "";
    for(std::list<Vertice*>::iterator i=listaAdjacencia.begin(); i!=listaAdjacencia.end(); i++) {
        const Vertice *aux = *i;
        saida += " |"+aux->descricao+"| =>";
    }
    return saida;
}

bool Vertice::buscarAdjacente(QString descricao)
{
    for(std::list<Vertice*>::iterator i=listaAdjacencia.begin(); i!=listaAdjacencia.end(); i++) {
        Vertice *aux = *i;
        if(aux->descricao==descricao) return true;
    }
    return false;
}

}
