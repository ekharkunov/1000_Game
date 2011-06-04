#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
}

ConnectionManager::~ConnectionManager() {
    QVector<QTcpSocket*>::iterator it = socketsArray.begin();
    for (; it != socketsArray.end(); ++it)
        delete it;
    socketsArray.clear();
}

void ConnectionManager::addConnection(QTcpSocket *socket) {
    Q_ASSERT(socket);
    socketsArray.push_back(socket);
}

void ConnectionManager::removeConnection(QTcpSocket *socket) {
    Q_ASSERT(socket);
    qDebug()<<"1234";
    int position = socketsArray.indexOf(socket);
    qDebug()<<position;
    Q_ASSERT(position != -1);
    socketsArray.remove(position);
    qDebug()<<socketsArray.isEmpty();
}
