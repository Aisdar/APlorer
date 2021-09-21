#include <QMouseEvent>
#include "mytabwidget.h"
#include "customstyle.h"
#include <QHBoxLayout>
#include <QDebug>
#include "driverwidget.h"
#include <QDir>
#include <QPushButton>
#include <QTime>
#include "mytableview.h"
#include "aplmainwindow.h"

MyTabWidget::MyTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    this->setMinimumSize(915, 570);
    // 用我们的tabbar替换现有tabbar
    bar = new TabBar(this);
    bar->setTabsClosable(true);
    this->setTabBar(bar);
    bar->setElideMode(Qt::TextElideMode::ElideMiddle);
    this->setTabsClosable(false);

    // 关联加号和添加页面的槽函数
    connect(bar, &TabBar::plusClicked, this, [=]() {
        QWidget *w = new QWidget;
        initHomeTab(w);
        int index = addTab(w, "Home");
        setCurrentIndex(index);
        if (tabsClosable() == false)
            setTabsClosable(true);
    });

    // 关联关闭页面和对应槽函数
    connect(this, &MyTabWidget::tabCloseRequested, this, [=](int index) {
        removeTab(index);
        if (count() == 1)
            setTabsClosable(false);
    });
    connect(this, &MyTabWidget::currentChanged, this, &MyTabWidget::currentPageChanged);

    // 设置加号在标签右侧
    bar->setPlusOnTabRight(true);
    // 设置风格
    bar->setStyle(new CustomStyle);
}

MyTabWidget::~MyTabWidget()
{

}

void MyTabWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (QString(this->childAt(event->pos())->metaObject()->className()) == "DriverWidget") {
        DriverWidget *driver = static_cast<DriverWidget*>(this->childAt(event->pos()));
        QString driverPath =  driver->getDriveName();
        QWidget *page = new QWidget;
        initPageTab(driverPath, page);
        int index = this->currentIndex();
        this->removeTab(index);
        this->insertTab(index, page, driverPath);
        this->setCurrentIndex(index);
        this->resize(this->width(), this->height());
    }
}

void MyTabWidget::resizeEvent(QResizeEvent *event)
{
    QTabWidget::resizeEvent(event);
    MyTableView *view = this->currentWidget()->findChild<MyTableView *>();
    if (view) {
        view->setCurrentPage(view->getDir(), view->getCurrentMode(), true);
    }  
}

void MyTabWidget::initHomeTab(QWidget *&homePageWidget)
{
    // 初始化主页
    delete homePageWidget;
    homePageWidget = new QWidget(this);
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
    aplMainWindow *mainwindow = static_cast<aplMainWindow *>(this->parentWidget()->
                                                             parent()->parent()->parent());

    connect(btn_music, &QPushButton::clicked, [=]() {
       mainwindow->setSearchContent("*.mp3");
    });
    connect(btn_image, &QPushButton::clicked, [=]() {
        mainwindow->setSearchContent("*.jpg|*.png|*.jpeg|*.gif");
    });
    connect(btn_document, &QPushButton::clicked, [=]() {
        mainwindow->setSearchContent("*.doc|*.docx|*.pdf|*.pptx|*.xlsx|*.txt");
    });
    connect(btn_video, &QPushButton::clicked, [=]() {
        mainwindow->setSearchContent("*.mp4|*.3gp|*.rmvb");
    });
    connect(btn_zip, &QPushButton::clicked, [=] {
        mainwindow->setSearchContent("*.7z|*.zip|*.rar|*.gz|*.bz2");
    });
}

void MyTabWidget::initPageTab(QString path, QWidget *&page)
{
    delete page;
    page = new QWidget(this);
    page->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QVBoxLayout *vLayout = new QVBoxLayout();
    MyTableView *view = new MyTableView(path, MyTableView::BIGICON, page);
    aplMainWindow *mainwindow = static_cast<aplMainWindow *>(this->parentWidget()->
                                                             parent()->parent()->parent());

    mainwindow->setToolButtonActions(view->forward, view->backward);
    mainwindow->setLayoutMenu(view->layoutMenu);
    mainwindow->setHistoryMenu(view->historyMenu);
    mainwindow->addPathBox(path);
    vLayout->addWidget(view);
    page->setLayout(vLayout);

    connect(view, &MyTableView::currentPageChanged, mainwindow, &aplMainWindow::addPathBox);
    connect(view, &MyTableView::currentPageChanged1, mainwindow, &aplMainWindow::setPathBox);
    connect(view, SIGNAL(refreshPreview(QModelIndex)), mainwindow, SLOT(setPreviewLabel(QModelIndex)));
    connect(view, &MyTableView::currentPageChanged3, mainwindow, &aplMainWindow::setStatuBarString);
    connect(view, &MyTableView::currentPageChanged, mainwindow, &aplMainWindow::setTreeView);
    connect(view, &MyTableView::backHome, mainwindow, &aplMainWindow::on_actionhome_triggered);
}


void MyTabWidget::currentPageChanged(int index)
{
    aplMainWindow *mainwindow = static_cast<aplMainWindow *>(this->parentWidget()->
                                                             parent()->parent()->parent());
    static int preIndex = index;
    if (index != preIndex) {
        mainwindow->setSearchWindowHidden(true);
        MyTableView* view = this->widget(preIndex)->findChild<MyTableView *>();

        if (view)
        {
            disconnect(view, SIGNAL(refreshPreview(QModelIndex)), mainwindow, SLOT(setPreviewLabel(QModelIndex)));
            disconnect(view, &MyTableView::backHome, mainwindow, &aplMainWindow::on_actionhome_triggered);
        }
    }

    MyTableView* view =  this->currentWidget()->findChild<MyTableView *>();
    if (view)
    {
        mainwindow->setToolButtonActions(view->forward, view->backward);
        mainwindow->setLayoutMenu(view->layoutMenu);
        mainwindow->setHistoryMenu(view->historyMenu);
        connect(view, SIGNAL(refreshPreview(QModelIndex)), mainwindow, SLOT(setPreviewLabel(QModelIndex)));
        connect(view, &MyTableView::backHome, mainwindow, &aplMainWindow::on_actionhome_triggered);
    }
}


