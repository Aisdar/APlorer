#ifndef DATA_H
#define DATA_H
#include <QString>
#include <QDateTime>

typedef struct FileInfo {
    QString fileName, type;
    QDateTime changeDate;
    qint64 size;
}FileInfo;

Q_DECLARE_METATYPE(struct FileInfo)

#endif // DATA_H
