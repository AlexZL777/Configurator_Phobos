#include "widget_power_data_1f.h"
#include "ui_widget_power_data_1f.h"

#include <Logger/Logger.h>

extern int count_bar;

widget_power_data_1f::widget_power_data_1f(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_power_data_1f)
{
    ui->setupUi(this);
    ui->gridLayout->setAlignment( Qt::AlignLeft );
  //  hide();
    tmr_tout = new QTimer();
    connect(tmr_tout, SIGNAL(timeout()), this, SLOT(timeout()));
}

widget_power_data_1f::~widget_power_data_1f()
{
    delete ui;
}

bool widget_power_data_1f::transmitt(){
    return transmit;
}

void widget_power_data_1f::slot_show_widget_power_data_1f(){
   // show();
    transmit = false;
    count = 0;
    count_bar = 34;
    emit signal_bar(count_bar);
}

void widget_power_data_1f::slot_disconnect(){
    tmr_tout->stop();
    transmit = false;
    count = 0;
    slot_hide_power_data_1f();
}

void widget_power_data_1f::slot_hide_power_data_1f(){
 //   hide();
    ui->lineEdit_2->setText("");     //Вывод
    ui->lineEdit_4->setText("");     //Вывод
    ui->lineEdit_6->setText("");    //Вывод
    ui->lineEdit_8->setText("");     //Вывод
    ui->lineEdit_10->setText("");     //Вывод
    ui->lineEdit_12->setText("");     //Вывод
    ui->lineEdit_14->setText("");    //Вывод
    ui->lineEdit_16->setText("");    //Вывод
}

void widget_power_data_1f::timeout(){
    log_1 << "count_tout"  << count_tout;
    if (count == 0){
        transmit = true;
        count = 0;
        emit signal_write_data_PDU_1f (QByteArray::fromHex("C001C1000101005E0700FF0300"));
    }
    else {
        transmit = true;
        count = 1;
        emit signal_write_data_PDU_1f (QByteArray::fromHex("C001C1000101005E0700FF0200"));
    }
    if (count_tout < 3){
        count_tout++;
        tmr_tout->start(5000);
    }
    else if ( count_tout == 3 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(5000);
    }
    else {
        transmit = false;
        tmr_tout->stop();
        emit signal_timeout_start (100);
        emit signal_disable_tab_kn(0, 3);
    }
}

void widget_power_data_1f::slot_start_pdata_1f(){
    transmit = true;
    count = 0;
    count_bar = 34;
    emit signal_bar(count_bar);
    emit signal_write_data_PDU_1f (QByteArray::fromHex("C001C1000101005E0700FF0300"));
  //  emit signal_timeout_start(5000);
    count_tout = 0;
    tmr_tout->start(5000);
}

void widget_power_data_1f::slot_read_data(QVariant data){
    if (transmit){
        transmit = false;
        tmr_tout->stop();
        count_bar += 34;
        emit signal_bar(count_bar);
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
                            //    log_1 << QString::number(i);
                            //    log_1 << obis_buf[k].toHex().toUpper();

                            }
                        }
                    }
                    QByteArray arr = QByteArray::fromHex("C001C1000101005E0700FF0200");
                    transmit = true;
                    count = 1;
                    emit signal_write_data_PDU_1f (arr);
                 //   emit signal_timeout_start(3000);
                    count_tout = 0;
                    tmr_tout->start(5000);
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
                  //  log_1 << QString::number(count_buf);
                    for (int n = 0; n < count_buf; ++n) {
                    //    log_1 << obis_buf[n].toHex().toUpper();
                        QString b;
                        b.setNum(data_buf[n], 'g', 4);
                     //   log_1 << b;
                        if (obis_buf[n].toHex().toUpper() == "01000C0700FF") ui->lineEdit_2->setText(QString::number(data_buf[n]));     //Вывод Напряжение
                        if (obis_buf[n].toHex().toUpper() == "01000B0700FF") ui->lineEdit_4->setText(QString::number(data_buf[n]));     //Вывод Ток
                        if (obis_buf[n].toHex().toUpper() == "01005B0700FF") ui->lineEdit_6->setText(QString::number(data_buf[n]));     //Вывод Ток нулевого провода
                        if (obis_buf[n].toHex().toUpper() == "01000D0700FF") ui->lineEdit_8->setText(QString::number(data_buf[n]));     //Вывод Коэффициент мощности
                        if (obis_buf[n].toHex().toUpper() == "01000E0700FF") ui->lineEdit_10->setText(QString::number(data_buf[n]));    //Вывод Частота сети
                        if (obis_buf[n].toHex().toUpper() == "0100090700FF") ui->lineEdit_12->setText(QString::number(data_buf[n]*1000));    //Вывод Полная мощность
                        if (obis_buf[n].toHex().toUpper() == "0100010700FF") ui->lineEdit_14->setText(QString::number(data_buf[n]*1000));    //Вывод Активная мощность
                        if (obis_buf[n].toHex().toUpper() == "0100030700FF") ui->lineEdit_16->setText(QString::number(data_buf[n]*1000));    //Вывод Реактивная мощность
                    }
                    emit signal_disable_tab_kn(0, 3);
                }
                return;
        }
    }
}
