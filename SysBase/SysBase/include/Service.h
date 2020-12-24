#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //ϵͳ����ִ������

    class IServiceHandler
    {
    public:

        IServiceHandler(){};
        virtual ~IServiceHandler(){};

        //�¼�:������������������Ӧ��ҵ���߼��̣߳���Ҫ�ڸ��¼���ʹ��ѭ���ȴ���Ϣ��
        //����ֵ: TRUE ������Ϣ�ȴ� FALSE �˳�
        virtual bool OnRun(int nArgc, char** argv) = 0;

        //�¼�: ���յ�����ֹͣ��
        virtual void OnStop() = 0;

        //�¼������̴߳���(OnRun�¼���OnStop�¼�ǰ ������ʱ�䣬�� bProcThread ����Ϊ true ʱ��Ч)
        virtual void OnProc(){};

        //�¼����� OnProc ����ʱ���յ�����������ύ��ֹͣ����ʱ��Ӧ�Ĵ���
        virtual void OnProcStop(){};
    };

    //////////////////////////////////////////////////////////////////////////
    //ϵͳ������

	//////////////////////////////////////////////////////////////////////////
	//CService
	
    class CService : CObject
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM,
            ERROR_CODE_SYSTEM,			//ϵͳ�������
            ERROR_CODE_STOP,			//����δ��������ֹͣ
            ERROR_CODE_START,			//����������
        };

        //////////////////////////////////////////////////////////////////////////

        CService();

        virtual ~CService();

        //����:��������
        //����:
        //      IServiceHandler* pIServiceHandler IN ������ϸ��
        //      const char* pServiceName IN ��������
        //      const char* pDisplayName IN ������ʾ����
        //      const char* pDesc IN ��������
        //      int nArgc IN �����в�������
        //      char** argv IN �����в�����Ϣ
        //      bool bProcThread IN �Ƿ��Լ��������߳�ѭ��(true: IServiceHandler.OnProc �¼�����ִ��; false: ��CService�����й����߳�ѭ��)
        //����ֵ��ERROR_CODE_SUCCESS Ϊ�ɹ�������ο� ERROR_CODE ö��
        ERROR_CODE Start(
            IServiceHandler* pIServiceHandler, 
            const char* pServiceName = "SYSBASE SRV", 
            const char* pDisplayName = "SYSBASE SRV", 
            const char* pDesc = "SYSBASE SRV",
            int nArgc = __argc, 
            char** argv = __argv,
            bool bProcThread = false);

    private:

        void* m_pImp;
    };
}