/**
* @file gameserverfactory.h
* @author Kharkunov Eugene
* @date 2.06.2011
* @brief Содержит описание базового класса фабрики игрового сервера
*/

#ifndef GAMESERVERFACTORY_H
#define GAMESERVERFACTORY_H

#include <QObject>
#include <QMap>
#include "abstractgameserver.h"

/**
* @class GameServerFactory
* @brief Класс абстрактной фабрики для создания и регистрации существующих игровых серверов
*/
class GameServerFactory : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief Стандартный конструктор
    * @param parent Указатель на родительский объект
    */
    explicit GameServerFactory(QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    virtual ~GameServerFactory();

    /**
    * @brief Регистрирует игоровые серверы
    * @param name       Название игрового сервера
    * @param port       Порт игрового сервера
    * @param factory    Фабрика игрового сервера
    */
    static void registerFactory(QString name, int port, GameServerFactory *factory);

    /**
    * @brief Удаляет зарегистрированную фабрику
    * @param name       Название игрового сервера
    */
    static void unregisterFactory(QString name);

    /**
    * @brief Удаляет все зарегистрированные фабрики
    */
    static void unregisterAllFactories();

    /**
    * @brief Возвращает список зарегистрированных фабрик
    * @return Список зарегистрированных серверов
    */
    static QList<AbstractGameServer*> registeredServer();

    /**
    * @brief Создает объект класса игрового сервера
    */
    virtual AbstractGameServer* createServerInstance() = 0;
private:
    //! Массив зарегистрированных фабрик
    static QMap<QString, GameServerFactory*> factories;

    //! Список активных серверов
    static QList<AbstractGameServer*> servers;
signals:

public slots:

};

#endif // GAMESERVERFACTORY_H
