#include "sqlback.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	sqlback w;
	w.show();
	return a.exec();
}
