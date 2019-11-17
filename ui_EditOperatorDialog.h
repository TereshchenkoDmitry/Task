/********************************************************************************
** Form generated from reading UI file 'EditOperatorDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOPERATORDIALOG_H
#define UI_EDITOPERATORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_EditOperatorDialog
{
public:

    void setupUi(QDialog *EditOperatorDialog)
    {
        if (EditOperatorDialog->objectName().isEmpty())
            EditOperatorDialog->setObjectName(QString::fromUtf8("EditOperatorDialog"));
        EditOperatorDialog->resize(295, 164);

        retranslateUi(EditOperatorDialog);

        QMetaObject::connectSlotsByName(EditOperatorDialog);
    } // setupUi

    void retranslateUi(QDialog *EditOperatorDialog)
    {
        EditOperatorDialog->setWindowTitle(QApplication::translate("EditOperatorDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditOperatorDialog: public Ui_EditOperatorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOPERATORDIALOG_H
