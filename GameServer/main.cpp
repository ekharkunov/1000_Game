#include <QtGui/QApplication>
#include "mainserver.h"
#include "config.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir appDir;
#ifdef QT_DEBUG
    appDir = QDir("d:/Repository921702/GameServer");
#else
    appDir = QApplication::applicationDirPath();
#endif
    Config::rootDirectory = appDir;
    Config::rootDirectory.cd("html");
    Config::pathIcons = appDir;
    Config::pathIcons.cd("icons");
    Config::pathStyles = appDir;
    Config::pathStyles.cd("style");
    Config::pathDatabases = appDir;
    Config::pathDatabases.cd("Databases");
    Config::portForHttpServer = 8080;
    Config::portsForGameServers = QMap<QString, int>();

    MainServer *server = MainServer::getInstance();
    server->showMaximized();
//    ThousandGameServer *ser = ThousandGameServer::getInstance();
//    ser->startServer();
    return a.exec();
}
