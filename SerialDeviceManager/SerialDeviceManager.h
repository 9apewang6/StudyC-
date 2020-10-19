#pragma once
#include <string>
#include <vector>
#include <map>
#include <QString>
#include "serialdevicemanager_global.h"
#include "ISerialDevice.h"
#include "DialIndicator.h"
#include "SerialCommCfg.h"
class SERIALDEVICEMANAGER_EXPORT SerialDeviceManager
{
public:
 
    ~SerialDeviceManager();
    static SerialDeviceManager* instance()
    {
        static SerialDeviceManager sdm;
        return &sdm;
    }
    void initialize();
    void deInitialize();
    int enumDevice(std::vector<std::string>& labels);
    ISerialDevice* getDeviceByLabel(const std::string& labelname);
    //add
    //delete 
    int loadConfig(const std::string& file);
private:
    SerialDeviceManager();
    void saveConfig();


private:
    QString cfgFile;
    std::vector<std::string> m_labels;
    std::map<std::string, ISerialDevice*> m_devices;
    std::vector<SerialCommInfo> m_SerialInfo;
};
