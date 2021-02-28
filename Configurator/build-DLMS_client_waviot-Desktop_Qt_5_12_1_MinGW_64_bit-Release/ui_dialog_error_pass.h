/********************************************************************************
** Form generated from reading UI file 'dialog_error_pass.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ERROR_PASS_H
#define UI_DIALOG_ERROR_PASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_error_pass
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_error_pass)
    {
        if (Dialog_error_pass->objectName().isEmpty())
            Dialog_error_pass->setObjectName(QString::fromUtf8("Dialog_error_pass"));
        Dialog_error_pass->resize(241, 81);
        verticalLayout = new QVBoxLayout(Dialog_error_pass);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_error_pass);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(Dialog_error_pass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_error_pass);

        QMetaObject::connectSlotsByName(Dialog_error_pass);
    } // setupUi

    void retranslateUi(QDialog *Dialog_error_pass)
    {
        Dialog_error_pass->setWindowTitle(QApplication::translate("Dialog_error_pass", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_error_pass", "\320\222\320\275\320\270\320\274\320\260\320\275\320\270\320\265! \320\235\320\265 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\321\213\320\271 \320\277\320\260\321\200\320\276\320\273\321\214!", nullptr));
        pushButton->setText(QApplication::translate("Dialog_error_pass", "\320\236\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_error_pass: public Ui_Dialog_error_pass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ERROR_PASS_H
