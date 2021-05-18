#include "View.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    View w(NULL);
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(3, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    w.setFormat(format);
    w.LoadData("data\FOURDIX-1.bin");
    w.show();
    return a.exec();*/

    QApplication a(argc, argv);
    View w;
    QSurfaceFormat format;
    QSurfaceFormat::setDefaultFormat(format);
    //glWidget->setFormat(format);

    w.setFormat(format);
    w.LoadData("1.bin");
    w.show();
    return a.exec();
   }