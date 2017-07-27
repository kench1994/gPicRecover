#include "picrecover.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PicRecover w;
    w.show();

    return a.exec();
}
