#include <QtGui/QApplication>
#include "mainwindow.h"
#include "httpserver.h"
#include "thousandgameserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ThousandGameServer *ser = ThousandGameServer::getInstance();
    ser->startServer();
    return a.exec();
}
