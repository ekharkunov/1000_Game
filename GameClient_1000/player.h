#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player
{

public:
    explicit Player(QString name);

private:
    QString nick;

};

#endif // PLAYER_H
