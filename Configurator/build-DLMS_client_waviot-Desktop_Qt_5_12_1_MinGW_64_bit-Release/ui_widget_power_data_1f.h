/********************************************************************************
** Form generated from reading UI file 'widget_power_data_1f.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_POWER_DATA_1F_H
#define UI_WIDGET_POWER_DATA_1F_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_power_data_1f
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *widget_power_data_1f)
    {
        if (widget_power_data_1f->objectName().isEmpty())
            widget_power_data_1f->setObjectName(QString::fromUtf8("widget_power_data_1f"));
        widget_power_data_1f->resize(400, 267);
        verticalLayout = new QVBoxLayout(widget_power_data_1f);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget_power_data_1f);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(300, 20));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget_power_data_1f);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(60, 20));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        lineEdit = new QLineEdit(widget_power_data_1f);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(300, 20));
        lineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget_power_data_1f);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setMinimumSize(QSize(120, 0));
        lineEdit_2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit_3 = new QLineEdit(widget_power_data_1f);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMinimumSize(QSize(300, 20));
        lineEdit_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 2, 0, 1, 1);

        lineEdit_4 = new QLineEdit(widget_power_data_1f);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        lineEdit_4->setMinimumSize(QSize(120, 0));
        lineEdit_4->setReadOnly(true);

        gridLayout->addWidget(lineEdit_4, 2, 1, 1, 1);

        lineEdit_5 = new QLineEdit(widget_power_data_1f);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMinimumSize(QSize(300, 20));
        lineEdit_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_5->setReadOnly(true);

        gridLayout->addWidget(lineEdit_5, 3, 0, 1, 1);

        lineEdit_6 = new QLineEdit(widget_power_data_1f);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        sizePolicy1.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy1);
        lineEdit_6->setMinimumSize(QSize(120, 0));
        lineEdit_6->setReadOnly(true);

        gridLayout->addWidget(lineEdit_6, 3, 1, 1, 1);

        lineEdit_7 = new QLineEdit(widget_power_data_1f);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy);
        lineEdit_7->setMinimumSize(QSize(300, 20));
        lineEdit_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_7->setReadOnly(true);

        gridLayout->addWidget(lineEdit_7, 4, 0, 1, 1);

        lineEdit_8 = new QLineEdit(widget_power_data_1f);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy1.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy1);
        lineEdit_8->setMinimumSize(QSize(120, 0));
        lineEdit_8->setReadOnly(true);

        gridLayout->addWidget(lineEdit_8, 4, 1, 1, 1);

        lineEdit_9 = new QLineEdit(widget_power_data_1f);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        sizePolicy.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy);
        lineEdit_9->setMinimumSize(QSize(300, 20));
        lineEdit_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_9->setReadOnly(true);

        gridLayout->addWidget(lineEdit_9, 5, 0, 1, 1);

        lineEdit_10 = new QLineEdit(widget_power_data_1f);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        sizePolicy1.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy1);
        lineEdit_10->setMinimumSize(QSize(120, 0));
        lineEdit_10->setReadOnly(true);

        gridLayout->addWidget(lineEdit_10, 5, 1, 1, 1);

        lineEdit_11 = new QLineEdit(widget_power_data_1f);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        sizePolicy.setHeightForWidth(lineEdit_11->sizePolicy().hasHeightForWidth());
        lineEdit_11->setSizePolicy(sizePolicy);
        lineEdit_11->setMinimumSize(QSize(300, 20));
        lineEdit_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_11->setReadOnly(true);

        gridLayout->addWidget(lineEdit_11, 6, 0, 1, 1);

        lineEdit_12 = new QLineEdit(widget_power_data_1f);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        sizePolicy1.setHeightForWidth(lineEdit_12->sizePolicy().hasHeightForWidth());
        lineEdit_12->setSizePolicy(sizePolicy1);
        lineEdit_12->setMinimumSize(QSize(120, 0));
        lineEdit_12->setReadOnly(true);

        gridLayout->addWidget(lineEdit_12, 6, 1, 1, 1);

        lineEdit_13 = new QLineEdit(widget_power_data_1f);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        sizePolicy.setHeightForWidth(lineEdit_13->sizePolicy().hasHeightForWidth());
        lineEdit_13->setSizePolicy(sizePolicy);
        lineEdit_13->setMinimumSize(QSize(300, 20));
        lineEdit_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_13->setReadOnly(true);

        gridLayout->addWidget(lineEdit_13, 7, 0, 1, 1);

        lineEdit_14 = new QLineEdit(widget_power_data_1f);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        sizePolicy1.setHeightForWidth(lineEdit_14->sizePolicy().hasHeightForWidth());
        lineEdit_14->setSizePolicy(sizePolicy1);
        lineEdit_14->setMinimumSize(QSize(120, 0));
        lineEdit_14->setReadOnly(true);

        gridLayout->addWidget(lineEdit_14, 7, 1, 1, 1);

        lineEdit_15 = new QLineEdit(widget_power_data_1f);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        sizePolicy.setHeightForWidth(lineEdit_15->sizePolicy().hasHeightForWidth());
        lineEdit_15->setSizePolicy(sizePolicy);
        lineEdit_15->setMinimumSize(QSize(300, 20));
        lineEdit_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_15->setReadOnly(true);

        gridLayout->addWidget(lineEdit_15, 8, 0, 1, 1);

        lineEdit_16 = new QLineEdit(widget_power_data_1f);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        sizePolicy1.setHeightForWidth(lineEdit_16->sizePolicy().hasHeightForWidth());
        lineEdit_16->setSizePolicy(sizePolicy1);
        lineEdit_16->setMinimumSize(QSize(120, 0));
        lineEdit_16->setReadOnly(true);

        gridLayout->addWidget(lineEdit_16, 8, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(widget_power_data_1f);

        QMetaObject::connectSlotsByName(widget_power_data_1f);
    } // setupUi

    void retranslateUi(QWidget *widget_power_data_1f)
    {
        widget_power_data_1f->setWindowTitle(QApplication::translate("widget_power_data_1f", "Form", nullptr));
        label->setText(QApplication::translate("widget_power_data_1f", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200", nullptr));
        label_2->setText(QApplication::translate("widget_power_data_1f", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        lineEdit->setText(QApplication::translate("widget_power_data_1f", "\320\235\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\320\265 (\320\222):", nullptr));
        lineEdit_3->setText(QApplication::translate("widget_power_data_1f", "\320\242\320\276\320\272 (\320\220):", nullptr));
        lineEdit_5->setText(QApplication::translate("widget_power_data_1f", "\320\242\320\276\320\272 \320\275\321\203\320\273\320\265\320\262\320\276\320\263\320\276 \320\277\321\200\320\276\320\262\320\276\320\264\320\260 (A):", nullptr));
        lineEdit_7->setText(QApplication::translate("widget_power_data_1f", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\274\320\276\321\211\320\275\320\276\321\201\321\202\320\270 (cosF):", nullptr));
        lineEdit_9->setText(QApplication::translate("widget_power_data_1f", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \321\201\320\265\321\202\320\270 (\320\223\321\206):", nullptr));
        lineEdit_11->setText(QApplication::translate("widget_power_data_1f", "\320\237\320\276\320\273\320\275\320\260\321\217 \320\274\320\276\321\211\320\275\320\276\321\201\321\202\321\214 (\320\222\320\220):", nullptr));
        lineEdit_13->setText(QApplication::translate("widget_power_data_1f", "\320\220\320\272\321\202\320\270\320\262\320\275\320\260\321\217 \320\274\320\276\321\211\320\275\320\276\321\201\321\202\321\214 (\320\222\321\202):", nullptr));
        lineEdit_15->setText(QApplication::translate("widget_power_data_1f", "\320\240\320\265\320\260\320\272\321\202\320\270\320\262\320\275\320\260\321\217 \320\274\320\276\321\211\320\275\320\276\321\201\321\202\321\214 (\320\222\320\260\321\200):", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_power_data_1f: public Ui_widget_power_data_1f {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_POWER_DATA_1F_H
