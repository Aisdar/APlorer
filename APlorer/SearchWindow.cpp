#include "SearchWindow.h"
#include "ui_SearchWindow.h"
#include "everythingutil.h"
#include "CShell.h"
#include <QFileIconProvider>
#include <QVector>
#include <QDesktopServices>
#include <QClipboard>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QUrl>
#include <QMouseEvent>

SearchWindow::SearchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Aplorer搜索");
    this->setWindowIcon(QIcon(":/Search.svg"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    this->model = new QStandardItemModel;
    this->proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);

    this->ui->tableView->setModel(proxyModel);
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableView->verticalHeader()->setVisible(false);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    this->ui->tableView->setSortingEnabled(true);


    lineEdit_textChanged("");
}

SearchWindow::~SearchWindow()
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

void SearchWindow::lineEdit_textChanged(const QString &keywords)
{
    search_arg = keywords;
    model->clear();
    this->model->setHorizontalHeaderItem(0, new QStandardItem(""));
    this->model->setHorizontalHeaderItem(1, new QStandardItem("文件名"));
    this->model->setHorizontalHeaderItem(2, new QStandardItem("路径"));
    this->model->setHorizontalHeaderItem(3, new QStandardItem("大小"));
    this->model->setHorizontalHeaderItem(4, new QStandardItem("修改日期"));

    fileInfos = EveryThingUtil::Search(search_arg);
    this->ui->tableView->setFileInfo(fileInfos);

    QStandardItem *aItem_0, *aItem_1, *aItem_2, *aItem_3, *aItem_4;
    QFileIconProvider provider;
    QIcon icon;

    for (int i = 0; i < fileInfos.length(); i++) {
        aItem_1 = new QStandardItem(fileInfos[i].fileName());
        aItem_2 = new QStandardItem(fileInfos[i].filePath());
        aItem_3 = new QStandardItem(getFileSize(fileInfos[i]));
        aItem_4 = new QStandardItem(fileInfos[i].lastModified().toString("yyyy-MM-dd HH:mm"));

        icon = provider.icon(fileInfos[i]);
        aItem_0 = new QStandardItem();
        aItem_0->setIcon(icon);

        model->setItem(i, 0, aItem_0);
        model->setItem(i, 1, aItem_1);
        model->setItem(i, 2, aItem_2);
        model->setItem(i, 3, aItem_3);
        model->setItem(i, 4, aItem_4);
    }

    this->ui->tableView->setColumnWidth(0, 30);
    this->ui->tableView->setColumnWidth(1, 170);
    this->ui->tableView->setColumnWidth(2, 330);
    this->ui->tableView->setColumnWidth(4, 150);
}





void SearchWindow::on_tableView_clicked(const QModelIndex &index)
{

}

