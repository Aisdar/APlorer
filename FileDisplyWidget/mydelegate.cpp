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
    QLineEdit *editor = new QLineEdit(parent); // 新建一个LineEdit作为编辑器，一定设置好父类，不然显示位置错误
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 从ModelIndex中获取Model中文件完整路径数据
    QFileInfo info(fileName); // 根据路径获得文件的FileInfo
    editor->setText(info.fileName()); // 设置编辑器的数据
    connect(editor, &QLineEdit::editingFinished, [=](){
        // 编辑器回车完成编辑后触发
        editor->hide(); // 编辑器隐藏
    });
    return editor; // 需要返回编辑器的指针
}

QSize MyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = option.rect.size(); // 获得原编辑器的尺寸
    size.setWidth(size.width()+300); // 宽度增加500
    return size;
}

void MyDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void MyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect.adjusted(+30, 0, 0, 0)); // 编辑器只占右边部分
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
        // 获得图标，文件夹
        icon = provider.icon(QFileIconProvider::Folder);
    } else {
        // 获得图标各种类型的文件
        icon = provider.icon(info);
    }
    icon.paint(painter, rect, Qt::AlignLeft); // 在左侧绘制图标，宽度大概为30
    // 设置文字略缩样式
    QFontMetrics metrics(painter->font());
    QString text = info.fileName();
    if(metrics.width(text) > rect.width()-40)
    {
        // 略缩字样如果大于可供显示的尺寸（rect.width()-40)文字略缩
        text = metrics.elidedText(text, Qt::ElideRight, rect.width()-40);
    }
    painter->drawText(rect.adjusted(+30, 0, 0, 0), Qt::AlignVCenter|Qt::AlignLeft, text); // 画出文件名的文字
}


void MyDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QStandardItemModel *smodel = static_cast<QStandardItemModel *>(model);
    QLineEdit *editor1 = static_cast<QLineEdit *>(editor); // 获得原编辑器
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFile file(fileName);
    QFileInfo x(file);
    if (file.rename(x.absoluteDir().path() + "/" + editor1->text())) {
        // 直接重命名文件
        x.setFile(file);
        QStandardItem *item = new QStandardItem; // 新建模型的Item重设显示信息
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件名
        item->setData(x.isDir(), Qt::UserRole+2); // 是否为文件夹
        smodel->setItem(index.row(), 0, item); // 重设item
    }
}

