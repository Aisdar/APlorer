#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H

#include <QTreeView>

class MyTreeView : public QTreeView
{
    Q_OBJECT
public:
    MyTreeView(QWidget *parent = nullptr);
    void setCurrentPage(QString path);

protected slots:
    void itemClicked(const QModelIndex &index);


signals:
    void itemData(QString filePath);
};

#endif // MYTREEVIEW_H
