#ifndef APLMAINWINDOW_H
#define APLMAINWINDOW_H

#include "tabbar.h"
#include "SearchWindow.h"
#include "detaildelegate.h"
#include "detaildelegate2.h"
#include "bigicondelegate.h"
#include "contentdelegate.h"
#include "listdelegate.h"
#include <mytableview.h>

#include <QMainWindow>
#include <QMenu>
#include <QDir>


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
    SearchWindow* searchWindow;

    void initToolBar(); // 初始化工具栏

    void setMenus(); // 设置菜单
public:
    void setToolButtonActions(QAction *forward, QAction *backward); // 设置按钮对应Action
};
#endif // APLMAINWINDOW_H
