/**
* @file tablemodel.h
* @author Kharkunov Eugene
* @date 27.06.2011
* @brief Содержит описание класса для представления данных в виде таблицы
*/

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QContextMenuEvent>

/**
* @class TableModel
* @brief Класс, реализующий модель представления данных в виде таблицы
*/
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /**
    * @brief Стандартный коструктор
    * @param parent Указатель на родительский объект
    */
    explicit TableModel(QObject *parent = 0);

    /**
    * @brief Стандартный деструктор
    */
    virtual ~TableModel();

    /**
    * @brief Возвращает число столбцов для указанного потомка @p parent
    * @param parent Индекс родительского объекта
    * @return Число столбцов
    */
    virtual int columnCount(const QModelIndex &parent) const;

    /**
    * @brief Возвращает число строк для указанного потомка @p parent
    * @param parent Индекс родительского объекта
    * @return Число строк
    */
    virtual int rowCount(const QModelIndex &parent) const;

    /**
    * @brief Возвращает данные содержащиеся по указанному индексу
    * @param index Индекс данных, которые необходимо получить
    * @param role  Роль, которая указывается для хранящихся данных
    * @return Данные, которые храняться по указанному индексу
    */
    virtual QVariant data(const QModelIndex &index, int role) const;

    /**
    * @brief Установка данных
    * @param index Индекс объекта, который будет содержать в ctmt устанавливаемые данные
    * @param value Устанавливаемые данные
    * @param role  Роль для устанавливаемых данных
    * @return Успешность выполнения операции
    */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    /**
    * @brief Получения данных, хранящихся в заголовке таблицы
    * @param section        Номер секции, в которой хранится необходимый заголовок
    * @param orientation    Ориентация выбора(горизонтальная или вертикальная)
    * @param role           Роль, которая указывается для хранящихся данных
    * @return Данные из указанного заголовка
    */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /**
    * @brief Возвращает установленные флаги для объекта с указанным индексом
    * @param index Индекс объекта
    * @return Устаноленные флаги
    */
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    //! Число столбцов
    int mColCount;

    //! Число строк
    int mRowCount;

    //! Данные, которые необходимо представить
    QVariant** table;

    //! Массив заголовков
    QVector<QString> headerNames;
};

#endif // TABLEMODEL_H
