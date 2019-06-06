/********************************************************************************
** Form generated from reading UI file 'dialog_insert_date_season.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_INSERT_DATE_SEASON_H
#define UI_DIALOG_INSERT_DATE_SEASON_H

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

class Ui_Dialog_insert_date_season
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit_6;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QLabel *label;
    QCalendarWidget *calendarWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *Dialog_insert_date_season)
    {
        if (Dialog_insert_date_season->objectName().isEmpty())
            Dialog_insert_date_season->setObjectName(QString::fromUtf8("Dialog_insert_date_season"));
        Dialog_insert_date_season->resize(439, 470);
        verticalLayout = new QVBoxLayout(Dialog_insert_date_season);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(Dialog_insert_date_season);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1, Qt::AlignRight);

        lineEdit_6 = new QLineEdit(Dialog_insert_date_season);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout->addWidget(lineEdit_6, 5, 1, 1, 1);

        label_5 = new QLabel(Dialog_insert_date_season);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1, Qt::AlignRight);

        lineEdit_4 = new QLineEdit(Dialog_insert_date_season);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 3, 1, 1, 1);

        lineEdit = new QLineEdit(Dialog_insert_date_season);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMaxLength(64);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        lineEdit_2 = new QLineEdit(Dialog_insert_date_season);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit_5 = new QLineEdit(Dialog_insert_date_season);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout->addWidget(lineEdit_5, 4, 1, 1, 1);

        lineEdit_3 = new QLineEdit(Dialog_insert_date_season);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        label_4 = new QLabel(Dialog_insert_date_season);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1, Qt::AlignRight);

        label_6 = new QLabel(Dialog_insert_date_season);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1, Qt::AlignRight);

        label_2 = new QLabel(Dialog_insert_date_season);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_7 = new QLabel(Dialog_insert_date_season);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1, Qt::AlignRight);

        label_8 = new QLabel(Dialog_insert_date_season);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 6, 0, 1, 1, Qt::AlignRight);

        lineEdit_7 = new QLineEdit(Dialog_insert_date_season);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout->addWidget(lineEdit_7, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        label = new QLabel(Dialog_insert_date_season);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignLeft);

        calendarWidget = new QCalendarWidget(Dialog_insert_date_season);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        verticalLayout->addWidget(calendarWidget);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_2 = new QPushButton(Dialog_insert_date_season);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pushButton_2, 0, 2, 1, 1, Qt::AlignLeft);

        pushButton = new QPushButton(Dialog_insert_date_season);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(93, 0));

        gridLayout_2->addWidget(pushButton, 0, 1, 1, 1, Qt::AlignRight);


        verticalLayout->addLayout(gridLayout_2);


        retranslateUi(Dialog_insert_date_season);

        QMetaObject::connectSlotsByName(Dialog_insert_date_season);
    } // setupUi

    void retranslateUi(QDialog *Dialog_insert_date_season)
    {
        Dialog_insert_date_season->setWindowTitle(QApplication::translate("Dialog_insert_date_season", "Dialog", nullptr));
        label_3->setText(QApplication::translate("Dialog_insert_date_season", "\320\222\320\242\320\236\320\240\320\235\320\230\320\232:", nullptr));
        label_5->setText(QApplication::translate("Dialog_insert_date_season", "\320\247\320\225\320\242\320\222\320\225\320\240\320\223:", nullptr));
        label_4->setText(QApplication::translate("Dialog_insert_date_season", "\320\241\320\240\320\225\320\224\320\220:", nullptr));
        label_6->setText(QApplication::translate("Dialog_insert_date_season", "\320\237\320\257\320\242\320\235\320\230\320\246\320\220:", nullptr));
        label_2->setText(QApplication::translate("Dialog_insert_date_season", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265, \320\277\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\275\320\276\320\274\320\265\321\200 \321\201\321\203\321\202\320\276\321\207\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\204\320\270\320\273\321\217 \320\237\320\236\320\235\320\225\320\224\320\225\320\233\320\254\320\235\320\230\320\232:", nullptr));
        label_7->setText(QApplication::translate("Dialog_insert_date_season", "\320\241\320\243\320\221\320\221\320\236\320\242\320\220:", nullptr));
        label_8->setText(QApplication::translate("Dialog_insert_date_season", "\320\222\320\236\320\241\320\232\320\240\320\225\320\241\320\225\320\235\320\254\320\225:", nullptr));
        label->setText(QApplication::translate("Dialog_insert_date_season", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265, \320\277\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\264\320\260\321\202\321\203 \321\201\320\265\320\267\320\276\320\275\320\275\320\276\320\263\320\276 \320\275\320\265\320\264\320\265\320\273\321\214\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\204\320\270\320\273\321\217:", nullptr));
        pushButton_2->setText(QApplication::translate("Dialog_insert_date_season", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        pushButton->setText(QApplication::translate("Dialog_insert_date_season", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_insert_date_season: public Ui_Dialog_insert_date_season {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_INSERT_DATE_SEASON_H
