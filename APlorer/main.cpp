#include "aplmainwindow.h"


#include <QDebug>
#include <QTranslator>
#include <QApplication>

aplMainWindow *apl; // 第一打开的窗口的指针
QList<aplMainWindow *> aplList; // 保存窗口的链表

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 应用单实例检测
    aplMainWindow pw;

    pw.show();
    QTranslator translator;
    translator.load(":/qt_zh_CN.qm");
    a.installTranslator(&translator);

    qApp->setStyleSheet("QTableView::item:hover{ \
                        }");

    return a.exec();
}
