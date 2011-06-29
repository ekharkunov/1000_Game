#ifndef THOUSANDCLIENT_H
#define THOUSANDCLIENT_H

#include "abstractclient.h"
#include "protocol.h"
#include "thousandclientdataparser.h"

class ThousandClientDataParser;
class ThousandClient : public AbstractClient
{
friend class ThousandClientDataParser;

  Q_OBJECT
public:
    ThousandClient(quint16 port,QString ip="127.0.0.1",QObject *parent = 0);
    //!Функция для присоединения к серверу
    void connectToServer();
    /**
    * @brief Функция изменения адеса сервеа
    * @param ip - ip-адрес сервера
    */
    void setHostAddress(const QString ip);

    /**
    * @brief Функция возвращает указатель на парсер данных
    * @return указатеьл на парсер данных
    */
    ThousandClientDataParser* getDataParser();

public slots:
    //! Слот для обеспечения проверки регистрации и входа в игру
    void serverConnected();
    /**
    * @brief Слот для обработки ошибок соединения
    * @param QAbstractSocket::SocketError - структурка для хранения ошибок
    */
    void connectEror(QAbstractSocket::SocketError);
    /**
    * @brief Слот для отправки данных на сервер
    * @param data - данные для отправки на север
    * @param query - запрос к серверу определяющй тип высылаемых данных
    */
    void sendToServer(QByteArray &data, const QueryType &type);
    //! Слот подготавливает клиент для работы с сервером вызываеться когда сервер присылает данные
    void serverReady();

private:
   //! Сокет для соединения с сервером
   QTcpSocket *connection;
   //! Переменная для хранения адреса сервера
   QHostAddress hostAddress;
   //! Переменная хранящая имя пользователя
   QString *name;
   //! Переменная хранящая ip-адрес сервера
   QString serverIp;
   //! Переменная хранящая пароль пользователя
   QString *password;
   //! Переменная хранящая порт сервера
   quint16 serverPort;
   //! Переменная показывающая установлено ли соединение
   bool connectComplite;
   //! Переменная хранящая размер следйющего блока данных от сервера
   quint16 nextBlocSize;
   //! Переменная указатель на объект ThousandClientDataParser
   ThousandClientDataParser *dataParser;
signals:
   void erorText(QString eror);

};

#endif // THOUSANDCLIENT_H
