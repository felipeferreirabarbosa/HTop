#-------------------------------------------------
#
# Project created by QtCreator 2017-09-03T07:06:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = HTOP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grafico.cpp \
    mythread.cpp \
    qcustomplot.cpp \
    mythread2.cpp

HEADERS  += mainwindow.h \
    grafico.h \
    mythread.h \
    qcustomplot.h \
    mythread2.h

FORMS    += mainwindow.ui \
    grafico.ui
