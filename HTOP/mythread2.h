#ifndef MYTHREAD2_H
#define MYTHREAD2_H
#include <QDebug>
#include <QThread>
#include <QObject>
#include "grafico.h"
#include <QTextEdit>
#include <mainwindow.h>
class MyThread2 : public QObject
{
    Q_OBJECT
public:
    explicit MyThread2(QObject *parent=0,QTextEdit * textoEdit=0);
    void DoSetup(QThread & cThread);
private:
    QTextEdit * textoEdit;

public slots:
    void run();

};

#endif // MYTHREAD2_H
