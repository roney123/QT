#include "joinodbc.h"

//初始化
joinodbc::joinodbc(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QODBC"); //连接库方式
    //qDebug()<<"ODBC driver?"<<db.isValid();
    dsn = QString::fromLocal8Bit("Roney");   //名字
    db.setHostName("127.0.0.1");             //IP
    db.setDatabaseName(dsn);
    //db.setUserName("sa");                 //用户名
    //db.setPassword("198811200");          //密码
    if(!db.open())                   //打开物理连接
    {

        //QMessageBox::information(this,"提示","未初始化打开串口");
    }
    else
    {
        //QMessageBox::information(this,"提示","已初始化打开串口");
        query = new QSqlQuery(db); //执行语句的句柄和库连接
    }
}
//析构
joinodbc::~joinodbc()
{
    delete query;
    if(db.isOpen())
        db.close();//关闭数据连接
}
//数据库是否连接
bool joinodbc::isJoinDB() const
{
    return db.isOpen();
}
//执行S语句
void joinodbc::SQLExec(QString s)
{
    query->exec(s);
}
//调用value()
QVariant joinodbc::getQSqlValue(int i) const
{
    return query->value(i);
}
//运行next
void joinodbc::getQSqlnext()
{
    query->next();
}

