#pragma once

#include <QtWidgets/QWidget>
#include "ui_PlcDeviceManageUI.h"
#include "PlcDeviceManage.h"
class PlcDeviceManageUI : public QWidget
{
    Q_OBJECT

public:
    PlcDeviceManageUI(QWidget *parent = Q_NULLPTR);
    void Open();
    void Close();
    ~PlcDeviceManageUI();
private:
    void sendmsg(QString content);
    void init();
    void uninit();
    void initTableWidgets();


    private slots:
    void on_pushButton_clicked();
    void on_pb_Init_clicked();
    void on_pb_Uninit_clicked();
    void on_pb_GetDevice_clicked();
    void on_pb_SetDevice_clicked();
    void on_pb_add_clicked();
    void on_pb_delete_clicked();


    void on_pb_setwidth_clicked();
    void on_pb_clearsegment_clicked();
    void on_pb_Getsegment_clicked();
    void on_pb_open_clicked();
    void on_pb_close_clicked();

private:
    Ui::PlcDeviceManageUIClass ui;
    PlcDeviceManager* plcmanager=nullptr;
    IPlcDevice *m_plcdevice = nullptr;
    std::vector<std::string> m_labels;
};
