/**
* @file abstractClient.h
* @brief Заголовочный файл класса AbstractClient
*/
#ifndef ABSTRACTCLIENT_H
#define ABSTRACTCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "protocol.h"


/**
* @class AbstractClient
* @brief Реализует модель клиента для произвольной игры
*/
class AbstractClient : public QObject
{
    Q_OBJECT
public:
  /**
  * @brief Конструктор класса для модели клиента
  * @param parent Указатель на дочерний объект
  */
  explicit AbstractClient(QObject *parent = 0);

    virtual ~AbstractClient();

  //!Функция для присоединения к серверу
  virtual void connectToServer() = 0;
  /**
  * @brief Функция изменения адеса сервеа
  * @param ip - ip-адрес сервера
  */
  virtual void setHostAddress(const QString ip) = 0;

signals:

public slots:
  //! Слот для обеспечения проверки регистрации и входа в игру
  virtual void serverConnected() = 0;
  /**
  * @brief Слот для обработки ошибок соединения
  * @param QAbstractSocket::SocketError - структурка для хранения ошибок
  */
  virtual void connectEror(QAbstractSocket::SocketError) = 0;
  /**
  * @brief Слот для отправки данных на сервер
  * @param data - данные для отправки на север
  * @param query - запрос к серверу определяющй тип высылаемых данных
  */
  virtual void sendToServer(QByteArray &data,const QueryType &query) = 0;
  //! Слот подготавливает клиент для работы с сервером вызываеться каждый раз когда сервер высылает данные
  virtual void serverReady() = 0;

};

#endif // ABSTRACTCLIENT_H
