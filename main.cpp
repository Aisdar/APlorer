#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "everythingutil.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    EveryThingUtil::openEverything();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
