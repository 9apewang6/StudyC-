#include "FindOrgImage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FindOrgImage w;
	w.show();
	return a.exec();
}
