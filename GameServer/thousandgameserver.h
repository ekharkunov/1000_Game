/**
* @file thousandgameserver.h
* @author Kharkunov Eugene
* @date 3.06.2011
* @brief Файл содердит описание класса, реализующего работу сервера карточной игры "Тысяча"
*/
#ifndef THOUSANDGAMESERVER_H
#define THOUSANDGAMESERVER_H

#include <QSqlDatabase>
#include <QReadWriteLock>
#include "abstractgameserver.h"

class ConnectionManager;
class QueryHandler;
class QReadWriteLock;

/**
* @class ThousandGameServer
* @brief Класс, реализующий работу сервера карточной игры "Тысяча"
*/
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
    * @brief Стандартный деструктор
    */
    virtual ~ThousandGameServer();

    /**
    * @brief Запускает игровой сервер. Автоматически запускается инициализация баз данных для данного сервера.
    * В случае возникновения ошибки появляется сообщение с необходимой информацией о возникшей ошибке
    * @sa initDatabases()
    * @return <b>true</b>  Если сервер запустился;
    *         <b>false</b> Если возникла ошибка при старте сервера
    */
    bool startServer();

    /**
    * @brief Останавливает запущенный игровой сервер. Разрывает все установленные соединения с клиентами
    * и отключается от присоединенных баз банных
    */
    void stopServer();

    /**
    * @brief Инициализация баз данных, в которых хранится вся информация для данного игрового сервера.
    * БД считается корректно подключенной, если файл по указанному пути существует и БД можно открыть для
    * последующей работы
    * @return <b>true</b>  Если все необходимы БД успешно подключены
    *         <b>false</b> Если во время инициализации произошла ошибка подключения к БД
    */
    bool initDatabases();

    /**
    * @brief чnо-то там
    */
    void disconnectDatabases();

    /**
    *
    */
    void sendToClient(QByteArray &array, QTcpSocket *socket);

    /**
    * @brief
    */
    AbstractGameServer::states serverState() const;
private:
    //! Объект класса ThousandGameServer
    static ThousandGameServer* _mInstance;

    //! Номер порта, на котором осуществляется работа сервера
    int _mPort;

    //! Текущее состояние сервера
    AbstractGameServer::states state;

    //! Менеждер соединений
    ConnectionManager* _mManager;

    //! Очередь запросов от клиентов
    QList<QueryStruct> _mRequestQueries;

    //! Обработчик очереди запросов
    QueryHandler *requestHandler;

    //! Список база данных данного сервера
    QList<QString> databaseNames;

    //! Массив ассоциаций имени БД с ее подключением
    QMap<QString, QSqlDatabase> mapName2Database;

    //!
    QReadWriteLock locker;
signals:
    //! Сигнал высылается в случае разрыва соединения одним из клиентов
    void connectionAborted(QTcpSocket*);

    //! Сигнал высылается, если в очередь запросов был добавлен новый запрос
    void queryListChanged();
private slots:
    //! Слот, определяющий соединение, которое будет разорвано
    void slotConnectionAborted();

public slots:
    /**
    * @brief Слот для добавления нового соединения
    */
    void addNewConnection();

    /**
    * @brief Слот для постановки запроса, который приходит от клиента, в очередь обработки
    */
    void addRequestQuery();
};

#endif // THOUSANDGAMESERVER_H
