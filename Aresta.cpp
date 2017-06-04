#include "Aresta.h"

namespace ED2
{

Vertice *Aresta::getOrigem() const
{
    return origem;
}

Vertice *Aresta::getDestino() const
{
    return destino;
}

void Aresta::setOrigem(Vertice *value)
{
    origem = value;
}

void Aresta::setDestino(Vertice *value)
{
    destino = value;
}

bool Aresta::operator ==(Aresta *b)
{
    return this->getOrigem()==b->getOrigem() && this->getDestino()==b->getDestino();
}

Aresta::Aresta() :
    origem(0),
    destino(0)
{

}

Aresta::Aresta(Vertice *origem, Vertice *destino)
{
    if(!origem || !destino) throw QString("Parametro vazio");
    this->origem = origem;
    this->destino = destino;
}

}
