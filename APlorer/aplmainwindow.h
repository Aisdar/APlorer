#ifndef APLMAINWINDOW_H
#define APLMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QFileSystemModel;



class aplMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    aplMainWindow(QWidget *parent = nullptr);
    ~aplMainWindow();
    void init();
    QFileSystemModel* fileModel();
    void copy(aplMainWindow* oldApl);

private:
    Ui::MainWindow *ui;

    QFileSystemModel *m_model;
};
#endif // APLMAINWINDOW_H
