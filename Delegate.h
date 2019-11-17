#ifndef DELEGATE_H
#define DELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DELEGATE_H
