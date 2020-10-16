#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include "PlcDeviceManage.h"

PlcDeviceManager::PlcDeviceManager()
{
    launchMITServer();
}

PlcDeviceManager::~PlcDeviceManager()
{
    delete mitserver;
    mitserver = nullptr;
}
// cfg ≈‰÷√Œƒº˛ 
// label_ip/sn_port_PLCType
int PlcDeviceManager::loadConfig(const std::string& file)
{
    m_plcInfo.clear();
    m_labels.clear();
    cfgFile = QString::fromStdString(file);
    QFile js(cfgFile);
    js.open(QIODevice::ReadWrite);
    QString contex;
    if (js.isOpen())
    {
        contex = js.readAll();
    }
    else
    {
        return -1;
    }
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(contex.toUtf8(), &parseJsonErr);

    if (!(parseJsonErr.error == QJsonParseError::NoError))
    {
        return -1;
    }
    QJsonObject jsonobj = document.object();
    if (jsonobj.contains(QStringLiteral("PLC")))
    {
        QJsonValue jsonValuelist = jsonobj.value(QStringLiteral("PLC"));
        if (jsonValuelist.isArray())
        {
            QJsonArray array = jsonValuelist.toArray();
            for (int i = 0; i < array.size(); i++)
            {
                PlcCmnInfo info;

                QJsonValue  iconArray = array.at(i);
                QJsonObject icon = iconArray.toObject();
               info.label = icon["label"].toString().toStdString();
               info.plcType = icon["Type"].toString().toStdString();
                info.ip = icon["ip"].toString().toStdString();
               info.port = icon["port"].toInt();
                info.logicalStationNumber = icon["logicalstationNumber"].toInt();

                QJsonArray dataarray = icon["WatchedRegister"].toArray();
                for (int j = 0; j < dataarray.size(); j++)
                {
                    info.WatchedRegisters.push_back(dataarray[i].toInt());
                }
                //info.WatchedRegisters.insert(info.WatchedRegisters.begin(), dataarray.toVariantList().toVector().begin(), dataarray.toVariantList().toVector().end());
                if (info.plcType == "MitSub" || info.plcType == "Omron")
                {
                    m_plcInfo.push_back(info);
                    m_labels.push_back(info.label);
                }
            }
        }
    }


    js.close();
    return 0;

}

int PlcDeviceManager::enumDevice(std::vector<std::string>& labels)
{
    labels = m_labels;
    return 0;
}

IPlcDevice* PlcDeviceManager::getDeviceByLabel(const std::string& label)
{
    if (m_devices.find(label) != m_devices.end())
    {
        return m_devices[label];
    }
    return nullptr;
}

int PlcDeviceManager::Initialize()
{
   
    for (auto iter : m_plcInfo)
    {
        CreatePlcModule(iter.plcType,iter);
    }

    return 0;
}

void PlcDeviceManager::deInitialize()
{ 
    for (auto iter : m_devices)
    {
        iter.second->close();
        delete iter.second;
        iter.second = nullptr;
    }
    m_devices.clear();
}

void PlcDeviceManager::addDevice(PlcCmnInfo info)
{
    auto iter_plcinfo = m_plcInfo.begin();
    for (; iter_plcinfo != m_plcInfo.end();)
    {
        if (iter_plcinfo->label == info.label)
        {
            return;
        }
        else
        {
            ++iter_plcinfo;
        }
    }
    if (info.plcType == "MitSub" || info.plcType == "Omron")
    {
        m_plcInfo.push_back(info);
        m_labels.push_back(info.label);
        CreatePlcModule(info.plcType,info);
    }
    saveConfig();
}

void PlcDeviceManager::deleteDevice(const std::string& label)
{
    auto iter_plcinfo = m_plcInfo.begin();
    for (; iter_plcinfo != m_plcInfo.end();)
    {
        if (iter_plcinfo->label == label)
        {
            iter_plcinfo = m_plcInfo.erase(iter_plcinfo);
        }
        else
        {
            ++iter_plcinfo;
        }
    }

    auto iter_labels = m_labels.begin();
    for (; iter_labels != m_labels.end();)
    {
        if (*iter_labels == label)
        {
            iter_labels = m_labels.erase(iter_labels);
        }
        else
        {
            ++iter_labels;
        }
    }

    auto iter_device = m_devices.begin();
    for (; iter_device != m_devices.end();)
    {
        if (iter_device->first == label)
        {
            iter_device->second->close();
            delete iter_device->second;
            iter_device->second = nullptr;
            iter_device = m_devices.erase(iter_device);
        }
        else
        {
            ++iter_device;
        }

    }
    saveConfig();

}

void PlcDeviceManager::launchMITServer()
{
   /* QProcess::start()*/

    if(!mitserver)mitserver = new QProcess;
    mitserver->setCreateProcessArgumentsModifier([](QProcess::CreateProcessArguments *args)
    {
        args->startupInfo->wShowWindow = SW_HIDE;
        args->startupInfo->dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    });
    mitserver->start("G:\\Study\\Test1\\Win32\\Release\\MITACTServer.exe");
    QObject::connect(mitserver, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), [=]() {mitserver->start("G:\\Study\\Test1\\Win32\\Release\\MITACTServer.exe"); });

    //ShellExecute(0,"open","G:\\Study\\Test1\\Win32\\Release\\MITACTServer.exe","","",SW_HIDE);
}

void PlcDeviceManager::saveConfig()
{
    QJsonObject jsonObj;
    QJsonArray jsonArray;
    QJsonDocument doc;
    for (int i = 0; i < m_plcInfo.size(); i++)
    {
        QJsonObject itemobj;
        itemobj.insert("Type", QString::fromStdString(m_plcInfo[i].plcType));
        itemobj.insert("label", QString::fromStdString(m_plcInfo[i].label));
        itemobj.insert("ip", QString::fromStdString(m_plcInfo[i].ip));
        itemobj.insert("port",m_plcInfo[i].port);
        itemobj.insert("logicalstationNumber", m_plcInfo[i].logicalStationNumber);
        QJsonArray itemarr;
        for (auto iter : m_plcInfo[i].WatchedRegisters)
        {
            itemarr.append(iter);
        }
        itemobj.insert("WatchedRegister", itemarr);

        jsonArray.append(itemobj);

    }

    jsonObj.insert("PLC", jsonArray);
    doc.setObject(jsonObj);


    QFile setcfg(cfgFile);
    if (!setcfg.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        return;
    }
    setcfg.write(doc.toJson());
    setcfg.close();
}

void PlcDeviceManager::CreatePlcModule(const std::string& type,PlcCmnInfo info)
{
    if (type == "MitSub")
    {
        IPlcDevice* mit_plc = new MitSubPlc;
        mit_plc->setCfg(info);
        m_devices.insert(make_pair(info.label, mit_plc));
    }
    else if (type == "Omron")
    {

    }
}
