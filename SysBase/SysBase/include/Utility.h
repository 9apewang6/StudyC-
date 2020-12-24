#pragma once

#include "SysBase.h"

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//CStringBuilder �ַ���������(ANSII)

	class CStringBuilderA;
	class CStringBuilderW;

#ifndef _UNICODE
	typedef CStringBuilderA CStringBuilder;
#else
	typedef CStringBuilderW CStringBuilder;
#endif

    //////////////////////////////////////////////////////////////////////////
    //CStringBuilderA

    class CStringBuilderA : public SysBase::CObject
    {
    public:
        CStringBuilderA(void);
        CStringBuilderA(const char* szSource);
        CStringBuilderA(const CStringBuilderA& strBuilder);

        ~CStringBuilderA(void);

        void Append(const char* szSource);

        char* GetString(char* outStr);

        INT64 GetStrLength();

        void Clear();

    private:

        void Build(const char* szSource);
        void FreeStr();

        void* m_vsHead;
        void* m_vsEnd;

        INT64 m_nLength;
    };
    
    //////////////////////////////////////////////////////////////////////////
    //CStringBuilderW
    
	class CStringBuilderW : public SysBase::CObject
	{
	public:
		CStringBuilderW(void);
		CStringBuilderW(const WCHAR* szSource);
		CStringBuilderW(const CStringBuilderW& strBuilder);

		~CStringBuilderW(void);

		void Append(const WCHAR* szSource);

		WCHAR* GetString(WCHAR* outStr);

		INT64 GetStrLength();

		void Clear();

	private:

		void Build(const WCHAR* szSource);
		void FreeStr();

		void* m_vsHead;
		void* m_vsEnd;

		INT64 m_nLength;
	};

    //////////////////////////////////////////////////////////////////////////
    //Convert ����ת�������ռ�

    class Convert
    {
    public:

        //����:��λ�ڵ�ǰ�ļ�ָ��
        //����:
        //      UINT32 nLow IN ��λ��DWORD
        //      UINT32 nHigh IN ��λ��DOWRD
        //����ֵ: ת���Ľ��
        static UINT64 ToUINT64(UINT32 nLow, UINT32 nHigh);


        //����:��λ�ڵ�ǰ�ļ�ָ��
        //����:
        //      UINT64 nInt64 IN ��Ҫת������
        //      DWORD* pDwHigh OUT ��λ��DOWRD,ΪNULLֵʱ�����ظ�λ
        //����ֵ: ��λ��DWORD
        static DWORD ToDWORD(UINT64 nInt64, DWORD* pDwHigh);

        static void LocalToUTF8(string strTextLocal, string& strTextUtf8);
    };

    //////////////////////////////////////////////////////////////////////////
    //CAppInfo Ӧ�ó�����Ϣ

    class CAppInfo
    {
    public:

		CAppInfo();

		virtual ~CAppInfo();

        //����:��ȡӦ�ó�����(��������·��)
        //����ֵ: Ӧ�ó�����(��������·��)
        PCHAR GetAppFilePath();

        //����:��ȡӦ�ó�����(����������·��)
        //����ֵ: Ӧ�ó�����
        PCHAR GetAppFileName();

        //����:��ȡӦ�ó�������Ŀ¼
        //����ֵ: Ӧ�ó�������Ŀ¼
        PCHAR GetAppDirectory();

	private:

		char m_szFilePath[MAX_PATH];

		char* m_pFileName;

		char m_szAppDir[MAX_PATH];
    };

    class CAppInfoW
    {
    public:

        CAppInfoW();

        virtual ~CAppInfoW();

        //����:��ȡӦ�ó�����(��������·��)
        //����ֵ: Ӧ�ó�����(��������·��)
        PWCHAR GetAppFilePath();

        //����:��ȡӦ�ó�����(����������·��)
        //����ֵ: Ӧ�ó�����
        PWCHAR GetAppFileName();

        //����:��ȡӦ�ó�������Ŀ¼
        //����ֵ: Ӧ�ó�������Ŀ¼
        PWCHAR GetAppDirectory();

    private:

        WCHAR m_szFilePathW[MAX_PATH];

        PWCHAR m_pFileNameW;

        WCHAR m_szAppDirW[MAX_PATH];
    };

    //////////////////////////////////////////////////////////////////////////
    //Ψһ��ʾ����

    class CGUID
    {
    public:

        CGUID();

        virtual ~CGUID();

        GUID Get();

        GUID ReCreate();

        string ToString();

        static string CreateToString();

    protected:
    private:

        GUID m_guid;
    };

    //////////////////////////////////////////////////////////////////////////
    //������
    
    class CMath
    {
    public:

        //��ȡָ�����ȵ������
        static bool GetRandom(unsigned char* buf ,int iCount);

    private:

        CMath();

        virtual ~CMath();
    };     
    
}
