/********************************************************************************
** Form generated from reading UI file 'dialog_err_date_seasons.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ERR_DATE_SEASONS_H
#define UI_DIALOG_ERR_DATE_SEASONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_err_date_seasons
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_err_date_seasons)
    {
        if (Dialog_err_date_seasons->objectName().isEmpty())
            Dialog_err_date_seasons->setObjectName(QString::fromUtf8("Dialog_err_date_seasons"));
        Dialog_err_date_seasons->resize(400, 84);
        verticalLayout = new QVBoxLayout(Dialog_err_date_seasons);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_err_date_seasons);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(Dialog_err_date_seasons);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_err_date_seasons);

        QMetaObject::connectSlotsByName(Dialog_err_date_seasons);
    } // setupUi

    void retranslateUi(QDialog *Dialog_err_date_seasons)
    {
        Dialog_err_date_seasons->setWindowTitle(QApplication::translate("Dialog_err_date_seasons", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_err_date_seasons", "\320\222\320\262\320\265\320\264\320\265\320\275\320\275\320\260\321\217 \320\264\320\260\321\202\320\260 \321\203\320\266\320\265 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\320\265\321\202. \320\237\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260 \320\262\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\321\200\321\203\320\263\321\203\321\216 \320\264\320\260\321\202\321\203.", nullptr));
        pushButton->setText(QApplication::translate("Dialog_err_date_seasons", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_err_date_seasons: public Ui_Dialog_err_date_seasons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ERR_DATE_SEASONS_H
