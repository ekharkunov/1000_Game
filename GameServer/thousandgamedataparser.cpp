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
