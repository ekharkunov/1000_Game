/**
* @file httpserver.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Содержит описание класса, реализующего работу HTTP сервера
*/

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>
#include <QString>

class ConnectionManager;
class HttpRequest;
class HttpResponse;

/**
* @class HttpServer
* @brief Реализует модель простейшего Http сервера
* @note Реализован с помощью паттерна "Синглетон"
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
    * @brief Получает объект класса HTTP сервер
    * @return Указатель на объект данного класса
    */
    static HttpServer* getInstance();

    /**
    * @brief Уничтожает объект данного класса
    */
    static void destroy();

    /**
    * @brief Конструктор по умолчанию
    * @param port Номер порта, на который будет прослушиваться сервером
    * @param parent Указатель на родительский объект
    * @note После создания необходим вызов HttpServer::startServer() для запуска сервера
    */
    explicit HttpServer(int port = 80, QObject *parent = 0);

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

    /**
    * @brief Функция, которая получает имя сервера
    * @return Строка, содержащая имя сервера
    */
    QString serverName() const;
private:
    //! Объект данного класса
    static HttpServer* _mInstance;

    //! Состояние сервера
    states currentState;

    //! Менеджер соединений
    ConnectionManager *manager;

    //! Номер порта, который прослушивается сервером
    int mPort;

    //! Имя сервера
    QString _mServerName;
signals:
    /**
    * @brief Сигнал, который высылается в случае возникновения нового сообщения у сервера
    * @param mes Текстовое сообщение, содержащие время события и краткое его описание
    */
    void newMessage(QString mes);
private slots:
    /**
    * @brief Слот, предназначенный для передачи информации по заданному соединению
    * @param data Информация, которую необходимо передать
    */
    void writeData(QByteArray data);

    /**
    * @brief Слот для подтверждения окончания транзакции между клиентом и сервером
    * @param req Запрос, полученный от клиента
    * @param res Ответ, сформированный сервером
    * @note На данном этапе слот содержит в себе лишь вывод данных в лог сервера
    */
    void finishTransaction(HttpRequest* req, HttpResponse* res);
public slots:
    /**
    * @brief Слот для создание нового соединения при запросе подключения
    */
    void addNewConnection();

    /**
    * @brief Слот для обработки принятой от клиента информации
    */
    void readClientInformation();
};

#endif // HTTPSERVER_H
