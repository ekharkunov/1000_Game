/**
* @file connectionmanager.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Файл содержит описание класса менеджера соединений, а также перечисления и структуры,
* которые описывают конкретного пользователя
*/

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include <QObject>
#include <QList>
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
* @struct UserDescription
* @brief Структура для описания конкретного пользователя
*/
struct UserDescription{
    //! Указатель на сокет
    QTcpSocket *socket;
    //! Состояние сокета
    SocketState _mState;
    //! Ник пользователя, ассоциированный с данным соединением
    QString UserNick;
    //! Флаг авторизации
    bool isAuthorize;
    /**
    * @brief ID пользователя, который он получает при подключении.
    * @note Не следует путать с ID пользователя, который хранится в БД сервера
    * @sa PlayerInformation::ID
    */
    quint16 ConnectionID;
    /**
    * @brief ID игры, к которой подключен пользователь.
    * @note Для пользователя, который создавал игру, его ID, полученный при подключении, совпадает с ID игры
    */
    quint16 GameID;

};

/**
* @class ConnectionManager
* @brief Класс для управления существующими подключениями
*/
class ConnectionManager : public QObject
{
    Q_OBJECT
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

    /**
    * @brief Получает ник пользователя, который ассоциирован с данным соединением
    * @param socket Сокет, посредством которого обеспечивается соединение
    * @return Ник пользователя
    */
    QString userNick(QTcpSocket *socket) const;

    /**
    * @brief Устанавливает ассоциацию указанного ника для данного соединения
    * @param socket     Сокет, посредством которого обеспечивается соединение
    * @param nickName   Новый ник пользователя, который нужно установить
    */
    void setUserNick(QTcpSocket *socket, QString nickName);

    /**
    * @brief Получает признак авторизованности пользователя для данного соединения
    * @param socket Сокет, посредством котороо обеспечивается соединение
    * @return Признак авторизованности пользователя
    */
    bool authorizationFlag(QTcpSocket *socket) const;

    /**
    * @brief Устанавливает флаг авторизации для заданного соединения
    * @param socket Сокет, посредством которого установлено соединение
    * @param flag   Признак авторизации пользователя
    */
    void setAuthorizationFlag(QTcpSocket *socket, bool flag);

    /**
    * @brief Получение информации о пользователе по ID его соединения
    * @param ID ID соединения
    * @return Информация о пользователе
    */
    UserDescription getUserDescription(quint32 ID);
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

    /**
    * @brief Закрывает все существующие соединения и очищает список подключенных пользователей
    */
    void closeAllConnections();
private:
    //! Список пользователей, подключенных к серверу
    QList<UserDescription> userList;
};

#endif // CONNECTIONMANAGER_H
