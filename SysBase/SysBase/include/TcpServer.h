#pragma once

#include "SysBase.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//��������

	class CTcpServer;

	//////////////////////////////////////////////////////////////////////////  
	//ITcpServerHandler : CTcpServer ��ִ��ϸ��

	class ITcpServerHandler
	{
	public:

		//////////////////////////////////////////////////////////////////////////

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,
			ERROR_CODE_USER_CLOSE,				//ҵ�񲿷������ؿ�
			ERROR_CODE_SYSTEM_CLOSE,			//ϵͳ�����ر�
			ERROR_CODE_REMOTE_CLOSE,			//Զ�����������ر�
			ERROR_CODE_SOCKET_FULL,				//��������
			ERROR_CODE_KEEP_ALIVE_TIME_OUT,		//������ʱ
			ERROR_CODE_SYSTEM,					//ϵͳ�ڲ�����
            ERROR_CODE_PROTOCOL,                //Э�����
		};

		//////////////////////////////////////////////////////////////////////////

		ITcpServerHandler(){};

		virtual ~ITcpServerHandler(){};

		//////////////////////////////////////////////////////////////////////////
		//�ӿں�������Ҫ����

		virtual UINT32 GetHeadSize() = 0;

		virtual UINT32 GetMsgSize(const char* pData, UINT32 nDataSize) = 0;

		//�¼������յ������� 
		//����ֵ: true:����;false:������ǰ���յ���������
		virtual bool OnAccepted(CTcpServer* pCTcpServer, UINT32 nSocketID, UINT32 nIP, UINT16 nPort){ return true; };

		virtual void OnAcceptedError(CTcpServer* pCTcpServer, UINT32 nIP, UINT16 nPort, ERROR_CODE errorCode){};

		virtual void OnReceived(CTcpServer* pCTcpServer, UINT32 nSocketID, UINT32 nIP, UINT16 nPort, const char* pData, UINT nDataSize){};

		virtual void OnClosed(CTcpServer* pCTcpServer, UINT32 nSocketID, UINT32 nIP, UINT16 nPort, ERROR_CODE errorCode){};
	};

	//////////////////////////////////////////////////////////////////////////
	//CTcpServer 

	class CTcpServer : public CObject 
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
			ERROR_CODE_QUEUE_FULL,		//������
			ERROR_CODE_OVER_SIZE,		//���͵����ݴ��ڷ��ͻ�������С
		};

		enum KEEP_ALIVE_TYPE
		{
			KEEP_ALIVE_TYPE_NONE = 0,	//��������
			KEEP_ALIVE_TYPE_SYSTEM,		//ϵͳ��������
			KEEP_ALIVE_TYPE_DATA		//ͨ���������ݰ���ʽ��Ϊ��������
		};

		//////////////////////////////////////////////////////////////////////////

		CTcpServer();

		virtual ~CTcpServer();

		//////////////////////////////////////////////////////////////////////////

		ERROR_CODE Start(
			ITcpServerHandler* pITcpServerHandler,
			UINT32 nListenIP,
			UINT16 nPort,
			UINT16 nMaxConnectCount,
			UINT16 nIOWorkerCount,
			UINT32 nRecvBufferSize,
			UINT32 nSendBufferSize,
			UINT32 nSendBufferCount, 
			KEEP_ALIVE_TYPE eKeepAliveType = KEEP_ALIVE_TYPE_NONE,
			UINT32 nKeepAliveIntervalTime = 0);

        ERROR_CODE Start(
            ITcpServerHandler* pITcpServerHandler,
            PCCHAR szListenIP,
            UINT16 nPort,
            UINT16 nMaxConnectCount,
            UINT16 nIOWorkerCount,
            UINT32 nRecvBufferSize,
            UINT32 nSendBufferSize,
            UINT32 nSendBufferCount, 
            KEEP_ALIVE_TYPE eKeepAliveType = KEEP_ALIVE_TYPE_NONE,
            UINT32 nKeepAliveIntervalTime = 0);

		void Stop();

		ERROR_CODE Send(
			UINT32 nSocketID,
			const void* pData,
			UINT32 nDataSize);

		void CloseSocket(UINT32 nSocketID);

		UINT32 GetSocketCount();

	private:

		void* m_Imp;
	};
}
