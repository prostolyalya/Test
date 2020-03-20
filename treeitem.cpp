#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    : m_itemData(data)
    , m_parentItem(parent)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem *>(this));

    return 0;
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

void TreeItem::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString value = index.data().toString();
    QStyleOptionViewItem opt = option;
    const QWidget *widget = option.widget;
    QStyle *style = widget->style();

    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
    QRect iconRect(option.rect.x() + 5, option.rect.y(), 18, 18);
    QString code = value.mid(value.lastIndexOf(" ") + 1);

    QRect textRect(option.rect.x() + 30, option.rect.y(), 170, option.rect.height());
    if (value[value.size() - 1] == ")")
    {
        style->drawItemText(painter, textRect, Qt::AlignLeft, option.palette,
                            option.state & QStyle::State_Enabled, value, QPalette::Text);
        code = value.mid(value.lastIndexOf(" ") + 2);
        code = code.mid(0, code.size() - 1);
        code = code.mid(0, code.indexOf(",")) + "_" + code.mid(code.indexOf(",") + 1);
        style->drawItemPixmap(painter, iconRect, Qt::AlignCenter,
                              QPixmap(":/icons/Operators/" + code + ".png"));
        if (option.state & QStyle::State_MouseOver)
        {
            QRect plusRect(textRect.x() + 170, option.rect.y(), 15, 15);
            style->drawItemPixmap(painter, plusRect, Qt::AlignRight, QPixmap(":/icons/plus.png"));
            plusPoint.setX(plusRect.x());
            plusPoint.setY(plusRect.y());
        }
    }
    else
    {
        style->drawItemPixmap(painter, iconRect, Qt::AlignCenter,
                              QPixmap(":/icons/Countries/" + code + ".png"));
        style->drawItemText(painter, textRect, Qt::AlignLeft, option.palette,
                            option.state & QStyle::State_Enabled, value.mid(0, value.lastIndexOf(" ")),
                            QPalette::Text);
    }
}

bool TreeItem::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                           const QModelIndex &index)
{
    QMouseEvent *me = (QMouseEvent *)event;

    if (event->type() == QEvent::MouseButtonPress)
    {

        const QPoint clickedPosition = me->pos();
        if (plusPoint.x() < clickedPosition.x() && plusPoint.x() + 15 > clickedPosition.x())
        {
            QString value = index.data().toString();

            if (value[value.size() - 1] != ")")
            {
                event->ignore();
                return false;
            }
            value = value.mid(value.lastIndexOf(" ") + 2);
            QString mcc = value.mid(0, value.indexOf(","));
            QString mnc = value.mid(value.indexOf(",") + 1);
            mnc = mnc.mid(0, mnc.size() - 1);

            emit plusClickOperator(mcc, mnc);
        }

        return true;
    }
    else if (event->type() == QEvent::MouseButtonDblClick)
    {

        const QPoint clickedPosition = me->pos();
        if (plusPoint.x() > clickedPosition.x())
        {
            QString value = index.data().toString();
            if (value[value.size() - 1] != ")")
            {
                event->ignore();
                return false;
            }
            QString name = value.mid(0, value.lastIndexOf(" "));
            value = value.mid(value.lastIndexOf(" ") + 2);
            QString mnc = value.mid(0, value.indexOf(","));
            QString mcc = value.mid(value.indexOf(",") + 1);
            mcc = mcc.mid(0, mcc.size() - 1);
            emit changeOperator(name, mnc, mcc, index);
        }

        return true;
    }
    else
    {
        event->ignore();
        return false;
    }
}

void TreeItem::setItemData(const QVector<QVariant> &itemData)
{
    m_itemData = itemData;
}

TreeItem *TreeItem::findItem(const QString &name)
{
    for (const auto &tmp : m_childItems)
    {
        if (tmp->data(0).toString().contains(name))
            return tmp;
    }
    return new TreeItem({});
}
