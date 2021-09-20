#include "listdelegate.h"
#include <QLineEdit>
#include <QFileIconProvider>
#include <QPainter>
#include <QStandardItemModel>
#include <QFile>
#include <QDir>
#include <QSize>
#include <QDebug>


ListDelegate::ListDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *ListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QString fileName = index.data().toString();
    editor->setText(fileName);
    connect(editor, &QLineEdit::editingFinished, [=](){
        // 编辑器回车完成编辑后触发
        editor->hide(); // 编辑器隐藏
    });
    return editor;
}

void ListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect; // 系统的矩形

    QFileIconProvider provider;  // 获得系统图标
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFileInfo info(fileName); // 获得对应路径下的文件信息
    bool isDir = info.isDir(); // 是否为文件夹
    QIcon icon;
    if (!info.exists())
        return;
    // 选中状态
    QPainterPath path;
    path.moveTo(rect.topRight());
    path.lineTo(rect.topLeft());
    path.quadTo(rect.topLeft(), rect.topLeft());
    path.lineTo(rect.bottomLeft());
    path.quadTo(rect.bottomLeft(), rect.bottomLeft());
    path.lineTo(rect.bottomRight());
    path.quadTo(rect.bottomRight(), rect.bottomRight());
    path.lineTo(rect.topRight());
    path.quadTo(rect.topRight(), rect.topRight());

    // 鼠标悬停或者选中时改变背景色
    painter->save();
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


    if (isDir) {
        // 获得图标，文件夹
        icon = provider.icon(QFileIconProvider::Folder);
    } else {
        // 获得图标各种类型的文件
        icon = provider.icon(info);
    }
    icon.paint(painter, rect, Qt::AlignLeft); // 在左侧绘制图标，宽度大概为30
    painter->drawText(rect.adjusted(+30, 0, 0, 0), Qt::AlignVCenter|Qt::AlignLeft, info.fileName()); // 画出文件名的文字
}

void ListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void ListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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
        item->setData(x.fileName(), Qt::DisplayRole); // 文件名
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件绝对路径
        smodel->setItem(index.row(), 0, item); // 重设item
    }
}

QSize ListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size1 = option.rect.size(); // 获得原编辑器的尺寸
    size1.setWidth(size1.width()+300); // 宽度增加500
    return size1;
}

void ListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect.adjusted(+30, 0, 0, 0)); // 编辑器只占右边部分
}
