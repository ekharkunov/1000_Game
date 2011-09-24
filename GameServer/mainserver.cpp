/**
* @file mainserver.cpp
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief ‘айл содержит реализацию методов класса главного сервера
*/

#include "mainserver.h"
#include "thousandgameserverfactory.h"
#include "config.h"
#include "tablemodel.h"
#include <QMap>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QMessageBox>
#include <QTableView>
#include <QTextEdit>
#include <QDateTime>
#include <QInputDialog>
#include <QTimer>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTranslator>

//! —писок поддерживаемых €зыков
static QStringList langList = QStringList() << "English"
                                            << "Russian";

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
    //регистраци€ фабрик игровых серверов
    GameServerFactory::registerFactory("Game: 1000", 1000, new ThousandGameServerFactory());

    createMenus();

    _mHttpServer = new HttpServer(Config::portForHttpServer);
    connect(_mHttpServer, SIGNAL(newMessage(QString)), this, SLOT(addHttpServerLog(QString)));

    timer = new QTimer(this);

    serversList = new QDockWidget(tr("List of registred servers"), this);
    serversList->setFeatures(QDockWidget::NoDockWidgetFeatures);
    serversMessages = new QDockWidget(tr("Servers messages"), this);
    serversMessages->setFeatures(QDockWidget::NoDockWidgetFeatures);

    addDockWidget(Qt::LeftDockWidgetArea, serversList);
    addDockWidget(Qt::BottomDockWidgetArea, serversMessages);

    model = new TableModel();
    view = new QTableView(serversList);
    view->setModel(model);
    selectionModel = view->selectionModel();
    serversList->setWidget(view);

    tabArea = new QTabWidget();
    serversMessages->setWidget(tabArea);
    QTextEdit *http = new QTextEdit();
    http->setReadOnly(true);
    tabArea->addTab(http, "HTTP Server");
    messages["HTTP Server"] = http;

    QList<AbstractGameServer*> list = GameServerFactory::registeredServer();
    for(int i = 0; i < list.size(); i++) {
        AbstractGameServer* server = list.at(i);
        connect(server, SIGNAL(newServerMessage(QString)), this, SLOT(addServerMessage(QString)));
        connect(server, SIGNAL(stateChanged()), this, SLOT(stateUpdate()));

        QTextEdit *edit = new QTextEdit();
        edit->setReadOnly(true);
        tabArea->addTab(edit, server->serverName());
        messages[server->serverName()] = edit;
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(updateElapsedTime()));
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(slotSelectionChanged(QItemSelection,QItemSelection)));
    _mHttpServer->startServer();
}

MainServer::~MainServer() {
    GameServerFactory::unregisterAllFactories();
    _mHttpServer->stopServer();
    delete _mHttpServer;
    delete timer;
    delete serversList;
    delete serversMessages;
    delete model;
    delete view;
    delete selectionModel;

    delete fileMenu;
    delete settingsMenu;
    delete aboutMenu;

    delete actionStartServer;
    delete actionStopServer;
    delete actionRestartServer;
    delete actionStartAllServers;
    delete actionStopAllServers;
    delete actionRestartAllServers;
    delete actionChangePort;
}

void MainServer::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    actionStartServer = fileMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/start.png"),
                                            tr("Start server"),
                                            this,
                                            SLOT(slotServerStart()));
    actionStartServer->setEnabled(false);
    actionStopServer = fileMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/stop.png"),
                                           tr("Stop server"),
                                           this,
                                           SLOT(slotServerStop()));
    actionStopServer->setEnabled(false);
    actionRestartServer = fileMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/restart.png"),
                                              tr("Restart server"),
                                              this,
                                              SLOT(slotServerRestart()));
    actionRestartServer->setEnabled(false);
    fileMenu->addSeparator();
    actionStartAllServers = fileMenu->addAction(tr("Start all servers"),
                                                this,
                                                SLOT(slotAllServersStart()));
    actionStopAllServers = fileMenu->addAction(tr("Stop all servers"),
                                               this,
                                               SLOT(slotAllServersStop()));
    actionRestartAllServers = fileMenu->addAction(tr("Restart al servers"),
                                                  this,
                                                  SLOT(slotAllServersRestart()));
    fileMenu->addSeparator();
    fileMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/quit.png"),
                        tr("Close"),
                        this,
                        SLOT(close()));

    settingsMenu = menuBar()->addMenu(tr("&Setting"));
    actionChangePort = settingsMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/change_port.png"),
                                               tr("Set new port"),
                                               this,
                                               SLOT(slotSetNewPort()));
    actionChangePort->setEnabled(false);
    settingsMenu->addSeparator();
    settingsMenu->addAction(tr("Choose language"), this, SLOT(retranslateApp()));

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/about.png"),
                         tr("About..."),
                         this,
                         SLOT(about()));
    aboutMenu->addAction(QIcon(Config::pathIcons.absolutePath() + "/about_qt.png"),
                         tr("About Qt"),
                         qApp,
                         SLOT(aboutQt()));
}

void MainServer::retranslateApp() {
    QDialog dlg;
    QLabel lbl(tr("Choose language:"), &dlg);
    QComboBox box(&dlg);
    box.addItems(langList);
    QPushButton buttonOk("Ok", &dlg);
    connect(&buttonOk, SIGNAL(clicked()), &dlg, SLOT(accept()));
    QVBoxLayout layout;
    layout.addWidget(&lbl);
    layout.addWidget(&box);
    layout.addWidget(&buttonOk);
    dlg.setLayout(&layout);
    if (dlg.exec() == QDialog::Accepted) {
        int index = box.currentIndex();
        QString langStr = Config::pathTranslations.absolutePath();
        switch (index) {
        case 0 : langStr += "/lang_en_EN"; break;
        case 1 : langStr += "/lang_ru_RU"; break;
        }
        QTranslator trans;
        trans.load(langStr);
        qApp->installTranslator(&trans);
    }
}

