#include "thousandgamedataparser.h"
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
    outInfo<<data;
    return outInfo;
}

QByteArray ThousandGameDataParser::outTotalStatistics(QVector<PlayerInformation> &data) {
    QByteArray outArray;
    QVector<PlayerInformation>::iterator it = data.begin();
    for(; it != data.end(); ++it)
        outArray<<*it;
    return outArray;
}

GameSettings ThousandGameDataParser::inNewGame(const QByteArray &data) {
    GameSettings settings;
    QDataStream stream(data);
    stream>>settings;
    return settings;
}
