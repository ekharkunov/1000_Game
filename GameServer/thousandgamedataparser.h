/**
* @file thousandgamedataparser.h
* @author Kharkunov Eugene
* @date 6.06.2011
* @brief —одержит описание класса, который обрабатывает данные дл€ передачи
*/

#ifndef THOUSANDGAMEDATAPARSER_H
#define THOUSANDGAMEDATAPARSER_H

#include "abstractdataparser.h"

/**
* @class DataParser
* @brief  ласс, обеспечивающий корректную обработку поступающих данных и подготовку данных дл€ передачи
* клиентам
*/
class ThousandGameDataParser : public AbstractDataParser
{
    Q_OBJECT
public:
    explicit ThousandGameDataParser(QObject *parent = 0);

signals:

public slots:

};

#endif // THOUSANDGAMEDATAPARSER_H
