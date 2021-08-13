#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setUsesScrollButtons(true);
    this->setMinimumSize(500, 300);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QIcon icon(":/add.png");
    this->addTab(new QWidget,icon, "1111111111111111111111111111111111111111111");
    this->addTab(new QWidget,icon, "2");
    this->addTab(new QWidget,icon, "3");
    initControlPart();
    this->setCornerWidget(controlBar);
    this->setTabsClosable(true);
    this->setMovable(true);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slt_removeTab(int)));
}


void TabWidget::initControlPart()
{
    // 初始化控制组件
    controlBar = new QToolBar(this); // 这个控制组件是一个ToolBar
    QIcon icon(":/add.png");  // 设置图标为加号
    QAction *act_addTab = new QAction(icon, "+", controlBar); // 触发的QAction
    controlBar->addAction(act_addTab);
    paddingWidget = new QWidget(); // 作为间隔的一个空白空间
    controlBar->addWidget(paddingWidget);
    controlBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    int width1 = width()-this->count()*(50+this->iconSize().width())-controlBar->iconSize().width()*count(); // 计算空白空间合适的宽度
    paddingWidget->setMinimumWidth(width1);
//    qDebug() << "tabWidget::width:" << width();
//    qDebug() << "count:" << this->count();
//    qDebug() << "tabBar().width()" << this->tabBar()->width();
//    qDebug() << "controlBar->iconSize().width():" << controlBar->iconSize().width();
//    qDebug() << "toolBarWidth:" << width1;


    connect(act_addTab, SIGNAL(triggered()), this, SLOT(slt_addTab())); // 连接添加页面Action和对应的槽函数
}

void TabWidget::slt_addTab()
{
    if (!tabsClosable())
        // 开启页面可关闭
        setTabsClosable(true);
    this->addTab(new QWidget, "1");
    int width1 = width()-this->count()*(50+this->iconSize().width())-controlBar->iconSize().width()*count();
    paddingWidget->setMinimumWidth(width1);
}

void TabWidget::slt_removeTab(int index)
{
    if (count() > 2) {
        // 在页面为大于2，都可以关闭
        removeTab(index);
        int width1 = width()-this->count()*(50+this->iconSize().width())-controlBar->iconSize().width()*count();
        paddingWidget->setMinimumWidth(width1);
    } else if (count() == 2){
        // 页面为2时，仅可再关闭一个
        removeTab(index);
        int width1 = width()-this->count()*(50+this->iconSize().width())-controlBar->iconSize().width()*count();
        paddingWidget->setMinimumWidth(width1);
        setTabsClosable(false);
    }
}
