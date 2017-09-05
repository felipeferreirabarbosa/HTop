#ifndef GRAFICO_H
#define GRAFICO_H

#include <QGraphicsScene>
#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
class Grafico;
}

class Grafico : public QDialog
{
    Q_OBJECT

public:
    explicit Grafico(QWidget *parent = 0);
    void setCoreId(int);
    int coreId;
    ~Grafico();
    long double CPU();

private:
    Ui::Grafico *ui;
    QTimer dataTimer;

private slots:

    void makePlot();
public slots:
    void realtimeDataSlot();
};

#endif // GRAFICO_H
