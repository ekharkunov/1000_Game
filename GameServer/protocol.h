/**
* @file protocol.h
* @author Kharkunov Eugene
* @date 5.06.2011
* @brief Файл содержит основные типы запросов пользовательского протокола передачи, а также структуру
* самого запроса
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QDataStream>

/**
* @enum QueryType
* @brief Перечисление описывает основные запросы, реализованные в пользовательском
* протоколе
*/
enum QueryType {
    //! Запрос на регистрацию нового участника
    REGISTER,
    //! Запрос на авторизацию пользователя
    AUTHORIZATION,
    //! Запрос на отправку сообщения в чат
    MESSAGE,
    //! Запрос на создание новой игры
    NEWGAME,
    //! Запрос на подключение игрока к созданной игре
    CONNECTGAME,
    //! Запрос на отключение игрока от созданной игры
    DISCONNECTGAME,
    //! Запрос на начало созданной игры
    STARTGAME,
    //! Запрос на отмену созданной игры
    CANCELGAME,
    //! Запрос на отпраку уведомления об окончании игры
    FINISHGAME,
    //! Запрос на получение полного списка игр на сервере
    LISTALLCURRENTGAME,
    //! Запрос на получение списка созданных игр, ожидающих запуска
    LISTALLNEWGAME,
    //! Запрос на получение статистики по серверу
    TOTALSTATISTICS,
    //! Запрос на получение статистики конкретного пользователя
    PLAYERSTATISTICS,
    //! Запрос на обработку выполненного хода
    MOVE
};

/**
* @struct QueryStruct
* @brief Описывает структуру запроса пользовательского протокола передачи данных
*/
struct QueryStruct {
    //! Дескриптор сокета
    quint16 socketDescriptor;
    //! Тип запроса
    QueryType type;
    //! Размер передаваемых данных
    qlonglong size;
    /**
    * @brief Перегруженный оператор помещения данных в поток
    * @param stream Поток с данными
    * @param str    Запрос, который необходимо поместить в поток
    * @return Поток с данными
    */
    friend QDataStream& operator <<(QDataStream &stream, const QueryStruct &str) {
        stream<<str.type<<str.size;
        return stream;
    }

    /**
    * @brief Перегруженный оператор извлечения данных из потока
    * @param stream Поток с данными
    * @param str    Извлеченный запрос
    * @return Поток с данными
    */
    friend QDataStream& operator >>(QDataStream &stream, QueryStruct &str) {
        int type = 0;
        stream>>type>>str.size;
        str.type = static_cast<QueryType>(type);
        return stream;
    }
};

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
};

/** @}*/

#endif // PROTOCOL_H
