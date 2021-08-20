#include "mydelegate.h"
#include <QLineEdit>
#include <QPainter>
#include <QDebug>
#include <QTableView>
#include <QFileIconProvider>
#include "data.h"
#include <QIcon>
#include <QPixmap>
#include <QStandardItemModel>
#include <QDir>


MyDelegate::MyDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

QWidget *MyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QString fileName = index.data(Qt::UserRole+1).value<QString>();
    QFileInfo info(fileName);
    editor->setText(info.fileName());
    connect(editor, &QLineEdit::editingFinished, [=](){
        editor->hide();
    });
    return editor;
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = option.rect.size();
    size.setWidth(size.width()+300);
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
    QFileIconProvider provider;  // 获得系统图标
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFileInfo info(fileName); // 获得对应路径下的文件信息
    bool isDir = index.data(Qt::UserRole+2).value<bool>(); // 通过是否为文件夹获得对应图标
    QIcon icon;
    if (isDir) {
        // 获得图标
        icon = provider.icon(QFileIconProvider::Folder);
    } else {
        icon = provider.icon(info);
    }
    icon.paint(painter, rect, Qt::AlignLeft); // 在左侧绘制图标
    // 设置文字略缩样式
    QFontMetrics metrics(painter->font());
    QString text = info.fileName();
    if(metrics.width(text) > rect.width()-40)
    {
        text = metrics.elidedText(text, Qt::ElideRight, rect.width()-40);
    }
    painter->drawText(rect.adjusted(+30, 0, 0, 0), Qt::AlignVCenter|Qt::AlignLeft, text);
}

void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QStandardItemModel *smodel = static_cast<QStandardItemModel *>(model);
    QLineEdit *editor1 = static_cast<QLineEdit *>(editor);
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFile file(fileName);
    QFileInfo x(file);
    // qDebug() << editor1->text();
    if (file.rename(x.absoluteDir().path() + "/" + editor1->text())) {
        x.setFile(file);
        QStandardItem *item = new QStandardItem;
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件名
        item->setData(x.isDir(), Qt::UserRole+2); // 是否为文件夹
        smodel->setItem(index.row(), 0, item);
    }
}

