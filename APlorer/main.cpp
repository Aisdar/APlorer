#include "aplmainwindow.h"
#include "aplsingleapplication.h"

#include <QDebug>
#include <QTranslator>

aplMainWindow *apl; // 第一打开的窗口的指针
QList<aplMainWindow *> aplList; // 保存窗口的链表

int main(int argc, char *argv[])
{
    aplSingleApplication a(argc, argv);
    // 应用单实例检测
    aplMainWindow *pw = nullptr;
    if(a.isRunning())
    {   // 已经被实例过，通知上一个进程
        a.sendMessage("create a new window", 500); // 500ms 通知第一个实例创建一个新窗口

        return EXIT_SUCCESS;
    }
    else
    {   // 从未被实例，创建一个新窗口并调用init做初始化
        pw = new aplMainWindow();
        pw->init();
        a.setActivationWindow(pw, false);

        apl = pw;
        aplList.append(pw);

        pw->show();
    }

    QTranslator translator;
    translator.load(":/qt_zh_CN.qm");
    a.installTranslator(&translator);

    return a.exec();
}
