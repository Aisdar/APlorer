#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QDebug>
#include <QDir>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir::setCurrent("C:");
    QDir dir;
    dir.setPath("E://APlorer");
    qDebug() << dir.dirName();
    qDebug() << dir.nameFilters();
    for (auto x: dir.entryInfoList())
        qDebug() << x;
}

MainWindow::~MainWindow()
{
    delete ui;
}

