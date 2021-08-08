#include "aplsingleapplication.h"
#include "aplmainwindow.h"
#include <QDebug>


aplSingleApplication::aplSingleApplication(int &argc, char **argv, bool GUIenabled)
    : QtSingleApplication(argc, argv, GUIenabled)
{
    connect(this, &aplSingleApplication::messageReceived, this, &aplSingleApplication::messageDeal);
}

aplSingleApplication::aplSingleApplication(const QString &id, int &argc, char **argv)
    : QtSingleApplication(id, argc, argv)
{
    connect(this, &aplSingleApplication::messageReceived, this, &aplSingleApplication::messageDeal);
}

void aplSingleApplication::messageDeal(const QString &message)
{
    qDebug() << "应用接受到消息:" << message;
    if(message == "create a new window"){
        if(apl)
        {
            aplMainWindow* pw = new aplMainWindow();
            pw->copy(apl);  // 拷贝第一个窗口的模型
            aplList.append(apl);
            this->setActivationWindow(pw, false);   // 设置为活动窗口

            pw->show();
        }
    }
}


