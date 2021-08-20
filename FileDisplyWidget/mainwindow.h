#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QStandardItem>
#include <QFileInfo>
#include <QStandardItemModel>
#include "data.h"
#include <QDir>
#include <QEvent>

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

    void openFile(QModelIndex index);

    // void closeEditor(QModelIndex index);

private:
    Ui::MainWindow *ui;
    QStandardItem *item;
    QStandardItemModel *model;
    QList <FileInfo> lst_fileInfo;
    QDir dir;

    QString fileType(QFileInfo info);
    QString sizeFormat(QFileInfo info);

    void setCurrentPage(QString path);

};
#endif // MAINWINDOW_H
