#pragma once

#include "SysBase.h"

namespace SysBase
{
    class CSystemInfo
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum SYSTEM_VER
        {
            SYSTEM_VER_NONSUPPORT = 0,      //��֧�ְ汾
            SYSTEM_VER_XP,                  //Windows XP 32λ
            SYSTEM_VER_XP_64,               //Windows XP Professional x64 Edition
            SYSTEM_VER_2003,                //Windows Server 2003
            SYSTEM_VER_HOME_SRV,            //Windows Home Server
            SYSTEM_VER_2003_R2,             //Windows Server 2003 R2
            SYSTEM_VER_VISTA,               //Windows Vista
            SYSTEM_VER_2008,                //Windows Server 2008
            SYSTEM_VER_2008_R2,             //Windows Server 2008 R2
            SYSTEM_VER_WIN7,                //Windows 7
            SYSTEM_VER_2012,                //Windows Server 2012
            SYSTEM_VER_WIN8,                //Windows 8
        };

        enum SYSTEM_VER_SUITE
        {
            SYSTEM_VER_SUITE_UNKNOWN = 0,       //δ֪�汾
            SYSTEM_VER_SUITE_WEB,               //WEB�������汾
            SYSTEM_VER_SUITE_CLUSTER,           //�������Ⱥ�汾
            SYSTEM_VER_SUITE_DATACENTER,        //�������İ汾
            SYSTEM_VER_SUITE_ENTERPRISE,        //��ҵ�汾
            SYSTEM_VER_SUITE_EMBEDDEDNT,        //Ƕ��ʽ�汾
            SYSTEM_VER_SUITE_PERSONAL,          //���˰汾
            SYSTEM_VER_SUITE_STORAGE,           //�洢����汾
            SYSTEM_VER_SUITE_HOME_SRV,          //��ͥ����汾
        };

        enum SYSTEM_NET_JOIN_TYPE
        {
            SYSTEM_NET_JOIN_TYPE_UN_JOIN = 0,
            SYSTEM_NET_JOIN_TYPE_WORK_GROUP,    //������
            SYSTEM_NET_JOIN_TYPE_DOMAIN,        //��
        };

        //////////////////////////////////////////////////////////////////////////

        static SYSTEM_VER GetSystemVersion();

        static SYSTEM_VER_SUITE GetSystemVerSuite();

        static void GetCurComputerName(string& strName);

        static void GetCurComputerName(wstring& strName);

        //���ܣ���ȡ��������Ĺ�������������
        //����:
        //      wstring& strMame OUT ����Ĺ������������ƣ�������ֵ������ SYSTEM_NET_JOIN_TYPE_UN_JOIN ʱ��
        //����ֵ�����������״̬���
        static SYSTEM_NET_JOIN_TYPE GetNetJoinName(wstring& strMame);

        static bool Is64bitSystem();

        //RemoteDesktopService
        static bool IsRDPRunOn();

    protected:
    private:
    };
}
