#include "EditOperatorDialog.h"

EditOperatorDialog::EditOperatorDialog(Operator &info, QWidget *parent)
    : IEditDialog(parent)
    , m_operatorInfo(info)
{
    QLineEdit* nameEdit = getNameFieldEdit();
    QLineEdit* mccEdit = getMccFieldEdit();
    QLineEdit* mncEdit = getMncFieldEdit();

    mccEdit->setEnabled(false);
    mncEdit->setEnabled(false);

    nameEdit->setText(m_operatorInfo.name);
    mccEdit->setText(QString::number(m_operatorInfo.mcc));
    mncEdit->setText(QString::number(m_operatorInfo.mnc));

    setImage(QString("%1_%2").arg(m_operatorInfo.mcc).arg(m_operatorInfo.mnc));

    connect(nameEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, [&](const QString& newName){
        m_operatorInfo.name = newName;
    });
}

EditOperatorDialog::~EditOperatorDialog()
{
    ///
}
