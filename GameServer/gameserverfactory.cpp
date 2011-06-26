#include "gameserverfactory.h"
#include "config.h"

QMap<QString, GameServerFactory*> GameServerFactory::factories = QMap<QString, GameServerFactory*>();

QList<AbstractGameServer*> GameServerFactory::servers = QList<AbstractGameServer*>();

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
        servers.append(factory->createServerInstance());
    }
}

void GameServerFactory::unregisterFactory(QString name) {
    if (factories.contains(name)) {
        factories.remove(name);
        Config::portsForGameServers.remove(name);
        QList<AbstractGameServer*>::iterator it = servers.begin();
        for (; it != servers.end(); ++it)
            if ((*it)->serverName() == name)
                servers.removeOne(*it);
    }
}

QList<AbstractGameServer*> GameServerFactory::registeredServer() {
    return servers;
}

void GameServerFactory::unregisterAllFactories() {
    QMap<QString, GameServerFactory*>::iterator it = factories.begin();
    for (; it != factories.end(); ++it)
        delete it.value();
    factories.clear();
    servers.clear();
}
