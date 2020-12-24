#pragma once

#include "SysBase.h"

namespace SysBase
{
    struct THWMemoryInfo 
    {  
        UINT32 nMemoryLoad;                 //�ڴ�ʹ���ʣ�0~100��
        UINT64 nllTotalPhys;                //�ܹ��������ڴ������ֽڣ�
        UINT64 nllAvailPhys;                //���õ������ڴ������ֽڣ�
        UINT64 nllTotalPageFile;            //�ܹ����ύ�������ڴ������ֽڣ�
        UINT64 nllAvailPageFile;            //���õ��ύ�������ڴ���(�ֽ�)
        UINT64 nllTotalVirtual;             //�ܹ��������ڴ������ֽڣ�
        UINT64 nllAvailVirtual;             //���õ������ڴ������ֽڣ�
        UINT64 nllAvailExtendedVirtual;     //������õ������ڴ������ֽڣ�
    };

    class CHWMemory
    {
    public:

        static bool GetMemoryInfo(THWMemoryInfo& aMemoryInfo);

    protected:
    private:

        CHWMemory();

        virtual ~CHWMemory();
    };
}
