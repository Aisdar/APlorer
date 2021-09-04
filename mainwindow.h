#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

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
    QModelIndex idx;
    QString search_arg;
    void initPopMenu();
};

#endif // MAINWINDOW_H
