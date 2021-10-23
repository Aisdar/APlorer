#include "tabwidget.h"
#include "customstyle.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    // 添加三个页面
    QTabBar *bar = this->tabBar();
    this->addTab(new QWidget, "Home");
    this->addTab(new QWidget, "C://");
    this->addTab(new QWidget, "");
    bar->setTabData(0, 0);
    bar->setTabData(1, 1);


    // 修改最后一个页面作为控制页面
    QToolButton *btn_createNewTab = new QToolButton(this);
    act_createNewTab = new QAction(QIcon(":/add.png"), "add page");
    btn_createNewTab->setDefaultAction(act_createNewTab);
    btn_createNewTab->setToolButtonStyle(Qt::ToolButtonIconOnly);
    bar->setTabButton(2, QTabBar::LeftSide, btn_createNewTab);
    bar->setTabEnabled(2, false);
    //
    act_closeTab = new QAction("x");
    // 设置显示风格
    bar->setStyle(new CustomStyle);

   // 设置页面模式
   this->setTabClosable(true);

    // 连接信号和槽
    connect(act_createNewTab, SIGNAL(triggered()), this, SLOT(slt_createNewTab()));
//    connect(act_closeTab, &QAction::triggered, tabBar(), &QTabBar::tabCloseRequested);
    // connect(act_closeTab, SIGNAL(triggered(int i)), this, SLOT(slt_removeTab(int)));
}

void TabWidget::setTabClosable(bool flag)
{
    QTabBar *bar = this->tabBar();
    if (flag) {
        for (int i = 0; i < count()-1; ++i) {
           if (!bar->tabButton(i, QTabBar::RightSide)) {
                // 遍历页面，为所有页面都加上关闭按钮
                QToolButton *btn_closeButton = new QToolButton(this); // 新建关闭按钮
                btn_closeButton->setDefaultAction(act_closeTab); // 关联对应Action
                bar->setTabButton(i, QTabBar::RightSide, btn_closeButton); // 向页面上设置按钮
//                connect(btn_closeButton, &QToolButton::clicked, tabBar(), &QTabBar::tabCloseRequested);
                connect(btn_closeButton, &QToolButton::clicked, [=](){
                    if (count() == 3) {
                        // 只剩3个页面，只能再多关闭一个
                        for (int j = 0; j < count(); ++j) {
                            // 遍历所有页面，通过访问他们页面包含的索引信息是否匹配来判断是否是要关闭的页面
                            // 但是有个缺陷，如果页面移动仍然可能关闭后来新建的页面
                            if (bar->tabData(j).toInt() == i) {
                                qDebug() << j;
                                removeTab(j);
                                break;
                            }
                        }

                        // 用于删除最后一个页面的关闭按钮，但是总是错误

                    }  else {
                        // 原理同上
                        for (int j = 0; j < count(); ++j) {
                            if (bar->tabData(j).toInt() == i) {
                                qDebug() << j;
                                removeTab(j);
                                break;
                            }
                        }
                    }
                });
            }

        }
    } else {
        for (int i = 0; i < count()-1; ++i) {
            // 遍历页面，为所有页面删除按钮
            delete bar->tabButton(i, QTabBar::RightSide);
        }
    }
}

void TabWidget::slt_createNewTab()
{
    // 按下加号后触发的槽函数，用来新建窗口并且为窗口指定它当前的索引值
    static int i = 0; // 这个用来辨识窗口，观察是否有关闭错误的情况
    this->insertTab(count()-1, new QWidget, "E://" + QString::number(i++));
    QTabBar *bar = this->tabBar();
    bar->setTabData(count()-2, count()-2); // 为新建的窗口赋予它当前的索引值
    setTabClosable(true); // 显示关闭的按钮
}

void TabWidget::slt_closeTab()
{
    // 预想能用上的函数，不确定

}




