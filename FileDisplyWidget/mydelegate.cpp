#include "mydelegate.h"
#include <QLineEdit>
#include <QDebug>
#include <QTableView>
#include "data.h"

MyDelegate::MyDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    FileInfo info = index.data(Qt::UserRole+1).value<FileInfo>();
    editor->setVisible(true);
    editor->setText(info.fileName);
    editor->setEnabled(false);
    return editor;
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = option.rect.size();
    qDebug() << size;
    size.setWidth(size.width()+100);
    qDebug() << size;
    return size;
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect;

}
