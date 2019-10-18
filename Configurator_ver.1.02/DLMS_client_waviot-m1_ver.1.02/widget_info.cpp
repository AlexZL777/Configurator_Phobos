#include "widget_info.h"
#include "ui_widget_info.h"

#include <Logger/Logger.h>
#include <assert.h>
#include <QDate>
#include <QTime>
#include <QList>
#include <QChar>
#include <QLineEdit>

int count_bar;
int type_counter;
QDateTime qdt;
QByteArray sn;
int ver_po[2];
int type[2];

typedef struct {
    uint8_t year_highbyte;
    uint8_t year_lowbyte;
    uint8_t month;
    uint8_t day_of_month;
    uint8_t day_of_week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t hundredths_of_second;
    uint8_t deviation_highbyte;
    uint8_t deviation_lowbyte;
    uint8_t clock_status;
} COSEM_date_time_struct;

widget_info::widget_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_info)
{
    ui->setupUi(this);
    ui->gridLayout->setAlignment( Qt::AlignLeft );
 //   hide();
    tmr_tout = new QTimer();
    connect(tmr_tout, SIGNAL(timeout()), this, SLOT(timeout()));
}

widget_info::~widget_info()
{
    delete ui;
}

bool widget_info::transmitt(){
    return transmit;
}

void widget_info::tmr_time(){
    tmr_t->stop();
    count = 15;
    widget_info::turn ();
}

void widget_info::timeout() {
    count_bar = 0;
    emit signal_bar(count_bar);
    log_1 << "count_tout" << count_tout;
    if ( count_tout < 2 ){
        count_tout++;

        if (count > 0) {
            transmit = true;
            count--;
          //  log_1 << "count" << count;
            widget_info::turn ();
        }
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
        count = 0;
        emit signal_timeout_start (100);
        emit signal_disable_tab_kn(0, 0);
    }
}

void widget_info::slot_show_widget_info(){
    count = 0;
    count_bar = 0;
    emit signal_bar(count_bar);
    transmit = true;
    emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600101FF0200")); //Запрос типа счетчика
    count_tout = 0;
    tmr_tout->start (3000);
}

void widget_info::slot_disconnect(){
    slot_hide_widget_info();
}

void widget_info::slot_hide_widget_info(){
    tmr_tout->stop();
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");
//    ui->lineEdit_9->setText("");
    ui->lineEdit_10->setText("");
    ui->lineEdit_11->setText("");
//    ui->lineEdit_12->setText("");
  //  hide();
  //  emit signal_bar(0);
  //  emit signal_min_window();
}

void widget_info::slot_view_data(QVariant(data))
{
    if (transmit){
        tmr_tout->stop();
        transmit = false;
        count_bar += 13;
    //    log_1 << "count_bar" << count_bar;
        emit signal_bar(count_bar);
        QByteArray arr;
        int a = 0;
        QVariantMap vm = data.toMap();
        if (vm.contains("long-unsigned")) a = vm["long-unsigned"].toInt();
        if (vm.contains("unsigned")) a = vm["unsigned"].toInt();
        if (vm.contains("octet-string")) arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
        if (vm.contains("date-time")) arr = QByteArray::fromHex(vm.value("date-time", "").toString().toLocal8Bit());
        if (count == 0){
            type_counter = arr.at(0);
            emit signal_fase(type_counter);
            emit signal_disable_tab_kn(1, 0);
            ui->lineEdit_2->setText(arr.toUpper());     //Вывод типа счетчика
            type[0] = arr.at(0) - 48;
            type[1] = arr.at(2) - 48;
            log_1 << "type" << type[0] << type[1];
            count = 1;
            widget_info::turn ();
            return;
        }
        if (count == 2){
            emit signal_main_window_sn(arr);
            sn = arr;
            ui->lineEdit->setText(arr.toUpper());       //Вывод серийного номера счетчика
            count = 3;
            widget_info::turn ();
            return;
        }
        if (count == 4){
            ui->lineEdit_3->setText(arr.toUpper());     //Вывод версии метрологического ПО
            count = 5;
            widget_info::turn ();
            return;
        }
        if (count == 6){
            char temp = arr[4];
            ver_po[0] = temp - '0';
            temp = arr[6];
            ver_po[1] = temp - '0';
            ui->lineEdit_4->setText(arr.toUpper());     //Вывод версии коммуникационного ПО
            count = 7;
            widget_info::turn ();
            return;
        }
        if (count == 8){
            QString s = QString::number(a);
            ui->lineEdit_5->setText(s);     //Вывод коэффициента трансформации по току
            count = 9;
            widget_info::turn ();
            return;
        }
        if (count == 10){
            QString s = QString::number(a);
            ui->lineEdit_6->setText(s);     //Вывод коэффициента трансформации по напряжению
            count = 11;
            widget_info::turn ();
            return;
        }
        if (count == 12){
            QString s = QString::number(a);
            ui->lineEdit_7->setText(s);     //Вывод даты выпуска счетчика
            count = 13;
            widget_info::turn ();
            return;
        }
        if (count == 14){
            COSEM_date_time_struct *cdt = (COSEM_date_time_struct *)arr.data();
            uint16_t y = (cdt->year_highbyte << 8) + cdt->year_lowbyte;
            QDateTime qdtn(QDate(y, cdt->month, cdt->day_of_month),QTime(cdt->hour,cdt->minute,cdt->second));
            qdt = qdtn;
            ui->lineEdit_8->setText(qdt.toString("dd.MM.yyyy"));          //Вывод системной даты счётчика
            ui->lineEdit_10->setText(qdt.toString("HH.mm.ss"));           //Вывод системного времени счётчика
            dev = arr.at(10);
            str_dev = str_dev.setNum((arr.at(9) << 8) + dev);
            ui->lineEdit_11->setText(str_dev);                            //Вывод значения девиации счётчика
            emit signal_disable_tab_kn(0, 0);
            return;
        }
    }
}

void widget_info::view_data_first()
{
    count = 0;
    QByteArray arr = QByteArray::fromHex("C001C100010000600101FF0200"); //Запрос типа счетчика
    transmit = true;
    emit signal_write_data_PDU (arr);
    tmr_tout->start(3000);
}

void widget_info::turn (){
    if (count == 1){
        count = 2;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600100FF0200"));     //Запрос серийного номера счетчика
        tmr_tout->start(3000);
        return;
    }
    if (count == 3){
        count = 4;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600102FF0200")); //Запрос версии метрологического ПО
        tmr_tout->start(3000);
        return;
    }
    if (count == 5){
        count = 6;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600103FF0200")); //Запрос версии коммуникационного ПО
        tmr_tout->start(3000);
        return;
    }
    if (count == 7){
        count = 8;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010100000402FF0200")); //Запрос коэффициента трансформации по току
        tmr_tout->start(3000);
        return;
    }
    if (count == 9){
        count = 10;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010100000403FF0200")); //Запрос коэффициента трансформации по напряжению
        tmr_tout->start(3000);
        return;
    }
    if (count == 11){
        count = 12;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600104FF0200")); //Запрос даты выпуска счетчика
        tmr_tout->start(3000);
        return;
    }
    if (count == 13){
        count = 14;
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000010000FF0200")); //Запрос системного времени счётчика
        tmr_tout->start(3000);
        return;
    }
}
