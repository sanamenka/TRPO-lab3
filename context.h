#ifndef CONTEXT_H
#define CONTEXT_H
#include "CalculationStrategy.h"

class Context {
public:
    Context (CalculationStrategy* method = nullptr):strategy(strategy) {}

    QMap<QString, qint64> calculate(QString directory);
    void setStrategy(CalculationStrategy* ptrmethod);

private:
    CalculationStrategy* strategy;
};

#endif // CONTEXT_H
