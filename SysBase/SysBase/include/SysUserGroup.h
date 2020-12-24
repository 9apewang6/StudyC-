#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //��ע:
    //AddGroupMembers,DeleteGroupMembers,SetGroupMembers �Ĳ��� domainAndNameList �е�ÿһ������� "����\�û�" ���ָ�ʽ
    //GetGroupMembers ���ص� domainAndNameListOut Ҳ��һ��

    //////////////////////////////////////////////////////////////////////////

    struct TSysUserGroupInfo
    {
        wstring strName;
        wstring strDesc;
    };

    class CSysUserGroup
    {
    public:

        static bool AddGroup(TSysUserGroupInfo& aInfo);

        static bool DeleteGroup(PCWCHAR szGroupName);

        static bool GetGroupInfo(PCWCHAR szGroupName, TSysUserGroupInfo& infoOut);

        static bool SetGroupInfo(TSysUserGroupInfo& aInfo);

        static bool SetGroupInfo(PCWCHAR szGroupName, TSysUserGroupInfo& aInfo);

        static bool GetGroupAll(list<TSysUserGroupInfo>& infoList);

        //domainAndNameList ��ÿ��Ԫ�صĸ�ʽ: <DomainName>\<AccountName>     
        static bool AddGroupMembers(PCWCHAR szGroupName, list<wstring>& domainAndNameList);

        static bool DeleteGroupMembers(PCWCHAR szGroupName, list<wstring>& domainAndNameList);

        static bool GetGroupMembers(PCWCHAR szGroupName, list<wstring>& domainAndNameListOut);

        static bool SetGroupMembers(PCWCHAR szGroupName, list<wstring>& domainAndNameList);

        //////////////////////////////////////////////////////////////////////////

        static bool AddLocalGroupMembers(PCWCHAR szGroupName, list<wstring>& userNameList);

        static bool DeleteLocalGroupMembers(PCWCHAR szGroupName, list<wstring>& userNameList);

        static bool SetLocalGroupMembers(PCWCHAR szGroupName, list<wstring>& userNameList);

        //////////////////////////////////////////////////////////////////////////

        static bool AddLocalGroupMember(PCWCHAR szGroupName, PCWCHAR szUserName);

        static bool DeleteLocalGroupMember(PCWCHAR szGroupName, PCWCHAR szUserName);
    };
}