#pragma once

#include <Windows.h>
#include <map>
#include <list>

using namespace std;

namespace SysBase
{
    struct TFastFileCacheBlock
    {
        UINT32 nIndex;      //���ݿ�����
        PCHAR pData;        //����
        UINT32 nDataSize;   //��Ч���ݴ�С
    };

    class CFastFileCache
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

        CFastFileCache();

        virtual ~CFastFileCache();

        ERROR_CODE Init(const char* lpFilePath, const char* lpName, UINT32 nMaxWriteSize, UINT32 nMaxFileSize);

        ERROR_CODE Add(const void* pData, UINT32 nDataSize, DWORD* pdwIndexOut);

        const TFastFileCacheBlock* GetBlock(UINT32 nIndex);

        DWORD GetCurBlockCount(BOOL* pbIsEnd = NULL);

        void Clear();

    protected:

    private:

#pragma pack(1)

        //�ļ�ͷ
        struct TFileHead
        {
            CHAR szName[64];            //�ļ���Ч��ʶ
            UINT32 nSize;               //�ļ���д����ܴ�С������ʵ�ʱ��ļ�С��[�̶�ֵ]
            UINT32 nHasWriteSize;       //��д����Ч�������ܴ�С
            UINT32 nWriteCount;         //д������ݰ�����
            BYTE btEnd;                 //�����Ƿ񲻿���д��
        };

        //���ݿ�ͷ
        struct TBlockHead
        {
            UINT32 nIndex;
            UINT32 nDataSize;
        };

#pragma pack()

        //////////////////////////////////////////////////////////////////////////

        typedef map<DWORD, TFastFileCacheBlock> BlockMap;

        BlockMap m_BlockMap;

        CRITICAL_SECTION m_CriticalSection;

        HANDLE m_hFile;

        HANDLE m_hFileMap;

        LPVOID m_lpBuffer;

        TFileHead* m_pTFileHead;        //�ļ�ͷ

        BOOL m_bInit;

        DWORD m_dwMaxWriteSize;
    };
}