#ifndef TREEMODEL_H
#define TREEMODEL_H
#include <QObject>
#include <QAbstractItemModel>
#include "treeitem.h"
#include <QTreeView>
#include "dbconnector.h"

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(const QList<DBConnector::listCountry> &data, QObject *parent = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void addRow(const QString &code, const QString &mcc, const QString &mnc, const QString &name);

private:
    void setupModelData(const QList<DBConnector::listCountry> &data, TreeItem *parent);

    TreeItem *rootItem;
};

#endif // TREEMODEL_H
