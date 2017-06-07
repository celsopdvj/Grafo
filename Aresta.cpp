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

int Aresta::getPeso() const
{
    return peso;
}

void Aresta::setPeso(int value)
{
    peso = value;
}

Aresta::Aresta() :
    origem(0),
    destino(0),
    peso(0)
{

}

Aresta::Aresta(Vertice *origem, Vertice *destino) :
    peso(0)
{
    if(!origem || !destino) throw QString("Parametro vazio");
    this->origem = origem;
    this->destino = destino;
}

Aresta::Aresta(Vertice *origem, Vertice *destino, int peso) :
    peso(peso)
{
    if(!origem || !destino) throw QString("Parametro vazio");
    this->origem = origem;
    this->destino = destino;
}

}
