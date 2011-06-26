#include "gamethousand.h"
#include <algorithm>

GameThousand::GameThousand(UserDescription creater, quint8 number, quint16 time, QObject *parent) :
    QThread(parent),
    _mID(creater.ConnectionID),
    _mPlayerNumber(number),
    _mTimeout(time)
{
    _mPlayerList.append(creater);
}

GameThousand::~GameThousand() {

}

bool GameThousand::addPlayer(UserDescription user) {
    if (_mPlayerNumber > _mPlayerList.size()) {
        _mPlayerList.append(user);
        return true;
    }
    else return false;
}

quint16 GameThousand::gameID() const {
    return _mID;
}

quint16 GameThousand::timeout() const {
    return _mTimeout;
}

quint8 GameThousand::playerNumber() const {
    return _mPlayerNumber;
}

QList<UserDescription>& GameThousand::players() {
    return _mPlayerList;
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
