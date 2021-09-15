#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QDebug>
#include <QTableView>
#include <QMouseEvent>
#include <QFileInfo>

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
