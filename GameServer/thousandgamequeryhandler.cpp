#include "thousandgamequeryhandler.h"
#include "thousandgameserver.h"

ThousandGameQueryHandler::ThousandGameQueryHandler(ThousandGameServer *parentServer, QObject *parent) :
    AbstractQueryHandler(parent),
    server(parentServer)
{
}

void ThousandGameQueryHandler::run() {

}
