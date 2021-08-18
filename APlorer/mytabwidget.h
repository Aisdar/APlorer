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
    QStackedLayout *sLayout;
public:
    // void initHomePage(QWidget *homePageWidget);
};



#endif // MYTABWIDGET_H
