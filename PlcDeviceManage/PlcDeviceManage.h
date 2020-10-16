#pragma once
#include "IPlcDevice.h"
#include "MitsubPlc.h"
#include <string>
#include <vector>
#include "plcdevicemanage_global.h"

class PLCDEVICEMANAGE_EXPORT PlcDeviceManager
{
public:
    PlcDeviceManager();
    ~PlcDeviceManager();
    static PlcDeviceManager* instance()
    {
        static PlcDeviceManager m_plcmanager;
        return &m_plcmanager;
    }
    int loadConfig(const std::string& file);
    int enumDevice(std::vector<std::string>& labels);
    IPlcDevice* getDeviceByLabel(const std::string& label);
    int Initialize();
    void deInitialize();

    void addDevice(PlcCmnInfo info);
    void deleteDevice(const std::string& label);
private:
    void launchMITServer();
    void saveConfig();
    void CreatePlcModule(const std::string& type,PlcCmnInfo info);
private:
    QString cfgFile;
    std::vector<std::string> m_labels;
    std::map<std::string, IPlcDevice*> m_devices;
    std::vector<PlcCmnInfo> m_plcInfo;
    QProcess *mitserver=nullptr;
};
