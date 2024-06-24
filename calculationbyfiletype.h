#ifndef CALCULATIONBYFILETYPE_H
#define CALCULATIONBYFILETYPE_H
#include <QDir>
#include <QMap>
#include "CalculationStrategy.h"

class CalculationByFileType : public CalculationStrategy
{
public:
    CalculationByFileType():CalculationStrategy() {}
    QMap<QString, qint64> calculate(QString directory, QString mapCatalog, int level);
};


#endif // CALCULATIONBYFILETYPE_H
