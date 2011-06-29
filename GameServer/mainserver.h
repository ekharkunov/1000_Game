/**
* @file mainserver.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Содержит класс главного окна приложения
*/

#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <QtGui/QMainWindow>
#include "httpserver.h"
#include <QItemSelectionModel>

class TableModel;
class QTableView;
class QTextEdit;

/**
* @class MainServer
* @brief Класс, реализующий работу и интерфейс главного сервера
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
    *
    * Содержит в себе также и создание основных действий с их настройками.
    */
    void createMenus();

    //! Объект класса MainServer
    static MainServer *server;

    //! HTTP сервер
    HttpServer *_mHttpServer;

    //! Модель, обеспечивающая работы с выделенными данными
    QItemSelectionModel *selectionModel;

    //! Таймер отвечающий за обновление данных в таблице, в частности за обновление времени работы серверов
    QTimer *timer;

    //! Меню "Файл". Содержит основные действия, связанные с изменением состояния серверов
    QMenu *fileMenu;

    //! Меню "Настройка". Включает в себя настройки серверов
    QMenu *settingsMenu;

    //! Меню "Помощь"
    QMenu *aboutMenu;

    //! Виджет, содержащий информацию о зарегистрированных игровых серверах
    QDockWidget *serversList;

    //! Виджет, содержащий информационные сообщения, возникающие во время работы серверов
    QDockWidget *serversMessages;

    //! Табличная модель представления данных
    TableModel *model;

    //! Виджет для отображение данных в виде таблицы
    QTableView *view;

    //! Содержит информацию о работе серверов
    QTextEdit *messanges;

    QAction *actionStartServer;
    QAction *actionStopServer;
    QAction *actionRestartServer;
    QAction *actionStartAllServers;
    QAction *actionStopAllServers;
    QAction *actionRestartAllServers;
    QAction *actionChangePort;
private slots:
    //! Слот запуска выбранного сервера
    void slotServerStart();

    //! Слот для остановки выбранного сервера
    void slotServerStop();

    //! Слот для перезапуска выбранного сервера
    void slotServerRestart();

    //! Слот для запуска всех доступных серверов
    void slotAllServersStart();

    //! Слот для остановки всех доступных серверов
    void slotAllServersStop();

    //! Слот для перезапуска всех доступных серверов
    void slotAllServersRestart();

    //! Слот для установки нового порта прослушки для выбранного сервера
    void slotSetNewPort();

    //! Слот для реализации выбора языка приложения
    void retranslateApp();

    //! Слот для вызова информации о приложении
    void about();

    /**
    * @brief Слот для обработки выделения данных
    * @param Выделенный диапозон
    * @param Невыделенный диапозон
    */
    void slotSelectionChanged(QItemSelection, QItemSelection);

public slots:
    //! Слот для обновления данных о состояния сервера
    void stateUpdate();

    /**
    * @brief Слот для добавления информационного сообщения о работе сервера
    *
    * Сообщение содержит в себе дату события и имя сервера, которое выслало данное сообщение
    * @param mes Информационное сообщение
    */
    void addServerMessage(QString mes);

    /**
    * @brief Слот для обновления времени работы всех запущенных серверов
    * @note Обновление прекращается в случае отсутствия запущенных серверов
    */
    void updateElapsedTime();
};

#endif // MAINSERVER_H
