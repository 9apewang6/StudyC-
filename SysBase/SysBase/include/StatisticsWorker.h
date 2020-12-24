#pragma once

#include "Thread.h"
#include "ThreadSync.h"

namespace SysBase
{
    struct TStatisticsData
    {
        TStatisticsData()
        {
            pnValue = NULL;
            nCount = 0;
        }

        INT64* pnValue;

        UINT8 nCount;
    };

    class IStatisticsWorkerHandler
    {
    public:

        IStatisticsWorkerHandler();

        virtual ~IStatisticsWorkerHandler();

        virtual void OnTime(INT64* nDataArray, UINT8 nDataCount, UINT8 nTypeIndex) = 0;
    };

    struct TStatisticsParam
    {
        TStatisticsParam()
        {
            nTypeCount = 0;
            
            ZeroMemory(nStatisticsCountArray, sizeof(UINT8) * 255);
            
            nOnTimeSecond = 60; //Ĭ��Ϊ60��
            
            pHandler = NULL;
        }

        //ͳ����Ϣ�����͸���
        UINT8 nTypeCount;

        //ÿһ��ͳ����Ϣ���Ͷ�Ӧ��ͳ�����ݸ���
        UINT8 nStatisticsCountArray[255];

        //��ʱ���ûص���ʱ�䣨��λ���룩(��СֵΪ 5)
        UINT16 nOnTimeSecond;

        //��ʱ�ص��Ĵ����߼�
        IStatisticsWorkerHandler* pHandler;
    };

    class CStatisticsWorker : protected CCustomThread
    {
    public:

        CStatisticsWorker();

        virtual ~CStatisticsWorker();

        bool Start(TStatisticsParam& aParam);

        void Stop();

        void SetOnTimeSecond(UINT16 nSecond);

        void Increment(UINT8 nTypeIndex, UINT8 nStatisticsIndex);

        void Decrement(UINT8 nTypeIndex, UINT8 nStatisticsIndex);

        void Exchange(UINT8 nTypeIndex, UINT8 nStatisticsIndex, INT64 nValue);

        void ExchangeAdd(UINT8 nTypeIndex, UINT8 nStatisticsIndex, INT64 nValue);

        void SetMax(UINT8 nTypeIndex, UINT8 nStatisticsIndex, INT64 nValue);

        void SetMin(UINT8 nTypeIndex, UINT8 nStatisticsIndex, INT64 nValue);

    protected:

        virtual void Proc();

        bool IsStatisticsValid(UINT8 nTypeIndex, UINT8 nStatisticsIndex);

    private:

        bool m_bStop;

        CEvent m_event;

        TStatisticsParam m_param;

        TStatisticsData* m_pData;

        INT64* m_nTempData;

        UINT32 m_nWaitTime;
    };
}
