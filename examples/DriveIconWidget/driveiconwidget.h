#ifndef DRIVEICONWIDGET_H
#define DRIVEICONWIDGET_H

#include <QWidget>
#include <QFileIconProvider>

class QLabel;
class QProgressBar;
class QProcess;


class DriveIconWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DriveIconWidget(QString driverName, QWidget *parent = nullptr);
    void setDriver(QString driverName);
    void setChecked(bool check);
    QSize sizeHint() const;


protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QString driverName;          // 盘符名
    QLabel *pLabName;           // 盘符号标签
    QLabel *pLabSize;           // 大小标签
    QLabel *pLabIcon;           // 图标标签
    QProgressBar *pBar;         // 使用进度条
    QProcess *pProcess;          // 执行命令进程

    QFileIconProvider provider; // 图标
    double totalNumberOfGb, totalNumberOfFreeGb; // 全部空间，单位Gb
    double usageRate; // 磁盘使用率

    bool check;

private:
    QString barColorStyleSheet();

private slots:
    void readData();


signals:
    void doubleClicked();
    void checked();
};

#endif // DRIVEICONWIDGET_H
