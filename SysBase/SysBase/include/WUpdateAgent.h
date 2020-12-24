#pragma once

#include "SysBase.h"
#include <Wuapi.h>
#pragma comment(lib, "Wuguid.lib")
#pragma comment(lib, "Advapi32.lib")

namespace SysBase
{
    //����ײ�ʵ��ΪCOM����ð�ʵ��������ĳ��������߳���һֱ�������Ժ�ÿ�ε��ü���
    //�ظ���ʼ���ͷ�COM CoInitialize �� CoUninitialize ���ܻ����Ч�ʵ�����
    class CWUpdateAgent
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_SYSTEM,          //�ڲ�����
            ERROR_CODE_INIT_FAILED,     //��ʼ��ʧ��
            ERROR_CODE_PARAM,           //��������
        };
   
        //////////////////////////////////////////////////////////////////////////

        enum SERVICE_STATUS
        {
            SERVICE_STATUS_ON = 0,  //������
            SERVICE_STATUS_OFF,     //����ر�
        };

        enum NOTIFY_TYPE
        {
            NOTIFY_TYPE_NOT_CONFIGURED = 0,     //û�������Զ��������û�������Թ���Ա����ʾ�û������������Զ����¡�
            NOTIFY_TYPE_DISABLED,               //�Զ����½������á�����֪ͨ�û��ļ��������Ҫ���¡�
            NOTIFY_TYPE_BEFORE_DOWNLOAD,        //�Զ�������ʾ�û���׼����֮ǰ���ػ�װ
            NOTIFY_TYPE_BEFORE_INSTALL,         //�Զ������Զ����ظ��£�����ʾ�û���׼���ڰ�װǰ
            NOTIFY_TYPE_SCHEDULED_INSTALL,      //�Զ����ز���װ����
        }; 

        //�� NOTIFY_TYPE Ϊ NOTIFY_TYPE_SCHEDULED_INSTALL ʱ����Ч
        enum AUTO_UPDATE_DAY
        {
            AUTO_UPDATE_NONE = 0,       //�޸�������
            AUTO_UPDATE_MONDAY = 1,     //����һ
            AUTO_UPDATE_TUESDAY = 2,    //���ڶ�
            AUTO_UPDATE_WEDNESDAY = 3,  //������
            AUTO_UPDATE_THURSDAY = 4,   //������
            AUTO_UPDATE_FRIDAY = 5,     //������
            AUTO_UPDATE_SATURDAY = 6,   //������
            AUTO_UPDATE_SUNDAY = 7,     //������
            AUTO_UPDATE_EVERY = 8,      //ÿ��
        };

        //////////////////////////////////////////////////////////////////////////

        CWUpdateAgent();

        virtual ~CWUpdateAgent();

        ERROR_CODE GetServiceStatus(SERVICE_STATUS& serviceStatus);

        //���ܣ�����WINDOWS UPDATE �Զ����£��������з���[���κ�����¶���������������Ѿ�������Ҳ���سɹ�]
        ERROR_CODE EnableService();

        ERROR_CODE DiableService();

        //���ܣ���ȡWINODWS UPDATE ����
        //������
        //      notifyType OUT ��������
        //      pAutoUpdateDay OUT �Զ��������ڣ�һ���еĵڼ��죩
        //          [notifyType == NOTIFY_TYPE_SCHEDULED_INSTALL ʱ��Ч, ��� notifyType �������ֵ���򷵻� AUTO_UPDATE_NONE������ΪNULL�򲻷����κ�����]
        //      pnAutoUpdateTime OUT �Զ�����ʱ�䣨һ���ڵĵڼ��㣬��Χ 0 ~ 23����Ӧ�賿0�㵽����23�㣩
        //          [notifyType == NOTIFY_TYPE_SCHEDULED_INSTALL ʱ��Ч, ��� notifyType �������ֵ���򷵻� -1������ΪNULL�򲻷����κ�����]
        ERROR_CODE GetNotiyType(
            NOTIFY_TYPE& notifyType, 
            AUTO_UPDATE_DAY* pAutoUpdateDay, 
            INT16* pnAutoUpdateTime);

        //���ܣ����� WINODWS UPDATE ����
        //������
        //      notifyType OUT ��������
        //      pAutoUpdateDay OUT �Զ��������ڣ�һ���еĵڼ��죩
        //          [notifyType == NOTIFY_TYPE_SCHEDULED_INSTALL ʱ��Ч, ��� notifyType �������ֵ�����ΪNULL�򲻽�������]
        //      pnAutoUpdateTime OUT �Զ�����ʱ�䣨һ���ڵĵڼ��㣬��Χ 0 ~ 23����Ӧ�賿0�㵽����23�㣩
        //          [notifyType == NOTIFY_TYPE_SCHEDULED_INSTALL ʱ��Ч, ��� notifyType �������ֵ�����ΪNULL�򲻽�������]
        ERROR_CODE SetNotiyType(
            NOTIFY_TYPE notifyType, 
            AUTO_UPDATE_DAY* pAutoUpdateDay, 
            INT16* pnAutoUpdateTime);

        ERROR_CODE GetLastUpdateTime(bool bHasUpdate, UINT64& nTime);

        //////////////////////////////////////////////////////////////////////////

        static bool GetWSUSUrl(string& strUrl);

    private:

        IAutomaticUpdates* m_pIAutomaticUpdates;
    };
}
