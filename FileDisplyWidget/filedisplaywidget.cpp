#include "filedisplaywidget.h"

FileDisplayWidget::FileDisplayWidget(QWidget *parent) : QWidget(parent)
{

}

FileDisplayWidget::FileDisplayWidget(QString fileName, QWidget *parent) :
    QWidget(parent), fileName(fileName)
{

}

void FileDisplayWidget::paintEvent(QPaintEvent *event)
{
    // 重绘事件
    Q_UNUSED(event)

}
