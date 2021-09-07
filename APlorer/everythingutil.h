#ifndef EVERYTHINGUTIL_H
#define EVERYTHINGUTIL_H

#include "Everything.h"

#include <QList>
#include <QFileInfo>
#include <QMutex>
#include <QDir>
#include <QVector>
#include <QProcess>
#include <QThread>

class EveryThingUtil
{
public:
    EveryThingUtil();
    static void openEverything();
    static QVector<QFileInfo> Search(const QString& str, bool reg=false);
    static QString getSearchErrorString();
    static qint64 getCategoryFileSize(const QString& str, bool reg=false);
};

#endif // EVERYTHINGUTIL_H
