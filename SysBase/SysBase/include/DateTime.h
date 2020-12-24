#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //CDateTime

    class CDateTime
    {
    public:

        //Ĭ��Ϊ��ǰʱ��(Now)
        CDateTime();

        CDateTime(UINT16 nYear, UINT16 nMonth, UINT16 nDay);

        CDateTime(UINT16 nYear, UINT16 nMonth, UINT16 nDay, UINT16 nHour, UINT16 nMinute, UINT16 nSecond);

        CDateTime(UINT16 nYear, UINT16 nMonth, UINT16 nDay, UINT16 nHour, UINT16 nMinute, UINT16 nSecond, UINT16 nMillisecond);

        CDateTime(INT64 nTime, UINT16 nMillisecond);

        CDateTime(SYSTEMTIME systemTime);

        virtual ~CDateTime();

        UINT16 GetYear();
        UINT16 GetMonth();
        UINT16 GetDay();
        UINT16 GetDayOfWeek();
        UINT16 GetDayOfYear();
        UINT16 GetHour();
        UINT16 GetMinute();
        UINT16 GetSecond();
        UINT16 GetMillisecond();

        INT64 GetTime();

    protected:

        void Init(UINT16 nYear = 0, 
            UINT16 nMonth = 0, 
            UINT16 nDay = 0,
            UINT16 nHour = 0, 
            UINT16 nMinute = 0,
            UINT16 nSecond = 0, 
            UINT16 nMillisecond = 0);

    private:

        UINT16 m_nYear;             //�� since 1900
        UINT16 m_nMonth;            //�� [1,12]
        UINT16 m_nDay;              //���� [1,31]
        UINT16 m_nDayOfWeek;        //һ���еĵڼ��� since Sunday - [0,6]
        UINT16 m_nDayOfYear;        //һ���еĵڼ��� since January 1 - [0,365]
        UINT16 m_nHour;             //Сʱ [0,23]
        UINT16 m_nMinute;           //���� [0,59]
        UINT16 m_nSecond;           //�� [0,59]
        UINT16 m_nMillisecond;      //����

        INT64 m_nTime;             //����1970��1��1��0ʱ0��0�� �������� ( UTC ʱ�� ) 
    };
}
