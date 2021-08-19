#ifndef DDTAILDELEGATE2_H
#define DDTAILDELEGATE2_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QWidget>

class dDtailDelegate2 : public QStyledItemDelegate
{
public:
    explicit dDtailDelegate2(QObject *parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DDTAILDELEGATE2_H
