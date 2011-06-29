#include "gamethousand.h"
#include <algorithm>

GameThousand::GameThousand(QList<Player> players, quint8 number, quint16 time)
{
    PlayerList=players;
    PlayerNumber=number;
    Timeout=time;
}

GameThousand::~GameThousand() {

}

bool GameThousand::addPlayer(Player user) {
   if (PlayerNumber > PlayerList.size()) {
        PlayerList.append(user);
        return true;
   }
    else return false;
}

quint16 GameThousand::gameID() const {
    return ID;
}

quint16 GameThousand::timeout() const {
    return Timeout;
}

quint8 GameThousand::playerNumber() const {
    return PlayerNumber;
}

QList<Player>& GameThousand::players() {
    return PlayerList;
}

void GameThousand::setGameId(quint16 id)
{
    ID=id;
}

void GameThousand::setPlayerNumber(quint8 number)
{
    PlayerNumber=number;
}

void GameThousand::setTimeout(quint16 time)
{
     Timeout=time;
}


