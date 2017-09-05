#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QThread cThread;

private slots:
    void on_pushButtonSTOP_clicked();

    void on_pushButtonCONTINUE_clicked();

    void on_pushButtonKILL_clicked();

    void on_pushButtonCPU_clicked();

    void on_pushButtonCPUGRAFICS_clicked();

    void on_pushButtonEXIT_clicked();

    void on_lineEditCPU_textChanged(const QString &arg1);

    void on_pushButtonGrep_clicked();

    void on_pushButtonPstree_clicked();

    void on_pushButtonALL_clicked();


private:
    Ui::MainWindow *ui;
public slots:


};

#endif // MAINWINDOW_H
