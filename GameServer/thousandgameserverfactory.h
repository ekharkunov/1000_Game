/**
* @file thousandgameserverfactory.h
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#ifndef THOUSANDGAMESERVERFACTORY_H
#define THOUSANDGAMESERVERFACTORY_H

#include "gameserverfactory.h"

class GameServerFactory;

/**
* @class ThousandGameServerFactory
* @brief
*/
class ThousandGameServerFactory : public GameServerFactory
{
public:
    /**
    * @brief Переопределена от GameServerFactory::createServerInstance
    */
    AbstractGameServer* createServerInstance();
};

#endif // THOUSANDGAMESERVERFACTORY_H
