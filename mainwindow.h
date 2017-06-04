#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyle>
#include <QDesktopWidget>
#include <QRegExp>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "PersistenciaGrafo.h"
#include <QFileDialog>
#include "TelaAjuda.h"
#include "Vertice.h"
#include "Grafo.h"
#include "TelaLista.h"
#include "TelaMatriz.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonCriar_clicked();

    void on_pushButtonInserir_clicked();

    void listarVertices();

    void listarArestas();

    void statusGrafo();

    void limparStatus();

    void habilitarBotoes(bool habilita);

    void on_pushButtonAdjancente_clicked();

    void on_pushButtonRemoverAdj_clicked();

    void on_pushButtonBfs_clicked();

    void on_pushButtonCarregar_clicked();

    void on_pushButtonSalvar_clicked();

    void on_pushButtonHelp_clicked();

    void on_pushButtonLista_clicked();

    void on_pushButtonMatriz_clicked();

private:
    Ui::MainWindow *ui;
    ED2::Grafo *grafo;
};

#endif // MAINWINDOW_H
