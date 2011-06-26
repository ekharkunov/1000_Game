/**
* @file thousandgamedataparser.h
* @author Kharkunov Eugene
* @date 6.06.2011
* @brief Содержит описание класса, который обрабатывает данные для передачи
*/

#ifndef THOUSANDGAMEDATAPARSER_H
#define THOUSANDGAMEDATAPARSER_H

#include "abstractdataparser.h"

class GameThousand;
class ThousandGameQueryHandler;

/**
* @class ThousandGameDataParser
* @brief Класс, обеспечивающий корректную обработку поступающих данных и подготовку данных для передачи
* клиентам
*/
class ThousandGameDataParser : public AbstractDataParser
{
    Q_OBJECT
public:
    /**
    * @brief Стандартный конструктор
    * @param parentHandler  Указатель на родительский обработчик запросов
    * @param parent         Указатель на родительский объект
    */
    explicit ThousandGameDataParser(ThousandGameQueryHandler *parentHandler, QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    ~ThousandGameDataParser();

    /**
    * @brief Переопределена от AbstractDataParser::inRegistration
    */
    RegistrationData inRegistration(const QByteArray &data);

    /**
    * @brief Переопределена от AbstractDataParser::outRegistration
    */
    QByteArray outRegistration(QVector<QString> &information);

    /**
    * @brief Переопределена от AbstractDataParser::inAuthorization
    */
    AuthorizationData inAuthorization(const QByteArray &data);

    /**
    * @brief Переопределена от AbstractDataParser::outAuthorization
    */
    QByteArray outAuthorization(QVector<QString> &information);

    /**
    * @brief Переопределена от AbstractDataParser::inPlayerStatistics
    */
    QString inPlayerStatistics(const QByteArray &data);

    /**
    * @brief Переопределена от AbstractDataParser::outPlayerStatistics
    */
    QByteArray outPlayerStatistics(const PlayerInformation &data);

    /**
    * @brief Переопределна от AbstractDataParser::outTotalStatistics
    */
    QByteArray outTotalStatistics(QVector<PlayerInformation> &data);

    /**
    * @brief Переопределена от AbstractDataParser::inNewGame
    */
    GameSettings inNewGame(const QByteArray &data);

    /**
    * @brief Формирует выходные данные по запросу списка всех новых игр(ожидающих запуска)
    *
    * Выходной массив формируется в следующем виде:
    *
    * [количество игр N]
    * <br><b>|</b> [ID 1 игры][Текущее количество игроков P]
    * <b>||</b> [Размер ника 1 игрока][Ник 1 игрока]..[Размер ника P игрока][Ник P игрока] <b>||</b>
    * [Допустимое количество игроков в 1 игре][Таймаут хода 1 игры]
    * <br>..
    * <br>[ID N игры][Текущее количество игроков P]
    * <b>||</b> [Размер ника 1 игрока][Ник 1 игрока]..[Размер ника P игрока][Ник P игрока] <b>||</b>
    * [Допустимое количество игроков в N игре][Таймаут хода N игры] <b>|</b>
    * @param list Список игр ожидающих запуска
    * @return Массив байт, в котором размещена готовая для передачи информация
    */
    QByteArray outListAllNewGame(QList<GameThousand*> &list);

    /**
    * @brief Формирует выходные данные по запросу списка всех текущих игр
    *
    * Выходной массив формируется в следующем виде:
    *
    * [количество игр N]
    * <br><b>|</b> [ID 1 игры][Допустимое количество игроков в 1 игре P]
    * <b>||</b> [Размер ника 1 игрока][Ник 1 игрока]..[Размер ника P игрока][Ник P игрока] <b>||</b>
    * [Таймаут хода 1 игры]
    * <br>..
    * <br>[ID N игры][Допустимое количество игроков в N игре P]
    * <b>||</b> [Размер ника 1 игрока][Ник 1 игрока]..[Размер ника P игрока][Ник P игрока] <b>||</b>
    * [Таймаут хода N игры] <b>|</b>
    * @param list Список текущих игр
    * @return Массив байт, в котором размещена готовая для передачи информация
    */
    QByteArray outListAllCurrentGame(QList<GameThousand*> &list);
private:
    //! Указатель на обработчик очереди запросов
    ThousandGameQueryHandler *handler;

signals:

public slots:

};

#endif // THOUSANDGAMEDATAPARSER_H
