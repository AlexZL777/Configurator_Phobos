#include "widget_power_data.h"
#include "ui_widget_power_data.h"

#include <Logger/Logger.h>

#include <QtMath>

float powCoefA;
float powCoefB;
float powCoefC;
float angl_AC;
float angl_AB;
float angl_BC;

/*QByteArray obis_buf[255];// = new QByteArray [];
QString data_buf[255];*/// = new QString [];

widget_power_data::widget_power_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_power_data)
{
    ui->setupUi(this);
    hide();
}

widget_power_data::~widget_power_data()
{
    delete ui;
}

void widget_power_data::slot_show_widget_power_data(){
    show();
    transmit = false;
    count = 0;
}

void widget_power_data::slot_hide_power_data(){
    hide();
    ui->textBrowser_8->setText("");     //Вывод Ток фазы А
    ui->textBrowser_9->setText("");     //Вывод Ток фазы B
    ui->textBrowser_10->setText("");    //Вывод Ток фазы C
    ui->textBrowser_2->setText("");     //Вывод Напряжения фазы А
    ui->textBrowser_3->setText("");     //Вывод Напряжения фазы B
    ui->textBrowser_4->setText("");     //Вывод Напряжения фазы C
    ui->textBrowser_20->setText("");    //Вывод Коэффициента мощности фазы А
    ui->textBrowser_21->setText("");    //Вывод Коэффициента мощности фазы B
    ui->textBrowser_22->setText("");    //Вывод Коэффициента мощности фазы C
    ui->textBrowser_24->setText("");    //Вывод Частота сети
    ui->textBrowser_18->setText("");    //Вывод Полная мощность
    ui->textBrowser_38->setText("");    //Вывод Полная мощность фазы А
    ui->textBrowser_39->setText("");    //Вывод Полная мощность фазы В
    ui->textBrowser_40->setText("");    //Вывод Полная мощность фазы C
    ui->textBrowser_6->setText("");     //Вывод Активная мощность
    ui->textBrowser_14->setText("");    //Вывод Активная мощность фазы А
    ui->textBrowser_15->setText("");    //Вывод Активная мощность фазы В
    ui->textBrowser_16->setText("");    //Вывод Активная мощность фазы C
    ui->textBrowser_12->setText("");    //Вывод Реактивная мощность
    ui->textBrowser_32->setText("");    //Вывод Реактивная мощность фазы А
    ui->textBrowser_33->setText("");    //Вывод Реактивная мощность фазы В
    ui->textBrowser_34->setText("");    //Вывод Реактивная мощность фазы C
    ui->textBrowser_30->setText("");    //Вывод Угол между фазами A и B
    ui->textBrowser_36->setText("");    //Вывод Угол между фазами B и C
    ui->textBrowser_42->setText("");    //Вывод Угол между фазами A и C
    ui->textBrowser_26->setText("");
    ui->textBrowser_27->setText("");
    ui->textBrowser_28->setText("");
}

void widget_power_data::slot_start_pdata(){
    QByteArray arr = QByteArray::fromHex("C001C1000101005E0700FF0300");
    transmit = true;
    count = 0;
    emit signal_write_data_PDU (arr);
}

