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
    ~SearchWindow();

private slots:
    void on_lineEdit_textChanged(const QString &);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QMenu *popMenu;
    QSortFilterProxyModel *proxyModel;
    QModelIndex idx;
    QString search_arg;
    QVector<QFileInfo> fileInfos;
};

#endif // SEARCHWINDOW_H
