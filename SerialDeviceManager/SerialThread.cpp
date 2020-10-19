#include "SerialThread.h"
#include<iostream>

static const int MAX_SIEZ_BUFFER_SIZE = 2048;

CSerialportThread::CSerialportThread():m_bInit(false)
   
{
}

CSerialportThread::~CSerialportThread()
{
}

CSerialportThread * CSerialportThread::getInstance()
{
    static CSerialportThread instance_;
    return &instance_;
}

//
void CSerialportThread::setCommConfig(const SerialCommInfo& info)
{
    m_cfg = info;

}

//


//
void CSerialportThread::runTask()
{
    if (!m_bInit)
    {
        initComm();
    }
    //
    while (1)
    {
        if (WaitForSingleObject(m_hEndEvent, 50) == WAIT_OBJECT_0)
            break;
        std::vector<char> readbuffer;
        readbuffer.resize(MAX_SIEZ_BUFFER_SIZE);
        DWORD dwRead;
        int nRet = m_serialport.ReadData(&readbuffer[0], 10);
        if (nRet == -1 || nRet == 0)
            continue;
        else
        {
            std::string tmp(readbuffer.begin(), readbuffer.begin() + dwRead);
            m_serialdata(tmp,m_context);
        }
        if (WaitForSingleObject(m_hEndEvent, 50) == WAIT_OBJECT_0)
            break;
    }
    SetEvent(m_hExitEvent);
}

void CSerialportThread::initComm()
{
    m_bInit = m_serialport.Open(m_cfg);
}

//
int CSerialportThread::writeFile(const char * writeBuffer, int size)
{
//     DWORD ret = 0;
//     vector<char> buffer;
//     int nSize = strlen(writeBuffer) < size ? strlen(writeBuffer) : size;
//     buffer.resize(nSize);
//     buffer.assign(writeBuffer, writeBuffer + nSize);
    return m_serialport.SendData(writeBuffer,size);

}

//

