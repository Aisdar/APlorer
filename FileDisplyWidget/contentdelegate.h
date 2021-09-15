#ifndef CONTENTDELEGATE_H
#define CONTENTDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QWidget>

class ContentDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ContentDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // CONTENTDELEGATE_H
