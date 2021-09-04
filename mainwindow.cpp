#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "everythingutil.h"

#include <QFileIconProvider>
#include <QVector>
#include <QDesktopServices>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Aplorer搜索");
    this->model = new QStandardItemModel;
    this->ui->tableView->setModel(model);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableView->verticalHeader()->setVisible(false);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setWindowIcon(QIcon("C:/Users/hellcat/Desktop/untitled/images/搜索.svg"));
    this->ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    initPopMenu();
    on_lineEdit_textChanged("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString getFileSize(const QFileInfo& fileInfo) {
    qint64 byteSize = fileInfo.size();
    if (byteSize == 0)
        return QString("");
    QVector<QString> vec { "B", "KB", "MB", "GB" };
    qint64 base = 1024;

    int i = 0;
    qint64 r = 0;
    while (byteSize >= base && i < vec.size()) {
        r = byteSize % base;
        byteSize /= base;
        i++;
    }
    QString res = QString::number(byteSize);
    if (r) {
        QString rs = QString::number(r);
        res += "." + rs[0] + rs[1];
    }
    res += vec[i];
    return res;
}

void MainWindow::on_lineEdit_textChanged(const QString &keywords)
{
    search_arg = keywords;
    model->clear();
    this->model->setHorizontalHeaderItem(0, new QStandardItem(""));
    this->model->setHorizontalHeaderItem(1, new QStandardItem("文件名"));
    this->model->setHorizontalHeaderItem(2, new QStandardItem("路径"));
    this->model->setHorizontalHeaderItem(3, new QStandardItem("大小"));

    QVector<QFileInfo> fileInfos = EveryThingUtil::Search(search_arg);
    QStandardItem *aItem_0, *aItem_1, *aItem_2, *aItem_3;
    QFileIconProvider provider;
    QIcon icon;

    for (int i = 0; i < fileInfos.length(); i++) {
        aItem_1 = new QStandardItem(fileInfos[i].fileName());
        aItem_2 = new QStandardItem(fileInfos[i].filePath());
        aItem_3 = new QStandardItem(getFileSize(fileInfos[i]));

        icon = provider.icon(fileInfos[i]);
        aItem_0 = new QStandardItem();
        aItem_0->setIcon(icon);

        model->setItem(i, 0, aItem_0);
        model->setItem(i, 1, aItem_1);
        model->setItem(i, 2, aItem_2);
        model->setItem(i, 3, aItem_3);
    }

    this->ui->tableView->setColumnWidth(0, 30);
    this->ui->tableView->setColumnWidth(1, 170);
    this->ui->tableView->setColumnWidth(2, 330);
}

void MainWindow::slot_context_menu(QPoint pos)
{
    idx = ui->tableView->indexAt(pos);
    if (idx.isValid()) {
        popMenu->exec(QCursor::pos());
    }
}

void MainWindow::slot_open_file()
{
    QString filePath =  model->item(idx.row(), 2)->text();
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void MainWindow::slot_delete_file()
{
    QString filePath =  model->item(idx.row(), 2)->text();
    QFile deleteFile(filePath);
    deleteFile.remove();
    on_lineEdit_textChanged(search_arg);
}

void MainWindow::slot_copy_file_path()
{
    QString filePath =  model->item(idx.row(), 2)->text();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(filePath);
}

void MainWindow::initPopMenu()
{
    popMenu = new QMenu(ui->tableView);

    QAction *deleteAction = new QAction(),
            *openAction = new QAction(),
            *copyPathAction = new QAction();
    openAction->setText(QString("打开"));
    deleteAction->setText(QString("删除"));
    copyPathAction->setText(QString("复制路径"));

    popMenu->addAction(openAction);
    popMenu->addAction(deleteAction);
    popMenu->addAction(copyPathAction);

    connect(openAction, SIGNAL(triggered()), this, SLOT(slot_open_file()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(slot_delete_file()));
    connect(copyPathAction, SIGNAL(triggered()), this, SLOT(slot_copy_file_path()));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_context_menu(QPoint)));
}
