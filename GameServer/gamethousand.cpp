#include "gamethousand.h"
#include <algorithm>

GameThousand::GameThousand(UserDescription creater, quint8 number, quint16 time, QObject *parent) :
    QThread(parent),
    _mID(creater.ConnectionID),
    _mPlayerNumber(number),
    _mTimeout(time)
{
    _mPlayerList.append(creater);

    winnerExist = false;
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

    while (!winnerExist) {
        //перемешиваем колоду
        shuffle();

    }
    //создаем лог игры
//    createLog();
}

void GameThousand::shuffle() {
    for (int i = 0; i < pack.size(); i++)
        currentPack.value(i) = pack.at(i);
    std::random_shuffle(currentPack.begin(), currentPack.end());
}

void GameThousand::calculatePoints() {
    QMap<quint16, CardPack>::iterator it = mapPlayer2Trick.begin();
    for (; it != mapPlayer2Trick.end(); ++it) {
        int sum = 0;
        int tempSum = 0;
        quint16 currentPlayerID = it.key();
        // считаем сразу сколько набрал игрок
        CardPack vector = it.value();
        for (int i = 0; i < vector.size(); i++)
            tempSum += vector.at(i).second;
        tempSum += _mPlayerLaud.value(currentPlayerID);
        QVector<qint16> playerScore = score.value(currentPlayerID);
        int prevScore = playerScore.isEmpty() ? 0 : playerScore.last();
        // проверка на факт сидения игрока на бочке
        if (_mBarrelPlayer.contains(currentPlayerID)) {
            if (currentPlayerID != _mWidowBringer) {
                int vecSize = playerScore.size();
                //если три раза не берет прикуп, то -100
                sum = (playerScore.at(vecSize - 1) == playerScore.at(vecSize - 2) &&
                       playerScore.at(vecSize - 2) == playerScore.at(vecSize - 3)) ? -100 : 0;
            }
            //случай, когда игрок взял прикуп и объявил конкретное количество очков(случай бочки)
            else {
                //минимум 100 очков, поэтому если набрал, то будет победителем
                if (tempSum >= _mPointOrdered) {
                    winnerExist = true;
                    _mWinner = currentPlayerID;
                    playerScore.append(1000);
                    continue;
                }
                else sum = 0 - tempSum;
            }
        }
        //случай без бочки
        else {
            if (currentPlayerID != _mWidowBringer) {
                int vecSize = playerScore.size();
                //если три болт, то -100
                sum = (playerScore.at(vecSize - 1) == playerScore.at(vecSize - 2) &&
                       playerScore.at(vecSize - 2) == playerScore.at(vecSize - 3)) ? -100 : tempSum;
            }
            //случай, когда игрок взял прикуп и объявил конкретное количество очков
            else {
                if (tempSum >= _mPointOrdered) sum = _mPointOrdered;
                else sum = 0 - tempSum;
            }
        }
            //производим обнуление очков
            if (_mBarrelPlayer.count(currentPlayerID) && sum == -100)
                playerScore.append(0);
            else playerScore.append(prevScore + sum);
    }
}

void GameThousand::distribute() {

}


void GameThousand::moveCycle() {

}
