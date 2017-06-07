#-------------------------------------------------
#
# Project created by QtCreator 2017-05-02T21:24:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Grafos
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    Vertice.cpp \
    Grafo.cpp \
    Aresta.cpp \
    PersistenciaGrafo.cpp \
    TelaAjuda.cpp \
    TelaMatriz.cpp \
    TelaArestas.cpp

HEADERS  += mainwindow.h \
    Vertice.h \
    Grafo.h \
    Aresta.h \
    PersistenciaGrafo.h \
    TelaAjuda.h \
    TelaMatriz.h \
    TelaArestas.h

FORMS    += mainwindow.ui \
    TelaAjuda.ui \
    TelaMatriz.ui \
    TelaArestas.ui

RESOURCES += \
    arquivos.qrc
