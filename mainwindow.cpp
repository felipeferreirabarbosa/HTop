#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grafico.h"

#include <QtCore/QCoreApplication>
#include "mythread.h"
#include "mythread2.h"

#include <QMessageBox>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/sysinfo.h>
#define _GNU_SOURCE
#include <sched.h>
#include <string>
int NUM_PROCS  =get_nprocs_conf();




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    QThread *dThread = new QThread();
    MyThread2 * mThread2=new MyThread2(parent,this->ui->textEdit);
    mThread2->DoSetup(*dThread);
    mThread2->moveToThread(QApplication:: instance()->thread());
    dThread->start();
    dThread->quit();

    MyThread * mThread[NUM_PROCS];
    int coreId;
    for(coreId=0;coreId<NUM_PROCS;coreId++){
        mThread[coreId]=new MyThread(parent,coreId);
        mThread[coreId]->DoSetup(cThread);
        mThread[coreId]->moveToThread(QApplication:: instance()->thread());

    }





}

MainWindow::~MainWindow()
{
    delete ui;
  }

void lerArq(char nome[],char saida[]){
    int i=0;
    FILE *file;
    file = fopen(nome, "r");

    while((saida[i] = fgetc(file)) != EOF)
    {
        i++;
    }

    saida[i+1] = '\0';

    fclose(file);

}

void MainWindow::on_pushButtonSTOP_clicked()
{
    pid_t pid;
    pid = ui-> lineEditPID ->text().toInt(NULL);
    kill(pid, SIGSTOP);
    return;
}


void MainWindow::on_pushButtonCONTINUE_clicked()
{
    pid_t pid;
    pid = ui-> lineEditPID ->text().toInt(NULL);
    kill(pid, SIGCONT);
    ui->lineEditPID->setText("");
}

void MainWindow::on_pushButtonKILL_clicked()
{
    pid_t pid;
    pid = ui-> lineEditPID ->text().toInt(NULL);
    kill(pid,SIGKILL);
    ui->lineEditPID->setText("");
}

void MainWindow::on_pushButtonCPU_clicked()
{
    if(ui->lineEditPID->text().compare("")==0){
        QMessageBox *obj=new QMessageBox(this);
        obj->setText("Voce precisa digitar um PID");
        obj->setWindowModality(Qt::NonModal);
        obj->setInformativeText("Clique OK para continuar");

        obj->setStandardButtons(QMessageBox::Ok);
        obj-> setDefaultButton(QMessageBox::Ok);
        int ret=obj->exec();
        ui->lineEditCPU-> setText("");

        return;
    }

    pid_t pid;
    cpu_set_t set;
    int num;


    pid = ui-> lineEditPID -> text().toInt(NULL);
    num = ui-> lineEditCPU -> text().toInt(NULL);

    CPU_ZERO(&set);
    CPU_SET(num, &set);

    sched_setaffinity(pid, sizeof(cpu_set_t), &set);

    ui->lineEditPID->setText("");
    ui->lineEditCPU->setText("");
}


void MainWindow::on_pushButtonCPUGRAFICS_clicked()
{
    cThread.start();
    cThread.quit();

}

void MainWindow::on_pushButtonEXIT_clicked()
{
    exit(0);
}

void MainWindow::on_lineEditCPU_textChanged(const QString &arg1)
{

    if(ui->lineEditCPU-> text().toInt(NULL) >= NUM_PROCS){
        //opção inválida
        QMessageBox *obj=new QMessageBox(this);

        QString aux="Esse numero de CPUs eh invalido\nNumero maximo de CPUs= ";
        char y[5];
        sprintf(y,"%d",NUM_PROCS);
        aux=aux+y+". Logo so eh possivel digitar cores ate esse valor menos 1, pois o core inicial eh zero.";

        obj->setText(aux);
        obj->setWindowModality(Qt::NonModal);
        obj->setInformativeText("Clique OK para tentar novamente");

        obj->setStandardButtons(QMessageBox::Ok);
        obj-> setDefaultButton(QMessageBox::Ok);
        int ret=obj->exec();
        ui->lineEditCPU-> setText("");

    }
}

void MainWindow::on_pushButtonGrep_clicked()
{
    if(ui->lineEditProcess->text().compare("")==0){
        QMessageBox *obj=new QMessageBox(this);
        obj->setText("Voce precisa digitar o nome de um processo para busca.");
        obj->setWindowModality(Qt::NonModal);
        obj->setInformativeText("Clique OK para continuar");

        obj->setStandardButtons(QMessageBox::Ok);
        obj-> setDefaultButton(QMessageBox::Ok);
        int ret=obj->exec();
        return;
    }


    char programa[200]="ps auf|grep ";
    strcat(programa,(ui->lineEditProcess->text().toStdString()).c_str());
    strcat(programa," > lista.txt");

    FILE *s = fopen("lista.txt","r");
    fseek(s,0, SEEK_END);
    int byteCount = ftell(s);
    fclose(s);
    char saida[byteCount];

    system(programa);
    lerArq("lista.txt",saida);

    QMessageBox *obj2=new QMessageBox(this);
    obj2->setText(saida);
    obj2->setWindowModality(Qt::NonModal);
    obj2->setInformativeText("Clique OK para continuar");

    obj2->setStandardButtons(QMessageBox::Ok);
    obj2-> setDefaultButton(QMessageBox::Ok);
    int ret2=obj2->exec();
    ui->lineEditProcess->setText("");

}

void MainWindow::on_pushButtonPstree_clicked()
{
    if(ui->lineEditProcess->text().compare("")==0){
        QMessageBox *obj=new QMessageBox(this);
        obj->setText("Voce precisa digitar o nome de um processo para busca.");
        obj->setWindowModality(Qt::NonModal);
        obj->setInformativeText("Clique OK para continuar");

        obj->setStandardButtons(QMessageBox::Ok);
        obj-> setDefaultButton(QMessageBox::Ok);
        int ret=obj->exec();
        return;
    }


    char programa[200]="pstree -a | grep ";


    strcat(programa,(ui->lineEditProcess->text().toStdString()).c_str());
    strcat(programa," > lista.txt");
    FILE *s = fopen("lista.txt","r");
    fseek(s,0, SEEK_END);
    int byteCount = ftell(s);
    fclose(s);
    char saida[byteCount];


    system(programa);
    lerArq("lista.txt",saida);
    QMessageBox *obj2=new QMessageBox(this);
    obj2->setText(saida);
    obj2->setWindowModality(Qt::NonModal);
    obj2->setInformativeText("Clique OK para continuar");

    obj2->setStandardButtons(QMessageBox::Ok);
    obj2-> setDefaultButton(QMessageBox::Ok);
    int ret2=obj2->exec();
    ui->lineEditProcess->setText("");

}

void MainWindow::on_pushButtonALL_clicked()
{
    system("ps au>lista.txt");
    FILE *s = fopen("lista.txt","r");
    fseek(s,0, SEEK_END);
    int byteCount = ftell(s);
    fclose(s);
    char saida[byteCount];
    lerArq("lista.txt",saida);
    ui->textEdit->setText(saida);
}
