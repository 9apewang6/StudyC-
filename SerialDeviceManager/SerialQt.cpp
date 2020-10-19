#include "SerialQt.h"

SerailQt::SerailQt()
{
    serialPort = new QSerialPort;
    QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(recvMsg()));

}

SerailQt::~SerailQt()
{
    delete serialPort;
    serialPort = nullptr;
}

bool SerailQt::Open(const SerialCommInfo& info)
{
    char szPort[15];
    sprintf(szPort, "COM%d", info.Comport);
    serialPort->setPortName(szPort);
    if (!serialPort->open(QIODevice::ReadWrite))
    {
        return false;
    }
    serialPort->setBaudRate(info.baudrate);
    if (info.databit == 8)
    {
        serialPort->setDataBits(QSerialPort::Data8);
    }
    else if (info.databit == 7)
    {
        serialPort->setDataBits(QSerialPort::Data7);

    }
    else if (info.databit == 6)
    {
        serialPort->setDataBits(QSerialPort::Data6);

    }

    if (info.stopbit == 1)
    {
        serialPort->setStopBits(QSerialPort::OneStop);
    }
    else if (info.stopbit == 2)
    {
        serialPort->setStopBits(QSerialPort::TwoStop);

    }

    if (info.parity == NONE)
    {
        serialPort->setParity(QSerialPort::NoParity);
    }
    else if (info.parity == EVEN)
    {
        serialPort->setParity(QSerialPort::EvenParity);
    }
    else if (info.parity == ODD)
    {
        serialPort->setParity(QSerialPort::OddParity);

    }
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    serialPort->setDataTerminalReady(info.DTR);
    return true;
}

void SerailQt::Close()
{
    serialPort->close();
}



int SerailQt::SendData(const QString& msg)
{
   return serialPort->write(QByteArray::fromHex(msg.toLatin1()));
}



void SerailQt::getMsg(QString& msg) const
{
    msg = m_msg;
}

void SerailQt::recvMsg()
{
    QByteArray msg = serialPort->readAll();
   
   // parseMsg(msg.toHex().data());
   // m_msg = msg.toHex().data();
    int size = msg.size();
    if(size>=10)m_msg = msg.data();
}

void SerailQt::parseMsg(const QString& msg)
{

}

void SerailQt::findFreePorts()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (int i = 0; i < ports.size(); ++i) {
        if (ports.at(i).isBusy()) {
            ports.removeAt(i);
            continue;
        }
      
    }
    if (!ports.size()) {
        QMessageBox::warning(NULL, "Tip", QStringLiteral("ÕÒ²»µ½¿ÕÏÐ´®¿Ú"));
        return;
    }
}
