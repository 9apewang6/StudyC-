#include "../SysBase_Interface.h"

#define SYSBASE_SRFQ_BLOCK_VALID_USE 0
#define SYSBASE_SRFQ_BLOCK_VALID_CONFIRM 1

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//CSlowReadFileQueueImpImp

	class CSlowReadFileQueueImp
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

		CSlowReadFileQueueImp();

		virtual ~CSlowReadFileQueueImp();

		CSlowReadFileQueue::ERROR_CODE Init(const char* lpFileDir, const char* lpName, UINT32 nBlockSize);

		CSlowReadFileQueue::ERROR_CODE GetData(PCHAR pBuffer, UINT32 nMaxBufferSize, UINT32& nDataSize, UINT32& nDataIndex);

		CSlowReadFileQueue::ERROR_CODE FreeData(UINT32 nDataIndex);

	protected:

		bool FindNewReadFile();

		bool OpenReadFile(PCHAR lpFilePath);

	private:

#pragma pack(1)

		//�ļ�ͷ
		struct TFileHead
		{
			//UINT32 nConfirmBlockCount;  //ȷ�ϵ����ݿ��������� nConfirmBlockCount == nBlockCount �����ɾ�����ļ���
			//UINT32 nBlockCount;         //�ļ����ڵ���Ч���ݿ����
			char szName[64];
			UINT32 nBlockSize;          //������д��ÿ��������ռ�
		};

		//���ݿ�ͷ
		struct TBlockHead
		{
			BYTE btValid;
			UINT32 nDataSize;
		};

