#pragma once

#include "SysBase.h"

namespace SysBase
{
    class CDump : public SysBase::CSingletonT<CDump>
    {
    public:

        friend class SysBase::CSingletonT<CDump>;

        //////////////////////////////////////////////////////////////////////////
        
        enum ERROR_CODE
        {
            ERROR_CODE_SUCCESS = 0,
            ERROR_CODE_PARAM,
            ERROR_CODE_SYSTEM,			//ϵͳ�������
            ERROR_CODE_HAS_INIT,	    //�����ѳ�ʼ��
        };

        //////////////////////////////////////////////////////////////////////////

        ERROR_CODE Init(const char* szDumpDir, const char* szAppName);

        virtual ~CDump();

    private:

        CDump();

        bool m_bInit;
    };
}
