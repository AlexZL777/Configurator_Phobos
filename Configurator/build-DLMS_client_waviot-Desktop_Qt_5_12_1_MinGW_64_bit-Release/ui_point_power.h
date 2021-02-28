/********************************************************************************
** Form generated from reading UI file 'point_power.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINT_POWER_H
#define UI_POINT_POWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_point_power
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *point_power)
    {
        if (point_power->objectName().isEmpty())
            point_power->setObjectName(QString::fromUtf8("point_power"));
        point_power->resize(400, 1514);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(point_power->sizePolicy().hasHeightForWidth());
        point_power->setSizePolicy(sizePolicy);
        point_power->setMinimumSize(QSize(200, 200));
        verticalLayout = new QVBoxLayout(point_power);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(point_power);

        QMetaObject::connectSlotsByName(point_power);
    } // setupUi

    void retranslateUi(QWidget *point_power)
    {
        point_power->setWindowTitle(QApplication::translate("point_power", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class point_power: public Ui_point_power {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINT_POWER_H
