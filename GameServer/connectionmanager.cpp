#include "connectionmanager.h"

ConnectionManager::ConnectionManager(QObject *parent) : QObject(parent)
{
}

ConnectionManager::~ConnectionManager() {
    for (int i = 0; i < userList.size(); i++)
        delete userList.at(i).socket;
    userList.clear();
}

SocketState ConnectionManager::socketState(QTcpSocket *socket) const {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket)
            return userList.at(i)._mState;
    return Undefined;
}

void ConnectionManager::setSocketState(QTcpSocket *socket, SocketState state) {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket) {
            userList.value(i)._mState = state;
            break;
        }
}

QTcpSocket* ConnectionManager::findSocket(int descriptor) const {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket->socketDescriptor() == descriptor)
            return userList.at(i).socket;
    return 0;
}

QString ConnectionManager::userNick(QTcpSocket *socket) const {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket)
            return userList.at(i).UserNick;
    return QString();
}

void ConnectionManager::setUserNick(QTcpSocket *socket, QString nickName) {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket) {
            userList.value(i).UserNick = nickName;
            break;
        }
}

bool ConnectionManager::authorizationFlag(QTcpSocket *socket) const {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket)
            return userList.at(i).isAuthorize;
    return false;
}

void ConnectionManager::setAuthorizationFlag(QTcpSocket *socket, bool flag) {
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket) {
            userList.value(i).isAuthorize = flag;
            break;
        }
}

void ConnectionManager::addConnection(QTcpSocket *socket) {
    Q_ASSERT(socket);
    UserDescription sd;
    sd.socket = socket;
    sd._mState = WaitForQueryTransmission;
    sd.UserNick = tr("Guest") + QString::number(socket->socketDescriptor());
    sd.isAuthorize = false;
    sd.ConnectionID = socket->socketDescriptor();
    sd.GameID = 0;
    userList.push_back(sd);
}

void ConnectionManager::removeConnection(QTcpSocket *socket) {
    Q_ASSERT(socket);
    socket->close();
//    qDebug()<<"1234";
    int position = -1;
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).socket == socket) { position = i; break; }
//    qDebug()<<position;
    Q_ASSERT(position != -1);
    userList.removeAt(position);
//    qDebug()<<userList.isEmpty();
}

UserDescription ConnectionManager::getUserDescription(quint32 ID) {
    UserDescription sd;
    for (int i = 0; i < userList.size(); i++)
        if (userList.at(i).ConnectionID == ID)
            return userList.at(i);
    return sd;
}

QList<UserDescription>& ConnectionManager::getUserList() {
    return userList;
}

void ConnectionManager::closeAllConnections() {
    QList<UserDescription>::iterator it= userList.begin();
    for (; it != userList.end(); ++it)
        (*it).socket->close();
    userList.clear();
}
