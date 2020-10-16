#ifndef _IPLCDEVICE_H_
#define _IPLCDEVICE_H_
#include "PlcCommonCfg.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class IPlcDevice
{
public:

    explicit IPlcDevice() {};
    virtual  ~IPlcDevice() {};
    virtual void setParam(std::string key, int value)=0;
    virtual void setParam(std::string key, float value) = 0;
    virtual void setParam(std::string key, std::string value) = 0;
    virtual void setCfg(PlcCmnInfo cfg)=0;
    virtual int open() = 0;
    virtual void close() = 0;
    virtual void setWatchRegist(std::map<RegisterType, int> watched)=0;
    virtual void registCallback(registChangeCallback cb, void* context)
    {
        m_cb = cb;
        m_context = context;
    };
    virtual int readInt(RegisterType Typeid, int registid, int& value) = 0;
    virtual int readFloat(RegisterType Typeid, int registid, float& value) = 0;
    virtual int readString(RegisterType Typeid, int registid,int len, std::string& value) = 0;
    virtual int readInts(RegisterType Typeid, int startaddr, int len, std::vector<int>& value) = 0;
    virtual int readFloats(RegisterType Typeid, int startaddr, int len, std::vector<float>& value) = 0;
    virtual int writeInt(RegisterType Typeid, int registid, int value) = 0;
    virtual int writeFloat(RegisterType Typeid, int registid, float value) = 0;
    virtual int writeString(RegisterType Typeid, int registid, int len, std::string value)=0;
    virtual int writeInts(RegisterType Typeid, int startaddr, int count, std::vector<int> value) = 0;
    virtual int writeFloats(RegisterType Typeid, int startaddr, int count, std::vector<float> value) = 0;

private:
    registChangeCallback m_cb;
    void* m_context;
};



#endif //_IPLCDEVICE_H_