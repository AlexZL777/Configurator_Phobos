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
    connect(tmr_tout_pulse, SIGNAL(timeout()), this, SLOT(timeout()));
}

widget_pulse_outputs::~widget_pulse_outputs()
{
    delete ui;
}

bool widget_pulse_outputs::transmitt(){
    return transmit;
}

void widget_pulse_outputs::timeout(){
    log_1 << "ppppppp" << count_tout;
    transmit = true;
    emit signal_write_data_(QByteArray::fromHex("EF17"));
    if (count_tout++ < 3) tmr_tout_pulse->start(3000);
    else if ( count_tout++ == 3 ) {
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
    emit signal_min_window();
    count_bar = 15;
    emit signal_bar(count_bar);
}

void widget_pulse_outputs::slot_hide_widget_pulse(){
    //ui->textBrowser->setText("");
    //ui->textBrowser_2->setText("");
    hide();
    emit signal_bar(0);
    emit signal_min_window();
}

void widget_pulse_outputs::slot_disconnect(){
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
}

void widget_pulse_outputs::slot_start_pulse(){
    transmit = true;
    emit signal_timeout_start(5000);
    emit signal_write_data_(QByteArray::fromHex("EF17"));
    count_tout = 0;
    tmr_tout_pulse->start(1000);
}

void widget_pulse_outputs::slot_read_data_(QByteArray data){
    if (transmit){
        tmr_tout_pulse->stop();
        transmit = false;
      //  log_1 << "read data" << data.toHex().toUpper();
        uint8_t buf_size = data.size();
        uint8_t * buf_start = (uint8_t *)data.data();
        uint8_t * buf = buf_start;
     //   log_1 << "buf_size" << buf_size;
        if (buf_size < 1) {
            return;
        }
        QVariantMap vmap_packet;
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
                    log_1 << "count_bar" << count_bar;
                    count_bar += 85;
                    emit signal_bar(count_bar);
                    log_1 << "count_bar" << count_bar;
                    emit signal_disable_tab_kn(0, 1);
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
    emit signal_write_data_(arr);
    emit signal_timeout_start(3000);
}
