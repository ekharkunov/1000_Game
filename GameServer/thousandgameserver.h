/**
* @file thousandgameserver.h
* @author Kharkunov Eugene
* @date 3.06.2011
*/
#ifndef THOUSANDGAMESERVER_H
#define THOUSANDGAMESERVER_H

#include <QSqlDatabase>
#include "abstractgameserver.h"

class ConnectionManager;

class ThousandGameServer : public AbstractGameServer
{
    Q_OBJECT
public:
    /**
    * @brief Получает объект класса @class ThousandGameServer
    * @return Объект класса
    */
    static ThousandGameServer* getInstance();

    /**
    * @brief Уничтожает объект класса @class ThousandGameServer
    */
    static void destroy();

    /**
    * @brief Стандартный конструктор
    * @param port Порт, который будет прослушивать сервер
    * @sa Config::portsForGameServers
    */
    explicit ThousandGameServer(int port, QObject *parent = 0);

    /**
    * @brief стандартный деструктор
    */
    virtual ~ThousandGameServer();

    /**
    * @brief Запускает игровой сервер
    * В случае возникновения ошибки появляется сообщение с необходимой информацией о возникшей ошибке
    * @return true  Если сервер запустился
    *         false Если возникла ошибка при старте сервера
    */
    bool startServer();

    /**
    * @brief Останавливает запущенный игровой сервер
    */
    void stopServer();

    /**
    * @brief Инициализация баз данных, в которых хранится вся информация для данного игрового сервера
    */
    bool initDatabases();

    void disconnectDatabases();

    /**
    *
    */
    void sendToClient(QByteArray &array, QTcpSocket *socket);
    AbstractGameServer::states serverState() const;
private:
    static ThousandGameServer* _mInstance;
    int _mPort;
    AbstractGameServer::states state;
    ConnectionManager* _mManager;
    QList<QString> databaseNames;
    QMap<QString, QSqlDatabase> mapName2Database;
//    QSqlDatabase dbUserInfo;
signals:
    void connectionAborted(QTcpSocket*);
private slots:
    void slotConnectionAborted();

public slots:
    void addNewConnection();

    void readClientInformation();
};

#endif // THOUSANDGAMESERVER_H
