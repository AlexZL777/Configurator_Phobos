/********************************************************************************
** Form generated from reading UI file 'dialog_date_spec.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DATE_SPEC_H
#define UI_DIALOG_DATE_SPEC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_date_spec
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QCalendarWidget *calendarWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_date_spec)
    {
        if (Dialog_date_spec->objectName().isEmpty())
            Dialog_date_spec->setObjectName(QString::fromUtf8("Dialog_date_spec"));
        Dialog_date_spec->resize(400, 306);
        verticalLayout = new QVBoxLayout(Dialog_date_spec);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(Dialog_date_spec);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEdit = new QLineEdit(Dialog_date_spec);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label = new QLabel(Dialog_date_spec);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignLeft);

        calendarWidget = new QCalendarWidget(Dialog_date_spec);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        verticalLayout->addWidget(calendarWidget);

        pushButton = new QPushButton(Dialog_date_spec);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_date_spec);

        QMetaObject::connectSlotsByName(Dialog_date_spec);
    } // setupUi

    void retranslateUi(QDialog *Dialog_date_spec)
    {
        Dialog_date_spec->setWindowTitle(QApplication::translate("Dialog_date_spec", "Dialog", nullptr));
        label_2->setText(QApplication::translate("Dialog_date_spec", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265, \320\277\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\275\320\276\320\274\320\265\321\200 \321\201\321\203\321\202\320\276\321\207\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\204\320\270\320\273\321\217:", nullptr));
        label->setText(QApplication::translate("Dialog_date_spec", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265, \320\277\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\275\320\276\320\262\321\203\321\216 \320\264\320\260\321\202\321\203 \320\276\321\201\320\276\320\261\320\276\320\263\320\276 \321\201\321\203\321\202\320\276\321\207\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\204\320\270\320\273\321\217:", nullptr));
        pushButton->setText(QApplication::translate("Dialog_date_spec", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_date_spec: public Ui_Dialog_date_spec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DATE_SPEC_H
