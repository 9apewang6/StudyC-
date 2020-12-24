#pragma once

#include "SysBase.h"

namespace SysBase
{
    class CFileBase
    {
    public:

        //����:�ļ����ļ����Ƿ����
        //����:
        //      const char* szPath IN ·��
        //����ֵ: �Ƿ����
        static bool IsExist(const char* szPath);

        //����:�ļ����ļ����Ƿ����
        //����:
        //      const char* szPath IN ·��
        //����ֵ: �Ƿ����
        static bool IsExist(const WCHAR* szPath);

        //����:�������ļ����ļ���
        //����:
        //      const char* szOldPath IN ��Ŀ¼��
        //      const char* szNewPath IN ��Ŀ¼��
        //����ֵ: �Ƿ�ɹ�
        static bool Rename(const char* szOldPath, const char* szNewPath);

        //����:�������ļ����ļ���
        //����:
        //      const char* szOldPath IN ��Ŀ¼��
        //      const char* szNewPath IN ��Ŀ¼��
        //����ֵ: �Ƿ�ɹ�
        static bool Rename(const WCHAR* szOldPath, const WCHAR* szNewPath);

    protected:
    private:
    };
}