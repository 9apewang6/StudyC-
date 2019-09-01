#include "plc_monitor.h"
#include <QtWidgets/QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	plc_monitor w;
	w.show();

	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
	return a.exec();
}
