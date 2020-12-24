#pragma once

#include "SysBase.h"

namespace SysBase
{
    typedef list<string> VolumeNameList;

    struct TVolumeSpace
    {
        UINT64 nFreeBytesAvailable;     //��Ч�����ֽ�
        UINT64 nTotalNumberOfBytes;     //���ֽ�
        UINT64 nTotalNumberOfFreeBytes; //�ܿ����ֽ�
    };

    class CHWVolume
    {
    public:

        static void GetVolumeNameList(VolumeNameList& volumeNameList);

        static bool GetDiskNumber(const char* szVolumeName, UINT32& nDiskNumber);

        static bool GetVolumeSpace(const char* szVolumeName, TVolumeSpace& volumeSpace);

    private:

        CHWVolume();

        virtual ~CHWVolume();
    };

}