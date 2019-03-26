/********************************************************************************
** Form generated from reading UI file 'widget_connect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_CONNECT_H
#define UI_WIDGET_CONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget_connect
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_udp_hdlc;
    QRadioButton *radioButton_rs_fastdl;
    QRadioButton *radioButton_rs_fastdl_hdlc;
    QRadioButton *radioButton_rs_485;
    QRadioButton *radioButton_opto_hdlc;
    QRadioButton *radioButton_opto_mode_e;
    QRadioButton *radioButton_rs_fastdl_electro;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_com_port;
    QLineEdit *lineEdit_host_udp_direct;
    QSpinBox *spinBox_port_udp_direct;
    QPushButton *pushButton_connect;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_client_addr;
    QLabel *label_pass;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpinBox *spinBox_server_addr_logical;
    QLabel *label_4;
    QSpinBox *spinBox_server_addr_physical;
    QLabel *label_2;
    QLineEdit *lineEdit_pass;
    QLabel *label;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBox_modem_dec;
    QSpinBox *spinBox_modem_hex;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *widget_connect)
    {
        if (widget_connect->objectName().isEmpty())
            widget_connect->setObjectName(QString::fromUtf8("widget_connect"));
        widget_connect->resize(390, 421);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_connect->sizePolicy().hasHeightForWidth());
        widget_connect->setSizePolicy(sizePolicy);
        widget_connect->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(widget_connect);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radioButton_udp_hdlc = new QRadioButton(widget_connect);
        radioButton_udp_hdlc->setObjectName(QString::fromUtf8("radioButton_udp_hdlc"));
        radioButton_udp_hdlc->setChecked(false);

        verticalLayout->addWidget(radioButton_udp_hdlc);

        radioButton_rs_fastdl = new QRadioButton(widget_connect);
        radioButton_rs_fastdl->setObjectName(QString::fromUtf8("radioButton_rs_fastdl"));

        verticalLayout->addWidget(radioButton_rs_fastdl);

        radioButton_rs_fastdl_hdlc = new QRadioButton(widget_connect);
        radioButton_rs_fastdl_hdlc->setObjectName(QString::fromUtf8("radioButton_rs_fastdl_hdlc"));

        verticalLayout->addWidget(radioButton_rs_fastdl_hdlc);

        radioButton_rs_485 = new QRadioButton(widget_connect);
        radioButton_rs_485->setObjectName(QString::fromUtf8("radioButton_rs_485"));
        radioButton_rs_485->setChecked(false);

        verticalLayout->addWidget(radioButton_rs_485);

        radioButton_opto_hdlc = new QRadioButton(widget_connect);
        radioButton_opto_hdlc->setObjectName(QString::fromUtf8("radioButton_opto_hdlc"));
        radioButton_opto_hdlc->setChecked(true);

        verticalLayout->addWidget(radioButton_opto_hdlc);

        radioButton_opto_mode_e = new QRadioButton(widget_connect);
        radioButton_opto_mode_e->setObjectName(QString::fromUtf8("radioButton_opto_mode_e"));

        verticalLayout->addWidget(radioButton_opto_mode_e);

        radioButton_rs_fastdl_electro = new QRadioButton(widget_connect);
        radioButton_rs_fastdl_electro->setObjectName(QString::fromUtf8("radioButton_rs_fastdl_electro"));
        radioButton_rs_fastdl_electro->setChecked(false);

        verticalLayout->addWidget(radioButton_rs_fastdl_electro);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox_com_port = new QComboBox(widget_connect);
        comboBox_com_port->setObjectName(QString::fromUtf8("comboBox_com_port"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_com_port->sizePolicy().hasHeightForWidth());
        comboBox_com_port->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(10);
        comboBox_com_port->setFont(font);
        comboBox_com_port->setMaxVisibleItems(10);

        horizontalLayout->addWidget(comboBox_com_port);

        lineEdit_host_udp_direct = new QLineEdit(widget_connect);
        lineEdit_host_udp_direct->setObjectName(QString::fromUtf8("lineEdit_host_udp_direct"));
        sizePolicy1.setHeightForWidth(lineEdit_host_udp_direct->sizePolicy().hasHeightForWidth());
        lineEdit_host_udp_direct->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lineEdit_host_udp_direct);

        spinBox_port_udp_direct = new QSpinBox(widget_connect);
        spinBox_port_udp_direct->setObjectName(QString::fromUtf8("spinBox_port_udp_direct"));
        sizePolicy1.setHeightForWidth(spinBox_port_udp_direct->sizePolicy().hasHeightForWidth());
        spinBox_port_udp_direct->setSizePolicy(sizePolicy1);
        spinBox_port_udp_direct->setMaximum(99999999);
        spinBox_port_udp_direct->setValue(10023);

        horizontalLayout->addWidget(spinBox_port_udp_direct);


        verticalLayout_3->addLayout(horizontalLayout);

        pushButton_connect = new QPushButton(widget_connect);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        sizePolicy1.setHeightForWidth(pushButton_connect->sizePolicy().hasHeightForWidth());
        pushButton_connect->setSizePolicy(sizePolicy1);
        pushButton_connect->setFont(font);
        pushButton_connect->setCheckable(true);

        verticalLayout_3->addWidget(pushButton_connect);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox_client_addr = new QComboBox(widget_connect);
        comboBox_client_addr->setObjectName(QString::fromUtf8("comboBox_client_addr"));
        comboBox_client_addr->setMinimumSize(QSize(200, 0));
        comboBox_client_addr->setFont(font);

        gridLayout_2->addWidget(comboBox_client_addr, 0, 1, 1, 1);

        label_pass = new QLabel(widget_connect);
        label_pass->setObjectName(QString::fromUtf8("label_pass"));
        sizePolicy1.setHeightForWidth(label_pass->sizePolicy().hasHeightForWidth());
        label_pass->setSizePolicy(sizePolicy1);
        label_pass->setFont(font);

        gridLayout_2->addWidget(label_pass, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(widget_connect);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        spinBox_server_addr_logical = new QSpinBox(widget_connect);
        spinBox_server_addr_logical->setObjectName(QString::fromUtf8("spinBox_server_addr_logical"));
        spinBox_server_addr_logical->setFont(font);
        spinBox_server_addr_logical->setMaximum(16383);

        horizontalLayout_4->addWidget(spinBox_server_addr_logical);

        label_4 = new QLabel(widget_connect);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFont(font);

        horizontalLayout_4->addWidget(label_4);

        spinBox_server_addr_physical = new QSpinBox(widget_connect);
        spinBox_server_addr_physical->setObjectName(QString::fromUtf8("spinBox_server_addr_physical"));
        spinBox_server_addr_physical->setFont(font);
        spinBox_server_addr_physical->setMaximum(16383);
        spinBox_server_addr_physical->setValue(1);

        horizontalLayout_4->addWidget(spinBox_server_addr_physical);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        label_2 = new QLabel(widget_connect);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_pass = new QLineEdit(widget_connect);
        lineEdit_pass->setObjectName(QString::fromUtf8("lineEdit_pass"));
        lineEdit_pass->setFont(font);

        gridLayout_2->addWidget(lineEdit_pass, 2, 1, 1, 1);

        label = new QLabel(widget_connect);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 9, -1, -1);
        spinBox_modem_dec = new QSpinBox(widget_connect);
        spinBox_modem_dec->setObjectName(QString::fromUtf8("spinBox_modem_dec"));
        sizePolicy1.setHeightForWidth(spinBox_modem_dec->sizePolicy().hasHeightForWidth());
        spinBox_modem_dec->setSizePolicy(sizePolicy1);
        spinBox_modem_dec->setMinimum(7274496);
        spinBox_modem_dec->setMaximum(16777215);
        spinBox_modem_dec->setValue(7520047);

        horizontalLayout_5->addWidget(spinBox_modem_dec);

        spinBox_modem_hex = new QSpinBox(widget_connect);
        spinBox_modem_hex->setObjectName(QString::fromUtf8("spinBox_modem_hex"));
        sizePolicy1.setHeightForWidth(spinBox_modem_hex->sizePolicy().hasHeightForWidth());
        spinBox_modem_hex->setSizePolicy(sizePolicy1);
        spinBox_modem_hex->setMinimum(7274496);
        spinBox_modem_hex->setMaximum(16777215);
        spinBox_modem_hex->setValue(7274496);
        spinBox_modem_hex->setDisplayIntegerBase(16);

        horizontalLayout_5->addWidget(spinBox_modem_hex);


        verticalLayout_3->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout_3, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);


        retranslateUi(widget_connect);

        QMetaObject::connectSlotsByName(widget_connect);
    } // setupUi

    void retranslateUi(QWidget *widget_connect)
    {
        widget_connect->setWindowTitle(QApplication::translate("widget_connect", "Form", nullptr));
        radioButton_udp_hdlc->setText(QApplication::translate("widget_connect", "UDP HDLC", nullptr));
        radioButton_rs_fastdl->setText(QApplication::translate("widget_connect", "Radio FAST DL", nullptr));
        radioButton_rs_fastdl_hdlc->setText(QApplication::translate("widget_connect", "Radio FAST DL HDLC", nullptr));
        radioButton_rs_485->setText(QApplication::translate("widget_connect", "RS-485", nullptr));
        radioButton_opto_hdlc->setText(QApplication::translate("widget_connect", "Opto HDLC", nullptr));
        radioButton_opto_mode_e->setText(QApplication::translate("widget_connect", "Opto Mode-E", nullptr));
        radioButton_rs_fastdl_electro->setText(QApplication::translate("widget_connect", "Radio FAST DL electro", nullptr));
        lineEdit_host_udp_direct->setText(QApplication::translate("widget_connect", "127.0.0.1", nullptr));
        pushButton_connect->setText(QApplication::translate("widget_connect", "connect DLMS", nullptr));
        label_pass->setText(QApplication::translate("widget_connect", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_3->setText(QApplication::translate("widget_connect", "logical", nullptr));
        label_4->setText(QApplication::translate("widget_connect", "physical", nullptr));
        label_2->setText(QApplication::translate("widget_connect", "\320\241\320\265\321\200\320\262\320\265\321\200", nullptr));
        label->setText(QApplication::translate("widget_connect", "\320\232\320\273\320\270\320\265\320\275\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget_connect: public Ui_widget_connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_CONNECT_H
