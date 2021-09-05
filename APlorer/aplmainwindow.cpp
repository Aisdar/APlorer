#include "aplmainwindow.h"
#include "ui_aplmainwindow.h"
#include "driverwidget.h"
#include "customstyle.h"
#include "tabbar.h"
#include <QFileSystemModel>
#include <QDebug>
#include <QPushButton>

aplMainWindow::aplMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::aplMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("APlorer"); // 设置标题
    setToolButtonActions(); // 设置按钮对应的Action
    setMenus(); // 设置按钮对应的一些菜单
    initToolBar(); // 初始化工具栏
    initBrowser(); // 初始化浏览窗口
    QWidget *homePage = new QWidget(ui->brower);
    initHomeTab(homePage); // 初始化浏览窗口的HomePage
    ui->brower->addTab(homePage, QIcon(":/icon/default theme/home-.png"), "Home");
    // init需要外部显示使用
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


void aplMainWindow::setToolButtonActions()
{

    ui->btn_backspace->setDefaultAction(ui->actionbackward);
    ui->btn_backward->setDefaultAction(ui->actionbackward);
    ui->btn_forward->setDefaultAction(ui->actionforward);

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

void aplMainWindow::initHomeTab(QWidget *&homePageWidget)
{
    delete homePageWidget;
    homePageWidget = new QWidget(ui->brower);
    // 为页面新建布局
    QVBoxLayout *vLayout = new QVBoxLayout();
    // 布局中添加ScrollArea
    QScrollArea *scrollArea = new QScrollArea(homePageWidget);//ScrollArea一定要指定对应的parent，不然不显示
    // ScrollArea中添加Widget
    QWidget *scrollWidget = new QWidget(homePageWidget); // ScrollArea中对应的widget
    scrollArea->setWidget(scrollWidget);
    scrollArea->setMinimumWidth(570);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidgetResizable(true); // widget 自适应尺寸，不然不显示

    // 滚动区域的布局，网格布局方便放置驱动显示部件
    QGridLayout *driveLayout = new QGridLayout;
    driveLayout->setHorizontalSpacing(10); // 设置每个部件间间隔

    // 计算当前的布局中可以容纳驱动信息显示部件的个数
    int maxColumn = scrollArea->width()/((DriverWidget::bigR<<1)) - 1;
    // qDebug() << "scrollArea.width " << scrollArea->width() << " maxColumn：" << maxColumn;
    for (auto drive:QDir::drives()) {
        // 遍历所有盘
        static int count = 0; // 这个计划在有可移动接入时count改变，新增驱动显示控件，所以设为static
        DriverWidget *w = new DriverWidget(drive.filePath()); // 驱动控件
        int row = count/maxColumn, column = count%maxColumn;
        driveLayout->addWidget(w, row, column); // 将该控件添加到布局中
        count++;
    }
    scrollArea->widget()->setLayout(driveLayout); // 设置滚动区域的布局
    vLayout->addWidget(scrollArea); // 主页布局中添加盘信息的滚动控件
    // 添加各种分类内容
    QScrollArea *scrollArea2 = new QScrollArea(homePageWidget);
    QWidget *scrollWidget2 = new QWidget(homePageWidget);
    scrollArea2->setMinimumWidth(570);
    scrollArea2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea2->setWidgetResizable(true); // widget 自适应尺寸，不然不显示
    scrollArea2->setWidget(scrollWidget2);
    QGridLayout *classifyLayout = new QGridLayout;
    QPushButton *btn_music = new QPushButton(QIcon(":/icon/default theme/folder-music-fill.png"), "音乐");
    QPushButton *btn_video = new QPushButton(QIcon(":/icon/default theme/video-gallery.png"), "视频");
    QPushButton *btn_document = new QPushButton(QIcon(":/icon/default theme/file-pdf-fill.png"), "文档");
    QPushButton *btn_image = new QPushButton(QIcon(":/icon/default theme/photo.png"), "图片");
    QPushButton *btn_collect = new QPushButton(QIcon(":/icon/default theme/folder-info-fill.png"), "收藏");
    QPushButton *btn_zip = new QPushButton(QIcon(":/icon/default theme/folder-zip-fill.png"), "压缩文件");
    classifyLayout->setHorizontalSpacing(20);
    classifyLayout->addWidget(btn_music, 0, 0);classifyLayout->addWidget(btn_video, 0, 1);
    classifyLayout->addWidget(btn_document, 0, 2);classifyLayout->addWidget(btn_image, 0, 3);
    classifyLayout->addWidget(btn_collect, 1, 0); classifyLayout->addWidget(btn_zip, 1, 1);
    scrollWidget2->setStyleSheet("QPushButton{width:30px; height:50px}");
    scrollWidget2->setLayout(classifyLayout);
    vLayout->addWidget(scrollArea2);
    // 主页设置垂直布局
    homePageWidget->setLayout(vLayout);
}




void aplMainWindow::on_actionforward_triggered()
{

}

void aplMainWindow::initToolBar()
{
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

void aplMainWindow::initBrowser()
{
//    TabBar *bar = new TabBar(this);
//    bar->setTabsClosable(true);
//    bar->addTab(QIcon(":/home.png"), "Home");
//    bar->setPlusOnTabRight(true);
//    bar->setStyle(new CustomStyle);
}


void aplMainWindow::on_actionhome_triggered()
{
    int index = ui->brower->currentIndex();
    qDebug() << index;
    ui->brower->removeTab(index);
    QWidget* homePage = new QWidget;
    this->initHomeTab(homePage);
    ui->brower->insertTab(index, homePage, QIcon(":/icon/default theme/home-.png"), "Home");
    ui->brower->setCurrentIndex(index);
}

