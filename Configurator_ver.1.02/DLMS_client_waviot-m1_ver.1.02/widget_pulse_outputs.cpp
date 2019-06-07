#include "widget_pulse_outputs.h"
#include "ui_widget_pulse_outputs.h"

#include <Logger/Logger.h>
#include <QJsonDocument>

#include "DLMS_obis_pack.h"
#include "DLMS_PDU.h"

#include <widget_info.h>

#include <QMessageBox>
#include <QLineEdit>

extern int count_bar;
bool pulse_write_bar;
extern int type_counter;
extern int ver_po[2];
extern uint32_t client_addr;

widget_pulse_outputs::widget_pulse_outputs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_pulse_outputs)
{
    ui->setupUi(this);
   // hide();
    ui->gridLayout->setAlignment( Qt::AlignLeft );
    ui->comboBox_ADE_Pulse0_Energy_type->addItem("Активная", 0);
    ui->comboBox_ADE_Pulse0_Energy_type->addItem("Реактивная", 1);
  //  ui->comboBox_ADE_Pulse0_Energy_type->addItem("Активка В", 4);
  //  ui->comboBox_ADE_Pulse0_Energy_type->addItem("Реактивка В", 5);
  //  ui->comboBox_ADE_Pulse0_Energy_type->addItem("Часы", 0x81);
    ui->comboBox_ADE_Pulse1_Energy_type->addItem("Активная", 0);
    ui->comboBox_ADE_Pulse1_Energy_type->addItem("Реактивная", 1);
 //   ui->comboBox_ADE_Pulse1_Energy_type->addItem("Активка В", 4);
 //   ui->comboBox_ADE_Pulse1_Energy_type->addItem("Реактивка В", 5);
    ui->comboBox_ADE_Pulse1_Energy_type->addItem("Часы", 0x81);

    tmr_tout_pulse = new QTimer();
    tmr_t = new QTimer();
    connect(tmr_tout_pulse, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(tmr_t, SIGNAL(timeout()), this, SLOT(tmr_time()));
    connect( ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
}

widget_pulse_outputs::~widget_pulse_outputs()
{
    delete ui;
}

void widget_pulse_outputs::setValue(int val){
    if ( ver_po[0] > 4 ){
        ui->horizontalSlider->setValue(val);
        count_bar = 0;
        emit signal_bar(count_bar);
        QByteArray arr;
        transmit = true;
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider->setTracking(false);
        ui->pushButton->setEnabled(false);
        ant = true;
        emit signal_disable_tab_kn(1, 1);
        if (val == 0){
            emit signal_write_data(QByteArray::fromHex("EF44C5FF0000000000")); //Переключение на встроенную антенну счётчика
        }
        if (val == 1){
            emit signal_write_data(QByteArray::fromHex("EF44C5FF0101000000")); //Переключение на внешнюю антенну счётчика
        }
        tmr_tout_pulse->start(500);
    }
    else{
        ui->horizontalSlider->setTracking(false);
        ui->horizontalSlider->setEnabled(false);
    }
}

bool widget_pulse_outputs::transmitt(){
    return transmit;
}

void widget_pulse_outputs::timeout(){
    log_1 << "count_tout" << count_tout;
    if (count_tout < 3){
        count_tout++;
        transmit = true;
        if (ant) {
            emit signal_write_data_(QByteArray::fromHex("EF4405FFFFFF000000")); //Запрос: подключена внутр. или внеш. антенна счётчика
            count_tout = 0;
        }
        else if (bn_click){
            QByteArray arr = QByteArray::fromHex("EF17000000000000000000000000000000000000000000000000");
            uint8_t * buf = (uint8_t *)arr.data();
            buf += 2;
            uint32_t Pulse0_energy_type = ui->comboBox_ADE_Pulse0_Energy_type->currentData().toUInt();
            uint32_t Pulse1_energy_type = ui->comboBox_ADE_Pulse1_Energy_type->currentData().toUInt();
            QString s = ui->textEdit->toPlainText();
            uint32_t Pulse0_freq = s.toInt();
            s = ui->textEdit_2->toPlainText();
            uint32_t Pulse1_freq = s.toInt();
            *buf++ = Pulse0_energy_type;
            *buf++ = Pulse1_energy_type;
            *buf++ = (Pulse0_freq >> 0) & 0xFF;
            *buf++ = (Pulse0_freq >> 8) & 0xFF;
            *buf++ = (Pulse1_freq >> 0) & 0xFF;
            *buf++ = (Pulse1_freq >> 8) & 0xFF;
            arr = arr.mid(0, buf - (uint8_t *)arr.data());
            emit signal_write_data_(arr);
        }
        else emit signal_write_data_(QByteArray::fromHex("EF17"));
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider->setTracking(false);
        ui->pushButton->setEnabled(false);
        tmr_tout_pulse->start(3000);
    }
    else if ( count_tout == 3 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout_pulse->start(3000);
    }
    else {
        transmit = false;
        tmr_tout_pulse->stop();
        emit signal_timeout_start (100);
        emit signal_disable_tab_kn(0, 1);
    }
}

void widget_pulse_outputs::slot_show_widget_pulse(){
  //  show();
    transmit = false;
  //  emit signal_min_window();
    count_bar = 15;
    emit signal_bar(count_bar);
    if (ver_po[0] < 5 && client_addr != 0x30 ){
        ui->horizontalSlider->setTracking(false);
        ui->horizontalSlider->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_14->setEnabled(false);
    }
    else {
        ui->label_10->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->label_14->setEnabled(true);
    }
}

void widget_pulse_outputs::slot_hide_widget_pulse(){
    //ui->textBrowser->setText("");
    //ui->textBrowser_2->setText("");
    hide();
    emit signal_bar(0);
    emit signal_min_window();
}

void widget_pulse_outputs::slot_disconnect(){
    tmr_t->stop();
    tmr_tout_pulse->stop();
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
}

void widget_pulse_outputs::slot_start_pulse(){
    transmit = true;
    emit signal_write_data_(QByteArray::fromHex("EF17"));
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setTracking(false);
    ui->pushButton->setEnabled(false);
    count_tout = 0;
    tmr_tout_pulse->start(3000);
}

void widget_pulse_outputs::slot_read_data_(QByteArray data){
    if (transmit){
        tmr_tout_pulse->stop();
        transmit = false;
        log_1 << "read data" << data.toHex().toUpper();
        uint8_t buf_size = data.size();
        uint8_t * buf_start = (uint8_t *)data.data();
        uint8_t * buf = buf_start;
     //   log_1 << "buf_size" << buf_size;
        if (buf_size < 1) {
            return;
        }
        uint8_t header = *buf++;
        if (header == 0xEF) {
            log_1 << "header";
            uint8_t sub_header = *buf++;
            switch (sub_header) {
                case 0x17: {
                    log_1 << "sub_header";
                    if (data.size() < 8) break;
                    uint32_t Pulse0_energy_type = *buf++;
                    uint32_t Pulse1_energy_type = *buf++;
                    uint32_t Pulse0_freq  = *buf++;
                    Pulse0_freq += (*buf++) << 8;
                    uint32_t Pulse1_freq  = *buf++;
                    Pulse1_freq += (*buf++) << 8;
                    ui->comboBox_ADE_Pulse0_Energy_type->setCurrentIndex(ui->comboBox_ADE_Pulse0_Energy_type->findData(Pulse0_energy_type));
                    ui->comboBox_ADE_Pulse1_Energy_type->setCurrentIndex(ui->comboBox_ADE_Pulse1_Energy_type->findData(Pulse1_energy_type));
                    QString str;
                    str = str.setNum(Pulse0_freq);
                    ui->textEdit->setText(str);
                    str = str.setNum(Pulse1_freq);
                    ui->textEdit_2->setText(str);
               //     log_1 << "count_bar" << count_bar;
                    count_bar += 50;
                    emit signal_bar(count_bar);
                    log_1 << "bn_click" << bn_click;
                    if (bn_click){
                        bn_click = false;
                        emit signal_disable_tab_kn(0, 1);
                        ui->horizontalSlider->setEnabled(true);
                        ui->horizontalSlider->setTracking(true);
                        ui->pushButton->setEnabled(true);
                        count_bar = 100;
                        emit signal_bar(count_bar);
                    }
                    else {
                        transmit = true;
                        emit signal_write_data_(QByteArray::fromHex("EF4405FFFFFF000000")); //Запрос: подключенна внутр. или внеш. антенна счётчика
                        count_tout = 0;
                        tmr_tout_pulse->start(3000);
                    }
                    break;
                }
                case 0x44: {
                    *buf++; *buf++;
                    uint32_t state_ant;
                    state_ant = *buf++; state_ant <<= 8;
                    log_1 << "state_ant" << state_ant;
                    state_ant+= *buf++;
                    log_1 << "state_ant 2" << state_ant;
                    if ( state_ant == 0) ui->horizontalSlider->setValue(0); //Вывод состояния внеш/внутр антенны счетчика
                    else ui->horizontalSlider->setValue(1);
                    ui->pushButton->setEnabled(true);
                    if (client_addr == 0x30){
                        ui->horizontalSlider->setEnabled(true);
                        ui->horizontalSlider->setTracking(true);
                    }
                   // count = 17;
                    tmr_tout_pulse->stop();
                    tmr_t->stop();
                    ant = false;
                    emit signal_disable_tab_kn(0, 1);
                    count_bar = 100;
                    emit signal_bar(count_bar);
                    break;
                }
                default: break;
            }
        }
    }
}

void widget_pulse_outputs::on_pushButton_clicked(){
    emit signal_bar(0);
    QByteArray arr = QByteArray::fromHex("EF17000000000000000000000000000000000000000000000000");
    uint8_t * buf = (uint8_t *)arr.data();
    buf += 2;

    uint32_t Pulse0_energy_type = ui->comboBox_ADE_Pulse0_Energy_type->currentData().toUInt();
    uint32_t Pulse1_energy_type = ui->comboBox_ADE_Pulse1_Energy_type->currentData().toUInt();

    QString s = ui->textEdit->toPlainText();
    uint32_t Pulse0_freq = s.toInt();
    s = ui->textEdit_2->toPlainText();
    uint32_t Pulse1_freq = s.toInt();

    *buf++ = Pulse0_energy_type;
    *buf++ = Pulse1_energy_type;
    *buf++ = (Pulse0_freq >> 0) & 0xFF;
    *buf++ = (Pulse0_freq >> 8) & 0xFF;
    *buf++ = (Pulse1_freq >> 0) & 0xFF;
    *buf++ = (Pulse1_freq >> 8) & 0xFF;

    arr = arr.mid(0, buf - (uint8_t *)arr.data());

    pulse_write_bar = true;
    bn_click = true;
    transmit = true;
    emit signal_disable_tab_kn(1, 1);
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setTracking(false);
    ui->pushButton->setEnabled(false);
    emit signal_write_data_(arr);
    emit signal_timeout_start(3000);
}
