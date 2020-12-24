#include "test.h"
#include <QtWidgets/QApplication>
#include "newmodelguide_global.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//     test w;
//     w.show();
  //  freopen("log.txt","w",stdout);

    QWidget* wid = nullptr;
    wid = createNewModelGuideWidget();
    wid->show();
  /*  delete wid;*/
//     delete wid;
//     fclose(stdout);

    return a.exec();
}
