#pragma once

#include <QtWidgets/QWidget>
#include "ui_MITACTServer.h"
#include <ActiveQt/QAxWidget>
class MITACTServer : public QWidget
{
    Q_OBJECT

public:
    MITACTServer(QWidget *parent = Q_NULLPTR);
    ~MITACTServer();

    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    int CheckDeviceString(QString szDevice, int ICheckType, int ISize, int& lpIDeviceType, QString& lpszDeviceName, int& lpIDeviceNumber, int & lpIDeviceRadix);
    int Close();
    int Connect();
    int Disconnect();
    int EntryDeviceStatus(QString sszDeviceList, int ISize, int IMonitorCycle, int& lpIData);
    int FreeDeviceStatus();
    int GetClockData(int& lpsYear, int& lpsMonth, int& lpsDay, int& lpsDayOfWeek, int& lpsHour, int& lpsMinute, int& lpsSecond);
    int GetCpuType(QString& szCpuName, int& lplCpuCode);
    int GetDevice(QString szDevice, int& lplData);
    int GetDevice2(QString szDevice, int& lpsData);
    int Open();
    int ReadBuffer(int LStartIO, int IAddress, int LSize, int &lpsData);
    int ReadDeviceBlock(QString szDevice, int lSize, int& lplData);
 //   int ReadDeviceBlock2(QString szDevice, int lSize, int& lpsData);
    int ReadDeviceRandom(QString szDeviceList, int lSize, int& lplData);
    int ReadDeviceRandom2(QString szDeviceList, int lSize, int& lpsData);
    void SetActLogicalStationNumber(int ActLogicalStationNumber);
    void SetActPassword(QString ActPassword);
    int SetClockData(int sYear, int sMonth, int sDay, int sDayOfWeek, int sHour, int sMinute, int sSecond);
    int SetCpuStatus(int lOperation);
    int SetDevice(QString szDevice, int IData);
    int SetDevice2(QString szDevice, int sData);
    int WriteBuffer(int lStartIO, int lAddress, int lSize, int& lpsData);
    int WriteDeviceBlock(QString szDevice, int lSize, int& lplData);
    int WriteDeviceBlock2(QString szDevice, int lSize, int& lpsData);
    int WriteDeviceRandom(QString szDeviceList, int lSize, int& lplData);
    int WriteDeviceRandom2(QString szDeviceList, int lSize, int& lpsData);


private:
    void init();
    void parseArgs(QString& arg);

    void initConnect();
    //     void readbuffer(int addr, int size, long* data);
    //     void writebuffer(int addr,int size,long* data)
private slots:
void on_pb_OpenCommunication_clicked();
void on_pb_GetDevice_clicked();
void on_pb_SetDevice_clicked();
void on_pb_CloseCommunication_clicked();
void on_pb_GetCpuType_clicked();


signals:
void getdevice(QString,int&);
void readdeviceblock2(QString, int, int&);
private:
    QAxWidget* m_act = nullptr;
    Ui::MITACTServerClass ui;
};
