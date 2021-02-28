/********************************************************************************
** Form generated from reading UI file 'dialog_err_del_profil.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ERR_DEL_PROFIL_H
#define UI_DIALOG_ERR_DEL_PROFIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_err_del_profil
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_err_del_profil)
    {
        if (Dialog_err_del_profil->objectName().isEmpty())
            Dialog_err_del_profil->setObjectName(QString::fromUtf8("Dialog_err_del_profil"));
        Dialog_err_del_profil->resize(347, 96);
        verticalLayout = new QVBoxLayout(Dialog_err_del_profil);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_err_del_profil);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(Dialog_err_del_profil);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_err_del_profil);

        QMetaObject::connectSlotsByName(Dialog_err_del_profil);
    } // setupUi

    void retranslateUi(QDialog *Dialog_err_del_profil)
    {
        Dialog_err_del_profil->setWindowTitle(QApplication::translate("Dialog_err_del_profil", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_err_del_profil", "\320\222\320\275\320\270\320\274\320\260\320\275\320\270\320\265! \320\235\320\265 \320\262\320\276\320\267\320\274\320\276\320\266\320\275\320\276 \321\203\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\320\274\321\213\320\271 \321\201\321\203\321\202\320\276\321\207\320\275\321\213\320\271 \320\277\321\200\320\276\321\204\320\270\320\273\321\214", nullptr));
        pushButton->setText(QApplication::translate("Dialog_err_del_profil", "\320\236\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_err_del_profil: public Ui_Dialog_err_del_profil {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ERR_DEL_PROFIL_H
