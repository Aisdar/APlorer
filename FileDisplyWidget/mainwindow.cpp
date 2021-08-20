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
#include "dtaildelegate2.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 显示详细信息的测试
    ui->setupUi(this);
    // 文件信息显示的model
    model = new QStandardItemModel(this);
    // 隐藏垂直标头
    QHeaderView* vHeaderView =  ui->tableView->verticalHeader();
    vHeaderView->setHidden(true);
    // 平行标头可移动
    QHeaderView* hHeaderView = ui->tableView->horizontalHeader();
    hHeaderView->setMinimumSectionSize(50); // 最小的表头宽度
    hHeaderView->setSectionsMovable(true);
    // model设置完毕，关联TableView
    ui->tableView->setModel(model);
    // ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    // ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 菜单
    // 名称显示部分使用代理
    MyDelegate *delegate = new MyDelegate(this);
    ui->tableView->setItemDelegateForColumn(0, delegate);
    // 其他部分也使用代理，做到无法选择的效果
    DtailDelegate2 *delegate2 = new DtailDelegate2;
    for (int i = 1; i < 3; ++i)
        ui->tableView->setItemDelegateForColumn(i, delegate2);

    setCurrentPage("E:/"); // 设置主页为E盘测试

     // connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::openFile); // 连接双击信号和进入目录(废弃）
    connect(ui->tableView, &MyTableView::openFile, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//    QFileDialog *fileDialog = new QFileDialog(nullptr, "hhh", "", "All files(*)");
//    fileDialog->exec();
//    QFile f(fileDialog->selectedFiles().at(0));
//    QFileInfo info(f);
//    FileInfo i;
//    qFileInfoToFileInfo(&info, i);
//    lst_fileInfo.append(i);
//    QStandardItem* item = new QStandardItem;
//    item->setData(QVariant::fromValue(i));
//    int row = model->rowCount();
//    model->setItem(row, item);
//    model->setItem(row, 1, new QStandardItem(i.changeDate.toString()));
//    model->setItem(row, 2, new QStandardItem(i.type));
//    model->setItem(row, 3, new QStandardItem(QString::number(i.size/1024)));
//    // ui->tableView->openPersistentEditor(model->index(row, 0));
//    qDebug() << ui->tableView->columnWidth(1);
//    ui->tableView->setColumnWidth(1, 300);
}


void MainWindow::on_pushButton_2_clicked()
{
    if (dir.cdUp())
        // 返回上一级
        setCurrentPage(dir.path());
}

QString MainWindow::fileType(QFileInfo info)
{
    // 获得文件类型
    QFileIconProvider provider;
    QString type;
    if (provider.type(info) == "File Folder")
        // 文件夹直接替换内容
        type = "文件夹";
    else {
        // 其他替换掉为文件字样
        QString temp = provider.type(info);
        type = temp.replace("File", "文件");
    }
    return type;
}

QString MainWindow::sizeFormat(QFileInfo info)
{
    // 获取文件大小合适的显示方式
    if (info.size() == 0)
        return "";
    else if (info.size() < 1024)
        return QString::number(info.size()) + "B";
    else if (info.size()/1024 < 1024)
        return QString::number(info.size()/1024) + "KB";
    else if (info.size()/(1024*1024) < 1024)
        return QString::number(info.size()/(1024*1024)) + "MB";
    else
        return QString::number(info.size()/(1024*1024)) + "GB";
}

void MainWindow::setCurrentPage(QString path)
{
    // 测试，遍历C盘
    model->clear();
    model->setColumnCount(4); // 设置列数4列如下，这个不设置标头不会显示
    model->setHeaderData(0, Qt::Horizontal, "名称");
    model->setHeaderData(1, Qt::Horizontal, "修改日期");
    model->setHeaderData(2, Qt::Horizontal, "类型");
    model->setHeaderData(3, Qt::Horizontal, "大小");
    dir.setPath(path);
    // qDebug() << dir.currentPath();
    for (auto x: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
        // 过滤选择不要上一级和本级目录
        QStandardItem* item = new QStandardItem; // 第一列需要较为复杂的item
        int row = model->rowCount(); // 每次都是新增列，所以行数为rowCount
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件名
        item->setData(x.isDir(), Qt::UserRole+2); // 是否为文件夹
        model->setItem(row, 0, item); // 第一列文件名
        model->setItem(row, 1, new QStandardItem(x.lastModified().toString("yyyy/M/d hh:m"))); // 第二列上次修改日期
        model->setItem(row, 2, new QStandardItem(fileType(x))); // 第三列文件类型
        model->setItem(row, 3, new QStandardItem(sizeFormat(x))); // 第四列大小
    }
    // 设置tableView的合适宽度,这个大小依赖于代理中的SizeHint

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->selectionModel();
}

void MainWindow::openFile(QModelIndex index)
{
    if (index.isValid()) {
        // qDebug() << "row" << index.row() << "column" << index.column();
        if (index.column() != 0)
            index = model->index(index.row(), 0);
        setCurrentPage(index.data(Qt::UserRole+1).value<QString>());
    }

}



