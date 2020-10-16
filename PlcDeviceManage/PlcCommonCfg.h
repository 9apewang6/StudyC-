#ifndef _PLCCOMMONCFG_H_
#define _PLCCOMMONCFG_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>

typedef void(_stdcall *registChangeCallback)(std::string label, int registid, int type, void* context);
enum RegisterType
{
    MPART,
    DPART
};

struct PlcCmnInfo
{
    std::string label;
    std::string plcType;
    std::string ip;
    int port;
    int logicalStationNumber;
    std::vector<int> WatchedRegisters;
    PlcCmnInfo()
    {
        label = "";
        plcType = "";
        ip = "";
        port = 1;
        logicalStationNumber = 1;
        WatchedRegisters.clear();
    }

};

#endif //_PLCCOMMONCFG_H_