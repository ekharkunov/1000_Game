/**
* @file abstractdataparser.h
* @author Sosnovitch Sergei
* @date 21.06.2011
* @brief Файл содержит описание класса, предоставляющего интерфейс для реализации обработки данных
* на клиенте
*/
#ifndef ABSTRACTDATAPARSER_H
#define ABSTRACTDATAPARSER_H

#include <QObject>
#include <QString>
#include <QDataStream>
#include "protocol.h"
#include "card.h"
#include "gamethousand.h"

/**
* @class AbstractDataParser
* @brief Абстрактный класс, предоставляющий интерфейс для реализации методов обработки
* входящих и исхоящих с сервера данных
*/
class AbstractDataParser : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief Стандартный конструктор
    * @param parent Указатель на родительский объект
    */
    explicit AbstractDataParser(QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    virtual ~AbstractDataParser();

    /**
    * @defgroup IncommingData Обработка входящих данных
    * Группа методов для обработки поступающих от клиента данных
    * @{
    */

    /**
    * @brief Обработка данных о регистрации нового пользователя
    * @param data Данные о пользователе
    */
    virtual void inRegistration(QByteArray &data) = 0;

    /**
    * @brief Обработка данных для авторизации пользователя
    * @param data Данные для авторизации
    */
    virtual void inAuthorization(QByteArray &data) = 0;

    /**
    * @brief Обработка данных, необходимых для создания новой игры на сервере
    * @param data Данные для создания игры
    */
    virtual void inNewGame(QByteArray &data) = 0;

    virtual void inMessage(QByteArray &data) = 0;

    /**
    * @brief Обработка данных о подключении игрока к игре
    * @param data Данные о подключении к созданной игре
    */
    virtual void inConnectToGame(QByteArray &data) = 0;

    /**
    * @brief Обработка данных об отключении от игры
    * @param data Данные об отключении игрока от созданной игры(до момента запуска)
    */
    virtual void inDisconnectGame(QByteArray &data) = 0;

    virtual void inStartGame(QByteArray &data) = 0;

    virtual void inFinishGame(QByteArray &data) = 0;

    /**
    * @brief Обработка данных об отмене созданной игры
    * @param data Данные, содержащие информацию об отмене созданной игры
    */
    virtual void inCancelGame(QByteArray &data) = 0;

    /**
    * @brief Обработка данных, необходимых для получения сведений об игроке
    * @param data Данные, содержащие информацию, необходимую для получения сведений об игроке
    */
    virtual void inPlayerStatistics(QByteArray &data) = 0;

    virtual void inTotalStatistics(QByteArray &data) = 0;

    virtual void inMove(QByteArray &data) = 0;

    virtual void inListAllGame(QByteArray &data) = 0;

    virtual void inListAllNewGame(QByteArray &data) = 0;
    /** @}*/

signals:

public slots:
    /**
    * @defgroup OutcommingData Подготовка данных для отправки
    * Группа методов, предназначенных для подготовке данных, полученных от сервера, к отправке клиентам
    * @{
    */

    /**
    * @brief Подготавливает данные о пользователе после регистрации
    * @return Данные о зарегистрированном пользователе
    */
    virtual void outRegistration(const RegistrationData &info) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outAuthorization(const AuthorizationData &info) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outMessage(const QString &message) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outNewGame(const GameSettings &game) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outConnectGame(const quint16 &gameID) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outDisconnectGame(const quint16 &gameID) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outCancelGame(const quint16 &gameID) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outStartGame(const GameSettings &game) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outFinishGame(const quint16 &gameID) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outListAllGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual void outListAllNewGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual void outTotalStatistics() = 0;

    /**
    * @brief
    * @return
    */
    virtual void outPlayerStatistics(const PlayerInformation &player) = 0;

    /**
    * @brief
    * @return
    */
    virtual void outMove(const Card &card) = 0;

    /** @}*/

};

#endif // ABSTRACTDATAPARSER_H
