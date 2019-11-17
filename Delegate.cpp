#include "Delegate.h"
#include <QPainter>
#include <QApplication>
#include "TreeModel.h"

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect;
    rect.setHeight(static_cast<int>(rect.height() * 0.9));
    rect.setWidth(static_cast<int>(rect.height() * 1.1));
    QImage img(QString(":/images/%1.png").arg(index.data(Roles::IMAGE).toString()));
    if(!img.isNull())
    {
        img.scaledToHeight(option.rect.height());
        img.scaledToWidth(option.rect.height());
        QApplication::style()->drawItemPixmap(painter, rect, 0, QPixmap::fromImage(img));

        QString operatorInfo = QString("%1 (%2, %3)")
                .arg(index.data(Roles::OPERATOR_NAME).toString())
                .arg(index.data(Roles::MCC).toString())
                .arg(index.data(Roles::MNC).toString());

        painter->drawText(QRect(static_cast<int>(rect.right() * 1.2),
                                rect.top(),
                                option.rect.width() - rect.width(),
                                rect.height()),
                          Qt::AlignVCenter,
                          operatorInfo);
    }

    else
    {
        if(index.data(Roles::COUNTRY_NAME).toString().isEmpty())
            painter->drawText(option.rect, Qt::AlignVCenter, QString("%1 (%2_%3)")
                              .arg(index.data(Roles::OPERATOR_NAME).toString())
                              .arg(index.data(Roles::MCC).toString())
                              .arg(index.data(Roles::MNC).toString()));
        else
            painter->drawText(option.rect, Qt::AlignVCenter, index.data(Roles::COUNTRY_NAME).toString());
    }
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}
