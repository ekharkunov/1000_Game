/**
* @file thousandgameserver.h
* @author Kharkunov Eugene
* @date 3.06.2011
*/
#ifndef THOUSANDGAMESERVER_H
#define THOUSANDGAMESERVER_H

#include <QSqlDatabase>
#include "abstractgameserver.h"
#include "config.h"

class ThousandGameServer : public AbstractGameServer
{
    Q_OBJECT
public:
    explicit ThousandGameServer(int port, QObject *parent = 0);
    virtual ~ThousandGameServer();
    void initDatabases();
    void sendToClient(QByteArray &array, QTcpSocket *socket);
    AbstractGameServer::states serverState() const;
private:
    AbstractGameServer::states state;

public slots:
    void readClientInformation();
};

#endif // THOUSANDGAMESERVER_H
