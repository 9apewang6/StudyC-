#include "TestWizard.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWizard w;
    w.show();
    return a.exec();
}
