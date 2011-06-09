/**
* @file abstractdataparser.h
* @author Kharkunov Eugene
* @date 9.06.2011
* @brief Файл содержит описание класса, предоставляющего интерфейс для реализации обработки данных
* на сервере
*/
#ifndef ABSTRACTDATAPARSER_H
#define ABSTRACTDATAPARSER_H

#include <QObject>

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
    virtual void inRegistration(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных для авторизации пользователя
    * @param data Данные для авторизации
    */
    virtual void inAuthorization(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных, необходимых для создания новой игры на сервере
    * @param data Данные для создания игры
    */
    virtual void inNewGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных о подключении игрока к игре
    * @param data Данные о подключении к созданной игре
    */
    virtual void inConnectToGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных об отключении от игры
    * @param data Данные об отключении игрока от созданной игры(до момента запуска)
    */
    virtual void inDisconnectGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных об отмене созданной игры
    * @param data Данные, содержащие информацию об отмене созданной игры
    */
    virtual void inCancelGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных, необходимых для получения сведений об игроке
    * @param data Данные, содержащие информацию, необходимую для получения сведений об игроке
    */
    virtual void inPlayerStatistics(const QByteArray &data) = 0;

    /** @}*/

    /**
    * @defgroup OutcommingData Подготовка данных для отправки
    * Группа методов, предназначенных для подготовке данных, полученных от сервера, к отправке клиентам
    * @{
    */

    /**
    * @brief Подготавливает набор данных для отправки клиенту, который только что подключился к серверу
    * @return Набор данных, высылаемых при подключении нового клиента
    */
    virtual QByteArray outInfoForNewConnection() = 0;

    /**
    * @brief Подготавливает данные о пользователе после регистрации
    * @return Данные о зарегистрированном пользователе
    */
    virtual QByteArray outRegistration() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outAuthorization() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outMessage() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outNewGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outConnectGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outDisconnectGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outCancelGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outStartGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outFinishGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outListAllGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outListAllNewGame() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outTotalStatistics() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outPlayerStatistics() = 0;

    /**
    * @brief
    * @return
    */
    virtual QByteArray outMove() = 0;

    /** @}*/
signals:

public slots:

};

#endif // ABSTRACTDATAPARSER_H
