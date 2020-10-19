#pragma once
#pragma once
#include"BaseThread.h"
#include"SerialWin.h"
#include<vector>
#include<list>
#include<mutex>
using std::vector;
using std::list;



class CSerialportThread :
    public CBaseThread
{
public:

    CSerialportThread(void);
    virtual ~CSerialportThread(void);
    void setCommConfig(const SerialCommInfo& info);
    static CSerialportThread * getInstance();
    int  writeFile(const char * writeBuffer, int size);
    void registCallBck(SerialData_CallBack cb, void* context)
    {
        m_serialdata = cb;
        m_context = context;
    }
protected:
    virtual void runTask();
    void initComm();

protected:
    CSerial m_serialport;
    //
    SerialCommInfo m_cfg;
    SerialData_CallBack m_serialdata;
    void* m_context;
    bool m_bInit;
};
