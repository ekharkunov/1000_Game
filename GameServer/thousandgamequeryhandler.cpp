#include "thousandgamequeryhandler.h"
#include "thousandgameserver.h"
#include "thousandgamedataparser.h"
#include "connectionmanager.h"
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
    QueryStruct incommingRequest;//входящий запрос
    QueryStruct outcommingRequest;//исходящий запрос
    QVector<QString> messageArray;//массив сообщений
    bool empty;//признак пустоты очереди
    do {
        messageArray.clear();
        //считываем запрос, который находится первым в очереди
        server->locker.lockForRead();
        incommingRequest = server->_mRequestQueries.first();
        server->locker.unlock();
        QByteArray inputData, outputData;//входящие и исходящие данные
        QTcpSocket *socket = server->_mManager->findSocket(incommingRequest.socketDescriptor);
        Q_ASSERT_X(socket, "ThousandGameQueryHandler::run()", "Cannot find socket for reading");
        //! TODO: Предусмотреть обрыв соединения
        if (incommingRequest.size > 0) {
            QDataStream stream(socket);
            quint16 dataSize = incommingRequest.size;
            quint16 blockSize = 0;
            //считываем данные для работы с запросом
            while(dataSize) {
                blockSize = socket->bytesAvailable();
                if (blockSize) {
                    char *buffer = new char[blockSize];
                    stream.readRawData(buffer, blockSize);
                    inputData += QByteArray::fromRawData(buffer, blockSize);
                    dataSize -= blockSize;
                    blockSize = 0;
                    delete buffer;
                }
                else { qDebug()<<"Null block"; return;}
            }
        }
        QueryType type = incommingRequest.type;
        switch(type) {
        //===============================================================================================
        case REGISTER : {
            RegistrationData regInfo = parser->inRegistration(inputData);
            //! TODO: сделать ассоцииации с названием БД через файл
            QSqlDatabase db = server->mapName2Database.value("1000_UserInformation.sqlite");
            if (!db.isValid()) {
                emit(server->newServerMessage(tr("Cannot find connetion to database 1000_UserInformation. sqlite\n")));
                messageArray.append(tr("Cannot find connetion to database 1000_UserInformation.sqlite\n"));
            }
            else {
                QSqlQuery query(db);
                QString strQuery = "SELECT Nickname FROM UserInformation WHERE Nickname = '%1';";
                strQuery = strQuery.arg(regInfo.nickName);
                query.prepare(strQuery);
                query.exec();
                query.next();
                if (query.isValid()) {
                    emit(server->newServerMessage(tr("The user with the same nickname is already exist!\n")));
                    messageArray.append(tr("The user with the same nickname is already exist!\n"));
                }
                else {
                    strQuery = "INSERT INTO UserInformation "
                            "(Nickname, Password, RealName, TotalNumberOfGames, Wins, Loses)"
                            "VALUES('%1', '%2', '%3', 0, 0, 0);";
                    strQuery = strQuery.arg(regInfo.nickName)
                            .arg(regInfo.password)
                            .arg(regInfo.realName);
                    query.prepare(strQuery);
                    query.exec();
                    if (!query.isActive()) {
                        emit(server->newServerMessage(query.lastError().text()));
                        messageArray.append(query.lastError().text());
                    }
                    else {
                        emit(server->newServerMessage(tr("Registration successful!\n")));
                        messageArray.append(tr("Registration successful!\n"));
                    }

                }
                query.finish();
            }
            outputData = parser->outRegistration(messageArray);
            outcommingRequest.type = REGISTER;
            break;
        }
        //===============================================================================================
        case AUTHORIZATION : {
            AuthorizationData authInfo = parser->inAuthorization(inputData);
            QSqlDatabase db = server->mapName2Database.value("1000_UserInformation.sqlite");
            if (!db.isValid()) {
                emit(server->newServerMessage(tr("Cannot find connetion to database 1000_UserInformation.sqlite\n")));
                messageArray.append(tr("Cannot find connetion to database 1000_UserInformation.sqlite\n"));
            }
            else {
                QSqlQuery query(db);
                //проверка на наличие указанного пользователя
                QString strQuery = "SELECT Nickname, Password FROM UserInformation "
                        "WHERE Nickname = '%1';";
                strQuery = strQuery.arg(authInfo.login);
                query.prepare(strQuery);
                query.exec();
                query.next();
                if (!query.isValid()) {
                    emit(server->newServerMessage(tr("Invalid user login\n")));
                    messageArray.append(tr("Invalid user login\n"));
                }
                else {//проверяем на совпадение паролей
                    if (query.value(1).toString() != authInfo.password) {
                        emit(server->newServerMessage(tr("Invalid user password\n")));
                        messageArray.append(tr("Invalid user password\n"));
                    }
                    else {
                        Q_ASSERT_X(socket, "Authorization query", "Socket pointer is null");
                        server->_mManager->setUserNick(socket, authInfo.login);
                        server->_mManager->setAuthorizationFlag(socket, true);
                        emit(server->newServerMessage(tr("Authorization successful!\n")));
                        messageArray.append(tr("Authorization successful!\n"));
                        emit(userListChanged());
                    }
                }
                query.finish();
            }
            outputData = parser->outAuthorization(messageArray);
            outcommingRequest.type = AUTHORIZATION;
            break;
        }
        //===============================================================================================
        case NEWGAME : {
            UserDescription user = server->_mManager->getUserDescription(socket->socketDescriptor());
            GameSettings settings = parser->inNewGame(inputData);
            bool success = server->createNewGame(user, settings);
            if (success) ;
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
        case LISTALLCURRENTGAME : {
            outputData = parser->outListAllCurrentGame(server->listCurrentGame);
            outcommingRequest.type = LISTALLCURRENTGAME;
            break;
        }
        case LISTALLNEWGAME : {
            outputData = parser->outListAllNewGame(server->listNewGame);
            outcommingRequest.type = LISTALLNEWGAME;
            break;
        }
        //===============================================================================================
        case TOTALSTATISTICS : {
            QSqlDatabase db = server->mapName2Database.value("1000_UserInformation.sqlite");
            if (db.isValid()) {
                QSqlQuery query(db);
                query.prepare("SELECT ID, Nickname, RealName, TotalNumberOfGames, Wins, Loses FROM UserInformation;");
                query.exec();
                PlayerInformation info;
                QVector<PlayerInformation> infoVector;
                while (query.next()) {
                    info.ID = query.value(0).toUInt();
                    info.Nickname = query.value(1).toString();
                    info.RealName = query.value(2).toString();
                    info.totalNumber = query.value(3).toUInt();
                    info.wins = query.value(4).toUInt();
                    info.loses = query.value(5).toUInt();
                    infoVector.append(info);
                }
                query.finish();
                outputData = parser->outTotalStatistics(infoVector);
                outcommingRequest.type = TOTALSTATISTICS;
            }
            break;
        }
        //===============================================================================================
        case PLAYERSTATISTICS : {
            QString nickName = parser->inPlayerStatistics(inputData);
            QSqlDatabase db = server->mapName2Database.value("1000_UserInformation.sqlite");
            if (db.isValid()) {
                QSqlQuery query(db);
                QString strQuery = "SELECT ID, Nickname, RealName, TotalNumberOfGames, Wins, Loses FROM UserInformation WHERE Nickname = '%1';";
                strQuery = strQuery.arg(nickName);
                query.prepare(strQuery);
                query.exec();
                query.next();
                PlayerInformation info = PlayerInformation();
                if (query.isValid()) {
                    info.ID = query.value(0).toUInt();
                    info.Nickname = query.value(1).toString();
                    info.RealName = query.value(3).toString();
                    info.totalNumber = query.value(4).toUInt();
                    info.wins = query.value(5).toUInt();
                    info.loses = query.value(6).toUInt();
                }
                query.finish();
                outputData = parser->outPlayerStatistics(info);
                outcommingRequest.type = PLAYERSTATISTICS;
            }
            break;
        }
        //===============================================================================================
        default : {
        }

        }
        outcommingRequest.socketDescriptor = incommingRequest.socketDescriptor;
        outcommingRequest.size = outputData.size();
        //отправка ответного запроса клиенту
        QByteArray byteRequest;
        QDataStream output(&byteRequest, QIODevice::WriteOnly);
        output<<outcommingRequest;
        mutex.lock();
        server->_mManager->setSocketState(socket, WaitForQueryTransmission);
        server->sendToClient(byteRequest, socket);
        server->_mManager->setSocketState(socket, WaitForDataTransmission);
        server->sendToClient(outputData, socket);
        server->_mManager->setSocketState(socket, WaitForQueryTransmission);
        mutex.unlock();
        //удаляем обработанный запрос из очереди
        server->locker.lockForWrite();
        server->_mRequestQueries.removeFirst();
        server->locker.unlock();
        //проверяем очерель на пустоту
        server->locker.lockForRead();
        empty = server->_mRequestQueries.isEmpty();
        server->locker.unlock();
    } while (!empty);

}
