#ifndef TELALISTA_H
#define TELALISTA_H

#include <QDialog>
#include "Grafo.h"

namespace Ui {
class TelaLista;
}

class TelaLista : public QDialog
{
    Q_OBJECT

public:
    explicit TelaLista(QWidget *parent = 0);
    ~TelaLista();
    void listar(ED2::Grafo *grafo);

private:
    Ui::TelaLista *ui;
};

#endif // TELALISTA_H
