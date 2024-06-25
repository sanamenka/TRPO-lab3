#ifndef CONTEXT_H
#define CONTEXT_H
#include "CalculationStrategy.h"

// Класс Context хранит указатель на объект конкретной стратегии, работая с ним через общий интерфейс стратегии
class Context {
public:
    // конструктор принимает указатель на стратегию и им инициализирует собственный атрибут стратегии
    Context (CalculationStrategy* strategy = nullptr):strategy(strategy) {}

    // метод calculate, который будет вызывать метод конкретной выбранной стратегии
    QMap<QString, qint64> calculate(QString directory);

    // метод setStrategy выбора стратегии
    void setStrategy(CalculationStrategy* ptrStrategy);

private:
    CalculationStrategy* strategy;
};

#endif // CONTEXT_H
