#ifndef EDITOPERATORDIALOG_H
#define EDITOPERATORDIALOG_H
#include "OperatorsInfo.h"
#include "IEditDialog.h"

class EditOperatorDialog : public IEditDialog
{
public:
     EditOperatorDialog(Operator& info, QWidget *parent = nullptr);
    ~EditOperatorDialog();

private:
    Operator&    m_operatorInfo;
};

#endif // EDITOPERATORDIALOG_H
