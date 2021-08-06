#include "aplmainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QDebug>

aplMainWindow::aplMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->treeView->setModel(m_model);

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
            this->ui->treeView->setModel(model);
        }
    }
    else{
        qDebug() << "aplMainWindow::aplMainWindow(QWidget *, aplMainWindow *)->新窗口的参数\
                    aplMainWindow * 为空指针";
    }
}




