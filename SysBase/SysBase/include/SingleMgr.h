//////////////////////////////////////////////////////////////////////////
//���ļ��µ�������������Ҫ��ʼ���ſ���ʹ�õĺ����������DLL����������
//SOCKET��init������
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "SysBase.h"

using namespace std;

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //����ģ��
    template <typename T>
    class CSingletonT
    {
    public:
  
        virtual ~CSingletonT(){}

    protected:

        CSingletonT(){}

    public:

        static T& Instance()
        {
            static T instance;
            return instance;
        } 
    };

    //����������
    class CSingleMgr
    {
    public:
        
        //�ͷ��йܶ���
        ~CSingleMgr();

        //�����йܵĶ��� //����Ϊ�̳� IInitLoader��IDLLLoader �������ӿڵ������
        static void Add(CObject* pCObject);

    protected:

        CSingleMgr();

    private:

        list<CObject*>* m_pCObjectList;

        static CSingleMgr s_CSingleManagerInstance;
    };

    //��ʼ����������࣬��SOCKETʹ��ǰ��Ҫ�ȵ��ú���������Ӧ�İ汾������
    class IInitLoader : public CObject
    {
    public:
        
        //�ͷź���
        virtual ~IInitLoader(){};

        //��ʼ����Ҫ�Ĺ���
        virtual BOOL Init() = 0;

    protected:

    private:
    };

    //��̬���ӿ���س���
    class IDLLLoader : public CObject
    {
    public:

        //�������ͷż��ص�DLL
        virtual ~IDLLLoader(){};

        //����DLL
        virtual BOOL Load(LPCWSTR lpFileName) = 0;

    private:

        HMODULE m_hModule;
    };

     
}
