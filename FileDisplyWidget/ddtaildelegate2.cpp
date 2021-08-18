#include "ddtaildelegate2.h"
#include <QPainter>
#include <QDebug>
#include <QStandardItem>

dDtailDelegate2::dDtailDelegate2(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *dDtailDelegate2::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return NULL;
}

void dDtailDelegate2::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // qDebug() << index.data().toString();
    painter->drawText(option.rect, index.data().toString(), Qt::AlignVCenter|Qt::AlignLeft);
}
