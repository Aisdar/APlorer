// 获取格式为NTFS的磁盘盘符
#ifndef NTFSDATA_H
#pragma execution_character_set("utf-8")
#define NTFSDATA_H

#include "volume.h"
#include <vector>
#include <QDebug>

class NTFSData
{
public:
    NTFSData();
    void initData(QStringList& fileName);
private:
    bool isNTFS(char c);
    bool GetVolumeVector();
    std::vector<Volume> volume_vec;
};

#endif // NTFSDATA_H
