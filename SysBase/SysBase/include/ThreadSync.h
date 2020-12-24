#pragma once

#include "SysBase.h"

using namespace std;

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //�̻߳���

    class CThreadMutex : public SysBase::CObject
    {
    public:

        CThreadMutex();

        virtual ~CThreadMutex();

        //����:����
        virtual void Lock();

        //����:����
        virtual void Unlock();

    private:

        void* m_pImp;
    };

    //////////////////////////////////////////////////////////////////////////
    //CSmartMutex ���ܻ���

    class CSmartMutex
    {
    public:

        CSmartMutex(CThreadMutex &aCThreadMutex);

        ~CSmartMutex();

    private:

        CThreadMutex* m_pCThreadMutex;

    };

    //���ٴ���һ�����ܻ������
#define CREATE_SMART_MUTEX(aCThreadMutex) CSmartMutex CREATE_UNIQUE_VAR_NAME(_aSmartMutex)(aCThreadMutex);

#define CREATE_SMART_MUTEX_PTR(pCThreadMutex) CSmartMutex CREATE_UNIQUE_VAR_NAME(_aSmartMutex)(*pCThreadMutex);

    //////////////////////////////////////////////////////////////////////////
    //ͬ���������

    class CSyncObject
    {
    public:

        CSyncObject();

        virtual ~CSyncObject();

        virtual	bool Wait(UINT32 nWaitTime) = 0;

        virtual void* GetHandle() = 0;

        static bool WaitSyncObjects(
            CSyncObject** pCSyncObjectArray, 
            UINT32 nCount, 
            bool bWaitAll, 
            UINT32 nMilliseconds,
            UINT32& nObjectIndex);
    
    };

    //////////////////////////////////////////////////////////////////////////
    //���̻���

    class CProcessMutex : public CSyncObject
    {
    public:

        CProcessMutex();

        virtual ~CProcessMutex();

        //����:���캯��
        //����:
        //      const char* pName IN ����
        bool Open(const char* pName = NULL);

        void Release();

        virtual void* GetHandle();

        virtual	bool Wait(UINT32 nWaitTime);

    private:

        void* m_pImp;
    };

    //////////////////////////////////////////////////////////////////////////
    //CEvent �¼�

    class CEvent : public CSyncObject
    {
    public:

        //����:���캯��
        //����:
        //      bool bManualReset IN true ʱ��Ҫ Reset() ��������״̬��false ʱ���߳��ͷź��Զ���Ϊ��ʼ״̬
        //      bool bInitialState IN true ʱΪ�����ͳ�ʼ��Ϊ�ȴ�״̬��false ʱΪ��ʼ״̬
        //      const char* lpName IN ����
        CEvent(  
            bool bManualReset = true,
            bool bInitialState = false,
            const char* lpName = NULL);

        virtual ~CEvent();

        //����:�����¼��ź�Ϊ��ʼ״̬
        void Reset();

        //����:�����¼��ͺ�Ϊ�ȴ�״̬
        void Set();

        virtual	bool Wait(UINT32 nWaitTime);

        virtual void* GetHandle();

    private:

        void* m_pImp;
    };

    class CAutoEvent : public CEvent
    {
    public:

        CAutoEvent(
            bool bInitialState = false,
            const char* lpName = NULL);

        virtual ~CAutoEvent();

    };

    //////////////////////////////////////////////////////////////////////////
    //CSemaphore �ź���

    class CSemaphore : public CSyncObject
    {
    public:

        //����:���캯��
        //����:
        //      int nInitialCount IN ��ʼ������
        //      int nlMaximumCount IN ���ֵ�����������
        //       const char* pName IN ����
        CSemaphore(
            int nInitialCount = 0,
            int nlMaximumCount = 2147483647, 
            const char* pName = NULL);

        //����:��������
        virtual ~CSemaphore();

        //����:�����ź�������
        //����:
        //      int nAddCount IN ���ӵļ�����
        void Add(int nAddCount = 1);

        virtual	bool Wait(UINT32 nWaitTime);

        virtual void* GetHandle();

    private:

        void* m_pImp;
    };
}
