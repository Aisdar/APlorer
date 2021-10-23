#ifndef BIGICONDELEGATE_H
#define BIGICONDELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QWidget>

class BigIconDelegate : public QStyledItemDelegate
{
public:
    enum IconSize{
        ExBigIcon,
        BigIcon,
        MidIcon,
    };

    explicit BigIconDelegate(QObject *parent = nullptr);
    explicit BigIconDelegate(IconSize size, QObject *parent = nullptr);

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

    static QIcon getIcon(QString path, IconSize size);
    static QString stringFomat(QString text, IconSize size);

private:
    enum IconSize size;

public:
    static QSize rectSize;
};

#endif // BIGICONDELEGATE_H
