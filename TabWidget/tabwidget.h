#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QToolButton>
#include <QTabBar>
#include <QAction>
#include <QToolBar>
#include <QDebug>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *parent = nullptr);
    void initControlPart();
protected:

private:
    QToolBar *controlBar; // 控制工具栏
    QWidget *paddingWidget; // 空白空间

private slots:
    void slt_addTab(); // 添加页面
    void slt_removeTab(int index); // 移除页面

};

#endif // TABWIDGET_H
