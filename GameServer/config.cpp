/**
* @file config.cpp
* @brief
* @author Kharkunov Eugene
* @date 2.06.2011
*/
#include "config.h"

QDir Config::rootDirectory = QDir("");
QDir Config::pathIcons = QDir("");
QDir Config::pathStyles = QDir("");
QDir Config::pathDatabases = QDir("d:/Repository921702/GameServer/Databases");
int Config::portForHttpServer = 8080;
QMap<QString, int> Config::portsForGameServers = QMap<QString, int>();
