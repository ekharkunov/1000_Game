/**
* @file thousandgamequeryhandler.h
* @author Kharkunov Eugene
* @date 9.06.2011
* @brief Файл содержит описание класса обработки очереди запросов для игрового сервера "Тысяча"
*/

#ifndef THOUSANDGAMEQUERYHANDLER_H
#define THOUSANDGAMEQUERYHANDLER_H

#include "abstractqueryhandler.h"

class ThousandGameServer;

/**
* @class ThousandGameQueryHandler
* @brief Класс обработки очереди запросов, поступивших на игровой сервер. Выполняется в отдельном потоке.
* @sa AbstractQueryHandler
*/
class ThousandGameQueryHandler : public AbstractQueryHandler
{
    Q_OBJECT
public:
    explicit ThousandGameQueryHandler(ThousandGameServer *parentServer, QObject *parent = 0);
    void run();
private:
    ThousandGameServer *server;
};

#endif // THOUSANDGAMEQUERYHANDLER_H
