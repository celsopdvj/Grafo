#ifndef VERTICE_H
#define VERTICE_H

#include <QString>
#include <list>

namespace ED2
{

/*
 * CLASSE RESPONSAVEL POR MANIPULAR VERTICES E SUA LISTA DE ADJACENCIA
*/

enum Cor {Branco,Cinza,Preto};

class Vertice
{
    QString descricao;
    std::list<Vertice *> listaAdjacencia;
    Cor cor;
    int distancia;
    Vertice *pai;
public:

    //============================ OPERACOES GERAIS DE VERTICE =====================
    Vertice();
    ~Vertice();
    Vertice(QString descricao,std::list<Vertice *> listaAdjacencia);
    bool operator ==(Vertice *segundo);

    QString getDescricao() const;
    Cor getCor() const;
    int getDistancia() const;
    Vertice *getPai() const;

    void setDescricao(const QString &value);
    void setCor(const Cor &value);
    void setDistancia(int value);
    void setPai(Vertice *value);


    //============================ OPERACOES DE LISTA DE AJDACENCIA =================
    void inserirAdjacente(Vertice *adjacente);
    void removerAdjancente(Vertice *adjacente);
    bool buscarAdjacente(QString descricao);
    QString getAdjacentes();
    std::list<Vertice *> getListaAdjacencia() const;

};

}

#endif // VERTICE_H
