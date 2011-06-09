/**
* @file abstractqueryhandler.h
* @author Kharkunov Eugene
* @date 6.06.2011
* @brief
*/

#ifndef ABSTRACTQUERYHANDLER_H
#define ABSTRACTQUERYHANDLER_H

#include <QThread>

/**
* @class QueryHandler
* @brief Класс обработки очереди запросов, поступивших на сервер. Выполняется в отдельном потоке
*/
class AbstractQueryHandler : public QThread
{
    Q_OBJECT
public:
    explicit AbstractQueryHandler(QObject *parent = 0);
    virtual ~AbstractQueryHandler();

    /**
    * @brief Содержит код, который необходимо выполнить при запуске потока
    */
    virtual void run() = 0;
signals:

public slots:

};

#endif // ABSTRACTQUERYHANDLER_H
