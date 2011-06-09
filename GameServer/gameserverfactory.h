/**
* @file gameserverfactory.h
* @author Kharkunov Eugene
* @date 2.06.2011
*/

#ifndef GAMESERVERFACTORY_H
#define GAMESERVERFACTORY_H

#include <QObject>
#include <QMap>


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
    * @param port       Порт игрового сервера с именем @p name
    */
    static void unregisterFactory(QString name, int port);

    /**
    * @brief Удаляет все зарешистрированные фабрики
    */
    static void unregisterAllFactories();

    /**
    * @brief Возвращает список зарегистрированных фабрик
    * @return Список зарегистрированных серверов
    */
    static QList<QString> registeredServer();

    /**
    * @brief Создает объект класса игрового сервера
    */
    virtual void createServerInstance() = 0;
private:
    //! Массив зарегистрированных фабрик
    static QMap<QString, GameServerFactory*> factories;
signals:

public slots:

};

#endif // GAMESERVERFACTORY_H
