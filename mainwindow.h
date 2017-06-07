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
#include "TelaMatriz.h"
#include "TelaArestas.h"

/*
 *  CLASSE RESPONSAVEL PELA TELA PRINCIPAL DO PROGRAMA
 *  TODO USO DOS METODOS DE GRAFO ESTA SENDO FEITO NESTA TELA
*/



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
    void on_pushButtonCriar_clicked();          // Botao de criar a matriz

    void on_pushButtonInserir_clicked();        // Botao para inserir vertice

    void listarVertices();                      // Lista vertices e lista de adjacencias

    void statusGrafo();                         // Atualiza grid de status do grafo

    void limparStatus();                        // Limpa grid de status do grafo

    void validaPeso(QString peso);              // Verifica em tempo real se o peso esta valido

    void habilitarBotoes(bool habilita);        // Habilita os botoes da tela

    void on_pushButtonAdjancente_clicked();     // Adiciona uma adjacencia entre dois vertices

    void on_pushButtonRemoverAdj_clicked();     // Remove uma adjacencia entre dois vertices

    void on_pushButtonBfs_clicked();            // Realiza a busca em largura

    void on_pushButtonCarregar_clicked();       // Carrega um grafo de um arquivo texto

    void on_pushButtonSalvar_clicked();         // Salva o grafo em arquivo texto

    void on_pushButtonHelp_clicked();           // Abre a janela de ajuda

    void on_pushButtonLista_clicked();          // Abre a janela da lista de arestas

    void on_pushButtonMatriz_clicked();         // Abre a janela da matriz de adjacencias

private:
    Ui::MainWindow *ui;
    ED2::Grafo *grafo;
};

#endif // MAINWINDOW_H
