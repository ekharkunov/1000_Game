/**
* @file main.cpp
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Главный исполняемый файл программы
*/

#include <QtGui/QApplication>
#include "mainserver.h"
#include "config.h"
#include <QTranslator>

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
    Config::pathLogs = appDir;
    Config::pathLogs.cd("logs");
    Config::pathTranslations = appDir;
    Config::pathTranslations.cd("translations");
    Config::portForHttpServer = 9000;
    Config::portsForGameServers = QMap<QString, int>();

    QTranslator trans;
    trans.load(Config::pathTranslations.absolutePath() + "/lang_" + QLocale::system().name());
    a.installTranslator(&trans);

    MainServer *server = MainServer::getInstance();
    server->show();
    return a.exec();
}
