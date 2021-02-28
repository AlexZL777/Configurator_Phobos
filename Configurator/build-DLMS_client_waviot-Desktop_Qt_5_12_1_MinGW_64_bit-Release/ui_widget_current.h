/********************************************************************************
** Form generated from reading UI file 'widget_current.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_CURRENT_H
#define UI_WIDGET_CURRENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_current
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_info;
    QPushButton *pushButton_EF0A;
    QTableView *tableView;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton_ADE_read;
    QSpinBox *spinBox_ADE_Pulse1_freq;
    QSpinBox *spinBox_ADE_Pulse0_freq;
    QLabel *label_5;
    QPushButton *pushButton_ADE_write;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *pushButton_set_Fast_DL;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox_display_min;
    QSpinBox *spinBox_display_max;
    QLabel *label_4;
    QPushButton *pushButton_display_write;
    QPushButton *pushButton_set_Time;
    QPushButton *pushButton_rele_on;
    QPushButton *pushButton_display_read;
    QLabel *label_6;
    QComboBox *comboBox_ADE_Pulse1_energy_type;
    QComboBox *comboBox_ADE_Pulse0_energy_type;
    QPushButton *pushButton_rele_off;
    QPushButton *pushButton;
    QLineEdit *lineEdit_in;
    QLineEdit *lineEdit_out;

    void setupUi(QWidget *widget_current)
    {
        if (widget_current->objectName().isEmpty())
            widget_current->setObjectName(QString::fromUtf8("widget_current"));
        widget_current->resize(400, 460);
        verticalLayout = new QVBoxLayout(widget_current);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_info = new QLabel(widget_current);
        label_info->setObjectName(QString::fromUtf8("label_info"));

        horizontalLayout->addWidget(label_info);

        pushButton_EF0A = new QPushButton(widget_current);
        pushButton_EF0A->setObjectName(QString::fromUtf8("pushButton_EF0A"));

        horizontalLayout->addWidget(pushButton_EF0A);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(widget_current);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->horizontalHeader()->setDefaultSectionSize(75);
        tableView->horizontalHeader()->setMinimumSectionSize(75);
        tableView->verticalHeader()->setDefaultSectionSize(22);
        tableView->verticalHeader()->setMinimumSectionSize(22);

        verticalLayout->addWidget(tableView);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(widget_current);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        pushButton_ADE_read = new QPushButton(widget_current);
        pushButton_ADE_read->setObjectName(QString::fromUtf8("pushButton_ADE_read"));

        gridLayout->addWidget(pushButton_ADE_read, 1, 3, 1, 1);

        spinBox_ADE_Pulse1_freq = new QSpinBox(widget_current);
        spinBox_ADE_Pulse1_freq->setObjectName(QString::fromUtf8("spinBox_ADE_Pulse1_freq"));
        spinBox_ADE_Pulse1_freq->setMaximum(999999999);

        gridLayout->addWidget(spinBox_ADE_Pulse1_freq, 2, 1, 1, 1);

        spinBox_ADE_Pulse0_freq = new QSpinBox(widget_current);
        spinBox_ADE_Pulse0_freq->setObjectName(QString::fromUtf8("spinBox_ADE_Pulse0_freq"));
        spinBox_ADE_Pulse0_freq->setMaximum(999999999);

        gridLayout->addWidget(spinBox_ADE_Pulse0_freq, 1, 1, 1, 1);

        label_5 = new QLabel(widget_current);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 2, 1, 1);

        pushButton_ADE_write = new QPushButton(widget_current);
        pushButton_ADE_write->setObjectName(QString::fromUtf8("pushButton_ADE_write"));

        gridLayout->addWidget(pushButton_ADE_write, 2, 3, 1, 1);

        label_3 = new QLabel(widget_current);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(widget_current);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        pushButton_set_Fast_DL = new QPushButton(widget_current);
        pushButton_set_Fast_DL->setObjectName(QString::fromUtf8("pushButton_set_Fast_DL"));

        gridLayout->addWidget(pushButton_set_Fast_DL, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        spinBox_display_min = new QSpinBox(widget_current);
        spinBox_display_min->setObjectName(QString::fromUtf8("spinBox_display_min"));
        spinBox_display_min->setMaximum(255);

        horizontalLayout_2->addWidget(spinBox_display_min);

        spinBox_display_max = new QSpinBox(widget_current);
        spinBox_display_max->setObjectName(QString::fromUtf8("spinBox_display_max"));
        spinBox_display_max->setMaximum(255);

        horizontalLayout_2->addWidget(spinBox_display_max);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        label_4 = new QLabel(widget_current);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        pushButton_display_write = new QPushButton(widget_current);
        pushButton_display_write->setObjectName(QString::fromUtf8("pushButton_display_write"));

        gridLayout->addWidget(pushButton_display_write, 3, 3, 1, 1);

        pushButton_set_Time = new QPushButton(widget_current);
        pushButton_set_Time->setObjectName(QString::fromUtf8("pushButton_set_Time"));

        gridLayout->addWidget(pushButton_set_Time, 0, 3, 1, 1);

        pushButton_rele_on = new QPushButton(widget_current);
        pushButton_rele_on->setObjectName(QString::fromUtf8("pushButton_rele_on"));

        gridLayout->addWidget(pushButton_rele_on, 4, 2, 1, 1);

        pushButton_display_read = new QPushButton(widget_current);
        pushButton_display_read->setObjectName(QString::fromUtf8("pushButton_display_read"));

        gridLayout->addWidget(pushButton_display_read, 3, 2, 1, 1);

        label_6 = new QLabel(widget_current);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        comboBox_ADE_Pulse1_energy_type = new QComboBox(widget_current);
        comboBox_ADE_Pulse1_energy_type->setObjectName(QString::fromUtf8("comboBox_ADE_Pulse1_energy_type"));

        gridLayout->addWidget(comboBox_ADE_Pulse1_energy_type, 2, 2, 1, 1);

        comboBox_ADE_Pulse0_energy_type = new QComboBox(widget_current);
        comboBox_ADE_Pulse0_energy_type->setObjectName(QString::fromUtf8("comboBox_ADE_Pulse0_energy_type"));

        gridLayout->addWidget(comboBox_ADE_Pulse0_energy_type, 1, 2, 1, 1);

        pushButton_rele_off = new QPushButton(widget_current);
        pushButton_rele_off->setObjectName(QString::fromUtf8("pushButton_rele_off"));

        gridLayout->addWidget(pushButton_rele_off, 4, 3, 1, 1);

        pushButton = new QPushButton(widget_current);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 4, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        lineEdit_in = new QLineEdit(widget_current);
        lineEdit_in->setObjectName(QString::fromUtf8("lineEdit_in"));

        verticalLayout->addWidget(lineEdit_in);

        lineEdit_out = new QLineEdit(widget_current);
        lineEdit_out->setObjectName(QString::fromUtf8("lineEdit_out"));

        verticalLayout->addWidget(lineEdit_out);


        retranslateUi(widget_current);

        QMetaObject::connectSlotsByName(widget_current);
    } // setupUi

    void retranslateUi(QWidget *widget_current)
    {
        widget_current->setWindowTitle(QApplication::translate("widget_current", "Form", nullptr));
        label_info->setText(QApplication::translate("widget_current", "info", nullptr));
        pushButton_EF0A->setText(QApplication::translate("widget_current", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        label->setText(QApplication::translate("widget_current", "Display period", nullptr));
        pushButton_ADE_read->setText(QApplication::translate("widget_current", "Read", nullptr));
        label_5->setText(QApplication::translate("widget_current", "type", nullptr));
        pushButton_ADE_write->setText(QApplication::translate("widget_current", "Write", nullptr));
        label_3->setText(QApplication::translate("widget_current", "\320\241\320\262\320\265\321\202\320\276\320\264\320\270\320\276\320\264", nullptr));
        label_2->setText(QApplication::translate("widget_current", "freq", nullptr));
        pushButton_set_Fast_DL->setText(QApplication::translate("widget_current", "set Fast_DL", nullptr));
        label_4->setText(QApplication::translate("widget_current", "\320\236\320\277\321\202\320\276\320\277\320\260\321\200\320\260", nullptr));
        pushButton_display_write->setText(QApplication::translate("widget_current", "Write", nullptr));
        pushButton_set_Time->setText(QApplication::translate("widget_current", "set Time", nullptr));
        pushButton_rele_on->setText(QApplication::translate("widget_current", "on", nullptr));
        pushButton_display_read->setText(QApplication::translate("widget_current", "Read", nullptr));
        label_6->setText(QApplication::translate("widget_current", "Rele", nullptr));
        pushButton_rele_off->setText(QApplication::translate("widget_current", "off", nullptr));
        pushButton->setText(QApplication::translate("widget_current", "fix calib", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_current: public Ui_widget_current {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_CURRENT_H
