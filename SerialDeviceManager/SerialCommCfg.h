#ifndef _SERIALCOMMCFG_H_
#define _SERIALCOMMCFG_H_
#include <string>
#include <vector>
#include <map>
#include <iostream>
enum ParityBit
{
    NONE,
    ODD,
    EVEN
};
struct SerialCommInfo
{
    std::string bm_label;
    int Comport;
    std::string stype;

    int baudrate;
    int databit;
    ParityBit parity;
    int stopbit;
    bool DTR;

    SerialCommInfo()
    {
        bm_label = "";
        Comport = 1;
        stype = "";
        baudrate = 9600;
        databit = 8;
        parity = NONE;
        stopbit = 1;
        DTR = false;
    }


};


typedef void(_stdcall *SerialData_CallBack)(std::string data,void* context);
const char DataSeperator1 = '+';
const char DataSeperator2 = '-';
const char Seperator = ' ';
#endif //_SERIALCOMMCFG_H_