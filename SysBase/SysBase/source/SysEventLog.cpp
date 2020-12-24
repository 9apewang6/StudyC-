#include "../SysBase_Interface.h"

#pragma comment(lib, "Advapi32.lib")

#define SYS_EVENT_LOG_BUFFER_SIZE 1024 * 64

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////

    struct TEventLogID 
    {
        UINT16 nNoNeedToKnown;
        UINT16 nEventID;
    };

    class CSysEventLogImp
    {
    public:

        //////////////////////////////////////////////////////////////////////////66a

        CSysEventLogImp();

        virtual ~CSysEventLogImp();

        CSysEventLog::ERROR_CODE Open(const char* szSourceName);

        void Close();

        CSysEventLog::ERROR_CODE GetCount(UINT32& recordCount);

        CSysEventLog::ERROR_CODE Read(list<TSysEventLogInfo>& sysEventLogInfoList);

    private:

        HANDLE m_hEventLog;
    };

    //////////////////////////////////////////////////////////////////////////


    CSysEventLogImp::CSysEventLogImp()
    {
        m_hEventLog = NULL;
    }

    CSysEventLogImp::~CSysEventLogImp()
    {
        this->Close();
    }

    CSysEventLog::ERROR_CODE CSysEventLogImp::Open(const char* szSourceName)
    {
        if (!szSourceName)
        {
            return CSysEventLog::ERROR_CODE_PARAM;
        }

        if (m_hEventLog)
        {
            return CSysEventLog::ERROR_CODE_HAS_OPEN;
        }

        m_hEventLog = OpenEventLogA(NULL, szSourceName);      

        if (!m_hEventLog)
        {
            return CSysEventLog::ERROR_CODE_SYSTEM;
        }

        return CSysEventLog::ERROR_CODE_SUCCESS;
    }

    void CSysEventLogImp::Close()
    {
        if (!m_hEventLog)
        {
            return;
        }

        CloseEventLog(m_hEventLog);

        m_hEventLog = NULL;
    }

    CSysEventLog::ERROR_CODE CSysEventLogImp::GetCount(UINT32& recordCount)
    {
        if (!m_hEventLog)
        {
            return CSysEventLog::ERROR_CODE_NOT_OPEN;
        }

        DWORD dwThisRecord = 0;

        GetNumberOfEventLogRecords(m_hEventLog, &dwThisRecord);

        recordCount = dwThisRecord;

        return CSysEventLog::ERROR_CODE_SUCCESS;
    }

    CSysEventLog::ERROR_CODE CSysEventLogImp::Read(list<TSysEventLogInfo>& sysEventLogInfoList)
    {
        if (!m_hEventLog)
        {
            return CSysEventLog::ERROR_CODE_NOT_OPEN;
        }

        DWORD dwRead, dwNeeded, dwThisRecord = 0;
        PEVENTLOGRECORD pEventLogRecord = NULL; 
        char recvbuffer[SYS_EVENT_LOG_BUFFER_SIZE] = {0}; 

        pEventLogRecord = (PEVENTLOGRECORD)&recvbuffer; 

        while (ReadEventLogA(m_hEventLog,
            EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ,
            0,
            recvbuffer,
            SYS_EVENT_LOG_BUFFER_SIZE,
            &dwRead,
            &dwNeeded))
        {
            while (dwRead > 0) 
            {
                TSysEventLogInfo aTSysEventLogInfo = {0};

                TEventLogID* pTEventLogID = (TEventLogID*)&pEventLogRecord->EventID;
                aTSysEventLogInfo.nEventID = pTEventLogID->nEventID;
                aTSysEventLogInfo.nEventLevel = pEventLogRecord->EventType;
                aTSysEventLogInfo.nEventNumber = pEventLogRecord->RecordNumber;
                aTSysEventLogInfo.nEventCategory = pEventLogRecord->EventCategory;
                aTSysEventLogInfo.nTimeGenerated = pEventLogRecord->TimeGenerated;
                aTSysEventLogInfo.nTimeWritten = pEventLogRecord->TimeWritten;

                if (pEventLogRecord->UserSidOffset > 0 && pEventLogRecord->UserSidLength > 0)
                {
                    PSID pUserSID = (PSID)((PCHAR)pEventLogRecord + pEventLogRecord->UserSidOffset);

                    char szUserName[41] = {0};
                    DWORD dwNameSize = 41;
                    char szDomain[256] = {0};
                    DWORD dwDomainSize = 256;
                    SID_NAME_USE SNU;

                    if (LookupAccountSid(NULL, pUserSID, szUserName, &dwNameSize, szDomain, &dwDomainSize, &SNU))
                    {
                        aTSysEventLogInfo.strUserName = szUserName;
                    }
                }

                //SourceName
                WCHAR* pwzSourceNasme = (WCHAR*)((PCHAR)pEventLogRecord + sizeof(EVENTLOGRECORD));
                aTSysEventLogInfo.strSourceName = pwzSourceNasme;

                //////////////////////////////////////////////////////////////////////////
                /*  ����ȡ������Ϣ���߼�:
                    1.ͨ��ע����� "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\%s" 
                        ������ Application Ϊ OpenEventLog ��SourceName ������ȡ "EventMessageFile" ��ֵ����Ϣ(�� ParameterMessageFile ��ֵ)��
                        ����ܻ�ȡ���ַ���ֵ������Ϊ ĳ dll �ĵ�ַ�����ҿ���ͬʱ���ڶ����ַ���� ; �Ÿ�������
                    2.��ȡ���ĵ�ַ�����п��ܱ������ϵͳ������������Ҫͨ�� GetEnvironmentVariable ��ȡ��������
                        ��Ӧ��ʵ���ַ�����Ϣ��
                    3.���ʵ�ʵ�ַ����Ҫ���ظ�DLL��

                        HANDLE hModule = LoadLibraryExW(  
                            szDllPath,                  //ʵ�ʵ�ַ�ַ�����Ϣ
                            NULL,  
                            LOAD_LIBRARY_AS_DATAFILE); 
                        
                        //ͨ��EventID��ȡ��Ӧ�������ַ�����Ϣ���ַ����д��ڲ������� %1, %2 ... %n��
                        if (hModule)
                        {
                            WCHAR szEventDesc[30240] = {0};

                            if (0 == FormatMessageW(FORMAT_MESSAGE_FROM_HMODULE, 
                            hModule, 
                            pEventLogRecord->EventID,
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                            szEventDesc,
                            30240,
                            NULL))
                        {
 
                             ��õĲ������У�
                             WCHAR* pStrings = (LPWSTR) ((LPBYTE) pEventLogRecord + pEventLogRecord->StringOffset);
                             list<wstring> strValueList;    //��õĲ�����Ϣ

                             for (UINT16 nIndex = 0; nIndex < pEventLogRecord->NumStrings; ++nIndex)
                             {
                                int nLen = (int)wcslen(pStrings);

                                if (nLen > 0)
                                {
                                    strValueList.push_back(pStrings);
                                }
                                    
                                pStrings += nLen + 1;
                             }

                            //��ͨ�� FormatMessageW(FORMAT_MESSAGE_FROM_STRING, ...., ��������); ���ʵ������������
                        }
                    
                    4.ʵ�ʵ�������Ϣ��Ϊ UNICODE �ַ�
                 */
                //////////////////////////////////////////////////////////////////////////

                dwRead -= pEventLogRecord->Length; 

                sysEventLogInfoList.push_back(aTSysEventLogInfo);

                pEventLogRecord = (PEVENTLOGRECORD)((PCHAR)pEventLogRecord + pEventLogRecord->Length); 
            }
        }

        return CSysEventLog::ERROR_CODE_SUCCESS;
    }

    //////////////////////////////////////////////////////////////////////////
    //CSysEventLog

    CSysEventLog::CSysEventLog()
    {
        m_pImp = new(std::nothrow) CSysEventLogImp();
    }

    CSysEventLog::~CSysEventLog()
    {
        if (!m_pImp)
        {
            return;
        }

        CSysEventLogImp* pImp = (CSysEventLogImp*)m_pImp;

        delete pImp;

        m_pImp = NULL;
    }

    CSysEventLog::ERROR_CODE CSysEventLog::Open(const char* szSourceName)
    {
        if (!m_pImp)
        {
            return ERROR_CODE_SYSTEM;
        }

        CSysEventLogImp* pImp = (CSysEventLogImp*)m_pImp;

        return pImp->Open(szSourceName);
    }

    void CSysEventLog::Close()
    {
        if (!m_pImp)
        {
            return;
        }

        CSysEventLogImp* pImp = (CSysEventLogImp*)m_pImp;

        pImp->Close();
    }

    CSysEventLog::ERROR_CODE CSysEventLog::GetCount(UINT32& recordCount)
    {
        if (!m_pImp)
        {
            return ERROR_CODE_SYSTEM;
        }

        CSysEventLogImp* pImp = (CSysEventLogImp*)m_pImp;

        return pImp->GetCount(recordCount);
    }

    CSysEventLog::ERROR_CODE CSysEventLog::Read(list<TSysEventLogInfo>& sysEventLogInfoList)
    {
        if (!m_pImp)
        {
            return ERROR_CODE_SYSTEM;
        }

        CSysEventLogImp* pImp = (CSysEventLogImp*)m_pImp;

        return pImp->Read(sysEventLogInfoList);
    }
}