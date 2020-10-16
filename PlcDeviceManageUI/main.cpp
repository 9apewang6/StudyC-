#include "PlcDeviceManageUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlcDeviceManageUI w;
    w.show();
    return a.exec();
}
