#include "MITACTServer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MITACTServer w;
    w.show();
    return a.exec();
}
