#include "bigicondelegate.h"
#include <QTextEdit>
#include <QFileInfo>
#include <QMimeDatabase>
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


QSize BigIconDelegate::rectSize = QSize(150, 150);

QIcon BigIconDelegate::getIcon(QString path, IconSize size)
{
    Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);
    QFileInfo info(path);
    SHFILEINFOW psfi;
    if (info.isDir()) {
        path.replace("/", "\\");
        SHGetFileInfo((CONST TCHAR*)path.utf16(), 0, &psfi, sizeof(psfi), SHGFI_SYSICONINDEX);
    } else if (info.suffix() == "")
        SHGetFileInfo((CONST TCHAR*)info.suffix().utf16(), 0, &psfi, sizeof(psfi), SHGFI_SYSICONINDEX);
    else{
        QString suffix = path;
        suffix.replace("/", "\\");
         SHGetFileInfo((CONST TCHAR*)suffix.utf16(), 0, &psfi, sizeof(psfi), SHGFI_SYSICONINDEX);
    }
    // SHGetFileInfo((CONST TCHAR*)QString("C:\\").utf16(), 0, &psfi, sizeof(psfi), SHGFI_SYSICONINDEX);
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
    }
    SHGetImageList(type, IID_IImageList, (void ** )&imageList);
    HICON hIcon;
    imageList->GetIcon(psfi.iIcon, ILD_TRANSPARENT, &hIcon);
    QPixmap pix = qt_pixmapFromWinHICON(hIcon);
    return QIcon(pix);
}


QString BigIconDelegate::stringFomat(QString text, BigIconDelegate::IconSize size) {
    QFontMetrics metrics(text);
    QString temp;
    int rectWidth;
    switch (size) {
    case BigIconDelegate::BigIcon:
        rectWidth = 140;
        break;
    case BigIconDelegate::ExBigIcon:
        rectWidth = 265;
        break;
    case BigIconDelegate::MidIcon:
        rectWidth = 80;
        break;
    }
    int hopeWidth = metrics.width(text);
    if (hopeWidth > rectWidth) {
        int start = 0, length = 1;
        int lines = hopeWidth/rectWidth;
        for (int i = 0; i < lines && i < 3; ++i) {
            while (metrics.width(text.mid(start, length)) < rectWidth) {
                length++;
            }
            temp += text.mid(start, length-1) + "\n";
            start += length - 1;
            length = 1;
        }
        if (lines > 4) {
            temp += metrics.elidedText(text.mid(start, text.length()-start), Qt::ElideRight, rectWidth);
        } else
            temp += text.mid(start, text.length()-start);
        text = temp;
    }
    return text;
}


BigIconDelegate::BigIconDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    size = BigIcon;
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
    QString absolutePath = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    if (absolutePath.isEmpty())
        return;

    // 选中状态绘制
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
        painter->setPen(QPen(QColor("#e3e3e5")));
        painter->setBrush(QColor("#e3e3e5"));
        painter->drawPath(path);
    }
    if (option.state.testFlag(QStyle::State_Selected)) {
        painter->setPen(QPen(QColor("#e3e3e5")));
        painter->setBrush(QColor("#e3e3e5"));
        painter->drawPath(path);
    }
    painter->restore();


    QFileInfo info(absolutePath); // 获得对应路径下的文件信息
    int adjustWidth, adjustHeight1;
    QFontMetrics metrics(info.fileName());
    QSize iconSize;
    int lines;
    switch (size) {
    case BigIcon:
        iconSize = QSize(128, 128);
        adjustHeight1 = 10;
        lines = metrics.width(info.fileName())/140 + 1;
        break;
    case ExBigIcon:
        iconSize = QSize(256, 256);
        adjustHeight1 = 13;
        lines = metrics.width(info.fileName())/256 + 1;
        break;
    case MidIcon:
        iconSize = QSize(48, 48);
        lines = metrics.width(info.fileName())/80 + 1;
        adjustHeight1 = 3;
        break;
    }
    QMimeDatabase db;
    QString mimeType = db.mimeTypeForUrl(absolutePath).name();
    QPixmap pixmap;
    adjustWidth = (rectSize.width()-iconSize.width()) / 2;
    QRect targetRect = rect.adjusted(+adjustWidth, 0, -adjustWidth, 0);
    if (mimeType.contains("image")) {
        pixmap.load(absolutePath);
        if (pixmap.isNull())
            pixmap = getIcon(absolutePath, size).pixmap(iconSize);
        pixmap = pixmap.scaled(iconSize, Qt::AspectRatioMode::KeepAspectRatio, Qt::SmoothTransformation);
        targetRect.setSize(pixmap.size());
        targetRect = targetRect.adjusted(0, +adjustHeight1, 0, +adjustHeight1);
        painter->drawPixmap(targetRect, pixmap);
    } else
    {
        pixmap = getIcon(absolutePath, size).pixmap(iconSize);
        targetRect.setHeight(iconSize.height());
        targetRect = targetRect.adjusted(0, +adjustHeight1, 0, +adjustHeight1);
        painter->drawPixmap(targetRect, pixmap);
    }

    painter->drawText(rect.adjusted(+0, +iconSize.height()+adjustHeight1, 0, 0),
                      Qt::AlignHCenter| Qt::AlignTop, stringFomat(info.fileName(), size)); // 画出文件名的文字
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
    QString fileName = index.data().toString();
    switch (size) {
    case BigIcon: {
        QFontMetrics metrics(stringFomat(fileName, size));
        int lines = metrics.width(fileName)/140 + 1;
        if (lines > 4)
            lines = 4;
        rectSize = QSize(150, lines*metrics.height()+128+10+5);
        break;
    }
    case ExBigIcon: {
        QFontMetrics metrics(fileName);
        int lines = metrics.width(fileName)/265 + 1;
        if (lines > 4)
            lines = 4;
        rectSize = QSize(275, lines*metrics.height()+256+13+5);
        break;
    }
    case MidIcon: {
        QFontMetrics metrics(stringFomat(fileName, size));
        int lines = metrics.width(fileName)/80 + 1;
        if (lines > 4)
            lines = 4;
        rectSize = QSize(90, lines*metrics.height()+64+5+5);
        break;
    }
    }
    return rectSize;
}

void BigIconDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    int adjustHeight1;
    QSize iconSize;
    switch (size) {
    case BigIcon:
        iconSize = QSize(128, 128);
        adjustHeight1 = 10;
        break;
    case ExBigIcon:
        iconSize = QSize(256, 256);
        adjustHeight1 = 13;
        break;
    case MidIcon:
        iconSize = QSize(48, 48);
        adjustHeight1 = 3;
        break;
    }
    QRect rect = option.rect;
    QFontMetrics metrics(lineEdit->text());
    rect.setWidth(metrics.width(lineEdit->text()));
    rect.setHeight(metrics.height());
    rect = rect.adjusted(0, +iconSize.height()-adjustHeight1, 0, +iconSize.height()-adjustHeight1);
    lineEdit->setAlignment(Qt::AlignHCenter);
    editor->setGeometry(option.rect.adjusted(0, +iconSize.height()-adjustHeight1, 0, 0)); // 编辑器只占右边部分
}
