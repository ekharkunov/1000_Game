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
#include <QString>
#include <QDataStream>
//#include <QByteArray>

/**
* @defgroup DataStructure Структуры данных для передачи
* @brief Структуры, которые описывают данные, передаваемые по пользовательскому протоколу передачи
* @{
*/

/**
* @struct RegistrationData
* @brief Структура описывает данные, которые передаются от клиента к серверу в случае регистрации нового
* пользователя
*/
struct RegistrationData {
    //! Ник пользователя(его использую как логин при авторизации)
    QString nickName;
    //! Пароль
    QString password;
    //! Настоящее имя
    //! TODO: Обеспечить совместимость с русским языком
    QString realName;

    /**
    * @brief Перегруженный оператор помещения данных о регистрации пользователя в поток
    * @param stream Поток с данными
    * @param data   Данные, которые необходимо поместить в поток
    * @return Поток с данными
    */
    friend QDataStream& operator <<(QDataStream &stream, const RegistrationData &data) {

        stream<<data.nickName.size()
              <<data.nickName
              <<data.password.size()
              <<data.password
              <<data.realName.size()
              <<data.realName;
        return stream;
    }

    /**
    * @brief Перегруженный оператор извлечения данных  о регистрации пользователя из потока
    * @param stream Поток с данными
    * @param data   Извлеченные данные
    * @return Поток с данными
    */
    friend QDataStream& operator >>(QDataStream &stream, RegistrationData &data) {
        quint32 strSize;
        stream>>strSize;
        data.nickName.resize(strSize);
        stream>>data.nickName;
        stream>>strSize;
        data.password.resize(strSize);
        stream>>data.password;
        stream>>strSize;
        data.realName.resize(strSize);
        stream>>data.realName;
        return stream;
    }
};

/**
* @struct AuthorizationData
* @brief Структура, которая содержит данные, необходимые для авторизации пользователя на сервере
*/
struct AuthorizationData {
    //! Логин пользователя(совпадает с ником)
    QString login;
    //! Пароль
    QString password;

    /**
    * @brief Перегруженный оператор помещения авторизационных данных в поток
    * @param stream Поток с данными
    * @param data   Данные, которые необходимо поместить в поток
    * @return Поток с данными
    */
    friend QDataStream& operator <<(QDataStream &stream, const AuthorizationData &data) {
        stream<<data.login.size()
              <<data.login
              <<data.password.size()
              <<data.password;
        return stream;
    }

    /**
    * @brief Перегруженный оператор извлечения авторизационных данных из потока
    * @param stream Поток с данными
    * @param data   Извлеченные данные
    * @return Поток с данными
    */
    friend QDataStream& operator >>(QDataStream &stream, AuthorizationData &data) {
        quint32 strSize;
        stream>>strSize;
        data.login.resize(strSize);
        stream>>data.login;
        stream>>strSize;
        data.password.resize(strSize);
        stream>>data.password;
        return stream;
    }
};

/**
* @struct PlayerInformation
* @brief Структура описывает информацию о пользователе, которая хранится в БД сервера
*/
struct PlayerInformation {
    /**
    * @brief ID пользователя в БД.
    * @note Не следует путать с ID пользователя, который присваивается при подключении к серверу.
    * @sa UserDescription::connectionID
    */
    quint16 ID;
    //! Ник пользователя
    QString Nickname;
    //! Настоящее имя пользователя
    QString RealName;
    //! Общее число игр
    quint16 totalNumber;
    //! Число побед
    quint16 wins;
    //! Число поражений
    quint16 loses;

    //! Конструктор пустой структуры
    PlayerInformation() :
        ID(0),
        Nickname(""),
        RealName(""),
        totalNumber(0),
        wins(0),
        loses(0) {}

    /**
    * @brief Перегруженный оператор помещения информации о пользователе в поток данных
    * @param stream Поток с данными
    * @param info   Информация о пользователе
    * @return Поток с помещенными в него данными о пользователе
    */
    friend QDataStream& operator <<(QDataStream& stream, const PlayerInformation &info) {
        stream<<info.ID
              <<info.Nickname.size()
              <<info.Nickname
              <<info.RealName.size()
              <<info.RealName
              <<info.totalNumber
              <<info.wins
              <<info.loses;
        return stream;
    }

    /**
    * @brief Перегруженный оператор извлечения информации о пользователе из потока данных
    * @param stream Поток с данными
    * @param info   Информация о пользователе
    * @return Поток с извлеченными данными
    */
    friend QDataStream& operator >>(QDataStream& stream, PlayerInformation &info) {
        quint32 strSize;
        stream>>info.ID;
        stream>>strSize;
        info.Nickname.resize(strSize);
        stream>>info.Nickname;
        stream>>strSize;
        info.RealName.resize(strSize);
        stream>>info.RealName
              >>info.totalNumber
              >>info.wins
              >>info.loses;
        return stream;
    }

