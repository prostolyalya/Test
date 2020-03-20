#ifndef TREEITEM_H
#define TREEITEM_H
#include <QVector>
#include <QVariant>
#include <QStyledItemDelegate>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>

class TreeItem : public QStyledItemDelegate
{

    Q_OBJECT

public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;
    void setPoint();

    void setItemData(const QVector<QVariant> &itemData);
    TreeItem *findItem(const QString &name);

signals:
    void changeOperator(const QString &name, const QString &mcc, const QString &mnc,
                        const QModelIndex &index);
    void plusClickOperator(const QString &mcc, const QString &mnc);

private:
    QVector<TreeItem *> m_childItems;
    QVector<QVariant> m_itemData;
    TreeItem *m_parentItem;
    mutable QPoint plusPoint;
};

#endif // TREEITEM_H
