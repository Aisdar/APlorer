#ifndef APLSINGLEAPPLICATION_H
#define APLSINGLEAPPLICATION_H

#include "qtsingleapplication.h"

class aplMainWindow;

extern aplMainWindow *apl; // 第一打开的窗口的指针
extern QList<aplMainWindow *> aplList; // 保存窗口的链表

class aplSingleApplication : public QtSingleApplication
{
    Q_OBJECT
public:
    aplSingleApplication(int &argc, char **argv, bool GUIenabled = true);
    aplSingleApplication(const QString &id, int &argc, char **argv);

private slots:
    void messageDeal(const QString &message);
};

#endif // APLSINGLEAPPLICATION_H
