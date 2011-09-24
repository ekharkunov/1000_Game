/**
* @file httpresponse.h
* @brief Файл содержит описание класса, представляющего ответ HTTP сервера
* @author Kharkunov Eugene
* @date 16.09.2011
*/
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QObject>
#include <QHash>

//! Таблица, хранящая в себе ассоциации номеров кодов состояния с их словесным описанием
extern QHash<int, QString> STATUS_CODE;

/**
* @macro ADD_CODE
* @brief Макрос для добавления кода состояния ответа сервера и его словесного описания
* @param num Код состояния
* @param status Словесное описание
*/
#define ADD_CODE(num, status) STATUS_CODE.insert(num, status)

class HttpRequest;

/**
* @class HttpResponse
* @brief Класс ответа сервера по протоколу HTTP
*/
class HttpResponse : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief Конструктор класса
    * @param name Имя сервера, который формирует ответ
    * @param parent Указатель на родительский объект
    */
    explicit HttpResponse(QString name, QObject *parent = 0);

    //! Стандартный деструктор
    virtual ~HttpResponse();

    /**
    * @brief Функция подготовки заголовка и тела ответа
    * @param request Клиентский запрос, для которого формируется ответ
    * @param arr     Тело ответа
    */
    void prepareResponse(const HttpRequest &request, QByteArray &arr);

    /**
    * @brief Функция получающая строковое представление ответа сервера
    * @return Строковое представление ответа сервера
    */
    QString responseStr() const;

private:
    //! Имя сервера, формирующего ответ
    QString serverName;

    //! Строковое представление ответа сервера
    QString _mResponseStr;

    /**
    * @brief Функция, реализующая подготовку тела ответа
    * @param filePath Путь к запрашиваемому файлу
    * @param found    Флаг, сигнализирующий о наличии запрашиваемого файла
    * @return Запрашиваемые данные
    * @note В случае отстутствия необходимых данных, возвращается страница с сообщением об ошибке
    */
    QByteArray prepareData(const QString filePath, bool &found);
};

#endif // HTTPRESPONSE_H
