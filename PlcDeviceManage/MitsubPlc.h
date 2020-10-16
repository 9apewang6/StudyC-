#ifndef _MITSUBPLC_H_
#define _MITSUBPLC_H_
#include <windows.h>
#include <QtWidgets/QtWidgets>

#include "IPlcDevice.h"
class MitSubPlc :public QWidget,public IPlcDevice {
    Q_OBJECT
public:
    MitSubPlc(QWidget* parent = nullptr);
    ~MitSubPlc();
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
public:
    void setParam(std::string key, int value);
    void setParam(std::string key, float value);
    void setParam(std::string key, std::string value);
    void setCfg(PlcCmnInfo cfg);
    int open();
    void close();
    void setWatchRegist(std::map<RegisterType, int> watched);
    int readInt(RegisterType Typeid, int registid, int& value);
    int readFloat(RegisterType Typeid, int registid, float& value);
    int readString(RegisterType Typeid, int registid, int len, std::string& value);
    int readInts(RegisterType Typeid, int startaddr, int len, std::vector<int>& value);
    int readFloats(RegisterType Typeid, int startaddr, int len, std::vector<float>& value);
    int writeInt(RegisterType Typeid,int registid,int value);
    int writeFloat(RegisterType Typeid, int registid, float value);
    int writeString(RegisterType Typeid, int registid, int len, std::string value);
    int writeInts(RegisterType Typeid, int startaddr, int count, std::vector<int> value);
    int writeFloats(RegisterType Typeid, int startaddr, int count, std::vector<float> value);

private:
    void init();
    void sendmsg(QString content);
    void setMPart(int addr, int val);
    void setDPart(int addr, int val);

    void getMPart(int addr, int& val);
    void getDPart(int addr, int& val);
    int parseStr(QString str);
private:
    HWND server;
    QString m_msg;
    int m_res;
    PlcCmnInfo mit_cfg;
};


#endif //_MITSUBPLC_H_