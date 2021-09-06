#ifndef DRIVEVIEW_H
#define DRIVEVIEW_H

#include <QListView>

///
/// \brief The DriveView class
///
///
class DriveView : public QListView
{
    Q_OBJECT
public:
    DriveView(QWidget *parent = nullptr);
};

#endif // DRIVEVIEW_H
