/**
* @file httprequest.h
* @brief Файл содержит описание класса, представляющего клиентский HTTP запрос
* @author Kharkunov Eugene
* @date 16.09.2011
*/
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QMap>
#include "httpdefs.h"

/**
* @class HttpRequest
* @brief Класс, реализующий обработку и представление клиентского запроса по протоколу HTTP
* @note Read-only class
*/
class HttpRequest : public QObject
{
    Q_OBJECT
public:
    /**
    * @brief Конструктор класса. В нем происходит разбор строкового запроса с помощью регулярных выражений
    * @param str Строка, содержащая клиентский запрос
    * @param parent Указатель на родительский объект
    */
    explicit HttpRequest(QString str, QObject *parent = 0);

    //! Стандартный деструктор класса
    virtual ~HttpRequest();

    /**
    * @brief Получает запрашиваемый URL
    * @return Строка, содержащая URL запрашиваемого ресурса
    */
    QString url() const;

    /**
    * @brief Получает путь к запрашиваемому ресурсу
    * @return Строка, содержащая путь к ресурсу относительно корневой директории
    * @sa Config::rootDirectory
    */
    QString path() const;

    /**
    * @brief Получает метод протокола
    * @return Метод запроса. В случае неверного либо не поддерживаемого запроса возвращает Method::UNDEFINED
    */
    Method method() const;

    /**
    * @brief Получает протокол, по которому отправлен клиентский запрос
    * @return Название протокола
    * @note Поддерживается только HTTP 1.0, HTTP 1.1
    */
    QString protocol() const;

    /**
    * @brief Получает номер версии протокола
    * @return Версия протокола
    */
    double version() const;

    /**
    * @brief Добавляет разобранные название и значение поля заголовка запроса
    * @param field Название поля заголовка
    * @param value Значение поля заголовка
    */
    void addHeaderValue(QString field, QString value);

    /**
    * @brief Получает значение запрашиваемого поля заголовка
    * @param field Запрашиваемое поле
    * @return Значение данного поля
    */
    QString getHeaderValue(const QString field) const;

    /**
    * @brief Получает строковое представление запроса
    * @return Строковое представление запроса
    */
    QString requestStr() const;

private:
    //! Строковое представление клиентского запроса
    QString _mRequestStr;

    //! Соотношение между полем заголовка и его значением
    QMap<QString, QString> headersField2Value;

    //! Запрашиваемый URL ресурса
    QString _mUrl;

    //! Путь к запрашиваемому ресурсу относительно корневой директории
    QString _mPath;

    //! Метод запроса
    Method _mMethod;

    //! Протокол, по которому осуществляется запрос данных
    QString _mProtocol;

    //! Версия протокола
    double _mVersion;
};

#endif // HTTPREQUEST_H
