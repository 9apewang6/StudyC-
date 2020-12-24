#pragma once

#include "SysBase.h"

namespace SysBase
{
    struct TSysEventLogInfo 
    {
        UINT32 nEventNumber;        //�¼����
        UINT16 nEventLevel;         //�¼����� 0:Error; 1:Warning; 2:Info; 3:Success Audit; 4:Failure Audit
        UINT16 nEventID;            //�¼�ID
        //UINT8 nEventSeverity;       //�¼����ؼ��� 0:�ɹ�;1:��Ϣ;2:����;3:����
        //UINT8 nEventCustomer;       //�ͻ�λ 0:System; 1:Customer;
        UINT16 nEventCategory;      //�¼����
        UINT64 nTimeGenerated;      //�¼��ύʱ�䣨UTC��
        UINT64 nTimeWritten;        //�¼���ϵͳ����д�뵽��־�е�ʱ�䣨UTC��
        string strUserName;         //�¼�����û�����Ϊϵͳ�����¼�ʱ���û�����Ϣ��
        wstring strSourceName;      //�¼�Դ
        //wstring strDesc;            //����
    };

    class CSysEventLog
    {
    public:

        //////////////////////////////////////////////////////////////////////////

        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM,
            ERROR_CODE_SYSTEM,
            ERROR_CODE_HAS_OPEN,
            ERROR_CODE_NOT_OPEN,
        };

        //////////////////////////////////////////////////////////////////////////66a

        CSysEventLog();

        virtual ~CSysEventLog();

        ERROR_CODE Open(const char* szSourceName);

        void Close();

        ERROR_CODE GetCount(UINT32& recordCount);

        ERROR_CODE Read(list<TSysEventLogInfo>& sysEventLogInfoList);

    private:

        void* m_pImp;
    };
}
