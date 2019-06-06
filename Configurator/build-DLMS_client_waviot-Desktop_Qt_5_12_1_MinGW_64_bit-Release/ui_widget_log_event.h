/********************************************************************************
** Form generated from reading UI file 'widget_log_event.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_LOG_EVENT_H
#define UI_WIDGET_LOG_EVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_log_event
{
public:

    void setupUi(QWidget *widget_log_event)
    {
        if (widget_log_event->objectName().isEmpty())
            widget_log_event->setObjectName(QString::fromUtf8("widget_log_event"));
        widget_log_event->resize(400, 300);

        retranslateUi(widget_log_event);

        QMetaObject::connectSlotsByName(widget_log_event);
    } // setupUi

    void retranslateUi(QWidget *widget_log_event)
    {
        widget_log_event->setWindowTitle(QApplication::translate("widget_log_event", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_log_event: public Ui_widget_log_event {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_LOG_EVENT_H
