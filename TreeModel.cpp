#include "TreeModel.h"
#include "TreeItem.h"
#include "DatabaseManager.h"

TreeModel::TreeModel(DatabaseManager &db, QObject *parent)
    : QAbstractItemModel(parent)
    , m_rootItem(new TreeItem(QString()))
    , m_database(db)
{
    fillNode(m_rootItem);
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    switch (role) {
        case COUNTRY_NAME: return item->countryName();
        case OPERATOR_NAME: return item->operatorName();
        case MCC: return item->mcc();
        case MNC: return item->mnc();
        case IMAGE: return QString("%1_%2").arg(item->mcc()).arg(item->mnc());
    default: return QVariant();
    }
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    return QVariant();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TreeItem* parentItem;
    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*> (parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*> (parent.internalPointer())->columnCount();
    else
        return m_rootItem->columnCount();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*> (index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

bool TreeModel::canFetchMore(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return false;

    const TreeItem* parentItem = static_cast<TreeItem*> (parent.internalPointer());
    return !parentItem->mapped();
}

void TreeModel::fetchMore(const QModelIndex &parent)
{
    TreeItem* parentItem = static_cast<TreeItem*>(parent.internalPointer());
    const auto& operatorsList = m_operatorInfo.value(parentItem->countryName());
    if(operatorsList.empty())
        return;

    beginInsertRows(parent, 0, operatorsList.size() - 1);
    foreach(const auto& it, operatorsList)
    {
        const Operator& currentOperator = it;
        TreeItem *childItem = new TreeItem(currentOperator.name, currentOperator.mcc, currentOperator.mnc, parentItem);
        parentItem->appendChild(childItem);
    }

    parentItem->setMapped();
    endInsertRows();
}

bool TreeModel::hasChildren(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        const TreeItem* parentItem = static_cast<TreeItem*>(parent.internalPointer());
        if (!parentItem->mapped())
            return true;
    }

    return QAbstractItemModel::hasChildren(parent);
}

void TreeModel::fillNode(TreeItem *parentItem)
{
    m_database.operatorsData(m_operatorInfo);
    if(m_operatorInfo.empty())
        return;

    foreach(const QString key, m_operatorInfo.keys())
    {
        const QString countryName = key;
        TreeItem *childItem = new TreeItem(countryName, INVALID_MCC, INVALID_MNC, parentItem);
        parentItem->appendChild(childItem);
    }
}

void TreeModel::updateOperator(const Operator& oper)
{
    if(!m_database.updateOperator(oper))
        return;

    beginResetModel();
    m_operatorInfo.clear();
    delete m_rootItem;
    m_rootItem = new TreeItem(QString());

    fillNode(m_rootItem);
    endResetModel();
}

void TreeModel::addOperator(const Operator &oper)
{
    if(!m_database.addOperator(oper))
        return;

    beginResetModel();
    m_operatorInfo.clear();
    delete m_rootItem;
    m_rootItem = new TreeItem(QString());

    fillNode(m_rootItem);
    endResetModel();
}
