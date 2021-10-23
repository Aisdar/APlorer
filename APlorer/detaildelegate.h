#ifndef DETAILDELEGATE_H
#define DETAILDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QWidget>

class DetailDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    DetailDelegate(QWidget *parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
signals:
    void editFinished() const;
public slots:

};

#endif // DETAILDELEGATE_H
