/********************************************************************************
** Form generated from reading UI file 'dialog_disconnect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DISCONNECT_H
#define UI_DIALOG_DISCONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_disconnect
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_3;

    void setupUi(QDialog *Dialog_disconnect)
    {
        if (Dialog_disconnect->objectName().isEmpty())
            Dialog_disconnect->setObjectName(QString::fromUtf8("Dialog_disconnect"));
        Dialog_disconnect->setEnabled(true);
        Dialog_disconnect->resize(361, 119);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog_disconnect->sizePolicy().hasHeightForWidth());
        Dialog_disconnect->setSizePolicy(sizePolicy);
        Dialog_disconnect->setAcceptDrops(false);
        Dialog_disconnect->setLayoutDirection(Qt::LeftToRight);
        label = new QLabel(Dialog_disconnect);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(20, 10, 341, 16));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setTabletTracking(false);
        pushButton = new QPushButton(Dialog_disconnect);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(130, 70, 93, 28));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setTabletTracking(false);
        label_3 = new QLabel(Dialog_disconnect);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 30, 191, 20));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setFont(font);
        label_3->setTabletTracking(false);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAutoFillBackground(true);

        retranslateUi(Dialog_disconnect);

        QMetaObject::connectSlotsByName(Dialog_disconnect);
    } // setupUi

    void retranslateUi(QDialog *Dialog_disconnect)
    {
        Dialog_disconnect->setWindowTitle(QApplication::translate("Dialog_disconnect", "Dialog", nullptr));
        label->setText(QApplication::translate("Dialog_disconnect", "\320\235\320\265\321\202 \321\201\320\262\321\217\320\267\320\270. \320\237\321\200\320\276\320\262\320\265\321\200\321\214\321\202\320\265 \320\277\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272\320\260\320\261\320\265\320\273\321\217 \320\272 \321\201\321\207\321\221\321\202\321\207\320\270\320\272\321\203", nullptr));
        pushButton->setText(QApplication::translate("Dialog_disconnect", "OK", nullptr));
        label_3->setText(QApplication::translate("Dialog_disconnect", " \320\270 \320\275\320\260\320\266\320\274\320\270\321\202e \320\272\320\275\320\276\320\277\320\272\321\203 C\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_disconnect: public Ui_Dialog_disconnect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DISCONNECT_H
