/**
* @file card.h
* @author Kharkunov Eugene
* @date 18.06.2011
* @brief Основные описания игровых карт. Содержит пользовательские типы данных и функции подготовки колоды карт
*/

#ifndef CARD_H
#define CARD_H

#include <QPair>
#include <QVector>

/**
* @enum Suit
* @brief Перечисление содержит масти карт, которым соответствует количество очков, которое начисляется
* за хваль соответствующей масти
*/
enum Suit {
    //! Пустая масть
    EMPTY        = 0,
    //! Пики
    SPADES      = 40,
    //! Трефы
    CLUBS       = 60,
    //! Бубны
    DIAMONDS    = 80,
    //! Червы
    HEARTS      = 100
};

/**
* @enum Value
* @brief Перечисление содержит номиналы карт, участвующих в игре "Тысяча", которым соответствуют
* количества очков, начисляемых за данный номинал
*/
enum Value {
    //! Девятка
    NINE    = 0,
    //! Валет
    JACK    = 2,
    //! Дама
    QUEEN   = 3,
    //! Король
    KING    = 4,
    //! Десятка
    TEN     = 10,
    //! Туз
    ACE     = 11
};

/**
* @typedef QPair<Suit, Value> Card
* @brief Объявление типа "карта"
*/
typedef QPair<Suit, Value> Card;

/**
* @typedef QVector<Card> CardPack
* @brief Объявление типа "колода карт"
*/
typedef QVector<Card> CardPack;

//! Колода карт
static CardPack pack = CardPack();

/**
* @brief Инициализация колоды карт
* @note Обязательна при старте игры. Обратить внимание на синхронизацию при работе с несколькими потоками
*/
static void packInit() {
    if (pack.isEmpty()) {
    pack.push_back(qMakePair(SPADES, NINE));
    pack.push_back(qMakePair(SPADES, JACK));
    pack.push_back(qMakePair(SPADES, QUEEN));
    pack.push_back(qMakePair(SPADES, KING));
    pack.push_back(qMakePair(SPADES, TEN));
    pack.push_back(qMakePair(SPADES, ACE));
    pack.push_back(qMakePair(CLUBS, NINE));
    pack.push_back(qMakePair(CLUBS, JACK));
    pack.push_back(qMakePair(CLUBS, QUEEN));
    pack.push_back(qMakePair(CLUBS, KING));
    pack.push_back(qMakePair(CLUBS, TEN));
    pack.push_back(qMakePair(CLUBS, ACE));
    pack.push_back(qMakePair(DIAMONDS, NINE));
    pack.push_back(qMakePair(DIAMONDS, JACK));
    pack.push_back(qMakePair(DIAMONDS, QUEEN));
    pack.push_back(qMakePair(DIAMONDS, KING));
    pack.push_back(qMakePair(DIAMONDS, TEN));
    pack.push_back(qMakePair(DIAMONDS, ACE));
    pack.push_back(qMakePair(HEARTS, NINE));
    pack.push_back(qMakePair(HEARTS, JACK));
    pack.push_back(qMakePair(HEARTS, QUEEN));
    pack.push_back(qMakePair(HEARTS, KING));
    pack.push_back(qMakePair(HEARTS, TEN));
    pack.push_back(qMakePair(HEARTS, ACE));
    }
}

#endif // CARD_H
