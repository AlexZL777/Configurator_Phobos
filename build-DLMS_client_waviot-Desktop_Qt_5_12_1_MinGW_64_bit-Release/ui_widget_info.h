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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_info
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser_7;
    QLabel *label_3;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_17;
    QTextBrowser *textBrowser_14;
    QLabel *label_5;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_5;
    QLabel *label;
    QTextBrowser *textBrowser_15;
    QTextBrowser *textBrowser_4;
    QTextBrowser *textBrowser_16;
    QLabel *label_6;
    QLabel *label_7;
    QTextBrowser *textBrowser_6;
    QLabel *label_15;
    QTextBrowser *textBrowser_3;
    QTextBrowser *textBrowser_10;
    QTextBrowser *textBrowser_11;
    QTextBrowser *textBrowser_18;
    QLabel *label_2;
    QTextBrowser *textBrowser_19;
    QTextBrowser *textBrowser_13;
    QLabel *label_12;
    QLabel *label_4;
    QLabel *label_8;
    QTextBrowser *textBrowser_20;
    QLabel *label_13;
    QLabel *label_9;
    QTextBrowser *textBrowser_8;

    void setupUi(QWidget *widget_info)
    {
        if (widget_info->objectName().isEmpty())
            widget_info->setObjectName(QString::fromUtf8("widget_info"));
        widget_info->resize(563, 467);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_info->sizePolicy().hasHeightForWidth());
        widget_info->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget_info);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setHorizontalSpacing(7);
        gridLayout->setVerticalSpacing(1);
        textBrowser_7 = new QTextBrowser(widget_info);
        textBrowser_7->setObjectName(QString::fromUtf8("textBrowser_7"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser_7->sizePolicy().hasHeightForWidth());
        textBrowser_7->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(10);
        textBrowser_7->setFont(font);
        textBrowser_7->setAcceptDrops(true);
        textBrowser_7->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_7->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_7, 7, 2, 1, 1);

        label_3 = new QLabel(widget_info);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        textBrowser = new QTextBrowser(widget_info);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);
        textBrowser->setFont(font);
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser, 1, 2, 1, 1);

        textBrowser_17 = new QTextBrowser(widget_info);
        textBrowser_17->setObjectName(QString::fromUtf8("textBrowser_17"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textBrowser_17->sizePolicy().hasHeightForWidth());
        textBrowser_17->setSizePolicy(sizePolicy2);
        textBrowser_17->setFont(font);
        textBrowser_17->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_17->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_17, 5, 1, 1, 1);

        textBrowser_14 = new QTextBrowser(widget_info);
        textBrowser_14->setObjectName(QString::fromUtf8("textBrowser_14"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textBrowser_14->sizePolicy().hasHeightForWidth());
        textBrowser_14->setSizePolicy(sizePolicy3);
        textBrowser_14->setFont(font);
        textBrowser_14->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_14->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_14, 2, 1, 1, 1);

        label_5 = new QLabel(widget_info);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        textBrowser_2 = new QTextBrowser(widget_info);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        sizePolicy1.setHeightForWidth(textBrowser_2->sizePolicy().hasHeightForWidth());
        textBrowser_2->setSizePolicy(sizePolicy1);
        textBrowser_2->setFont(font);
        textBrowser_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_2->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_2, 2, 2, 1, 1);

        textBrowser_5 = new QTextBrowser(widget_info);
        textBrowser_5->setObjectName(QString::fromUtf8("textBrowser_5"));
        sizePolicy1.setHeightForWidth(textBrowser_5->sizePolicy().hasHeightForWidth());
        textBrowser_5->setSizePolicy(sizePolicy1);
        textBrowser_5->setFont(font);
        textBrowser_5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_5->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_5, 5, 2, 1, 1);

        label = new QLabel(widget_info);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        textBrowser_15 = new QTextBrowser(widget_info);
        textBrowser_15->setObjectName(QString::fromUtf8("textBrowser_15"));
        sizePolicy2.setHeightForWidth(textBrowser_15->sizePolicy().hasHeightForWidth());
        textBrowser_15->setSizePolicy(sizePolicy2);
        textBrowser_15->setFont(font);
        textBrowser_15->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_15->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_15, 3, 1, 1, 1);

        textBrowser_4 = new QTextBrowser(widget_info);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        sizePolicy1.setHeightForWidth(textBrowser_4->sizePolicy().hasHeightForWidth());
        textBrowser_4->setSizePolicy(sizePolicy1);
        textBrowser_4->setFont(font);
        textBrowser_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_4->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);

        gridLayout->addWidget(textBrowser_4, 4, 2, 1, 1);

        textBrowser_16 = new QTextBrowser(widget_info);
        textBrowser_16->setObjectName(QString::fromUtf8("textBrowser_16"));
        sizePolicy2.setHeightForWidth(textBrowser_16->sizePolicy().hasHeightForWidth());
        textBrowser_16->setSizePolicy(sizePolicy2);
        textBrowser_16->setFont(font);
        textBrowser_16->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_16->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_16, 4, 1, 1, 1);

        label_6 = new QLabel(widget_info);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        label_7 = new QLabel(widget_info);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        textBrowser_6 = new QTextBrowser(widget_info);
        textBrowser_6->setObjectName(QString::fromUtf8("textBrowser_6"));
        sizePolicy1.setHeightForWidth(textBrowser_6->sizePolicy().hasHeightForWidth());
        textBrowser_6->setSizePolicy(sizePolicy1);
        textBrowser_6->setFont(font);
        textBrowser_6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_6->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_6, 6, 2, 1, 1);

        label_15 = new QLabel(widget_info);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_15->setFont(font1);

        gridLayout->addWidget(label_15, 0, 0, 1, 2);

        textBrowser_3 = new QTextBrowser(widget_info);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        sizePolicy1.setHeightForWidth(textBrowser_3->sizePolicy().hasHeightForWidth());
        textBrowser_3->setSizePolicy(sizePolicy1);
        textBrowser_3->setFont(font);
        textBrowser_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_3->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_3, 3, 2, 1, 1);

        textBrowser_10 = new QTextBrowser(widget_info);
        textBrowser_10->setObjectName(QString::fromUtf8("textBrowser_10"));
        sizePolicy1.setHeightForWidth(textBrowser_10->sizePolicy().hasHeightForWidth());
        textBrowser_10->setSizePolicy(sizePolicy1);
        textBrowser_10->setFont(font);
        textBrowser_10->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_10->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_10, 10, 2, 1, 1);

        textBrowser_11 = new QTextBrowser(widget_info);
        textBrowser_11->setObjectName(QString::fromUtf8("textBrowser_11"));
        sizePolicy1.setHeightForWidth(textBrowser_11->sizePolicy().hasHeightForWidth());
        textBrowser_11->setSizePolicy(sizePolicy1);
        textBrowser_11->setFont(font);
        textBrowser_11->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_11->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_11, 11, 2, 1, 1);

        textBrowser_18 = new QTextBrowser(widget_info);
        textBrowser_18->setObjectName(QString::fromUtf8("textBrowser_18"));
        sizePolicy2.setHeightForWidth(textBrowser_18->sizePolicy().hasHeightForWidth());
        textBrowser_18->setSizePolicy(sizePolicy2);
        textBrowser_18->setFont(font);
        textBrowser_18->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_18->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_18, 6, 1, 1, 1);

        label_2 = new QLabel(widget_info);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        textBrowser_19 = new QTextBrowser(widget_info);
        textBrowser_19->setObjectName(QString::fromUtf8("textBrowser_19"));
        sizePolicy2.setHeightForWidth(textBrowser_19->sizePolicy().hasHeightForWidth());
        textBrowser_19->setSizePolicy(sizePolicy2);
        textBrowser_19->setFont(font);
        textBrowser_19->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_19->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_19, 7, 1, 1, 1);

        textBrowser_13 = new QTextBrowser(widget_info);
        textBrowser_13->setObjectName(QString::fromUtf8("textBrowser_13"));
        sizePolicy1.setHeightForWidth(textBrowser_13->sizePolicy().hasHeightForWidth());
        textBrowser_13->setSizePolicy(sizePolicy1);
        textBrowser_13->setFont(font);
        textBrowser_13->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_13->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_13, 1, 1, 1, 1);

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

        textBrowser_20 = new QTextBrowser(widget_info);
        textBrowser_20->setObjectName(QString::fromUtf8("textBrowser_20"));
        textBrowser_20->setEnabled(true);
        sizePolicy2.setHeightForWidth(textBrowser_20->sizePolicy().hasHeightForWidth());
        textBrowser_20->setSizePolicy(sizePolicy2);
        textBrowser_20->setFont(font);
        textBrowser_20->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_20->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_20, 8, 1, 1, 1);

        label_13 = new QLabel(widget_info);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);

        gridLayout->addWidget(label_13, 11, 0, 1, 1);

        label_9 = new QLabel(widget_info);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 9, 0, 1, 1);

        textBrowser_8 = new QTextBrowser(widget_info);
        textBrowser_8->setObjectName(QString::fromUtf8("textBrowser_8"));
        sizePolicy1.setHeightForWidth(textBrowser_8->sizePolicy().hasHeightForWidth());
        textBrowser_8->setSizePolicy(sizePolicy1);
        textBrowser_8->setFont(font);
        textBrowser_8->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_8->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        gridLayout->addWidget(textBrowser_8, 9, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(widget_info);

        QMetaObject::connectSlotsByName(widget_info);
    } // setupUi

    void retranslateUi(QWidget *widget_info)
    {
        widget_info->setWindowTitle(QApplication::translate("widget_info", "Form", nullptr));
        label_3->setText(QApplication::translate("widget_info", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\272\320\276\320\274\320\274\321\203\320\275\320\270\320\272\320\260\321\206\320\270\320\276\320\275\320\275\320\276\320\263\320\276 \320\237\320\236", nullptr));
        textBrowser->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:7.8pt;\"><br /></p></body></html>", nullptr));
        textBrowser_17->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1.0.0.4.2.255</p></body></html>", nullptr));
        textBrowser_14->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0.96.1.1.255</p></body></html>", nullptr));
        label_5->setText(QApplication::translate("widget_info", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\277\320\276 \321\202\320\276\320\272\321\203", nullptr));
        label->setText(QApplication::translate("widget_info", "\320\242\320\270\320\277 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", nullptr));
        textBrowser_15->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0.96.1.2.255</p></body></html>", nullptr));
        textBrowser_16->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0.96.1.3.255</p></body></html>", nullptr));
        label_6->setText(QApplication::translate("widget_info", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\277\320\276 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\321\216", nullptr));
        label_7->setText(QApplication::translate("widget_info", "\320\224\320\260\321\202\320\260 \320\262\321\213\320\277\321\203\321\201\320\272\320\260 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", nullptr));
        label_15->setText(QApplication::translate("widget_info", "\320\236\320\261\321\211\320\260\321\217 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276\320\261 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\265:", nullptr));
        textBrowser_18->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1.0.0.4.3.255</p></body></html>", nullptr));
        label_2->setText(QApplication::translate("widget_info", "\320\241\320\265\321\200\320\270\320\271\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", nullptr));
        textBrowser_19->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0.96.1.4.255</p></body></html>", nullptr));
        textBrowser_13->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0.96.1.0.255</p></body></html>", nullptr));
        label_12->setText(QApplication::translate("widget_info", "     - \320\262\321\200\320\265\320\274\321\217", nullptr));
        label_4->setText(QApplication::translate("widget_info", "\320\222\320\265\321\200\321\201\320\270\321\217 \320\274\320\265\321\202\321\200\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\276\320\263\320\276 \320\237\320\236", nullptr));
        label_8->setText(QApplication::translate("widget_info", "\320\241\320\270\321\201\321\202\320\265\320\274\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217:", nullptr));
        textBrowser_20->setHtml(QApplication::translate("widget_info", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0.1.0.0.255</p></body></html>", nullptr));
        label_13->setText(QApplication::translate("widget_info", "     - \320\264\320\265\320\262\320\270\320\260\321\206\320\270\321\217, \320\274\320\270\320\275", nullptr));
        label_9->setText(QApplication::translate("widget_info", "     - \320\264\320\260\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_info: public Ui_widget_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_INFO_H
