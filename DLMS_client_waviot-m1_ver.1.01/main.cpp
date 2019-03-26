#include "mainwindow.h"
#include <QApplication>
#include <Logger/Logger.h>

;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QVariant>("QVariant");
//    initializeLogger("DLMS_client_waviot.log", 5, true);
    MainWindow w;
    w.show();

    return a.exec();
}
