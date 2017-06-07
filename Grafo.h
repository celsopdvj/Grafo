#ifndef GRAFO_H
#define GRAFO_H

#include <stdint.h>
#include <vector>
#include <queue>
#include "Vertice.h"
#include "Aresta.h"

namespace ED2
{


/*
 *  CLASSE RESPONSAVEL POR MANIPULAR VERTICES ARESTAS E ADJACENCIAS
 *  ESSA CLASSE DETERMINA COMO SERAO MANIPULADOS CADA ELEMENTO DO GRAFO
 *  ALEM DE IPLEMENTAR O METODO DE BUSCA EM LARGURA
*/

class Grafo
{
    int tamanho;                                                    // Quantidade maxima de vertices
    Vertice **vertices;                                             // Colecao de vertices
    std::vector<Aresta*> *arestas;                                  // Vector de Arestas (sem tamanho maximo)
    int ultimoVerticeOcupado;                                       // Indice do ultimo vertice inserido
    int **matrizAdjacencia;                                         // Matriz de adjacencia

public:
    //============================= OPERACOES DO GRAFO EM GERAL ========================

    Grafo(int tamanho);                                             // Construtor com alocacao da colecao de vertices
    ~Grafo();                                                       // Destrutor para desalocar colecao de vertices

    bool isEmpty() const{return ultimoVerticeOcupado==0;}           // Verifica se nao tem vertices inseridos
    bool isFull() const{return ultimoVerticeOcupado==tamanho;}      // Verifica se todos vertices estao inseridos
    int getTamanho() const;                                         // Retorna tamanho maximo da colecao de vertices

    bool conexo() const;                                            // Verifica se o grafo e conexo
    bool direcionado() const;                                       // Verifica se o grafo e direcionado

    //============================= OPERACOES RELACIONADAS A VERTICE ====================

    void incluirVertice(Vertice *vertice);                          // Inclui um vertice na colecao
    bool existeVertice(QString descricao) const;                    // Verifica se um vertice com mesma descricao existe na colecao
    int getPosicaoVertice(Vertice *vertice) const;                  // Retorna a posicao de um vertice na colecao
    int getVerticesOcupados()const {return ultimoVerticeOcupado;}   // Retorna a quantidade de vertices inseridos
    Vertice *getVertice(QString descricao) const;                   // Retorna um vertice com mesma descricao da colecao
    Vertice *getVerticePorPosicao(int pos) const;                   // Retorna o vertice desta posicao da colecao
    Vertice **getListaVertices() const;                             // Retorna a colecao de vertices

    //============================== OPERACOES RELACIONADAS A ARESTAS ====================

    void incluirAresta(Vertice *a, Vertice *b);                     // Inclui uma aresta com origem A e destino B caso nao exista
    void incluirAresta(Vertice *a, Vertice *b, int peso);           // Inclui uma aresta com origem A e destino B caso nao exista
    void removerAresta(Vertice *a,Vertice *b);                      // Remove uma aresta com origem A e destino B caso exista
    std::vector<Aresta*> *getArestas() const;                       // Retorna a vector de arestas
    bool existeAresta(Vertice *a,Vertice *b) const;                 // Verifica se existe uma aretsa com origem a e destino b
    int getQuantidadeArestas() const;                               // Retorna a quantidade de arestas

    //============================== OPERACOES RELACIONADAS A MATRIZ DE AJDACENCIA ========

    void incluirAdjacencia(Vertice *a, Vertice *b, int peso) const; // Coloca o peso na posicao que representa os vertices na matriz
    void excluirAdjacencia(Vertice *a,Vertice *b);                  // Coloca o peso 0 na posicao que representa os vertices na matriz
    int **getMatrizAdjacencia() const;                              // retorna a matriz
    void setMatrizAdjacencia(int **value);                          // Atribui uma nova matriz

    //============================== OPERACOES DE BUSCA EM LARGURA ========================

    int BuscaEmLargura(Vertice *partida) const;                     // Metodo de BFS com origem em *partida
    QString printPath(Vertice *partida, Vertice *destino);          // Retorna uma string com o caminho de partida a destino
};

}

#endif // GRAFO_H
