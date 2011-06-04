/**
* @file abstractgameserver.h
* @author Kharkunov Eugene
* @date 3.06.2011
*/
#ifndef ABSTRACTGAMESERVER_H
#define ABSTRACTGAMESERVER_H

#include <QTcpServer>

/**
* @class AbstractGameServer
* @brief Класс предоставляет интерфейс для реализации игрового сервера
*/
class AbstractGameServer : public QTcpServer
{
    Q_OBJECT
protected:
    /**
    * @enum states
    * @brief
    */
    enum states {Running, NotRunning};
public:
    /**
    * @brief Стандартный конструктор
    * @param port Номер порта, который будет прослушивать игровой сервер
    * @param parent Дочерний объект
    */
    explicit AbstractGameServer(int port, QObject *parent = 0);

    /**
    * Стандартный деструктор
    */
    virtual ~AbstractGameServer();

    /**
    * @brief
    * @return
    */
    virtual bool startServer() = 0;

    /**
    *
    */
    virtual void stopServer() =0;

    virtual states serverState() const = 0;

    /**
    * @brief Метод для отправки данных клиенту
    * @param array Данные, которые необходимо переслать
    * @param socket Сокет, по средством которого осуществляется связь с клиентом
    */
    virtual void sendToClient(QByteArray &array, QTcpSocket *socket) = 0;

    /**
    * @brief Инициализация баз данных сервера
    */
    virtual bool initDatabases() = 0;

    virtual void disconnectDatabases() = 0;

public slots:

    virtual void addNewConnection() = 0;
    /**
    * Слот для чтения информации, переданной клиентом
    */
    virtual void readClientInformation() = 0;
};

#endif // ABSTRACTGAMESERVER_H
