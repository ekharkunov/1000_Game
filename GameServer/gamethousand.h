/**
* @file gamethousand.h
* @author Kharkunov Eugene
* @date 4.06.2011
* @brief
*/

#ifndef GAMETHOUSAND_H
#define GAMETHOUSAND_H

#include <QThread>
#include <QTcpSocket>
#include "connectionmanager.h"
#include "card.h"

class QFile;

/**
* @class GameThousand
* @brief Класс, реализующий игру в "Тысячу" в отдельном потоке
*/
class GameThousand : public QThread
{
    Q_OBJECT
public:
    /**
    * @brief Конструктор класса
    * @param creater    ID создаваемой игры
    * @param number     Число участников
    * @param time       Продолжительность хода
    * @param parent     Указатель на родительский объект
    */
    explicit GameThousand(UserDescription creater, quint8 number, quint16 time, QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    ~GameThousand();

    /**
    * @brief Добавляет пользователя к игре
    * @param user   Данные о пользователе
    * @return Успешность выполнения операции
    */
    bool addPlayer(UserDescription user);

    /**
    * @brief Получает ID игры
    * @return ID игры(потока)
    */
    quint16 gameID() const;

    /**
    *
    */
    quint16 timeout() const;

    /**
    *
    */
    quint8 playerNumber() const;

    /**
    * @brief
    * @return
    */
    QList<UserDescription>& players();

    /**
    * @brief Обрабатывает процесс игры
    */
    void run();

    /**
    * @brief Подсчет очков в конце розыгрыша
    */
    void calculatePoints();

    /**
    * @brief Перемешивание карт в начале розыгрыша
    */
    void shuffle();

    /**
    * @brief Создает лог игры
    *
    * Лог хранит в себе всю динамику счета. Формируется в конце игры
    * @return Файл, хранящий лог игры. Название файла в виде ДАТА_ИМЕНА УЧАСТНИКОВ.txt
    */
    QFile createLog();
private:
    //! ID игры
    quint16 _mID;
    //! Число игроков
    quint8 _mPlayerNumber;
    //! Продолжительность хода
    quint16 _mTimeout;
    //! ID игрока, который раздает в текущем цикле
    quint16 currentDealer;
    //! Спосок подключенных к данной игре участников
    QList<UserDescription> _mPlayerList;
    //! Список карт, которые на руках в данный момент у игроков(ID игрока, набор карт)
    QMap< quint16, CardPack > mapPlayer2CardSet;
    //! Счет(ID игрока, его динамика счета)
    QMap< quint16, QVector<qint8> > score;
    //! Текущие очки каждого из игроков(ID игрока, очки)
    QMap< quint16, quint8 > currentPoints;
    //! Текущая колода(перемешенная)
    CardPack currentPack;
signals:

public slots:

};

#endif // GAMETHOUSAND_H
