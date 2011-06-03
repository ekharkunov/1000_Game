/**
* @file mainserver.cpp
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#include "mainserver.h"
#include "thousandgameserverfactory.h"

MainServer* MainServer::server = 0;

MainServer* MainServer::getInstance() {
    if (!server)
        server = new MainServer();
    return server;
}

void MainServer::destroy() {
    if(server) {
        delete server;
        server = 0;
    }
}

MainServer::MainServer(QWidget *parent) :
        QWidget(parent) {
    GameServerFactory::registerFactory("Game: 1000", 1000, new ThousandGameServerFactory());
}

MainServer::~MainServer() {
    GameServerFactory::unregisterAllFactories();
}
