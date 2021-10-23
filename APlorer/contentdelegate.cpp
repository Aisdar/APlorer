#include "contentdelegate.h"
#include "bigicondelegate.h"
#include <QTextEdit>
#include <QFileInfo>
#include <QLineEdit>
#include <QFileIconProvider>
#include <QPainter>
#include <windows.h>
#include <QtWinExtras/QtWinExtras>
#include <QIcon>
#include <QPixmap>
#include <windows.h>
#include <QFileInfo>
#include <QtWinExtras/QtWin>
#include <QMessageBox>
#include <shellapi.h>
#include <initguid.h>
#include <commctrl.h>
#include <commoncontrols.h>
#include <QFontMetrics>
#include <QSizePolicy>
#include "mytableview.h"

ContentDelegate::ContentDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *ContentDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 从ModelIndex中获取Model中文件完整路径数据
    QFileInfo info(fileName); // 根据路径获得文件的FileInfo
    editor->setText(info.fileName());
    connect(editor, &QLineEdit::editingFinished, [=](){
        // 编辑器回车完成编辑后触发
        editor->hide(); // 编辑器隐藏
    });
    return editor;
}

void ContentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect; // 系统的矩形

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

    QFileIconProvider provider;  // 获得系统图标
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFileInfo info(fileName); // 获得对应路径下的文件信息
    bool isDir = info.isDir();
    QIcon icon = BigIconDelegate::getIcon(fileName, BigIconDelegate::MidIcon);
    QPixmap pix = icon.pixmap(48, 48);
    painter->drawPixmap(rect.adjusted(+0, +0, -rect.width()+48, 0), pix);
    // 设置文字略缩样式
    QString textFileName = info.fileName();
    QString dateMeg = "修改时间:" + info.lastModified().toString("yyyy/M/dd hh:mm");
    QFontMetrics metrics1(textFileName);
    if (metrics1.width(textFileName) > rect.width()-200) {
        textFileName = metrics1.elidedText(textFileName, Qt::ElideRight, rect.width()-200);
    }
    painter->drawText(rect.adjusted(+48, +8, 0, 0), Qt::AlignLeft|Qt::AlignTop, textFileName); // 画出文件名的文字
    if (!isDir) {
        painter->drawText(rect.adjusted(+48, 0, 0, -5),
                          Qt::AlignLeft|Qt::AlignBottom, MyTableView::fileType(info));
        QString sizeMeg = "大小:" + MyTableView::sizeFormat(info);
        painter->drawText(rect.adjusted(+rect.width()-200, 0, 0, -10),
                          Qt::AlignLeft|Qt::AlignBottom, "大小:"+ MyTableView::sizeFormat(info));
    }
    painter->drawText(rect.adjusted(+rect.width()-200, 0, 0, 0),
                      Qt::AlignLeft|Qt::AlignTop, dateMeg);
}

void ContentDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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

QSize ContentDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    MyTableView *mainwindow = static_cast<MyTableView *>(this->parent());
    return QSize(mainwindow->contentsRect().width(), 50);
}

void ContentDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    QFontMetrics metrics(lineEdit->text());
    QRect rect = option.rect;
    rect.setWidth(metrics.width(lineEdit->text()));
    rect.setHeight(metrics.height());
    rect = rect.adjusted(+48, +8, 0, +8);
    lineEdit->setGeometry(rect);
}
