#pragma once

#include "SysBase.h"

namespace SysBase
{
    struct TSysUserParam
    {
        TSysUserParam()
        {
            nUserFlags = 0;
            nExpiresTime = INFINITE;
        }

        wstring strUserName;        //�û���
        wstring strPwd;             //����
        wstring strFullName;        //ȫ��
        wstring strDesc;            //����
        UINT64  nExpiresTime;       //�˻��Ĺ���ʱ��(CSysUser::ESysUserFlag)
        UINT32  nUserFlags;         //�û��˻���־
    };
    
    struct TSysUserInfo 
    {
        TSysUserInfo()
        {
            nPwdAge = 0;
            nPrivilege = 0;
            nUserFlags = 0;
            nExpiresTime = INFINITE;
            nLastLogonTime = 0;
            nBadPwdCount = 0;
            nLogonCount = 0;
        }

        wstring strUserName;
        wstring strFullName;        //ȫ��
        wstring strDesc;            //����
        UINT32  nUserFlags;         //�û��˻���־(CSysUser::ESysUserFlag)
        UINT64  nExpiresTime;       //�˻��Ĺ���ʱ��

        //////////////////////////////////////////////////////////////////////////
        //���µĳ�Ա����ֻ�ܻ�ȡ���޷� Set

        UINT32  nPrivilege;         //��Ȩ��CSysUser::ESysUserPrivilege��
        UINT32  nPwdAge;            //������һ���޸���������ڵ�ʱ��
        UINT64  nLastLogonTime;     //���һ�γɹ���¼��ʱ��
        UINT32  nBadPwdCount;       //ʹ�ø��û������������������
        UINT32  nLogonCount;        //ʹ�ø��û����ɹ���¼ϵͳ�Ĵ���
    };

    class CSysUser
    {
    public:

        //�û�Ȩ������
        enum ESysUserPrivilege
        {
            Guest = 0,     //�ÿ�
            User = 1,      //�û�
            Admin = 2,     //ϵͳ����Ա
        };

        //�û��˻���־
        enum ESysUserFlag
        {
            None = 0,                   //��
            AccountDisable = 1,         //�����˻�
            PwdCantChange = 2,          //���벻�ܱ��޸�
            DontExpirePwd = 4,          //������������
            PwdExpired = 8,             //�����Ѿ����ڣ����������޸����룩
        };

        static bool AddUser(TSysUserParam& aParam);

        static bool DeleteUser(PCWCHAR szUserName);
        
        //����:
        //  pnErrorCode:    ϵͳ������
        //      ERROR_ACCESS_DENIED 5         �ܾ�����
        //      ERROR_INVALID_PASSWORD 86L    ��Ч������
        //      NERR_InvalidComputer 2351     ��Ч�����
        //      NERR_NotPrimary 2226          �ò���ֻ�����������������
        //      NERR_UserNotFound 2221        �޸��û�
        //      NERR_PasswordTooShort 2245    ����������衣������Ҳ����̫���������ĸ�����ʷ��̫����û���㹻�������ַ����򲻷�����һ���������Ҫ�󡣣�
        static bool ChangeUserPwd(PCWCHAR szUserName, PCWCHAR szOldPwd, PCWCHAR szNewPwd, UINT32* pnErrorCode = NULL);

        static bool GetUserInfo(PCWCHAR szUserName, TSysUserInfo& infoOut);

        static bool SetUserInfo(TSysUserInfo& aParam);

        static bool SetUserInfo(PCWCHAR szUserName, TSysUserInfo& aParam);

        static bool GetUserAll(list<TSysUserInfo>& infoList);
        
        static bool GetGroupAllByUser(PCWCHAR szName, list<wstring>& groupList);

    };
}