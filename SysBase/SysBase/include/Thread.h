#pragma once

#include "SysBase.h"
#include "Process.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //IThreadProcHandler CThread���߳�ִ��ϸ��

    class IThreadProcHandler
    {
    public:

        IThreadProcHandler(){};

        virtual ~IThreadProcHandler(){};

        virtual void Proc() = 0;

    protected:
    private:
    };

	//////////////////////////////////////////////////////////////////////////
	//CThread �߳���

    class CThread : public SysBase::CObject
	{
	public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM, 
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_INIT,
        };

        //////////////////////////////////////////////////////////////////////////

		CThread();

		virtual ~CThread();

		//����:�����߳�
		//����:
		//      IThreadProcHandler* pIThreadProcHandler IN �߳�ִ���߼�
		//      bool bRun IN Ϊ ture ���߳��߼�����ִ�У�Ϊ false ʱ����Ҫ���� Resume ��ִ��
		//�쳣
		ERROR_CODE Start(
			IThreadProcHandler* pIThreadProcHandler,
			bool bRun = true);//CREATE_SUSPENDED

		//����:�ر��߳�
		void Close();

		//����:�����߳�
		//����ֵ: �����ɹ����
		bool Resume();

		//����:��ֹ�߳�
		//����:
		//		UINT32 nWaitTime IN �ȴ��߳�ʱ��
		//      UINT32 nExitCode IN �߳��˳�����
		//����ֵ: ��ֹ�ɹ����
		bool Terminate(UINT32 nWaitTime, UINT32 nExitCode);

		//����:�����߳�
		//����ֵ: ����ɹ����
		bool Suspend();

		//����:��ȡ�߳�ID
		//����ֵ: �߳�ID
		UINT32 GetThreadID();

		//����:��ȡ�߳��˳�����
		//����:
		//      UINT32* pnExitCode OUT �߳��˳�������
		//����ֵ: ��ֹ�ɹ����
		bool GetExitCode(UINT32* pnExitCode);

		//////////////////////////////////////////////////////////////////////////
		//��̬����

		//����:��ͣ�߳�ָ����ʱ�䣨�̺߳���ʹ�ã�
		//����:
		//      UINT32 nWaitTime IN ʱ�䣬��λΪ���� 
		//����ֵ: ��ֹ�ɹ����
		static void SleepThread(UINT32 nWaitTime);

		//����:�˳���ǰ�̣߳��̺߳���ʹ�ã�
		//����:
		//      UINT32 nExitCode IN �߳��˳�����
		static void ExitCurrentThread(UINT32 nExitCode);

		//����:��ȡ��ǰ�߳�ID���̺߳���ʹ�ã�
		//����ֵ: �߳�ID
		static UINT32 GetCurrentThreadID();

	private:

		void* m_pImp;
	};

	//////////////////////////////////////////////////////////////////////////
	//CCustomThread �Զ����߳��࣬����ֻ��ͨ���̳���ʹ�ã�����ʵ��Proc�ӿ�

    class CCustomThread : public IThreadProcHandler, public SysBase::CObject
	{
	public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM, 
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_INIT,
        };

        //////////////////////////////////////////////////////////////////////////

		CCustomThread();

		virtual ~CCustomThread();

		//����:�����߳�
		ERROR_CODE Start();

		//����:ֹͣ�߳�
		//����:
		//      UINT32 nWaitTime IN �ȴ���ʱ�����ֹ�߳�
		//      UINT32 nExitCode IN �߳��˳�����
		void Stop(UINT32 nWaitTime = SYSBASE_STOP_WAIT_TIME, UINT32 nExitCode = 0);

		//����:��ȡ�߳�ID
		//����ֵ: �߳�ID
		UINT32 GetThreadID();

	protected:

		//����:�̴߳������
		//����ֵ: �̷߳���ֵ
		virtual void Proc() = 0;

	private:

		void* m_pImp;
	};

    //////////////////////////////////////////////////////////////////////////
    //CTimeThread �ṩָ��ʱ�䴥���ص��¼��Ķ����̹߳���

    class CTimeThread : private CCustomThread
    {
    public:
        
        //////////////////////////////////////////////////////////////////////////

        CTimeThread();

        virtual ~CTimeThread();

        //����:�����߳�
        //����:
        //      UINT32 nWaitTime IN ��ʱ�ĵȴ�ʱ��
        //      bool bRunFirst IN �߳��������ߵ���һ��OnTime�ٽ��붨ʱ�ȴ�
        bool Start(UINT32 nWaitTime = 1000, bool bRunFirst = false);

        //����:ֹͣ�߳�
        //����:
        //      UINT32 nWaitTime IN �ȴ���ʱ�����ֹ�߳�
        //      UINT32 nExitCode IN �߳��˳�����
        void Stop(UINT32 nWaitTime = SYSBASE_STOP_WAIT_TIME, UINT32 nExitCode = 0);

        void SetWaitTime(UINT32 nWaitTime);

        //����:��ȡ�߳�ID
        //����ֵ: �߳�ID
        UINT32 GetThreadID();

    protected:

        //ָ��ʱ�䵽�����ø��¼�
        virtual void ProcOnTime() = 0;

    private:

        virtual void Proc();

        UINT32 m_nWaitTime;
        bool m_bRunFirst;

        bool m_bStop;
        CAutoEvent m_event;
    };

	//////////////////////////////////////////////////////////////////////////
	//CCustomMultiThread �Զ�����߳��࣬����ֻ��ͨ���̳���ʹ�ã�����ʵ��Proc�ӿ�

	class CCustomMultiThread : public IThreadProcHandler, public SysBase::CObject
	{
	public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM, 
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_INIT,
        };

        //////////////////////////////////////////////////////////////////////////

		CCustomMultiThread();

		virtual ~CCustomMultiThread();

		//����:���������̳߳�
		//����:
		//      unsigned short sThreadCount IN �̸߳���
		//�쳣
		virtual ERROR_CODE Start(unsigned short sThreadCount);

		//����:�ȴ����ٺ�������ֹͣ���ҹر������߳�
		//����:
		//      UINT32 nWaitTime IN ���ٺ���,���Ϊ 0 ʱ���Ͻ��������߳�
		virtual void Stop(UINT32 nWaitTime = SYSBASE_STOP_WAIT_TIME);

		//����:��ȡ�̱߳�ż���
		//����:
		//      unsigned short* psThreadCount OUT �̱߳�Ÿ���
		//����ֵ:
		//		��������ַ[���û���򷵻�NULL]
		//�쳣
		UINT32* GetThreadIDs(unsigned short* psThreadCount);

	protected:

		//����:�̴߳������
		//����ֵ: �̷߳���ֵ
		virtual void Proc() = 0;

	private:

		void* m_pImp;
	};

    //////////////////////////////////////////////////////////////////////////
    //TTaskThrreadInfo

    struct TTaskInfo
    {
        UINT32 nThreadID;
    };

	//////////////////////////////////////////////////////////////////////////
	//ITaskHandler �������߶���

	class ITaskHandler
	{
	public:

		ITaskHandler();

		virtual ~ITaskHandler();

        //�¼����̴߳���
		virtual void Proc(void* pParam) = 0;

        //�¼������յ��̹߳ر���Ϣ֪ͨ����ʱ�̻߳�δ�رգ�
		virtual void Stop(const TTaskInfo* pTTaskInfo) = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	//ITaskHandlerFactory ���񹤳�

	class ITaskHandlerFactory
	{
	public:

		ITaskHandlerFactory();

		virtual ~ITaskHandlerFactory();

		virtual ITaskHandler* Create() = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	//CTaskMultiThread ���߳�ִ������

	class CTaskMultiThread : public SysBase::CObject
	{
	public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM, 
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_INIT,
        };

        //////////////////////////////////////////////////////////////////////////

		//����:��ʼ��
		CTaskMultiThread();

		virtual ~CTaskMultiThread();

		//����:���������̳߳�
		//����:
		//	    ITaskHandlerFactory *pITaskHandlerFactory IN ���񹤳�����
		//      unsigned short sThreadCount IN �̸߳���
		//      const void* lpParam IN �̺߳����Ĳ���
		//�쳣
		ERROR_CODE Start(ITaskHandlerFactory *pITaskHandlerFactory, unsigned short sThreadCount, void* lpParam = NULL);

		//����:�ȴ����ٺ�������ֹͣ���ҹر������߳�
		//����:
		//      UINT32 nWaitTime IN ���ٺ���,���Ϊ 0 ʱ���Ͻ��������߳�
		void Stop(UINT32 nWaitTime = SYSBASE_STOP_WAIT_TIME);

		//����:��ȡ�߳�ID����
		//����:
		//      vector<UINT32> *pThreadIDArray OUT �߳�ID����
		void GetThreadIDArray(vector<UINT32>* pThreadIDArray);

	private:

		void* m_pImp;
	};
}