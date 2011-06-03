#include <QtGui/QApplication>
#include "mainwindow.h"
#include "httpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpServer ser;
    ser.startServer();
    return a.exec();
}
