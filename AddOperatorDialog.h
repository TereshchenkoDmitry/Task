#ifndef ADDOPERATORDIALOG_H
#define ADDOPERATORDIALOG_H
#include "OperatorsInfo.h"
#include "IEditDialog.h"

class AddOperatorDialog : public IEditDialog
{
    Q_OBJECT
public:
    AddOperatorDialog(Operator& info, QWidget *parent = nullptr);
    ~AddOperatorDialog();

signals:
    void dataChanged();

private:
    Operator&    m_operatorInfo;

private:
    void changeImage();
};

#endif // ADDOPERATORDIALOG_H
