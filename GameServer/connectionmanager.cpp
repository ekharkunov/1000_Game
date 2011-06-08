#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
}

ConnectionManager::~ConnectionManager() {
    for (int i = 0; i < socketsArray.size(); i++)
        delete socketsArray.at(i).socket;
    socketsArray.clear();
}

SocketState ConnectionManager::socketState(QTcpSocket *socket) const {
    for (int i = 0; i < socketsArray.size(); i++)
        if (socketsArray.at(i).socket == socket)
            return socketsArray.at(i)._mState;
    return Undefined;
}

void ConnectionManager::setSocketState(QTcpSocket *socket, SocketState state) {
    for (int i = 0; i < socketsArray.size(); i++)
        if (socketsArray.at(i).socket == socket) {
            socketsArray.value(i)._mState = state;
            break;
        }
}

void ConnectionManager::addConnection(QTcpSocket *socket) {
    Q_ASSERT(socket);
    SocketDescr sd;
    sd.socket = socket;
    sd._mState = WaitForQueryTransmission;
    socketsArray.push_back(sd);
}

void ConnectionManager::removeConnection(QTcpSocket *socket) {
    Q_ASSERT(socket);
    qDebug()<<"1234";
    int position = -1;
    for (int i = 0; i < socketsArray.size(); i++)
        if (socketsArray.at(i).socket == socket) { position = i; break; }
    qDebug()<<position;
    Q_ASSERT(position != -1);
    socketsArray.remove(position);
    qDebug()<<socketsArray.isEmpty();
}
