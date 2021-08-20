#include "mytableview.h"
#include <QDebug>
#include <QDateTime>
#include <QLineEdit>

MyTableView::MyTableView(QWidget *parent) : QTableView(parent)
{

}

void MyTableView::mousePressEvent(QMouseEvent *event)
{
    if (openedEdior != nullptr) {
        closePersistentEditor(*openedEdior);
    }
    static QTime lastTime = QTime::currentTime();
    static bool isLeft = false;
    static QModelIndex lastIndex = this->indexAt(event->pos());
    if (event->button() == Qt::LeftButton)
    {
        if (!isLeft) {
            isLeft = true;
        } else {
            QTime currentTime = QTime::currentTime();
            // qDebug() << "last:" << lastTime << " current:" << currentTime << " diff" << currentTime.secsTo(lastTime);
            if (lastTime.msecsTo(currentTime) < 500) {
                // 两次点击事件不超过1s，打开文件
                QModelIndex index = this->indexAt(event->pos());
                if (index == lastIndex) {
                    // 两次点击同一个名称
                    emit openFile(index);
                }
            } else {
                // 否则修改文件名
                QModelIndex index = this->indexAt(event->pos());
                if (index == lastIndex && index.column() == 0) {
                    // 两次点击同一个名称
                    this->openPersistentEditor(index);
                    openedEdior = new QModelIndex(index);
                }
                lastIndex = index;
            }
            lastTime = QTime::currentTime();
        }
    } else {
        isLeft = false;
    }
}




