#pragma once

#include "SocketCommon.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//WINDOWS SOCKET ��ʼ���࣬�����Զ����� WSAStartup �� WSACleanup

	class CSocketLoader
	{
	public:

		~CSocketLoader();

		//////////////////////////////////////////////////////////////////////////
		//��̬����

		//��ʼ��SOCKET��
		//�쳣
		static bool InitSocket();

	protected:

		CSocketLoader();

	private:

		static CSocketLoader s_CSocketLoader;

		static BOOL bInitSocket;
	};
}
