#include "httpserver.h"
#include "config.h"
#include "connectionmanager.h"
#include <QMessageBox>
#include <QFile>

HttpServer::HttpServer(int port, QObject *parent) :
        QTcpServer(parent),
        mPort(port)
{
    manager = new ConnectionManager();
    connect(this, SIGNAL(connectionAborted(QTcpSocket*)), manager, SLOT(removeConnection(QTcpSocket*)));
}

HttpServer::~HttpServer() {
    delete manager;
    manager = 0;
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
    QFile mainPage(Config::rootDirectory.absolutePath() + "/index.html");
    bool isOpened = mainPage.open(QIODevice::ReadOnly);
    QString str = "HTTP/1.1 200 OK\r\n"
          "Server: myserver/0.0.1\r\n"
          "Content-Language: ru\r\n"
          "Content-Type: text/html; charset=zutf-8\r\n"
          "Content-Length: %1\r\n"
          "Connection: keep-alive\r\n"
          "\r\n";
    if (isOpened) st = mainPage.readAll();
    else qDebug()<<"Cannot open file!";
    str = str.arg(st.size());

//    QDataStream writer(&arr, QIODevice::WriteOnly);
//    writer<<str;
    arr.append(str);
    newSocket->write(arr);
    newSocket->write(st);
    QImage img(Config::rootDirectory.absolutePath() + "/images/bg1.jpg");
    QByteArray imgByte;
    QDataStream stream(&imgByte, QIODevice::WriteOnly);
    stream<<img;
    newSocket->write(imgByte);
}

void HttpServer::stopServer() {

}

void HttpServer::readClientInformation() {

}

void HttpServer::slotConnectionAborted() {
    qDebug()<<"socket deletition";
    QTcpSocket *socket = static_cast<QTcpSocket*> (sender());
    emit(connectionAborted(socket));
}
