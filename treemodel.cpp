#include "treemodel.h"

TreeModel::TreeModel(const QList<DBConnector::listCountry> &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem({ tr("Country & Operators") });
    setupModelData(data, rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

void TreeModel::setupModelData(const QList<DBConnector::listCountry> &data, TreeItem *parent)
{

    for (const auto &tmp : data)
    {
        parent->appendChild(new TreeItem({ tmp.country + " " + tmp.code }, parent));
        for (const auto &tmps : tmp.operators)
        {
            parent->child(parent->childCount() - 1)
                ->appendChild(new TreeItem({ tmps.name + " (" + tmps.mcc + "," + tmps.mnc + ")" },
                                           parent->child(parent->childCount() - 1)));
        }
    }
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem *>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem *>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem *>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
    item->setItemData({ value });
    return true;
}

void TreeModel::addRow(const QString &code, const QString &mcc, const QString &mnc, const QString &name)
{
    TreeItem *parent = rootItem->findItem(code);
    beginInsertRows(QModelIndex(), parent->childCount(), parent->childCount() + 1);
    TreeItem *item = new TreeItem({ name + " (" + mcc + "," + mnc + ")" }, parent);
    parent->appendChild(item);
    endInsertRows();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem *>(index.internalPointer());

    return item->data(index.column());
}
