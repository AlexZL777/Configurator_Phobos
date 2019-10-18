#include "widget_power_data.h"
#include "ui_widget_power_data.h"

#include <Logger/Logger.h>

#include <QtMath>
#include <qmath.h>
#include <QPalette>

extern int count_bar;

float powCoefA;
float powCoefB;
float powCoefC;
float angl_AC;
float angl_AB;
float angl_BC;

widget_power_data::widget_power_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_power_data)
{
    ui->setupUi(this);

    point_p = new point_power(this);
    ui->verticalLayout_2->addWidget(point_p);
    ui->gridLayout->setAlignment( Qt::AlignLeft );
    connect (this, &widget_power_data::signal_repaint, point_p, &point_power::slot_repaint, Qt::QueuedConnection);
    tmr_tout = new QTimer();
    connect(tmr_tout, SIGNAL(timeout()), this, SLOT(timeout()));
}

widget_power_data::~widget_power_data()
{
    delete ui;
}

bool widget_power_data::transmitt(){
    return transmit;
}

void widget_power_data::timeout(){
    if (count == 0){
        transmit = true;
        count_bar = 34;
        emit signal_bar(count_bar);
        emit signal_write_data_PDU (QByteArray::fromHex("C001C1000101005E0700FF0300"));
    }
    else {
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C1000101005E0700FF0200"));
    }
    if (count_tout < 2){
        count_tout++;
        tmr_tout->start(3000);
    }
    else if ( count_tout == 2 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(3000);
    }
    else if ( count_tout == 3 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(6000);
    }
    else if ( count_tout == 4 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(12000);
    }
    else if ( count_tout > 4 ) {
        transmit = false;
        tmr_tout->stop();
        emit signal_timeout_start (100);
        emit signal_disable_tab_kn(0, 2);
    }
}

void widget_power_data::slot_show_widget_power_data(){
    transmit = false;
    count = 0;
}

void widget_power_data::slot_disconnect(){
    count = 0;
    transmit = false;
    tmr_tout->stop();
    slot_hide_power_data();
}

void widget_power_data::slot_hide_power_data(){
    ui->lineEdit_8->setText("");     //Вывод Ток фазы А
    ui->lineEdit_9->setText("");     //Вывод Ток фазы B
    ui->lineEdit_10->setText("");    //Вывод Ток фазы C
    ui->lineEdit_2->setText("");     //Вывод Напряжения фазы А
    ui->lineEdit_3->setText("");     //Вывод Напряжения фазы B
    ui->lineEdit_4->setText("");     //Вывод Напряжения фазы C
    ui->lineEdit_20->setText("");    //Вывод Коэффициента мощности фазы А
    ui->lineEdit_21->setText("");    //Вывод Коэффициента мощности фазы B
    ui->lineEdit_22->setText("");    //Вывод Коэффициента мощности фазы C
    ui->lineEdit_24->setText("");    //Вывод Частота сети
    ui->lineEdit_18->setText("");    //Вывод Полная мощность
    ui->lineEdit_38->setText("");    //Вывод Полная мощность фазы А
    ui->lineEdit_39->setText("");    //Вывод Полная мощность фазы В
    ui->lineEdit_40->setText("");    //Вывод Полная мощность фазы C
    ui->lineEdit_6->setText("");     //Вывод Активная мощность
    ui->lineEdit_14->setText("");    //Вывод Коэффициента мощности фазы А cosF
    ui->lineEdit_15->setText("");    //Вывод Коэффициента мощности фазы B cosF
    ui->lineEdit_16->setText("");    //Вывод Коэффициента мощности фазы C cosF
    ui->lineEdit_12->setText("");    //Вывод Реактивная мощность
    ui->lineEdit_32->setText("");    //Вывод Реактивная мощность фазы А
    ui->lineEdit_33->setText("");    //Вывод Реактивная мощность фазы В
    ui->lineEdit_34->setText("");    //Вывод Реактивная мощность фазы C
    ui->lineEdit_30->setText("");    //Вывод Угол между фазами A и B
    ui->lineEdit_36->setText("");    //Вывод Угол между фазами B и C
    ui->lineEdit_42->setText("");    //Вывод Угол между фазами A и C
    ui->lineEdit_26->setText("");    //Вывод Активная мощность фазы А
    ui->lineEdit_27->setText("");    //Вывод Активная мощность фазы B
    ui->lineEdit_28->setText("");    //Вывод Активная мощность фазы C
}

void widget_power_data::slot_start_pdata(){
    QByteArray arr = QByteArray::fromHex("C001C1000101005E0700FF0300");
    transmit = true;
    count = 0;
    count_bar = 34;
    emit signal_bar(count_bar);
    emit signal_write_data_PDU (arr);
    count_tout = 0;
    tmr_tout->start(3000);
}

