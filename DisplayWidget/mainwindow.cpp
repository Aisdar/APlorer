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
    // qDebug() << "cleanPath:" << QDir::cleanPath("此电脑\迅雷下载");
    // qDebug() << QDir::drives();
//    QWidget *wd = new QWidget(this);
//    QHBoxLayout *driveLayout = new QHBoxLayout(this);
//    wd->setLayout(driveLayout);
//    ui->scrollArea->setWidget(wd);
    static QGridLayout driveLayout;
    driveLayout.setHorizontalSpacing(10);
    int maxColumn = ui->scrollArea->width()/((DriverWidget::bigR<<1)) - 1;
    // qDebug() << "maxColumn:" << maxColumn;
    for (int i = 0; i < 10; ++i)
    {
        for (auto drive:QDir::drives()) {
            static int count = 0;

            // qDebug() << drive.filePath();// 获得驱动名称
            //        ULARGE_INTEGER FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes;
            //        // GetDiskFreeSpaceExA("C:", &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes);
            //        if (GetDiskFreeSpaceExA(drive.filePath().toUtf8(), &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes)) {
            //                qDebug() << TotalNumberOfBytes.QuadPart/GB << "GB";
            //                qDebug() << TotalNumberOfFreeBytes.QuadPart/GB << "GB";
            //        } else
            //            qDebug() << "错误：获取磁盘属性内容失败";

            DriverWidget *w = new DriverWidget(drive.filePath());
            w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            w->setMinimumSize((DriverWidget::bigR<<1)+10, (DriverWidget::bigR<<1)+10);
            int row = count/maxColumn, column = count%maxColumn;
            driveLayout.addWidget(w, row, column);
            count++;
        }
    }
    ui->scrollArea->widget()->setLayout(&driveLayout);
}

