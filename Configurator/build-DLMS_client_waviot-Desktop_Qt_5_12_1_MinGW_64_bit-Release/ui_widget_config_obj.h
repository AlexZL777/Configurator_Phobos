/********************************************************************************
** Form generated from reading UI file 'widget_config_obj.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_CONFIG_OBJ_H
#define UI_WIDGET_CONFIG_OBJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_config_obj
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox_rele_state;
    QSpinBox *spinBox_rele_mode;
    QSpinBox *spinBox_rele_status;
    QPushButton *pushButton_rele_write;
    QPushButton *pushButton_rele_read;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *widget_config_obj)
    {
        if (widget_config_obj->objectName().isEmpty())
            widget_config_obj->setObjectName(QString::fromUtf8("widget_config_obj"));
        widget_config_obj->resize(280, 220);
        verticalLayout = new QVBoxLayout(widget_config_obj);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(widget_config_obj);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox_rele_state = new QSpinBox(groupBox);
        spinBox_rele_state->setObjectName(QString::fromUtf8("spinBox_rele_state"));

        gridLayout->addWidget(spinBox_rele_state, 1, 1, 1, 1);

        spinBox_rele_mode = new QSpinBox(groupBox);
        spinBox_rele_mode->setObjectName(QString::fromUtf8("spinBox_rele_mode"));

        gridLayout->addWidget(spinBox_rele_mode, 0, 1, 1, 1);

        spinBox_rele_status = new QSpinBox(groupBox);
        spinBox_rele_status->setObjectName(QString::fromUtf8("spinBox_rele_status"));

        gridLayout->addWidget(spinBox_rele_status, 2, 1, 1, 1);

        pushButton_rele_write = new QPushButton(groupBox);
        pushButton_rele_write->setObjectName(QString::fromUtf8("pushButton_rele_write"));

        gridLayout->addWidget(pushButton_rele_write, 3, 1, 1, 1);

        pushButton_rele_read = new QPushButton(groupBox);
        pushButton_rele_read->setObjectName(QString::fromUtf8("pushButton_rele_read"));

        gridLayout->addWidget(pushButton_rele_read, 3, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox);


        retranslateUi(widget_config_obj);

        QMetaObject::connectSlotsByName(widget_config_obj);
    } // setupUi

    void retranslateUi(QWidget *widget_config_obj)
    {
        widget_config_obj->setWindowTitle(QApplication::translate("widget_config_obj", "Form", nullptr));
        groupBox->setTitle(QApplication::translate("widget_config_obj", "Rele", nullptr));
        label->setText(QApplication::translate("widget_config_obj", "mode", nullptr));
        pushButton_rele_write->setText(QApplication::translate("widget_config_obj", "Write", nullptr));
        pushButton_rele_read->setText(QApplication::translate("widget_config_obj", "Read", nullptr));
        label_2->setText(QApplication::translate("widget_config_obj", "state", nullptr));
        label_3->setText(QApplication::translate("widget_config_obj", "status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_config_obj: public Ui_widget_config_obj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_CONFIG_OBJ_H
