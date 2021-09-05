#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

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
    void on_lineEdit_textChanged(const QString &);
    void slot_context_menu(QPoint);
    void slot_open_file();
    void slot_delete_file();
    void slot_copy_file_path();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QMenu *popMenu;
    QSortFilterProxyModel *proxyModel;
    QModelIndex idx;
    QString search_arg;
    void initPopMenu();
};

#endif // SEARCHWINDOW_H
