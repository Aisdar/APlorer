#include "widget.h"
#include "ui_widget.h"
#include "customstyle.h"
#include "tabbar.h"
#include <QHBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    TabBar* bar = new TabBar(this);
    bar->setTabsClosable(true);
    this->setTabBar(bar);
    for(int i = 0; i < 2; i++)
    {
        bar->addTab("123");
    }
    bar->setPlusOnTabRight(true);
    bar->setStyle(new CustomStyle);
    this->setWindowTitle("不开启'+'标签右侧显示");
}

Widget::~Widget()
{
    delete ui;
}

