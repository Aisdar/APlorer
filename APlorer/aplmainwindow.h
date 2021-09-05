#ifndef APLMAINWINDOW_H
#define APLMAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "tabbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class aplMainWindow; }
QT_END_NAMESPACE

class QFileSystemModel;



class aplMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    aplMainWindow(QWidget *parent = nullptr);
    ~aplMainWindow();
    void init();
    QFileSystemModel* fileModel();
    void copy(aplMainWindow* oldApl);

private slots:
    void on_actionforward_triggered();

    void on_actionhome_triggered();

    void on_actionSearch_triggered();

private:
    Ui::aplMainWindow *ui;

    QFileSystemModel *m_model;
    TabBar *bar;

    void initToolBar(); // 初始化工具栏
    void initBrowser(); // 初始化浏览窗口
    void setToolButtonActions(); // 设置按钮对应Action
    void setMenus(); // 设置菜单
    void initHomeTab(QWidget *& homePage); // 初始化主页菜单
protected:



};
#endif // APLMAINWINDOW_H
