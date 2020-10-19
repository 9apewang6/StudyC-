#include "SerialDeviceTest.h"

SerialDeviceTest::SerialDeviceTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    init();
}

SerialDeviceTest::~SerialDeviceTest()
{
    m_manager->deInitialize();
}

void SerialDeviceTest::connect()
{
    if (m_device)
    {
        m_device->open();
    }
}

void SerialDeviceTest::disconnect()
{
    if (m_device)
    {
        m_device->close();
    }
}

void SerialDeviceTest::init()
{
    m_manager = SerialDeviceManager::instance();
    m_manager->initialize();
    m_device = m_manager->getDeviceByLabel("text");
   
}

void SerialDeviceTest::on_pbConnect_clicked()
{
    
    connect();
}

void SerialDeviceTest::on_pbDisconnect_clicked()
{
    disconnect();
}

void SerialDeviceTest::on_pbGetValue_clicked()
{
    float val;
    if (m_device)
    {
        val = m_device->readValue();
        ui.doubleSpinBox->setValue(val);
    }
}
