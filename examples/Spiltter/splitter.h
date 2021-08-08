#ifndef SPLITTER_H
#define SPLITTER_H

#include <QSplitter>

class Splitter : public QSplitter
{
    Q_OBJECT
public:
    Splitter(QWidget* parent = nullptr);
    Splitter(Qt::Orientation orientation, QWidget* parent = nullptr);
};

#endif // SPLITTER_H
