/********************************************************************************
** Form generated from reading UI file 'dialog_insert_data_season.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_INSERT_DATA_SEASON_H
#define UI_DIALOG_INSERT_DATA_SEASON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dialog_insert_data_season
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QCalendarWidget *calendarWidget;
    QPushButton *pushButton;

    void setupUi(QWidget *dialog_insert_data_season)
    {
        if (dialog_insert_data_season->objectName().isEmpty())
            dialog_insert_data_season->setObjectName(QString::fromUtf8("dialog_insert_data_season"));
        dialog_insert_data_season->resize(358, 278);
        verticalLayout_2 = new QVBoxLayout(dialog_insert_data_season);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(dialog_insert_data_season);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        calendarWidget = new QCalendarWidget(dialog_insert_data_season);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        verticalLayout->addWidget(calendarWidget);

        pushButton = new QPushButton(dialog_insert_data_season);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setFocusPolicy(Qt::WheelFocus);
        pushButton->setLayoutDirection(Qt::LeftToRight);
        pushButton->setAutoFillBackground(false);

        verticalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(dialog_insert_data_season);

        QMetaObject::connectSlotsByName(dialog_insert_data_season);
    } // setupUi

    void retranslateUi(QWidget *dialog_insert_data_season)
    {
        dialog_insert_data_season->setWindowTitle(QApplication::translate("dialog_insert_data_season", "Form", nullptr));
        label->setText(QApplication::translate("dialog_insert_data_season", "\320\222\321\213\320\261\320\265\321\200\320\270\321\202\320\265, \320\277\320\276\320\266\320\260\320\273\321\203\320\271\321\201\321\202\320\260, \320\264\320\260\321\202\321\203 \320\275\320\276\320\262\320\276\320\263\320\276 \321\201\320\265\320\267\320\276\320\275\320\275\320\276\320\263\320\276 \320\275\320\265\320\264\320\265\320\273\321\214\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\204\320\270\320\273\321\217:", nullptr));
        pushButton->setText(QApplication::translate("dialog_insert_data_season", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dialog_insert_data_season: public Ui_dialog_insert_data_season {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_INSERT_DATA_SEASON_H
