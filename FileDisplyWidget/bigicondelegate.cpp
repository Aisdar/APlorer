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


QSize BigIconDelegate::rectSize = QSize(150, 150);

QIcon BigIconDelegate::getIcon(QString path, IconSize size)
{
    Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);
    QFileInfo info(path);
    SHFILEINFOW psfi;
    if (info.suffix() == "")
        SHGetFileInfo((CONST TCHAR*)info.suffix().utf16(), -1, &psfi, sizeof(psfi), SHGFI_SYSICONINDEX);
    else {
        QString suffix = path;
        suffix.replace("/", "\\");
        SHGetFileInfo((CONST TCHAR*)suffix.utf16(), -1, &psfi, sizeof(psfi), SHGFI_SYSICONINDEX);
    }
    IImageList* imageList = nullptr;
    int type;
    switch (size) {
    case ExBigIcon:
        type = 4;
        break;
    case BigIcon:
        type = 4;
        break;
    case MidIcon:
        type = SHIL_EXTRALARGE;
        break;
    case SmallIcon:
        type = SHIL_SMALL;
        break;
    }
    SHGetImageList(type, IID_IImageList, (void ** )&imageList);
    HICON hIcon;
    imageList->GetIcon(psfi.iIcon, ILD_TRANSPARENT, &hIcon);
    QPixmap pix = qt_pixmapFromWinHICON(hIcon);
    return QIcon(pix);
}




BigIconDelegate::BigIconDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

BigIconDelegate::BigIconDelegate(IconSize size, QObject *parent) :
    QStyledItemDelegate(parent), size(size)
{

}


QWidget *BigIconDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

void BigIconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect; // 系统的矩形
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFileInfo info(fileName); // 获得对应路径下的文件信息
    // (200, 150)
    QSize iconSize;
    int fontLength;
    int adjustWidth, adjustHeight1, adjustHeight2;
    switch (size) {
    case BigIcon:
        iconSize = QSize(128, 128);
        fontLength = 12;
        adjustHeight1 = 5;
        break;
    case ExBigIcon:
        iconSize = QSize(256, 256);
        fontLength = 30;
        adjustHeight1 = 5;
        break;
    case MidIcon:
        iconSize = QSize(48, 48);
        fontLength = 10;
        adjustHeight1 = 3;
        break;
    }

    QPixmap pixmap = getIcon(fileName, size).pixmap(iconSize);
    // QIcon icon1 = getIcon(fileName, size);
    painter->save();
    painter->setPen(QPen(Qt::red));
    painter->drawRect(rect);
    painter->restore();
    adjustWidth = (rectSize.width()-iconSize.width()) / 2;
    adjustHeight2 = rectSize.height() - iconSize.height() - adjustHeight1;
//    qDebug() << adjustWidth;
//    qDebug() << adjustHeight1;
//    qDebug() << adjustHeight2;
     painter->drawPixmap(rect.adjusted(+adjustWidth, +adjustHeight1,
                                       -adjustWidth, -adjustHeight2), pixmap);
    //  icon1.paint(painter, rect.adjusted(+adjustWidth, +adjustWidth,
                                 //      -adjustWidth, -adjustHeight2), Qt::AlignCenter);
    // painter->drawImage(rect.adjusted(0, 0, 0, +8), pixmap.toImage());

    QString text = info.fileName();
    QString displayText = "";
    if (text.length() > fontLength) {
        for (int i = 0; i < text.length()/fontLength; i++) {
            displayText += text.mid(i, fontLength) + "\n";
        }
        displayText += text.mid(text.length()-text.length()%fontLength, text.length()%fontLength);
    } else {
        displayText = text;
    }
    painter->drawText(rect.adjusted(0, +iconSize.height()-adjustHeight1, 0, 0),
                      Qt::AlignCenter, displayText); // 画出文件名的文字
}


void BigIconDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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
        item->setData(x.fileName(), Qt::DisplayRole);
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件名
        smodel->setItem(index.row(), 0, item); // 重设item
    }
}


QSize BigIconDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//  QSize rectSize;
    switch (size) {
    case BigIcon:
        rectSize = QSize(150, 150);
        break;
    case ExBigIcon:
        rectSize = QSize(275, 275);
        break;
    case MidIcon:
        rectSize = QSize(90, 90);
        break;
    }
    return rectSize;
}

void BigIconDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect.adjusted(+30, 0, 0, 0)); // 编辑器只占右边部分
}
