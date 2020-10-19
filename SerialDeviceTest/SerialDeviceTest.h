#pragma once

#include <QtWidgets/QWidget>
#include "ui_SerialDeviceTest.h"
#include "SerialDeviceManager.h"
class SerialDeviceTest : public QWidget
{
    Q_OBJECT

public:
    SerialDeviceTest(QWidget *parent = Q_NULLPTR);
    ~SerialDeviceTest();
private:
    void connect();
    void disconnect();
    void init();
    

public slots:
void on_pbConnect_clicked();
void on_pbDisconnect_clicked();
void on_pbGetValue_clicked();
private:
    Ui::SerialDeviceTestClass ui;
    SerialDeviceManager* m_manager;
    ISerialDevice* m_device=nullptr;
};
