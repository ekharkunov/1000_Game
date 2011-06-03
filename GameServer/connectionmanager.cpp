#include "connectionmanager.h"

ConnectionManager* ConnectionManager::_mManager = 0;

ConnectionManager* ConnectionManager::getInstance() {
    if (!_mManager)
        _mManager = new ConnectionManager();
    return _mManager;
}

void ConnectionManager::destroy() {
    if (_mManager) {
        delete _mManager;
        _mManager = 0;
    }
}

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
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
