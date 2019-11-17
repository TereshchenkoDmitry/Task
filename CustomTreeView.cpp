#include "CustomTreeView.h"

CustomTreeView::CustomTreeView(QWidget *parent)
    : QTreeView(parent)
{
    ///
}

void CustomTreeView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() != Qt::RightButton)
        emit click();

    QTreeView::mouseDoubleClickEvent(event);
}
