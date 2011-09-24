/**
* @file httpresponse.h
* @brief Реализация работы простейшего HTTP сервера
* @author Kharkunov Eugene
* @date 16.09.2011
*/
#include <QDate>
#include <QFile>
#include "config.h"
#include "httpresponse.h"
#include "httprequest.h"
#include "httpdefs.h"

QHash<int, QString> STATUS_CODE;
QHash<QString, QString> format2MIME;

HttpResponse::HttpResponse(QString name, QObject *parent) :
    QObject(parent),
    serverName(name)
{
    //1xx: Информационные
    //    ADD_CODE(100, "Continue");
    //    ADD_CODE(101, "Switching protocols");
    //    ADD_CODE(102, "Proccessing");
    //2xx: Успешно
    ADD_CODE(200, "200 OK");
    ADD_CODE(201, "201 Created");
    ADD_CODE(202, "202 Accepted");
    //    ADD_CODE(203, "203 Non-Authoritative Information");
    ADD_CODE(204, "204 No Content");
    //    ADD_CODE(205, "Reset Content");
    //    ADD_CODE(206, "Partial Content");
    //    ADD_CODE(207, "Multi-Status");
    //    ADD_CODE(226, "IM Used");
    //3xx: Перенаправление
    ADD_CODE(300, "300 Multiple Choices");
    ADD_CODE(301, "301 Moved Permanently");
    ADD_CODE(302, "302 Found");
    //    ADD_CODE(303, "See Other");
    ADD_CODE(304, "304 Not Modified");
    //    ADD_CODE(305, "Use Proxy");
    //    ADD_CODE(307, "Temporary Redirect");
    //4xx: Ошибка клиента
    ADD_CODE(400, "400 Bad Request");
    ADD_CODE(401, "401 Unauthorized");
    //    ADD_CODE(402, "Payment Required");
    ADD_CODE(403, "403 Forbidden");
    ADD_CODE(404, "404 Not Found");
    //    ADD_CODE(405, "Method Not Allowed");
    //    ADD_CODE(406, "Not Acceptable");
    //    ADD_CODE(407, "Proxy Authentication Required");
    //    ADD_CODE(408, "Request Timeout");
    //    ADD_CODE(409, "Conflict");
    //    ADD_CODE(410, "Gone");
    //    ADD_CODE(411, "Length Required");
    //    ADD_CODE(412, "Precondition Failed");
    //    ADD_CODE(413, "Request Entity Too Large");
    //    ADD_CODE(414, "Request-URI Too Long");
    //    ADD_CODE(415, "Unsupported Media Type");
    //    ADD_CODE(416, "Requested Range Not Satisfiable");
    //    ADD_CODE(417, "Expectation Failed");
    //    ADD_CODE(422, "Unproccessable Entity");
    //    ADD_CODE(423, "Locked");
    //    ADD_CODE(424, "Failed Dependency");
    //    ADD_CODE(425, "Unordered Collection");
    //    ADD_CODE(426, "Upgrade Required");
    //    ADD_CODE(449, "Retry With");
    //    ADD_CODE(456, "Unrecoverable Error");
    //5xx: Ошибка сервера
    ADD_CODE(500, "500 Internal Server Error");
    ADD_CODE(501, "501 Not Implemented");
    ADD_CODE(502, "502 Bad Gateway");
    ADD_CODE(503, "503 Service Unavailable");
    //    ADD_CODE(504, "Gateway Timeout");
    //    ADD_CODE(505, "HTTP Version Not Supported");
    //    ADD_CODE(506, "Variant Also Negatiates");
    //    ADD_CODE(507, "Insufficient Storage");
    //    ADD_CODE(509, "Bandwidth Limit Exceeded");
    //    ADD_CODE(510, "Not Extended");

    //инициализация MIME форматов
    initFormat();
}

HttpResponse::~HttpResponse() {}

void HttpResponse::prepareResponse(const HttpRequest &request, QByteArray &arr) {
    bool found = false;
    _mResponseStr = "HTTP/%1 %2\r\n"
            "Date: %3\r\n"
            "Server: %4\r\n"
            "%5"//дополнительные заголовки, в случае отсутствия ""
            "Content-Type: %6\r\n"
            "Content-Length: %7\r\n"
            "Connection: keep-alive\r\n"
            "\r\n";
    QString version, status, date, server, type, length, additionalHeaders;
    version = "1.1";
    date = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
    server = serverName;
    switch (request.method()) {
    case GET  : case HEAD : {
        QString path = request.path();
        int index = path.lastIndexOf('.');
        QString ext = path.mid(index + 1, path.size() - index);
        type = format2MIME.value(ext);
        if (type.isEmpty()) type = "application/octet-stream";

        if (type.contains("text")) {
            additionalHeaders.append("Content-Language: ru\r\n");
            type.append("; charset=utf-8");
        }
        QString filePath = Config::rootDirectory.absolutePath() + request.path();
        arr = prepareData(filePath, found);
        length = QString::number(arr.size());

        if (found) status = STATUS_CODE.value(200);
        else status = STATUS_CODE.value(404);
        break;
    }
    case POST : {
        //! TODO: если не совпадут данные, то 401
        break;
    }
    case UNDEFINED : {
        status = STATUS_CODE.value(400);
    }
    }
    _mResponseStr = _mResponseStr.arg(version)
            .arg(status)
            .arg(date)
            .arg(server)
            .arg(additionalHeaders)
            .arg(type)
            .arg(length);
}

QByteArray HttpResponse::prepareData(const QString filePath, bool &found) {
    QByteArray data;
    QFile file (filePath);
    found = file.exists();
    if (found) {
        if(file.open(QIODevice::ReadOnly))
            data = file.readAll();
    }
    else {
        QString errorString = "<html><head><title>MyServer ver. 0.1 - Error report</title>"
                "<style><!--H1 {font-family:Tahoma,Arial,sans-serif;"
                "color:white;background-color:#525D76;font-size:22px;} "
                "H2 {font-family:Tahoma,Arial,sans-serif;color:white;"
                "background-color:#525D76;font-size:16px;} "
                "H3 {font-family:Tahoma,Arial,sans-serif;color:white;"
                "background-color:#525D76;font-size:14px;} "
                "BODY {font-family:Tahoma,Arial,sans-serif;color:black;background-color:white;} "
                "B {font-family:Tahoma,Arial,sans-serif;color:white;background-color:#525D76;} "
                "P {font-family:Tahoma,Arial,sans-serif;background:white;color:black;font-size:12px;}"
                "A {color : black;}A.name {color : black;}HR {color : #525D76;}--></style>"
                "</head><body><h1>HTTP Status 404 - %1</h1>"
                "<p><b>type</b> Status report</p><p><b>message</b>"
                "<u>%1</u></p><p><b>description</b> "
                "<u>The requested resource (%1) is not available.</u></p>"
                "<h3>MyServer ver. 0.1</h3></body></html>";
        errorString = errorString.arg(filePath);
        data.append(errorString);
    }
    return data.isEmpty() ? QByteArray() : data;
}

QString HttpResponse::responseStr() const {
    return _mResponseStr;
}
