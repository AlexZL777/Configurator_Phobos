/********************************************************************************
** Form generated from reading UI file 'widget_log.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_LOG_H
#define UI_WIDGET_LOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_log
{
public:

    void setupUi(QWidget *widget_log)
    {
        if (widget_log->objectName().isEmpty())
            widget_log->setObjectName(QString::fromUtf8("widget_log"));
        widget_log->resize(410, 325);

        retranslateUi(widget_log);

        QMetaObject::connectSlotsByName(widget_log);
    } // setupUi

    void retranslateUi(QWidget *widget_log)
    {
        widget_log->setWindowTitle(QApplication::translate("widget_log", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_log: public Ui_widget_log {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_LOG_H
