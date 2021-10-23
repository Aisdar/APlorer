#ifndef COUNTTHEFILESIZEOFEACHCATEGORY_H
#define COUNTTHEFILESIZEOFEACHCATEGORY_H

#include "everythingutil.h"
#include "SearchWindow.h"

#include <QFile>
#include <QDebug>
#include <QVector>

class CountTheFileSizeOfEachCategory
{
public:
    CountTheFileSizeOfEachCategory();
    static void test01() {  }

private:
    QVector<QString> VideoFormat = { "*.mp4",  "*.avi", "*.rm", "*.ev1" };
    QVector<QString> AudioFormat = { "*.mp3", "*.flac", "*.wav" };
    QVector<QString> DocumentFormat = { "*.pdf", "*.doc", "*.docx", "*.ppt",
                                        "*.pptx", "*.xls", "*.xlsx", "*.txt" };
    QVector<QString> ZipFormat = { "*.zip", "*.7z", "*.rar", "*.iso" };
    QVector<QString> PicFormat = { "*.jpg", "*.png", "*.gif", "*.bmp" };

    static qint64 countSize(const QVector<QString>& );
};

#endif // COUNTTHEFILESIZEOFEACHCATEGORY_H
