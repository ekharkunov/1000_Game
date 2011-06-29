/**
* @file gamethousand.h
* @author Sosnovitch Sergei
* @date 28.06.2011
* @brief класс описывающй игру 1000
*/

#ifndef GAMETHOUSAND_H
#define GAMETHOUSAND_H

#include <QThread>
#include <QTcpSocket>
#include "card.h"
#include "player.h"

/**
* @class GameThousand
* @brief Класс, реализующий игру в "Тысячу" в отдельном потоке
*/
class GameThousand
{

public:
    /**
    * @brief Конструктор класса
    * @param players    список играков
    * @param number     Число участников
    * @param time       Продолжительность хода
    * @param parent     Указатель на родительский объект
    */
    explicit GameThousand(QList<Player> players, quint8 number, quint16 time);

    /**
    * @brief Стандартный деструктор
    */
    ~GameThousand();

    /**
    * @brief Добавляет пользователя к игре
    * @param user   Данные о пользователе
    * @return Успешность выполнения операции
    */
    bool addPlayer(Player user);

    /**
    * @brief Получает ID игры
    * @return ID игры
    */
    quint16 gameID() const;

    /**
    * @brief Устанавливает ID игры
    * @param id      id игры
    */
    void setGameId(quint16 id);

    /**
    * @brief  Получает задержку хода в игре
    * @return Задержка хода в игре
    */
    quint16 timeout() const;

    /**
    * @brief  Устанавливает задержку хода в игре
    * @param  time    задержка хода
    */
    void setTimeout(quint16 time);

    /**
    * @brief  Получает число игроков в игре
    * @return число игроков в игре
    */
    quint8 playerNumber() const;

    /**
    * @brief  Устанавливает число игроков игре
    * @param  number число игроков
    */
    void setPlayerNumber(quint8 number);

    /**
    * @brief  Получает список игроков в игре
    * @return список игроков в игре
    */
    QList<Player>& players();

private:
    //! ID игры
    quint16 ID;
    //! Число игроков
    quint8 PlayerNumber;
    //! Продолжительность хода
    quint16 Timeout;
    //! ID игрока, который раздает в текущем цикле
    quint16 currentDealer;
    //! Спосок подключенных к данной игре участников
    QList<Player> PlayerList;
    //! Текущая колода(перемешенная)
    CardPack currentPack;


};

#endif // GAMETHOUSAND_H
