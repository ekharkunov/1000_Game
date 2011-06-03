/**
* @file mainserver.h
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QWidget>


/**
* @class MainServer
* @brief Класс, реализующий работу главного сервера
* @note Реализован как синглетон
*/
class MainServer : public QWidget
{
    Q_OBJECT
public:
    /**
    * @brief Метод получения объекта класса MainServer
    * @return Указатель на объект класса MasinServer
    */
    static MainServer* getInstance();

    //! Уничтожает созданный объект класса MainServer
    static void destroy();

    /**
    * @brief Конструктор по умолчанию
    * @param parent Дочерний виджет
    */
    explicit MainServer(QWidget *parent = 0);

    //! Стандарный деструктор
    ~MainServer();

private:
    static MainServer *server;
};

#endif // MAINSERVER_H
