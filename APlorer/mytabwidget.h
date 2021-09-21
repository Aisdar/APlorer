#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>
#include "tabbar.h"
#include <QStackedLayout>
#include <QScrollArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MyTabWidget; }
QT_END_NAMESPACE

class MyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    MyTabWidget(QWidget *parent = nullptr);
    ~MyTabWidget();

private:
    Ui::MyTabWidget *ui;
    TabBar *bar;


    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void currentPageChanged(int index);
    void initHomeTab(QWidget *&homePageWidget);
    void initPageTab(QString path, QWidget *&page);
};



#endif // MYTABWIDGET_H
