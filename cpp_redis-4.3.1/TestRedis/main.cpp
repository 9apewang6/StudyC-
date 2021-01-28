#include "TestRedis.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestRedis w;
    w.show();
    return a.exec();
}
