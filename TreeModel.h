#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include "OperatorsInfo.h"

enum Roles
{
    COUNTRY_NAME = Qt::UserRole + 1,
    OPERATOR_NAME,
    IMAGE,
    MCC,
    MNC
};

class TreeItem;
class DatabaseManager;
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel(DatabaseManager& db, QObject* parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    bool canFetchMore(const QModelIndex& parent) const override;
    void fetchMore(const QModelIndex& parent) override;
    bool hasChildren(const QModelIndex &parent) const override;

    void updateOperator(const Operator& oper);
    void addOperator(const Operator& oper);

private:
    void fillNode(TreeItem* parentItem);

private:
    TreeItem*        m_rootItem;
    OperatorInfo     m_operatorInfo;
    DatabaseManager& m_database;
};

#endif // TREEMODEL_H
