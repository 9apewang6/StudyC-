#pragma once

#include "SysBase.h"

namespace SysBase
{
    //������������
    enum SYSBASE_SERVICE_RUN_TYPE
    {
        SYSBASE_SERVICE_RUN_TYPE_AUTO_START = 0,      //�Զ�����
        SYSBASE_SERVICE_RUN_TYPE_DEMAND_START = 1,    //�ֶ�����
        SYSBASE_SERVICE_RUN_TYPE_DISABLED = 2,        //����
        SYSBASE_SERVICE_RUN_TYPE_BOOT_START =3,       //��������
        SYSBASE_SERVICE_RUN_TYPE_SYSTEM_START = 4,    //ϵͳ����
    };

    //����ǰ����״̬
    enum SYSBASE_SERVICE_STATE
    {
        SYSBASE_SERVICE_STATE_CONTINUE_PENDING = 0,     //�����ȴ�
        SYSBASE_SERVICE_STATE_PAUSE_PENDING = 1,        //��ͣ�ȴ�
        SYSBASE_SERVICE_STATE_PAUSED = 2,               //����ͣ
        SYSBASE_SERVICE_STATE_RUNNING = 3,              //������
        SYSBASE_SERVICE_START_PENDING = 4,              //��ʼ�ȴ�
        SYSBASE_SERVICE_STATE_STOP_PENDING = 5,         //ֹͣ�ȴ�
        SYSBASE_SERVICE_STATE_STOPPED = 6,              //��ֹͣ
    };

    //��������
    enum SYSBASE_SERVICE_TYPE
    {
        SYSBASE_SERVICE_TYPE_KERNEL_DRIVER = 1,             //������������
        SYSBASE_SERVICE_TYPE_FILE_SYSTEM_DRIVER = 2,        //�ļ�ϵͳ��������
        SYSBASE_SERVICE_TYPE_WIN32_OWN_PROCESS = 10,        //WIN32һ�����
        SYSBASE_SERVICE_TYPE_WIN32_SHARE_PROCESS = 16,      //WIN32�������
        SYSBASE_SERVICE_TYPE_INTERACTIVE_PROCESS = 256,     //�������̣���ʱ��֪��ʲô��˼��
    };

    struct TServiceInfo
    {
        TServiceInfo()
        {
            runType = SYSBASE_SERVICE_RUN_TYPE_DISABLED;
            curState = SYSBASE_SERVICE_STATE_STOPPED;
            nServicesType = SYSBASE_SERVICE_TYPE_WIN32_OWN_PROCESS;
            nProcessID = 0;
        }

        string strServiceName;                  //������
        string strDisplayName;                  //������ʾ��
        string strBinaryPathName;               //�����Ӧ�Ľ�������·����������
        string strStartName;                    //����������û���
        SYSBASE_SERVICE_RUN_TYPE runType;       //������������
        SYSBASE_SERVICE_STATE curState;         //����ǰ״̬
        UINT32 nServicesType;                   //�������ͣ�SYSBASE_SERVICE_TYPE��
        UINT32 nProcessID;                      //��Ӧ�Ľ���ID
    };

    struct TServiceInfoW
    {
        TServiceInfoW()
        {
            runType = SYSBASE_SERVICE_RUN_TYPE_DISABLED;
            curState = SYSBASE_SERVICE_STATE_STOPPED;
            nServicesType = SYSBASE_SERVICE_TYPE_WIN32_OWN_PROCESS;
            nProcessID = 0;
        }

        wstring strServiceName;                 //������
        wstring strDisplayName;                 //������ʾ��
        wstring strBinaryPathName;              //�����Ӧ�Ľ�������·����������
        wstring strStartName;                   //����������û���
        SYSBASE_SERVICE_RUN_TYPE runType;       //������������
        SYSBASE_SERVICE_STATE curState;         //����ǰ״̬
        UINT32 nServicesType;                   //�������ͣ�SYSBASE_SERVICE_TYPE��
        UINT32 nProcessID;                      //��Ӧ�Ľ���ID
    };

    class CServicesHelper
    {
    public:

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS,
            ERROR_CODE_PARAM,               //��������
            ERROR_CODE_SYSTEM,              //�߼�����
            ERROR_CODE_INVALID_HANDLE,      //��Ч�ľ��
        };

        static bool GetServiceInfo(list<TServiceInfo>& serviceInfoList);
        static bool GetServiceInfo(list<TServiceInfoW>& serviceInfoList);

        static ERROR_CODE GetServiceInfo(const char* szServiceName, TServiceInfo& serviceInfo);
        static ERROR_CODE GetServiceInfo(const WCHAR* szServiceName, TServiceInfoW& serviceInfo);

        static ERROR_CODE InstallService(const char* szServiceName,const char* szDisplayName, const char* szExePath);
        static ERROR_CODE InstallService(const WCHAR* szServiceName,const WCHAR* szDisplayName, const WCHAR* szExePath);

        static ERROR_CODE UnInstallService(const char* szServiceName);
        static ERROR_CODE UnInstallService(const WCHAR* szServiceName);

        static bool IsServiceExist(const char* szServiceName);
        static bool IsServiceExist(const WCHAR* szServiceName);

        static ERROR_CODE RunService(const char* szServiceName);
        static ERROR_CODE RunService(const WCHAR* szServiceName);

        static ERROR_CODE StopService(const char* szServiceName);
        static ERROR_CODE StopService(const WCHAR* szServiceName);

        static ERROR_CODE PauseService(const char* szServiceName);
        static ERROR_CODE PauseService(const WCHAR* szServiceName);

        static ERROR_CODE ContinueService(const char* szServiceName);
        static ERROR_CODE ContinueService(const WCHAR* szServiceName);

    private:

        CServicesHelper();

        virtual ~CServicesHelper();
    };
}
