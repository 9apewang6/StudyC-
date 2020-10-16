#include <windows.h>
#include <QTime>
#include "MITACTServer.h"



MITACTServer::MITACTServer(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    init();
    setWindowTitle(QStringLiteral("MITACTSERVER"));
}

MITACTServer::~MITACTServer()
{
    delete m_act;
    m_act = nullptr;
}

bool MITACTServer::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    switch (msg->message)
    {
    case WM_COPYDATA:
      //  qDebug() << "收到WM_COPYDATA客户端消息";
        DWORD dwPid = 0;
        GetWindowThreadProcessId((HWND)msg->wParam, &dwPid);
        COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
        QString text = QStringLiteral("PID=[%1]的进程发来的消息为：%2").arg((int)dwPid).arg((char*)cds->lpData);
        QString args = QString("%1").arg((char*)cds->lpData);
        parseArgs(args);

        ui.label->setText(text);
        //给客户端回一个时间
     
        COPYDATASTRUCT cds2;
        cds2.dwData = 0;
        cds2.cbData = args.length() + 1;
        cds2.lpData = args.toUtf8().data();

        ::SendMessage((HWND)msg->wParam, WM_COPYDATA, NULL, reinterpret_cast<LPARAM>(&cds2));
        return true;
    }
    //其他交给qt处理
    return QWidget::nativeEvent(eventType, message, result);
}

int MITACTServer::CheckDeviceString(QString szDevice, int ICheckType, int ISize, int& lpIDeviceType, QString& lpszDeviceName, int& lpIDeviceNumber, int & lpIDeviceRadix)
{
    return 0;
}

int MITACTServer::Close()
{

    QVariant var;
    var = m_act->dynamicCall("Close()");


    return var.toInt();
}

int MITACTServer::Connect()
{
    return 0;

}

int MITACTServer::Disconnect()
{
    return 0;

}

int MITACTServer::EntryDeviceStatus(QString sszDeviceList, int ISize, int IMonitorCycle, int& lpIData)
{
    return 0;

}

int MITACTServer::FreeDeviceStatus()
{
    return 0;

}

int MITACTServer::GetClockData(int& lpsYear, int& lpsMonth, int& lpsDay, int& lpsDayOfWeek, int& lpsHour, int& lpsMinute, int& lpsSecond)
{
    return 0;

}

int MITACTServer::GetCpuType(QString& szCpuName, int& lplCpuCode)
{
    QVariant var;
    QVariantList params;
    params.append(szCpuName);
    params.append(lplCpuCode);
    var = m_act->dynamicCall("GetCpuType(QString&,int&)",params);
    szCpuName = params[0].toString();
    lplCpuCode = params[1].toInt();


    return var.toInt();
}

int MITACTServer::GetDevice(QString szDevice, int& lplData)
{
    QVariant var;
    QVariantList params;
    params.append(szDevice);
    params.append(lplData);
    var = m_act->dynamicCall("GetDevice(QString,int&)", params);
    lplData = params[1].toInt();
    return var.toInt();
}

int MITACTServer::GetDevice2(QString szDevice, int& lpsData)
{
    QVariant var;
    QVariantList params;
    params.append(szDevice);
    params.append(lpsData);
    var = m_act->dynamicCall("GetDevice2(QString,int&)", params);
    lpsData = params[2].toInt();
    return var.toInt();
}

int MITACTServer::Open()
{
    QVariant var;
    var = m_act->dynamicCall("Open()");


    return var.toInt();
}

int MITACTServer::ReadBuffer(int LStartIO, int IAddress, int LSize, int &lpsData)
{
    QVariantList params;
    params.append(LStartIO);
    params.append(IAddress);
    params.append(LSize);
    params.append(lpsData);
    m_act->dynamicCall("ReadBuffer(int,int,int,int&)", params);

    return 0;

}

int MITACTServer::ReadDeviceBlock(QString szDevice, int lSize, int& lplData)
{
    QVariant var;
  
    QVariantList params;
    params.append(szDevice);
    params.append(lSize);
    params.append(lplData);
    var = m_act->dynamicCall("ReadDeviceBlock(QString,int,int&)",params);
    lplData = params[2].toInt();

    return var.toInt();
}

// int MITACTServer::ReadDeviceBlock2(QString szDevice, int lSize, int& lpsData)
// {
//     QVariant var;
//     QVariant data;
//     QVariantList params;
//     params.append(szDevice);
//     params.append(lSize);
//     params.push_back(data);
//   
//     var = m_act->dynamicCall("ReadDeviceBlock2(QString,int,int&)",params);
//    
//     lpsData = params[2].toInt();
// 
//     return var.toInt();
// }

