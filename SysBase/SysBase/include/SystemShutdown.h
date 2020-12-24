#pragma once

#include "SysBase.h"

namespace SysBase
{
    class CSystemShutdown
    {
    public:

        //�˳�����
        enum EExitFlag
        {
            EXIT_FLAG_LOGOFF = 1,       //�û��ǳ���ע����
            EXIT_FLAG_POWER_OFF = 2,    //ϵͳ�رղ��رյ�Դ
            EXIT_FLAG_REBOOT = 4,       //ϵͳ�رղ���������
            EXIT_FLAG_SHUTDOWN = 8,     //ϵͳ�رգ������رյ�Դ���������ߣ�
        };
    
        //�˳�ϵͳ
        //������
        //      UINT32 nFlags IN �˳���־����ֵΪ EExitFlag �е�����һ������������� | �����ϲ�
        static bool ExitSystem(UINT32 nFlags);

        //�ر�ϵͳ
        //����:
        //      PCWCHAR szMsg IN
        //      UINT32 nTimeout IN
        //      bool bForceAppsClosed IN
        //      bool bRebootAfterShutdown IN 
        static bool ShutdownSystem(PCWCHAR szMsg, UINT32 nTimeout, bool bForceAppsClosed, bool bRebootAfterShutdown);

        //ȡ���رգ���û�е���ǿ�ƹرղ��رյ�Դ����ʾ�ر���ʾȷ�ϵ����������
        static bool CancelShutdown();

        //����
        static bool LockSystem();
    };
}