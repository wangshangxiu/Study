#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString addr("10.10.10.181");
    qint16 port = 6001;
    w.Connect(addr, port);
    w.show();

    return a.exec();
}
