/********************************************************************************
** Form generated from reading UI file 'widget_tarifs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_TARIFS_H
#define UI_WIDGET_TARIFS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_tarifs
{
public:

    void setupUi(QWidget *widget_tarifs)
    {
        if (widget_tarifs->objectName().isEmpty())
            widget_tarifs->setObjectName(QString::fromUtf8("widget_tarifs"));
        widget_tarifs->resize(500, 500);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_tarifs->sizePolicy().hasHeightForWidth());
        widget_tarifs->setSizePolicy(sizePolicy);

        retranslateUi(widget_tarifs);

        QMetaObject::connectSlotsByName(widget_tarifs);
    } // setupUi

    void retranslateUi(QWidget *widget_tarifs)
    {
        widget_tarifs->setWindowTitle(QApplication::translate("widget_tarifs", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_tarifs: public Ui_widget_tarifs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_TARIFS_H
