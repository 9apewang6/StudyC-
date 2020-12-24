#pragma once

#include "SysBase.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//��������

	class CTcpMultiClient;

	//////////////////////////////////////////////////////////////////////////  
	//ITcpMultiClientHandler ��ִ��ϸ��

	class ITcpMultiClientHandler
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

		ITcpMultiClientHandler(){};

		virtual ~ITcpMultiClientHandler(){};

		//////////////////////////////////////////////////////////////////////////
		//�ӿں�������Ҫ����

		virtual UINT32 GetHeadSize() = 0;

		virtual UINT32 GetMsgSize(const char* pData, UINT32 pDataSize) = 0;

		virtual void OnReceived(CTcpMultiClient* pCTcpMultiClient, UINT32 nSocketID, UINT32 nIP, UINT16 nPort, const char* pData, UINT nDataSize){};

		virtual void OnClosed(CTcpMultiClient* pCTcpMultiClient, UINT32 nSocketID, UINT32 nIP, UINT16 nPort, ERROR_CODE errorCode){};
	};

	//////////////////////////////////////////////////////////////////////////
	//CTcpMultiClient

	class CTcpMultiClient : public CObject 
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
			ERROR_CODE_SOCKET_FULL,		//��������
            ERROR_CODE_CONNECT_FAILED,  //����ʧ��
		};

		//////////////////////////////////////////////////////////////////////////

		CTcpMultiClient();

		virtual ~CTcpMultiClient();

		//////////////////////////////////////////////////////////////////////////

		ERROR_CODE Start(
			ITcpMultiClientHandler* pITcpMultiClientHandler,
			UINT16 nMaxClientCount,
			UINT16 nIOWorkerCount,
			UINT32 nRecvBufferSize,
			UINT32 nSendBufferSize,
			UINT32 nSendBufferCount);

		void Stop();

        ERROR_CODE Connect(
            UINT32& SocketID_out, 
            UINT32 nIP, 
            UINT16 nPort, 
            UINT32 nWaitTime = 3000,
            bool bSysKeepAlive = false,
            UINT32 nIntervalTime = 20000);

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