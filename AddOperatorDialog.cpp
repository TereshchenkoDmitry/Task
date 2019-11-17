#include "AddOperatorDialog.h"
#include <QRegExpValidator>

AddOperatorDialog::AddOperatorDialog(Operator &info, QWidget *parent)
    : IEditDialog(parent)
    , m_operatorInfo(info)
{    
    QLineEdit* nameEdit = getNameFieldEdit();
    QLineEdit* mccEdit  = getMccFieldEdit();
    QLineEdit* mncEdit  = getMncFieldEdit();

    QRegExp reg("[0-9]+");
    QRegExpValidator *validator = new QRegExpValidator(reg, this);
    mccEdit->setValidator(validator);
    mncEdit->setValidator(validator);

    setImage("question");

    connect(nameEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, [&](const QString& newName){
        m_operatorInfo.name = newName;
    });

    connect(mccEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, [&](const QString& newMcc){
        m_operatorInfo.mcc = newMcc.toInt();
        emit dataChanged();
    });

    connect(mncEdit, QOverload<const QString&>::of(&QLineEdit::textChanged), this, [&](const QString& newMnc){
        m_operatorInfo.mnc = newMnc.toInt();
        emit dataChanged();
    });

    connect(this, &AddOperatorDialog::dataChanged, this, &AddOperatorDialog::changeImage);
}

AddOperatorDialog::~AddOperatorDialog()
{
    ///
}

void AddOperatorDialog::changeImage()
{
    QImage image(QString(":/images/%1.png").arg(QString("%1_%2").arg(m_operatorInfo.mcc).arg(m_operatorInfo.mnc)));
    if(!image.isNull())
        setImage(QString("%1_%2").arg(m_operatorInfo.mcc).arg(m_operatorInfo.mnc));
    else
        setImage("question");
}
