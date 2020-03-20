#ifndef TREEDELEGATE_H
#define TREEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include "treeitem.h"

class TreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TreeDelegate(QObject *parent = 0);
    ~TreeDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

public slots:
    void cellEntered(const QModelIndex &index);

private:
};

#endif // TREEDELEGATE_H
