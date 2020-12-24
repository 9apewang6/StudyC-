#pragma once

#include "SysBase.h"
#include "Socket.h"

namespace SysBase
{
    class CTcpSocket : public CSocket
    {
    public:

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM,           //��������
            ERROR_CODE_NO_CONNECT,      //û������
            ERROR_CODE_HAS_CONNECT,     //�Ѿ�����
            ERROR_CODE_DISCONNECT,      //�����жϻ�Ͽ�
            ERROR_CODE_HAS_CLOSE,       //�����Ѿ��ر�
            ERROR_CODE_REMOTE_CLOSE,    //Զ�����ӹر�
            ERROR_CODE_SYSTEM,			//ϵͳ�������
            ERROR_CODE_CONNECT_FAILED,  //����ʧ��
            ERROR_CODE_TIMEOUT,         //��ʱ
            ERROR_CODE_RECV_NO_DATA,    //û�н��յ��κ�����
            ERROR_CODE_RECV_OVER_SIZE,  //���յ����ݴ����ύ�Ļ���������
            ERROR_CODE_PROTOCOL,        //Э�����
        };

        CTcpSocket();

        virtual ~CTcpSocket();

        ERROR_CODE Connect(const char* szIP, UINT16 nPort, UINT32 nWaitTime = INFINITE);

        ERROR_CODE Connect(UINT32 nIP, UINT16 nPort, UINT32 nWaitTime = INFINITE);

        void Disconnect();

        bool IsConnected();

        ERROR_CODE Send(const void* pData, UINT32 nSize);

        //��������
        ERROR_CODE Recv(void* pBuffer, UINT32 nBufferSize, UINT32& nRecvSzie, UINT32 nWaitTime = INFINITE);

        //ͨ���Զ�������Э�鷽ʽ������������(Ĭ��Э����Ĵ�С�ֶζ��ڰ�ͷ��ǰ4���ֽ�)
        ERROR_CODE RecvEx(void* pBuffer, UINT32 nBufferSize, UINT32& nRecvSzie, UINT32 nWaitTime = INFINITE);

    private:

        bool m_bConnected;
    };
}
