#include "gamethousand.h"
#include <algorithm>

GameThousand::GameThousand(UserDescription creater, quint8 number, quint16 time, QObject *parent) :
    QThread(parent),
    ID(creater.ConnectionID),
    playerNumber(number),
    timeout(time)
{
    playerList.append(creater);
}

GameThousand::~GameThousand() {

}

bool GameThousand::addPlayer(UserDescription user) {
    if (playerNumber > playerList.size()) {
        playerList.append(user);
        return true;
    }
    else return false;
}

quint16 GameThousand::gameID() const {
    return ID;
}

void GameThousand::run() {

}

void GameThousand::shuffle() {
    for (int i = 0; i < pack.size(); i++)
        currentPack.value(i) = pack.at(i);
    std::random_shuffle(currentPack.begin(), currentPack.end());
}

void GameThousand::calculatePoints() {

}
