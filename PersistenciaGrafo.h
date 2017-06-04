#ifndef PERSISTENCIAGRAFO_H
#define PERSISTENCIAGRAFO_H

#include "Grafo.h"
#include <fstream>
#include <QStringList>

/*
 *  CLASSE RESPONSAVEL POR MANIPULACAO DE ARQUIVOS
 *  ESCRITA E LEITURA DE GRAFOS EM ARQUIVO TXT
*/
namespace ED2
{

class PersistenciaGrafo
{
public:
    PersistenciaGrafo();
    static Grafo *carregarGrafo(QString nomeDoArquivo);             // monta um grafo a partir de um arquivo texto
    static void salvarGrafo(Grafo *grafo,QString nomeDoArquivo);    // salva o grafo em um arquivo texto
};

}

#endif // PERSISTENCIAGRAFO_H
