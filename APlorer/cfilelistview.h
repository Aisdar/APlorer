#ifndef CFILELISTVIEW_H
#define CFILELISTVIEW_H

#include <QListView>

class CFileListView : public QListView
{
    Q_OBJECT
public:
    CFileListView(QWidget* parent);

protected:
    void mouseReleaseEvent(QMouseEvent *e) override;
};

#endif // CFILELISTVIEW_H
