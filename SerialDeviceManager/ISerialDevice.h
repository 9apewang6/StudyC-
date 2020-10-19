#ifndef _ISERIALDEVICE_H_
#define _ISERIALDEVICE_H_

#include "SerialCommCfg.h"
class  ISerialDevice
{
public:
    explicit ISerialDevice() {};
    virtual ~ISerialDevice() {};
    virtual void setCfg(SerialCommInfo info)=0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual float readValue() = 0;

};



#endif //_ISERIALDEVICE_H_