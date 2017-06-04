#ifndef ARESTA_H
#define ARESTA_H

#include "Vertice.h"

namespace ED2
{

class Aresta
{
    Vertice *origem;
    Vertice *destino;
public:

    //=========== OPERACOES GERAIS VERTICE ==============
    Aresta();                                   // Construtor padrao
    Aresta(Vertice *origem,Vertice *destino);   // Construtor que inicializa os atributos por parametro
    bool operator ==(Aresta *b);                // Verifica se a descricao de dois vertices é a mesma

    Vertice *getOrigem() const;                 // Retorna a origem da aresta
    Vertice *getDestino() const;                // Retorna o destino da aresta

    void setOrigem(Vertice *value);             // Atribui a origem da aresta
    void setDestino(Vertice *value);            // Atribui o destino da aresta
};

}

#endif // ARESTA_H
