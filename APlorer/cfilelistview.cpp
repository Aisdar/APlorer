#include "cfilelistview.h"
#include <QMouseEvent>
#include <QDebug>
#include <CShell.h>
#include <QFileSystemModel>

CFileListView::CFileListView(QWidget *parent)
    : QListView(parent)
{
}


void CFileListView::mouseReleaseEvent(QMouseEvent *e)
{
    QFileSystemModel* model = dynamic_cast<QFileSystemModel*>(this->model());
    QPoint pos = this->mapToGlobal(e->pos());   // 必须为全局！！
    QModelIndex index = QModelIndex();
    QString path;
    if(e->button() == Qt::RightButton)
    {
        index = currentIndex();
        path = model->filePath(index);
        std::vector<std::wstring> paths;
        paths.push_back(path.toStdWString());
        OsShell::openShellContextMenuForObjects(paths, pos.x(), pos.y(), reinterpret_cast<void*>(winId()));
    }
}
