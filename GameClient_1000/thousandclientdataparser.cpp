#include "thousandclientdataparser.h"

ThousandClientDataParser::ThousandClientDataParser(ThousandClient *client, QObject *parent)
    : AbstractDataParser(parent)
{
  workClient=client;
}

void ThousandClientDataParser::incomingData()
{
     QueryStruct query;
    quint16 blockSize = 0;
    QTcpSocket *socket = workClient->connection;
    QDataStream stream(socket);
    quint16 requestSize = sizeof(QueryStruct) - 2 * sizeof(quint16);
    QByteArray incomingRequest;
    while (requestSize) {
         blockSize = socket->bytesAvailable();
         if (blockSize > requestSize) blockSize = requestSize;
         if (!blockSize) {
                emit(workClient->erorText("Invalid size of query"));
             break;
         }
         char *buffer = new char[blockSize];
         stream.readRawData(buffer, blockSize);
         incomingRequest += QByteArray::fromRawData(buffer, blockSize);
         requestSize -= blockSize;
         blockSize = 0;
         delete []buffer;
     }
    QDataStream reader(incomingRequest);
         reader>>query;  //Извлекаем структуру с запросом из входящего потока


    QByteArray data;
    requestSize = query.size;
         while (requestSize) {
              blockSize = socket->bytesAvailable();
              if (blockSize > requestSize) blockSize = requestSize;
              if (!blockSize) {
                   emit(workClient->erorText("Invalid size of query"));
                  break;
              }
              char *buffer = new char[blockSize];
              stream.readRawData(buffer, blockSize);
              data += QByteArray::fromRawData(buffer, blockSize);
              requestSize -= blockSize;
              blockSize = 0;
              delete []buffer;
          }

     switch(query.type)
     {
       case REGISTER:
         inRegistration(data);
         break;
       case AUTHORIZATION:
         inAuthorization(data);
         break;
       case MESSAGE:
         inMessage(data);
         break;
       case NEWGAME:
         inNewGame(data);
         break;
       case CONNECTGAME:
         inConnectToGame(data);
         break;
       case DISCONNECTGAME:
         inDisconnectGame(data);
         break;
       case STARTGAME:
         inStartGame(data);
         break;
       case CANCELGAME:
         inCancelGame(data);
         break;
       case FINISHGAME:
         inFinishGame(data);
         break;
       case LISTALLCURRENTGAME:
         inListAllGame(data);
         break;
       case LISTALLNEWGAME:
         inListAllNewGame(data);
         break;
       case TOTALSTATISTICS:
         inTotalStatistics(data);
         break;
       case PLAYERSTATISTICS:
         inPlayerStatistics(data);
         break;
       case MOVE:
         inMove(data);
         break;
     }
}

void ThousandClientDataParser::inRegistration(QByteArray &data)
{
    QDataStream in(data);
    QVector<QString> inData;
    int size,sizeString;
    in>>size;
    inData.resize(size);
    for(int i=0;i<size;i++)
    {
        in>>sizeString;
        inData[i].resize(sizeString);
        in>>inData[i];
    }
    emit(compliteRegistration(inData));
}

void ThousandClientDataParser::inAuthorization(QByteArray &data)
{
    QDataStream in(data);
    QVector<QString> inData;
    int size,sizeString;
    in>>size;
    inData.resize(size);
    for(int i=0;i<size;i++)
    {
        in>>sizeString;
        inData[i].resize(sizeString);
        in>>inData[i];
    }
    emit(compliteAuthorization(inData));
}

void ThousandClientDataParser::inNewGame(QByteArray &data)
{

}

void ThousandClientDataParser::inConnectToGame(QByteArray &data)
{

}

void ThousandClientDataParser::inDisconnectGame(QByteArray &data){}

void ThousandClientDataParser::inCancelGame(QByteArray &data){}

void ThousandClientDataParser::inPlayerStatistics(QByteArray &data)
{
   QDataStream in(data);
   PlayerInformation player;
   in>>player;
   emit(complitePlayerStatistics(player));
}

void ThousandClientDataParser::inMessage(QByteArray &data)
{
   QDataStream stream(data);
   quint32 size;
   QString newMessage;
   stream>>size;
   newMessage.resize(size);
   stream>>newMessage;
   emit(compliteMessage(newMessage));
}

void ThousandClientDataParser::inStartGame(QByteArray &data){}

void ThousandClientDataParser::inFinishGame(QByteArray &data){}

