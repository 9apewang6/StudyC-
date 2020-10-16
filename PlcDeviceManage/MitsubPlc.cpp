#include "MitsubPlc.h"
MitSubPlc::MitSubPlc(QWidget* parent) :QWidget(parent),IPlcDevice(),m_res(0)
{
    init();
}

MitSubPlc::~MitSubPlc()
{

}

bool MitSubPlc::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    switch (msg->message)
    {
    case WM_COPYDATA:
        COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
        QString text = QString("%1").arg((char*)cds->lpData);
        //         QStringList l = text.split(";");
        //         m_segment = l.at(l.size() - 1).toInt();
       m_res = parseStr(text);
        return true;
    }
    //其他交给qt处理
    return QWidget::nativeEvent(eventType, message, result);
}

void MitSubPlc::setParam(std::string key, int value)
{

}

void MitSubPlc::setParam(std::string key, float value)
{

}

void MitSubPlc::setParam(std::string key, std::string value)
{

}

void MitSubPlc::setCfg(PlcCmnInfo cfg)
{
    mit_cfg = cfg;
}

int MitSubPlc::open()
{
    m_msg = QString("SetActLogicalStationNumber;%1").arg(QString::number(1));
    sendmsg(m_msg);

    m_msg = "Open";
    sendmsg(m_msg);
    return m_res;
}

void MitSubPlc::close()
{
    m_msg = "Close";
    sendmsg(m_msg);
   
}

void MitSubPlc::setWatchRegist(std::map<RegisterType, int> watched)
{

}

int MitSubPlc::readInt(RegisterType Typeid, int registid, int& value)
{
    if (Typeid == RegisterType::MPART)
    {
        getMPart(registid, value);
    }
    else if (Typeid == RegisterType::DPART)
    {
        getDPart(registid, value);
    }
    return 0;
}

int MitSubPlc::readFloat(RegisterType Typeid, int registid, float& value)
{
    return -1;
}

int MitSubPlc::readString(RegisterType Typeid, int registid, int len, std::string& value)
{
    return -1;
}

int MitSubPlc::readInts(RegisterType Typeid, int startaddr, int len, std::vector<int>& value)
{
    return -1;
}

int MitSubPlc::readFloats(RegisterType Typeid, int startaddr, int len, std::vector<float>& value)
{
    return -1;
}

int MitSubPlc::writeInt(RegisterType Typeid, int registid, int value)
{
    if (Typeid == RegisterType::MPART)
    {
        setMPart(registid, value);
    }
    else if (Typeid == RegisterType::DPART)
    {
        setDPart(registid, value);
    }
    return m_res;
 
}

int MitSubPlc::writeFloat(RegisterType Typeid, int registid, float value)
{
    return -1;
}

int MitSubPlc::writeString(RegisterType Typeid, int registid, int len, std::string value)
{
    return -1;

}

int MitSubPlc::writeInts(RegisterType Typeid, int startaddr, int count, std::vector<int> value)
{
    return -1;

}

int MitSubPlc::writeFloats(RegisterType Typeid, int startaddr, int count, std::vector<float> value)
{
    return -1;

}

void MitSubPlc::init()
{
    QString dest = "MITACTSERVER";
    LPCWSTR title = dest.toStdWString().c_str();
    server = ::FindWindowW(nullptr, title);
    if (!IsWindow(server))
    {
        return;
    }

}

void MitSubPlc::sendmsg(QString content)
{
    COPYDATASTRUCT cds;
    cds.dwData = winId();//自定义数据
    cds.cbData = content.length() + 1;//lpData指向数据的长度，如果内容有汉字 貌似长度有问题
    cds.lpData = content.toUtf8().data();
    HWND sender = (HWND)effectiveWinId();//SendMessage 消息发送者可以不用填写
    ::SendMessage(server, WM_COPYDATA, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&cds));
}

void MitSubPlc::setMPart(int addr, int val)
{
    m_msg = QString("SetDevice;M%1;%2").arg(QString::number(addr)).arg(QString::number(val));
    sendmsg(m_msg);
}

void MitSubPlc::setDPart(int addr, int val)
{
    m_msg = QString("SetDevice;D%1;%2").arg(QString::number(addr)).arg(QString::number(val));
    sendmsg(m_msg);
}

void MitSubPlc::getMPart(int addr, int& val)
{
    m_msg = QString("GetDevice;M%1").arg(QString::number(addr));
    sendmsg(m_msg);
    val = m_res;
}

void MitSubPlc::getDPart(int addr, int& val)
{
    m_msg = QString("GetDevice;D%1").arg(QString::number(addr));
    sendmsg(m_msg);
    val = m_res;
}

int MitSubPlc::parseStr(QString str)
{
    // 1. 
    QStringList l = str.split(";");
    if (str.contains("Open"))
    {
        if (l.size() > 1)return l[1].toInt();
    }
    else if (str.contains("Close"))
    {
        if (l.size() > 1)return l[1].toInt();
    }
    else if (str.contains("SetDevice"))
    {
        if (l.size() > 3)return l[3].toInt();
    }
    else if (str.contains("GetDevice"))
    {
        if (l.size() > 2)return l[2].toInt();
    }
    return 0;
}
