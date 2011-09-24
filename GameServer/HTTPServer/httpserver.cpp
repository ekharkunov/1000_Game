/**
* @file httpserver.cpp
* @brief Файл содержит в себе реализацию базовых функций HTTP сервера
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#include "httpserver.h"
#include "config.h"
#include "httpconnection.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "connectionmanager.h"
#include <QMessageBox>
#include <QFile>

HttpServer* HttpServer::_mInstance = 0;

HttpServer* HttpServer::getInstance() {
    return _mInstance;
}

HttpServer::HttpServer(int port, QObject *parent) :
    QTcpServer(parent),
    mPort(port),
    _mServerName("MyServer ver. 0.1")
{
    Q_ASSERT_X(!_mInstance, "HTTP Server", "Instance is already created!");
    _mInstance = this;
}

HttpServer::~HttpServer() {
}

bool HttpServer::startServer() {
    bool started = listen(QHostAddress::Any, mPort);
    if (!started) {
        emit(newMessage(tr("Unable to start HTTP server!:") + errorString()));
        currentState = NotRunning;
        close();
        return false;
    }
    else {
        currentState = Running;
        connect(this, SIGNAL(newConnection()), this, SLOT(addNewConnection()));
        emit(newMessage("Server started!"));
        return true;
    }
}

void HttpServer::addNewConnection() {
    QTcpSocket *newSocket = nextPendingConnection();
    HttpConnection *newConnection = new HttpConnection(newSocket, _mServerName);
    connect(newSocket, SIGNAL(disconnected()), newConnection, SLOT(deleteLater()));
    connect(newSocket, SIGNAL(readyRead()), newConnection, SIGNAL(readyRead()));
    connect(newConnection,SIGNAL(readyRead()), this, SLOT(readClientInformation()));
    connect(newConnection, SIGNAL(transactionDone(HttpRequest*,HttpResponse*)), this, SLOT(finishTransaction(HttpRequest*,HttpResponse*)));
    connect(newConnection, SIGNAL(dataReady(QByteArray)), this, SLOT(writeData(QByteArray)));
}

void HttpServer::stopServer() {
    close();
}

void HttpServer::readClientInformation() {
    HttpConnection *connection = static_cast<HttpConnection*>(sender());
    connection->start(QThread::NormalPriority);
}

QString HttpServer::serverName() const {
    return _mServerName;
}

void HttpServer::writeData(QByteArray data) {
    HttpConnection *connection = static_cast<HttpConnection*> (sender());
    QTcpSocket *socket = connection->socket();
    socket->write(data);
}

void HttpServer::finishTransaction(HttpRequest *req, HttpResponse *res) {
    QString transaction;
    transaction.append("\n====Request====\n");
    transaction.append(req->requestStr());
    transaction.append("\n====Response====\n");
    transaction.append(res->responseStr());
    emit(newMessage(transaction));
}
