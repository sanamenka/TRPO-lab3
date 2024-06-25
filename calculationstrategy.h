#ifndef CALCULATIONSTRATEGY_H
#define CALCULATIONSTRATEGY_H
#include <QDir>
#include <QMap>

// абстрактный класс CalculationStrategy, определяющий общий интерфейс
class CalculationStrategy : public QDir
{
public:
    CalculationStrategy():QDir() {}
    // виртуальный метод calculate принимает директорию, имя папки по умолчанию "", и уровень вложенности по умолчанию = 0
    virtual QMap<QString, qint64> calculate(QString directory, QString mapCatalog = "", int level = 0) = 0;
};

#endif // CALCULATIONSTRATEGY_H
