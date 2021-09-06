#include "widget.h"
#include "ui_widget.h"
#include <driveiconwidget.h>
#include <QListWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    DriveIconWidget *icon = new DriveIconWidget("C:\\", this);
    connect(icon, &DriveIconWidget::doubleClicked, this, &Widget::devDoubleClicked);
    DriveIconWidget *dicon = new DriveIconWidget("D:\\", this);
    connect(dicon, &DriveIconWidget::doubleClicked, this, &Widget::devDoubleClicked);
    QListWidget *v = new QListWidget(this);
    QListWidgetItem *item = new QListWidgetItem(v);
    QListWidgetItem *ditem = new QListWidgetItem(v);
    item->setSizeHint(icon->sizeHint());
    v->addItem(item);
    v->setItemWidget(item, icon);

    ditem->setSizeHint(dicon->sizeHint());
    v->addItem(ditem);
    v->setItemWidget(ditem, dicon);

    v->setViewMode(QListWidget::IconMode);


    QHBoxLayout* lay = new QHBoxLayout();
    setLayout(lay);
    lay->addWidget(v);

    QLabel* lab = new QLabel("测试", this);
    QListWidgetItem *tItem = new QListWidgetItem(v);
    v->addItem(tItem);
    tItem->setSizeHint(dicon->sizeHint());
    v->setItemWidget(tItem, lab);
    lab->setStyleSheet("background:red");


    connect(v, &QListWidget::itemDoubleClicked, this, &Widget::clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::clicked(QListWidgetItem *item)
{
    qDebug() << item;
}

void Widget::devDoubleClicked()
{
    qDebug() << 1;
}

