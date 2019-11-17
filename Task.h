#ifndef TASK_H
#define TASK_H
#include <QMainWindow>
#include <QTreeView>
#include "TreeModel.h"
#include "CustomTreeView.h"
#include "DatabaseManager.h"
#include "EditOperatorDialog.h"
#include "AddOperatorDialog.h"
#include <QWidget>

namespace Ui {
class Task;
}

class Task : public QWidget
{
    Q_OBJECT

public:
     Task(QWidget *parent = nullptr);
    ~Task();
    void installModel();

private:
    TreeModel* m_treeModel;
    DatabaseManager m_db;

private:
    void editOperator();
    void addOperator();

private:
    Ui::Task *ui;
    IEditDialog* m_editor;
};

#endif // TASK_H
