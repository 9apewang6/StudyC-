#pragma once

#include "SysBase.h"

#define SYSBASE_LOG_FILE_MAX_SIZE 1024 * 1024 * 20      //20M

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //CLog:������ļ�����־��Ϣ��

    class CLog : public CObject
    {
    public:

		//////////////////////////////////////////////////////////////////////////
		//������

		enum ERROR_CODE
		{
			ERROR_CODE_SUCCESS = 0,
			ERROR_CODE_PARAM,
			ERROR_CODE_SYSTEM,
			ERROR_CODE_HAS_INIT,
		};

		//////////////////////////////////////////////////////////////////////////
		//��־��Ϣ�ȼ�

		enum LOG_LEVEL
		{
			LOG_LEVEL_NONE = 0,       //�������Ϣ
			LOG_LEVEL_ERROR = 1,      //������Ϣ
			LOG_LEVEL_WARNING = 2,    //������Ϣ
			LOG_LEVEL_INFO = 3,       //������Ϣ
			LOG_LEVEL_DEBUG = 4,      //������Ϣ
			LOG_LEVEL_SYSTEM = 5      //ϵͳ�ײ���Ϣ
		};

		//////////////////////////////////////////////////////////////////////////

        CLog();

		virtual ~CLog();

        //����:��ʼ��(ʹ�ø���ǰ�����ȵ���)
		//����:
        //      const char* pFilePath IN ��־�ļ�����·��
        //      TRACE_LEVEL eLevel IN ��־����ȼ�
        //      UINT32 nMaxFileSize IN ��־�ļ�����С
        //      bool bOutputDefault IN �Ƿ�Ĭ��������ڣ�ʱ�䣬�̱߳��
        //      bool bAutoLine IN �Ƿ�Ĭ�������������־ʵ���������ʱ�Զ�����
        //����ֵ��ERROR_CODE_SUCCESS Ϊ�ɹ��������ο� ERROR_CODE
        ERROR_CODE Init(
			const char* pFilePath, 
			LOG_LEVEL eLevel = LOG_LEVEL_DEBUG, 
			UINT32 nMaxFileSize = SYSBASE_LOG_FILE_MAX_SIZE, 
			bool bOutputDefault = true,
            bool bAutoLine = false);

		//����:д����־��Ϣ
		//����:
		//      TRACE_LEVEL eLevel IN ��־�ȼ�
		//       const char* szFormat IN ��ʽ���ַ���
		void Write(LOG_LEVEL eLevel, const char* szFormat, ...);

		//����:������־�ȼ�
		//����:
		//      TRACE_LEVEL eLevel IN ��־�ȼ�
		void SetLogLevel(LOG_LEVEL eLevel);

    private:

		void* m_pImp;
    };

    //////////////////////////////////////////////////////////////////////////
    //��־����

    bool LOG_INIT(
        int nLogKey,
        const char* pFilePath, 
        CLog::LOG_LEVEL eLevel = CLog::LOG_LEVEL_DEBUG, 
        UINT32 nMaxFileSize = SYSBASE_LOG_FILE_MAX_SIZE, 
        bool bOutputDefault = true,
        bool bAutoLine = false);

    void LOG_WRITE(int nLogKey, CLog::LOG_LEVEL eLevel, const char* szFormat, ...);

    void LOG_SET_LEVEL(int nLogKey, CLog::LOG_LEVEL eLevel);

    //////////////////////////////////////////////////////////////////////////
}
