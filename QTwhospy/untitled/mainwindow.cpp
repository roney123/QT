#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = new serial();
    setWindowTitle("谁是卧底");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    s->gm->release();
    s->gm->InsertPlanGameTotal(5+ui->comboBox->currentIndex());
    //qDebug() << s->gm->getPlanGameTotal();
    s->open_spy = false;
    s->gm->InsertGame();
    this->close();
    s->show();
}



void MainWindow::on_textButton_clicked()
{
    text t;
    t.show();
    t.exec();


}
