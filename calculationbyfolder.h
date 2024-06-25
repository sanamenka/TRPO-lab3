#ifndef CALCULATIONBYFOLDER_H
#define CALCULATIONBYFOLDER_H
#include <QDir>
#include <QMap>
#include "CalculationStrategy.h"

class CalculationByFolder : public CalculationStrategy
{
public:
    CalculationByFolder():CalculationStrategy() {};

    // алгоритм подсчета объема в процентах, который занимают файлы и папки верхнего уровня
    QMap<QString, qint64> calculate(QString directory, QString mapCatalog, int level);
};

#endif // CALCULATIONBYFOLDER_H
