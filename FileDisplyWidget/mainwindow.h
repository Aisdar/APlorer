#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStandardItem>
#include <QFileInfo>
#include <QStandardItemModel>
#include "detaildelegate.h"
#include "dtaildelegate2.h"
#include "listdelegate.h"
#include "bigicondelegate.h"
#include <QDir>
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum DisplayMode {
        DETAIL, // 详细信息模式
        LIST, // 列表模式
        BIGICON // 大图标模式
    };

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void openFile(QModelIndex index);

    // void closeEditor(QModelIndex index);

private:
    Ui::MainWindow *ui;
    QStandardItem *item;
    QStandardItemModel *model;
    QDir dir;
    DisplayMode currentModel;
    DetailDelegate *detailDelegate;
    DetailDelegate2 *detailDelegate2;
    ListDelegate *listDelegate;
    BigIconDelegate *bigIconDelegate;

    QString fileType(QFileInfo info); // 获得文件类型
    QString sizeFormat(QFileInfo info); // 获得文件大小信息

    void setCurrentPage(QString path, DisplayMode displayModel); // 设置最近页面
    void setDetailModel(); // 设置详细信息显示模式
    void setListModel(); // 设置列表显示模式
    void setBigIconModel(); // 设置大图标显示模型
    void resizeEvent(QResizeEvent *event) override;

};
#endif // MAINWINDOW_H
