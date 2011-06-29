#include "thousandgamedataparser.h"
#include "gamethousand.h"
#include <QVector>

ThousandGameDataParser::ThousandGameDataParser(ThousandGameQueryHandler *parentHandler, QObject *parent) :
    AbstractDataParser(parent),
    handler(parentHandler)
{
}

ThousandGameDataParser::~ThousandGameDataParser() {

}

RegistrationData ThousandGameDataParser::inRegistration(const QByteArray &data) {
    RegistrationData info;
    QDataStream stream(data);
    stream>>info;
    return info;
}

QByteArray ThousandGameDataParser::outRegistration(QVector<QString> &information) {
    QByteArray array;
    array.append(information.size());
    QVector<QString>::iterator it = information.begin();
    for (; it != information.end(); ++it)
        array.append(*it);
    return array;
}

AuthorizationData ThousandGameDataParser::inAuthorization(const QByteArray &data) {
    AuthorizationData info;
    QDataStream stream(data);
    stream>>info;
    return info;
}

QByteArray ThousandGameDataParser::outAuthorization(QVector<QString> &information) {
    QByteArray array;
    array.append(information.size());
    QVector<QString>::iterator it = information.begin();
    for (; it != information.end(); ++it)
        array.append(*it);
    return array;
}

QString ThousandGameDataParser::inPlayerStatistics(const QByteArray &data) {
    QString outStr;
    QDataStream stream(data);
    stream>>outStr;
    return outStr;
}

QByteArray ThousandGameDataParser::outPlayerStatistics(const PlayerInformation &data) {
    QByteArray outInfo;
    QDataStream writer(&outInfo, QIODevice::WriteOnly);
    writer<<data;
    return outInfo;
}

QByteArray ThousandGameDataParser::outTotalStatistics(QVector<PlayerInformation> &data) {
    QByteArray outArray;
    QDataStream writer(&outArray, QIODevice::WriteOnly);
    QVector<PlayerInformation>::iterator it = data.begin();
    for(; it != data.end(); ++it)
        writer<<*it;
    return outArray;
}

GameSettings ThousandGameDataParser::inNewGame(const QByteArray &data) {
    GameSettings settings;
    QDataStream stream(data);
    stream>>settings;
    return settings;
}

QByteArray ThousandGameDataParser::outListAllNewGame(QList<GameThousand *> &list) {
    QByteArray arr;
    QDataStream out(arr);
    out<<list.size();
    for (int i = 0; i < list.size(); i++) {
        GameThousand *game = list.at(i);
        out<<game->gameID();
        QList<UserDescription> userList = game->players();
        out<<userList.size();
        for (int j = 0; j < userList.size(); j++) {
            UserDescription user = userList.at(j);
            out<<user.UserNick.size();
            out<<user.UserNick;
        }
        out<<game->playerNumber()<<game->timeout();
    }
    return arr;
}

QByteArray ThousandGameDataParser::outListAllCurrentGame(QList<GameThousand*> &list) {
    QByteArray arr;
    QDataStream out(arr);
    out<<list.size();
    for (int i = 0; i < list.size(); i++) {
        GameThousand *game = list.at(i);
        out<<game->gameID();
        QList<UserDescription> userList = game->players();
        out<<game->playerNumber();
        for (int j = 0; j < userList.size(); j++) {
            UserDescription user = userList.at(j);
            out<<user.UserNick.size();
            out<<user.UserNick;
        }
        out<<game->timeout();
    }
    return arr;
}
