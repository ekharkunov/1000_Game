#include "httpserver.h"
#include "connectionmanager.h"
#include <QMessageBox>

HttpServer::HttpServer(int port, QObject *parent) :
        QTcpServer(parent),
        mPort(port)
{
    manager = ConnectionManager::getInstance();
    connect(this, SIGNAL(connectionAborted(QTcpSocket*)), manager, SLOT(removeConnection(QTcpSocket*)));
}

HttpServer::~HttpServer() {
    ConnectionManager::destroy();
}

bool HttpServer::startServer() {
    bool started = listen(QHostAddress::Any, mPort);
    if (!started) {
        QMessageBox::critical(0,
                              tr("Server error"),
                              tr("Unable to start HTTP server!:") + errorString());
        currentState = NotRunning;
        close();
        return false;
    }
    else {
        currentState = Running;
        connect(this, SIGNAL(newConnection()), this, SLOT(addNewConnection()));
        return true;
    }
}

void HttpServer::addNewConnection() {
    QTcpSocket* newSocket = nextPendingConnection();
    manager->addConnection(newSocket);
    //! TODO: удаление из менеджера
    connect(newSocket, SIGNAL(disconnected()), this, SLOT(slotConnectionAborted()));
    connect(newSocket, SIGNAL(disconnected()), newSocket, SLOT(deleteLater()));
    connect(newSocket, SIGNAL(readyRead()), this, SLOT(readClientInformation()));
    QByteArray arr, st;
    QString str = "HTTP/1.1 200 OK\r\n"
          "Server: myserver/0.0.1\r\n"
          "Content-Language: ru\r\n"
          "Content-Type: text/html; charset=utf-8\r\n"
          "Content-Length: %1\r\n"
          "Connection: keep-alive\r\n"
          "\r\n";
    newSocket->write(arr);
    st = "<html>"
         "<body>Server connected!</body>"
         "</html>";
    newSocket->write(st);
}

void HttpServer::readClientInformation() {

}

void HttpServer::slotConnectionAborted() {
    qDebug()<<"socket deletition";
    QTcpSocket *socket = static_cast<QTcpSocket*> (sender());
    emit(connectionAborted(socket));
}
