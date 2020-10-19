#ifndef _DIALINDICATOR_H_
#define _DIALINDICATOR_H_
#include "ISerialDevice.h"
#include "SerialQt.h"
//2B 30 30 30 30 2E 30 30 30 0D   
// 2B 30 30 30 34 2E 30 30 39 0D 
//2B 30 30 2E 32 32 31 34 30 0D 
class DialIndicator :public ISerialDevice
{
public:
    DialIndicator();
    ~DialIndicator();
    void open();
    void close();
    float readValue();
    void setCfg(SerialCommInfo info);
private:
    void sendMsg(const QString& msg);
    float parseMsg(const QString& msg);
private:
    float readTimeDia;
    SerialCommInfo diacfg;
    SerailQt m_Scmm;

};



#endif //_DIALINDICATOR_H_