#pragma once

#include "SysBase.h"

namespace SysBase
{
    //��̫����������Ϣ
    struct THWEthernetAdapterInfo
    {
        THWEthernetAdapterInfo()
        {
            nIndex = 0;
            bDhcpEnabled = false;
            bHaveWins = false;
            nLeaseObtained = 0;
            nLeaseExpires = 0;
            bAutoconfigEnabled = false;
            bAutoconfigActive = false;
            bConnected = false;
        }

        string Name;                                //���������ƣ�GUID��
        string Description;                         //���������������ƣ�
        string macAddr;                             //MAC��ַ
        UINT32 nIndex;                              //����������
        bool bDhcpEnabled;                          //�Ƿ�����DHCP

        //KEY:IP��ַ VALUE:��������
        map<string, string> ipAddrList;             //IP��ַ

        list<string> gateWayList;                   //���ص�ַ
        list<string> dhcpSrvList;                   //DHCP�����ַ
        bool bHaveWins;                              //�Ƿ�ʹ��WINS
        list<string> primaryWinsSrvList;            //��ҪWINS�����ַ
        list<string> secondaryWinsSrvList;          //��ҪWINS�����ַ
        INT64 nLeaseObtained;                      //�����Լʱ��(��λ����[UTC])
        INT64 nLeaseExpires;                       //��Լ����ʱ��(��λ����)[�� nLeaseObtained ʱ������ϵĹ�������]

        bool bAutoconfigEnabled;                    //�Զ������Ƿ�����
        bool bAutoconfigActive;                     //�Զ������Ƿ�
        list<string> dnsAddrList;                   //DNS��ַ�б�

        bool bConnected;                            //��ǰ����״̬���Ƿ��Ѿ��������磩
    };

    //��̫��������������Ϣ
    struct TEthernetAdaptersPerformance
    {
        UINT32 nIndex;                  //���
        UINT32 nMtu;                    //Maximum Transmission Unit (MTU)
        UINT32 nSpeed;                  //����ÿ��������ٶȣ���λ��bits [ 1 bit = 1/8 byte ] ��
        UINT32 nAdminStatus;            //������״̬��1:����; 0:����
        UINT32 nLastChange;             //������ʱ��
        UINT32 nInOctets;               //�յ��������ֽ���
        UINT32 nInUcastPkts;            //���յĵ������ݰ�����
        UINT32 nInNUcastPkts;           //���յķǵ������ݰ��������㲥�Ͷಥ���ݰ����������ڣ�
        UINT32 nInDiscards;             //��������ݰ�����������ʹ���ǲ�û�д���
        UINT32 nInErrors;               //��������ݰ�����������Ϊ���������
        UINT32 nInUnknownProtos;        //��������ݰ�����������Ϊ��Э����δ֪
        UINT32 nOutOctets;              //���͵������ֽ���
        UINT32 nOutUcastPkts;           //���͵ĵ������ݰ�����
        UINT32 nOutNUcastPkts;          //���͵ķǵ������ݰ��������㲥�Ͷಥ���ݰ����������ڣ�
        UINT32 nOutDiscards;            //���͵����ݰ�����������ʹ���ǲ�û�д���
        UINT32 nOutErrors;              //���͵����ݰ�����������Ϊ���������
        UINT32 nOutQueueLen;            //������г���
    };

    class CHWEthernetAdapter
    {
    public:

        static bool GetEthernetAdaptersInfoList(list<THWEthernetAdapterInfo>& ethernetAdapterInfoList);

        static bool GertEthernetAdaptersIndexList(list<UINT32>& ethernetAdapterIndexList);

        static bool GetEthernetAdaptersPerformance(
            UINT32 ethernetAdapterIndex, 
            TEthernetAdaptersPerformance& ethernetAdapterPerformanceOut);

        //////////////////////////////////////////////////////////////////////////
        /*  ����ʹ���ʵļ��㷽����
            1.���� GetEthernetAdaptersInfoList �Ȼ�ȡ������Ϣ 
            2.��������Ϣ�е�nIndex��Ϊ�������� GetEthernetAdaptersPerformance ��ȡ��������
            3.��һ���ȼ�¼ nInOctets + nOutOctets �����շ����ֽ���
            4.���һ��ʱ����ٵ��� GetEthernetAdaptersPerformance ������շ��ֽ��� (nInOctets + nOutOctets)
            5.���շ��ֽ��� ��ȥ �ɵ��շ��ֽ������ٳ��� nSpeed ,�͵õ���ǰ������ʹ���ʣ�����ʱ�趼��תΪ double ��
        */
        //////////////////////////////////////////////////////////////////////////

    private:

        CHWEthernetAdapter();
        virtual ~CHWEthernetAdapter();

    };
}
