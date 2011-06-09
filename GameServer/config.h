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
    //! Путь к директории, в которой находятся все используемые иконки в интерфейсе сервера
    static QDir pathIcons;

    //! Путь к директории, содержащей файлы описания стилей интерфейса (*.qss)
    static QDir pathStyles;

    //! Путь к корневой директории, в которой хранятся html-страницы
    static QDir rootDirectory;

    //! Путь к директории, в которой находятся базы данных всех доступных серверов
    static QDir pathDatabases;

    //! Порт, на котором запущен http сервер
    static int  portForHttpServer;

    //! Массив, в котором хранятся порты, на которых работают игровые серверы, ассоциированные с их названиями
    static QMap<QString, int> portsForGameServers;
};

#endif // CONFIG_H
