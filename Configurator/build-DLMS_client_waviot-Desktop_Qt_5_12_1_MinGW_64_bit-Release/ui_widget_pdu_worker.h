/********************************************************************************
** Form generated from reading UI file 'widget_pdu_worker.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_PDU_WORKER_H
#define UI_WIDGET_PDU_WORKER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_PDU_worker
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_fw;
    QPlainTextEdit *plainTextEdit_log;
    QLineEdit *lineEdit_radio_in;
    QPushButton *pushButton_electro_spec;
    QLineEdit *lineEdit_radio_out;

    void setupUi(QWidget *widget_PDU_worker)
    {
        if (widget_PDU_worker->objectName().isEmpty())
            widget_PDU_worker->setObjectName(QString::fromUtf8("widget_PDU_worker"));
        widget_PDU_worker->resize(400, 300);
        verticalLayout = new QVBoxLayout(widget_PDU_worker);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_fw = new QPushButton(widget_PDU_worker);
        pushButton_fw->setObjectName(QString::fromUtf8("pushButton_fw"));

        verticalLayout->addWidget(pushButton_fw);

        plainTextEdit_log = new QPlainTextEdit(widget_PDU_worker);
        plainTextEdit_log->setObjectName(QString::fromUtf8("plainTextEdit_log"));

        verticalLayout->addWidget(plainTextEdit_log);

        lineEdit_radio_in = new QLineEdit(widget_PDU_worker);
        lineEdit_radio_in->setObjectName(QString::fromUtf8("lineEdit_radio_in"));

        verticalLayout->addWidget(lineEdit_radio_in);

        pushButton_electro_spec = new QPushButton(widget_PDU_worker);
        pushButton_electro_spec->setObjectName(QString::fromUtf8("pushButton_electro_spec"));

        verticalLayout->addWidget(pushButton_electro_spec);

        lineEdit_radio_out = new QLineEdit(widget_PDU_worker);
        lineEdit_radio_out->setObjectName(QString::fromUtf8("lineEdit_radio_out"));
        lineEdit_radio_out->setReadOnly(true);

        verticalLayout->addWidget(lineEdit_radio_out);


        retranslateUi(widget_PDU_worker);

        QMetaObject::connectSlotsByName(widget_PDU_worker);
    } // setupUi

    void retranslateUi(QWidget *widget_PDU_worker)
    {
        widget_PDU_worker->setWindowTitle(QApplication::translate("widget_PDU_worker", "Form", nullptr));
        pushButton_fw->setText(QApplication::translate("widget_PDU_worker", "fw", nullptr));
        lineEdit_radio_in->setText(QApplication::translate("widget_PDU_worker", "EF06", nullptr));
        pushButton_electro_spec->setText(QApplication::translate("widget_PDU_worker", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_PDU_worker: public Ui_widget_PDU_worker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_PDU_WORKER_H