void MainServer::about() {
    QMessageBox::about(this, tr("About Game Server"),
                       QString(tr("Author: Kharhunov Eugene\n"
                                  "Version: 0.1.0")));
}

void MainServer::stateUpdate() {
    AbstractGameServer *server= static_cast<AbstractGameServer*>(sender());
    int row = GameServerFactory::registeredServer().indexOf(server);
    if (row == -1) {
        row = selectionModel->selectedIndexes().at(0).row();
        server = GameServerFactory::registeredServer().at(row);
    }
    int state = server->serverState();
    QString strState = "";
    QModelIndex indx;
    indx = model->index(row, 3);
    model->setData(indx, server->startTime().toString("dd.MM.yyyy hh:mm:ss"), Qt::EditRole);
    indx = model->index(row, 4);
    QTime time(0, 0, 0, 0);
    time = time.addMSecs(server->runningTime());
    model->setData(indx, time.toString("hh:mm:ss"), Qt::EditRole);
    switch (state) {
    case 0 : {
        strState = tr("Running");
        actionStartServer->setEnabled(false);
        actionStopServer->setEnabled(true);
        timer->start(1000);
        break;
    }
    case 1 : {
        strState = tr("Not running");
        actionStartServer->setEnabled(true);
        actionStopServer->setEnabled(false);
        break;
    }
    }
    indx = model->index(row, 1);
    model->setData(indx, strState, Qt::EditRole);
    indx = model->index(row, 2);
    model->setData(indx, server->serverPort(), Qt::EditRole);
}

void MainServer::slotServerStart() {
    QModelIndexList list = selectionModel->selectedIndexes();
    //берем строку, в которой находитс€ перва€ выделенна€ €чейка
    quint16 row = list.at(0).row();
    GameServerFactory::registeredServer().at(row)->startServer();
}

void MainServer::slotServerStop() {
    QModelIndexList list = selectionModel->selectedIndexes();
    //берем строку, в которой находитс€ перва€ выделенна€ €чейка
    quint16 row = list.at(0).row();
    AbstractGameServer* server = GameServerFactory::registeredServer().at(row);
    server->stopServer();
}

void MainServer::slotServerRestart() {
    slotServerStop();
    slotServerStart();
}

void MainServer::slotAllServersStart() {
    QList<AbstractGameServer*> list = GameServerFactory::registeredServer();
    QList<AbstractGameServer*>::iterator it = list.begin();
    for (; it != list.end(); ++it)
        if ((*it)->serverState() == AbstractGameServer::NotRunning)
            (*it)->startServer();
}

void MainServer::slotAllServersStop() {
    QList<AbstractGameServer*> list = GameServerFactory::registeredServer();
    QList<AbstractGameServer*>::iterator it = list.begin();
    for (; it != list.end(); ++it)
        if ((*it)->serverState() == AbstractGameServer::Running)
            (*it)->stopServer();
}

void MainServer::slotAllServersRestart() {
    slotAllServersStop();
    slotAllServersStart();
}

void MainServer::slotSetNewPort() {
    QModelIndexList list = selectionModel->selectedIndexes();
    //берем строку, в которой находитс€ перва€ выделенна€ €чейка
    quint16 row = list.at(0).row();
    AbstractGameServer* server = GameServerFactory::registeredServer().at(row);
    bool ok;
    quint16 newPort = QInputDialog::getInt(this,
                                           tr("Setting a new server port"),
                                           tr("Input a new port for listening(maximum value is 9999).\n"
                                              "The server wil be restarted automatically."),
                                           server->serverPort(),
                                           1,
                                           9999,
                                           1,
                                           &ok);
    if (ok) {
    server->setServerPort(newPort);
    Config::portsForGameServers[server->serverName()] = newPort;
    server->stopServer();
    server->startServer();
    }
}

void MainServer::addServerMessage(QString mes) {
    QString str = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ");
    AbstractGameServer* server = static_cast<AbstractGameServer*> (sender());
    str.append(mes + "\n");
    messages.value(server->serverName())->append(str);
}

void MainServer::addHttpServerLog(QString mes) {
    QString str = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ");
    str.append(mes + "\n");
    messages.value("HTTP Server")->append(str);
}

void MainServer::updateElapsedTime() {
    bool startFlag = false;
    QList<AbstractGameServer*> list = GameServerFactory::registeredServer();
    for (int i = 0; i < list.size(); i++)
        if (list.at(i)->serverState() == AbstractGameServer::Running) {
            startFlag = true;
            QModelIndex indx = model->index(i, 4);
            QTime time(0, 0, 0, 0);
            time = time.addMSecs(list.at(i)->runningTime());
            model->setData(indx, time.toString("hh:mm:ss"), Qt::EditRole);
        }
    if(startFlag) timer->start(1000);
}

void MainServer::slotSelectionChanged(QItemSelection selection, QItemSelection deselection) {
    bool enabledFlag = false;
    enabledFlag = selection.indexes().isEmpty() ? false : true;
    actionStartServer->setEnabled(enabledFlag);
    actionStopServer->setEnabled(enabledFlag);
    actionRestartServer->setEnabled(enabledFlag);
    actionChangePort->setEnabled(enabledFlag);
    if (enabledFlag) stateUpdate();
}
