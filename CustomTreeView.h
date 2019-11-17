#ifndef CUSTOMTREEVIEW_H
#define CUSTOMTREEVIEW_H
#include <QMouseEvent>
#include <QTreeView>

class CustomTreeView : public QTreeView
{
    Q_OBJECT
public:
    CustomTreeView(QWidget *parent = nullptr);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void click();
};

#endif // CUSTOMTREEVIEW_H
