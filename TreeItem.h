#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#define INVALID_MCC -1
#define INVALID_MNC -1

class TreeItem
{
public:
    TreeItem(const QString& name, int mcc = INVALID_MCC, int mnc = INVALID_MNC, TreeItem *parent = nullptr);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem* child(int row);
    TreeItem* parent();
    QString countryName() const;
    QString operatorName() const;

    int row() const;
    int childCount() const;
    static int columnCount();
    int mcc() const;
    int mnc()const;

    bool mapped() const; // производился ли поиск дочерних узлов.
    void setMapped(bool mapped = true);

private:
    int                 m_mcc;
    int                 m_mnc;
    bool                m_mapped;
    QString             m_country;
    QString             m_operator;
    TreeItem*           m_parentItem;
    QList<TreeItem*>    m_childItems;
};
#endif // TREEITEM_H
