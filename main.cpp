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

    std::string string;
    CalculationByFolder* byfolder = new CalculationByFolder;
    CalculationByFileType* byfiletype = new CalculationByFileType;
    Context* calculator = new Context(byfolder);
    QMap<QString, qint64> map;
    bool flag = 0;
    while (true) {
        std::cout << "Select strategy: 'folder' , 'type' " << std::endl;
        std::cin >> string;
        if (string == "folder") {
            calculator->setStrategy(byfolder);
            flag = 1;
        }
        if (string == "type") {
            calculator->setStrategy(byfiletype);
            flag = 1;
        }

        if (flag) {
            flag = 0;
            std::cout << "Enter directory" << std::endl;
            std::cin >> string;
            map = calculator->calculate(string.c_str());

            qint64 size = 0;
            foreach (const qint64 value, map.values())
                size += value;

            qDebug() << "Map > " << map.values();
            qDebug() << Qt::endl;
            for (auto i = map.cbegin(), end = map.cend(); i != end; ++i)
            {
                if (size != 0) {
                    if ((i.value() * 100000 / size) >= 10)
                        qDebug() << (i.key()) << ": " <<  round(((double)i.value() * 10000 / size))/100 << "%";
                    else
                        if (i.value() != 0)
                            qDebug() << (i.key()) << ": " <<  " < 0.01" << "%";
                        else
                            qDebug() << (i.key()) << ": " <<  " 0 ";
                }
                else
                    qDebug() << (i.key()) << ": " <<  " 0 ";
            }
            qDebug() << Qt::endl;
        }
    }
    return a.exec();
}





    /*
    calculator->setStrategy(byfolder);
    //calculator->setStrategy(byfiletype);
    std::cout << "Enter directory" << std::endl;
    std::cin >> string;
    map = calculator->calculate(string.c_str());
    qint64 size = 0;
    foreach (const qint64 value, map.values())
        size += value;

    qDebug() << "Map > " << map.values();
    qDebug() << Qt::endl;
    for (auto i = map.cbegin(), end = map.cend(); i != end; ++i)
    {
        if (size != 0) {
            if ((i.value() * 100000 / size) >= 10)
                qDebug() << (i.key()) << ": " <<  round(((double)i.value() * 10000 / size))/100 << "%";
            else
                if (i.value() != 0)
                    qDebug() << (i.key()) << ": " <<  " < 0.01" << "%";
                else
                    qDebug() << (i.key()) << ": " <<  " 0 ";
        }
        else
            qDebug() << (i.key()) << ": " <<  " 0 ";
    }
    qDebug() << Qt::endl;
    return a.exec();
}
*/
