#include "mythread2.h"
#include "unistd.h"


MyThread2::MyThread2(QObject *parent,QTextEdit * textoEdit ):
    QObject(parent)
{
    this->textoEdit = textoEdit;

}

void MyThread2::DoSetup(QThread & cThread){

    connect(&cThread,SIGNAL(started()), this, SLOT(run()));

}

void leitura(char nome[],char saida[]){
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

void MyThread2:: run(){
        system("ps au>lista.txt");
        FILE *s = fopen("lista.txt","r");
        fseek(s,0, SEEK_END);
        int byteCount = ftell(s);
        fclose(s);
        char saida[byteCount];
        leitura("lista.txt",saida);
        textoEdit->setText(saida);


}




