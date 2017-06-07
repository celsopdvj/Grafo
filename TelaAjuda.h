#ifndef TELAAJUDA_H
#define TELAAJUDA_H

#include <QDialog>

/*
 * CLASSE RESPONSAVEL POR IMPRIMIR UMA TELA DE AJUDA, COM O PADRAO
 * DE ESCRITA QUE O PROGRAMA USA EM ARQUIVO TXT
*/

namespace Ui {
class TelaAjuda;
}

class TelaAjuda : public QDialog
{
    Q_OBJECT

public:
    explicit TelaAjuda(QWidget *parent = 0);
    ~TelaAjuda();

private:
    Ui::TelaAjuda *ui;
};

#endif // TELAAJUDA_H
