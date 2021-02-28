/********************************************************************************
** Form generated from reading UI file 'dialog_err_profil_spec.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ERR_PROFIL_SPEC_H
#define UI_DIALOG_ERR_PROFIL_SPEC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_err_profil_spec
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_err_profil_spec)
    {
        if (Dialog_err_profil_spec->objectName().isEmpty())
            Dialog_err_profil_spec->setObjectName(QString::fromUtf8("Dialog_err_profil_spec"));
        Dialog_err_profil_spec->resize(254, 88);
        verticalLayout = new QVBoxLayout(Dialog_err_profil_spec);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_err_profil_spec);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(Dialog_err_profil_spec);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_err_profil_spec);

        QMetaObject::connectSlotsByName(Dialog_err_profil_spec);
    } // setupUi

    void retranslateUi(QDialog *Dialog_err_profil_spec)
    {
        Dialog_err_profil_spec->setWindowTitle(QApplication::translate("Dialog_err_profil_spec", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_err_profil_spec", "\320\235\320\265 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\320\276 \320\262\321\213\320\261\321\200\320\260\320\275 \321\201\321\203\321\202\320\276\321\207\320\275\321\213\320\271 \320\277\321\200\320\276\321\204\320\270\320\273\320\254.", nullptr));
        pushButton->setText(QApplication::translate("Dialog_err_profil_spec", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_err_profil_spec: public Ui_Dialog_err_profil_spec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ERR_PROFIL_SPEC_H
