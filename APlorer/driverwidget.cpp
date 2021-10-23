#include "driverwidget.h"
#include <QFileIconProvider>
#include <QLabel>
#include "bigicondelegate.h"
#include <QProgressBar>
#include <QHBoxLayout>
#include <QGridLayout>
/**
  driveWidget使用驱动盘名字初始化后可以自动绘制
**/


int DriverWidget::bigR = 70, DriverWidget::circleWidth = 10;

DriverWidget::DriverWidget(QWidget *parent) : QWidget(parent)
{

}

DriverWidget::DriverWidget(QString driverName, QWidget *parent):driverName(driverName), QWidget(parent)
{
    this->setObjectName("DriveWidget");
    this->setDrive(driverName);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // 策略Fixed
    setMinimumSize((DriverWidget::bigR<<1)+10, (DriverWidget::bigR<<1)+10); // 设置尺寸
    QPixmap icon = BigIconDelegate::getIcon(driverName, BigIconDelegate::ExBigIcon).pixmap(64, 64);
    QProgressBar *bar = new QProgressBar(this);
    // bar->setMinimumSize(200, 20);
    bar->setMaximum(int(totalNumberOfGb));
    bar->setValue(int(totalNumberOfGb-totalNumberOfFreeGb));
    bar->setTextVisible(false);
    if (color == Qt::red)
        bar->setStyleSheet("QProgressBar:chunk{background-color:red;}");
    else if (color == Qt::green)
         bar->setStyleSheet("QProgressBar:chunk{background-color:green;}");
    else
        bar->setStyleSheet("QProgressBar:chunk{background-color:rgb(255, 97, 0);");
    // bar->setStyleSheet("QProgressBar:chunk{background-color:rgb(255, 97, 0);}");
    QGridLayout *layout = new QGridLayout(this);
    QLabel *label = new QLabel(this);
    QLabel *label1 = new QLabel("本地磁盘:" + QString(driverName.at(0)));
    QLabel *label2 = new QLabel("可用：" + QString::number(int(totalNumberOfFreeGb)) + "GB  总计：" +
                                QString::number(int(totalNumberOfGb)) + "GB已用：" +
                                QString::number(int(totalNumberOfGb-totalNumberOfFreeGb)) + "GB", this);
    label->setMinimumSize(64, 64);
    label->setPixmap(icon);
    layout->addWidget(label, 0, 0, 3, 1);
    layout->addWidget(label1, 0, 1);
    layout->addWidget(bar, 1, 1);
    layout->addWidget(label2, 2, 1);
    layout->setRowMinimumHeight(0, 10);
    layout->setRowMinimumHeight(2, 10);
    this->setLayout(layout);
}


void DriverWidget::setDrive(QString driverName)
{
    ULARGE_INTEGER temp;
    this->driverName = driverName;
    if (GetDiskFreeSpaceExA(driverName.toUtf8(), &temp, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
        // qDebug() << "driverWidget::DriverWidget(QString, QWidget) " << " success";
        totalNumberOfFreeGb = (double)totalNumberOfFreeBytes.QuadPart/GB;
        totalNumberOfGb = (double) totalNumberOfBytes.QuadPart/GB;
        // qDebug() << "totalNumberOfFreeGb: " << totalNumberOfFreeGb << "  totalNumberOfGb: " << totalNumberOfGb;
        usageRate = 1 - totalNumberOfFreeGb/totalNumberOfGb;
        spanAngle = usageRate * 360;
        if (usageRate < 0.5)
            color = Qt::green;
        else if (usageRate < 0.8)
            color = QColor(255, 97, 0);
        else
            color = Qt::red;
    } else {
        // qDebug() << "driverWidget::DriverWidget(QString, QWidget) " << " faild";

    }
}

void DriverWidget::paintEvent(QPaintEvent *event)
{
    // 重绘事件
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    QPen pen;
//    pen.setStyle(Qt::SolidLine);
//    pen.setColor(Qt::black);
//    pen.setWidth(1);
//    pen.setCapStyle(Qt::FlatCap);
//    pen.setJoinStyle(Qt::RoundJoin);
//    painter.setPen(pen);
//    QPoint center = this->rect().center(); // widget的中心
//    // 画大圆和小圆组成圆环
//    smallR = bigR - circleWidth;
//    painter.drawEllipse(center, bigR, bigR);
//    painter.drawEllipse(center, bigR-circleWidth, bigR-circleWidth);
//    // 更换颜色和宽度画进度条
//    pen.setColor(color);
//    pen.setWidth(circleWidth);
//    painter.setPen(pen);
//    // qDebug() << "startAngle: " << startAngle << "   spanAngle:" << spanAngle; // 打印角度
//    QRect rect1(center.x()-bigR+(circleWidth>>1), center.y()-bigR+(circleWidth>>1), (bigR<<1)-circleWidth, (bigR<<1)-circleWidth);
//    painter.drawArc(rect1, (int)startAngle * 16, (int)spanAngle * 16);
//    // 画中间的内容提示条
//    QPoint point(center.x()-bigR, center.y()-int((bigR>>1)*1.2));
//    QRect rect2(point.x(), point.y()-2, bigR<<1, bigR>>1);
//    pen.setColor(Qt::black);
//    painter.setPen(pen);
//    // 写中间的盘名
//    QFont font("宋体");
//    font.setPixelSize(int(rect2.height()*0.8));
//    painter.setFont(font);
//    painter.drawText(rect2, Qt::AlignCenter, driverName.mid(0, 1));
//    // 写内存情况
//    point.setY(point.y()+rect2.height()+2);
//    rect2.moveTo(point);
//    rect2.setHeight(3*rect2.height()/2);
//    font.setPixelSize(smallR>>2);
//    painter.setFont(font);
//    QString meg = "可用：" + QString::number(int(totalNumberOfFreeGb)) + "GB\n总计：" +
//            QString::number(int(totalNumberOfGb)) + "GB\n已用：" +
//            QString::number(int(totalNumberOfGb-totalNumberOfFreeGb)) + "GB";
//    painter.drawText(rect2, Qt::AlignCenter, meg);

    QWidget::paintEvent(event);
}
