/**
* @file thousandgameserverfactory.cpp
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#include "thousandgameserverfactory.h"
#include "thousandgameserver.h"

AbstractGameServer* ThousandGameServerFactory::createServerInstance() {
    return ThousandGameServer::getInstance();
}
