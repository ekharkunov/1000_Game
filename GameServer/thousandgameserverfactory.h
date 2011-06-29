/**
* @file thousandgameserverfactory.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Содержит описание фабрики для игрового сервера "Тысяча"
*/

#ifndef THOUSANDGAMESERVERFACTORY_H
#define THOUSANDGAMESERVERFACTORY_H

#include "gameserverfactory.h"

class GameServerFactory;

/**
* @class ThousandGameServerFactory
* @brief Класс фабрики игрового сервера "Тысяча"
*/
class ThousandGameServerFactory : public GameServerFactory
{
public:
    /**
    * @brief Переопределена от GameServerFactory::createServerInstance
    *
    * Создание ссущности сервера
    */
    AbstractGameServer* createServerInstance();
};

#endif // THOUSANDGAMESERVERFACTORY_H
