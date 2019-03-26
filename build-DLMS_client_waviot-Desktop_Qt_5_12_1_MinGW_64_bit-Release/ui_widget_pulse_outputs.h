/********************************************************************************
** Form generated from reading UI file 'widget_pulse_outputs.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_PULSE_OUTPUTS_H
#define UI_WIDGET_PULSE_OUTPUTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_pulse_outputs
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_4_;
    QComboBox *comboBox_ADE_Pulse0_Energy_type;
    QLabel *label_3_;
    QComboBox *comboBox_ADE_Pulse1_Energy_type;
    QLabel *label;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *widget_pulse_outputs)
    {
        if (widget_pulse_outputs->objectName().isEmpty())
            widget_pulse_outputs->setObjectName(QString::fromUtf8("widget_pulse_outputs"));
        widget_pulse_outputs->resize(430, 108);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_pulse_outputs->sizePolicy().hasHeightForWidth());
        widget_pulse_outputs->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(widget_pulse_outputs);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        label_4_ = new QLabel(widget_pulse_outputs);
        label_4_->setObjectName(QString::fromUtf8("label_4_"));
        QFont font;
        font.setPointSize(10);
        label_4_->setFont(font);

        gridLayout->addWidget(label_4_, 1, 0, 1, 1);

        comboBox_ADE_Pulse0_Energy_type = new QComboBox(widget_pulse_outputs);
        comboBox_ADE_Pulse0_Energy_type->setObjectName(QString::fromUtf8("comboBox_ADE_Pulse0_Energy_type"));
        comboBox_ADE_Pulse0_Energy_type->setFont(font);

        gridLayout->addWidget(comboBox_ADE_Pulse0_Energy_type, 1, 2, 1, 1);

        label_3_ = new QLabel(widget_pulse_outputs);
        label_3_->setObjectName(QString::fromUtf8("label_3_"));
        label_3_->setFont(font);

        gridLayout->addWidget(label_3_, 3, 0, 1, 1);

        comboBox_ADE_Pulse1_Energy_type = new QComboBox(widget_pulse_outputs);
        comboBox_ADE_Pulse1_Energy_type->setObjectName(QString::fromUtf8("comboBox_ADE_Pulse1_Energy_type"));
        comboBox_ADE_Pulse1_Energy_type->setFont(font);

        gridLayout->addWidget(comboBox_ADE_Pulse1_Energy_type, 3, 2, 1, 1);

        label = new QLabel(widget_pulse_outputs);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        pushButton = new QPushButton(widget_pulse_outputs);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setFont(font);

        gridLayout->addWidget(pushButton, 1, 3, 1, 1);

        textEdit = new QTextEdit(widget_pulse_outputs);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);
        textEdit->setFont(font);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setReadOnly(true);

        gridLayout->addWidget(textEdit, 1, 1, 1, 1);

        textEdit_2 = new QTextEdit(widget_pulse_outputs);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        sizePolicy2.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
        textEdit_2->setSizePolicy(sizePolicy2);
        textEdit_2->setFont(font);
        textEdit_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit_2->setReadOnly(true);

        gridLayout->addWidget(textEdit_2, 3, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        retranslateUi(widget_pulse_outputs);

        QMetaObject::connectSlotsByName(widget_pulse_outputs);
    } // setupUi

    void retranslateUi(QWidget *widget_pulse_outputs)
    {
        widget_pulse_outputs->setWindowTitle(QApplication::translate("widget_pulse_outputs", "Form", nullptr));
        label_4_->setText(QApplication::translate("widget_pulse_outputs", "\320\241\320\262\320\265\321\202\320\276\320\264\320\270\320\276\320\264", nullptr));
        label_3_->setText(QApplication::translate("widget_pulse_outputs", "\320\236\320\277\321\202\320\276\320\277\320\260\321\200\320\260", nullptr));
        label->setText(QApplication::translate("widget_pulse_outputs", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\270\320\274\320\277\321\203\320\273\321\214\321\201\320\275\321\213\321\205 \320\262\321\213\321\205\320\276\320\264\320\276\320\262:", nullptr));
        pushButton->setText(QApplication::translate("widget_pulse_outputs", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", nullptr));
        textEdit->setHtml(QApplication::translate("widget_pulse_outputs", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4800</p></body></html>", nullptr));
        textEdit_2->setHtml(QApplication::translate("widget_pulse_outputs", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4800</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_pulse_outputs: public Ui_widget_pulse_outputs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_PULSE_OUTPUTS_H
