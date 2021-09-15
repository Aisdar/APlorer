#include "mytableview.h"
#include "CShell.h"

myTableView::myTableView(QWidget* parent) : QTableView(parent) {

}

void myTableView::setFileInfo(const QVector<QFileInfo> &fileInfos)
{
    _fileInfos = fileInfos;
}

void myTableView::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button() == Qt::RightButton) {
        qDebug() << "在tableView中点击了右键";
        QModelIndex idx = this->indexAt(e->pos());
        QPoint pos = mapToGlobal(e->pos());
        if (idx.isValid()) {
            QString filePath(_fileInfos[idx.row()].path() + "/" + _fileInfos[idx.row()].fileName());
            std::vector<std::wstring> paths;
            paths.push_back(filePath.toStdWString());
            OsShell::openShellContextMenuForObjects(paths, pos.x(), pos.y(), reinterpret_cast<void*>(winId()));
        }
        qDebug() << idx.row() << " " << idx.column();
    }
}
