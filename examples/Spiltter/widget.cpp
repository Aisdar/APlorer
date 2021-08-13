#include "widget.h"
#include "splitter.h"
#include <QTreeView>
#include <QListView>
#include <QFileSystemModel>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initSplitter();
}

Widget::~Widget()
{
}

void Widget::initSplitter()
{
    // 设置两个View
    QTreeView *tree = new QTreeView(this);
    QListView *list = new QListView(this);
    QFileSystemModel *model = new QFileSystemModel;
    tree->setModel(model);
    list->setModel(model);
    model->setRootPath("");

    // 创建一个分裂器
    Splitter* splitter = new Splitter(this);
        // View组件加入分裂其，默认水平布局
    splitter->addWidget(tree);
    splitter->addWidget(list);


    // 将分离器使用布局管理，自动填充至窗口大小。
    QHBoxLayout *layout = new QHBoxLayout();
    this->setLayout(layout);
    layout->addWidget(splitter);

    //使用样式表把 QSplitter 分界线的背景色设置为蓝色，这是一种快速设置所有分界线背景色的方法。
    // 但是不推荐在代码中使用样式表，而推荐qss
    // 尝试注释一下样式？
    splitter->setStyleSheet("QSplitter::handle{background-color: pink}");
}

