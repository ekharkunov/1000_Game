/**
* @file queryhandler.h
* @author Kharkunov Eugene
* @date 6.06.2011
* @brief Файл содержит описание класса обработки очереди запросов
*/

#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include <QThread>

/**
* @class QueryHandler
* @brief Класс обработки очереди запросов, поступивших на сервер. Выполняется в отдельном потоке
*/
class QueryHandler : public QThread
{
    Q_OBJECT
public:
    explicit QueryHandler(QObject *parent = 0);
    ~QueryHandler();
    void run();
signals:

public slots:

};

#endif // QUERYHANDLER_H