void widget_power_data::slot_read_data(QVariant data){
    if (transmit){
        transmit = false;
        QByteArray arr;
        QVariantMap vm = data.toMap();
        switch (count) {
            case 0:
                if (vm.contains("array")){
                    QVariantList list = vm.value("array", QVariantMap()).toList();
                 //   log_1 << list[0];
                    for (int i = 0; i < list.size(); ++i) {
                        QVariantMap vm = list.at(i).toMap();
                        QVariantList vl = vm.value("structure", QVariantList()).toList();
                        for (int k = 0; k < vl.size(); ++k) {
                            QVariantMap vm = vl.at(k).toMap();
                            if (vm.contains("octet-string")){
                                arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
                             //   QString::fromAscii(data.data());
                                obis_buf[i] = arr;
                                log_1 << QString::number(i);
                                log_1 << obis_buf[k].toHex().toUpper();

                            }
                        }
                    }
                    QByteArray arr = QByteArray::fromHex("C001C1000101005E0700FF0200");
                    transmit = true;
                    count = 1;
                    emit signal_write_data_PDU (arr);
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
                    log_1 << QString::number(count_buf);
                    for (int n = 0; n < count_buf; ++n) {
                        log_1 << obis_buf[n].toHex().toUpper();
                        QString b;
                        b.setNum(data_buf[n], 'g', 4);
                        log_1 << b;//QString::number(data_buf[n]);
                        if (obis_buf[n].toHex().toUpper() == "01001F0700FF") ui->textBrowser_8->setText(QString::number(data_buf[n]));          //Вывод Ток фазы А
                        if (obis_buf[n].toHex().toUpper() == "0100330700FF") ui->textBrowser_9->setText(QString::number(data_buf[n]));          //Вывод Ток фазы B
                        if (obis_buf[n].toHex().toUpper() == "0100470700FF") ui->textBrowser_10->setText(QString::number(data_buf[n]));         //Вывод Ток фазы C
                        if (obis_buf[n].toHex().toUpper() == "0100200700FF") ui->textBrowser_2->setText(QString::number(data_buf[n]));          //Вывод Напряжения фазы А
                        if (obis_buf[n].toHex().toUpper() == "0100340700FF") ui->textBrowser_3->setText(QString::number(data_buf[n]));          //Вывод Напряжения фазы B
                        if (obis_buf[n].toHex().toUpper() == "0100480700FF") ui->textBrowser_4->setText(QString::number(data_buf[n]));          //Вывод Напряжения фазы C
                        if (obis_buf[n].toHex().toUpper() == "0100210700FF") ui->textBrowser_14->setText(QString::number(data_buf[n]));         //Вывод Коэффициента мощности фазы А cosF
                        if (obis_buf[n].toHex().toUpper() == "0100350700FF") ui->textBrowser_15->setText(QString::number(data_buf[n]));         //Вывод Коэффициента мощности фазы B cosF
                        if (obis_buf[n].toHex().toUpper() == "0100490700FF") ui->textBrowser_16->setText(QString::number(data_buf[n]));         //Вывод Коэффициента мощности фазы C cosF
                        if (obis_buf[n].toHex().toUpper() == "01000E0700FF") ui->textBrowser_24->setText(QString::number(data_buf[n]));         //Вывод Частота сети
                        if (obis_buf[n].toHex().toUpper() == "0100090700FF") ui->textBrowser_18->setText(QString::number(abs(data_buf[n])));    //Вывод Полная мощность
                        if (obis_buf[n].toHex().toUpper() == "01001D0700FF") ui->textBrowser_38->setText(QString::number(data_buf[n]));         //Вывод Полная мощность фазы А
                        if (obis_buf[n].toHex().toUpper() == "0100310700FF") ui->textBrowser_39->setText(QString::number(data_buf[n]));         //Вывод Полная мощность фазы В
                        if (obis_buf[n].toHex().toUpper() == "0100450700FF") ui->textBrowser_40->setText(QString::number(data_buf[n]));         //Вывод Полная мощность фазы C
                        if (obis_buf[n].toHex().toUpper() == "0100010700FF") ui->textBrowser_6->setText(QString::number(abs(data_buf[n])));     //Вывод Активная мощность
                        if (obis_buf[n].toHex().toUpper() == "0100150700FF"){
                            actPowA = abs(data_buf[n]);
                            ui->textBrowser_26->setText(QString::number(actPowA));    //Вывод Активная мощность фазы А
                        }
                        if (obis_buf[n].toHex().toUpper() == "0100290700FF"){
                            actPowB = abs(data_buf[n]);
                            ui->textBrowser_27->setText(QString::number(actPowB));    //Вывод Активная мощность фазы В
                        }
                        if (obis_buf[n].toHex().toUpper() == "01003D0700FF"){
                            actPowC = abs(data_buf[n]);
                            ui->textBrowser_28->setText(QString::number(actPowC));    //Вывод Активная мощность фазы C
                        }
                        if (obis_buf[n].toHex().toUpper() == "0100030700FF") ui->textBrowser_12->setText(QString::number(abs(data_buf[n])));    //Вывод Реактивная мощность
                        if (obis_buf[n].toHex().toUpper() == "0100170700FF"){
                            reactPowA = abs(data_buf[n]);
                            ui->textBrowser_32->setText(QString::number(reactPowA));    //Вывод Реактивная мощность фазы А
                        }
                        if (obis_buf[n].toHex().toUpper() == "01002B0700FF"){
                            reactPowB = abs(data_buf[n]);
                            ui->textBrowser_33->setText(QString::number(reactPowB));    //Вывод Реактивная мощность фазы В
                        }
                        if (obis_buf[n].toHex().toUpper() == "01003F0700FF"){
                            reactPowC = abs(data_buf[n]);
                            ui->textBrowser_34->setText(QString::number(reactPowC));    //Вывод Реактивная мощность фазы C
                        }
                        if (obis_buf[n].toHex().toUpper() == "010051070AFF"){
                            angl_AB = data_buf[n];
                            ui->textBrowser_30->setText(QString::number(angl_AB));    //Вывод Угол между фазами A и B
                        }
                        if (obis_buf[n].toHex().toUpper() == "0100510715FF"){
                            angl_BC = data_buf[n];
                            ui->textBrowser_36->setText(QString::number(angl_BC));    //Вывод Угол между фазами B и C
                        }
                        angl_AC = 360 - angl_AB - angl_BC;
                        ui->textBrowser_42->setText(QString::number(angl_AC));    //Вывод Угол между фазами A и C
                        //if (obis_buf[n].toHex().toUpper() == "0100510702FF") ui->textBrowser_42->setText(QString::number(data_buf[n]));    //Вывод Угол между фазами A и C
                        powCoefA = atan2(reactPowA, actPowA / M_PI * 180);
                        ui->textBrowser_20->setText(QString::number(powCoefA));    //Вывод Коэффициента мощности фазы А град
                        powCoefB = atan2(reactPowB, actPowB / M_PI * 180);
                        ui->textBrowser_21->setText(QString::number(powCoefB));    //Вывод Коэффициента мощности фазы B град
                        powCoefC = atan2(reactPowC, actPowC / M_PI * 180);
                        ui->textBrowser_22->setText(QString::number(powCoefC));    //Вывод Коэффициента мощности фазы C град
                        emit signal_repaint();
                    }
                }
                return;
        }
    }
}

void widget_power_data::slot_view_pdata(QVariant data){

}

void widget_power_data::turn (){

}
