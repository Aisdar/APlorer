#include "mydelegate.h"
#include <QLineEdit>
#include <QPainter>
#include <QDebug>
#include <QTableView>
#include <QFileIconProvider>
#include "data.h"
#include <QIcon>
#include <QPixmap>


MyDelegate::MyDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QString fileName = index.data(Qt::UserRole+1).value<QString>();
    QFileInfo info(fileName);
    editor->setText(info.fileName());
    editor->setEnabled(true);
    return editor;
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = option.rect.size();
    size.setWidth(size.width()+100);
    return size;
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect.adjusted(+30, 0, 0, 0));
}

void MyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect; // 系统的矩形
    QFileIconProvider provider;
    QString fileName = index.data(Qt::UserRole+1).value<QString>();
    QFileInfo info(fileName);
    bool isDir = index.data(Qt::UserRole+2).value<bool>();
    QIcon icon;
    if (isDir) {
        icon = provider.icon(QFileIconProvider::Folder);
    } else {
        icon = provider.icon(info);
    }
    icon.paint(painter, rect, Qt::AlignLeft);
    painter->drawText(rect.adjusted(+30, 0, -10, 0), Qt::AlignVCenter|Qt::AlignLeft, info.fileName());
}
