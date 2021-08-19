#include "mytableview.h"
#include <QDebug>


MyTableView::MyTableView(QWidget *parent) : QTableView(parent)
{

}

void MyTableView::mousePressEvent(QMouseEvent *event)
{
    static ulong lastTime = event->timestamp();
    static bool isLeft = false;
    if (isLeft) {

    }
}

//void MyTableView::mouseMoveEvent(QMouseEvent *event)
//{
//    if (event->type() == QEvent::MouseButtonPress)
//        qDebug() << event->type();
//}
