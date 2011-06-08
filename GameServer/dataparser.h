/**
* @file dataparser.h
* @author Kharkunov Eugene
* @date 6.06.2011
*/

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>

class DataParser : public QObject
{
    Q_OBJECT
public:
    explicit DataParser(QObject *parent = 0);

signals:

public slots:

};

#endif // DATAPARSER_H
