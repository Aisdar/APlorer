#include "widget.h"
#include "ui_widget.h"

#include "tabbar.h"
#include <QHBoxLayout>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    TabBar* bar = new TabBar(this);
    this->setTabBar(bar);
    for(int i = 0; i < 2; i++)
    {
        bar->addTab("123");
    }
    connect(bar, &TabBar::plusClicked, [=]
    {
        bar->addTab("aab");
    });
    bar->setPlusVisiable(false);
    this->setWindowTitle("Qt原版的标签条");
}

Widget::~Widget()
{
    delete ui;
}

