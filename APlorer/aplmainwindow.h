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
#include <QLabel>
#include <QMenu>
#include <QDir>
#include <QToolButton>


QT_BEGIN_NAMESPACE
namespace Ui { class aplMainWindow; }
QT_END_NAMESPACE

class QFileSystemModel;



class aplMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    aplMainWindow(QWidget *parent = nullptr);
    ~aplMainWindow() override;

    void init();
    QFileSystemModel* fileModel();
    void copy(aplMainWindow* oldApl);

private slots:

    void on_actionhome_triggered(); // 主页

    void on_actionSearch_triggered();

    void on_pathBox_currentIndexChanged(const QString &arg1); // 路径改变

    void on_directoryTree_clicked(const QModelIndex &index); // 路径树改变

    void slt_hidePreview(); // 预览窗口

    void on_searchBox_textChanged(const QString &arg1); // 搜索框改变

    void on_aplMainWindow_destroyed();

private:
    Ui::aplMainWindow *ui;
    QFileSystemModel *m_model;
    TabBar *bar;
    SearchWindow* searchWindow;
    QToolButton *btn_layout;
    QToolButton *btn_rank;
    QToolButton *btn_hide;
    QLabel *label_statuBar;

    void initToolBar(); // 初始化工具栏
    void resizeEvent(QResizeEvent *e) override;
    void moveEvent(QMoveEvent *event) override;

public slots:
    void setToolButtonActions(QAction *forward, QAction *backward); // 设置按钮对应Action
    void setLayoutMenu(QMenu *menu); // 设置布局按钮对应菜单
    void setHistoryMenu(QMenu *menu); // 设置历史路径的菜单
    void setPathBox(QString path); // 设置路径框
    void addPathBox(QString path); // 添加路径框
    void setRankMenu(QMenu *menu); // 设置排序菜单
    void setPreviewLabel(QModelIndex index); // 设置预览窗
    void setStatuBarString(QString text); // 设置状态栏文字
    void setSearchContent(QString text); // 设置搜索文字
};
#endif // APLMAINWINDOW_H
