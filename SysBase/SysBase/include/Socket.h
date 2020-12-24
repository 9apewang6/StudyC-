#pragma once

#include "SocketCommon.h"
#include "ThreadSync.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//Socket��ַ��Ϣ��
	
	class CSocketAddr
	{
	public:
	
#ifndef SOCKET_IPV6

		//����:ת�������ֽ���IPV4��ַ��ϢΪ�ַ���
		//����:
		//      char* szIP OUT ����Ļ�����
		//		WORD wSize IN ��������С(������ڵ��� SOCKET_IP_MAX_SIZE = 50)
		//		UINT32 nIP IN IP��ַ
		//����ֵ:0 ����; >0 ʵ����Ч�����ݴ�С��������\0��

		static WORD ToStringIP(char* szIP, WORD wSize, UINT32 nIP);
		
		//����:ת��IPV4��ַ�ַ���Ϊ�����ֽ�����ֵ
		//����:
		//		char* szIP IN ��ַ�ַ���
		//����ֵ: �����ֽ�����ֵ

		static DWORD ToDwordIP(const char* szIP);
#endif

		//����:ת����ַ��ϢΪpTSockAddr�ṹ 
		//����:
		//      INET_SOCKET_ADDRESS_STRUCT* pSockAddr IN ��ַ��Ϣ,����ΪNULL
		//      TSockAddr* pTSockAddr OUT ��ַ��Ϣ�ṹָ��
		static bool ToTSockAddr(
			const INET_SOCKET_ADDRESS_STRUCT* pSockAddr, 
			TSockAddr* pTSockAddr);
	
		//����:ת����ַ��ϢΪpTSockAddr�ṹ 
		//����:
		//      TSockAddr* pTSockAddr IN ��ַ��Ϣ�ṹָ��
		//      INET_SOCKET_ADDRESS_STRUCT* pSockAddr OUT ��ַ��Ϣ,����ΪNULL
		static bool ToInetSockAddr(
			const TSockAddr* pTSockAddr,
			INET_SOCKET_ADDRESS_STRUCT* pSockAddr);
	};

	//////////////////////////////////////////////////////////////////////////
	//CSOCKET �׽�����

	class CSocket : public CThreadMutex
	{
	public:

		virtual ~CSocket();

		//����:closesocket��һ�㲻�������رն�����TIME_WAIT�Ĺ��̣����Ƿ����ø�socket
		//����:
		//      bool bIsReUse IN �ǻ��

		bool SetReuseAddr(bool bIsReUse);

		//����:�Ƿ����ø�socket
		//����ֵ: ���û��

		bool IsReuseAddr();

		//����: �Ƿ�Ҫ�Ѿ���������״̬��soket�ڵ���closesocket��ǿ�ƹرգ�������TIME_WAIT�Ĺ���
		//����:
		//      bool bIsReUse IN �ǻ��

		bool SetDontLinger(bool bDontLinger);

		//����: �Ѿ���������״̬��soket�ڵ���closesocket���Ƿ�ǿ�ƹرգ�������TIME_WAIT�Ĺ���
		//����ֵ: �Ƿ񲻵ȴ�

		bool IsDontLinger();

		//����: ����SOCKET���ͻ�������С������ʹ��ϵͳһ�ο��Է��͸������Ϣ[ϵͳĬ�ϵ�״̬����һ��Ϊ8688�ֽ�(ԼΪ8K)]
		//      �������ݵģ�ϣ��ʱ��������ϵͳ��������socket�������Ŀ�����Ӱ���������ܣ�����Ϊ 0 
		//����:
		//      int nBufferSize IN ��������С

		bool SetSendBufferSize(int nBufferSize);

		//����: ��ȡSOCKET���ͻ�������С
		//����ֵ: ���ͻ�������С

		int GetSendBufferSize();

		//����: ����SOCKET���ջ�������С������ʹ��ϵͳһ�ο��Խ��ո������Ϣ[ϵͳĬ�ϵ�״̬����һ��Ϊ8688�ֽ�(ԼΪ8K)]
		//      �������ݵģ�ϣ��ʱ��������ϵͳ��������socket�������Ŀ�����Ӱ���������ܣ�����Ϊ 0 
		//����:
		//      int nBufferSize IN ��������С

		bool SetRecvBufferSzie(int nBufferSize);

		//����: ��ȡSOCKET���ջ�������С
		//����ֵ: ���ջ�������С

		int GetRecvBufferSize();

		//����: �����ڷ���UDP���ݱ���ʱ�򣬸�socket���͵������Ƿ���й㲥����
		//����:
		//      bool bBroadcast IN �ǻ��

		bool SetBroadcast(bool bBroadcast);

		//����: ��ȡ�ڷ���UDP���ݱ���ʱ�򣬸�socket���͵������Ƿ���й㲥����
		//����ֵ: �Ƿ�

		bool IsBroadcast();

		//����: ������client���ӷ����������У�������ڷ�����ģʽ�µ�socket��connect()�Ĺ�����
		//      �Ƿ���ʱ,ֱ��accpet()������(����������ֻ���ڷ������Ĺ�������������
		//      ���ã��������ĺ������������ò���)
		//����:
		//      bool bBroadcast IN �ǻ��

		bool SetConditionalAccept(bool bConditionalAccept);

		//����: ��ȡ���ڷ�����ģʽ�µ�socket��connect()�Ĺ������Ƿ���ʱ
		//����ֵ: �Ƿ�

		bool IsConditionalAccept();

		//����: ���õȴ���������û��������ݷ��ͳ�ȥ���ٹر�socket[�����ڷ������ݵĹ�����(send()û����ɣ�
		//      ��������û����)��������closesocket(),�����ǿ϶���ʧ��]
		//����:
		//      u_short dwSecond IN �ȴ�������

		bool SetWaitTime(u_short dwSecond);

		//����: ��ȡ�ȴ�������
		//����ֵ: �ȴ�������

		WORD GetWaitTime();

		//����: �����ӱ�����
		//����:
		//      UINT32 nIntervalTime IN ���μ������ʱ��[��λΪ����]
		//      UINT32 nTime IN �״ο�ʼ����ʱ��[��λΪ����]

		bool OpenKeepAlive(
			UINT32 nIntervalTime, 
			UINT32 nTime);

		//����: �ر����ӱ��ּ��

		bool CloseKeepAlive();

		//����: ֹͣͨ��
		//����:
		//  int nHow IN ö�����ͣ�SD_BOTH���رս��պͷ��͡�SD_RECEIVE���رս��ա�SD_SEND���رշ���
		void Stop(int nHow = SD_BOTH);

		//����: �Ƿ��Ѿ�ֹͣ
		//����ֵ:TURE ֹͣ false δֹͣ
		bool IsStop();

		//����:�ر�
		virtual void Close();

		//����;�Ƿ��Ѿ��ر�
		//����ֵ:TURE �ر� false δ�ر�
		bool IsClose();

		//��ȡ Socket �� HANDLE 
		//����ֵ: Socket �� HANDLE 
		SOCKET GetSocketHandle();

		//����:��ȡԶ�̵�ַ
		//����:
		//      INET_SOCKET_ADDRESS_STRUCT* pSockAddr OUT ��ַ��Ϣ,����ΪNULL
		//����ֵ: ת���Ƿ�ɹ�
		bool GetRemoveAddress(INET_SOCKET_ADDRESS_STRUCT* pSocketAddress);

		//����:��ȡԶ�̵�ַ
		//����:
		//      TSockAddr* pSockAddr OUT ��ַ��Ϣ,����ΪNULL
		//����ֵ: ת���Ƿ�ɹ�
		bool GetRemoveAddress(TSockAddr* pSocketAddress);

		//����:��ȡ���ص�ַ
		//����:
		//      INET_SOCKET_ADDRESS_STRUCT* pSockAddr OUT ��ַ��Ϣ,����ΪNULL
		//����ֵ: ת���Ƿ�ɹ�
		bool GetLoaclAddress(INET_SOCKET_ADDRESS_STRUCT* pSocketAddress);

		//����:��ȡ���ص�ַ
		//����:
		//      TSockAddr* pSockAddr OUT ��ַ��Ϣ,����ΪNULL
		//����ֵ: ת���Ƿ�ɹ�
		bool GetLoaclAddress(TSockAddr* pSocketAddress);

	protected:

		//���캯��

		CSocket();

		//����:�ȴ��Ƿ������ݿɽ���
		//����:
		//		 UINT32 nWaitTime IN �ȴ�������ʱ��
		//����ֵ:�����ݿɽ��ջ���
		bool WaitRecv(UINT32 nWaitTime);
		
		//����:�Ƿ��ܷ�������
		//����:
		//		 UINT32 nWaitTime IN �ȴ�������ʱ��
		//����ֵ:�ǻ��
		bool WaitSend(UINT32 nWaitTime);
		
		//����:�����Ƿ�Ϊ����
		//����:
		//      bool bBlock IN TURE Ϊ����ģʽ false Ϊ������ģʽ
		bool SetBlock(bool bBlock);

		//�����ο�MSDN setsockopt
		bool SetSocketOption(
			int level, 
			int optname, 
			const char* optval, 
			int optlen);

		//�����ο�MSDN getsockopt
		bool GetSocketOption(
			int level, 
			int optname, 
			char* optval, 
			int* optlen);

		//////////////////////////////////////////////////////////////////////////
		//���ݳ�Ա

		bool m_bIsClose;    //�Ƿ�ر�

		SOCKET m_Socket;    //��Ҫ�����ݳ�Ա��SOCKET
	};
}