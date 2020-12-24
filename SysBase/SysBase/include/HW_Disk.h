#pragma once

#include "SysBase.h"

namespace SysBase
{
    struct TDiskPerforance
    {
        UINT64 nBytesRead;       //�ܶ��ֽ���
        UINT64 nBytesWritten;   //��д�ֽ���
        UINT64 nReadTime;       //���ܹ����ĵ�ʱ��
        UINT64 nWriteTime;      //д�ܹ����ĵ�ʱ��
        UINT64 nIdleTime;       //�ܿ���ʱ��
        UINT32 nReadCount;      //�ܶ�����
        UINT32 nWriteCount;     //��д����
        UINT32 nQueueDepth;     //������ȣ���ʱ��֪����;��
        UINT32 nSplitCount;     //IO���IO �ۼƼ�������ʱ��֪����;��
    };

    class CHWDisk
    {
    public:

        static void GetDiskNumberList(list<UINT32>& diskNumberList);

        static bool GetDiskSize(UINT32 diskNumber, UINT64& nDiskSize);

        static bool GetDiskPerformance(UINT32 diskNumber, TDiskPerforance& aTDiskPerforance);

    private:

        CHWDisk();

        virtual ~CHWDisk();
    };
}
