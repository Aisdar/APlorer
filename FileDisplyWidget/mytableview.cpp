#include "mytableview.h"
#include <QDebug>
#include <QDateTime>
#include <QLineEdit>
#include <QHeaderView>
#include <QSettings>

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
    } else if (event->button() == Qt::RightButton) {
        isLeft = false;
        QSettings reg("HKEY_CLASSES_ROOT\\*", QSettings::NativeFormat);
        qDebug() << reg.childGroups();
        foreach (auto x, reg.childKeys()){
            qDebug() << reg.value(x);
        }
        qDebug() << reg.childKeys();
        qDebug() << reg.allKeys();
        qDebug() << reg.status();
        reg.beginGroup("HKEY_CLASSES_ROOT");
        qDebug() << reg.childKeys();
        QMenu *menu = new QMenu(this);
        menu->addAction(QString("111"));
        QPoint pos = event->globalPos();
        menu->exec(pos);
    } else {
        isLeft = false;
    }
}




