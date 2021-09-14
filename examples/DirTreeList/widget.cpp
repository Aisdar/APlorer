#include "widget.h"
#include "ui_widget.h"
#include <QFileSystemModel>
#include <QDebug>
#include <QStandardItemModel>
#include "mydelegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);

    ui->treeView->setModel(model);
   //  ui->listView->setModel(model);

    QStandardItemModel *model1 = new QStandardItemModel;
    model1->setItem(0, 0, new QStandardItem("111"));
    ui->listView->setModel(model1);
    ui->listView->setEditTriggers(QListView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->listView->setItemDelegate(new MyDelegate);
    init();

    model->setRootPath("C:\\");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    // 隐藏左侧treeView的size、type...等列
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);
    // 绑定一些信号
    connect(ui->treeView, &QTreeView::clicked, this, &Widget::treeViewIndexClicked);
    // connect(ui->listView, &QListView::doubleClicked, this, &Widget::listViewIndexDoubleClicked);

    // List
    ui->listView->setResizeMode(QListView::Adjust);   // 设置大小模式自动调节
    ui->listView->setMovement(QListView::Static);     // 设置单元项不可被拖动
    ui->listView->setTextElideMode(Qt::TextElideMode::ElideRight); // 省略的方式：省略号在右侧


    // 绑定按钮
    connect(ui->BtnIcon, &QPushButton::clicked, this, [=]{
       ui->listView->setViewMode(QListView::ViewMode::IconMode);

       ui->listView->setIconSize(QSize(100, 100));
       ui->listView->setGridSize(QSize(100, 100));

    });

    connect(ui->BtnList, &QPushButton::clicked, this, [=]{
       ui->listView->setViewMode(QListView::ViewMode::ListMode);
       ui->listView->setGridSize(QSize(-1, -1));
       ui->listView->setIconSize(QSize(-1, -1));
    });
}

void Widget::treeViewIndexClicked(const QModelIndex &index)
{
    // 文件夹则右侧展示详细
    QFileInfo file(model->filePath(index));
    if(file.isDir())
    {
        ui->listView->setRootIndex(index);
    }
}

void Widget::listViewIndexDoubleClicked(const QModelIndex &index)
{
    // 双击list的文件夹时会进入
    QFileInfo file(model->filePath(index));
    if(file.isDir())
    {// list处 文件夹进入，非文件夹不进入
        ui->listView->setRootIndex(index);
    }
    // 双击list时左侧tree会同步展开当前点击项
    ui->treeView->setCurrentIndex(index);

}


