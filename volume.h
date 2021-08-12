/**
  * 读取磁盘驱动器的USN日志文件
  * NTFS文件格式下每个卷都有自己的USN日志(要求管理员权限 否则GetHandle会返回Error Code 5)
  * ref:
  * http://atr.pub/2016/04/16/NTFS-USN/
  * https://blog.csdn.net/gigggg/article/details/103846103
  * https://stackoverflow.com/questions/46978678/walking-the-ntfs-change-journal-on-windows-10
  * https://docs.microsoft.com/en-us/windows/win32/fileio/walking-a-buffer-of-change-journal-records
  */
#ifndef VOLUME_H
#define VOLUME_H

#include <Windows.h>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <unordered_map>
#include <QFile>
#include <vector>

struct PFRN_Name {
    DWORDLONG ParentFileReferenceNumber;
    QString FileName;
};
using FrnPfrnNameMap = std::unordered_map<DWORDLONG, PFRN_Name>;

class Volume
{
public:
    Volume(char v): m_volume(v), hVol(nullptr) {}
    void test01() { GetHandle(); CreateUSN(); GetUSNInfo();
                    ReadUSNJournal();
                                DeleteUSN();
                  QString test, test2 = "200000000f6bb"; bool ok;
                              GetFilePathByFrn(test2.toLongLong(&ok, 16), test); qDebug() << test << endl; }

    bool InitVolumeInformation() {
        return GetHandle() && CreateUSN() && GetUSNInfo() && ReadUSNJournal();
    }
    std::vector<QString> fileNameVec;
    std::multimap<QString, DWORDLONG> fileNameFrnMap;

private:
    bool GetHandle();          // 获取磁盘驱动器句柄
    bool CreateUSN();          // 初始化USN日志文件
    bool GetUSNInfo();         // 获取USN日志信息
    bool ReadUSNJournal();     // 读取USN日志的所有数据
    bool ReadUSNJournal_test();// 读取USN日志的所有数据
    bool DeleteUSN();          // 删除USN日志文件

    bool GetFileFrnByName(const QString&, std::vector<DWORDLONG>&); // 依据文件名获取(多个)frn
    bool GetFilePathByFrn(DWORDLONG, QString&);     // 依据frn获取文件的完整路径

    char m_volume;             // 磁盘驱动器盘符
    HANDLE hVol;               // 磁盘驱动器句柄
    CREATE_USN_JOURNAL_DATA created_usn_data;  // 创建缓冲区
    USN_JOURNAL_DATA JournalData;
    PFRN_Name pfrn_name;
    FrnPfrnNameMap frnPfrnNameMap;

};

#endif // VOLUME_H
