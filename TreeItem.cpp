#include "TreeItem.h"
#include <QStringList>

TreeItem::TreeItem(const QString &name, const int mcc, const int mnc, TreeItem *parent)
    : m_mcc(mcc)
    , m_mnc(mnc)
    , m_mapped(false)
    , m_parentItem(parent)
    , m_childItems()
{
    if(m_mcc == INVALID_MCC && m_mnc == INVALID_MNC)
        m_country = name;
    else
        m_operator = name;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
    m_childItems.clear();
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount()
{
    return 1;
}

QString TreeItem::countryName() const
{
    return m_country;
}

QString TreeItem::operatorName() const
{
    return m_operator;
}

int TreeItem::mcc() const
{
    return m_mcc;
}

int TreeItem::mnc() const
{
    return m_mnc;
}

TreeItem *TreeItem::parent()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    return 0;
}

bool TreeItem::mapped() const
{
    return m_mapped;
}

void TreeItem::setMapped(bool mapped)
{
    m_mapped = mapped;
}