void widget_power_data::slot_read_data(QVariant data){
    if (transmit){
        count_bar += 34;
        emit signal_bar(count_bar);
        transmit = false;
        tmr_tout->stop();
        QByteArray arr;
        QVariantMap vm = data.toMap();
        switch (count) {
            case 0:
                if (vm.contains("array")){
                    QVariantList list = vm.value("array", QVariantMap()).toList();
                    for (int i = 0; i < list.size(); ++i) {
                        QVariantMap vm = list.at(i).toMap();
                        QVariantList vl = vm.value("structure", QVariantList()).toList();
                        for (int k = 0; k < vl.size(); ++k) {
                            QVariantMap vm = vl.at(k).toMap();
                            if (vm.contains("octet-string")){
                                arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
                                obis_buf[i] = arr;
                             //   log_1 << "i" << i << obis_buf[k].toHex().toUpper();

                            }
                        }
                    }
                    QByteArray arr = QByteArray::fromHex("C001C1000101005E0700FF0200");
                    transmit = true;
                    count = 1;
                    emit signal_write_data_PDU (arr);
                    count_tout = 0;
                    tmr_tout->start(3000);
                }
                return;
            case 1:
                unsigned long b;
                int count_buf = 0;
                if (vm.contains("array")){
                    QVariantList list = vm.value("array", QVariantMap()).toList();
                    for (int i = 0; i < list.size(); ++i) {
                        QVariantMap vm = list.at(i).toMap();
                        QVariantList vl = vm.value("structure", QVariantList()).toList();
                        for (int k = 0; k < vl.size(); ++k) {
                            QVariantMap vm = vl.at(k).toMap();
                            if (vm.contains("octet-string")){
//                                data_buf[k] = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
                                count_buf++;
//                                log_1 << arr.toHex().toUpper();
                            }
                            if (vm.contains("double-long")){
                                long a = vm["double-long"].toLongLong();
                                float b = (float)a/1000;
                                data_buf[k] = b;
                                count_buf++;
                            }
                            if (vm.contains("double-long-unsigned")){
                                long a = vm["double-long-unsigned"].toLongLong();
                                float b = (float)a/1000;
                                data_buf[k] = b;
                                count_buf++;
                            }
                        }
                    }
                    for (int n = 0; n < count_buf; ++n) {
                        QString b;
                        b.setNum(data_buf[n], 'g', 4);
                    //    log_1 << "n" << n << obis_buf[n].toHex().toUpper() << b;
                        if (obis_buf[n].toHex().toUpper() == "01001F0700FF") ui->lineEdit_8->setText(QString::number(data_buf[n]));          //Вывод Ток фазы А
                        if (obis_buf[n].toHex().toUpper() == "0100330700FF") ui->lineEdit_9->setText(QString::number(data_buf[n]));          //Вывод Ток фазы B
                        if (obis_buf[n].toHex().toUpper() == "0100470700FF") ui->lineEdit_10->setText(QString::number(data_buf[n]));         //Вывод Ток фазы C
                        if (obis_buf[n].toHex().toUpper() == "0100200700FF") ui->lineEdit_2->setText(QString::number(data_buf[n]));          //Вывод Напряжения фазы А
                        if (obis_buf[n].toHex().toUpper() == "0100340700FF") ui->lineEdit_3->setText(QString::number(data_buf[n]));          //Вывод Напряжения фазы B
                        if (obis_buf[n].toHex().toUpper() == "0100480700FF") ui->lineEdit_4->setText(QString::number(data_buf[n]));          //Вывод Напряжения фазы C
                        if (obis_buf[n].toHex().toUpper() == "01000E0700FF") ui->lineEdit_24->setText(QString::number(data_buf[n]));         //Вывод Частота сети
                        if (obis_buf[n].toHex().toUpper() == "0100090700FF") ui->lineEdit_18->setText(QString::number(data_buf[n]*1000));    //Вывод Полная мощность
                        if (obis_buf[n].toHex().toUpper() == "01001D0700FF") ui->lineEdit_38->setText(QString::number(data_buf[n]*1000));         //Вывод Полная мощность фазы А
                        if (obis_buf[n].toHex().toUpper() == "0100310700FF") ui->lineEdit_39->setText(QString::number(data_buf[n]*1000));         //Вывод Полная мощность фазы В
                        if (obis_buf[n].toHex().toUpper() == "0100450700FF") ui->lineEdit_40->setText(QString::number(data_buf[n]*1000));         //Вывод Полная мощность фазы C
                        if (obis_buf[n].toHex().toUpper() == "0100010700FF") ui->lineEdit_6->setText(QString::number(data_buf[n]*1000));     //Вывод Активная мощность
                        if (obis_buf[n].toHex().toUpper() == "0100150700FF"){
                            actPowA = data_buf[n];
                            ui->lineEdit_26->setText(QString::number(actPowA*1000));    //Вывод Активная мощность фазы А
                        }
                        if (obis_buf[n].toHex().toUpper() == "0100290700FF"){
                            actPowB = data_buf[n];
                            ui->lineEdit_27->setText(QString::number(actPowB*1000));    //Вывод Активная мощность фазы В
                        }
                        if (obis_buf[n].toHex().toUpper() == "01003D0700FF"){
                            actPowC = data_buf[n];
                            ui->lineEdit_28->setText(QString::number(actPowC*1000));    //Вывод Активная мощность фазы C
                        }
                        if (obis_buf[n].toHex().toUpper() == "0100030700FF") ui->lineEdit_12->setText(QString::number(data_buf[n]*1000));    //Вывод Реактивная мощность
                        if (obis_buf[n].toHex().toUpper() == "0100170700FF"){
                            reactPowA = data_buf[n];
                            ui->lineEdit_32->setText(QString::number(reactPowA*1000));    //Вывод Реактивная мощность фазы А
                        }
                        if (obis_buf[n].toHex().toUpper() == "01002B0700FF"){
                            reactPowB = data_buf[n];
                            ui->lineEdit_33->setText(QString::number(reactPowB*1000));    //Вывод Реактивная мощность фазы В
                        }
                        if (obis_buf[n].toHex().toUpper() == "01003F0700FF"){
                            reactPowC = data_buf[n];
                            ui->lineEdit_34->setText(QString::number(reactPowC*1000));    //Вывод Реактивная мощность фазы C
                        }
                        if (obis_buf[n].toHex().toUpper() == "010051070AFF"){
                            angl_AB = data_buf[n];
                            ui->lineEdit_30->setText(QString::number(angl_AB));    //Вывод Угол между фазами A и B
                        }
                        if (obis_buf[n].toHex().toUpper() == "0100510715FF"){
                            angl_BC = data_buf[n];
                            ui->lineEdit_36->setText(QString::number(angl_BC));    //Вывод Угол между фазами B и C
                        }
//                        if (obis_buf[n].toHex().toUpper() == "0100210700FF"){

//                        }
                      //  if (obis_buf[n].toHex().toUpper() == "0100350700FF") ui->lineEdit_15->setText(QString::number(data_buf[n]));         //Вывод Коэффициента мощности фазы B cosF
                      //  if (obis_buf[n].toHex().toUpper() == "0100490700FF") ui->lineEdit_16->setText(QString::number(data_buf[n]));         //Вывод Коэффициента мощности фазы C cosF
                    }
                    if (qSqrt(actPowA*actPowA + reactPowA*reactPowA) == 0) ui->lineEdit_14->setText("1");
                    else ui->lineEdit_14->setText(QString::number(actPowA / (qSqrt(actPowA*actPowA + reactPowA*reactPowA))));         //Вывод Коэффициента мощности фазы А cosF
                    if (qSqrt(actPowB*actPowB + reactPowB*reactPowB) == 0) ui->lineEdit_15->setText("1");
                    else ui->lineEdit_15->setText(QString::number(actPowB / (qSqrt(actPowB*actPowB + reactPowB*reactPowB))));         //Вывод Коэффициента мощности фазы B cosF
                    if (qSqrt(actPowC*actPowC + reactPowC*reactPowC) == 0) ui->lineEdit_16->setText("1");
                    else ui->lineEdit_16->setText(QString::number(actPowC / (qSqrt(actPowC*actPowC + reactPowC*reactPowC))));         //Вывод Коэффициента мощности фазы C cosF
                    angl_AC = 360 - angl_AB - angl_BC;
                    ui->lineEdit_42->setText(QString::number(angl_AC));    //Вывод Угол между фазами A и C
                    //if (obis_buf[n].toHex().toUpper() == "0100510702FF") ui->lineEdit_42->setText(QString::number(data_buf[n]));    //Вывод Угол между фазами A и C
                    powCoefA = atan2(reactPowA, actPowA) / M_PI *180;

                    ui->lineEdit_20->setText(QString::number(powCoefA));    //Вывод Коэффициента мощности фазы А град
                    powCoefB = atan2(reactPowB, actPowB) / M_PI *180;
                    ui->lineEdit_21->setText(QString::number(powCoefB));    //Вывод Коэффициента мощности фазы B град
                    powCoefC = atan2(reactPowC, actPowC) / M_PI *180;
                    ui->lineEdit_22->setText(QString::number(powCoefC));    //Вывод Коэффициента мощности фазы C град
                    emit signal_repaint();
                    emit signal_disable_tab_kn(0, 2);
                }
                return;
        }
    }
}
