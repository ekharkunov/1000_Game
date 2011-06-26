/**
* @file abstractgameserver.h
* @author Kharkunov Eugene
* @date 3.06.2011
* @brief Файл содержит описание абстрактного класса, предоставляющего интерфейс для последующей
* реализации игрового сервера
*/
#ifndef ABSTRACTGAMESERVER_H
#define ABSTRACTGAMESERVER_H

#include <QTcpServer>
#include "protocol.h"
#include "abstractdataparser.h"

/**
* @class AbstractGameServer
* @brief Класс предоставляет интерфейс для реализации игрового сервера
*/
class AbstractGameServer : public QTcpServer
{
    Q_OBJECT
protected:
    /**
    * @enum States
    * @brief Перечисление опысывает состояние игрового сервера
    */
    enum States {
        //! Сервер работает
        Running,
        //! Сервер остановлен либо не был запущен
        NotRunning
    };

public:
    /**
    * @brief Стандартный конструктор
    * @param name Имя игрового сервера
    * @param port Номер порта, который будет прослушивать игровой сервер
    * @param parent Указатель на родительский объект
    */
    explicit AbstractGameServer(QString name, int port, QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    virtual ~AbstractGameServer();

    /**
    * @brief Запуск сервера. Должна содержать все необходимые для старта сервера настройки.
    * @return Успешность запуска сервера
    */
    virtual bool startServer() = 0;

    /**
    * @brief Останавливает работающий сервер
    */
    virtual void stopServer() = 0;

    /**
    * @brief Определяет текущее состояние игрового сервера
    * @return Текущее состояние сервера
    */
    virtual States serverState() const = 0;

    /**
    * @brief Возвращает имя сервера
    * @return Имя сервера
    */
    virtual QString serverName() const = 0;

    /**
    * @brief Метод для отправки данных клиенту
    * @param array Данные, которые необходимо переслать
    * @param socket Сокет, по средством которого осуществляется связь с клиентом
    */
    virtual void sendToClient(QByteArray &array, QTcpSocket *socket) = 0;

    /**
    * @brief Инициализация баз данных сервера
    * @return Успешность инициализации всех необходимых БД
    */
    virtual bool initDatabases() = 0;

    /**
    * @brief Закрывает все созданные подключения к БД
    */
    virtual void disconnectDatabases() = 0;

signals:
    //! Сигнал высылается, если в очередь запросов был добавлен новый запрос
    void queryListChanged();

public slots:
    /**
    * @brief Слот для добавления нового соединения с клиентом
    */
    virtual void addNewConnection() = 0;
    /**
    * @brief Слот для постановки запроса, который приходит от клиента, в очередь обработки
    */
    virtual void addRequestQuery() = 0;
};

#endif // ABSTRACTGAMESERVER_H
