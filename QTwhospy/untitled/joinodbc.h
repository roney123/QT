#ifndef JOINODBC_H
#define JOINODBC_H

#include <QObject>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <qDebug>

class joinodbc : public QObject
{
    Q_OBJECT
public:
    explicit joinodbc(QObject *parent = 0);
    ~joinodbc();
    void SQLExec(QString s);//执行s语句
    QVariant getQSqlValue(int i) const;//得到value()
    void getQSqlnext();//运行next
    bool isJoinDB() const;//数据库是否连接
private:
    QSqlDatabase db;  //数据库句柄
    QString dsn;
    QSqlQuery *query; //执行语句的句柄
signals:

public slots:
};

#endif // JOINODBC_H
