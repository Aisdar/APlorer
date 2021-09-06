#include "countthefilesizeofeachcategory.h"

CountTheFileSizeOfEachCategory::CountTheFileSizeOfEachCategory()
{

}

qint64 CountTheFileSizeOfEachCategory::countSize(const QVector<QString> &vec)
{
    qint64 fileSize { 0 };
    for (const auto& i : vec) {
        fileSize += EveryThingUtil::getCategoryFileSize(i);
    }
    return fileSize;
}
