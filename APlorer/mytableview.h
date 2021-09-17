#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>
#include <QAction>
#include <QDir>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QStandardItemModel>
#include <QFileInfo>
#include <QStack>

class ContentDelegate;
class DetailDelegate;
class DetailDelegate2;
class ListDelegate;
class BigIconDelegate;


class MyTableView : public QTableView
{
    Q_OBJECT
public:
    enum DisplayMode {
        DETAIL, // 详细信息模式
        LIST, // 列表模式
        BIGICON, // 大图标模式
        EXBIGICION, // 超大图标
        MIDICON, // 中图标
        CONTENT, // 内容
    };

    MyTableView(QWidget *parent = nullptr);
    MyTableView(QString absolutePath, DisplayMode mode, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;

    void setCurrentPage (QString absolutePath, DisplayMode mode, bool isNew);
    QString static fileType(QFileInfo info); // 获得文件类型
    QString static sizeFormat(QFileInfo info); // 获得文件大小信息
    QAction *backward;
    QAction *forward;

public slots:
        void slt_backward(); // 回退
        void slt_forward(); // 前进


private:
    QModelIndex *openedEdior = nullptr;
    DisplayMode currentMode;
    QStandardItemModel *model;
    QDir dir;
    QVector <QString> history;
    int historyIndex;

    DetailDelegate *detailDelegate;
    DetailDelegate2 *detailDelegate2;
    ListDelegate *listDelegate;
    BigIconDelegate *bigIconDelegate, *exbigIconDelegate, *midIconDelegate;
    ContentDelegate *contentDelegate;

    void setDetailModel(); // 设置详细信息显示模式
    void setListModel(); // 设置列表显示模式
    void setBigIconModel(); // 设置大图标显示模型
    void setContentModel(); // 设置内容显示模型

    void openFile(QModelIndex);

    void resizeEvent(QResizeEvent *event) override; // resize事件

};

class myTableView : public QTableView
{
    Q_OBJECT
public:
    myTableView(QWidget* parent);
    void setFileInfo(const QVector<QFileInfo>& fileInfos);

protected:
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QVector<QFileInfo> _fileInfos;

};

#endif // MYTABLEVIEW_H
