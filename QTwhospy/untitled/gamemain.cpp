#include "gamemain.h"

gamemain::gamemain(QObject *parent) : QObject(parent),jdb(parent)
{
    qsrand(time(NULL));//随机函数初始化
    spy_number = 0;
    game_total = 0;
    plan_game_total = 0;
    for( auto& i:game_name)
        i = "0";
    for( auto& i:com_name)
        i ="0";
    for( auto& i:game_out)
        i = 1;
}
gamemain::~gamemain()
{
    jdb.~joinodbc();

}
//得到卧底数字
int gamemain::getSypNumber() const
{
    return this->spy_number;
}
//加入角色的总人数
int gamemain::InsertPlanGameTotal(int n)
{
    this->plan_game_total = n;
    return this->plan_game_total;
}
//已注册的角色+1
int gamemain::AddGameTotal()
{
    game_total += 1;
    return game_total;
}
//已注册的角色-1
int gamemain::SubGameTotal()
{
    this->game_total -= 1;
    return this->game_total;
}

int gamemain::getGameTotal() const
{
    return game_total;
}

int gamemain::getPlanGameTotal() const
{
    return plan_game_total;
}

bool gamemain::isJoinOdbc() const
{
    return jdb.isJoinDB();
}

QString gamemain::getGameName(int g) const
{
    if(g < getPlanGameTotal())
        return game_name[g];
    else
    {
        qDebug() << "查询角色超过范围" << endl;
        return -1;
    }
}

QString gamemain::getComName(int g) const
{
    if(g < getPlanGameTotal())
        return com_name[g];
    else
    {
        qDebug() << "查询角色超过范围" << endl;
        return -1;
    }
}
bool gamemain::getGameOut(int g) const
{
    if(g < getPlanGameTotal())
        return game_out[g];
    else
    {
        qDebug() << "查询角色超过范围" << endl;
        return 0;
    }

}

//这个串口的数据是否是卧底
int gamemain::ComIsSpy(QString &s)
{
    int n = getPlanGameTotal();
    for(int i=0;i<n;i++)
    {
        if(s == com_name[i])
        {
            if(!getGameOut(i))
            {
                game_out[i] = 1;
                SubGameTotal();
                if(i == getSypNumber())
                {
                    return 1; //是
                }

                else
                    return 0; //不是
            }
            else
            {
                if(i == getSypNumber())
                {
                    return -2; //已out是卧底
                }

                else
                    return -3; //已out不是卧底
            }
        }
    }
    //QMessageBox::information(this,"提示","无匹配串口数据");
    return -1; //无此卡
}
//这个串口数据的角色
QString gamemain::ComGame(QString &s) const
{
    int n = getPlanGameTotal();
    for(int i=0;i<n;i++)
    {
        if(s == com_name[i])
            return getGameName(i);
    }
    //QMessageBox::information(this,"提示","无匹配角色数据");
    return "-1";
}

//添加进去所有角色
void gamemain::InsertGame()
{
    //查询游戏者有多少方案可以玩
    QString s ="select* from play_number where number = ";
    s = s + QString::number(getPlanGameTotal());
    //qDebug() << "fangan" << s;
    jdb.SQLExec(s);
    jdb.getQSqlnext();
    int num = int(jdb.getQSqlValue(1).toInt());
    //qDebug() << "fangan" << num;
    //选择第rn中方案
    int rn = qrand()%num+1;
    //qDebug() << "rn" << rn;
    s = "select* from player_" + QString::number(num) + " where opt=" + QString::number(rn);
    jdb.SQLExec(s);
    jdb.getQSqlnext();
    for(int i=0;i<num;i++)
        game_name[i] = jdb.getQSqlValue(i+1).toString();
    //添加对应的卧底下标
    s = "select spy from game_over" + QString::number(num) + " where opt=" + QString::number(rn);
    jdb.SQLExec(s);
    jdb.getQSqlnext();
    spy_number = jdb.getQSqlValue(0).toInt() - 1;
}
//添加串口，并返回与之对应的角色
 QString gamemain::InsertCom(QString s)
 {
     //添加串口到随机位置
     qDebug()<<  ComGame(s);
     if(ComGame(s) != "-1")
         return "重复卡："+ComGame(s);
     int rn = qrand()%getPlanGameTotal();
     while(getComName(rn)!="0")
     {
         rn++;
         if(rn == getPlanGameTotal())
            rn = 0;
     }
     com_name[rn] = s;
     game_out[rn] = 0;
     qDebug()<< AddGameTotal();
     return getGameName(rn);
 }

void gamemain::release()
{
    spy_number = 0;
    game_total = 0;
    for( auto& i:game_name)
        i = "0";
    for( auto& i:com_name)
        i ="0";
    for( auto& i:game_out)
        i = 1;
}
