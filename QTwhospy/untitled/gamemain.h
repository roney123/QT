#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <QObject>
#include <QMessageBox>
#include <QString>
#include <ctime>
#include "joinodbc.h"
//#include "qt5serialport/serial.h"

class gamemain : public QObject
{
    Q_OBJECT
public:
    explicit gamemain(QObject *parent = 0);
    ~gamemain();
    int getSypNumber() const;  //得到卧底数字
    int InsertPlanGameTotal(int n = 0); //加入角色的总人数
    int AddGameTotal(); //已注册的角色+1
    int SubGameTotal(); //已注册的角色-1
    int getGameTotal() const;
    int getPlanGameTotal() const;
    bool isJoinOdbc() const;
    QString getGameName(int g) const;
    QString getComName(int g) const;
    bool getGameOut(int g) const;

    int ComIsSpy(QString &s) ;//这个串口的数据是否是卧底
    QString ComGame(QString &s) const; //这个串口数据的角色
    void InsertGame(); //添加进去所有角色
    QString InsertCom(QString s); //添加串口，并返回与之对应的角色
    void release();//清除数据

private:
    int spy_number;//spy的下标
    int game_total;//已注册的角色人数
    int plan_game_total;//计划的角色人数
    QString game_name[10]; //角色名
    QString com_name[10]; //串口数据
    bool game_out[10]; //角色淘汰
    joinodbc jdb;   //连接数据库的接口

signals:

public slots:
};

#endif // GAMEMAIN_H
