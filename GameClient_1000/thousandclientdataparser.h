#ifndef THOUSANDCLIENTDATAPARSER_H
#define THOUSANDCLIENTDATAPARSER_H

#include "abstractdataparser.h"
#include "thousandclient.h"
#include "protocol.h"

class ThousandClient;
class ThousandClientDataParser : public AbstractDataParser
{
    Q_OBJECT
public:
    ThousandClientDataParser(ThousandClient *client,QObject *parent=0);
    /**
    * @defgroup IncommingData Обработка входящих данных
    * Группа методов для обработки поступающих от клиента данных
    * @{
    */
    /**
    * @brief Обработка данных о регистрации нового пользователя
    * @param data Данные о пользователе
    */
    void inRegistration(QByteArray &data);
    /**
    * @brief Обработка данных для авторизации пользователя
    * @param data Данные для авторизации
    */
    void inAuthorization(QByteArray &data);
    /**
    * @brief Обработка данных, необходимых для создания новой игры на сервере
    * @param data Данные для создания игры
    */
    void inNewGame(QByteArray &data);

    void inMessage(QByteArray &data);
    /**
    * @brief Обработка данных о подключении игрока к игре
    * @param data Данные о подключении к созданной игре
    */
    void inConnectToGame(QByteArray &data);
    /**
    * @brief Обработка данных об отключении от игры
    * @param data Данные об отключении игрока от созданной игры(до момента запуска)
    */
    void inDisconnectGame(QByteArray &data);
    /**
    * @brief Обработка данных об отмене созданной игры
    * @param data Данные, содержащие информацию об отмене созданной игры
    */
    void inCancelGame(QByteArray &data);

    void inStartGame(QByteArray &data);

    void inFinishGame(QByteArray &data);
    /**
    * @brief Обработка данных, необходимых для получения сведений об игроке
    * @param data Данные, содержащие информацию, необходимую для получения сведений об игроке
    */
    void inPlayerStatistics(QByteArray &data);

    void inTotalStatistics(QByteArray &data);

    void inMove(QByteArray &data);

    void inListAllGame(QByteArray &data);

    void inListAllNewGame(QByteArray &data);
    /** @}*/

    /**
    * @brief Фукция для обработки входящх данных
    */
    void incomingData();

private:
    //! Указатель на клиент данные которого мы парсим
    ThousandClient *workClient;

public slots:
    /**
    * @defgroup OutcommingData Подготовка данных для отправки
    * Группа методов, предназначенных для подготовке данных, полученных от сервера, к отправке клиентам
    * @{
    */

    /**
    * @brief Подготавливает данные о пользователе для регистрации
    * @param info Данные о зарегистрированном пользователе
    */
    void outRegistration(const RegistrationData &info);
    /**
    * @brief Подготавливает данне об авторзации
    * @param info данные афтаризации пользователя
    */
    void outAuthorization(const AuthorizationData &info);
    /**
    * @brief
    * @param
    */
    void outMessage(const QString &message);
    /**
    * @brief
    * @return
    */
    void outNewGame(const GameSettings &game);
    /**
    * @brief
    * @return
    */
    void outConnectGame(const quint16 &gameID);
    /**
    * @brief
    * @return
    */
    void outDisconnectGame(const quint16 &gameID);
    /**
    * @brief
    * @return
    */
    void outCancelGame(const quint16 &gameID);
    /**
    * @brief
    * @return
    */
    void outStartGame(const quint16 &gameID);
    /**
    * @brief
    * @return
    */
    void outFinishGame(const quint16 &gameID);
    /**
    * @brief
    * @return
    */
    void outListAllGame();
    /**
    * @brief
    * @return
    */
    void outListAllNewGame();
    /**
    * @brief
    * @return
    */
    void outTotalStatistics();
    /**
    * @brief
    * @return
    */
    void outPlayerStatistics(const PlayerInformation &player);
    /**
    * @brief
    * @return
    */
    void outMove(const Card &card);
    /** @}*/

signals:
    //! Сигнал о завершении регистации
    void compliteRegistration(QVector<QString> data);
    //! Синал о завершении авторизации
    void compliteAuthorization(QVector<QString> data);
    //! Сигнал о завешении создания новой игры на сервере
    void compliteNewGame(QDataStream &in);
    //! Сигнал о том что на клиент пришло сообщение
    void compliteMessage(QString message);
    //! Сигнал о том что клиент приссоеденился к игре
    void compliteConnectToGame(QDataStream &in);
    //! Сигнал о том что клиент отсоединился от игры
    void compliteDisconnectGame(QDataStream &in);
    //! Сигнал об успешной отмене созданной игры
    void compliteCancelGame(QDataStream &in);
    //! Сигнал о начале игры
    void compliteStartGame(QDataStream &in);
    //! Сигнал об окончани игры
    void compliteFinishGame(QDataStream &in);
    //! Сигнал передающий статистику играка
    void complitePlayerStatistics(PlayerInformation info);
    //! Сигнал передающий всю статистику игроков
    void compliteTotalStatistics(QVector<PlayerInformation> info);
    //! Сигнал о сделаном ходе
    void compliteMove(Card card);
    //! Сигнал передающий список всех игр
    void compliteListAllGame(QList<GameThousand> list);
    //! Сигнал передающй список всех новых игр
    void compliteListAllNewGame(QList<GameThousand> list);
};

#endif // THOUSANDCLIENTDATAPARSER_H
