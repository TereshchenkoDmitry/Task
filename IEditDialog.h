#ifndef IEDITDIALOG_H
#define IEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class EditOperatorDialog;
}

class IEditDialog : public QDialog
{
    Q_OBJECT

public:
    IEditDialog(QWidget *parent = nullptr);
    ~IEditDialog();
    void setImage(const QString &img);

    QLineEdit* getNameFieldEdit() const;
    QLineEdit* getMccFieldEdit() const;
    QLineEdit* getMncFieldEdit() const;

protected:
     void keyPressEvent(QKeyEvent *);

private:
    Ui::EditOperatorDialog *ui;

private:
    QLineEdit*   m_lineEditName;
    QLineEdit*   m_lineEditMcc;
    QLineEdit*   m_lineEditMnc;
    QLabel*      m_imgLabel;
    QPushButton* m_acceptBttn;
    QPushButton* m_rejectBttn;

    QVBoxLayout* m_editorLayout;
    QHBoxLayout* m_editNameLayout;
    QHBoxLayout* m_editMccLayout;
    QHBoxLayout* m_editMncLayout;
    QHBoxLayout* m_bttnLayout;
};

#endif // IEDITDIALOG_H
