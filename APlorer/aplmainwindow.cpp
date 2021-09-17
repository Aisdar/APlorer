#include "aplmainwindow.h"
#include "ui_aplmainwindow.h"
#include "driverwidget.h"
#include "customstyle.h"
#include "tabbar.h"
#include "SearchWindow.h"
#include "everythingutil.h"

#include <QFileSystemModel>
#include <QDebug>
#include <QPushButton>
#include <QTableView>
#include <QApplication>
#include <QTranslator>
#include <QStandardItemModel>
#include <QDesktopServices>
#include <QDateTime>
#include <QFileIconProvider>

aplMainWindow::aplMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::aplMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("APlorer"); // 设置标题
    // setToolButtonActions(); // 设置按钮对应的Action
    setMenus(); // 设置按钮对应的一些菜单
    initToolBar(); // 初始化工具栏
    QWidget *homePage = new QWidget(ui->brower);
    ui->brower->initHomeTab(homePage); // 初始化浏览窗口的HomePage
    ui->brower->addTab(homePage, QIcon(":/icon/default theme/home-.png"), "Home"); // 添加一个页面

}

aplMainWindow::~aplMainWindow()
{
    delete ui;
}

void aplMainWindow::init()
{
    // 文件模型M
    m_model = new QFileSystemModel;
    m_model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    // [重要]设置根目录，直接初始化了磁盘索引信息到M中
    m_model->setRootPath("c:");
    // 设置模型
    ui->directoryTree->setModel(m_model);


    //    ui->treeView->setSortingEnabled(true);
}

QFileSystemModel *aplMainWindow::fileModel()
{
    return m_model;
}

void aplMainWindow::copy(aplMainWindow *oldApl)
{
    if(oldApl){
        QFileSystemModel* model = oldApl->fileModel();
        if(model){
            this->ui->directoryTree->setModel(model);
        }
    }
    else{
        qDebug() << "aplMainWindow::aplMainWindow(QWidget *, aplMainWindow *)->新窗口的参数aplMainWindow * 为空指针";\
    }
}


void aplMainWindow::setToolButtonActions(QAction *forward, QAction *backward)
{
    // 设置按钮对应Action
    ui->btn_backward->setDefaultAction(backward);
    ui->btn_forward->setDefaultAction(forward);
}


void aplMainWindow::setMenus()
{
    // 设置前进后退按钮的下拉式菜单
   QMenu *backwardMenu = new QMenu(this);
   QMenu *forwardMenu = new QMenu(this);
   // backwardMenu->addAction(ui->actionforward);

   ui->btn_backward->setPopupMode(QToolButton::MenuButtonPopup);
   ui->btn_backward->setToolButtonStyle(Qt::ToolButtonIconOnly);
   ui->btn_backward->setMenu(backwardMenu);

   ui->btn_forward->setPopupMode(QToolButton::MenuButtonPopup);
   ui->btn_forward->setToolButtonStyle(Qt::ToolButtonIconOnly);
   ui->btn_forward->setMenu(forwardMenu);

}


void aplMainWindow::on_actionforward_triggered()
{
    // 前进按钮
}

void aplMainWindow::initToolBar()
{
    // 初始化工具栏
    // 一个空白
    QWidget *emptyWidget1 = new QWidget(this);
    emptyWidget1->setFixedSize(60, 35);
    ui->toolBar->insertWidget(ui->actionsetting, emptyWidget1);

    // 排序按钮和菜单
    QMenu *rankMenu = new QMenu(this);
    rankMenu->addAction("修改日期排序");
    rankMenu->addAction("名称排序");
    rankMenu->addAction("大小排序");
    rankMenu->addSeparator();
    rankMenu->addAction("递增");
    rankMenu->addAction("递减");

    QToolButton *btn_rank = new QToolButton(this);
    btn_rank->setIcon(QIcon(":/icon/default theme/rank.png"));
    btn_rank->setText("排序");
    btn_rank->setPopupMode(QToolButton::MenuButtonPopup);
    btn_rank->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn_rank->setMenu(rankMenu);

    ui->toolBar->insertWidget(ui->actionsetting, btn_rank);
    // 布局按钮和菜单
    QMenu *layoutMenu = new QMenu(this);
    layoutMenu->addAction(ui->actionbigIcon);
    layoutMenu->addAction(ui->actionsmallIcon);
    layoutMenu->addAction(ui->actiondetails);

    QToolButton *btn_layout = new QToolButton(this);
    btn_layout->setIcon(QIcon(":/icon//default theme/grid.png"));
    btn_layout->setText("布局");
    btn_layout->setPopupMode(QToolButton::MenuButtonPopup);
    btn_layout->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn_layout->setMenu(layoutMenu);
    ui->toolBar->insertWidget(ui->actionsetting, btn_layout);

    // 添加设置按钮
    QWidget *emptyWidget2 = new QWidget(this);
    emptyWidget2->setFixedSize(200, 35);
    ui->toolBar->insertWidget(ui->actionsetting, emptyWidget2);
}


void aplMainWindow::on_actionhome_triggered()
{
    // 回到主页
    int index = ui->brower->currentIndex();
    ui->brower->removeTab(index);
    QWidget* homePage = new QWidget;
    ui->brower->initHomeTab(homePage);
    ui->brower->insertTab(index, homePage, QIcon(":/icon/default theme/home-.png"), "Home");
    ui->brower->setCurrentIndex(index);

}


void aplMainWindow::on_actionSearch_triggered()
{
    EveryThingUtil::openEverything();
    searchWindow = new SearchWindow();
    searchWindow->show();
}


