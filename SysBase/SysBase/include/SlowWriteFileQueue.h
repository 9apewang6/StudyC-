#pragma once

#include "SysBase.h"

namespace SysBase
{
	class CSlowWriteFileQueue : public CObject
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

        CSlowWriteFileQueue();

        virtual ~CSlowWriteFileQueue();

        ERROR_CODE Init(const char* lpFileDir, const char* lpWirteFileName, const char* lpExtName, const char* lpName, UINT32 nBlockSize, UINT32 nMaxFileSize, UINT32 nFileLiveTime);

        ERROR_CODE Add(const void* pData, UINT32 nDataSize);

    private:
  
		void* m_pImp;
    };
}