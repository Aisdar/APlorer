#include "detaildelegate2.h"
#include "mytableview.h"
#include <QPainter>
#include <QDebug>
#include <QStandardItem>

DetailDelegate2::DetailDelegate2(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *DetailDelegate2::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return nullptr; // 返回空指针，这个项目不可编辑
}

void DetailDelegate2::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect; // 系统的矩形
    MyTableView *view = static_cast<MyTableView *>(this->parent());
    int x = view->geometry().right();
    int x1 = view->geometry().left();
    QPainterPath path;
    QPoint topRight(x, rect.top());
    path.moveTo(topRight);
    QPoint topLeft(x1, rect.top());
    path.lineTo(topLeft);
    path.quadTo(topLeft, topLeft);
    QPoint bottomLeft(x1, rect.bottom());
    path.lineTo(bottomLeft);
    path.quadTo(bottomLeft, bottomLeft);
    QPoint bottomRight(x, rect.bottom());
    path.lineTo(bottomRight);
    path.quadTo(bottomRight, bottomRight);
    path.lineTo(topRight);
    path.quadTo(topRight, topRight);

    painter->save();
    // 鼠标悬停或者选中时改变背景色
    if (option.state.testFlag(QStyle::State_MouseOver)) {
        painter->setPen(QPen(QColor("#ebeced")));
        painter->setBrush(QColor("#ebeced"));
        painter->drawPath(path);
    }
    if (option.state.testFlag(QStyle::State_Selected)) {
        painter->setPen(QPen(QColor("#e3e3e5")));
        painter->setBrush(QColor("#e3e3e5"));
        painter->drawPath(path);
    }
    painter->restore();

    // 绘制略缩文字
    QString text = index.data().toString();
    QFontMetrics metrics(painter->font());
    if(metrics.width(text) > rect.width())
    {
        text = metrics.elidedText(text, Qt::ElideRight, rect.width());
    }
    painter->drawText(option.rect, text, Qt::AlignVCenter|Qt::AlignLeft);
}

QSize DetailDelegate2::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150, option.rect.height()); // 固定宽度
}
