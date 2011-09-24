/**
* @file httpconnection.h
* @brief Файл с описанием класса HTTP соединения
* @author Kharkunov Eugene
* @date 16.09.2011
*/
#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QThread>

class QTcpSocket;
class HttpRequest;
class HttpResponse;

/**
* @class HttpConnection
* @brief Класс, реализующий обработку запросов и подготовку ответов в отдельном потоке
*/
class HttpConnection : public QThread
{
    Q_OBJECT
public:
    /**
    * @brief Конструктор класса, создающий соединение посредством указанного сокета
    * @param socket Сокет, который обеспечивает обмен данными между клиентом и сервером
    * @param name   Имя сервера, для которого создается соединение
    * @param parent Указатель на родительский объект
    */
    explicit HttpConnection(QTcpSocket *socket, QString name, QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    virtual ~HttpConnection();

    /**
    * @brief Метод содержащий в себе исполняемый код потока
    *
    * Происходит обработка запроса, пришедшего от клиента, и формирование соответствующего ответа
    */
    void run();

    /**
    * @brief Получает указатель на сокет, посредством которог обеспечивается передача данных
    * @return Указатель на сокет
    */
    QTcpSocket* socket() const;

private:
    //! Указатель на сокет, обеспечивающий соединение
    QTcpSocket *_mSocket;

    //! Имя сервера, для которого создано данное соединение
    QString _mServerName;

    //! Запрос, пришедший от клиента
    HttpRequest *_mRequest;

    //! Ответ, сформированный на основании данных запроса
    HttpResponse *_mResponse;

signals:
    /**
    * @brief Сигнал, который высылается в случае, если есть данные для чтения
    */
    void readyRead();

    /**
    * @brief Сигнал, который сигнализирует о том, что данные подготовлены к передаче через соединение
    * @param data Данные, для передачи
    */
    void dataReady(QByteArray data);

    /**
    * @brief Сигнал, который высылается, когда вся обработка данных завершена
    * @param res Запрос, пришедший от клиента
    * @param req Ответ, сформированный сервером
    */
    void transactionDone(HttpRequest* req, HttpResponse* res);
};

#endif // HTTPCONNECTION_H
