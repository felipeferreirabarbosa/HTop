#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QDebug>
#include <QThread>
#include <QObject>
#include "grafico.h"

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent=0,int coreId=0);
    void DoSetup(QThread & cThread);
    Grafico *g;
    int coreId;

public slots:
    void DoWork();

};

#endif // MYTHREAD_H
