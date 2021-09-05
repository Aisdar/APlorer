#include "driveiconwidget.h"
#include <QLabel>
#include <QProgressBar>
#include <QProcess>
#include <QDebug>

#ifdef Q_OS_WIN
#include "windows.h"
#endif
#define GB (1024 * 1024 * 1024)
#define MB (1024 * 1024)
#define KB (1024)

DriveIconWidget::DriveIconWidget(QString driverName, QWidget *parent)
    : QWidget(parent)
{
    setFont(QFont("Microsoft YaHei"));  // 雅黑

    int width = 250;
    int height = 57;
    setFixedSize(QSize(width, height));

    pLabName = new QLabel(QString("盘符名:%1").arg(driverName), this);
    pLabSize = new QLabel(" GB 可用, 共 GB:", this);
    pLabIcon = new QLabel("图标", this);
    pBar = new QProgressBar(this);
    pProcess = new QProcess(this);

    // 以IconSize为基准
    int iconWidth = 50;
    int iconHeight = 57;
    pLabIcon->setGeometry(0, 0, iconWidth, iconHeight);

    pLabName->setGeometry(iconWidth, 0, width - iconWidth, 18);
    pBar->setGeometry(iconWidth, 18, width - iconWidth, 18);
    pLabSize->setGeometry(iconWidth, 39, width - iconWidth, 18);

    QFileInfo info(driverName);
    QIcon icon = provider.icon(info);
    pLabIcon->setPixmap(icon.pixmap(QSize(64, 64)));
    pLabIcon->setAutoFillBackground(true);
    pLabIcon->setAlignment(Qt::AlignCenter);

    pBar->setRange(0, 100);
    pBar->setTextVisible(false);

//    this->setStyleSheet("QWidget:hover{ \
//                        background-color:rgba(100,255,100, 100); \
//                        border-color: rgba(255, 225, 255, 200); \
//                        color:rgba(0, 0, 0, 200);}");

    connect(pProcess, &QProcess::readyRead, this, &DriveIconWidget::readData);

    setDriver(driverName);

}

void DriveIconWidget::setDriver(QString driverName)
{
    if(driverName == this->driverName)
        return;

#ifdef Q_OS_WIN
    ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
    this->driverName = driverName;
    if (GetDiskFreeSpaceExA(driverName.toUtf8(), &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes)) {
        // qDebug() << "driverWidget::DriverWidget(QString, QWidget) " << " success";
        totalNumberOfFreeGb = (double)liTotalFreeBytes.QuadPart / GB;
        totalNumberOfGb = (double)liTotalBytes.QuadPart / GB;
        // qDebug() << "totalNumberOfFreeGb: " << totalNumberOfFreeGb << "  totalNumberOfGb: " << totalNumberOfGb;
        usageRate = 1 - totalNumberOfFreeGb / totalNumberOfGb;
    }

    QString totalNumberOfFreeGbStr = QString::number((double)liTotalFreeBytes.QuadPart / GB, 'f', 1);
    QString totalNumberOfTotalGbStr = QString::number((double)liTotalBytes.QuadPart / GB, 'f', 1);
    pLabName->setText(driverName);
    pLabSize->setText(QString("%1 GB 可用, 共 %2 GB").arg(totalNumberOfFreeGbStr).arg(totalNumberOfTotalGbStr));
    pBar->setValue(usageRate * 100);
    pBar->setStyleSheet(barColorStyleSheet());

#else
    pProcess->start("df -h");
#endif


}

void DriveIconWidget::setChecked(bool check)
{
    if(check == this->check)
        return;

    this->check = check;
    if(check){

    }
    else{

    }
}

QSize DriveIconWidget::sizeHint() const
{
    return QSize(250, 57);
}

void DriveIconWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit checked();
}

void DriveIconWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit doubleClicked();
}

void DriveIconWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

QString DriveIconWidget::barColorStyleSheet()
{
    QString sheet =
            "QProgressBar { \
            border: 1px solid gray; \
            border-radius: 1px; \
            width:10px;}";

    if (usageRate < 0.9)
    {// 岚色
        sheet +=
            "QProgressBar::chunk { \
            background-color: \
            rgba(38, 160, 210, 255)};";
    }
    else
    {// 虹色
        sheet +=
            "QProgressBar::chunk { \
            background-color: \
            rgba(218, 38, 38, 255)};";
    }
    return sheet;
}

void DriveIconWidget::readData()
{
    while (!pProcess->atEnd()) {
        QString result = QLatin1String(pProcess->readLine());
#ifdef __arm__
        if (result.startsWith("/dev/root")) {
            checkSize(result, "本地存储");
        } else if (result.startsWith("/dev/mmcblk")) {
            checkSize(result, "本地存储");
        } else if (result.startsWith("/dev/mmcblk1p")) {
            checkSize(result, "SD卡");
            QStringList list = result.split(" ");
            emit sdcardReceive(list.at(0));
        } else if (result.startsWith("/dev/sd")) {
            checkSize(result, "U盘");
            QStringList list = result.split(" ");
            emit udiskReceive(list.at(0));
        }
#else
//        if (result.startsWith("/dev/sd")) {
//            checkSize(result, "");
//            QStringList list = result.split(" ");
//            emit udiskReceive(list.at(0));
//        }
        qDebug() << result;
#endif
    }
}
