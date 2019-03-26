/********************************************************************************
** Form generated from reading UI file 'widget_update_fw.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_UPDATE_FW_H
#define UI_WIDGET_UPDATE_FW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_update_fw
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser_log;
    QPushButton *pushButton_file_fw_update;
    QPushButton *pushButton_auto_update;
    QProgressBar *progressBar;

    void setupUi(QWidget *widget_update_fw)
    {
        if (widget_update_fw->objectName().isEmpty())
            widget_update_fw->setObjectName(QString::fromUtf8("widget_update_fw"));
        widget_update_fw->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_update_fw->sizePolicy().hasHeightForWidth());
        widget_update_fw->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget_update_fw);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser_log = new QTextBrowser(widget_update_fw);
        textBrowser_log->setObjectName(QString::fromUtf8("textBrowser_log"));

        verticalLayout->addWidget(textBrowser_log);

        pushButton_file_fw_update = new QPushButton(widget_update_fw);
        pushButton_file_fw_update->setObjectName(QString::fromUtf8("pushButton_file_fw_update"));

        verticalLayout->addWidget(pushButton_file_fw_update);

        pushButton_auto_update = new QPushButton(widget_update_fw);
        pushButton_auto_update->setObjectName(QString::fromUtf8("pushButton_auto_update"));

        verticalLayout->addWidget(pushButton_auto_update);

        progressBar = new QProgressBar(widget_update_fw);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);


        retranslateUi(widget_update_fw);

        QMetaObject::connectSlotsByName(widget_update_fw);
    } // setupUi

    void retranslateUi(QWidget *widget_update_fw)
    {
        widget_update_fw->setWindowTitle(QApplication::translate("widget_update_fw", "Form", nullptr));
        pushButton_file_fw_update->setText(QApplication::translate("widget_update_fw", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\277\321\200\320\276\321\210\320\270\320\262\320\272\321\203", nullptr));
        pushButton_auto_update->setText(QApplication::translate("widget_update_fw", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_update_fw: public Ui_widget_update_fw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_UPDATE_FW_H
