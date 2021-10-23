#include "mytableview.h"
#include <QDebug>
#include <QDateTime>
#include <QLineEdit>
#include <QHeaderView>
#include <QSettings>
#include <mainwindow.h>

MyTableView::MyTableView(QWidget *parent) : QTableView(parent)
{
    // 隐藏垂直标头
    QHeaderView* vHeaderView =  this->verticalHeader();
    vHeaderView->setHidden(true);
    // 平行标头可移动
    QHeaderView* hHeaderView = this->horizontalHeader();
    hHeaderView->setMinimumSectionSize(50); // 最小的表头宽度
    hHeaderView->setSectionsMovable(true);
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
                if (index == lastIndex) {
                    // 两次点击同一个名称
                    MainWindow *mainwindow =  static_cast<MainWindow *>(this->parent());
                    if (mainwindow->getCurrentModel() == MainWindow::DETAIL && index.column() == 0)
                        openPersistentEditor(index);
                    else
                        openPersistentEditor(index);
                    openedEdior = new QModelIndex(index);
                }
                lastIndex = index;
            }
            lastTime = QTime::currentTime();
        }
    } else if (event->button() == Qt::RightButton) {
        isLeft = false;
        QMenu *menu = new QMenu(this);
        menu->addAction(QString("111"));
        QPoint pos = event->globalPos();
        menu->exec(pos);
    } else {
        isLeft = false;
    }
}




