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
#include <shellapi.h>
#include <windows.h>
#include <QFileInfo>
// #include <commoncontrols.h>
#include <commctrl.h>


QIcon getIcon(QString path)
{
    QFileInfo info(path);
    Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);
    SHFILEINFOA psfi;
    // qDebug() << info.suffix();
    if (info.suffix().isEmpty())
        SHGetFileInfoA(info.suffix().toStdString().c_str(),NULL,&psfi,
                       sizeof(SHFILEINFOA),SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_LARGEICON);
    else {
        qDebug() << QString(".") + info.suffix();
        SHGetFileInfoA((QString(".") + info.suffix()).toStdString().c_str(),
                       NULL,&psfi,sizeof(SHFILEINFOA),SHGFI_ICON);
    }
    QPixmap pixmap = qt_pixmapFromWinHICON(psfi.hIcon);
    DestroyIcon(psfi.hIcon);
    return QIcon(pixmap);

//    static bool bInit = false;
//    static IImageList *imageList = NULL;

//    if (!bInit && imageList == NULL)
//    {
//        bInit = true;
//        IID IID_IImageList = { 0 };
//        HRESULT hr = IIDFromString(L"{46EB5926-582E-4017-9FDF-E8998DAA0950}", &IID_IImageList);
//        // ASSERT(SUCCEEDED(hr));
//        SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void **)(&imageList));
//    }

//    SHFILEINFOA info = { 0 };
//    if (SHGetFileInfoA(info1.suffix().toStdString().c_str(), FILE_ATTRIBUTE_DIRECTORY, &info, sizeof(info), SHGFI_ICON | SHGFI_DISPLAYNAME))
//    {
//        HICON hIcon = info.hIcon;
//        if (imageList)
//        {

//            hIcon = ImageList_GetIcon((HIMAGELIST)imageList, info.iIcon, 0);
//            if (hIcon)
//                DestroyIcon(info.hIcon);
//            else
//                hIcon = info.hIcon;
//        }
//        return QIcon(QtWin::fromHICON(hIcon));
//    }
}

BigIconDelegate::BigIconDelegate(QObject *parent) : QStyledItemDelegate(parent)
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
    QFileIconProvider provider;  // 获得系统图标
    QString fileName = index.data(Qt::UserRole+1).value<QString>(); // 获取在索引中的文件绝对路径
    QFileInfo info(fileName); // 获得对应路径下的文件信息
//    bool isDir = index.data(Qt::UserRole+2).value<bool>(); // 通过是否为文件夹获得对应图标
    QPixmap pixmap = getIcon(fileName).pixmap(48, 48);
    // icon.paint(painter, rect, Qt::AlignLeft); // 在左侧绘制图标，宽度大概为30
    painter->save();
    painter->setPen(QPen(Qt::red));
    painter->drawRect(rect);
    painter->restore();
    painter->drawPixmap(rect.adjusted(+51, 0, -51, -102), pixmap);
    // painter->drawImage(rect.adjusted(0, 0, 0, +8), pixmap.toImage());
    // 设置文字略缩样式
    QString text = info.fileName();
    painter->drawText(rect.adjusted(+30, 0, 0, 0), Qt::AlignVCenter|Qt::AlignLeft, text); // 画出文件名的文字
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
    QSize size = option.rect.size(); // 获得原编辑器的尺寸
    size.setWidth(size.width()+300); // 宽度增加500
    size.setHeight(size.height()+300); // 高度加300
    return QSize(150, 150);
}

void BigIconDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect.adjusted(+30, 0, 0, 0)); // 编辑器只占右边部分
}
