/**
* @file mainserver.h
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QtGui/QMainWindow>

/**
* @class MainServer
* @brief Класс, реализующий работу главного сервера
* @note Реализован как синглетон
*/
class MainServer : public QMainWindow
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
    * @param parent Указатель на родительский виджет
    */
    explicit MainServer(QWidget *parent = 0);

    //! Стандарный деструктор
    ~MainServer();

private:
    /**
    * @brief Создание меню
    */
    void createMenus();
    //! Объект класса MainServer
    static MainServer *server;

    //!
    QMenu *fileMenu;
    QMenu *settingsMenu;
    QMenu *aboutMenu;

    QDockWidget *serversList;
    QDockWidget *controlButtons;
    QDockWidget *errorMessages;
private slots:
    void retranslateApp();
    void aboutQt();
};

#endif // MAINSERVER_H
