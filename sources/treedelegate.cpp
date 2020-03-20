#include "treedelegate.h"

TreeDelegate::TreeDelegate(QObject *parent)
{
}

QWidget *TreeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
}

bool TreeDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                               const QModelIndex &index)
{
}

void TreeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
}

void TreeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    {
        if (index.column() == 0)
        {
            //            TreeItem *childItem = static_cast<TreeItem *>(index.internalPointer());
            //            if (childItem->type() == TreeItem::Type::Checkable)
            //            {
            QStyleOptionViewItem opt = option;
            QStyledItemDelegate::initStyleOption(&opt, index);

            const int desiredThreshold = 10;

            opt.rect.setX(opt.rect.x() - desiredThreshold);
            option.widget->style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter, option.widget);

            return;
            //            }
        }

        return QStyledItemDelegate::paint(painter, option, index);
    }
}
