/**
* @file gamethousand.h
* @author Kharkunov Eugene
* @date 4.06.2011
*/

#ifndef GAMETHOUSAND_H
#define GAMETHOUSAND_H

#include <QThread>

class GameThousand : public QThread
{
    Q_OBJECT
public:
    explicit GameThousand(QObject *parent = 0);

signals:

public slots:

};

#endif // GAMETHOUSAND_H
