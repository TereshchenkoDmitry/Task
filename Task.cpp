#include "Task.h"
#include "ui_Task.h"
#include "Delegate.h"
#include <QTreeView>

Task::Task(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
  , m_editor(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Task");
    setFixedSize(350, 600);
    ui->treeView->viewport()->installEventFilter(this);
    ui->treeView->setHeaderHidden(true);

    ui->addButton->setStyleSheet("background-color: transparent;"
                                  "font: 24px;");

    connect(ui->treeView, &CustomTreeView::click, this, &Task::editOperator);
    connect(ui->addButton, &QPushButton::clicked, this, &Task::addOperator);
    installModel();
}

Task::~Task()
{
    delete ui;
}

void Task::installModel()
{
    m_treeModel = new TreeModel(m_db, this);
    ui->treeView->setModel(m_treeModel);
    ui->treeView->setItemDelegate(new Delegate);
}

void Task::editOperator()
{
    const QModelIndex index = ui->treeView->currentIndex();
    if(!index.isValid())
        return;

    if(index.data(Roles::OPERATOR_NAME).toString().isEmpty())
        return;

    Operator currentOperator;
    currentOperator.name = index.data(Roles::OPERATOR_NAME).toString();
    currentOperator.mcc = index.data(Roles::MCC).toInt();
    currentOperator.mnc = index.data(Roles::MNC).toInt();

    m_editor = new EditOperatorDialog(currentOperator, this);
    switch (m_editor->exec()) {
        case QDialog::Rejected: break;
        case QDialog::Accepted: m_treeModel->updateOperator(currentOperator); break;
    default: break;
    }
    m_editor->deleteLater();
}

void Task::addOperator()
{
    Operator newOperator;
    m_editor = new AddOperatorDialog(newOperator, this);
    switch (m_editor->exec()) {
        case QDialog::Rejected: break;
        case QDialog::Accepted: m_treeModel->addOperator(newOperator); break;
    default: break;
    }
    m_editor->deleteLater();
}
