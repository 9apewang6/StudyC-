#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QList>
#include <QMessageBox>
#include <QDateTime>
#include "SerialCommCfg.h"
class SerailQt:public QObject
{
    Q_OBJECT
public:
    explicit SerailQt();
    ~SerailQt();
    bool Open(const SerialCommInfo& info);
    void Close();

   
    int SendData(const QString& msg);
   

    bool IsOpened(void) { return(m_bOpened); }
    void getMsg(QString& msg)const;
public slots:
    void recvMsg();
private:
    void parseMsg(const QString& msg);
    void findFreePorts();
private:
    bool m_bOpened;
    QSerialPort *serialPort=nullptr;
    QString m_msg;
};

#endif // MAINWINDOW_H#pragma once
