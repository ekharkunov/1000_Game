/**
* @file tablemodel.cpp
* @author Kharkunov Eugene
* @date 27.06.2011
* @brief
*/

#include "tablemodel.h"
#include "gameserverfactory.h"
#include <QDateTime>

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    headerNames.append(tr("Server name"));
    headerNames.append(tr("Status"));
    headerNames.append(tr("Server port"));
    headerNames.append(tr("Start time"));
    headerNames.append(tr("Running time"));
    mRowCount = GameServerFactory::registeredServer().size();
    mColCount = headerNames.size();
    table = new QVariant* [mRowCount];
    for (int i = 0; i < mRowCount; i++)
        table[i] = new QVariant [mColCount];
    for (int i = 0; i < mRowCount; i++)
        for (int j = 0; j < mColCount; j++) {
            AbstractGameServer* server = GameServerFactory::registeredServer().at(i);
            QString str = "";
            switch(j) {
            case 0 : str = server->serverName(); break;
            case 1 : str = !server->serverState() ? tr("Running") : tr("Not running"); break;
            case 2 : str = QString::number(server->serverPort()); break;
            case 3 : str = server->startTime().toString("dd.MM.yyyy hh:mm:ss"); break;
            case 4 : {
                QTime time;
                time = time.addMSecs(server->runningTime());
                str = time.toString("hh:mm:ss");
                break;
            }
            }
            table[i][j] = str;
        }

}

TableModel::~TableModel() {
    for (int i = 0; i < mRowCount; i++) {
        delete []table[i];
        table[i] = 0;
    }
    delete []table;
    table = 0;
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return mColCount;
}

int TableModel::rowCount(const QModelIndex &parent) const {
    return mRowCount;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        table[index.row()][index.column()] = value.toString();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() > mRowCount || index.column() > mColCount)
        return QVariant();
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? table[index.row()][index.column()] : QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal && section <= mColCount)
        return QVariant(headerNames.at(section));
    else if (orientation == Qt::Vertical && section <= mRowCount)
    return QVariant(QString::number(section + 1));
    else return QVariant();
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return (index.isValid() && index.row() <= mRowCount) ? (flags | Qt::ItemIsEditable) : flags;
}
