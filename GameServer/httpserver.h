/**
* @file httpserver.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Содержит описание класса, реализующего работу HTTP сервера
*/

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>

class ConnectionManager;

/**
* @class HttpServer
* @brief Реализует модель простейшего Http сервера
*/
class HttpServer : public QTcpServer
{
    Q_OBJECT
    /**
    * @enum states
    * @brief Описывает состояния сервера
    */
enum states {Running, NotRunning};
public:
    /**
    * @brief Конструктор по умолчанию
    * @param port Номер порта, на который будет прослушиваться сервером
    * @param parent Указатель на родительский объект
    * @note После создания необходим вызов HttpServer::startServer() для запуска сервера
    */
    explicit HttpServer(int port = 8080, QObject *parent = 0);

    //! Стандартный деструктор
    ~HttpServer();

    /**
    * @brief Проверяет, запущен ли сервер
    * @return Running       Если сервер работает
    *         NotRunning    Если сервер не запущен
    */
    states serverState() const;

    /**
    * @brief Функция, которая осуществляет запуск сервера. В случае возникновения ошибки,
    * появится сообщение со всей необходимой информацией
    * @return true  Если сервер запущен без ошибок
    *         false Если сервер не удалось запустить
    */
    bool startServer();

    /**
    * @brief Остановка запущенного сервера
    */
    void stopServer();

private:
    //! Состояние сервера
    states currentState;

    //! Менеджер соединений
    ConnectionManager *manager;

    //! Номер порта, который прослушивается сервером
    int mPort;
signals:
    /**
    * @brief Сигнал, который высылается при
    * разрыве соединения, которое обеспечивалось посредством @p QTcpSocket
    * @note Высылается в слоте @sa HttpServer::slotConnectionAborted()
    */
    void connectionAborted(QTcpSocket*);
private slots:
    /**
    * @brief Слот, для разрыва установленного соединения
    * @sa ConnectionManager::removeConnection()
    */
    void slotConnectionAborted();

public slots:
    /**
    * @brief Слот для создание нового соединения при запросе подключения
    */
    void addNewConnection();

    /**
    * @brief Сдот для обработки принятой от клиента информации
    */
    void readClientInformation();
};

#endif // HTTPSERVER_H
