#pragma once

#include "SlowReadFileQueue.h"
#include "SlowWriteFileQueue.h"

namespace SysBase
{
    class CSlowFileQueue : public CObject
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_NONE = 0,
            ERROR_CODE_NO_INIT,         //δ��ʼ��
            ERROR_CODE_PARAM,           //��������
            ERROR_CODE_SYSTEM,          //�ڲ���Դ����ʧ�ܻ�������߼�ʧ��
            ERROR_CODE_FILE,            //Ŀ���ļ��뵱ǰ��ʼ����Ϣ
            ERROR_CODE_FULL,            //û�п��е����ݿռ�
            ERROR_CODE_EMTPY,           //������û���κ���Ч����
            ERROR_CODE_INDEX_OUT,       //����ֵ������Χ
            ERROR_CODE_INDEX_INVALID,   //����ֵ��Ӧ�����ݿ��Ѿ��ͷ�
        };

        //////////////////////////////////////////////////////////////////////////

        CSlowFileQueue();

        virtual ~CSlowFileQueue();

        ERROR_CODE Init(const char* lpFileDir, const char* lpWirteFileName, const char* lpExtName, const char* lpName, UINT32 nBlockSize, UINT32 nMaxFileSize, UINT32 nFileLiveTime);

        ERROR_CODE Add(const void* pData, UINT32 nDataSize);

        ERROR_CODE GetData(PCHAR pBuffer, UINT32 nMaxBufferSize, UINT32& nDataSize, UINT32& nDataIndex);

        ERROR_CODE FreeData(UINT32 nDataIndex);

    protected:
    private:

        CSlowWriteFileQueue m_CSlowWriteFileQueue;
        CSlowReadFileQueue m_CSlowReadFileQueue;
    };
}