#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QFileSystemModel;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void init();

private slots:
    void treeViewIndexClicked(const QModelIndex &index);
    void listViewIndexDoubleClicked(const QModelIndex &index);

private:
    Ui::Widget *ui;

    QFileSystemModel* model;

};
#endif // WIDGET_H
