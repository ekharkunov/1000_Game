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
    MESSANGE,
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
    LISTALLGAME,
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
    qulonglong size;
    /**
    * @brief Перегруженный оператор помещения данных в поток
    * @param stream Поток с данными
    * @param str    Запрос, который необходимо поместить в поток
    * @return Поток с данными
    */
    friend QDataStream& operator <<(QDataStream &stream, const QueryStruct &str) {
        stream<<static_cast<quint32>(sizeof(str));
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
        quint32 size;
        stream>>size;
        stream>>type>>str.size;
        str.type = static_cast<QueryType>(type);
        return stream;
    }

    friend QByteArray& operator <<(QByteArray &array, const QueryStruct &str) {
        array.append(str.socketDescriptor);
        array.append(str.type);
        array.append(str.size);
        return array;
    }
};

#endif // PROTOCOL_H
