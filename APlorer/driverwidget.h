#ifndef DRIVERWIDGET_H
#define DRIVERWIDGET_H

#include <QObject>
#include <QWidget>
#include <fileapi.h>
#include <QDebug>
#include <QPainter>
#include <QColor>
#include <QString>

#define GB (1024*1024*1024)
#define MB (1024*1024)
#define KB (1024)

class DriverWidget : public QWidget
{
    // 磁盘显示控件
    Q_OBJECT
public:
    explicit DriverWidget(QWidget *parent = nullptr);
    DriverWidget(QString driverName, QWidget *parent = nullptr);
    void setDrive(QString driverName); // 设置驱动器的名称
    QString getDriveName() {return driverName;};
    static int bigR, circleWidth;
    int smallR; // 外圆环半径，圆环宽度
signals:

private:
    QString driverName; // 驱动器名称
    ULARGE_INTEGER totalNumberOfBytes, totalNumberOfFreeBytes; // 全部空间，可用空间单位:B
    QString anotherName; // 别名

    double totalNumberOfGb, totalNumberOfFreeGb; // 全部空间，单位Gb

    double usageRate; // 磁盘使用率


    QColor color = Qt::gray; // 颜色
    double startAngle = 90, spanAngle = 360; // 绘制时圆形的角度

protected:
    void paintEvent(QPaintEvent *event) override;
};



#endif // DRIVERWIDGET_H
