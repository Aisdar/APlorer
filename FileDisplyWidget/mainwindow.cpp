#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QDateTime>
#include <QTableView>
#include <QMimeType>
#include <QMimeDatabase>
#include <QStandardItemModel>
#include <QFileIconProvider>
#include <QDir>
#include "data.h"
#include "mydelegate.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 显示详细信息的测试
    model = new QStandardItemModel(this);
    MyDelegate *delegate = new MyDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, delegate);
    ui->tableView->setModel(model);

    QDir dir("E:");
    qDebug() << dir.count();
    qDebug() << dir.dirName();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QFileDialog *fileDialog = new QFileDialog(nullptr, "hhh", "", "All files(*)");
    fileDialog->exec();
    QFile f(fileDialog->selectedFiles().at(0));
    QFileInfo info(f);
    FileInfo i;
    qFileInfoToFileInfo(&info, i);
    lst_fileInfo.append(i);
    QStandardItem* item = new QStandardItem;
    item->setData(QVariant::fromValue(i));
    int row = model->rowCount();
    model->setItem(row, item);
    model->setItem(row, 1, new QStandardItem(i.changeDate.toString()));
    model->setItem(row, 2, new QStandardItem(i.type));
    model->setItem(row, 3, new QStandardItem(QString::number(i.size/1024)));
    ui->tableView->openPersistentEditor(model->index(row, 0));
    qDebug() << ui->tableView->columnWidth(1);
    ui->tableView->setColumnWidth(1, 300);
}


void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::qFileInfoToFileInfo(QFileInfo *info, FileInfo &i)
{
    i.fileName = info->fileName();
    i.size = info->size();
    i.changeDate = info->metadataChangeTime();
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(i.fileName);
    i.type = type.name();
}


