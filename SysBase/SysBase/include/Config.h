#pragma once

#include <map>

#include "SysBase.h"

using namespace std;

//ע����ַ���󳤶�
#define REG_SZ_MAX_LENGTH 256

namespace SysBase
{
	//////////////////////////////////////////////////////////////////////////
	//CIniConfig ������profile����INI�ļ���ʽ���ļ��ж�ȡ�򱣴�������Ϣ

    class CIniConfig 
    {
    public:
        
        CIniConfig();

        ~CIniConfig();

        //����:���캯��
        //����:
        //      const char* pFilePath IN �ļ���
        //      bool bExist IN �Ƿ��ж��ļ�����
        //����ֵ��true�ɹ���false ʧ�ܣ��� bExist == false ʱ���ܻ᷵��true
        bool Load(const char* pFilePath, bool bExist = false);

        //����:��ȡ����ֵ
        //����:
        //      const char* pSection IN ����ģ�������
        //      const char* pKey IN ���ü�
        //      char* pValue OUT ����ֵ(�ַ����Ĵ�С����Ӧ��Ϊ sizeof(TCHAR)*  1024)
        //      UINT32 nValueSize IN lpValue ��������С
        //      char* pDefaultValue IN �����������Ϣ��lpValue ����Ĭ��ֵ����
        //����ֵ: ��ȡ���ַ������ȣ����Ȳ���������NULL��
        UINT32 GetString(const char* pSection, const char* pKey, char* pValue, 
			UINT32 nValueSize, const char* pDefaultValue = "");

        //����:��������ֵ
        //����:
        //      const char* pSection IN ����ģ�������
        //      const char* pKey IN ���ý�
        //      const char* pValue IN ����ֵ
        //����ֵ: �����Ƿ�ɹ�
        bool SetString(const char* pSection, const char* pKey, const char* pValue);
        
        //����:��ȡ��������ֵ
        //����:
        //      const char* pSection IN ����ģ�������
        //      const char* pKey IN ���ý�
        //      INT32 nDefault IN Ĭ��ֵ
        //����ֵ: ��������ֵ
        UINT32 GetInt(const char* pSection, const char* pKey, INT32 nDefault);

        //����:������������ֵ
        //����:
        //      const char* pSection IN ����ģ�������
        //      const char* pKey IN ���ý�
        //      INT32 nValue IN Ĭ��ֵ
        //����ֵ: ��������ֵ
        bool SetInt(const char* pSection, const char* pKey, INT32 nValue);

        const char* GetFilePath(); 

    private:

        char m_szFilePath[MAX_PATH];
    };
}
