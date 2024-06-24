#include "calculationbyfiletype.h"

QMap<QString, qint64> CalculationByFileType::calculate(QString directory, QString mapCatalog, int level)
{
    QMap<QString, qint64> map;

    if (!level) {
        QFileInfo file(directory);
        if (file.isFile()) {
            map.insert(file.suffix(), file.size());
            return map;
        }
    }

    if (exists(directory)) {
        this->cd(directory);
        for (const QFileInfo& file : this->entryInfoList(QDir::Files))
            map.insert(file.suffix(), map.contains(file.suffix()) ? map.find(file.suffix()).value() + file.size() : file.size());

        QMap<QString, qint64> dirMap;
        for (const QString &dir : this->entryList(QDir::NoDotAndDotDot | QDir::Dirs))
        {
            dirMap = this->calculate(directory + "\\" + dir, "", 1);
            for (auto i = dirMap.cbegin(), end = dirMap.cend(); i != end; ++i)
                map.insert(i.key(), map.contains(i.key()) ? map.find(i.key()).value() + i.value() : i.value());
        }
    }

    if (!level)
        this->cd(directory);

    return map;
}
