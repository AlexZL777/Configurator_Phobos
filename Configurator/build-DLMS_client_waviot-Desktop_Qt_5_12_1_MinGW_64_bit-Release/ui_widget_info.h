/********************************************************************************
** Form generated from reading UI file 'widget_info.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_INFO_H
#define UI_WIDGET_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_info
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_15;
    QLabel *label_2;
    QLabel *label_12;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *label_9;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QLineEdit *lineEdit_19;
    QLineEdit *lineEdit_20;
    QGridLayout *gridLayout_2;
    QFrame *line;
    QLabel *label_10;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer;
    QSlider *horizontalSlider;
    QLabel *label_14;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *widget_info)
    {
        if (widget_info->objectName().isEmpty())
            widget_info->setObjectName(QString::fromUtf8("widget_info"));
        widget_info->resize(563, 467);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_info->sizePolicy().hasHeightForWidth());
        widget_info->setSizePolicy(sizePolicy);
        widget_info->setMinimumSize(QSize(0, 467));
        widget_info->setMaximumSize(QSize(16777215, 467));
        verticalLayout = new QVBoxLayout(widget_info);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setHorizontalSpacing(7);
        gridLayout->setVerticalSpacing(1);
        label_3 = new QLabel(widget_info);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_5 = new QLabel(widget_info);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        label = new QLabel(widget_info);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_6 = new QLabel(widget_info);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        label_7 = new QLabel(widget_info);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        label_15 = new QLabel(widget_info);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_15->setFont(font1);

        gridLayout->addWidget(label_15, 0, 0, 1, 2);

        label_2 = new QLabel(widget_info);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_12 = new QLabel(widget_info);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font);

        gridLayout->addWidget(label_12, 10, 0, 1, 1);

        label_4 = new QLabel(widget_info);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_8 = new QLabel(widget_info);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 8, 0, 1, 1);

        label_13 = new QLabel(widget_info);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);

        gridLayout->addWidget(label_13, 11, 0, 1, 1);

        label_9 = new QLabel(widget_info);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 9, 0, 1, 1);

        lineEdit = new QLineEdit(widget_info);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 1, 2, 1, 1);

        lineEdit_2 = new QLineEdit(widget_info);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_2, 2, 2, 1, 1);

        lineEdit_3 = new QLineEdit(widget_info);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setReadOnly(true);

        gridLayout->addWidget(lineEdit_3, 3, 2, 1, 1);

        lineEdit_4 = new QLineEdit(widget_info);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        lineEdit_4->setReadOnly(true);

        gridLayout->addWidget(lineEdit_4, 4, 2, 1, 1);

        lineEdit_5 = new QLineEdit(widget_info);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy1.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy1);
        lineEdit_5->setReadOnly(true);

        gridLayout->addWidget(lineEdit_5, 5, 2, 1, 1);

        lineEdit_6 = new QLineEdit(widget_info);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        sizePolicy1.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy1);
        lineEdit_6->setReadOnly(true);

        gridLayout->addWidget(lineEdit_6, 6, 2, 1, 1);

        lineEdit_7 = new QLineEdit(widget_info);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy1.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy1);
        lineEdit_7->setReadOnly(true);

        gridLayout->addWidget(lineEdit_7, 7, 2, 1, 1);

        lineEdit_8 = new QLineEdit(widget_info);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy1.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy1);
        lineEdit_8->setReadOnly(true);

        gridLayout->addWidget(lineEdit_8, 9, 2, 1, 1);

        lineEdit_10 = new QLineEdit(widget_info);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        sizePolicy1.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy1);
        lineEdit_10->setReadOnly(true);

        gridLayout->addWidget(lineEdit_10, 10, 2, 1, 1);

        lineEdit_11 = new QLineEdit(widget_info);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        sizePolicy1.setHeightForWidth(lineEdit_11->sizePolicy().hasHeightForWidth());
        lineEdit_11->setSizePolicy(sizePolicy1);
        lineEdit_11->setReadOnly(true);

        gridLayout->addWidget(lineEdit_11, 11, 2, 1, 1);

        lineEdit_13 = new QLineEdit(widget_info);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        sizePolicy1.setHeightForWidth(lineEdit_13->sizePolicy().hasHeightForWidth());
        lineEdit_13->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_13, 1, 1, 1, 1);

        lineEdit_14 = new QLineEdit(widget_info);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        sizePolicy1.setHeightForWidth(lineEdit_14->sizePolicy().hasHeightForWidth());
        lineEdit_14->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_14, 2, 1, 1, 1);

        lineEdit_15 = new QLineEdit(widget_info);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        sizePolicy1.setHeightForWidth(lineEdit_15->sizePolicy().hasHeightForWidth());
        lineEdit_15->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_15, 3, 1, 1, 1);

        lineEdit_16 = new QLineEdit(widget_info);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        sizePolicy1.setHeightForWidth(lineEdit_16->sizePolicy().hasHeightForWidth());
        lineEdit_16->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_16, 4, 1, 1, 1);

        lineEdit_17 = new QLineEdit(widget_info);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        sizePolicy1.setHeightForWidth(lineEdit_17->sizePolicy().hasHeightForWidth());
        lineEdit_17->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_17, 5, 1, 1, 1);

        lineEdit_18 = new QLineEdit(widget_info);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));
        sizePolicy1.setHeightForWidth(lineEdit_18->sizePolicy().hasHeightForWidth());
        lineEdit_18->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_18, 6, 1, 1, 1);

        lineEdit_19 = new QLineEdit(widget_info);
        lineEdit_19->setObjectName(QString::fromUtf8("lineEdit_19"));
        sizePolicy1.setHeightForWidth(lineEdit_19->sizePolicy().hasHeightForWidth());
        lineEdit_19->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_19, 7, 1, 1, 1);

        lineEdit_20 = new QLineEdit(widget_info);
        lineEdit_20->setObjectName(QString::fromUtf8("lineEdit_20"));
        sizePolicy1.setHeightForWidth(lineEdit_20->sizePolicy().hasHeightForWidth());
        lineEdit_20->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_20, 8, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout->addLayout(verticalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        line = new QFrame(widget_info);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 0, 0, 1, 3);

        label_10 = new QLabel(widget_info);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font);

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1, Qt::AlignRight);

        label_11 = new QLabel(widget_info);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        gridLayout_2->addWidget(label_11, 2, 2, 1, 1, Qt::AlignLeft);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 3, 1, 1);

        horizontalSlider = new QSlider(widget_info);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy2);
        horizontalSlider->setMaximum(1);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(horizontalSlider, 2, 1, 1, 1, Qt::AlignHCenter);

        label_14 = new QLabel(widget_info);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font1);

        gridLayout_2->addWidget(label_14, 1, 0, 1, 3);


        verticalLayout->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(widget_info);

        QMetaObject::connectSlotsByName(widget_info);
    } // setupUi

    void retranslateUi(QWidget *widget_info)
    {
        widget_info->setWindowTitle(QApplication::translate("widget_info", "Form", nullptr));
        label_3->setText(QApplication::translate("widget_info", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\272\320\276\320\274\320\274\321\203\320\275\320\270\320\272\320\260\321\206\320\270\320\276\320\275\320\275\320\276\320\263\320\276 \320\237\320\236", nullptr));
        label_5->setText(QApplication::translate("widget_info", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\277\320\276 \321\202\320\276\320\272\321\203", nullptr));
        label->setText(QApplication::translate("widget_info", "\320\242\320\270\320\277 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", nullptr));
        label_6->setText(QApplication::translate("widget_info", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\277\320\276 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\321\216", nullptr));
        label_7->setText(QApplication::translate("widget_info", "\320\224\320\260\321\202\320\260 \320\262\321\213\320\277\321\203\321\201\320\272\320\260 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", nullptr));
        label_15->setText(QApplication::translate("widget_info", "\320\236\320\261\321\211\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276\320\261 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\265:", nullptr));
        label_2->setText(QApplication::translate("widget_info", "\320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", nullptr));
        label_12->setText(QApplication::translate("widget_info", "     - \320\262\321\200\320\265\320\274\321\217", nullptr));
        label_4->setText(QApplication::translate("widget_info", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\274\320\265\321\202\321\200\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\276\320\263\320\276 \320\237\320\236", nullptr));
        label_8->setText(QApplication::translate("widget_info", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217:", nullptr));
        label_13->setText(QApplication::translate("widget_info", "     - \320\264\320\265\320\262\320\270\320\260\321\206\320\270\321\217, \320\274\320\270\320\275", nullptr));
        label_9->setText(QApplication::translate("widget_info", "     - \320\264\320\260\321\202\320\260", nullptr));
        lineEdit_13->setText(QApplication::translate("widget_info", "0.0.96.1.0.255", nullptr));
        lineEdit_14->setText(QApplication::translate("widget_info", "0.0.96.1.1.255", nullptr));
        lineEdit_15->setText(QApplication::translate("widget_info", "0.0.96.1.2.255", nullptr));
        lineEdit_16->setText(QApplication::translate("widget_info", "0.0.96.1.3.255", nullptr));
        lineEdit_17->setText(QApplication::translate("widget_info", "1.0.0.4.2.255", nullptr));
        lineEdit_18->setText(QApplication::translate("widget_info", "1.0.0.4.3.255", nullptr));
        lineEdit_19->setText(QApplication::translate("widget_info", "0.0.96.1.4.255", nullptr));
        lineEdit_20->setText(QApplication::translate("widget_info", "0.0.1.0.0.255", nullptr));
        label_10->setText(QApplication::translate("widget_info", "\320\222\321\201\321\202\321\200\320\276\320\265\320\275\320\275\320\260\321\217 \320\260\320\275\321\202\320\265\320\275\320\275\320\260", nullptr));
        label_11->setText(QApplication::translate("widget_info", "\320\222\320\275\320\265\321\210\320\275\321\217\321\217 \320\260\320\275\321\202\320\265\320\275\320\275\320\260", nullptr));
        label_14->setText(QApplication::translate("widget_info", "\320\222\321\213\320\261\320\276\321\200 \320\260\320\275\321\202\320\265\320\275\320\275\321\213:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_info: public Ui_widget_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_INFO_H
