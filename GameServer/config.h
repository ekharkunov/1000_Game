/**
* @file config.h
* @brief Хранит параметры настройки главного сервера
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <QDir>
#include <QString>
#include <QMap>

/**
* @class Config
* @brief Базовый класс, хранящий настройки сервера:
*
*
*/

class  Config {
public:
    static QDir pathIcons;
    static QDir pathStyles;
    static QDir rootDirectory;
    static QDir pathDatabases;
    static int  portForHttpServer;
    static QMap<QString, int> portsForGameServers;
};

#endif // CONFIG_H
