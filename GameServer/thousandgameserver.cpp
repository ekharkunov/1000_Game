#include "thousandgameserver.h"
#include "config.h"
#include "connectionmanager.h"
#include <QMessageBox>
#include <QSqlError>

ThousandGameServer* ThousandGameServer::_mInstance = 0;

ThousandGameServer* ThousandGameServer::getInstance() {
    if (!_mInstance)
        _mInstance = new ThousandGameServer(Config::portsForGameServers.value("Game: 1000"));
    return _mInstance;
}

void ThousandGameServer::destroy() {
}

ThousandGameServer::ThousandGameServer(int port, QObject *parent) :
        AbstractGameServer(port, parent),
        _mPort(port),
        state(AbstractGameServer::NotRunning)
{
    databaseNames << "1000_UserInformation.sqlite";
    _mManager = new ConnectionManager();
    connect(this, SIGNAL(connectionAborted(QTcpSocket*)), _mManager, SLOT(removeConnection(QTcpSocket*)));
}

ThousandGameServer::~ThousandGameServer() {
    delete _mManager;
}

AbstractGameServer::states ThousandGameServer::serverState() const {
    return state;
}

bool ThousandGameServer::startServer() {
    bool isStarted = listen(QHostAddress::Any, _mPort);
    if (!isStarted) {
        QMessageBox::critical(0,
                              "Game server error",
                              "Unable to start the server:" + errorString());
        close();
        return false;
    }
    else {
        connect(this, SIGNAL(newConnection()), this, SLOT(addNewConnection()));
        bool isDatabasesInit = initDatabases();
        if (!isDatabasesInit) {
        close();
        return false;
        }
    }
    state = AbstractGameServer::Running;
    return true;
}

void ThousandGameServer::stopServer() {

}

bool ThousandGameServer::initDatabases() {
    QSqlDatabase tempDB;
    tempDB = QSqlDatabase::addDatabase("QSQLITE");
    QList<QString>::iterator it = databaseNames.begin();
    for (; it != databaseNames.end(); ++it) {
        tempDB.setDatabaseName(Config::pathDatabases.absolutePath() + "/" + *it);
        bool isOpened = tempDB.open();
        if (!isOpened) {
            QMessageBox::critical(0,
                                  "Database initialization error",
                                  "Unable to initialization a "  + *it + "\n"
                                  + tempDB.lastError().text());
            return false;
        }
        else {
            mapName2Database[*it] = tempDB;
        }
    }
    qDebug()<<"database OK!";
    return true;
}

void ThousandGameServer::disconnectDatabases() {
    QMap<QString, QSqlDatabase>::iterator it = mapName2Database.begin();
    for (; it != mapName2Database.end(); ++it) {
        it.value().close();
    }
    mapName2Database.clear();
    databaseNames.clear();
}

void ThousandGameServer::readClientInformation() {

}

void ThousandGameServer::sendToClient(QByteArray &array, QTcpSocket *socket) {

}

void ThousandGameServer::addNewConnection() {
    QTcpSocket *socket = nextPendingConnection();
    _mManager->addConnection(socket);
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotConnectionAborted()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readClientInformation()));
}

void ThousandGameServer::slotConnectionAborted() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    emit(connectionAborted(socket));
}
