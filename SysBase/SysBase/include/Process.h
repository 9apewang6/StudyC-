#pragma once

#include "SysBase.h"
#include "ProcessInfo.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//CProcess ������

	class CProcess
	{
	public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_NOT_CREATE_OR_OPEN,
            ERROR_CODE_PARAM,
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_INIT,
            ERROR_CODE_NO_EXIST,
            ERROR_CODE_TIME_OUT,
            ERROR_CODE_PROC_NOT_FIND,
        };

        enum OPEN_RIGHT_TYPE
        {
            OPEN_RIGHT_TYPE_ALL = 0,            //����Ȩ��
            OPEN_RIGHT_TYPE_QUERY_LIMITED,      //���ٽ�����Ϣ��ѯȨ��
            OPEN_RIGHT_TYPE_QUERY_ALL,          //���н�����Ϣ��ѯȨ��
        };

        //////////////////////////////////////////////////////////////////////////

		CProcess();

		virtual ~CProcess();

		//����:��������
		//����:
		//      char* lpCommandLine IN �������̵�������
		//      bool bRun IN ture ʱ��������; false ʱ�̴߳�������ֱͣ������ Resume ����ʱ������
        //      bool bShowWindow IN ture ʱ��ʾ����; false ʱ����ʾ
		ERROR_CODE Create(char* lpCommandLine, bool bRun = true, bool bShowWindow = true);

        //����:��������
        //����:
        //      char* lpCommandLine IN �������̵�������
        //      bool bRun IN ture ʱ��������; false ʱ�̴߳�������ֱͣ������ Resume ����ʱ������
        //      bool bShowWindow IN ture ʱ��ʾ����; false ʱ����ʾ
        ERROR_CODE Create(WCHAR* lpCommandLine, bool bRun = true, bool bShowWindow = true);

        //���ܣ��ָ���������
        ERROR_CODE Resume();

		//����:��һ�����еĽ���
		//����:
		//      UINT32 nProcessID IN ����ID
        //      OPEN_RIGHT_TYPE openRightType IN ����Ȩ��
		ERROR_CODE Open(UINT32 nProcessID, OPEN_RIGHT_TYPE openRightType = OPEN_RIGHT_TYPE_ALL);

		//����:���ݽ�������ȡ�Ѿ��򿪵Ľ���
		//����:
		//      const char* szProcessName IN ������
		//�쳣
		ERROR_CODE OpenByName(const char* szProcessName, OPEN_RIGHT_TYPE openRightType = OPEN_RIGHT_TYPE_ALL);

        //����:�򿪵�ǰ����(��Ҫ�ͷ�)
        ERROR_CODE OpenCurrent();

		//����:�ر��߳�
		void Close();

        //����:��ֹ����
        //����:
        //      UINT32 nExitCode IN �����˳�����
        ERROR_CODE Terminate(UINT32 nExitCode);
        
        //���ܣ��ȴ������Ƿ��˳�
        ERROR_CODE Wait(UINT32 nWaitTime);

		//����:��ȡ���̷�����
		//����:
		//      UINT32* pnExitCode IN ���̷��صĴ���
		//����ֵ: �߳�ʵ��ָ��
		ERROR_CODE GetExitCode(UINT32* pnExitCode);

        //���ܣ������ܵ��ͷŲ���ʹ�õ��ڴ�
        ERROR_CODE ReleaseMemory();

		//����:��ȡ����ID
		//����ֵ: ����ID
		ERROR_CODE GetProcessID(UINT32& nProcessID);

        ERROR_CODE GetProcessNormal(TProcessNormal& aTProcessNormal);

        ERROR_CODE GetProcessMemory(TProcessMemory& aTProcessMemory);

        ERROR_CODE GetProcessIOCounter(TProcessIOCounter& aTProcessIOCounter);

        ERROR_CODE GetProcessResource(TProcessResource& aTProcessResource);

        ERROR_CODE GetProcessAdvanced(TProcessAdvanced& aTProcessAdvanced);

        ERROR_CODE GetProcessTime(TProcessTime& aTProcessTime);
        
		//////////////////////////////////////////////////////////////////////////
		//��̬����

		//����:��ȡ��ǰ����������
		//����ֵ: ����������
		static const char* GetCurrentCommandLine();

        static UINT32 GetCurProcessID();

        static bool KillProcess(UINT32 nProcessID, UINT32 nExitCode = 0);

        //����:�����������̣��������ٹ������ӽ��̣�
        //����:
        //      char* lpCommandLine IN �������̵�������
        //      bool bShowWindow IN ture ʱ��ʾ����; false ʱ����ʾ
        static bool RunProcesss(const char* szCmdLine,UINT32& nProcessID, const char* strCurrentDir,bool bShowWindow = true);

        //����:�����������̣��������ٹ������ӽ��̣�
        //����:
        //      char* lpCommandLine IN �������̵�������
        //      bool bShowWindow IN ture ʱ��ʾ����; false ʱ����ʾ
        static bool RunProcesss(const WCHAR* szCmdLine, UINT32& nProcessID,const WCHAR* strCurrentDir,bool bShowWindow = true);

	protected:

		void* m_pImp;
	};
}