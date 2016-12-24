#include "serial.h"
#include "ui_serial.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include "datadeal.h"
#include <QMessageBox>
#include <QFileDIalog>

serial::serial(QWidget *parent) :
    QWidget(parent),ui(new Ui::serial)
{
    ui->setupUi(this);
    gm = new gamemain();
    open_spy = false;
    ui->closeButton->setEnabled(false); //打开串口后“关闭串口”按钮bu可用
    ui->send1Button->setEnabled(false); //打开串口后“识别”按钮不可用
    ui->startgame->setEnabled(false);//人数满后下一步管用
    ui->picture_left->hide();  //隐藏左边图片
    ui->pushButton_3->hide();//再来一次按钮隐藏
    ui->send3Button->hide(); //是否卧底按钮隐藏
}

serial::~serial()
{
    delete ui;
}


//serial information
void serial::on_startButton_clicked()
{
    my_serialport= new QSerialPort();

    my_serialport->setPortName(ui->comboBox->currentText());    //端口名字
    if(my_serialport->open(QIODevice::ReadWrite))                  //设置为打开的状态
    {
        my_serialport->setBaudRate(19200);  //波特率
        my_serialport->setDataBits(QSerialPort::Data8);
        my_serialport->setParity(QSerialPort::NoParity);
        my_serialport->setStopBits(QSerialPort::OneStop);
        my_serialport->setFlowControl(QSerialPort::NoFlowControl);


        ui->send1Button->setFocus();
        ui->send1Button->setShortcut(QKeySequence::InsertParagraphSeparator ); //设置快捷键为键盘的“回车”键
        ui->send1Button->setShortcut(Qt::Key_Return);


        connect( my_serialport,SIGNAL(readyRead()),this,SLOT(update()));

        ui->startButton->setEnabled(false); //打开串口后“打开串口”按钮不可用
        ui->closeButton->setEnabled(true); //打开串口后“关闭串口”按钮可用
        ui->send1Button->setEnabled(true); //打开串口后“识别”按钮可用

        ui->plangamer->setText(QString::number(gm->getPlanGameTotal()));
        ui->plangamer->update();
        ui->gamer->setText(QString::number(gm->getGameTotal()));
        ui->gamer->update();
    }
    else
        QMessageBox::warning(this, "警告", "串口未打开", QMessageBox::Ok);
}

//recive data
QString serial::update()
{
    QString buf;
    requestData = my_serialport->readAll();  //读取数据
    buf = Convert4Hex(requestData);
    if(buf!= NULL)
    {
        qDebug() << buf ;
    }
    if(open_spy)
    {
        if(buf == "AABB 0800 0004 0102 0004 0007 ")
        {
            QString s2= "AABB0600000002020404";
            my_serialport->write(QString2Hex(s2));
        }
        else if(buf[20] =='0'&&buf[21]=='0')
        {
            int i = gm->ComIsSpy(buf);
            if(i==0)
                QMessageBox::about(this,"身份","NO");
            else if(i==1)
                QMessageBox::about(this,"身份","YES");
            else if(i==-1)
                QMessageBox::about(this,"身份","NULL");
            else if(i==-2)
                QMessageBox::about(this,"身份","Die,YES");
            else if(i==-3)
                QMessageBox::about(this,"身份","Die,NO");
            ui->gamer->setText(QString::number(gm->getGameTotal()));//参与游戏人数获取
            ui->gamer->update();
            if(gm->getGameTotal()==0)
            {
                ui->send3Button->setEnabled(false);
            }
        }
        else
        {
            QMessageBox::warning(this, "警告", "not initialization",QMessageBox::Ok);
        }
    }
    else
    {
        if(buf == "AABB 0800 0004 0102 0004 0007 ")
        {
            QString s2= "AABB0600000002020404";
            my_serialport->write(QString2Hex(s2));
        }
        else if(buf[20] =='0'&&buf[21]=='0')
        {
            QString qs;
            qs = gm->InsertCom(buf);
            QMessageBox::about(this,"身份",qs);
            ui->gamer->setText(QString::number(gm->getGameTotal()));
            ui->gamer->update();
            if(gm->getGameTotal()==gm->getPlanGameTotal())
            {
                ui->send1Button->setEnabled(false);
                ui->startgame->setEnabled(true);
            }
        }
        else
        {
            QMessageBox::warning(this, "警告", "not initialization",QMessageBox::Ok);
        }
    }
    requestData.clear();
    return buf;
}

//close serial
void serial::on_closeButton_clicked()
{
    my_serialport->close();
    delete my_serialport;

    ui->startButton->setEnabled(true);
    ui->closeButton->setEnabled(false);
    ui->send1Button->setEnabled(false);

}



void serial::on_send1Button_clicked()
{
    //buf = "";
    QString s1= "AABB0600000001025251";
    my_serialport->write(QString2Hex(s1));

}





void serial::on_returnButton_clicked()
{
    this->close();
}

void serial::on_startgame_clicked()
{

    open_spy = true;  //打开检查卧底
    ui->picture_left->show();  //显示左边图片
    ui->picture_right->hide();//隐藏右边图片

    ui->send1Button->hide();
    ui->startgame->hide();
    ui->pushButton_3->show();
    ui->send3Button->show();

}

void serial::on_send3Button_clicked()
{
    QString s1= "AABB0600000001025251";
    my_serialport->write(QString2Hex(s1));
}

void serial::on_pushButton_3_clicked()
{
    ui->picture_left->hide();  //隐藏左边图片
    ui->picture_right->show();//显示右边图片

    ui->send1Button->show();
    ui->startgame->show();
    ui->pushButton_3->hide();
    ui->send3Button->hide();
    ui->startgame->setEnabled(false);
    ui->send1Button->setEnabled(true);

    gm->release();
    gm->InsertGame();
    open_spy = false;
}

