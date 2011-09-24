/**
* @file httpconnection.cpp
* @brief Реализация класса соединения с HTTP сервером
* @author Kharkunov Eugene
* @date 16.09.2011
*/
#include <QTcpSocket>
#include "httpconnection.h"
#include "httprequest.h"
#include "httpresponse.h"

HttpConnection::HttpConnection(QTcpSocket *socket, QString name, QObject *parent) :
    QThread(parent),
    _mSocket(socket),
    _mServerName(name)
{
}

HttpConnection::~HttpConnection() {

    if (_mRequest) {
        delete _mRequest;
        _mRequest = 0;
    }

    if (_mResponse) {
        delete _mResponse;
        _mResponse = 0;
    }
}

void HttpConnection::run() {
//    Q_ASSERT_X(parser, "HttpConnection::run()", "Pointer to the http parser is null");
    int byteRead = 0;
    QByteArray arr, resp, data;
    //считываем данные от клиента
    for(;;) {
        byteRead = _mSocket->bytesAvailable();
        if (byteRead) arr.append(_mSocket->read(byteRead));
        else break;
    }
    //обрабатываем запрос и готовим ответ
    _mRequest = new HttpRequest(QString(arr));
    _mResponse = new HttpResponse(_mServerName);
    _mResponse->prepareResponse(*_mRequest, data);
    resp.append(_mResponse->responseStr());
    //отсылаем данные для передачи их клиенту
    emit(dataReady(resp));
    if (_mRequest->method() != HEAD) emit(dataReady(data));
    //высылаем сигнал об окончании обработки
    emit(transactionDone(_mRequest, _mResponse));
}

QTcpSocket* HttpConnection::socket() const {
    return _mSocket;
}
