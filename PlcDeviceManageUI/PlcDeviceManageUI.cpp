#include "PlcDeviceManageUI.h"

PlcDeviceManageUI::PlcDeviceManageUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void PlcDeviceManageUI::Open()
{

}

void PlcDeviceManageUI::Close()
{

}

PlcDeviceManageUI::~PlcDeviceManageUI()
{
 if(plcmanager)plcmanager->deInitialize();
}

void PlcDeviceManageUI::on_pb_setwidth_clicked()
{
    int width = ui.spinBox->value();
  //  m_scan.sendwidth(width);
}

void PlcDeviceManageUI::on_pb_clearsegment_clicked()
{
    int height = ui.spinBox_2->value();
   // m_scan.sendClearMarker(height);
}

void PlcDeviceManageUI::sendmsg(QString content)
{

}

void PlcDeviceManageUI::init()
{
    plcmanager = PlcDeviceManager::instance();
    plcmanager->loadConfig("G:\\plcManage.json");
//     plcmanager->Initialize();
//     std::vector<std::string > labels;
//     plcmanager->enumDevice(labels);
// 
//     if(labels.size()>0)m_plcdevice = plcmanager->getDeviceByLabel(labels[0]);
}

void PlcDeviceManageUI::uninit()
{
    if (plcmanager)
    {
        plcmanager->deInitialize();
    }
}

void PlcDeviceManageUI::initTableWidgets()
{
    for (int i = 0; i < m_labels.size(); i++)
    {
        int rowcount = ui.tableWidget->rowCount();
        ui.tableWidget->insertRow(rowcount);
        ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m_labels[i])));
    }
}

void PlcDeviceManageUI::on_pushButton_clicked()
{
    QString cont = ui.lineEdit->text();
    //sendmsg(cont);
    init();
    int data;
    if (m_plcdevice)
    {
        m_plcdevice->open();
        m_plcdevice->readInt(RegisterType::DPART, 1001, data);
    }
    ui.spinBox_2->setValue(data);
   // if (plcmanager)plcmanager->saveConfig();
}

void PlcDeviceManageUI::on_pb_Init_clicked()
{
    init();
    if (plcmanager)
    {
        plcmanager->Initialize();
        plcmanager->enumDevice(m_labels);
        
        if (m_labels.size()>0)m_plcdevice = plcmanager->getDeviceByLabel(m_labels[0]);

    }
   
    initTableWidgets();
   
}

void PlcDeviceManageUI::on_pb_Uninit_clicked()
{
    uninit();
    ui.tableWidget->setRowCount(0);
}

void PlcDeviceManageUI::on_pb_GetDevice_clicked()
{
    int addr;
    addr = ui.spinBox_4->value();
    int data;
    if (ui.comboBox->currentText() == "M")
    {
        if(m_plcdevice)m_plcdevice->readInt(RegisterType::MPART, addr, data);
        ui.spinBox_5->setValue(data);

    }
    else
    {
        if (m_plcdevice)m_plcdevice->readInt(RegisterType::DPART, addr, data);
        ui.spinBox_5->setValue(data);
    }
}

void PlcDeviceManageUI::on_pb_SetDevice_clicked()
{
    int addr = ui.spinBox_6->value();
    int data = ui.spinBox_7->value();
    int res=-1;
    if (ui.comboBox_2->currentText() == "M")
    {
        if (m_plcdevice) res= m_plcdevice->writeInt(RegisterType::MPART, addr, data);
        ui.label->setText(QString::number(res));
    }
    else
    {
        if (m_plcdevice) res = m_plcdevice->writeInt(RegisterType::DPART, addr, data);
        ui.label->setText(QString::number(res));

    }
}

void PlcDeviceManageUI::on_pb_add_clicked()
{
    QString newtype = ui.lineEdit->text();
    PlcCmnInfo info;
    info.label = newtype.toStdString();
    info.plcType = "MitSub";
    info.logicalStationNumber = 3;
    if (plcmanager)
    {
        plcmanager->addDevice(info);

        for (auto iter : m_labels)
        {
            if (iter == info.label)
            {
                return;
            }
        }
        m_labels.push_back(info.label);
        int rowcount = ui.tableWidget->rowCount();
        ui.tableWidget->insertRow(rowcount);
        ui.tableWidget->setItem(rowcount, 0, new QTableWidgetItem(QString::fromStdString(m_labels[rowcount])));
    }

}

void PlcDeviceManageUI::on_pb_delete_clicked()
{
    QString deltype = ui.lineEdit_3->text();
    if (plcmanager)
    {
       
        plcmanager->deleteDevice(deltype.toStdString());
    }
}

void PlcDeviceManageUI::on_pb_Getsegment_clicked()
{
    int segment;
    //m_scan.getSegment(segment);
}

void PlcDeviceManageUI::on_pb_open_clicked()
{
 //   m_scan.Open();
    if (m_plcdevice)
    {
        m_plcdevice->open();
   }
}

void PlcDeviceManageUI::on_pb_close_clicked()
{
 //   m_scan.Close();
    if (m_plcdevice)
    {
        m_plcdevice->close();
    }
}
