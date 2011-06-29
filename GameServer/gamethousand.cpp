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
    bool winnerExist = false;
    while (!winnerExist) {
    //перемешиваем колоду
        shuffle();

    }
}

void GameThousand::shuffle() {
    for (int i = 0; i < pack.size(); i++)
        currentPack.value(i) = pack.at(i);
    std::random_shuffle(currentPack.begin(), currentPack.end());
}

void GameThousand::calculatePoints() {
    QMap<quint16, CardPack>::iterator it = mapPlayer2Trick.begin();
    for (; it != mapPlayer2Trick.end(); ++it) {
        CardPack vector = it.value();
        int sum = 0;
        QVector<qint8> playerScore = score.value(it.key());
        if (1) {//что-то связанное с торгами за прикуп
        for (int i = 0; i < vector.size(); i++)
            sum += vector.at(i).second;
        }
        else {

        }
        if (!playerScore.isEmpty()) sum += playerScore.last();
        playerScore.append(sum);
    }
}

void GameThousand::distribute() {

}


void GameThousand::moveCycle() {

}
