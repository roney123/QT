#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <windows.h>
//#include "mainwindow.h"
#include "gamemain.h"
namespace Ui {
class serial;
}

class serial : public QWidget
{
    Q_OBJECT

public:
    gamemain *gm;
    bool open_spy; //是否打开检查卧底
    explicit serial(QWidget *parent = 0);
    ~serial();
private slots:
    void on_startButton_clicked();

     QString update();

     void on_closeButton_clicked();


     void on_send1Button_clicked();



     void on_returnButton_clicked();

     void on_startgame_clicked();

     void on_send3Button_clicked();

     void on_pushButton_3_clicked();



private:
    Ui::serial  *ui;
    QSerialPort *my_serialport;
    QByteArray  requestData;
};

#endif // SERIAL_H
