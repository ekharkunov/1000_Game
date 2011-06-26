/**
* @file mainserver.cpp
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#include "mainserver.h"
#include "thousandgameserverfactory.h"
#include "config.h"
#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>

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
        QMainWindow(parent) {
    //регистрация фабрик игровых серверов
    GameServerFactory::registerFactory("Game: 1000", 1000, new ThousandGameServerFactory());
    createMenus();
    serversList = new QDockWidget(tr("List of registred servers"), this);

    controlButtons = new QDockWidget(tr("Servers control"), this);
    errorMessages = new QDockWidget(tr("Servers errors"), this);
    addDockWidget(Qt::LeftDockWidgetArea, serversList);
    addDockWidget(Qt::BottomDockWidgetArea, errorMessages);
    addDockWidget(Qt::RightDockWidgetArea, controlButtons);
}

MainServer::~MainServer() {
    GameServerFactory::unregisterAllFactories();
    delete serversList;
    delete controlButtons;
    delete errorMessages;
}

void MainServer::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    settingsMenu = menuBar()->addMenu(tr("&Setting"));
    aboutMenu = menuBar()->addMenu(tr("&About"));

    fileMenu->addAction(QIcon(), tr("Close"), this, SLOT(close()));

    settingsMenu->addAction("Choose language", this, SLOT(retranslateApp()));

    aboutMenu->addAction(QIcon(), "About Qt", this, SLOT(aboutQt()));


}

void MainServer::retranslateApp() {

}


void MainServer::aboutQt() {

}
