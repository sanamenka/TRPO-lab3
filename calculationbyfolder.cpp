#include "calculationbyfolder.h"

QMap<QString, qint64> CalculationByFolder::calculate(QString directory, QString mapCatalog, int level)
{
    QMap<QString, qint64> map; // map хранит результаты подсчета

    if (!level) // проверяется уровень рекурсии, если 0, то это начальный вызов
    {
        QFileInfo file(directory); // создается объект для указанной директории
        if (file.isFile()) // если это файл
        {
            map.insert("Current Folder", file.size()); // в map добавляется запись "Current Folder" с размером файла
            return map;
        }
        mapCatalog = "Current Folder";
    }

    // основная реализация алгоритма
    if (exists(directory))
    {
        map.insert(mapCatalog, 0); //добавляем запись с текущей папкой и размером 0

        this->cd(directory); // cd - функция QDir перехода в указанную папку

        //перебираем все файлы в папке с помощью foreach
        foreach (const QFileInfo& file, this->entryInfoList(QDir::Files))
            // если для текущего ключа mapCatalog есть запись, то суммируем размер файла с предыдущим значением, если нет - то добавляем новую запись
            map.insert(mapCatalog, map.contains(mapCatalog) ? map.find(mapCatalog).value() + file.size() : file.size());

        // создаем временную QMap для хранения результатов подсчета в подпапках
        QMap<QString, qint64> tempMap;

        //перебираем все подпапки (без учета (.) и (..))
        foreach (const QString &dir, this->entryList(QDir::NoDotAndDotDot | QDir::Dirs))
        {   //если это начальный вызов level=0
            if (!level)
            {   // добавляем запись с именем подпапки и размером 0
                map.insert(dir, 0);
                // рекурсивно вызываем calculate для подпапки, передавая полный путь и увеличивая уровень рекурсии. Результат сохраняем в tempMap
                tempMap = this->calculate(directory + "\\" + dir, dir, level + 1);
            }
            // иначе рекурсивно вызываем calculate, но используем текущее имя папки mapCatalog
            else
                tempMap = this->calculate(directory + "\\" + dir, mapCatalog, 2);

            // перебираем tempMap и суммируем с соответствующими записями в map
            for (auto i = tempMap.cbegin(), end = tempMap.cend(); i != end; ++i)
                map.insert(i.key(), map.contains(i.key()) ? map.find(i.key()).value() + i.value() : i.value());
        }
    }
    // если начальный уровень, то выполняем cd
    if (!level)
        this->cd(directory);
    return map;
}
