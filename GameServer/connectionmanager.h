/**
* @file connectionmanager.h
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <QObject>
#include <QVector>
#include <QTcpSocket>

/**
* @class ConnectionManager
* @brief Класс для управления существующими подключениями
*/
class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief Функция получения существующего объекта данного класса
    * @return Объект класса @class ConnectionManager
    */
    static ConnectionManager* getInstance();

    /**
    * @brief Уничтожение объекта
    */
    static void destroy();

    /**
    * @brief Стандартный конструктор
    * @param parent Дочерний объект
    */
    ConnectionManager(QObject *parent = 0);
public slots:
    /**
    * @brief Слот для добавления соединения в список существующих соединений
    * @param socket Соке, посредством которого обеспечивается соединение
    */
    void addConnection(QTcpSocket *socket);

    /**
    * @brief Слот для удаления соединения из списка существующих соединений
    * @param socket Сокет, который необходимо удалить из списка
    * @note Слот соединяется с сигналом @sa QAbstractSocket::disconnected()
    */
    void removeConnection(QTcpSocket *socket);
private:
    //! Уrазатель на объект класса @class ConnectionManager
    static ConnectionManager* _mManager;

    //! Список сокетов для существующих соединений
    QVector<QTcpSocket*> socketsArray;
};

#endif // CONNECTIONMANAGER_H
