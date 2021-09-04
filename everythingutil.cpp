/**
  * 通过进程间通信调用Everything实现文件管理器的查询功能
  */
#pragma execution_character_set("utf-8")

#include "everythingutil.h"
#include <QDebug>

EveryThingUtil::EveryThingUtil()
{

}

void EveryThingUtil::openEverything()
{
    QString everythingName = "Everything.exe";
    QProcess process;
    process.startDetached(everythingName, QStringList("-close"));
    process.waitForStarted();
    QThread::sleep(3);
}

QVector<QFileInfo> EveryThingUtil::Search(const QString& str, bool reg)
{
    QMutex mutex;
    mutex.lock();
    QVector<QFileInfo> files;
    // 搜索字符串
    std::wstring wstr = str.toStdWString();
    LPCWSTR lpcwstr = wstr.c_str();
    if (reg) {
        Everything_SetRegex(true);
    }

    Everything_SetSearch(lpcwstr);
    Everything_SetMax(200);
    Everything_SetRequestFlags(EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH);
    // 执行查询
    BOOL result = Everything_Query(TRUE);
    if (!result) {
        qDebug() << getSearchErrorString();
    } else {
        DWORD fileCount = Everything_GetNumResults();
        for (DWORD i = 0; i < fileCount; i++) {
            QString name = QString::fromStdWString(Everything_GetResultFileName(i));
            QString path = QDir::toNativeSeparators(QString::fromStdWString(Everything_GetResultPath(i)));
            QFileInfo fileInfo(path + QDir::separator() + name);
            files.push_back(fileInfo);
        }
    }
    Everything_Reset();
    mutex.unlock();
    return files;
}

QString EveryThingUtil::getSearchErrorString(){
    DWORD error = Everything_GetLastError();
    QString str;
    if(error == EVERYTHING_ERROR_MEMORY){
        str = "未能为搜索查询分配内存。";
    }
    if(error == EVERYTHING_ERROR_IPC){
        str = "IPC不可用。";
    }
    if(error == EVERYTHING_ERROR_REGISTERCLASSEX){
        str = "未能注册搜索查询窗口类。";
    }
    if(error == EVERYTHING_ERROR_CREATEWINDOW){
        str = "创建搜索查询窗口失败。";
    }
    if(error == EVERYTHING_ERROR_CREATETHREAD){
        str = "创建搜索查询线程失败。";
    }
    if(error == EVERYTHING_ERROR_INVALIDINDEX){
        str = "无效索引。索引必须大于或等于0，小于可见结果的数目。";
    }
    if(error == EVERYTHING_ERROR_INVALIDCALL){
        str = "无效的呼叫。";
    }
    return str;
}
