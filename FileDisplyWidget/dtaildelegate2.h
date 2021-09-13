#ifndef DTAILDELEGATE2_H
#define DTAILDELEGATE2_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QWidget>

class DetailDelegate2 : public QStyledItemDelegate
{
public:
    explicit DetailDelegate2(QObject *parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // DTAILDELEGATE2_H
