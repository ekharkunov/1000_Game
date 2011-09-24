/**
* @file httprequest.cpp
* @brief Файл содержит реализацию обработки клиентского запроса
* @author Kharkunov Eugene
* @date 16.09.2011
*/

#include "httprequest.h"
#include <QRegExp>
#include <QDebug>
#include <QStringList>

HttpRequest::HttpRequest(QString str, QObject *parent) :
    QObject(parent),
    _mRequestStr(str)
{
    QString method, url, full;
    QRegExp rx("([A-Z]+)\\s(\\w*|/*|.*)\\s(\\w+)/(\\d.\\d)\\r\\n");
    if (rx.indexIn(str) != -1) {
        full = rx.cap(0);
    method = rx.cap(1);
    url = rx.cap(2);
    _mProtocol = rx.cap(3);
    _mVersion = rx.cap(4).toDouble();
    }
    _mPath = url;
    if (method == "GET") _mMethod = GET;
    else if (method == "POST") _mMethod = POST;
    else if (method == "HEAD") _mMethod = HEAD;
    else _mMethod = UNDEFINED;
    if (_mProtocol != "HTTP") _mMethod = UNDEFINED;
    str = str.remove(full);
    QStringList list = str.split(QRegExp("\\r\\n"), QString::SkipEmptyParts);
    //! TODO: метод POST и данные
    QString st;
    foreach(st, list) {
        QRegExp reg("(.*):\\s(.*)");
        if (reg.indexIn(st) != 1) {
            QString field = reg.cap(1);
            QString value = reg.cap(2);
            addHeaderValue(field, value);
        }
        else qDebug()<<"fail\n";
    }
}

HttpRequest::~HttpRequest() {}

QString HttpRequest::url() const {
    return _mUrl;
}

Method HttpRequest::method() const{
    return _mMethod;
}

QString HttpRequest::path() const {
    return _mPath;
}

QString HttpRequest::protocol() const {
    return _mProtocol;
}

double HttpRequest::version() const {
    return _mVersion;
}

void HttpRequest::addHeaderValue(QString field, QString value) {
    headersField2Value[field] = value;
}

QString HttpRequest::getHeaderValue(const QString field) const {
    return headersField2Value.value(field);
}

QString HttpRequest::requestStr() const {
    return _mRequestStr;
}
