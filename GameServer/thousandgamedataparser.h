/**
* @file thousandgamedataparser.h
* @author Kharkunov Eugene
* @date 6.06.2011
* @brief Содержит описание класса, который обрабатывает данные для передачи
*/

#ifndef THOUSANDGAMEDATAPARSER_H
#define THOUSANDGAMEDATAPARSER_H

#include "abstractdataparser.h"

class ThousandGameQueryHandler;

/**
* @class ThousandGameDataParser
* @brief Класс, обеспечивающий корректную обработку поступающих данных и подготовку данных для передачи
* клиентам
*/
class ThousandGameDataParser : public AbstractDataParser
{
    Q_OBJECT
public:
    /**
    * @brief Стандартный конструктор
    * @param parentHandler  Указатель на родительский обработчик запросов
    * @param parent         Указатель на родительский объект
    */
    explicit ThousandGameDataParser(ThousandGameQueryHandler *parentHandler, QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    ~ThousandGameDataParser();

    /**
    * @brief Переопределена от AbstractDataParser::inRegistration
    */
    RegistrationData inRegistration(const QByteArray &data);

    /**
    * @brief Переопределена от AbstractDataParser::outRegistration
    */
    QByteArray outRegistration(QVector<QString> &information);

    /**
    * @brief Переопределена от AbstractDataParser::inAuthorization
    */
    AuthorizationData inAuthorization(const QByteArray &data);

    /**
    * @brief Переопределена от AbstractDataParser::outAuthorization
    */
    QByteArray outAuthorization(QVector<QString> &information);

    /**
    * @brief Переопределена от AbstractDataParser::inPlayerStatistics
    */
    QString inPlayerStatistics(QByteArray &data);

    /**
    * @brief Переопределена от AbstractDataParser::outPlayerStatistics
    */
    QByteArray outPlayerStatistics(const PlayerInformation &data);

    /**
    * @brief Переопределна от AbstractDataParser::outTotalStatistics
    */
    QByteArray outTotalStatistics(QVector<PlayerInformation> &data);
private:
    //! Указатель на обработчик очереди запросов
    ThousandGameQueryHandler *handler;

signals:

public slots:

};

#endif // THOUSANDGAMEDATAPARSER_H
