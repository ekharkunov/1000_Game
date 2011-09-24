/**
* @file httpdefs.h
* @brief Файл с основными типами, которые используются при построении HTTP серверов
* @author Kharkunov Eugene
* @date 16.09.2011
*/

#ifndef HTTPDEFS_H
#define HTTPDEFS_H

#include <QHash>

/**
* @enum Method
* @brief Описывает методы HTTP запросов
*/
enum Method {
    GET = 0,
    POST,
    HEAD,
    UNDEFINED = 128
};

//! Соответствие форматов файлов их MIME типам
extern QHash<QString, QString> format2MIME;

/**
* @fn initFormat
* @brief Функция инициализации поддерживаемых MIME типов
*/
static void initFormat() {
    //text
    format2MIME["css"] = "text/css";
    format2MIME["html"] = "text/html";
    format2MIME["htm"] = "text/html";
    format2MIME["txt"] = "text/plain";
    format2MIME["rtx"] = "text/richtext";
    format2MIME["rtf"] = "text/rtf";
    //images
    format2MIME["png"] = "image/png";
    format2MIME["bmp"] = "image/bmp";
    format2MIME["gif"] = "image/gif";
    format2MIME["jpeg"] = "image/jpeg";
    format2MIME["jpg"] = "image/jpeg";
    format2MIME["jpe"] = "image/jpeg";
    format2MIME["svg"] = "image/svg+xml";
    format2MIME["tiff"] = "image/tiff";
    format2MIME["tif"] = "image/tiff";
    format2MIME["djvu"] = "image/vnd.djvu";
    format2MIME["djv"] = "image/vnd.djvu";
    //application
    format2MIME["doc"] = "application/msword";
    format2MIME["bin"] = "application/octet-stream";
    format2MIME["exe"] = "application/octet-stream";
    format2MIME["ogg"] = "application/ogg";
    format2MIME["pdf"] = "application/pdf";
    format2MIME["xls"] = "application/vnd.ms-excel";
    format2MIME["ppt"] = "application/vnd.ms-powerpoint";
    format2MIME["js"] = "application/x-javascript";
    format2MIME["latex"] = "application/x-latex";
    format2MIME["sh"] = "application/x-sh";
    format2MIME["swf"] = "application/x-shockwave-flash";
    format2MIME["tar"] = "application/x-tar";
    format2MIME["zip"] = "application/zip";

}

#endif // HTTPDEFS_H
