/********************************************************************************
** Form generated from reading UI file 'dialog_profile_break.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_PROFILE_BREAK_H
#define UI_DIALOG_PROFILE_BREAK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_profile_break
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_profile_break)
    {
        if (Dialog_profile_break->objectName().isEmpty())
            Dialog_profile_break->setObjectName(QString::fromUtf8("Dialog_profile_break"));
        Dialog_profile_break->resize(307, 110);
        verticalLayout = new QVBoxLayout(Dialog_profile_break);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_profile_break);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter|Qt::AlignTop);

        label_2 = new QLabel(Dialog_profile_break);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2, 0, Qt::AlignHCenter|Qt::AlignTop);

        pushButton = new QPushButton(Dialog_profile_break);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter|Qt::AlignBottom);


        retranslateUi(Dialog_profile_break);

        QMetaObject::connectSlotsByName(Dialog_profile_break);
    } // setupUi

    void retranslateUi(QDialog *Dialog_profile_break)
    {
        Dialog_profile_break->setWindowTitle(QApplication::translate("Dialog_profile_break", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_profile_break", "\320\242\320\260\320\272\320\276\320\271 \320\275\320\276\320\274\320\265\321\200 \320\277\321\200\320\276\321\204\320\270\320\273\321\217 \321\203\320\266\320\265 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\320\265\321\202.", nullptr));
        label_2->setText(QApplication::translate("Dialog_profile_break", " \320\237\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\267\320\260\320\264\320\260\320\271\321\202\320\265 \320\264\321\200\321\203\320\263\320\276\320\271 \320\275\320\276\320\274\320\265\321\200 \321\201\321\203\321\202\320\276\321\207\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\204\320\270\320\273\321\217.", nullptr));
        pushButton->setText(QApplication::translate("Dialog_profile_break", "\320\236\320\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_profile_break: public Ui_Dialog_profile_break {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_PROFILE_BREAK_H
