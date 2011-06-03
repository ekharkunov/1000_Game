#include "gameserverfactory.h"
#include "config.h"

QMap<QString, GameServerFactory*> GameServerFactory::factories = QMap<QString, GameServerFactory*>();

GameServerFactory::GameServerFactory(QObject *parent) :
    QObject(parent)
{
}

GameServerFactory::~GameServerFactory() {
}

void GameServerFactory::registerFactory(QString name, int port, GameServerFactory *factory) {
    if (!factories.contains(name)) {
        factories[name] = factory;
        Config::portsForGameServers[name] = port;
    }
}

void GameServerFactory::unregisterFactory(QString name, int port) {
    if (factories.contains(name)) {
        factories.remove(name);
        Config::portsForGameServers.remove(name);
    }
}

QList<QString> GameServerFactory::registeredServer() {
    return factories.keys();
}

void GameServerFactory::unregisterAllFactories() {
    QMap<QString, GameServerFactory*>::iterator it = factories.begin();
    for (; it != factories.end(); ++it)
        delete it.value();
    factories.clear();
}
