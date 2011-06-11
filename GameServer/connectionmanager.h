/**
* @file connectionmanager.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Файл содержит описание класса менеджера соединений, а также перечисления и структуры,
* которые описывают сокет
*/

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <QObject>
#include <QVector>
#include <QTcpSocket>

/**
* @enum SocketState
* @brief Описывает состояние сокета.
*
* Сокет может находится в двух состояниях:
* 1. По средством данного сокета был отправлен запрос на сервер. Сокет ждет передачи данных
* 2. Запрос еще не отсылался
*/
enum SocketState{
    //! Состояние соединения не определено
    Undefined,
    //! Ожидание передачи запроса
    WaitForQueryTransmission,
    //! Ожидание передачи данных
    WaitForDataTransmission
};

/**
* @struct SocketDesc
* @brief Структура для описания конкретного сокета
*
* Содержит в себе указатель на сокет и его состояние
* @sa SocketState
*/
struct SocketDescr{
    //! Указатель на сокет
    QTcpSocket *socket;
    //! Состояние сокета
    SocketState _mState;
};

/**
* @class ConnectionManager
* @brief Класс для управления существующими подключениями
*/
class ConnectionManager : public QObject
{
    Q_OBJECT
    friend class QueryHandler;
public:
    /**
    * @brief Стандартный конструктор
    * @param parent Указатель на родительский объект
    */
    ConnectionManager(QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    ~ConnectionManager();

    /**
    * @brief Получает состояние указанного сокета
    * @param socket Указатель на сокет, состояние которого необходимо узнать
    * @return Состояние сокета. Возвращает состояние SocketState::Undefined, если указанный сокет не найден
    * @sa SocketState
    */
    SocketState socketState(QTcpSocket *socket) const;

    /**
    * @brief Устанавливает состояние @p state для сокета @p socket
    * @param socket Указатель на сокет, состояние которого необходимо изменить
    * @param state  Состояние сокета, которое необходимо установить
    * @sa SocketState
    */
    void setSocketState(QTcpSocket *socket, SocketState state);

    /**
    * @brief Поиск сокета по указанному дескриптору
    * @param descriptor Дескриптор сокета, который необходимо найти
    * @return Указатель на найденный сокет. Если сокет не найден, возвращает 0
    */
    QTcpSocket* findSocket(int descriptor) const;
public slots:
    /**
    * @brief Слот для добавления соединения в список существующих соединений
    *
    * Добавленный сокет будет находится в состоянии SocketState::WaitForQueryTransmission
    * @param socket Сокет, посредством которого обеспечивается соединение
    */
    void addConnection(QTcpSocket *socket);

    /**
    * @brief Слот для удаления соединения из списка существующих соединений
    * @param socket Сокет, который необходимо удалить из списка
    * @note Слот соединяется с сигналом QAbstractSocket::disconnected()
    */
    void removeConnection(QTcpSocket *socket);
private:
    //! Список сокетов и их состояний для существующих соединений
    QVector<SocketDescr> socketsArray;
};

#endif // CONNECTIONMANAGER_H
