#include "datadeal.h"
#include <QDebug>

//将1-9 a-f字符转化为对应的整数
 char ConvertHexChar(char ch)
    {
        if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return (-1);
    }
//将字符型进制转化为16进制
 QByteArray QString2Hex(QString str)
    {
        QByteArray senddata;
        int hexdata,lowhexdata;
        int hexdatalen = 0;
        int len = str.length();
        senddata.resize(len/2);
        char lstr,hstr;
        for(int i=0; i<len; )
        {
            hstr=str[i].toLatin1();   //字符型
            if(hstr == ' ')
            {
                i++;
                continue;
            }
            i++;
            if(i >= len)
                break;
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
                break;
            else
                hexdata = hexdata*16+lowhexdata;
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        return senddata;
    }

//将接收的一串QByteArray类型的16进制,转化为对应的字符串16进制
 QString ShowHex(QByteArray str)
 {

     QDataStream out(&str,QIODevice::ReadWrite);   //将str的数据 读到out里面去
     QString buf;
     while(!out.atEnd())
     {
           qint8 outChar = 0;
           out >> outChar;   //每次一个字节的填充到 outchar
           QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0')).toUpper() + QString("");   //2 字符宽度

           buf += str;
     }
     return buf;
 }

//将接收的一串QByteArray类型的16进制,每2个16进制转化为1个字的16进制的字符串
 QString Convert4Hex(QByteArray str)
 {

     QDataStream out(&str,QIODevice::ReadWrite);   //将str的数据 读到out里面去
     QString buf;
     while(!out.atEnd())
     {
           qint16 outChar = 0;
           out>>outChar;   //每次一个字节的填充到 outchar
           QString str = QString("%1").arg(outChar&0xFFFF,4,16,QLatin1Char('0')).toUpper() + QString(" ");   //2 字符宽度

           buf += str;
     }
     return buf;
 }