#pragma pack()

		//////////////////////////////////////////////////////////////////////////
		//���ò���

		bool m_bInit;

		char m_szFileDir[MAX_PATH];

		char m_szKeyName[64];

		UINT32 m_nBlockSize;            //���С

		//////////////////////////////////////////////////////////////////////////

		typedef map<UINT32, BYTE> WaitFreeDataIndexMap;

		WaitFreeDataIndexMap m_WaitFreeDataIndexMap;

		typedef list<UINT32> BlockList;

		BlockList m_Read_BlockList;

		char m_szReadFilePath[MAX_PATH];

		CRITICAL_SECTION m_Read_CriticalSection;

		TFileHead m_Read_TFileHead;  //�ļ�ͷ

		HANDLE m_hReadFile;      

		UINT32 m_nNeedConfirmBlockCount;
		UINT32 m_nHasConfirmBlockCount;
	};

	//////////////////////////////////////////////////////////////////////////

    CSlowReadFileQueueImp::CSlowReadFileQueueImp()
    {
        m_bInit = false;

        m_nNeedConfirmBlockCount = 0;

        m_nHasConfirmBlockCount = 0;
    }

    CSlowReadFileQueueImp::~CSlowReadFileQueueImp()
    {
        m_bInit = false;

        LeaveCriticalSection(&m_Read_CriticalSection);

        if (INVALID_HANDLE_VALUE != m_hReadFile)
        {
            CloseHandle(m_hReadFile);

            m_hReadFile = INVALID_HANDLE_VALUE;
        }
    }

    CSlowReadFileQueue::ERROR_CODE CSlowReadFileQueueImp::Init(const char* lpFileDir, const char* lpName, UINT32 nBlockSize)
    {
        if (m_bInit)
        {
            return CSlowReadFileQueue::ERROR_CODE_NONE;
        }

        if (!lpFileDir
            || !lpName
            || 0 == nBlockSize)
        {
            return CSlowReadFileQueue::ERROR_CODE_PARAM;
        }

        //////////////////////////////////////////////////////////////////////////

        ZeroMemory(m_szFileDir, MAX_PATH);

        ZeroMemory(m_szKeyName, 64);

        ZeroMemory(m_szReadFilePath, MAX_PATH);

        //////////////////////////////////////////////////////////////////////////
        //Base

        //KeyName
        int nKeyLen = (int)strlen(lpName);

        if (nKeyLen > 64)
        {
            memcpy(m_szKeyName, lpName, 64);

        }
        else
        {
            memcpy(m_szKeyName, lpName, nKeyLen);
        }

        //FileDir
        int nFileDirLen = (int)strlen(lpFileDir);

        strncpy(m_szFileDir, lpFileDir, nFileDirLen > MAX_PATH ? MAX_PATH : nFileDirLen);

        m_szFileDir[MAX_PATH - 1] = NULL;

        //m_nBlockSize
        m_nBlockSize = nBlockSize + sizeof(TBlockHead);

        InitializeCriticalSection(&m_Read_CriticalSection);

        m_hReadFile = INVALID_HANDLE_VALUE;

        m_bInit = true;

        return CSlowReadFileQueue::ERROR_CODE_NONE;
    }

    CSlowReadFileQueue::ERROR_CODE CSlowReadFileQueueImp::GetData(PCHAR pBuffer, UINT32 nMaxBufferSize, UINT32& nDataSize, UINT32& nDataIndex)
    {
        if (!m_bInit)
        {
            return CSlowReadFileQueue::ERROR_CODE_NO_INIT;
        }

        if (!pBuffer
            || (m_nBlockSize - sizeof(TBlockHead)) > nMaxBufferSize)
        {
            return CSlowReadFileQueue::ERROR_CODE_PARAM;
        }

        //�ȴ������Ƿ������ݿ�ȡ
        EnterCriticalSection(&m_Read_CriticalSection);

        //���û�������ļ����Ƿ��пɶ��ļ�
        if (INVALID_HANDLE_VALUE == m_hReadFile)
        {
            if (!this->FindNewReadFile())
            {
                LeaveCriticalSection(&m_Read_CriticalSection);

                return CSlowReadFileQueue::ERROR_CODE_EMTPY;
            }
        }

        if (0 == m_Read_BlockList.size())
        {
            LeaveCriticalSection(&m_Read_CriticalSection);

            return CSlowReadFileQueue::ERROR_CODE_EMTPY;
        }

        UINT32 nBlockIndex = m_Read_BlockList.front();

        m_Read_BlockList.pop_front();

        SetFilePointer(m_hReadFile, nBlockIndex, NULL, FILE_BEGIN);

        DWORD dwReadBytes = 0;

        TBlockHead aTBlockHead = {0};

        if (!ReadFile(m_hReadFile, &aTBlockHead, sizeof(TBlockHead), &dwReadBytes, NULL))
        {

        }

        if (sizeof(TBlockHead) != dwReadBytes)
        {

        }

        if (!ReadFile(m_hReadFile, pBuffer, aTBlockHead.nDataSize, &dwReadBytes, NULL))
        {

        }

        if (aTBlockHead.nDataSize != nDataSize)
        {

        }

        nDataSize = dwReadBytes;

        nDataIndex = nBlockIndex;

        m_WaitFreeDataIndexMap.insert(WaitFreeDataIndexMap::value_type(nBlockIndex, 0));

        LeaveCriticalSection(&m_Read_CriticalSection);

        return CSlowReadFileQueue::ERROR_CODE_NONE;
    }

    CSlowReadFileQueue::ERROR_CODE CSlowReadFileQueueImp::FreeData(UINT32 nDataIndex)
    {
        if (!m_bInit)
        {
            return CSlowReadFileQueue::ERROR_CODE_NO_INIT;
        }

        EnterCriticalSection(&m_Read_CriticalSection);

        if (m_WaitFreeDataIndexMap.end() == m_WaitFreeDataIndexMap.find(nDataIndex))
        {
            LeaveCriticalSection(&m_Read_CriticalSection);

            return CSlowReadFileQueue::ERROR_CODE_INDEX_INVALID;
        }

        if (m_hReadFile)
        {
            m_nHasConfirmBlockCount++;

            DWORD dwWriteBytes = 0;

            SetFilePointer(m_hReadFile, nDataIndex, NULL, FILE_BEGIN);

            BYTE btValid = SYSBASE_SRFQ_BLOCK_VALID_CONFIRM;

            WriteFile(m_hReadFile, &btValid, sizeof(BYTE), &dwWriteBytes, NULL);
        }

        m_WaitFreeDataIndexMap.erase(nDataIndex);

        //���ȫ��ȷ�ϣ�ɾ�����ļ�
        if (m_nHasConfirmBlockCount >= m_nNeedConfirmBlockCount)
        {
            CloseHandle(m_hReadFile);

            m_hReadFile = INVALID_HANDLE_VALUE;

            DeleteFileA(m_szReadFilePath);
        }

        LeaveCriticalSection(&m_Read_CriticalSection);

        return CSlowReadFileQueue::ERROR_CODE_NONE;
    }

    bool CSlowReadFileQueueImp::FindNewReadFile()
    {
        WIN32_FIND_DATAA FindFileData;
        HANDLE hFind = INVALID_HANDLE_VALUE;

        char szDirPath[MAX_PATH * 2] = {0};        
        char szFilePath[MAX_PATH * 2] = {0};

        DWORD dwHighLastWriteTime = 0;
        DWORD dwLowLastWriteTime = 0;

        sprintf(szDirPath, "%s\\*", m_szFileDir);

        //////////////////////////////////////////////////////////////////////////
        //2.������ԣ�������ط�(��ѯ�����ļ��������ļ�)

        hFind = FindFirstFileA(szDirPath, &FindFileData);

        if (hFind != INVALID_HANDLE_VALUE) //û���κ��ļ�
        {
            if (dwLowLastWriteTime == FindFileData.ftLastWriteTime.dwLowDateTime 
                && dwHighLastWriteTime == FindFileData.ftLastWriteTime.dwHighDateTime)
            {
                return false;
            }
            else
            {
                dwLowLastWriteTime = FindFileData.ftLastWriteTime.dwLowDateTime;
                dwHighLastWriteTime = FindFileData.ftLastWriteTime.dwHighDateTime;

                //�ҵ���һ���ļ�
                if (FILE_ATTRIBUTE_DIRECTORY != (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    sprintf(szFilePath, "%s\\%s", m_szFileDir, FindFileData.cFileName);

                    if(this->OpenReadFile(szFilePath))
                    {
                        return true;
                    }
                }

                //////////////////////////////////////////////////////////////////////////

                //��������һ���ļ�
                while (FindNextFileA(hFind, &FindFileData) != 0) 
                {
                    if (FILE_ATTRIBUTE_DIRECTORY != (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    {
                        sprintf(szFilePath, "%s\\%s", m_szFileDir, FindFileData.cFileName);

                        if(this->OpenReadFile(szFilePath))
                        {
                            FindClose(hFind);

                            hFind = INVALID_HANDLE_VALUE;

                            return true;
                        }
                    }
                }
            }

            FindClose(hFind);

            hFind = INVALID_HANDLE_VALUE;
        }

        return false;
    }

    bool CSlowReadFileQueueImp::OpenReadFile(PCHAR lpFilePath)
    {
        if (!lpFilePath)
        {
            return false;
        }

        //��֤���ļ��Ƿ�ɶ�
        HANDLE hFile = CreateFileA(lpFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (INVALID_HANDLE_VALUE == hFile)
        {
            //�򲻿���ֻ�������ڱ������ռ��д���ļ������������һ��
            return false;
        }

        //��������֤�ļ��Ƿ�Ϊ��Ч�����������Ч�ļ�����ɾ��(��Ϊ���ļ��в�Ӧ�ô��������Ƿ��ļ�)

        TFileHead aTFileHead = {0};

        DWORD dwReadBytes = 0;

        if (!ReadFile(hFile, &aTFileHead, sizeof(TFileHead), &dwReadBytes, NULL))
        {
            CloseHandle(hFile);

            DeleteFileA(lpFilePath);

            return false;
        }

        if (dwReadBytes != sizeof(TFileHead))
        {
            CloseHandle(hFile);

            DeleteFileA(lpFilePath);

            return false;
        }

        //�Ƚ���֤����,�������Ϊ�����ݣ�����Ч���ݣ���Ҳɾ��
        if (0 != memcmp(aTFileHead.szName, m_szKeyName, 64)
            || 0 == aTFileHead.nBlockSize)
        {
            CloseHandle(hFile);

            DeleteFileA(lpFilePath);

            return false;
        }

        m_WaitFreeDataIndexMap.clear();

        m_Read_BlockList.clear();

        //��ȡ���п��Զ�ȡ�����ݿ���Ϣ

        TBlockHead aTBlockHead = {0};

        while (ReadFile(hFile, &aTBlockHead, sizeof(TBlockHead), &dwReadBytes, NULL))
        {
            if (sizeof(TBlockHead) != dwReadBytes)
            {
                break;
            }

            //����Ѿ�Ϊȷ�ϵ����ݣ�������
            DWORD dwValidDataIndex = 0;

            dwValidDataIndex = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

            if (SYSBASE_SRFQ_BLOCK_VALID_USE == aTBlockHead.btValid)
            {
                //����ȡ����Ч����ʱ����������
                m_Read_BlockList.push_back(dwValidDataIndex - sizeof(TBlockHead));
            }

            //�Ѿ��޷���ȡ���κ�����ʱ����ɾ�����ļ�(����ط����ܲ���)
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, aTBlockHead.nDataSize, NULL, FILE_CURRENT))
            {
                CloseHandle(hFile);

                DeleteFileA(lpFilePath);

                return false;
            }
        }

        //û���ܶ�ȡ�����ݣ���ɾ��
        if (0 == m_Read_BlockList.size())
        {
            CloseHandle(hFile);

            DeleteFileA(lpFilePath);

            return false;
        }

        m_nNeedConfirmBlockCount = (UINT32)m_Read_BlockList.size();

        m_nHasConfirmBlockCount = 0;

        m_Read_TFileHead = aTFileHead;

        //������Ч
        m_hReadFile = hFile;

        sprintf(m_szReadFilePath, lpFilePath);

        return true;
    }

	//////////////////////////////////////////////////////////////////////////
	//CSlowReadFileQueue

	CSlowReadFileQueue::CSlowReadFileQueue()
	{
		m_pImp = new(std::nothrow) CSlowReadFileQueueImp();
	}

	CSlowReadFileQueue::~CSlowReadFileQueue()
	{
		if (!m_pImp)
		{
			return;
		}

		CSlowReadFileQueueImp* pCSlowReadFileQueueImp = (CSlowReadFileQueueImp*)m_pImp;

		delete pCSlowReadFileQueueImp;

		m_pImp = NULL;
	}

	CSlowReadFileQueue::ERROR_CODE CSlowReadFileQueue::Init(const char* lpFileDir, const char* lpName, UINT32 nBlockSize)
	{
		if (!m_pImp)
		{
			return ERROR_CODE_SYSTEM;
		}

		CSlowReadFileQueueImp* pCSlowReadFileQueueImp = (CSlowReadFileQueueImp*)m_pImp;

		return pCSlowReadFileQueueImp->Init(lpFileDir, lpName, nBlockSize);
	}

	CSlowReadFileQueue::ERROR_CODE CSlowReadFileQueue::GetData(PCHAR pBuffer, UINT32 nMaxBufferSize, UINT32& nDataSize, UINT32& nDataIndex)
	{
		if (!m_pImp)
		{
			return ERROR_CODE_SYSTEM;
		}

		CSlowReadFileQueueImp* pCSlowReadFileQueueImp = (CSlowReadFileQueueImp*)m_pImp;

		return pCSlowReadFileQueueImp->GetData(pBuffer, nMaxBufferSize, nDataSize, nDataIndex);
	}

	CSlowReadFileQueue::ERROR_CODE CSlowReadFileQueue::FreeData(UINT32 nDataIndex)
	{
		if (!m_pImp)
		{
			return ERROR_CODE_SYSTEM;
		}

		CSlowReadFileQueueImp* pCSlowReadFileQueueImp = (CSlowReadFileQueueImp*)m_pImp;

		return pCSlowReadFileQueueImp->FreeData(nDataIndex);
	}
}