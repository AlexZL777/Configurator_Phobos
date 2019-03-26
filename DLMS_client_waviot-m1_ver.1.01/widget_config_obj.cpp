#include "widget_config_obj.h"
#include "ui_widget_config_obj.h"
#include "DLMS_obis_pack.h"

#include "Logger/Logger.h"

widget_config_obj::widget_config_obj(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget_config_obj)
{
    ui->setupUi(this);
}

widget_config_obj::~widget_config_obj()
{
    delete ui;
}

void widget_config_obj::slot_read_data(QByteArray data)
{
    uint8_t buf_size = data.size();
    while (data.size() < 7) {
        data.append((char)0);
    }
    uint8_t * buf_start = (uint8_t *)data.data();
    uint8_t * buf = buf_start;
    if (buf_size < 8) {
        return;
    }

    if (*buf++ == 0xED) {
        OBIS obis;
        buf += ElectroGet_OBIS(buf, &obis);
        if (    obis.A == 1 &&
                obis.B == 0 &&
                obis.C == 0x60 &&
                obis.D == 0x03 &&
                obis.E == 0x0A &&
                obis.F == 255) {

            buf++;

            uint8_t rele_mode = *buf++;
            uint8_t rele_state = *buf++;
            uint8_t rele_status = *buf++;
            ui->spinBox_rele_mode->setValue(rele_mode);
            ui->spinBox_rele_state->setValue(rele_state);
            ui->spinBox_rele_status->setValue(rele_status);
        }
    }
}

void widget_config_obj::on_pushButton_rele_read_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED0000000000000000000000000000000000000000000000");
    uint8_t * buf = (uint8_t *)arr.data() + 1;
    OBIS obis;
    obis.A = 1;
    obis.B = 0;
    obis.C = 0x60;
    obis.D = 0x03;
    obis.E = 0x0A;
    obis.F = 255;
    buf += ElectroAdd_OBIS(buf, &obis);
    *buf++ = 2;
    emit signal_write_data(arr.mid(0, buf - (uint8_t *)arr.data()));
}

void widget_config_obj::on_pushButton_rele_write_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED60030A0000000000000000000000000000000000000000000000");
    uint8_t * buf = (uint8_t *)arr.data();
    buf += 4;
    *buf++ = ui->spinBox_rele_mode->value();
    *buf++ = ui->spinBox_rele_state->value();
    arr = arr.mid(0, buf - (uint8_t *)arr.data());
    emit signal_write_data(arr);
}
