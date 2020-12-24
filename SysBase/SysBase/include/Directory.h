#pragma once

#include "SysBase.h"

namespace SysBase
{
    class CDirectory
    {
    public:

        //����:����Ŀ¼
        //����:
        //      const char* szPathName IN ��Ҫ������Ŀ¼·��
        //      bool bRecurrence IN ��û�и�Ŀ¼��ʱ���Ƿ�ݹ鴴��
        //����ֵ: �Ƿ�ɹ�
        static bool Create(const char* szPathName, bool bRecurrence = false);

        //����:����Ŀ¼
        //����:
        //      const WCHAR* wzPathName IN ��Ҫ������Ŀ¼·��
        //      bool bRecurrence IN ��û�и�Ŀ¼��ʱ���Ƿ�ݹ鴴��
        //����ֵ: �Ƿ�ɹ�
        static bool Create(const WCHAR* wzPathName, bool bRecurrence = false);

        //����:���õ�ǰĿ¼
        //����:
        //      const char* szPathName IN Ŀ��Ŀ¼
        //����ֵ: �Ƿ�ΪĿ¼
        static bool IsDirectory(const char* szPathName);

        //����:���õ�ǰĿ¼
        //����:
        //      const WCHAR* wzPathName IN Ŀ��Ŀ¼
        //����ֵ: �Ƿ�ΪĿ¼
        static bool IsDirectory(const WCHAR* wzPathName);

        //����:ɾ��һ�����ڵ�Ŀ¼ : ����ܼ�һ���ص�����
        //����:
        //      const char* szPathName IN ��Ҫɾ����Ŀ¼·��
        //      bool bDeleteAllNode IN �Ƿ�ɾ����Ŀ¼�µ�������Ŀ¼�����ļ������Ϊfalse��ɾ����Ŀ¼��ҪΪ��Ŀ¼�ſ���ɾ��
        //����ֵ: �Ƿ�ɹ�
        static bool Delete(const char* szPathName, bool bDeleteAllNode = false);

        //����:ɾ��һ�����ڵ�Ŀ¼ : ����ܼ�һ���ص�����
        //����:
        //      const WCHAR* szPathName IN ��Ҫɾ����Ŀ¼·��
        //      bool bDeleteAllNode IN �Ƿ�ɾ����Ŀ¼�µ�������Ŀ¼�����ļ������Ϊfalse��ɾ����Ŀ¼��ҪΪ��Ŀ¼�ſ���ɾ��
        //����ֵ: �Ƿ�ɹ�
        static bool Delete(const WCHAR* szPathName, bool bDeleteAllNode = false);

        //����:����һ��Ŀ¼����һ��Ŀ¼ : ����ܼ�һ���ص�����
        //����:
        //      const char* szFromPath IN ԴĿ¼
        //      const char* szToPath IN Ŀ��Ŀ¼
        //����ֵ: �Ƿ�ɹ�
        static bool Copy(const char* szFromPath, const char* szToPath);

        //����:����һ��Ŀ¼����һ��Ŀ¼ : ����ܼ�һ���ص�����
        //����:
        //      const WCHAR* szFromPath IN ԴĿ¼
        //      const WCHAR* szToPath IN Ŀ��Ŀ¼
        //����ֵ: �Ƿ�ɹ�
        static bool Copy(const WCHAR* szFromPath, const WCHAR* szToPath);

        static bool Move(const char* szFromPath, const char* szToPath);

        static bool Move(const WCHAR* szFromPath, const WCHAR* szToPath);

        static bool GetOpenDirName(string& strPath, const char* szTitle = NULL);

        static bool GetOpenDirName(wstring& strPath, const WCHAR* wzTitle = NULL);

    private:

        CDirectory();

        virtual ~CDirectory();
    };
}
