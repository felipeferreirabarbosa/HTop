#include "mythread.h"
#include <QtCore>
#include "grafico.h"
#include <signal.h>
MyThread::MyThread(QObject *parent, int coreId):
    QObject(parent)
{
    this->coreId=coreId;
}
void MyThread::DoSetup(QThread & cThread){

    connect(&cThread,SIGNAL(started()), this, SLOT(DoWork()));

}


void MyThread:: DoWork(){
    //thread starts here

    this->g=new Grafico();
    this->g->setCoreId(this->coreId);

    this->g->setModal(true);
    this->g->exec();


}
