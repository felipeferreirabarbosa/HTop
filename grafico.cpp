#include "grafico.h"
#include "ui_grafico.h"
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



Grafico::Grafico(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Grafico)
{
    ui->setupUi(this);
    Grafico::makePlot();
}
void Grafico::setCoreId(int coreId){

    this->coreId=coreId;
    char y[5];
    sprintf(y,"%d",coreId);
    ui->label2->setText(y);
}

Grafico::~Grafico()
{
    delete ui;


}

void Grafico::makePlot(){
    ui->customPlot->addGraph(); // blue line
    ui->customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    //ui->customPlot->addGraph(); // red line
    //ui->customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(0, 100);

    // make left and bottom axes transfer their ranges to right and top axes:
 //   connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
 //   connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

long double Grafico:: CPU(){
    int num_PROCS  =get_nprocs_conf();
    long double a[num_PROCS], b[num_PROCS], cpu,soma=0;
    FILE *fp;
    int i;

    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %Lf",&a[0]);
    for(i=1;i<=num_PROCS;i++){
        fscanf(fp," %Lf",&a[i]);
    }
    fclose(fp);
    /*
    sleep(1);

    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %Lf",&b[0]);

    for(i=1;i<num_PROCS;i++){
        fscanf(fp," %Lf",&b[i]);
    }
    fclose(fp);

    for(i=1;i<=num_PROCS;i++){
        soma+=a[i];
    }*/
    cpu = (a[this->coreId+1]/a[0])*100;
    printf("The current CPU %i utilization is : %Lf\n",this->coreId,100-cpu);
    return 100-cpu;

}


void Grafico:: realtimeDataSlot(){

    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      //ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      ui->customPlot->graph(0)->addData(key, CPU());


      //ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
     /* ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
            , 0);
      lastFpsKey = key;
      frameCount = 0;*/
    }

}
