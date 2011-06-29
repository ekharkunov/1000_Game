/**
* @file thousandgameserver.h
* @author Kharkunov Eugene
* @date 3.06.2011
* @brief Файл содержит описание класса, реализующего работу сервера карточной игры "Тысяча"
*/
#ifndef THOUSANDGAMESERVER_H
#define THOUSANDGAMESERVER_H

#include <QDateTime>
#include <QSqlDatabase>
#include <QReadWriteLock>
#include "abstractgameserver.h"
#include "connectionmanager.h"

class ThousandGameQueryHandler;
class GameThousand;

/**
* @class ThousandGameServer
* @brief Класс, реализующий работу сервера карточной игры "Тысяча"
*/
class ThousandGameServer : public AbstractGameServer
{
    Q_OBJECT
    friend class ThousandGameQueryHandler;
public:
    /**
    * @brief Получает объект класса
    * @return Объект класса
    */
    static ThousandGameServer* getInstance();

    /**
    * @brief Уничтожает объект класса
    */
    static void destroy();

    /**
    * @brief Стандартный конструктор
    * @param name Имя игрового сервера
    * @param port Порт, который будет прослушивать сервер
    * @param parent Указатель на родительский объект
    * @sa Config::portsForGameServers
    */
    explicit ThousandGameServer(QString name, int port, QObject *parent = 0);

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
    * @brief Закрывает и удаляет все установленные соединения с базами данных
    */
    void disconnectDatabases();

    /**
    * @brief Отсылает информацию клиенту
    * @param array  Данные, которые необходимо отослать
    * @param socket Указатель на сокет, посредством которого установлено соединение с клиентом
    */
    void sendToClient(QByteArray &array, QTcpSocket *socket);

    /**
    * @brief Получение текущего состояния сервера
    * @return Состояние сервера
    * @sa AbstractGameServer::States
    */
    AbstractGameServer::States serverState() const;

    /**
    * @brief Возвращает имя сервера
    * @return Имя сервера
    */
    QString serverName() const;

    /**
    * @brief Возвращает время начало работы сервера
    * @return Денб и время запуска сервера
    */
    QDateTime startTime() const;

    /**
    * @brief Время работы сервера
    * @return Время в милисекундах, прошедшее с начала работы сервера
    */
    quint64 runningTime() const;

    /**
    * @brief Создает новую игру
    * @param creater    Информация о пользователе, который создает игру
    * @param settings   Настройки игры
    * @return Успешность создания
    */
    bool createNewGame(UserDescription creater, GameSettings settings);

    /**
    * @brief Обеспечивает подключение игрока к указанной игре
    * @param gameID ID игры
    * @param user   Информация о пользователе
    * @return Успешность операции
    */
    bool connectToGame(quint16 gameID, UserDescription user);

    /**
    * @brief Установка нового значения для прослушки сервером
    * @param port Новое значение порта
    * @note Для того, чтобы изменения вступили в силу, необходим перезапуск сервера
    */
    void setServerPort(quint16 port);

private:
    /**
    * @brief Поиск игры с указанным @p ID
    * @param list   Указатель на список игр, в котором необходимо произвести поиск
    * @param ID     ID игры
    * @return Указатель на игру. Если игра не найдена возвращает 0
    */
    GameThousand* findGame(QList<GameThousand*> *list, quint16 ID);

    //! Объект класса ThousandGameServer
    static ThousandGameServer* _mInstance;

    //! Имя сервера
    QString _mName;

    //! Номер порта, на котором осуществляется работа сервера
    int _mPort;

    //! Текущее состояние сервера
    AbstractGameServer::States state;

    //! Время старта сервера
    QDateTime _mTimeStart;

    //! Счетчик работы сервера
    QTime *_mTimer;

    //! Менеждер соединений
    ConnectionManager* _mManager;

    //! Очередь запросов от клиентов
    QList<QueryStruct> _mRequestQueries;

    //! Очередь ходов, которые поступают от всех клиентов
    QList<QueryStruct> _mMoveQueries;

    //! Обработчик очереди запросов
    ThousandGameQueryHandler *requestHandler;

    //! Список баз данных данного сервера
    QList<QString> databaseNames;

    //! Массив ассоциаций имени БД с ее подключением
    QMap<QString, QSqlDatabase> mapName2Database;

    //! Блокировщик данных для обеспечения синхронизированного доступа к очереди запросов
    QReadWriteLock locker;

    //! Список созданных игр, которые ожидают начала
    QList<GameThousand*> listNewGame;

    //! Список текущих запущенных игр
    QList<GameThousand*> listCurrentGame;

    //! Массив ассоциаций соединений с сервером
    QMap<QTcpSocket*, QString> mapConnection2Nick;
signals:
    //! Сигнал высылается в случае разрыва соединения одним из клиентов
    void connectionAborted(QTcpSocket*);

    //! Сигнал высылается при добавлении нового запроса в очередь обработки ходов
    void moveListChanged();
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
