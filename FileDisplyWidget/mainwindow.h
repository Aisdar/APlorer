#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStandardItem>
#include <QFileInfo>
#include <QStandardItemModel>
#include "data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItem *item;
    QStandardItemModel *model;
    QList <FileInfo> lst_fileInfo;
    void qFileInfoToFileInfo(QFileInfo *info, FileInfo &info2);
};
#endif // MAINWINDOW_H