void ThousandClientDataParser::inTotalStatistics(QByteArray &data)
{
  QDataStream in(data);
  QVector<PlayerInformation> info;
  int size;
  in>>size;
  for(int i=0;i<size;i++)
  {
      in>>info[i];
  }
  emit(compliteTotalStatistics(info));
}

void ThousandClientDataParser::inListAllGame(QByteArray &data)
{
       QDataStream in(data);
       QList<GameThousand> gamesList;
       QList<Player> players;
       QString player;
       quint16 time,id;
       quint8 number;
       int size,nick_size;
       in>>size;
       for(int i=0;i<size;i++){
           players.clear();
           in>>id;
           in>>number;
           for(quint8 j=0;j<number;j++){
                    in>>nick_size;
                    in>>player;
                    Player pl(player);
                    players.append(pl);
           }
           in>>time;
           GameThousand game(players,number,time);
           game.setGameId(id);
           gamesList.append(game);
       }
       emit(compliteListAllGame(gamesList));
}

void ThousandClientDataParser::inListAllNewGame(QByteArray &data)
{
    QDataStream in(data);
    QList<GameThousand> gamesList;
    QList<Player> players;
    QString player;
    quint16 time,id;
    quint8 number;
    int size,nick_size;
    in>>size;
    for(int i=0;i<size;i++){
        players.clear();
        in>>id;
        in>>number;
        for(quint8 j=0;j<number;j++){
                 in>>nick_size;
                 in>>player;
                 Player pl(player);
                 players.append(pl);
        }
        in>>time;
        GameThousand game(players,number,time);
        gamesList.append(game);
    }
    emit(compliteListAllNewGame(gamesList));
}

void ThousandClientDataParser::inMove(QByteArray &data){}

void ThousandClientDataParser::outRegistration(const RegistrationData &info)
{
   QByteArray array;
   QDataStream out(array);
    out<<info;
   workClient->sendToServer(array,REGISTER);
}

void ThousandClientDataParser::outAuthorization(const AuthorizationData &info)
{
    QByteArray array;
    QDataStream out(&array, QIODevice::WriteOnly);
    out<<info;
    workClient->sendToServer(array,AUTHORIZATION);
}

void ThousandClientDataParser::outMessage(const QString &message)
{
    QByteArray array;
    QDataStream writer(&array, QIODevice::WriteOnly);
    writer<<message.size()<<message;
    workClient->sendToServer(array,MESSAGE);
}

void ThousandClientDataParser::outNewGame(const GameSettings &game)
{
    QByteArray array;
    QDataStream out(array);
     out<<game;
    workClient->sendToServer(array,NEWGAME);
}

void ThousandClientDataParser::outConnectGame(const quint16 &gameID)
{
    QByteArray array;
    QDataStream out(array);
     out<<gameID;
    workClient->sendToServer(array,CONNECTGAME);
}

void ThousandClientDataParser::outDisconnectGame(const quint16 &gameID)
{
    QByteArray array;
    QDataStream out(array);
     out<<gameID;
    workClient->sendToServer(array,DISCONNECTGAME);
}

void ThousandClientDataParser::outCancelGame(const quint16 &gameID)
{
    QByteArray array;
    QDataStream out(array);
     out<<gameID;
    workClient->sendToServer(array,CANCELGAME);
}

void ThousandClientDataParser::outStartGame(const quint16 &gameID)
{
    QByteArray array;
    QDataStream out(array);
     out<<gameID;
    workClient->sendToServer(array,STARTGAME);
}

void ThousandClientDataParser::outFinishGame(const quint16 &gameID)
{
    QByteArray array;
    QDataStream out(array);
     out<<gameID;
    workClient->sendToServer(array,FINISHGAME);
}

void ThousandClientDataParser::outListAllGame()
{
   QByteArray array=0;
   workClient->sendToServer(array,LISTALLCURRENTGAME);
}

void ThousandClientDataParser::outListAllNewGame()
{
    QByteArray array=0;
    workClient->sendToServer(array,LISTALLNEWGAME);
}

void ThousandClientDataParser::outTotalStatistics()
{
    QByteArray array=0;
    workClient->sendToServer(array,TOTALSTATISTICS);
}

void ThousandClientDataParser::outPlayerStatistics(const PlayerInformation &player)
{
    QByteArray array;
    QDataStream str(array);
    str<<player;
    workClient->sendToServer(array,PLAYERSTATISTICS);
}

void ThousandClientDataParser::outMove(const Card &card)
{
    QByteArray array=0;
    QDataStream out(array);
     out<<card;
    workClient->sendToServer(array,MOVE);
}
