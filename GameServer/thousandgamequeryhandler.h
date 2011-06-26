/**
* @file thousandgamequeryhandler.h
* @author Kharkunov Eugene
* @date 9.06.2011
* @brief Файл содержит описание класса обработки очереди запросов для игрового сервера "Тысяча"
*/

#ifndef THOUSANDGAMEQUERYHANDLER_H
#define THOUSANDGAMEQUERYHANDLER_H

#include "abstractqueryhandler.h"
#include <QMutex>

class ThousandGameServer;
class ThousandGameDataParser;

/**
* @class ThousandGameQueryHandler
* @brief Класс обработки очереди запросов, поступивших на игровой сервер. Выполняется в отдельном потоке.
* @sa AbstractQueryHandler
*/
class ThousandGameQueryHandler : public AbstractQueryHandler
{
    Q_OBJECT
public:
    /**
    * @brief Стандартный конструктор
    * @param parentServer   Указатель на объект игрового сервера "Тысяча"
    * @param parent         Указатель на родительский объект
    */
    explicit ThousandGameQueryHandler(ThousandGameServer *parentServer, QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    ~ThousandGameQueryHandler();

    /**
    * @brief Обрабатывает очередь запросов до тех пор, пока она не станет пустой
    * @sa ThousandGameServer::_mRequestQueries
    */
    void run();
private:
    //! Указатель на объект игрового сервера, очередь запросов которого необходимо обработать
    ThousandGameServer *server;
    //! Указатель на обработчик данных
    ThousandGameDataParser *parser;
    //! Мьютекс для блокировки данных
    QMutex mutex;
signals:
    //! Сигнал об изменении списка игроков
    void userListChanged();
};

#endif // THOUSANDGAMEQUERYHANDLER_H
