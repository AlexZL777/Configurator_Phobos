#include "widget_info.h"
#include "ui_widget_info.h"

#include <Logger/Logger.h>
#include <assert.h>
#include <QDate>
#include <QTime>
#include <QList>
#include <QChar>

int count_bar;
int type_counter;

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
    hide();
}

widget_info::~widget_info()
{
    delete ui;
}

void widget_info::slot_show_widget_info(){
    //ui-<setRowMinimumHeight();
    show();
    emit signal_min_window();
    count = 0;
    QByteArray arr = QByteArray::fromHex("C001C100010000600100FF0200");     //Запрос серийного номера счетчика
    count_bar = 0;
    emit signal_bar(count_bar);
    transmit = true;
    emit signal_write_data_PDU (arr);
}

void widget_info::slot_hide_widget_info(){
    ui->textBrowser->setText("");
    ui->textBrowser_2->setText("");
    ui->textBrowser_3->setText("");
    ui->textBrowser_4->setText("");
    ui->textBrowser_5->setText("");
    ui->textBrowser_6->setText("");
    ui->textBrowser_7->setText("");
    ui->textBrowser_8->setText("");
//    ui->textBrowser_9->setText("");
    ui->textBrowser_10->setText("");
    ui->textBrowser_11->setText("");
//    ui->textBrowser_12->setText("");
    hide();
    emit signal_bar(0);
    emit signal_min_window();
}

void widget_info::slot_view_data(QVariant(data))
{
    if (transmit){
        transmit = false;
        count_bar += 10;
        emit signal_bar(count_bar);
        QByteArray arr;
        int a;
        QVariantMap vm = data.toMap();
        if (vm.contains("long-unsigned")) a = vm["long-unsigned"].toInt();
        if (vm.contains("octet-string")) arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
        if (vm.contains("date-time")) arr = QByteArray::fromHex(vm.value("date-time", "").toString().toLocal8Bit());
        if (count == 0){
            ui->textBrowser->setText(arr.toUpper());       //Вывод серийного номера счетчика
            count = 1;
            widget_info::turn ();
            return;
        }
        if (count == 2){
            type_counter = arr.at(0);
            if (type_counter == 51){
                emit signal_show_point_power();
                emit signal_show_widget_power_data();
            }
            else if (type_counter == 49){
                emit signal_show_widget_power_data_1f();
            }
            ui->textBrowser_2->setText(arr.toUpper());     //Вывод типа счетчика
            count = 3;
            widget_info::turn ();
            return;
        }
        if (count == 4){
            ui->textBrowser_3->setText(arr.toUpper());     //Вывод версии метрологического ПО
            count = 5;
            widget_info::turn ();
            return;
        }
        if (count == 6){
            ui->textBrowser_4->setText(arr.toUpper());     //Вывод версии коммуникационного ПО
            count = 7;
            widget_info::turn ();
            return;
        }
        if (count == 8){
            QString s = QString::number(a);
            ui->textBrowser_5->setText(s);     //Вывод коэффициента трансформации по току
            count = 9;
            widget_info::turn ();
            return;
        }
        if (count == 10){
            QString s = QString::number(a);
            ui->textBrowser_6->setText(s);     //Вывод коэффициента трансформации по напряжению
            count = 11;
            widget_info::turn ();
            return;
        }
        if (count == 12){
            QString s = QString::number(a);
            ui->textBrowser_7->setText(s);     //Вывод даты выпуска счетчика
            count = 13;
            widget_info::turn ();
            return;
        }
        if (count == 14){
            COSEM_date_time_struct *cdt = (COSEM_date_time_struct *)arr.data();
            uint16_t y = (cdt->year_highbyte << 8) + cdt->year_lowbyte;
            QDateTime qdt(QDate(y, cdt->month, cdt->day_of_month),QTime(cdt->hour,cdt->minute,cdt->second));
            ui->textBrowser_8->setText(qdt.toString("dd.MM.yyyy"));          //Вывод системной даты счётчика
            ui->textBrowser_10->setText(qdt.toString("HH.mm.ss"));           //Вывод системного времени счётчика
            dev = arr.at(10);
            str_dev = str_dev.setNum((arr.at(9) << 8) + dev);
            ui->textBrowser_11->setText(str_dev);                            //Вывод значения девиации счётчика
    /*        str_status = str_status.setNum(arr.at(11));
            ui->textBrowser_12->setText(str_status);  */                            //Вывод системного времени счётчика
            count = 15;
          //  widget_info::turn ();
            emit signal_start_pulse();
            return;
        }
    }
}

void widget_info::view_data_first()
{
    count = 0;
    QByteArray arr = QByteArray::fromHex("C001C100010000600100FF0200");     //Запрос серийного номера счетчика
    transmit = true;
    emit signal_write_data_PDU (arr);
}

void widget_info::turn (){
    if (count == 1){
        QByteArray arr = QByteArray::fromHex("C001C100010000600101FF0200"); //Запрос типа счетчика
        count = 2;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
    if (count == 3){
        QByteArray arr = QByteArray::fromHex("C001C100010000600102FF0200"); //Запрос версии метрологического ПО
        count = 4;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
    if (count == 5){
        QByteArray arr = QByteArray::fromHex("C001C100010000600103FF0200"); //Запрос версии коммуникационного ПО
        count = 6;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
    if (count == 7){
        QByteArray arr = QByteArray::fromHex("C001C100010100000402FF0200"); //Запрос коэффициента трансформации по току
        count = 8;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
    if (count == 9){
        QByteArray arr = QByteArray::fromHex("C001C100010100000403FF0200"); //Запрос коэффициента трансформации по напряжению
        count = 10;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
    if (count == 11){
        QByteArray arr = QByteArray::fromHex("C001C100010000600104FF0200"); //Запрос даты выпуска счетчика
        count = 12;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
    if (count == 13){
        QByteArray arr = QByteArray::fromHex("C001C100010000010000FF0200"); //Запрос системного времени счётчика
        count = 14;
        transmit = true;
        emit signal_write_data_PDU (arr);
        return;
    }
}
