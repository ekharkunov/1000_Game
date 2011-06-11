#include "thousandgamequeryhandler.h"
#include "thousandgameserver.h"
#include "thousandgamedataparser.h"
#include "connectionmanager.h"
#include "protocol.h"
#include <QSqlQuery>
#include <QSqlError>

ThousandGameQueryHandler::ThousandGameQueryHandler(ThousandGameServer *parentServer, QObject *parent) :
    AbstractQueryHandler(parent),
    server(parentServer)
{
    parser = new ThousandGameDataParser(this, parent);
}

ThousandGameQueryHandler::~ThousandGameQueryHandler() {
    delete parser;
    parser = 0;
}

void ThousandGameQueryHandler::run() {
    QueryStruct incommingRequest;
    QueryStruct outcommingRequest;
    bool empty;
    do {
        //считываем запрос, который находитс€ первым в очереди
        server->locker.lockForRead();
        incommingRequest = server->_mRequestQueries.first();
        server->locker.unlock();
        QByteArray inputData, outputData;
        QTcpSocket *socket = 0;
        //! TODO: ѕредусмотреть обрыв соединени€
        if (incommingRequest.size > 0) {
            socket = server->_mManager->findSocket(incommingRequest.socketDescriptor);
            QDataStream stream(socket);
            Q_ASSERT_X(socket, "ThousandGameQueryHandler::run()", "Cannot find socket for reading");
            quint16 dataSize = incommingRequest.size;
            quint16 blockSize = 0;
            while(dataSize) {
                blockSize = socket->bytesAvailable();
                if (blockSize) {
                    char *buffer = new char[blockSize];
                    stream.readRawData(buffer, sizeof(buffer));
                    inputData.append(buffer);
                    dataSize -= blockSize;
                    blockSize = 0;
                    delete buffer;
                }
                else qDebug()<<"Null block";
            }
            server->_mManager->setSocketState(socket, WaitForQueryTransmission);
        }
        QueryType type = incommingRequest.type;
        switch(type) {
        case REGISTER : {
            QVector<QString> errorMess;
            RegistrationData regInfo = parser->inRegistration(inputData);
            //! TODO: сделать ассоцииации с названием Ѕƒ через файл
            QSqlDatabase db = server->mapName2Database.value("1000_UserInformation.sqlite");
            if (db.isValid())
                errorMess.append(tr("Cannot find connetion to database 1000_UserInformation.sqlite"));
            else {
                QSqlQuery query(db);
                QString strQuery = "INSERT INTO UserInformation "
                        "(Nickname, Password, RealName, TotalNumberOfGames, Wins, Loses)"
                        "VALUES('%1', '%2', '%3', 0, 0, 0);";
                strQuery.arg(regInfo.nickName)
                        .arg(regInfo.password)
                        .arg(regInfo.realName);
                query.prepare(strQuery);
                query.exec();
                if (!query.isActive()) errorMess.append(query.lastError().text());
                else errorMess.append(tr("Registration successful!"));
            }
            outputData = parser->outRegistration(errorMess);
            outcommingRequest.socketDescriptor = incommingRequest.socketDescriptor;
            outcommingRequest.type = REGISTER;
            outcommingRequest.size = sizeof(outputData);
            break;
        }
        case AUTHORIZATION : {
            break;
        }
        case MESSANGE : {
            break;
        }
        case NEWGAME : {
            break;
        }
        case CONNECTGAME : {
            break;
        }
        case DISCONNECTGAME : {
            break;
        }
        case STARTGAME : {
            break;
        }
        case CANCELGAME : {
            break;
        }
        case FINISHGAME : {
            break;
        }
        case LISTALLGAME : {
            break;
        }
        case LISTALLNEWGAME : {
            break;
        }
        case TOTALSTATISTICS : {
            break;
        }
        case PLAYERSTATISTICS : {
            break;
        }
        case MOVE : {
            break;
        }
        default : {
        }

        }
        //отправка ответного запроса клиенту
        QByteArray byteRequest;
        byteRequest<<outcommingRequest;
        server->sendToClient(byteRequest, socket);
        server->sendToClient(outputData, socket);

        //удал€ем обработанный запрос из очереди
        server->locker.lockForWrite();
        server->_mRequestQueries.removeFirst();
        server->locker.unlock();
        //провер€ем очерель на пустоту
        server->locker.lockForRead();
        empty = server->_mRequestQueries.isEmpty();
        server->locker.unlock();
    } while (!empty);
}
