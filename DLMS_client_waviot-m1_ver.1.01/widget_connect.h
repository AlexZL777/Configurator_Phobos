#ifndef WIDGET_CONNECT_H
#define WIDGET_CONNECT_H

#include <QWidget>
#include <QUdpSocket>
#include <QSerialPort>
#include "NBFi_settings.h"

#include <QFile>
#include <QTextStream>

namespace Ui {
class widget_connect;
}

typedef enum {
    SWITCH_CONNECT_none,
    SWITCH_CONNECT_UDP_HDLC,
    SWITCH_CONNECT_radio_FASTDL,
    SWITCH_CONNECT_radio_FASTDL_HDLC,
    SWITCH_CONNECT_rs485,
    SWITCH_CONNECT_opto_HDLC,
    SWITCH_CONNECT_opto_MODE_E,
    SWITCH_CONNECT_radio_FASTDL_electro,
} SWITCH_CONNECT;

class widget_connect : public QWidget
{
    Q_OBJECT

public:
    explicit widget_connect(QWidget *parent = 0);
    ~widget_connect();
    void start_write_pass();
protected:
    QUdpSocket *udp;
    QSerialPort *serial;
    QHostAddress udp_senderAddress;
    int udp_senderPort;
    QString com_port;
    SWITCH_CONNECT sconnect;
    QByteArray data_from_channel;
    nbfi_settings_t *nbfi;
    uint32_t server_addr();
    bool is_connected;

    QByteArray tx_rx(uint cmd, QByteArray arr_send);
    bool nbfi_read();
    bool nbfi_write();
    bool nbfi_set_FastDL(uint freq = 447000000);
    void update_com_ports();
    void update_button();
private:
    Ui::widget_connect *ui;
signals:
    void signal_connect(uint32_t server, uint32_t client, QByteArray pass);
    void signal_disconnect();
    void signal_HDLC_from_device(QByteArray data);
    void signal_read_data(QByteArray data);
    void signal_show_widget_info();
    void signal_hide_widget_info();
    void signal_show_widget_pulse();
    void signal_hide_widget_pulse();
    void signal_hide_point_power();
    void signal_timeout_start(int);
    void signal_hide_power_data();
    void signal_hide_power_data_1f();
protected slots:
    void slot_udp_readyRead();
    void slot_serial_readyRead();
    void slot_update_switch_connect();
public slots:
    void slot_HDLC_to_device(QByteArray data);
    void slot_disconnect();
    void on_pushButton_connect_clicked(bool checked);
    void slot_write_pass(QByteArray pass, bool);
private slots:
    void on_comboBox_client_addr_currentIndexChanged(int index);
    void on_spinBox_modem_dec_valueChanged(int arg1);
    void on_spinBox_modem_hex_valueChanged(int arg1);
};

#endif // WIDGET_CONNECT_H
