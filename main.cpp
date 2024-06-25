#include <QCoreApplication>
#include <QDir>
#include <cmath>
#include <iostream>
#include <QDebug>
#include <QMap>
#include "calculationstrategy.h"
#include "context.h"
#include "calculationbyfolder.h"
#include "calculationbyfiletype.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string mystring; //строка директории
    CalculationByFolder* byfolder = new CalculationByFolder; // указатель на стратегию по папкам
    CalculationByFileType* byfiletype = new CalculationByFileType; // указатель на стратегию по типам
    Context* calculator = new Context(); // создаем контекст
    QMap<QString, qint64> map; // map хранит результаты вычислений

    // устанавливаем необходимую стратегию
    calculator->setStrategy(byfolder);
    calculator->setStrategy(byfiletype);

    std::cout << "Enter directory for explore" << std::endl;
    std::cin >> mystring;
    //контекст получил вызов и делегировал его объекту конкретной стратегии
    map = calculator->calculate(mystring.c_str()); // c_str() формирует массив строк и возвращает указатель на него

    qint64 globalsize = 0; // в переменной globalsize храним общий размер всех файлов
    foreach (const qint64 value, map.values())
        globalsize += value;

    qDebug() << map; // выводим результат
    qDebug() << Qt::endl;

    // цикл для вывода информации о каждом элементе
    // i - текущий элемент, содержащий ключ и значение. перебираем все элементы map
    for (auto i = map.cbegin(), end = map.cend(); i != end; ++i)
    {
        if (globalsize != 0)
        {
            if ((i.value() * 100000 / globalsize) >= 10) // если >= 0,01%, то выводим с обозначением процентного соотношения
                qDebug() << (i.key()) << ": " <<  round(((double)i.value() * 10000 / globalsize))/100 << "%";
            else // иначе сравниваем с нулем
                if (i.value() != 0)
                    qDebug() << (i.key()) << ": " <<  " < 0.01" << "%"; // если занимается меньше 0,01% выводим информацию об этом
                else
                    qDebug() << (i.key()) << ": " <<  " 0 "; // иначе выводим 0
        }
        else
            qDebug() << (i.key()) << ": " <<  " 0 ";
    }
    qDebug() << Qt::endl;
    return a.exec();
}

