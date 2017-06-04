#include "TelaAjuda.h"
#include "ui_TelaAjuda.h"

TelaAjuda::TelaAjuda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TelaAjuda)
{
    ui->setupUi(this);
}

TelaAjuda::~TelaAjuda()
{
    delete ui;
}
