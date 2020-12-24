#pragma once

#include "SysBase.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //CSystemTime

    class CSystemTime
    {
    public:
		struct WindowsPatchResult
		{
			INT64 Time;
			INT64 Ret;
		};
        static UINT64 GetTickCount();

        //��ȡ����ʱ��
        static INT64 GetStartTime();

        //��ȡ�ϴο���ʱ��
        static INT64 GetLastShutdownTime();

		//��ȡϵͳ��װʱ��
		static INT64 GetInstallTime();

		//��ȡ�ϴβ����İ�װʱ��
		static bool GetPatchInstallTime(WindowsPatchResult& result);

		//��ȡ�ϴβ����ļ��ʱ��
		static bool GetPatchDectectTime(WindowsPatchResult& result);

		//��ȡ�ϴβ���������ʱ��
		static bool GetPatchDownloadTime(WindowsPatchResult& result);

		//��ȡָ�����ȵ������
		static bool GetRandom(unsigned char* buf ,int iCount);
    private:

        CSystemTime();

        virtual ~CSystemTime();
    };
}
