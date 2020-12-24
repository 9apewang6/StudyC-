#pragma once

#include "SysBase.h"
#include "ProcessInfo.h"

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //����CPUʹ����

    struct TProcessCpuUsage 
    {
        UINT8 nCpuUsage;        //����CPUʹ����
    };

    //////////////////////////////////////////////////////////////////////////
    //�߼�������Ϣ

    struct TProcessPerformance
    {
        TProcessNormal aNormal;

        TProcessMemory aMemory;

        TProcessIOCounter aIOCounter;

        TProcessResource aResource;

        TProcessAdvanced aAdvanced;

        TProcessTime aTime;

        TProcessCpuUsage aCpuUsage;
    };

    //KEY:����ID; VALUE:������Ϣ
    typedef map<UINT32, TProcessPerformance> ProcessPerformanceMap;

    //////////////////////////////////////////////////////////////////////////
    //ϵͳCPUʹ����

    struct TSystemCpuUsage 
    {
        UINT8 nSystemCpuUsage;
        UINT8 nSystemIdleCpuUsage;
    };

    //////////////////////////////////////////////////////////////////////////
    //ϵͳ��Դ��Ϣ

    struct TSystemResource
    {
        UINT64 nCommitTotal;            //ϵͳ�ύ�ֽ���
        UINT64 nCommitLimit;            //ϵͳ��ǰ���ύ������ֽ���
        UINT64 nCommitPeak;             //��ǰϵͳ���ύ������ֽ���
        UINT64 nPhysicalTotal;          //�����ڴ��ֽ�����
        UINT64 nPhysicalAvailable;      //�û����̿��õ������ڴ��ֽ���
        UINT64 nSystemCache;            //ϵͳϵͳ�����ڴ��ֽ���
        UINT64 nKernelTotal;            //ϵͳ���ĳ��ܹ��ֽ���
        UINT64 nKernelPaged;            //ϵͳ���ĳ��ѷ�ҳ���ֽ���
        UINT64 nKernelNonpaged;         //ϵͳ���ĳ�δ��ҳ���ֽ���
        UINT64 nPageSize;               //ϵͳÿҳ�Ĵ�С���ֽڣ�
        UINT32 nHandleCount;            //�����
        UINT32 nProcessCount;           //������
        UINT32 nThreadCount;            //�߳���
    };

    //////////////////////////////////////////////////////////////////////////
    //ϵͳ��Ϣ

    struct TSystemPerformance
    {
        TSystemResource aResource;

        TSystemCpuUsage aCupUsage;
    };
}
