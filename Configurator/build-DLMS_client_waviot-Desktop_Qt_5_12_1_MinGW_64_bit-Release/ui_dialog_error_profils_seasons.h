/********************************************************************************
** Form generated from reading UI file 'dialog_error_profils_seasons.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ERROR_PROFILS_SEASONS_H
#define UI_DIALOG_ERROR_PROFILS_SEASONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_error_profils_seasons
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_error_profils_seasons)
    {
        if (Dialog_error_profils_seasons->objectName().isEmpty())
            Dialog_error_profils_seasons->setObjectName(QString::fromUtf8("Dialog_error_profils_seasons"));
        Dialog_error_profils_seasons->resize(305, 118);
        verticalLayout = new QVBoxLayout(Dialog_error_profils_seasons);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Dialog_error_profils_seasons);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        label_2 = new QLabel(Dialog_error_profils_seasons);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2, 0, Qt::AlignHCenter);

        pushButton = new QPushButton(Dialog_error_profils_seasons);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton, 0, Qt::AlignHCenter);


        retranslateUi(Dialog_error_profils_seasons);

        QMetaObject::connectSlotsByName(Dialog_error_profils_seasons);
    } // setupUi

    void retranslateUi(QDialog *Dialog_error_profils_seasons)
    {
        Dialog_error_profils_seasons->setWindowTitle(QApplication::translate("Dialog_error_profils_seasons", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_error_profils_seasons", "\320\235\320\265 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\275\320\276 \320\262\321\213\320\261\321\200\320\260\320\275\321\213 \321\201\321\203\321\202\320\276\321\207\320\275\321\213\320\265 \320\277\321\200\320\276\321\204\320\270\320\273\320\270.", nullptr));
        label_2->setText(QApplication::translate("Dialog_error_profils_seasons", "\320\237\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\262\321\213\320\261\320\265\321\200\320\270\321\202\320\265 \321\201\321\203\321\202\320\276\321\207\320\275\321\213\320\265 \320\277\321\200\320\276\321\204\320\270\320\273\320\270 \320\270\320\267 \320\270\320\274\320\265\321\216\321\211\320\270\321\205\321\201\321\217.", nullptr));
        pushButton->setText(QApplication::translate("Dialog_error_profils_seasons", "\320\236\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_error_profils_seasons: public Ui_Dialog_error_profils_seasons {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ERROR_PROFILS_SEASONS_H
