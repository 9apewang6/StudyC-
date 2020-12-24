#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //����

    class CTcpClient;

    //////////////////////////////////////////////////////////////////////////
    //ITcpClientHandler ��ִ��ϸ��

    class ITcpClientHandler
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_USER_CLOSE,				//ҵ�񲿷������ؿ�
            ERROR_CODE_SYSTEM_CLOSE,			//ϵͳ�����ر�
            ERROR_CODE_REMOTE_CLOSE,			//Զ�����������ر�
            ERROR_CODE_SYSTEM,					//ϵͳ�ڲ�����
            ERROR_CODE_PROTOCOL,                //Э�����
        };

        //////////////////////////////////////////////////////////////////////////

        ITcpClientHandler(){};
        virtual ~ITcpClientHandler(){};

        //////////////////////////////////////////////////////////////////////////
        //�ӿں�������Ҫ����

        //����:��ȡ���յ���Ϣͷ��С ����CAsynTcpServer���ã� [һ����Ҫ����]
        //����ֵ:��Ϣͷ��С;������� 0 ��CTcpClient���󲻻������ݣ��յ���ֱ��֪ͨ OnReceive
        virtual UINT32 GetHeadSize() = 0;

        //����:��ȡ��ǰ���յ���Ϣ�ܴ�С ����CAsynTcpServer���ã� [һ����Ҫ����]
        //����ֵ:��Ϣ��С
        virtual UINT32 GetMsgSize(const char* pData, UINT32 nDataSize) = 0;

        //�¼�:���յ���Ϣ [һ����Ҫ����]
        virtual void OnReceived(CTcpClient* pCTcpClient, const char* pData, UINT32 nSize) = 0;

        //�¼�:����ǰ
        //����ֵ��true ִ������; false ������
        virtual bool OnConnecting(CTcpClient* pCTcpClient, UINT32& nIP, UINT16& nPort) = 0;

        //�¼�:���ӳɹ�
        virtual void OnConnected(CTcpClient* pCTcpClient, UINT32 nIP, UINT16 nPort){};

        //�¼�:����ʧ��
        virtual void OnConnectFailed(CTcpClient* pCTcpClient, UINT32 nIP, UINT16 nPort){};

        //�¼�:���ӹر�
        virtual void OnClosed(CTcpClient* pCTcpClient, ERROR_CODE errorCode){};

        //�¼�:���ʱ��(ֻ�����ӳɹ��󴥷�)
        virtual void OnTime(CTcpClient* pCTcpClient){};
    };

    //////////////////////////////////////////////////////////////////////////
    //CTcpClient SOCKE �ͻ�����

    class CTcpClient : public SysBase::CObject
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM,
            ERROR_CODE_SYSTEM,			//ϵͳ�������
            ERROR_CODE_STOP,			//����δ��������ֹͣ
            ERROR_CODE_START,			//����������
            ERROR_CDOE_NO_CONNECT,      //δ�ɹ����ӷ�����
            ERROR_CODE_QUEUE_FULL,		//������
            ERROR_CODE_OVER_SIZE,		//���͵����ݴ��ڷ��ͻ�������С
        };

        //////////////////////////////////////////////////////////////////////////

        CTcpClient();

        virtual ~CTcpClient();
        
        //����:����
        //����:
        //      ITcpClientHandler* pHandler IN ִ��ϸ��
        //		UINT32 nRecvBufferSize IN ���ջ�������С
        //		UINT32 nSendBufferSize IN ���ͻ�������С
        //      UINT32 nSendBufferCount IN ���ͻ�����������
        //		UINT32 nIntervalOnTime IN ���ʱ�䣨���� OnTime �¼���
        //      bool bSysKeepAlive IN �Ƿ�����ϵͳ��������
        //      UINT32 nIntervalTime IN ���������ܺ��������������ʱ��[��λΪ����]
        //      UINT32 nConnectIntervalTime IN �������ӵļ��ʱ��[��λΪ����]
        ERROR_CODE Start(
            ITcpClientHandler* pHandler,
            UINT32 nRecvBufferSize,
            UINT32 nSendBufferSize,
            UINT32 nSendBufferCount,
            UINT32 nIntervalOnTime = 1000,
            bool bSysKeepAlive = false,
            UINT32 nIntervalTime = 0,
            UINT32 nConnectIntervalTime = 1);

        //����:ֹͣ
        void Stop();

        //����:Ͷ���첽������Ϣ
        //����:
        //      const void* pData IN ���͵Ļ������׵�ַ
        //      UINT32 nDataSize IN ���ͻ�������С
        //����ֵ:Ͷ�ݷ��ͳɹ����
        ERROR_CODE Send(
            const void* pData, 
            UINT32 nDataSize);
        
        //�����Ƿ�ɹ�
        bool IsConnected();

        //����:�����Ͽ����ӣ���������Զ�������
        void Abort();

    private:

        void* m_pImp;

    };
}
