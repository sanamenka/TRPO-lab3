#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H
#include <QDir>
#include <QMap>

class CalculationStrategy : public QDir
{
public:
    CalculationStrategy():QDir() {}
    virtual QMap<QString, qint64> calculate(QString directory, QString mapCatalog = "", int level = 0) = 0;
};

#endif // CALCULATIONSTRATEGY_H
