#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QMenu>

class MyTableView : public QTableView
{
    Q_OBJECT
public:
    MyTableView(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override; // 处理鼠标事件
signals:
    void openFile(QModelIndex);
    void changeFileName(QModelIndex);

private:
    QModelIndex *openedEdior = nullptr;

};

#endif // MYTABLEVIEW_H
