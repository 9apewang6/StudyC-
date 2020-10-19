#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonValue>
#include "SerialDeviceManager.h"

SerialDeviceManager::~SerialDeviceManager()
{

}

void SerialDeviceManager::initialize()
{
    ISerialDevice* test = new DialIndicator;
    SerialCommInfo info;
    info.baudrate = 9600;
    info.Comport = 4;
    info.databit = 8;
    info.stopbit = 1;
    info.parity = NONE;
    info.DTR = true;
    
    test->setCfg(info);
   
    m_devices["test"] = test;
}

void SerialDeviceManager::deInitialize()
{
    for (auto iter : m_devices)
    {
        iter.second->close();
        delete iter.second;
        iter.second = nullptr;
    }
   
    m_devices.clear();
}



int SerialDeviceManager::enumDevice(std::vector<std::string>& labels)
{
    labels = m_labels;
    return 0;
}

ISerialDevice* SerialDeviceManager::getDeviceByLabel(const std::string& labelname)
{
    return m_devices["test"];
   // return nullptr;
}

int SerialDeviceManager::loadConfig(const std::string& file)
{
    m_SerialInfo.clear();
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
        QJsonValue jsonValuelist = jsonobj.value(QStringLiteral("SERIALPORT"));
        if (jsonValuelist.isArray())
        {
            QJsonArray array = jsonValuelist.toArray();
            for (int i = 0; i < array.size(); i++)
            {
                SerialCommInfo info;

                QJsonValue  iconArray = array.at(i);
                QJsonObject icon = iconArray.toObject();
                info.bm_label = icon["label"].toString().toStdString();
                info.stype = icon["Type"].toString().toStdString();
                info.Comport = icon["ip"].toInt();
                info.baudrate = icon["port"].toInt();
                info.parity =ParityBit(icon["logicalstationNumber"].toInt());
                info.stopbit = icon["stopbit"].toInt();
                info.databit = icon["databit"].toInt();

              
                //info.WatchedRegisters.insert(info.WatchedRegisters.begin(), dataarray.toVariantList().toVector().begin(), dataarray.toVariantList().toVector().end());
                if (info.stype == "MitSub" || info.stype == "Omron")
                {
                    m_SerialInfo.push_back(info);
                    m_labels.push_back(info.bm_label);
                }
            }
        }
    }


    js.close();
    return 0;
}

SerialDeviceManager::SerialDeviceManager()
{
}

void SerialDeviceManager::saveConfig()
{

}
