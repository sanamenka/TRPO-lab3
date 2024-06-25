#include "calculationbyfiletype.h"

QMap<QString, qint64> CalculationByFileType::calculate(QString directory, QString mapCatalog, int level)
{
    QMap<QString, qint64> map; // map хранит результаты подсчета

    if (!level) // проверяется уровень рекурсии, если 0, то это начальный вызов
    {
        QFileInfo file(directory); // создается объект для указанной директории
        if (file.isFile()) // если это файл
        {
            map.insert(file.suffix(), file.size()); // добавляем запись с расширением и его размером
            return map;
        }
    }

    // основная реализация алгоритма
    if (exists(directory))
    {
        this->cd(directory); // cd - функция QDir перехода в указанную папку

        // перебираем все файлы в папке с помощью foreach
        for (const QFileInfo& file : this->entryInfoList(QDir::Files))
            // если для расширение уже есть запись, то суммируем размер файла с предыдущим значением, если нет - то добавляем новую запись
            map.insert(file.suffix(), map.contains(file.suffix()) ? map.find(file.suffix()).value() + file.size() : file.size());

        // создаем временную QMap для хранения результатов подсчета в подпапках
        QMap<QString, qint64> tempMap;

        //перебираем все подпапки (без учета (.) и (..))
        for (const QString &dir : this->entryList(QDir::NoDotAndDotDot | QDir::Dirs))
        {   // для каждой подпапки рекурсивно вызываем calculate, передаем полный путь, пустой mapCatalog (метод его не учитывает), и уровень рекурсии 1
            tempMap = this->calculate(directory + "\\" + dir, "", 1);

            //перебираем tempMap и суммируем с соответствующими записями в map
            for (auto i = tempMap.cbegin(), end = tempMap.cend(); i != end; ++i)
                map.insert(i.key(), map.contains(i.key()) ? map.find(i.key()).value() + i.value() : i.value());
        }
    }

    // если эот начальный вызов, выполняем cd
    if (!level)
        this->cd(directory);

    return map;
}
