#ifndef WIDGET_CONNECT_H
#define WIDGET_CONNECT_H

#include <QWidget>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QSerialPort>
#include "NBFi_settings.h"

#include <QFile>
#include <QTextStream>
#include <QString>

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
    SWITCH_CONNECT_usb_dongle,
    SWITCH_CONNECT_TCP_HDLC,
} SWITCH_CONNECT;

class widget_connect : public QWidget
{
    Q_OBJECT
    QTimer *tmr_tout;

public:
    explicit widget_connect(QWidget *parent = 0);
    ~widget_connect();
    void start_write_pass();

protected:
    QUdpSocket *udp;
    QTcpSocket *tcp;

    QSerialPort *serial;
    QHostAddress udp_senderAddress;
    int udp_senderPort;
    QString com_port;
    QString serv_pass = "phobos3";
    QString serv_pass2 = "3sobohp";
    SWITCH_CONNECT sconnect;
    QByteArray data_from_channel;
    nbfi_settings_t *nbfi;
    uint32_t server_addr();
    bool is_connected;
    bool transmit = false;
    quint16     m_nNextBlockSize;
    QByteArray tx_rx(uint cmd, QByteArray arr_send);
    bool nbfi_read();
    bool nbfi_write();
    bool nbfi_set_FastDL(uint freq = 447000000);
    void update_com_ports();
    void update_button();
    int m_msgSize;
    bool contains_enough_data;
    bool m_headerRead;
    QByteArray firstSendTcpData;
    QByteArray nextSendTcpData;
    int nextSendTcpDataSize;
    QByteArray IntToArray(qint32 source);
    bool connect_ok = false;
private:
    Ui::widget_connect *ui;
signals:
    void signal_form_log_close();
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
    void signal_start_pulse();
    void tabb_ReadData();
    void signal_tab_hide();
    void signal_disable_tab_kn(bool, int);
    void signal_min_max_window(bool);
    void signal_enable_tab_kn();
    void signal_log(QString);
protected slots:
    void slot_udp_readyRead();

    void slot_serial_readyRead();
    void slot_update_switch_connect();
    void timeout();
public slots:
    void slot_HDLC_to_device(QByteArray data);
    void slot_disconnect();
    void on_pushButton_connect_clicked(bool checked);
    void slot_write_pass(QByteArray pass, bool);
    void on_pushButton_ReadData_clicked();
    void slot_pushButton_ReadData_show();
    void slot_view_log_hide_show(bool);
    void slot_disable_tab_kn(bool, int);
    void slot_tcp_readyRead();
private slots:
    void on_comboBox_client_addr_currentIndexChanged(int index);
    void on_spinBox_modem_dec_valueChanged(int arg1);
    void on_spinBox_modem_hex_valueChanged(int arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void slotError(QAbstractSocket::SocketError);
//    void slotSendToServer();
    void slotConnected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // WIDGET_CONNECT_H
