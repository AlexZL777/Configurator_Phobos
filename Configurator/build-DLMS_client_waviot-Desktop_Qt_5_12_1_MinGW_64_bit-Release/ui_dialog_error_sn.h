/********************************************************************************
** Form generated from reading UI file 'dialog_error_sn.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ERROR_SN_H
#define UI_DIALOG_ERROR_SN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_error_sn
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_error_sn)
    {
        if (Dialog_error_sn->objectName().isEmpty())
            Dialog_error_sn->setObjectName(QString::fromUtf8("Dialog_error_sn"));
        Dialog_error_sn->resize(282, 95);
        verticalLayout = new QVBoxLayout(Dialog_error_sn);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_error_sn);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        label_2 = new QLabel(Dialog_error_sn);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(Dialog_error_sn);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_error_sn);

        QMetaObject::connectSlotsByName(Dialog_error_sn);
    } // setupUi

    void retranslateUi(QDialog *Dialog_error_sn)
    {
        Dialog_error_sn->setWindowTitle(QApplication::translate("Dialog_error_sn", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_error_sn", "\320\222\320\235\320\230\320\234\320\220\320\235\320\230\320\225! \320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200 \321\201\321\207\321\221\321\202\321\207\320\270\320\272\320\260", nullptr));
        label_2->setText(QApplication::translate("Dialog_error_sn", "\320\275\320\265 \321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\321\202\320\262\321\203\320\265\321\202 \320\275\320\276\320\274\320\265\321\200\321\203 \320\277\321\200\320\270 \320\270\320\275\320\270\321\206\320\270\320\260\320\273\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        pushButton->setText(QApplication::translate("Dialog_error_sn", "\320\236\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_error_sn: public Ui_Dialog_error_sn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ERROR_SN_H
