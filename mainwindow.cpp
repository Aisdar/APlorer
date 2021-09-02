#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "everythingutil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->model = new QStandardItemModel;
    this->ui->tableView->setModel(model);

    on_lineEdit_textChanged("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    model->clear();
    this->model->setHorizontalHeaderItem(0, new QStandardItem("文件名"));
    this->model->setHorizontalHeaderItem(1, new QStandardItem("路径"));

    QVector<QFileInfo> fileInfos = EveryThingUtil::Search(arg1);
    QStandardItem *aItem_1, *aItem_2;
    for (int i = 0; i < fileInfos.length(); i++) {
        aItem_1 = new QStandardItem(fileInfos[i].fileName());
        aItem_2 = new QStandardItem(fileInfos[i].filePath());
        model->setItem(i, 0, aItem_1);
        model->setItem(i, 1, aItem_2);
    }
}
