#ifndef TELAARESTAS_H
#define TELAARESTAS_H

#include <QDialog>
#include "Grafo.h"

/*
 * CLASSE RESPONSAVEL POR IMPRIMIR UMA TELA DE LISTAGEM DE
 * ARESTAS E SEUS PESOS
*/

namespace Ui {
class TelaArestas;
}

class TelaArestas : public QDialog
{
    Q_OBJECT

public:
    explicit TelaArestas(QWidget *parent = 0);
    ~TelaArestas();
    void listarArestas(ED2::Grafo *grafo);

private:
    Ui::TelaArestas *ui;
};

#endif // TELAARESTAS_H