int MITACTServer::ReadDeviceRandom(QString szDeviceList, int lSize, int& lplData)
{
    return 0;

}

int MITACTServer::ReadDeviceRandom2(QString szDeviceList, int lSize, int& lpsData)
{
    return 0;

}

void MITACTServer::SetActLogicalStationNumber(int ActLogicalStationNumber)
{
    QVariant var;
    var = m_act->dynamicCall("SetActLogicalStationNumber(int ActLogicalStationNumber)", ActLogicalStationNumber);
}

void MITACTServer::SetActPassword(QString ActPassword)
{
    QVariant var;
    var = m_act->dynamicCall("SetActPassword(QString ActPassword)", ActPassword);
}

int MITACTServer::SetClockData(int sYear, int sMonth, int sDay, int sDayOfWeek, int sHour, int sMinute, int sSecond)
{
    return 0;

}

int MITACTServer::SetCpuStatus(int lOperation)
{
    return 0;

}

int MITACTServer::SetDevice(QString szDevice, int IData)
{
    QVariant var;
    var = m_act->dynamicCall("SetDevice(QString szDevice, int lData)", szDevice, IData);


    return var.toInt();
}

int MITACTServer::SetDevice2(QString szDevice, int sData)
{
    return 0;

}

int MITACTServer::WriteBuffer(int lStartIO, int lAddress, int lSize, int& lpsData)
{
    return 0;

}

int MITACTServer::WriteDeviceBlock(QString szDevice, int lSize, int& lplData)
{
    return 0;

}

int MITACTServer::WriteDeviceBlock2(QString szDevice, int lSize, int& lpsData)
{
    QVariant var;
    var = m_act->dynamicCall("WriteDeviceBlock2(QString szDevice, int lSize, int& lpsData)", szDevice, lSize, lpsData);


    return var.toInt();
}

int MITACTServer::WriteDeviceRandom(QString szDeviceList, int lSize, int& lplData)
{
    return 0;

}

int MITACTServer::WriteDeviceRandom2(QString szDeviceList, int lSize, int& lpsData)
{
    return 0;

}

void MITACTServer::init()
{
    m_act = new QAxWidget;
    m_act->setControl(QString::fromUtf8("{63885648-1785-41A4-82D5-C578D29E4DA8}"));
    QString doc = m_act->generateDocumentation();

    initConnect();
}

void MITACTServer::parseArgs(QString& arg)
{
    QStringList slist = arg.split(";");
    QString res;
    int data;
    if (arg.contains("Open"))
    {
       res = QString::number(Open());
       slist.append(res);
    
       arg = arg + ";" + res;
       return;
    }
    if (arg.contains("SetActLogicalStationNumber")&& slist.size()>1)
    {
        SetActLogicalStationNumber(slist[1].toInt());
        return;
    }
    if (arg.contains("GetDevice")&&slist.size()>1)
    {
        GetDevice(slist[1], data);
        res = QString::number(data);
        arg = arg + ";" + QString::number(data) + ";" + res;
        return;
    }
   
    if (arg.contains("WriteDeviceBlock2")&&slist.size()>2)
    {
        WriteDeviceBlock2(slist[1], slist[2].toInt(), data);
        res = QString::number(data);
        arg = arg + ";" + res;
        return;
    }
    if (arg.contains("SetDevice")&&slist.size()>2)
    {
        SetDevice(slist[1], slist[2].toInt());
        return;
    }
    if (arg.contains("Close"))
    {
        res = QString::number(Close());
        slist.append(res);
        arg = arg + ";" + res;
        return;
    }

}

void MITACTServer::initConnect()
{
    connect(this, SIGNAL(getdevice(QString, int&)), m_act,SLOT(GetDevice(QString,int&)) );
}

void MITACTServer::on_pb_OpenCommunication_clicked()
{
    SetActLogicalStationNumber(1);
    Open();
}

void MITACTServer::on_pb_GetDevice_clicked()
{
    QString szdevice = ui.lineEdit->text();
    int data;
    //GetDevice(szdevice, data);
    emit getdevice(szdevice,data);
   // ReadDeviceBlock2(szdevice, 5, data);
    ui.spinBox->setValue(data);
}

void MITACTServer::on_pb_SetDevice_clicked()
{
    QString szdevice = ui.lineEdit_2->text();
    int  data = ui.spinBox_2->value();
    SetDevice(szdevice, data);
}

void MITACTServer::on_pb_CloseCommunication_clicked()
{
    Close();
}

void MITACTServer::on_pb_GetCpuType_clicked()
{
    QString cputype;
    int cpuvalue;
    GetCpuType(cputype,cpuvalue);
    ui.lineEdit_3->setText(cputype);
    ui.spinBox_3->setValue(cpuvalue);
}

