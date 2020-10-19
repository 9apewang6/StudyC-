#include "SerialDeviceTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialDeviceTest w;
    w.show();
    return a.exec();
}
