#pragma once

#include "SysBase.h"
#include "SystemPerformanceInfo.h"
#include "SingleMgr.h"
#include "ThreadSync.h"
#include "Thread.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //CProcUsageCollecter

    class CSystemPerformanceCollecter : public CSingletonT<CSystemPerformanceCollecter>, private SysBase::CObject
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM, 
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_START,
            ERROR_CODE_NO_START,
            ERROR_CODE_NO_ASSIGN,       //������ģʽ��Ϊ�ռ�ָ������
        };

        enum COLLECT_TYPE
        {
            COLLECT_TYPE_PROC_BASE = 0,           //������Ϣ[����]�����̣�Normal, Time, CpuUsage; ϵͳ: CpuUsage, CpuIdle��
            COLLECT_TYPE_PROC_MEMORY = 1,         //�����ڴ���Ϣ
            COLLECT_TYPE_PROC_IO = 2,             //����IO����
            COLLECT_TYPE_PROC_RESOURCE = 4,       //������Դ
            COLLECT_TYPE_PROC_ADVANCED = 8,       //���̸߼���Ϣ
            COLLECT_TYPE_SYS_RESOURCE = 16,       //ϵͳ��Դ(�ڴ棬�������)
        };

        enum COLLECT_MODE
        {
            COLLECT_MODE_ALL = 0,       //�ռ����н�����Ϣ
            COLLECT_MODE_ASSIGN,        //�ռ�ָ��������Ϣ
        };

        //////////////////////////////////////////////////////////////////////////

        friend class CSingletonT<CSystemPerformanceCollecter>;

        virtual ~CSystemPerformanceCollecter();

        //////////////////////////////////////////////////////////////////////////

        ERROR_CODE Start(
            UINT32 collectTypes = COLLECT_TYPE_PROC_BASE, 
            COLLECT_MODE collectMode = COLLECT_MODE_ALL,
            UINT32 nIntervalTime = 1000,
            bool bSuspend = false);

        void Stop();

        ERROR_CODE Suspend();

        ERROR_CODE Resume();

        ERROR_CODE SetIntervalTime(UINT32 nIntervalTime);

        ERROR_CODE SetCollectTypes(UINT32 collectTypes);

        ERROR_CODE AddProcess(const wchar_t* szProcessName);

        ERROR_CODE RemoveProcess(const wchar_t* szProcessName);

        ERROR_CODE Get(ProcessPerformanceMap* pProcessPerformanceMap, 
            TSystemPerformance* pTSystemPerformance);

    private:

        CSystemPerformanceCollecter();

        void* m_pImp;
    };

}
