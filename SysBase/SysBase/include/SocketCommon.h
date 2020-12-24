#pragma once

#include "SysBase.h"


#include <Winsock2.h>
#include <mswsock.h>
#include <Ws2tcpip.h>
#pragma comment( lib, "Ws2_32.lib" )

#include <map>
using namespace std;

//////////////////////////////////////////////////////////////////////////
//��ע��ʹ���й���SOCKET��֮ǰ�����ȵ���CWinSocketLoader::InitSocket()
//      ����ʼ��Socket��
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//��

#define SOCKET_IP_MAX_SIZE 50               //IP��ַ�ַ�������������С
#define SOCKET_IP_MAX_LENGTH 49             //IP��ַ�ַ�����󳤶�
#define SOCKET_UDP_SIZE 1024             //Ĭ�ϵ�UDP���շ����ݴ�С
#define SOCKET_UDP_SEND_BUFFER_COUNT 3000   //Ĭ�ϵ�UDP���ͻ���������

//SOCKET ��ַ���------------------------------------->
#define INET_SOCKET_ADDRESS_STRUCT_IPV4 SOCKADDR_IN                 //IPV4 ��ַ�ṹ

#define INET_SOCKET_ADDRESS_STRUCT_IPV6 SOCKADDR_IN6                //IPV6 ��ַ�ṹ

#define INET_SOCKET_ADDRESS_STRUCT_LENGTH_IPV4 sizeof(SOCKADDR_IN)  //IPV4 ��ַ�ṹ��С

#define INET_SOCKET_ADDRESS_STRUCT_LENGTH_IPV6 sizeof(SOCKADDR_IN6) //IPV6 ��ַ�ṹ��С

#define INET_LOCALHOST_IPV4 "127.0.0.1"		//IPV4 �ı��ص�ַ��ʽ

#define INET_LOCALHOST_IPV6 "::1"			//IPV6 �ı��ص�ַ��ʽ

#define INET_ADDR_ANY_IPV4 "0.0.0.0"		//IPV4 �������ַ��ʽ

#define INET_ADDR_ANY_IPV6 "::0"			//IPV6 �ı��ص�ַ��ʽ

//-------------------------------------<

//Э���� IPV4ΪPE_INET ; IPV6ΪPF_INET6
#ifdef SOCKET_IPV6

#define INET_PF_FAMILY PF_INET6

#define INET_SOCKET_ADDRESS_STRUCT INET_SOCKET_ADDRESS_STRUCT_IPV6  //��ַ�ṹ[����]

#define INET_SOCKET_ADDRESS_STRUCT_LENGTH INET_SOCKET_ADDRESS_STRUCT_LENGTH_IPV6    //��ַ�ṹ��С[����]

#define INET_LOCALHOST_IP INET_LOCALHOST_IPV6   //���ص�ַ��ʽ[����]

#define INET_ADDR_ANY_IP INET_ADDR_ANY_IPV6		//�����ַ��ʽ[����]

#else   //����Ϊ IPV4 Э��

#define INET_PF_FAMILY PF_INET   

#define INET_SOCKET_ADDRESS_STRUCT INET_SOCKET_ADDRESS_STRUCT_IPV4  //��ַ�ṹ[����]

#define INET_SOCKET_ADDRESS_STRUCT_LENGTH INET_SOCKET_ADDRESS_STRUCT_LENGTH_IPV4    //��ַ�ṹ��С[����]

#define INET_LOCALHOST_IP INET_LOCALHOST_IPV4   //���ص�ַ��ʽ[����]

#define INET_ADDR_ANY_IP INET_ADDR_ANY_IPV4		//�����ַ��ʽ[����]

#endif

//////////////////////////////////////////////////////////////////////////
//����ṹ���� 

//WIN32 ������Ĭ�Ͻṹ
typedef struct sysbase_tcp_keepalive
{ 
	u_long  onoff;
	u_long  keepalivetime; 
	u_long  keepaliveinterval; 
}SYSBASE_TCP_KEEPALIVE,* PSYSBASE_TCP_KEEPALIVE; 

#define SIO_KEEPALIVE_VALS   _WSAIOW(IOC_VENDOR,4) 

//////////////////////////////////////////////////////////////////////////

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//TSockAddr SOCKET��ַ���ݽṹ

	struct TSockAddr
	{
		char szIP[SOCKET_IP_MAX_SIZE];
		USHORT uPort;
	};
}
