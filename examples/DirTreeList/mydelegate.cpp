#include "mydelegate.h"
#include <QLineEdit>
#include <QDebug>

MyDelegate::MyDelegate(QWidget *parent):
    QStyledItemDelegate(parent)
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    qDebug() << 2;
    return editor;
}

//void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{

//}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

//QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    return option.rect.size();
//}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << option.rect;
    editor->setGeometry(option.rect);
    qDebug() << 1;
}





