#pragma once

#include "SysBase.h"

namespace SysBase
{
    class CProcessHelper : public SysBase::CObject
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum PROCESS_INFO_TYPE
        {
            PROCESS_INFO_TYPE_NORMAL = 0,           //������Ϣ�����У�
            PROCESS_INFO_TYPE_MEMORY = 1,           //�ڴ���Ϣ
            PROCESS_INFO_TYPE_IO = 2,               //IO����
            PROCESS_INFO_TYPE_RESOURCE = 4,         //��Դ
            PROCESS_INFO_TYPE_ADVANCED = 8,         //�߼���Ϣ
            PROCESS_INFO_TYPE_TIME = 16,            //ʱ����Ϣ
        };
	
        //////////////////////////////////////////////////////////////////////////

        static bool GetAllProcessInfo(
            list<TProcessInfo>& processInfoList,
            UINT32 nProcessInfoTypes = PROCESS_INFO_TYPE_NORMAL);

        static bool GetProcessInfo(
            UINT32 nProcessID, 
            TProcessInfo& processInfo, 
            UINT32 nProcessInfoTypes = PROCESS_INFO_TYPE_NORMAL);

        static bool GetProcessIDListByName(const char* szProcessName, list<UINT32>& processIDList);

        static bool GetProcessIDListByNameW(const WCHAR* szProcessName, list<UINT32>& processIDList);

        //��ȡϵͳ������������2��ϵͳĬ�Ͻ��̣�ϵͳ���� �� ϵͳidle���̣�
        static UINT32 GetProcessCount();

        static bool EnableDebugPrivilege(bool bEnable);

        //////////////////////////////////////////////////////////////////////////

    private:

        CProcessHelper();

        virtual ~CProcessHelper();

        static CProcessHelper s_CProcessHelper;
    };
}
