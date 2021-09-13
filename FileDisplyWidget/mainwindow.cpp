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
#include <QProcess>
#include <QDesktopServices>
#include <QSize>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 显示详细信息的测试
    ui->setupUi(this);
    // 文件信息显示的model
    model = new QStandardItemModel(this);
//    // 隐藏垂直标头
//    QHeaderView* vHeaderView =  ui->tableView->verticalHeader();
//    vHeaderView->setHidden(true);
//    // 平行标头可移动
//    QHeaderView* hHeaderView = ui->tableView->horizontalHeader();
//    hHeaderView->setMinimumSectionSize(50); // 最小的表头宽度
//    hHeaderView->setSectionsMovable(true);

    // 创建代理
    detailDelegate = new DetailDelegate(this);
    detailDelegate2 = new DetailDelegate2(this);
    listDelegate = new ListDelegate(this);
    bigIconDelegate = new BigIconDelegate(this);
    // model设置完毕，关联TableView
    ui->tableView->setModel(model);
    // ui->tableView->setEditTriggers(QTableView::NoEditTriggers);
    // ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 菜单

    setCurrentPage("E:/", LIST); // 设置主页为E盘测试

     // connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::openFile); // 连接双击信号和进入目录(废弃）
    connect(ui->tableView, &MyTableView::openFile, this, &MainWindow::openFile);
    connect(ui->tableView, &QTableView::customContextMenuRequested, [=](){
        qDebug() << 1;
    });
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
        setCurrentPage(dir.path(), currentModel);
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

void MainWindow::setCurrentPage(QString path, DisplayMode displayModel)
{
    // 改变当前路径
    if (path != dir.path())
        dir.setPath(path);
    if (currentModel != displayModel) {
        currentModel = displayModel;
        QHeaderView* hHeaderView =  ui->tableView->horizontalHeader();
        switch (currentModel) {
        case DETAIL:
            // 名称显示部分使用代理
            ui->tableView->setItemDelegateForColumn(0, detailDelegate);
            // 其他部分也使用代理，做到无法选择的效果
            for (int i = 1; i < 4; ++i)
                ui->tableView->setItemDelegateForColumn(i, detailDelegate2);
            break;
        case LIST:
            ui->tableView->setItemDelegate(listDelegate);
            // 隐藏水平表头
            hHeaderView->setHidden(true);
            break;
        case BIGICON:
            ui->tableView->setItemDelegate(bigIconDelegate);
            hHeaderView->setHidden(true);
            break;
        }
    }
    switch (currentModel) {
    case DETAIL:
        setDetailModel();
        break;
    case LIST:
        setListModel();
        break;
    case BIGICON:
        setBigIconModel();
        break;
    }
    // 设置tableView的合适宽度,这个大小依赖于代理中的SizeHint
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->selectionModel();
}

void MainWindow::setDetailModel()
{
    model->clear();
    model->setColumnCount(4); // 设置列数4列如下，这个不设置标头不会显示
    model->setHeaderData(0, Qt::Horizontal, "名称");
    model->setHeaderData(1, Qt::Horizontal, "修改日期");
    model->setHeaderData(2, Qt::Horizontal, "类型");
    model->setHeaderData(3, Qt::Horizontal, "大小");

    // qDebug() << "currentPath:" << dir.currentPath() << " Path:" << dir.path();
    for (auto x: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
        // 过滤选择不要上一级和本级目录
        // qDebug() << x;
        QStandardItem* item = new QStandardItem; // 第一列需要较为复杂的item
        int row = model->rowCount(); // 每次都是新增列，所以行数为rowCount
        item->setData(x.fileName(), Qt::DisplayRole); // 排序用文件名
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件绝对路径
        item->setData(x.isDir(), Qt::UserRole+2); // 是否为文件夹
        model->setItem(row, 0, item); // 第一列文件名
        model->setItem(row, 1, new QStandardItem(x.lastModified().toString("yyyy/M/d hh:m"))); // 第二列上次修改日期
        model->setItem(row, 2, new QStandardItem(fileType(x))); // 第三列文件类型
        model->setItem(row, 3, new QStandardItem(sizeFormat(x))); // 第四列大小
    }
}

void MainWindow::setListModel()
{
    model->clear();
    int row = 0;
    for (auto x: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
        // 过滤选择不要上一级和本级目录
        // qDebug() << x;
        QStandardItem* item = new QStandardItem; // 第一列需要较为复杂的item
        item->setData(x.fileName(), Qt::DisplayRole); // 文件名
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件绝对路径名
        static int maxColumn;
        if (row == 0) {
            model->setItem(row, 0, item);
            maxColumn = ui->tableView->contentsRect().height()/ui->tableView->rowHeight(0) - 1;
            row++;
        } else {
            model->setItem(row%maxColumn, row/maxColumn, item);
            row++;
        }
    }
}

void MainWindow::setBigIconModel()
{
    model->clear();
    int count = 0;
    for (auto x: dir.entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries)) {
        // 过滤选择不要上一级和本级目录
        // qDebug() << x;
        QStandardItem* item = new QStandardItem; // 第一列需要较为复杂的item
        item->setData(x.fileName(), Qt::DisplayRole); // 文件名
        item->setData(x.absoluteFilePath(), Qt::UserRole+1); // 文件绝对路径名
        static int maxColumn;
        if (count == 0) {
            model->setItem(count, 0, item);
            maxColumn = ui->tableView->contentsRect().width()/ui->tableView->columnWidth(0) - 1;
            qDebug() << maxColumn;
            count++;
        } else {
            model->setItem(count/maxColumn, count%maxColumn, item);
            count++;
        }
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (currentModel == LIST) {
        this->setCurrentPage(dir.absolutePath(), LIST);
    }
}

void MainWindow::openFile(QModelIndex index)
{
    if (index.isValid()) {
        QString absolutePath;
        QFileInfo info;
        switch (currentModel) {
        case DETAIL:
            if (index.column() != 0)
                index = model->index(index.row(), 0);
            absolutePath = index.data(Qt::UserRole+1).value<QString>();
            info.setFile(absolutePath);
            if (info.isDir())
                // 是文件夹打开文件夹
                setCurrentPage(index.data(Qt::UserRole+1).value<QString>(), currentModel);
            else
                QDesktopServices::openUrl(QUrl::fromLocalFile(absolutePath));
            break;
        case LIST:
            absolutePath = index.data(Qt::UserRole+1).value<QString>();
            info.setFile(absolutePath);
            if (info.isDir())
                // 是文件夹打开文件夹
                setCurrentPage(index.data(Qt::UserRole+1).value<QString>(), currentModel);
            else
                QDesktopServices::openUrl(QUrl::fromLocalFile(absolutePath));
            break;
        }
    }

}



