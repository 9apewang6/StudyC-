#pragma once

/*
���ฺ����֯���ļ���������Э���������NetClient���͵����񣬵ȵ����շ�����Ϣʱ�ٴ����ظ�ǰ��ҵ��
*/

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //���̰߳�ȫ��ͬһ��WaitKeyID��Ҫ��֤��ͬһ���߳���ʹ��

    class CMsgWaitPool
    {
    public:

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,             //�ɹ�
            ERROR_CODE_PARAM,                   //��������
            ERROR_CODE_OBJECT_EMPTY,            //û�пɷ���Ķ���
            ERROR_CODE_NO_OBJECT,               //û�иõȴ�����
            ERROR_CODE_TIMEOUT,				    //��ʱ
            ERROR_CODE_RECV_SIZE_BIG,			//���յ����ݹ���
            ERROR_CODE_SYSTEM,                  //�ڲ�����
        };

        CMsgWaitPool();

        virtual ~CMsgWaitPool();

        ERROR_CODE Init(UINT32 nWaitObjectCount);
        
        ERROR_CODE SubmitRequest(char* recvBuffer, UINT32 nMaxRecvSize, INT32& nWaitKeyIDOut);

        void CancelWait(INT32 nWaitKeyID);

        ERROR_CODE WaitResponse(INT32 nWaitKeyID, UINT32 nWaitTime, UINT32 &nRecvSizeOut);
       
        void SetResponce(INT32 nWaitKeyID, const void* pData, UINT32 nDataSize);

    protected:

    private:

        struct TMsgEvent 
        {
            TMsgEvent()
            {
                event.Reset();
                pRecvBuffer = NULL;
                nRecvSize = 0;
                nMaxRecvSize = 0;
                errorCode = ERROR_CODE_SUCCESS;
            }

            CEvent event;
            char* pRecvBuffer;
            UINT32 nRecvSize;
            UINT32 nMaxRecvSize;
            ERROR_CODE errorCode;
        };

        //////////////////////////////////////////////////////////////////////////

        TMsgEvent* GetMsgEvent(INT32 nWaitKeyID);

        //////////////////////////////////////////////////////////////////////////

        INT32 m_lKeyValue;

        CThreadMutex m_lock;

        typedef map<INT32, TMsgEvent*> MsgEventMap;

        MsgEventMap m_msgEventMap;

        typedef CPool<TMsgEvent> MsgEventPool;

        MsgEventPool m_MsgEventPool;
    };
}
