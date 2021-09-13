#include "dtaildelegate2.h"
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
    // 绘制略缩文字
    QRect rect = option.rect;
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
