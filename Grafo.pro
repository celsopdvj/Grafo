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
    TelaLista.cpp \
    TelaMatriz.cpp

HEADERS  += mainwindow.h \
    Vertice.h \
    Grafo.h \
    Aresta.h \
    PersistenciaGrafo.h \
    TelaAjuda.h \
    TelaLista.h \
    TelaMatriz.h

FORMS    += mainwindow.ui \
    TelaAjuda.ui \
    TelaLista.ui \
    TelaMatriz.ui

RESOURCES += \
    arquivos.qrc
