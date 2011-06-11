/**
* @file thousandgameserver.cpp
* @author Kharkunov Eugene
* @date 4.06.2011
* @brief Файл содержит реализацию методов класса ThousandGameServer
*/

#include "thousandgameserver.h"
#include "config.h"
#include "connectionmanager.h"
#include "thousandgamequeryhandler.h"
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
    //Дописывать все необхоимые для сервера названия БД
    //! TODO: Сделать регистрацию БД через внешний файл
    databaseNames << "1000_UserInformation.sqlite";
    _mManager = new ConnectionManager();
    connect(this, SIGNAL(connectionAborted(QTcpSocket*)), _mManager, SLOT(removeConnection(QTcpSocket*)));
    requestHandler = new ThousandGameQueryHandler(this);
    connect(this, SIGNAL(queryListChanged()), requestHandler, SLOT(start(QThread::LowPriority)), Qt::DirectConnection);
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
    if (!isStarted) {//проверяем, удался ли захват порта
        QMessageBox::critical(0,
                              tr("Game server error"),
                              tr("Unable to start the server:") + errorString());
        close();
        return false;
    }
    else {

        bool isDatabasesInit = initDatabases();
        if (!isDatabasesInit) {//проверяем, прошла ли инициализация всех БД сервера
            close();
            return false;
        }
    }
    connect(this, SIGNAL(newConnection()), this, SLOT(addNewConnection()));
    state = AbstractGameServer::Running;
    return true;
}

void ThousandGameServer::stopServer() {

}

bool ThousandGameServer::initDatabases() {
    QSqlDatabase tempDB;
    QList<QString>::iterator it = databaseNames.begin();
    for (; it != databaseNames.end(); ++it) {
        bool fileExist = QFile::exists(Config::pathDatabases.absolutePath() + "/" + *it);
        if (!fileExist) {//проверяем на предмет существования файла БД
            QMessageBox::warning(0,
                                 tr("Warning"),
                                 tr("Database ") + *it + tr(" not found!"));
            return false;
        }
        else {
            tempDB = QSqlDatabase::addDatabase("QSQLITE", *it);
            tempDB.setDatabaseName(Config::pathDatabases.absolutePath() + "/" + *it);
            bool isOpened = tempDB.open();
            if (!isOpened) {//удалось ли открыть БД для работы
                QMessageBox::critical(0,
                                      tr("Database initialization error"),
                                      tr("Unable to initialization a ")  + *it + "\n"
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
    if (_mManager->socketState(socket) != WaitForQueryTransmission) return;
    quint16 blockSize = 0;//размер блока передаваемых данных
    quint16 requestSize = sizeof(QueryStruct) - sizeof(quint16);//количество байт, которое нам надо считать
    QueryStruct requestQuery;// преобразованный запрос
    QByteArray incomingRequest;//массив, куда считываются данные из потока
    QDataStream stream(socket);//поток считывания данных
    while (requestSize) {
        blockSize = socket->bytesAvailable();
        if (blockSize > requestSize) blockSize = requestSize;
        if (!blockSize) {
            qDebug()<<"Invalid size of query";
            break;
        }
        char *buffer = new char[blockSize];
        stream.readRawData(buffer, sizeof(buffer));
        incomingRequest.append(buffer);
        requestSize -= blockSize;
        blockSize = 0;
        delete []buffer;
    }
    QDataStream byteHandler(&incomingRequest, QIODevice::ReadOnly);
    byteHandler>>requestQuery;
    if (requestQuery.size != 0) {//в случае запроса, после которого не последует передача данных size == -1
        requestQuery.socketDescriptor = socket->socketDescriptor();
        Q_ASSERT(requestQuery.socketDescriptor != -1);
        //ставим запрос в очередь обработки
        locker.lockForWrite();
        _mRequestQueries.append(requestQuery);
        locker.unlock();
        _mManager->setSocketState(socket, WaitForDataTransmission);
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
