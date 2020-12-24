#pragma once

#include "SysBase.h"

#define MAX_SYSBASE_USER_NAME_SIZE 41
#define MAX_SYSBASE_USER_NAME_LEN 40

namespace SysBase
{
    //////////////////////////////////////////////////////////////////////////
    //һ����Ϣ

    struct TProcessNormal
    {
        UINT32  nProcessID;             //����ID
        UINT32  nParentProcessID;       //������ID
        UINT32  nThreadCount;           //�߳���
        INT32   nPriClassBase;          //�������ȼ�
        WCHAR   szExeFile[MAX_PATH];    //��������
    };

    //////////////////////////////////////////////////////////////////////////
    //�ڴ���Ϣ

    struct TProcessMemory
    {
        UINT32  nPageFaultCount;              //Number of page faults
        UINT64  nPeakWorkingSetSize;          //��ֵ�ڴ�ʹ��
        UINT64  nWorkingSetSize;              //��ǰ�ڴ�ʹ��
        UINT64  nQuotaPeakPagedPoolUsage;     //��ֵҳ�滺���
        UINT64  nQuotaPagedPoolUsage;         //��ǰҳ�滺���
        UINT64  nQuotaPeakNonPagedPoolUsage;  //��ֵ��ҳ�滺���
        UINT64  nQuotaNonPagedPoolUsage;      //��ǰ��ҳ�滺���
        UINT64  nPagefileUsage;               //��ǰ�����ڴ�ʹ��
        UINT64  nPeakPagefileUsage;           //��ֵ�����ڴ�ʹ��
    };

    //////////////////////////////////////////////////////////////////////////
    //IO���� 

    struct TProcessIOCounter
    {
        UINT64  nReadOperationCount;        //������
        UINT64  nWriteOperationCount;       //д����
        UINT64  nOtherOperationCount;       //������д����
        UINT64  nReadTransferCount;         //��-�ֽ���
        UINT64  nWriteTransferCount;        //д-�ֽ���
        UINT64  nOtherTransferCount;        //������д-�ֽ���
    };

    //////////////////////////////////////////////////////////////////////////
    //������Դ

    struct TProcessResource
    {
        UINT32  nHandleCount;               //�����
        UINT32  nGDICount;                  //GDI��
        UINT32  nUserObjectCount;           //�û�������
    };

    //////////////////////////////////////////////////////////////////////////
    //�߼���Ϣ
#define COMAND_MAX_PATH			1024
    struct TProcessAdvanced
    {
        UINT8   nPriority;                                  //���ȼ���0:������; 1:��; 2:���ڱ�׼; 3:��ͨ; 4:���ڱ�׼; 5:��; 6:��ߣ�
        bool    bIs64;                                      //�Ƿ�Ϊ64λ����
        UINT32  nSessionID;                                 //Terminal Services session ���ն˷���Ự��ţ�
        WCHAR   szImageFileName[MAX_PATH];                  //��ȡ���̵��ļ���ȫ�̣�����·����
		WCHAR   szCommandLine[COMAND_MAX_PATH];                  //��ȡ���̵��ļ���ȫ�̣�����·����
        WCHAR   szUserName[MAX_SYSBASE_USER_NAME_SIZE];     //�û���
    };

    //////////////////////////////////////////////////////////////////////////
    //ʱ����Ϣ

    struct TProcessTime
    {
        INT64  nCreateTime;                 //���̴���ʱ��
        INT64  nExitTime;                   //�����˳�ʱ��
        INT64  nKernelTime;                 //���̺���ʱ��
        INT64  nUserTime;                   //�����û�ʱ��
    };

    //////////////////////////////////////////////////////////////////////////
    //������Ϣ

    struct TProcessInfo 
    {
        TProcessNormal aNormal;

        TProcessMemory aMemory;

        TProcessIOCounter aIOCounter;

        TProcessResource aResource;

        TProcessAdvanced aAdvanced;

        TProcessTime aTime;
    };
}
