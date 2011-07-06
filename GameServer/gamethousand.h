/**
* @file gamethousand.h
* @author Kharkunov Eugene
* @date 4.06.2011
* @brief Содержит описание класса, реализующего игру "Тысяча"
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
    * @brief Возвращает ID игры
    * @return ID игры(потока)
    */
    quint16 gameID() const;

    /**
    * @brief Возвращает время, которое отводится игроку для совершения хода
    * @return Время в секундах. Имеет дискретный ограниченный набор значений
    */
    quint16 timeout() const;

    /**
    * @brief Возвращает количество игроков, на которое расчитана данная игра.
    * @return Число игроков. Может принимать значения от 2 до 4
    */
    quint8 playerNumber() const;

    /**
    * @brief Возвращает список участников данной игры
    * @return Список участников
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

    //! Количество прикупов
    quint8 _mWidowCount;

    //! Количество карт в каждом прикупе
    quint8 _mWidowCardCount;

    //! Число игроков
    quint8 _mPlayerNumber;

    //! Спосок подключенных к данной игре участников
    QList<UserDescription> _mPlayerList;

    //! ID игрока, который раздает в текущем цикле
    quint16 _mCurrentDealer;

    //! Флаг, показывающий, пропускает ли текущий розыгрыш игрок, который был раздающим
    bool _mDealerMissingMove;

    //! ID игрока, который забрал прикуп
    quint16 _mWidowBringer;

    //! Количество очков, объявленных за прикуп
    quint8 _mPointOrdered;

    //! Количество очков, которые игроки получили за хвали в текущей раздаче
    QMap<quint16, quint8> _mPlayerLaud;

    //! Текущая козырая масть
    Suit _mTrumpSuit;

    /**
    * @brief Список игроков на бочке. В него добавляются подряд ID, когда игрок достигает 900 очков.
    * Когда в списке встречается 3 раза один и тот же ID, то очки игрока обнуляются(3 раза слетел с бочки)
    */
    QList<quint16> _mBarrelPlayer;

    //! Продолжительность хода
    quint16 _mTimeout;

    //! Флаг наличия победителя
    bool winnerExist;

    //! Победеитель
    quint16 _mWinner;

    //! Список карт, которые на руках в данный момент у игроков(ID игрока, набор карт)
    QMap< quint16, CardPack > mapPlayer2CardSet;

    //! Список взяток, которые получает каждый из игроков в течении раздачи(ID игрока, набор карт)
    QMap< quint16, CardPack > mapPlayer2Trick;

    //! Счет(ID игрока, его динамика счета)
    QMap< quint16, QVector<qint16> > score;
    //! Текущие очки каждого из игроков(ID игрока, очки)
    QMap< quint16, qint8 > currentPoints;
    //! Текущая колода(перемешенная)
    CardPack currentPack;

    //! Раздача карт по игрокам и по прикупам
    void distribute();

    //! Обработка одного цикла ходов
    void moveCycle();
signals:

public slots:

};

#endif // GAMETHOUSAND_H
