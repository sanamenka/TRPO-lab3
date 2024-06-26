#include "context.h"

QMap<QString, qint64> Context::calculate(QString directory)
{
    return strategy->calculate(directory);
}

void Context::setStrategy(CalculationStrategy* ptrStrategy)
{
    this->strategy = ptrStrategy;
}
