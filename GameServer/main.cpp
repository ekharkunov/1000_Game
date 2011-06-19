#include <QtGui/QApplication>
#include "mainwindow.h"
#include "httpserver.h"
#include "thousandgameserver.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//#if _DEBUG
//Config::rootDirectory = QDir("");
//Config::pathIcons = QDir("");
//Config::pathStyles = QDir("");
//Config::pathDatabases = QDir("d:/Repository921702/GameServer/Databases");
//Config::portForHttpServer = 8080;
//Config::portsForGameServers = QMap<QString, int>();
//#else
////Config::rootDirectory = QApplication::applicationDirPath();

//Config::pathIcons = QDir("");
//Config::pathStyles = QDir("");
//Config::pathDatabases = QDir("d:/Repository921702/GameServer/Databases");
//Config::portForHttpServer = 8080;
//Config::portsForGameServers = QMap<QString, int>();
//#endif

    ThousandGameServer *ser = ThousandGameServer::getInstance();
    ser->startServer();
    return a.exec();
}
