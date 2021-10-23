#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // 测试用
    QTabBar *bar = ui->tabWidget->tabBar();
    int index = ui->tabWidget->currentIndex();
    // bar->setTabEnabled(index, false);
    QIcon icon(":/add.png");
    QPushButton *button = new QPushButton(icon, "+", this);
    bar->setTabButton(index, QTabBar::LeftSide, button);
}

