#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QTabBar>
#include <QToolButton>
#include <QAction>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *parent = nullptr);

private:
    void setTabClosable(bool flag);
    QAction *act_closeTab, *act_createNewTab;
public slots:
    void slt_createNewTab();
    void slt_closeTab();
};

#endif // TABWIDGET_H
