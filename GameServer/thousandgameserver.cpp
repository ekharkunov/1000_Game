#include "thousandgameserver.h"
#include "config.h"
#include "connectionmanager.h"
#include "queryhandler.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDataStream>
#include <QFile>

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
    requestHandler = new QueryHandler();
}

ThousandGameServer::~ThousandGameServer() {
    delete _mManager;
    delete requestHandler;
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
        bool fileExist = QFile::exists(Config::pathDatabases.absolutePath() + "/" + *it);
        if (!fileExist) {
            QMessageBox::warning(0,
                                 "Warning",
                                 "Database " + *it + " not found!");
            return false;
        }
        else {
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

void ThousandGameServer::addRequestQuery() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    // проверяем состояние сокета
    if (mManager->socketState(socket) != WaitForQueryTransmission) return;
    quint16 blockSize = 0;//размер блока передаваемых данных
    quint16 requestSize = sizeof(QueryStruct) - sizeof(quint16);//количество байт, которое нам надо считать
    QueryStruct requestQuery;
    QDataStream stream(socket, QIODevice::ReadOnly);
    stream>>blockSize;
    if (socket->bytesAvailable() == requestSize) stream>>requestQuery;
    if (requestQuery.size > 0) {
        requestQuery.socketDescriptor = socket->socketDescriptor();
        Q_ASSERT(requestQuery.socketDescriptor != -1);
        //ставим запрос в очередь обработки
        locker.lockForWrite();
        _mRequestQueries.append(requestQuery);
        locker.unlock();
        emit (queryListChanged());//высылаем сигнал об изменении в очереди запросов
    }
}

void ThousandGameServer::sendToClient(QByteArray &array, QTcpSocket *socket) {

}

void ThousandGameServer::addNewConnection() {
    QTcpSocket *socket = nextPendingConnection();
    _mManager->addConnection(socket);
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotConnectionAborted()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(addRequestQuery()));
}

void ThousandGameServer::slotConnectionAborted() {
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    emit(connectionAborted(socket));
}
