#pragma once
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ui_DebugMotion.h"
#include "debugmotion_global.h"
#include "AxisCfg.h"
#include "PlcDeviceManage.h"
#include "IPlcDevice.h"


class DEBUGMOTION_EXPORT DebugMotion : public QWidget
{
    Q_OBJECT
public:
    DebugMotion(QWidget* parent = nullptr);
    ~DebugMotion();
    void loadConfig(const std::string& path);

    void setCurrentProductId(const int index);
private:
    void initMotionHandle();


    void initView();
    void leftmove(int addr,bool tostart=true);
    void rightmove(int addr, bool tostart = true);
    void startmoving(int addr,bool tostart = true);
    void goback(int addr, bool tostart = true);

    void setSpeed(int addr, int value);
    void setPosition(int addr, int value);

    void PointOk(int addr,bool isOk = true );
    void reset();
private slots:

    void GoLeft();
    void StopLeft();
    void GoRight();
    void StopRight();

    void MoveTo();
    void BackTo();
    void SpeedChange();
    void PositionChange();

    void EnsurePoint();

private:
    void parseAddr(const std::string& intro, int& addr,RegisterType& t);
private:
    Ui::DebugMotion ui;
    QString cfgFile;
    QString motionFile;
    QString qssFile;
    std::string motionLabel;
    
    std::vector<AxisConfig> cfgs_;
    std::vector<std::string> m_points;
    std::vector<bool> m_pointSured;
    Components views_;

    QList<QHBoxLayout*> horizont_;


    QList<QPushButton*> m_pointBtn;

    QVBoxLayout* vblayout = nullptr;

    QHBoxLayout* pbtnLayout = nullptr;

    bool _isInit;


    PlcDeviceManager* plcmanager = nullptr;
    IPlcDevice *m_plcdevice = nullptr;

    std::string product_addr;
    // 
    int len_;
    int addr_;
    int val_;
    int m_CurId;

    RegisterType type_;
};

