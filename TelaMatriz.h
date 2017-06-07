#ifndef TELAMATRIZ_H
#define TELAMATRIZ_H

#include <QDialog>
#include <QTableWidgetItem>
#include "Grafo.h"



/*
 * CLASSE RESPONSAVEL POR IMPRIMIR UMA TELA DE LISTAGEM DA
 * MATRIZ DE ADJACENCIAS E SEUS PESOS
*/

namespace Ui {
class TelaMatriz;
}

class TelaMatriz : public QDialog
{
    Q_OBJECT

public:
    explicit TelaMatriz(QWidget *parent = 0);
    ~TelaMatriz();
    void listarMatriz(ED2::Grafo *grafo);
private:
    Ui::TelaMatriz *ui;
};

#endif // TELAMATRIZ_H
