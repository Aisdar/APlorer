#ifndef FILEDISPLAYWIDGET_H
#define FILEDISPLAYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPen>

class FileDisplayWidget : public QWidget
{
    Q_OBJECT
    enum FILETYPE {
        FOLDER,
        MUSICFILE,
        IMAGEFILE,
        TEXTFILE,
        UNDFINED
    };
    enum DISPLAYMODE {
        DETAILS, // 详细信息
    };

public:
    explicit FileDisplayWidget(QWidget *parent = nullptr);
    FileDisplayWidget(QString fileName, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString fileName;
    DISPLAYMODE mode = DETAILS;
    FILETYPE type = UNDFINED;
signals:

};

#endif // FILEDISPLAYWIDGET_H
