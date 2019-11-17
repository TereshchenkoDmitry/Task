#include "IEditDialog.h"
#include "ui_EditOperatorDialog.h"
#include <QPixmap>
#include <QKeyEvent>

IEditDialog::IEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditOperatorDialog)
    , m_lineEditName(new QLineEdit(this))
    , m_lineEditMcc(new QLineEdit(this))
    , m_lineEditMnc(new QLineEdit(this))
    , m_imgLabel(new QLabel(this))
    , m_acceptBttn(new QPushButton("Accept", this))
    , m_rejectBttn(new QPushButton("Reject", this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setFixedSize(300, 190);
    QVBoxLayout* layout = new QVBoxLayout(this);

    m_editorLayout = new QVBoxLayout;
    m_editNameLayout = new QHBoxLayout;
    m_editMccLayout = new QHBoxLayout;
    m_editMncLayout = new QHBoxLayout;
    m_bttnLayout = new QHBoxLayout;

    QLabel* editorTextHeader = new QLabel("Operator Editor");
    editorTextHeader->setAlignment(Qt::AlignHCenter);
    editorTextHeader->setStyleSheet("font: 14pt; color: red;");

    m_editorLayout->addWidget(editorTextHeader);
    m_editNameLayout->addWidget(new QLabel("Name", this));
    m_editNameLayout->addWidget(m_lineEditName);
    m_editorLayout->addLayout(m_editNameLayout);

    m_editMccLayout->addWidget(new QLabel("MCC", this));
    m_editMccLayout->addWidget(m_lineEditMcc);

    m_editorLayout->addLayout(m_editMccLayout);


    m_editMncLayout->addWidget(new QLabel("MNC", this));
    m_editMncLayout->addWidget(m_lineEditMnc);
    m_editorLayout->addLayout(m_editMncLayout);

    m_bttnLayout->addWidget(m_rejectBttn);
    m_bttnLayout->addWidget(m_acceptBttn);

    layout->addLayout(m_editorLayout);
    layout->addLayout(m_bttnLayout);

    setLayout(layout);

    connect(m_acceptBttn, &QPushButton::clicked, this, &IEditDialog::accept);
    connect(m_rejectBttn, &QPushButton::clicked, this, &IEditDialog::reject);

    m_editMccLayout->addWidget(m_imgLabel);
}

QLineEdit *IEditDialog::getNameFieldEdit() const
{
    return m_lineEditName;
}

QLineEdit *IEditDialog::getMccFieldEdit() const
{
    return m_lineEditMcc;
}

QLineEdit *IEditDialog::getMncFieldEdit() const
{
    return m_lineEditMnc;
}

IEditDialog::~IEditDialog()
{
    delete ui;
}

void IEditDialog::setImage(const QString &img)
{
    QPixmap image(QString(":/images/%1.png").arg(img));
    m_imgLabel->setPixmap(image);
}

void IEditDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape: reject(); break;
        case Qt::Key_Return: accept(); break;
    default: QDialog::keyPressEvent(event); break;
    }
}
