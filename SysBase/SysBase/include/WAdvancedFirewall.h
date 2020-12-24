#include "SysBase.h"
#include <Icftypes.h>
#include <Netfw.h>

namespace SysBase
{
    //����վ����
    enum EWAFDirectionType
    {
        WAF_DIRECTION_TYPE_IN = 1,      //��վ
        WAF_DIRECTION_TYPE_OUT = 2,     //��վ

    };

    //��������
    enum EWAFActionType
    {
        WAF_ACTION_TYPE_BLOCK = 0,  //��ֹ����
        WAF_ACTION_TYPE_ALLOW,      //��������
    };

    //��������
    enum EWAFProfileType
    {
        WAF_PROFILE_TYPE_DOMAIN   = 1,              //��
        WAF_PROFILE_TYPE_PRIVATE  = 2,              //ר��
        WAF_PROFILE_TYPE_PUBLIC   = 4,              //����
        WAF_PROFILE_TYPE_ALL      = 0x7FFFFFFF,     //ȫ��
    };

    struct TWAFRule
    {
        TWAFRule()
        {
            eAction = WAF_ACTION_TYPE_BLOCK;
            eDirection = WAF_DIRECTION_TYPE_IN;
            bEnabled = false;
            nProfiles = 0;
            nProtocol = WAF_PROFILE_TYPE_ALL;
        }

        wstring strName;                //�������ƣ����ظ���
        EWAFDirectionType eDirection;   //����վ(EDirectionType)
        bool    bEnabled;               //���û���ã�0:����;1:���ã�
        EWAFActionType eAction;         //�������ͣ�EActionType��
        wstring strAppName;             //Ӧ�øù���ĳ���ȫ·��
        wstring strServiceName;         //Ӧ�øù���ķ�����
        wstring strDesc;                //����
        wstring strGroup;               //��������
        INT32   nProtocol;              //Э�飨6:TCP; 17:UDP��[0:�κ�,HOPOPT;1:ICMPv4;2:IGMP;6:TCP;17:UDP;41:IPv6;43:IPv6-Route;44:IPv6-Frag;47:GRE;58:ICMPv6;59:IPv6-NoNxt;60:IPv6-0pts;112:VRRP;113:PGM;115:L2TP]
        wstring strLocalAddr;           //���ص�ַ(ȫ����""��"*")
        wstring strLocalPorts;          //���ض˿�(ȫ����""��"*")
        wstring strRemoteAddr;          //���ص�ַ(ȫ����""��"*")
        wstring strRemotePorts;         //���ض˿�(ȫ����""��"*")
        INT32   nProfiles;              //�������ù���EProfileType �е�һ��������
    };

    //WINDOWS�߼�����ǽ
    class CWAdvancedFirewall
    {
    public:

        CWAdvancedFirewall();

        virtual ~CWAdvancedFirewall();

        bool GetStatus(EWAFProfileType type, bool& bEnabled);

        bool SetStatus(EWAFProfileType type, bool bEnable);

        bool GetRuleAll(list<TWAFRule>& ruleList);

        bool AddRule(TWAFRule& aRule);

        bool RemoveRule(PCWCHAR szRuleName);

        bool UpdateRule(TWAFRule& aRule);

        bool GetRulesByName(PCWCHAR szRuleName, TWAFRule& aRule);

    protected:
    private:

        INetFwPolicy2* m_pPolicy;
    };
}