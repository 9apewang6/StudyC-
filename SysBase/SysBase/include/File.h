#pragma once

#include "SysBase.h"

namespace SysBase
{
    struct TFileInfo
    {
        bool isDirectory;
        INT64 nCreationTime;
        INT64 nLastAccessTime;
        INT64 nLastWriteTime;
        INT64 nFileSize;
        CHAR szFileName[MAX_PATH];
    };

    typedef list<TFileInfo> FileInfoList;

    struct TFileInfoW
    {
        bool isDirectory;
        INT64 nCreationTime;
        INT64 nLastAccessTime;
        INT64 nLastWriteTime;
        INT64 nFileSize;
        WCHAR wzFileName[MAX_PATH];
    };

    typedef list<TFileInfoW> FileInfoListW;

    class CFile : SysBase::CObject
    {
    public:

        enum EFileSeek
        {
            FILE_SEEK_CUR = 0,
            FILE_SEEK_BEGIN,
            FILE_SEEK_END
        };

        CFile();

        virtual ~CFile();

        void Close();

        bool Create(const char* szFileName, const char* szMode, bool bThreadSafe = false);

        bool Create(const WCHAR* wzFileName, const WCHAR* wzMode, bool bThreadSafe = false);

        bool IsOpen();

        UINT32 Read(void* pBuffer, UINT32 nMaxReadBytesCount);
        
        UINT32 Write(const void* pBuffer, UINT32 nMaxWriteBytesCount);

        UINT32 Read(void* pBuffer, UINT32 nMaxReadBytesCount, INT64 nSeekOffset, EFileSeek eSeekOpt);

        UINT32 Write(const void* pBuffer, UINT32 nMaxWriteBytesCount, INT64 nSeekOffset, EFileSeek eSeekOpt);
        
        bool Flush();

        bool Seek(INT64 nOffset, EFileSeek eSeekOpt);

        INT64 GetSize();

        //////////////////////////////////////////////////////////////////////////

        static bool IsFile(const char* szFilePath);

        static bool IsFile(const WCHAR* wzFilePath);

        static bool Copy(const char* szFromFilePath, const char* szToFilePath);

        static bool Copy(const WCHAR* szFromFilePath, const WCHAR* szToFilePath);

        static bool Move(const char* szFromFilePath, const char* szToFilePath);

        static bool Move(const WCHAR* szFromFilePath, const WCHAR* szToFilePath);

        static bool Delete(const char* szFilePath);

        static bool Delete(const WCHAR* szFilePath);
        
        //��ȡ�ļ���С
        //�������ļ�·��
        //����ֵ: -1 ����
        static INT64 GetFileSize(const char* szFilePath);

        //��ȡ�ļ���С
        //�������ļ�·��
        //����ֵ: -1 ����
        static INT64 GetFileSize(const WCHAR* wzFilePath);

        static bool GetFileInfosByDirPath(const char* szDirPath, FileInfoList& fileInfoList);

        //��ȡָ��Ŀ¼·���µ��ļ����ļ�����Ϣ����������Ŀ¼�µ��ļ����ļ��У�
        static bool GetFileInfosByDirPath(const WCHAR* wzDirPath, FileInfoListW& fileInfoList);

        static bool GetSaveFilePath(string& strFilePath, const PCHAR szFileName = NULL, const PCHAR szTitle = NULL);

        static bool GetSaveFilePath(wstring& strFilePath, const PWCHAR wzFileName = NULL, const PWCHAR wzTitle = NULL);

        static bool GetOpenFilePath(string& strPath, const char* szTitle = NULL);

        static bool GetOpenFilePath(wstring& strPath, const WCHAR* wzTitle = NULL);

        static bool CreateEmptyFile(PCCHAR szFilePath, INT64 nSize);

        static bool CreateEmptyFile(PCWCHAR szFilePath, INT64 nSize);

    protected:

    private:

        FILE* m_pFile;

        CThreadMutex m_lock;

        bool m_bThreadSafe;

    };
}