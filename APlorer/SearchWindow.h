#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QVector>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SearchWindow : public QMainWindow
{
    Q_OBJECT

public:
    SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow() override;

public slots:
    void lineEdit_textChanged(const QString &);

private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QMenu *popMenu;
    QSortFilterProxyModel *proxyModel;
    QModelIndex idx;
    QString search_arg;
    QVector<QFileInfo> fileInfos;

};


QString getFileSize(const QFileInfo& fileInfo);
#endif // SEARCHWINDOW_H
