#include "mytreeview.h"
#include <QFileSystemModel>
#include <QDebug>

MyTreeView::MyTreeView(QWidget *parent)
    : QTreeView(parent)
{
    connect(this, &QAbstractItemView::clicked, this, &MyTreeView::itemClicked);
}

void MyTreeView::setCurrentPage(QString path)
{
    QFileSystemModel *model = static_cast<QFileSystemModel *>(this->model());
    model->setRootPath(path);
}

void MyTreeView::itemClicked(const QModelIndex &index)
{
    QFileSystemModel *model = static_cast<QFileSystemModel *>(this->model());
    QString path = model->filePath(index);
    emit itemData(path);
}