    /**
    * @brief Перегруженный оператор помещения данных о пользователе в массив байт
    * @param array  Массив байт
    * @param info   Информация о пользователе
    * @return Массив байт с записанной в него информацией
    */
    friend QByteArray& operator <<(QByteArray &array, const PlayerInformation &info) {
        array.clear();
        array.append(info.ID);
        array.append(info.Nickname.size());
        array.append(info.Nickname);
        array.append(info.RealName.size());
        array.append(info.RealName);
        array.append(info.totalNumber);
        array.append(info.wins);
        array.append(info.loses);
        return array;
    }
};

/**
* @struct GameSettings
* @brief Структура описывает данные, необходимые для настройки создаваемой игры
*/
struct GameSettings {
    //! ID игрока, который создает игру
    quint16 createrID;
    /**
    * @brief Количество игроков, на которое рассчитана создаваемая игра
    * @note Должно быть от 2 до 4
    */
    quint8   playersNumber;
    /**
    * @brief Время, которое отводится участнику, чтобы сделать ход (значение передается в секундах)
    * @note Должно быть в пределах от 30 до 90 секунд(возможные значения: 30, 45, 60, 90)
    */
    quint16  timeout;

    /**
    * @brief Перегруженный оператор помещения игровых настроек в поток данных
    * @param stream     Поток с данными
    * @param settings   Игровые настройки
    * @return Поток с помещенными в него игровыми настройками
    */
    friend QDataStream& operator <<(QDataStream& stream, const GameSettings &settings) {
        stream<<settings.createrID
             <<settings.playersNumber
            <<settings.timeout;
        return stream;
    }

    /**
    * @brief Перегруженный оператор извлечения игровых настроек из потока данных
    * @param stream     Поток с данными
    * @param settings   Игровые настройки
    * @return Поток с извлеченными данными
    */
    friend QDataStream& operator >>(QDataStream& stream, GameSettings &settings) {
        stream>>settings.createrID
             >>settings.playersNumber
            >>settings.timeout;
        return stream;
    }

    /**
    * @brief Перегруженный оператор помещения игровых настроек в массив байт
    * @param array      Массив байт
    * @param settings   Игровые настройки
    * @return Массив байт с записанными в него настройками
    */
    friend QByteArray& operator <<(QByteArray &array, const GameSettings &settings) {
        array.clear();
        array.append(settings.createrID);
        array.append(settings.playersNumber);
        array.append(settings.timeout);
        return array;
    }
};

/** @}*/

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
    * @return Данные, преобразованные в структуру RegistrationData
    */
    virtual RegistrationData inRegistration(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных для авторизации пользователя
    * @param data Данные для авторизации
    * @return Данные, преобразованные в структуру AuthorizationData
    */
    virtual AuthorizationData inAuthorization(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных, необходимых для создания новой игры на сервере
    * @param data Данные для создания игры
    * @return Игровые настройки
    */
    virtual GameSettings inNewGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных о подключении игрока к игре
    * @param data Данные о подключении к созданной игре
    */
    //    virtual void inConnectToGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных об отключении от игры
    * @param data Данные об отключении игрока от созданной игры(до момента запуска)
    */
    //    virtual void inDisconnectGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных об отмене созданной игры
    * @param data Данные, содержащие информацию об отмене созданной игры
    */
    //    virtual void inCancelGame(const QByteArray &data) = 0;

    /**
    * @brief Обработка данных, необходимых для получения сведений об игроке
    * @param data Данные, содержащие информацию, необходимую для получения сведений об игроке
    * @return Ник пользователя, о котором запрашивается информация
    */
    virtual QString inPlayerStatistics(const QByteArray &data) = 0;

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
    //    virtual QByteArray outInfoForNewConnection() = 0;

    /**
    * @brief Подготавливает данные о пользователе после регистрации
    * @param information Информация о результате регистрации
    * @return Сообщения, которые возникли в ходе работы. В случае успеха, содержит в себе сообщение
    * "Registration successful!"
    */
    virtual QByteArray outRegistration(QVector<QString> &information) = 0;

    /**
    * @brief Подготавливает данные о результатх авторизации
    * @param information Информация о результатах авторизации
    * @return Сообщения, которые возникли в ходе работы. В случае успеха, содержит в себе сообщение
    * "Authorization successful!"
    */
    virtual QByteArray outAuthorization(QVector<QString> &information) = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outMessage() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outNewGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outConnectGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outDisconnectGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outCancelGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outStartGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outFinishGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outListAllGame() = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outListAllNewGame() = 0;

    /**
    * @brief Преобразование совокупной информации по серверу в массив байт
    * @param data Совокупная информация
    * @return Массив байт, содержащий всю информацию о зарегистрированных игроках на данном сервере
    */
    virtual QByteArray outTotalStatistics(QVector<PlayerInformation> &data) = 0;

    /**
    * @brief Преобразование информации о пользователе в массив байт
    * @param data Информация о пользователе
    * @return Массив с данными о пользователе
    */
    virtual QByteArray outPlayerStatistics(const PlayerInformation &data) = 0;

    /**
    * @brief
    * @return
    */
    //    virtual QByteArray outMove() = 0;

    /** @}*/
signals:

public slots:

};

#endif // ABSTRACTDATAPARSER_H
