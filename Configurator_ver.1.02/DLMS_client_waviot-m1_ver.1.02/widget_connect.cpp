#include "widget_connect.h"
#include "ui_widget_connect.h"

#include <QNetworkDatagram>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <Logger/Logger.h>
#include "DLMS_CRC.h"

#include <QFile>
#include <QTextStream>
#include <QPushButton>

uint32_t client_addr;
int bn_fl = 0;

#define FORMAT_TYPE_HDLC (0xA)
#define FORMAT_TYPE_ELECTRO5 (0xC)

enum {SLIP_MODE_START = 0, SLIP_MODE_RECEIVING_PAYLOAD, SLIP_MODE_RECEIVING_CMD, SLIP_MODE_ESC};

typedef struct {
    quint8 cmd;
    quint8 mode;
    QByteArray data;

    uint8_t mode_frame;
    uint8_t frame_length;
    uint8_t frame_byte_counter;
    uint8_t format_type;
    uint16_t crc;
    uint16_t FCS;
} type_slip_buf;

widget_connect::widget_connect(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget_connect)
{
    ui->setupUi(this);

    is_connected = false;
    nbfi = new nbfi_settings_t;

    udp = new QUdpSocket(this);
    connect(udp, QUdpSocket::readyRead, this, widget_connect::slot_udp_readyRead);
    serial = new QSerialPort(this);
    connect(serial, QSerialPort::readyRead, this, widget_connect::slot_serial_readyRead);

    ui->comboBox_client_addr->clear();
//    ui->comboBox_client_addr->addItem("Отсутствие аутентификации", 0x10);
    ui->comboBox_client_addr->addItem("Низкий уровень безопасности", 0x20);
    ui->comboBox_client_addr->addItem("Высокий уровень безопасности", 0x30);
    ui->comboBox_client_addr->setCurrentIndex(1);

    on_spinBox_modem_dec_valueChanged(ui->spinBox_modem_dec->value());

    connect(ui->radioButton_udp_hdlc, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));
    connect(ui->radioButton_rs_fastdl, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));
    connect(ui->radioButton_rs_fastdl_hdlc, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));
    connect(ui->radioButton_rs_485, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));
    connect(ui->radioButton_opto_hdlc, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));
    connect(ui->radioButton_opto_mode_e, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));
    connect(ui->radioButton_rs_fastdl_electro, SIGNAL(toggled(bool)), this, SLOT(slot_update_switch_connect()));

    ui->radioButton_udp_hdlc->hide();
    ui->radioButton_rs_fastdl->hide();
    ui->radioButton_rs_fastdl_hdlc->hide();
    ui->radioButton_opto_mode_e->hide();
    ui->radioButton_rs_485->hide();
    ui->radioButton_opto_hdlc->hide();
    ui->radioButton_rs_fastdl_electro->hide();
    ui->radioButton_rs_485->setChecked(true);

    ui->pushButton_ReadData->hide();
    ui->pushButton_2->hide();

//    ui->comboBox_client_addr->hide();
//    ui->label->hide();
//    ui->label_2->hide();
//    ui->label_3->hide();
//    ui->label_4->hide();
//    ui->label_pass->hide();
//    ui->lineEdit_pass->hide();
//    ui->comboBox_client_addr->hide();
//    ui->spinBox_server_addr_logical->hide();
//    ui->spinBox_server_addr_physical->hide();

    slot_update_switch_connect();
}

widget_connect::~widget_connect()
{
    delete ui;
}

void widget_connect::slot_pushButton_ReadData_show(){
    ui->pushButton_ReadData->show();
}

void widget_connect::start_write_pass(){
    QFile file("file.txt");
    QStringList strList;
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {file.close();}
    if ((file.exists()) && (file.open(QIODevice::WriteOnly))){
        int n = strList.size();
        QString s;
        s = s.setNum(n);
     //   log_1 << "N strok" << n;
    }
}

void widget_connect::slot_write_pass(QByteArray pass, bool err){
    QFile file("file.txt");
    QStringList strList;
    if ((file.exists()) && (file.open(QIODevice::ReadOnly))){
        while(!file.atEnd()){
            strList << file.readLine();
        }
        file.close();
    }

    client_addr = ui->comboBox_client_addr->currentData().toUInt();
    switch (client_addr) {
        case 0x10: break;
        case 0x20: {
            if ((file.exists()) && (file.open(QIODevice::WriteOnly))){
                int n = strList.size();
                n = strList.size();
                QString s1;
            //    log_1 << "s0.setNum(n);" << s1.setNum(n);
                if (n == 0){
             //       log_1 << "stroka0000000";
                    if (err) {strList.insert(0, pass);}
                    QTextStream stream(&file);
                    foreach(QString s, strList){
                        stream << s << "\r\n";
                    }
                }
                else if (n >= 1){
             //       log_1 << "stroka1111111";
                    if (err) {strList[0] = pass+"\r\n";}
                    else {strList[0] = "\r\n";}
                    QTextStream stream(&file);
                    foreach(QString s, strList){
                        stream << s;
                    }
                }
                file.close();
            }
            break;
        }
        case 0x30: {
            if ((file.exists()) && (file.open(QIODevice::WriteOnly))){
                int n = strList.size();
                n = strList.size();
                QString s1;
           //     log_1 << "s1.setNum(n);" << s1.setNum(n);
                if (n == 0){
           //         log_1 << "stroka22222222";
                    if (err) {
                        strList.insert(0, "\n");
                        strList.insert(1, pass);
                        QTextStream stream(&file);
                        foreach(QString s, strList){
                            stream << s;
                        }
                        n = strList.size();
                        QString s1;
            //            log_1 << "s2.setNum(n);" << s1.setNum(n);
                    }
                }
                else if (n == 1){
           //         log_1 << "stroka33333333";
                    if (err) {strList.insert(1, pass);}
                   // else {strList[1] = "";}
                    QTextStream stream(&file);
                    foreach(QString s, strList){
                        stream << s;
                    }
                }
                else if (n >= 2){
           //         log_1 << "stroka444444";
                    if (err) {strList[1] = pass;}
                    else {strList[1] = "";}
                    QTextStream stream(&file);
                    foreach(QString s, strList){
                        stream << s;
                    }
                }
                file.close();
            }
            else {

            }
            break;
        }
        default: break;
    }



  /*  if ((file.exists()) && (file.open(QIODevice::WriteOnly))){
        strList.insert(1,"333333333\n");
        QTextStream stream(&file);
        foreach(QString s, strList){
            stream << s;
        }
        file.close();
    }*/
}

uint32_t widget_connect::server_addr()
{
    if (!ui->spinBox_server_addr_logical->value())
        return ui->spinBox_server_addr_physical->value();
    return (ui->spinBox_server_addr_logical->value() << 14) + ui->spinBox_server_addr_physical->value();
}

static quint8 CRC8byte(quint8 data)
{
   quint8 crc = 0;
   if(data & 1)     crc ^= 0x5e;
   if(data & 2)     crc ^= 0xbc;
   if(data & 4)     crc ^= 0x61;
   if(data & 8)     crc ^= 0xc2;
   if(data & 0x10)  crc ^= 0x9d;
   if(data & 0x20)  crc ^= 0x23;
   if(data & 0x40)  crc ^= 0x46;
   if(data & 0x80)  crc ^= 0x8c;
   return crc;
}

quint8 CRC8(quint8 * data, quint8 len)
{
    quint8 crc = 0;
    for (quint8 i = 0; i < len; i++) {
        crc = CRC8byte(data[i] ^ crc);
    }
    return crc;
}

#define SLIP_START  0xDD
#define SLIP_END    0xDE
#define SLIP_ESC    0xDF

#define SLIP_CMD    0x32

QByteArray CMD_to_SLIP(quint8 cmd, quint8 *payload, quint8 len)
{
    QByteArray ba;
    ba.append(SLIP_START);
    ba.append(cmd);
    for(int i=0; i<=len; i++) {
        quint8 c;
        if (i == len) {
            c = CRC8(payload, len);
        } else c = payload[i];

        if ((c==SLIP_START) || (c==SLIP_END) || (c==SLIP_ESC)) {
            ba.append(SLIP_ESC);
            ba.append(c ^ 0xFF);
        } else ba.append(c);
    }
    ba.append(SLIP_END);

    return ba;
}
QByteArray SLIP_Receive(void *vsbuf, QByteArray read)
{
    type_slip_buf * sbuf = (type_slip_buf *)vsbuf;
    quint8 c;

    for(quint16 j = 0; j < read.size(); j++) {
        c = read[j];
        switch (sbuf->mode) {
        case  SLIP_MODE_START:
            if (c == SLIP_START) {
                sbuf->data.clear();
                sbuf->mode = SLIP_MODE_RECEIVING_CMD;
            }
            break;
        case SLIP_MODE_RECEIVING_PAYLOAD:
        case SLIP_MODE_RECEIVING_CMD:
            if(c == SLIP_ESC) {
                sbuf->mode = SLIP_MODE_ESC;
                break;
            }
            if(c == SLIP_START) {
                sbuf->data.clear();
                sbuf->mode = SLIP_MODE_RECEIVING_CMD;
                break;
            }
            if(c == SLIP_END) {
                sbuf->mode = SLIP_MODE_START;
                if (CRC8((uint8_t*)sbuf->data.data(), sbuf->data.size() - 1) != (quint8)sbuf->data.at(sbuf->data.size() - 1)) {
           //         log_1 << "error slip crc" << CRC8((uint8_t*)sbuf->data.data(), sbuf->data.size() - 1) << (quint8)sbuf->data.at(sbuf->data.size() - 1);
                    continue;
                }
                return sbuf->data.mid(0, sbuf->data.size() - 1);
            }
            if(sbuf->mode == SLIP_MODE_RECEIVING_CMD) {
                sbuf->cmd = c;
                sbuf->mode = SLIP_MODE_RECEIVING_PAYLOAD;
                break;
            }
            if(sbuf->mode == SLIP_MODE_RECEIVING_PAYLOAD) {
                sbuf->data.append(c);
                break;
            }
            break;
        case SLIP_MODE_ESC:
            sbuf->data.append(c ^ 0xFF);
            sbuf->mode = SLIP_MODE_RECEIVING_PAYLOAD;
            break;
        default:
            sbuf->mode = SLIP_MODE_START;
            break;
        }
    }
    return QByteArray();
}

QByteArray ELECTRO5_to_HDLC(QByteArray data)
{
    QByteArray ba;
    uint16_t crc = 0xFFFF;
    uint16_t frame_length = data.size() + 2 + 2;

    auto HDLC_TX_add_byte = [&] (uint8_t c) {
        crc = DLMS_crc_byte(crc, c);
        ba.append((char)c);
        log_1 << QByteArray(1,(char)c).toHex().toUpper() << crc << (crc ^ 0xFFFF);
    };

    ba.append(0x7E);
    HDLC_TX_add_byte((FORMAT_TYPE_ELECTRO5 << 4) + ((frame_length >> 8) & 0x7));
    HDLC_TX_add_byte(frame_length & 0xFF);
    for (int i = 0; i < data.size(); ++i) {
        HDLC_TX_add_byte(data.at(i));
    }
    crc = crc ^ 0xFFFF;
    ba.append((crc >> 0) & 0xFF);
    ba.append((crc >> 8) & 0xFF);
    ba.append(0x7E);
    return ba;
}
void ELECTRO5_Clear(void *vsbuf)
{
    type_slip_buf * hdlc = (type_slip_buf *)vsbuf;

    hdlc->data.clear();
//    if (!hdlc->segmentation) {
//        hdlc->data_len = 0;
//        hdlc->data_index = 0;
//    }
    hdlc->mode_frame = 0;
//    hdlc->LLC_flag = 0;
    hdlc->crc = 0xFFFF;
    hdlc->frame_byte_counter = 0;
    hdlc->format_type = 0;
//    hdlc->segmentation = 0;
    hdlc->frame_length = 0;
//    hdlc->serv.addr = 0;
//    hdlc->clnt.addr = 0;
//    hdlc->control.control = 0;
//    hdlc->HCS = 0;
    hdlc->FCS = 0;
}
QByteArray HDLC_to_ELECTRO5(void *vsbuf, QByteArray read)
{
    type_slip_buf * hdlc = (type_slip_buf *)vsbuf;
    quint8 c;

    for(quint16 j = 0; j < read.size(); j++) {
        c = read[j];

        if (!hdlc->mode_frame) {
            if (c == 0x7E) {
                hdlc->mode_frame++;
                hdlc->crc = 0xFFFF;
            }
            continue;
        }
        hdlc->frame_byte_counter++;
//        log_1 << QByteArray(1,(char)c).toHex().toUpper() << hdlc->mode_frame << hdlc->frame_length << hdlc->frame_byte_counter
//              << (hdlc->frame_byte_counter >= hdlc->frame_length) << hdlc->crc << (hdlc->crc ^ 0xFFFF);;
        if ((c == 0x7E) && (hdlc->mode_frame > 2) && (hdlc->frame_byte_counter > hdlc->frame_length)) { // end packet
            hdlc->crc ^= 0xFFFF;
//            log_1 << hdlc->mode_frame << (hdlc->HCS == hdlc->calc_HCS) << (hdlc->crc == hdlc->FCS) << (hdlc->control.control || hdlc->data_len);
//            log_1 << hdlc->crc << hdlc->FCS << (hdlc->crc == hdlc->FCS) << hdlc->data.size();
            if ((hdlc->crc == hdlc->FCS) && hdlc->data.size() > 2) {
                //log_1 << "pdu";// << (hdlc->HCS == hdlc->calc_HCS) << (hdlc->crc == hdlc->FCS) << (hdlc->control.control || hdlc->data_len);
//                HDLC_MAC_parser_controller(hdlc);
                QByteArray data = hdlc->data.remove(hdlc->data.size() - 2, 2);
//                log_1 << data.toHex().toUpper();
                ELECTRO5_Clear(hdlc);
                return data;
            }
    //        if (cb && (hdlc->HCS == hdlc->calc_HCS) && (hdlc->crc == hdlc->FCS) && (hdlc->control.control || hdlc->data_len)) {
    //            cb(hdlc, DLMS_pdu);
    //        }
            ELECTRO5_Clear(hdlc);
            continue;
        }
//        log_1 << (hdlc->mode_frame <= 2) << (hdlc->frame_byte_counter <= hdlc->frame_length - 2);
//        log_1 << ((hdlc->frame_length - hdlc->frame_byte_counter) >= 2);
        if (hdlc->mode_frame <= 2 || (hdlc->frame_byte_counter <= hdlc->frame_length - 2)) {
//            log_1 << hdlc->crc;
            hdlc->crc = DLMS_crc_byte(hdlc->crc, c);
        }
        // flag | frame format | dest.addr | src.addr | control | HSC | information | FCS | flag
        switch (hdlc->mode_frame) {
        case 1: {   // Frame format 1byte
            if (c == 0x7E) {
                hdlc->frame_byte_counter--;
                hdlc->crc = 0xFFFF;
                break;
            }
            hdlc->format_type = c >> 4;
            if (hdlc->format_type != FORMAT_TYPE_ELECTRO5) {
                ELECTRO5_Clear(hdlc);
            }
//            hdlc->segmentation = (c >> 3) & 0x1;
            hdlc->frame_length = (c & 0x7) << 8;
            hdlc->mode_frame++;
            break;
        }
        case 2: {   // Frame format 2byte
            hdlc->frame_length += c;
            if (hdlc->format_type == FORMAT_TYPE_HDLC) {
                hdlc->mode_frame++;
            } else {
                hdlc->mode_frame = 7;
            }
            break;
        }
        case 3: {   // Dest.address
//            hdlc->serv.bytes4.flag++;
//            if (c & 0x1) {
//                hdlc->mode_frame++;
//            }
//            hdlc->serv.bytes4.addr <<= 7;
//            hdlc->serv.bytes4.addr += c >> 0x1;
//            if (hdlc->serv.bytes4.flag > 4) {
//                HDLC_Clear(hdlc);
//                break;
//            }
            break;
        }
        case 4: {   // Src. address
//            hdlc->clnt.bytes4.flag++;
//            if (c & 0x1) {
//                hdlc->mode_frame++;
//            }
//            hdlc->clnt.bytes4.addr <<= 7;
//            hdlc->clnt.bytes4.addr += c >> 0x1;
//    //        if (hdlc->serv.bytes4.flag <= 1) { // fix spodes
//    //            HDLC_Clear(hdlc);
//    //            break;
//    //        }
//            if (hdlc->clnt.bytes4.flag > 4) {
//                HDLC_Clear(hdlc);
//            }
            break;
        }
        case 5: {   // Control
//            hdlc->control.control = c;
//            hdlc->calc_HCS = hdlc->crc ^ 0xFFFF;
//            hdlc->mode_frame++;
            break;
        }
        case 6: {   // HFS
//            if (hdlc->frame_length - hdlc->frame_byte_counter < 2) {
//                hdlc->FCS >>= 8;
//                hdlc->FCS += (c << 8);
//                hdlc->HCS = hdlc->FCS;
//                break;
//            }
//            hdlc->HCS >>= 8;
//            hdlc->HCS += (c << 8);
//            if (hdlc->frame_byte_counter == 2 + hdlc->serv.bytes4.flag + hdlc->clnt.bytes4.flag + 1 + 2) {
//                hdlc->mode_frame++;
//            }
            break;
        }
        case 7: {   // data
//            log_1 << (hdlc->frame_length - hdlc->frame_byte_counter < 2);
//            if (hdlc->frame_length - hdlc->frame_byte_counter < 2) {
                hdlc->FCS >>= 8;
                hdlc->FCS += (c << 8);
//                break;
//            }
//            if (!hdlc->control.bits.is_n_I && !hdlc->data_len) {
//                if ((c == 0xE6 && hdlc->LLC_flag == 0) ||
//                    (c == 0xE7 && hdlc->LLC_flag == 1) ||
//                    (c == 0x00 && hdlc->LLC_flag == 2)) {
//                    hdlc->LLC_flag++;
//                    break;
//                }
//            }
//            if (hdlc->data_len < DLMS_MaxServerPDUSize) {
//                hdlc->data_buf[hdlc->data_len++] = c;
//                hdlc->data_index = 0;
//            }
            hdlc->data.append(c);
            break;
        }
        default: break;
        }
    }
    return QByteArray();
}

QByteArray widget_connect::tx_rx(uint cmd, QByteArray arr_send)
{
    data_from_channel.clear();
    uint32_t read_timeout = 10000;
//    if (serial->baudRate() != 115200 && cmd == 0x32) {
//        cmd = 0x10;
//    }
    QEventLoop loop;
    QTimer::singleShot(read_timeout, &loop, SLOT(quit()));
    connect(this, SIGNAL(signal_read_data(QByteArray)), &loop, SLOT(quit()));

    arr_send = CMD_to_SLIP(cmd, (quint8 *)arr_send.data(), arr_send.size());
    serial->write(arr_send);

    loop.exec();
//    if (serial->baudRate() != 115200) {
//        rx_data.prepend(QByteArray::fromHex("00FF00001122"));
//    }
    return data_from_channel;
}

bool widget_connect::nbfi_read()
{
    QByteArray buf;
    buf = tx_rx(0x09, QByteArray());
    log_1 << buf.toHex().toUpper();
    if (buf.size() != 4) return false;

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_MODE));
    if (buf.size() <= 6) return false;
    if ((uint8_t)buf[1] != 0xff) nbfi->mode = (nbfi_mode_t)buf.at(1);
    if ((uint8_t)buf[2] != 0xff) nbfi->mack_mode = (nbfi_mack_mode_t)buf.at(2);
    if ((uint8_t)buf[3] != 0xff) nbfi->tx_phy_channel = (nbfi_phy_channel_t)buf.at(3);
    if ((uint8_t)buf[4] != 0xff) nbfi->rx_phy_channel = (nbfi_phy_channel_t)buf.at(4);
    if ((uint8_t)buf[5] != 0xff) nbfi->tx_pwr = buf[5];
    if ((uint8_t)buf[6] != 0xff) nbfi->num_of_retries = buf[6];

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_HANDSHAKE));
    if (buf.size() <= 2) return false;
    nbfi->handshake_mode = (nbfi_handshake_t)buf.data()[1];
    nbfi->mack_mode = (nbfi_mack_mode_t)buf.data()[2];

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_MAXLEN));
    if (buf.size() <= 1) return false;
    nbfi->max_payload_len = buf[1];

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_TXFREQ));
    if (buf.size() <= 4) return false;
    nbfi->tx_freq  = (((uint32_t)buf[4]) & 0xFF) << 0;
    nbfi->tx_freq += (((uint32_t)buf[3]) & 0xFF) << 8;
    nbfi->tx_freq += (((uint32_t)buf[2]) & 0xFF) << 16;
    nbfi->tx_freq += (((uint32_t)buf[1]) & 0xFF) << 24;

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_RXFREQ));
    if (buf.size() <= 4) return false;
    nbfi->rx_freq  = (((uint32_t)buf[4]) & 0xFF) << 0;
    nbfi->rx_freq += (((uint32_t)buf[3]) & 0xFF) << 8;
    nbfi->rx_freq += (((uint32_t)buf[2]) & 0xFF) << 16;
    nbfi->rx_freq += (((uint32_t)buf[1]) & 0xFF) << 24;

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_ANT));
    if (buf.size() <= 3) return false;
    if ((uint8_t)buf[1] != 0xff) nbfi->tx_pwr = buf[1];
    if ((uint8_t)buf[2] != 0xff) nbfi->tx_antenna = buf[2];
    if ((uint8_t)buf[3] != 0xff) nbfi->rx_antenna = buf[3];

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_DL_ADD));
    if (buf.size() <= 3) return false;
    for(uint8_t i = 0; i != 3; i++) ((uint8_t*)&nbfi->dl_ID)[i] = buf[1 + 2 - i];

    buf = tx_rx(0x40, QByteArray((int)1, NBFI_PARAM_HEART_BEAT));
    if (buf.size() <= 3) return false;
    nbfi->heartbeat_num = buf[1];
    nbfi->heartbeat_interval = buf[2];
    nbfi->heartbeat_interval <<= 8;
    nbfi->heartbeat_interval += buf[3];

    return true;
}
bool widget_connect::nbfi_write()
{
    { // NBFI_PARAM_MODE
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_MODE;
        buf[1] = (uint8_t)nbfi->mode & 0xFF;
        buf[2] = (uint8_t)nbfi->mack_mode & 0xFF;
        buf[3] = (uint8_t)nbfi->tx_phy_channel & 0xFF;
        buf[4] = (uint8_t)nbfi->rx_phy_channel & 0xFF;
        buf[5] = (uint8_t)nbfi->tx_pwr & 0xFF;
        buf[6] = (uint8_t)nbfi->num_of_retries & 0xFF;
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_HANDSHAKE
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_HANDSHAKE;
        buf[1] = (uint8_t)nbfi->handshake_mode & 0xFF;
        buf[2] = (uint8_t)nbfi->mack_mode & 0xFF;
        buf = tx_rx(0x40, buf);
       log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_MAXLEN
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_MAXLEN;
        buf[1] = (uint8_t)nbfi->max_payload_len & 0xFF;
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_TXFREQ
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_TXFREQ;
        buf[1] = (nbfi->tx_freq >> 24) & 0xFF;
        buf[2] = (nbfi->tx_freq >> 16) & 0xFF;
        buf[3] = (nbfi->tx_freq >>  8) & 0xFF;
        buf[4] = (nbfi->tx_freq >>  0) & 0xFF;
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_RXFREQ
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_RXFREQ;
        buf[1] = (nbfi->rx_freq >> 24) & 0xFF;
        buf[2] = (nbfi->rx_freq >> 16) & 0xFF;
        buf[3] = (nbfi->rx_freq >>  8) & 0xFF;
        buf[4] = (nbfi->rx_freq >>  0) & 0xFF;
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_ANT
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_ANT;
        buf[1] = nbfi->tx_pwr & 0xFF;
        buf[2] = nbfi->tx_antenna & 0xFF;
        buf[3] = nbfi->rx_antenna & 0xFF;
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_DL_ADD
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_DL_ADD;
        for(uint8_t i = 0; i != 3; i++)  buf[1 + 2 - i] = ((uint8_t*)&nbfi->dl_ID)[i];
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    { // NBFI_PARAM_HEART_BEAT
        QByteArray buf((int)8, (char)0);
        buf[0] = 0x40 | NBFI_PARAM_HEART_BEAT;
        buf[1] = nbfi->heartbeat_num;
        buf[2] = (nbfi->heartbeat_interval >> 8) & 0xFF;
        buf[3] = (nbfi->heartbeat_interval >> 0) & 0xFF;
        buf = tx_rx(0x40, buf);
        log_1 << buf.toHex().toUpper();
    }
    return true;
}
bool widget_connect::nbfi_set_FastDL(uint freq)
{
    if (serial->baudRate() != 115200) {
        return true;
    }
    nbfi_read();
    nbfi->tx_freq = freq;
    nbfi->rx_freq = freq;
    nbfi->max_payload_len = 128;
    nbfi->dl_ID = ui->spinBox_modem_dec->value(); //0xFF0000;
    nbfi->rx_phy_channel = DL_PSK_FASTDL;
    nbfi->tx_phy_channel = UL_PSK_FASTDL;
    nbfi->mode = TRANSPARENT;
    nbfi->handshake_mode = HANDSHAKE_NONE;
    return nbfi_write();
}

void widget_connect::slot_udp_readyRead()
{
    while (udp->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp->receiveDatagram();
//        udp_senderAddress = datagram.senderAddress();
//        udp_senderPort = datagram.senderPort();
//        QVariantMap vmap = QJsonDocument::fromJson(datagram.data()).toVariant().toMap();
//        QByteArray data = QByteArray::fromHex(vmap.value("data", "").toString().toLocal8Bit());
//        log_1 << qPrintable(datagram.data().toHex().toUpper());
        data_from_channel = datagram.data();
        emit signal_HDLC_from_device(datagram.data());
    }
}

void widget_connect::slot_serial_readyRead()
{
    static type_slip_buf slip_buf;
    if (!serial->isOpen()) return;
    QByteArray resp = serial->readAll();
    log_6 << "RX" << resp.toHex().toUpper();
//    log_1 << sconnect;
    switch (sconnect) {
    case SWITCH_CONNECT_radio_FASTDL:
    case SWITCH_CONNECT_radio_FASTDL_HDLC:
    case SWITCH_CONNECT_radio_FASTDL_electro: {
        resp = SLIP_Receive(&slip_buf, resp);
        if (resp.isEmpty()) return;
        if (slip_buf.cmd == SLIP_CMD && resp.size() == 1 && resp.at(0) == 0) {
            return;
        }
        if (resp.size() < 7 && slip_buf.cmd == SLIP_CMD) {
            log_1 << QString::number(slip_buf.cmd, 16);
            return;
        }
        if (slip_buf.cmd == SLIP_CMD && resp.size() == 7 && resp.at(6) == 0) {
            return;
        }
        if (slip_buf.cmd == 0x10 && resp.size() < 6) {
            data_from_channel.clear();
            break;
        }
        if (slip_buf.cmd == 0x10) {
            uint8_t * buf_in = (uint8_t *)resp.data();
//            QByteArray header = resp.left(6);
//            log_2 << "RX" << QString("%1").arg(resp.size(), 3) << resp.toHex().toUpper() << QByteArray::number(slip_buf.cmd, 16);
            uint32_t modem_id = 0;
            modem_id <<= 8; modem_id += buf_in[1];
            modem_id <<= 8; modem_id += buf_in[2];
            modem_id <<= 8; modem_id += buf_in[3];
            if (modem_id != nbfi->dl_ID) {
                break;
            }
//            log_2 << "RX" << QString("%1").arg(resp.size(), 3) << resp.toHex().toUpper() << QByteArray::number(slip_buf.cmd, 16);
//          57 71C5CA B9D5 4000005B23E255A078000369088E780000C350957800000000A97800000000977800000000AB7800000000818900000246818A00000000818B00000000818C00000000828800000248838800000002848800000001
            uint8_t flags = buf_in[4] & 0xE0;
            if (flags == 0xA0) { // group
                uint8_t lens = buf_in[5];
                if (!(lens & 0x80)) { // not multi packet
                    data_from_channel = resp.mid(8);
                    break;
                }
                data_from_channel = resp.mid(6);
            } else if (flags == 0x20) {
                data_from_channel += resp.mid(5);
            } else { // single
                data_from_channel = resp.mid(6);
            }
        }

//        5F 71C5C7 BE028E8D 4000005B1BEBF8A0780000032EB4780003633EC8780003653DDB78000000468E780000C363957800000000A97800000000BD7800000000977800000000AB7800000000BF7800000000010051070AFF0001270F0100510715FF00000000D17A000127558189000004C0818A00000000818B00000000818C000000008288
//        5F 71C5C7 3F00000000838800000002848800000021

        is_connected = true;
        update_button();
//        61 71C5C7 808E EF4002010210000A820001000000
//        data_from_channel += resp;
//        log_2 << "RX" << QString("%1").arg(resp.size(), 3) << resp.toHex().toUpper() << QByteArray::number(slip_buf.cmd, 16);
        log_1 << "RX" << QString("%1").arg(data_from_channel.size(), 3) << data_from_channel.toHex().toUpper() << QByteArray::number(slip_buf.cmd, 16);
        emit signal_read_data(data_from_channel);
        if (sconnect == SWITCH_CONNECT_radio_FASTDL_HDLC) {
            if (!resp.isEmpty() && ((uint8_t)resp.at(0) == 0xD3)) {
                data_from_channel = resp.mid(1);
                emit signal_HDLC_from_device(data_from_channel);
            }
        }
//        if (sconnect == SWITCH_CONNECT_radio_FASTDL_electro || sconnect == SWITCH_CONNECT_radio_FASTDL_HDLC) {
        if (data_from_channel.size() > 2 && ((uint8_t)data_from_channel.at(0) == 0xEF) && ((uint8_t)data_from_channel.at(1) == 0x40)) {
            slot_HDLC_to_device(QByteArray::fromHex("EF01"));
            slot_HDLC_to_device(QByteArray::fromHex("EF06"));
        }
//            if (resp.size() > 2 && ((uint8_t)resp.at(0) == 0x40)) {
//                slot_HDLC_to_device(QByteArray::fromHex("EF01"));
//            }
//            EF40010102000106820000000000
//        }
        break;
    }
//    case SWITCH_CONNECT_radio_FASTDL_HDLC: {
//        resp = SLIP_Receive(&slip_buf, resp);
//        if (resp.isEmpty()) return;
//        if (slip_buf.cmd == SLIP_CMD && resp.size() == 1 && resp.at(0) == 0) {
//            return;
//        }
//        log_2 << "RX" << QString("%1").arg(resp.size(), 3) << resp.toHex().toUpper() << QByteArray::number(slip_buf.cmd, 16);
//        if (resp.size() < 7 && slip_buf.cmd == SLIP_CMD) {
//            log_1 << QString::number(slip_buf.cmd, 16);
//            return;
//        }
//        if (slip_buf.cmd == SLIP_CMD && resp.size() == 7 && resp.at(6) == 0) {
//            return;
//        }
//        if (resp.size() < 6) {
//            data_from_channel.clear();
//            break;
//        }
//        //QByteArray header = resp.left(6);
//        if (resp.at(0) == 0x10) {
//            resp = resp.mid(6);
//        }
//        data_from_channel = resp;
//        emit signal_read_data(data_from_channel);
//        if (!resp.isEmpty() && ((uint8_t)resp.at(0) == 0xD3)) {
//            data_from_channel = resp.mid(1);
//            emit signal_HDLC_from_device(data_from_channel);
//        }
//        break;
//    }
    case SWITCH_CONNECT_rs485: {
        data_from_channel.append(resp);
        if (data_from_channel.size() > 5 && data_from_channel.right(1).at(0) == 0x7E) {
            log_5 << "RX" << data_from_channel.toHex().toUpper();
            emit signal_HDLC_from_device(data_from_channel);
            data_from_channel.clear();
        }
        is_connected = true;
        update_button();
     //   emit signal_show_widget_info();
     //   emit signal_show_widget_pulse();
        break;
    }
    case SWITCH_CONNECT_opto_HDLC: {
        static type_slip_buf slip_buf;
//        QByteArray arr = ELECTRO5_to_HDLC(QByteArray::fromHex("EF06"));
        //            log_1 << arr.toHex().toUpper();
        QByteArray arr_upack = HDLC_to_ELECTRO5(&slip_buf, resp);
        if (arr_upack.isEmpty()) break;
        is_connected = true;
        update_button();
        log_1 << "RX" << arr_upack.toHex().toUpper();
        data_from_channel = arr_upack;
        emit signal_read_data(data_from_channel);
//        emit signal_HDLC_from_device(data_from_channel);
        break;
    }
    default:
        break;
    }
}

void widget_connect::update_com_ports()
{
    ui->comboBox_com_port->clear();
    QList<QSerialPortInfo> spa = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo spi, spa) {
        QString str;
        str.append(spi.portName()); str.append(" ");
        str.append(spi.manufacturer()); str.append(" ");
        str.append(spi.serialNumber());
        if (spi.hasProductIdentifier()) {
            str.append(" ");
            str.append(QString::number(spi.productIdentifier(), 16).toUpper());
        }
        if (spi.hasVendorIdentifier()) {
            str.append(" ");
            str.append(QString::number(spi.vendorIdentifier(), 16).toUpper());
        }
        ui->comboBox_com_port->addItem(str, spi.portName());
        if (com_port == spi.portName()) {
            ui->comboBox_com_port->setCurrentIndex(ui->comboBox_com_port->count() - 1);
        }
    }
}

void widget_connect::update_button()
{
    if (is_connected){
        ui->pushButton_connect->setText("Связь установлена/Отключить соединение");
        ui->label->hide();
        ui->label_2->hide();
        ui->label_pass->hide();
        ui->comboBox_client_addr->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->spinBox_server_addr_logical->hide();
        ui->spinBox_server_addr_physical->hide();
        ui->lineEdit_pass->hide();
        ui->comboBox_com_port->hide();
        ui->pushButton->hide();
    }
    else{
        ui->pushButton_connect->setText("Соединение");
        ui->label->show();
        ui->label_2->show();
        ui->label_pass->show();
        ui->comboBox_client_addr->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->spinBox_server_addr_logical->show();
        ui->spinBox_server_addr_physical->show();
        ui->comboBox_com_port->show();
        uint32_t client_addr = ui->comboBox_client_addr->currentData().toUInt();
        ui->lineEdit_pass->hide();
        ui->label_pass->hide();
        ui->pushButton->show();
        switch (client_addr) {
            case 0x10: break;
            case 0x20: {
                ui->lineEdit_pass->show();
                ui->label_pass->show();
             //   ui->lineEdit_pass->setText("Reader");
                break;
            }
            case 0x30: {
                ui->lineEdit_pass->show();
                ui->label_pass->show();
                ui->lineEdit_pass->setText("SettWaviotPhobos");
                break;
            }
            default: break;
        }
    }
}

void widget_connect::slot_update_switch_connect()
{
    is_connected = false;
    emit signal_disconnect();
    ui->lineEdit_host_udp_direct->hide();
    ui->spinBox_port_udp_direct->hide();
    ui->comboBox_com_port->hide();
    ui->spinBox_modem_dec->hide();
    ui->spinBox_modem_hex->hide();
    sconnect = SWITCH_CONNECT_none;
    if (ui->pushButton_connect->isChecked()) {
        ui->pushButton_connect->click();
    }
    if (serial->isOpen()) {
        serial->close();
    }
    if (ui->radioButton_udp_hdlc->isChecked()) {
        ui->lineEdit_host_udp_direct->show();
        ui->spinBox_port_udp_direct->show();
        sconnect = SWITCH_CONNECT_UDP_HDLC;
    }
    if (ui->radioButton_rs_fastdl->isChecked()) {
        update_com_ports();
        ui->comboBox_com_port->show();
        sconnect = SWITCH_CONNECT_radio_FASTDL;
    }
    if (ui->radioButton_rs_fastdl_hdlc->isChecked()) {
        update_com_ports();
        ui->comboBox_com_port->show();
        sconnect = SWITCH_CONNECT_radio_FASTDL_HDLC;
    }
    if (ui->radioButton_rs_485->isChecked()) {
        update_com_ports();
        ui->comboBox_com_port->show();
        sconnect = SWITCH_CONNECT_rs485;
    }
    if (ui->radioButton_opto_hdlc->isChecked()) {
        update_com_ports();
        ui->comboBox_com_port->show();
        sconnect = SWITCH_CONNECT_opto_HDLC;
    }
    if (ui->radioButton_opto_mode_e->isChecked()) {
        update_com_ports();
        ui->comboBox_com_port->show();
        sconnect = SWITCH_CONNECT_opto_MODE_E;
    }
    if (ui->radioButton_rs_fastdl_electro->isChecked()) {
        update_com_ports();
        ui->comboBox_com_port->show();
        ui->spinBox_modem_dec->show();
        ui->spinBox_modem_hex->show();
        sconnect = SWITCH_CONNECT_radio_FASTDL_electro;
    }
    update_button();
}

void widget_connect::slot_HDLC_to_device(QByteArray data)
{
    log_5 << "TX" << data.toHex().toUpper();
    switch (sconnect) {
    case SWITCH_CONNECT_UDP_HDLC: {
        //udp->writeDatagram(data, udp_senderAddress, udp_senderPort);
        log_1 << data.toHex().toUpper() << QHostAddress(ui->lineEdit_host_udp_direct->text()) << ui->spinBox_port_udp_direct->value();
        udp->writeDatagram(data, QHostAddress(ui->lineEdit_host_udp_direct->text()), ui->spinBox_port_udp_direct->value());
        break;
    }
    case SWITCH_CONNECT_radio_FASTDL: {
        if (!serial->isOpen()) break;
        data.prepend(QByteArray::fromHex("D3"));
        data = CMD_to_SLIP(0x32, (quint8 *)data.data(), data.size());
        serial->write(data);
        break;
    }
    case SWITCH_CONNECT_radio_FASTDL_HDLC: {
        if (!serial->isOpen()) break;
        data.prepend(QByteArray::fromHex("D3"));
        data = CMD_to_SLIP(0x32, (quint8 *)data.data(), data.size());
        serial->write(data);
        break;
    }
    case SWITCH_CONNECT_rs485: {
        if (!serial->isOpen()) break;
       // is_connected = true;
        serial->write(data);
        break;
    }
    case SWITCH_CONNECT_opto_HDLC: {
        if (!serial->isOpen()) break;
        data = ELECTRO5_to_HDLC(data);
//        log_1 << "TX" << data.toHex().toUpper();
        serial->write(data);
        break;
    }
    case SWITCH_CONNECT_radio_FASTDL_electro: {
        if (!serial->isOpen()) break;
        data = CMD_to_SLIP(0x32, (quint8 *)data.data(), data.size());
        serial->write(data);
        break;
    }
    default: break;
    }
}

//#include <QPushButton>
void widget_connect::slot_disconnect()
{
    if (ui->pushButton_connect->isChecked()) {
        ui->pushButton_connect->click();
    }
}

void widget_connect::on_pushButton_connect_clicked(bool checked)
{
    if (checked) {
     //   emit signal_timeout_start(3000);
        switch (sconnect) {
                case SWITCH_CONNECT_UDP_HDLC: {
            emit signal_connect(server_addr(), ui->comboBox_client_addr->currentData().toUInt(), ui->lineEdit_pass->text().toLocal8Bit());
            break;
        }
        case SWITCH_CONNECT_radio_FASTDL:
        case SWITCH_CONNECT_radio_FASTDL_HDLC: {
            if (serial->isOpen()) {
                serial->close();
            }
            serial->setPortName(ui->comboBox_com_port->currentData().toString());
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setBaudRate(115200);
            if (!serial->open(QIODevice::ReadWrite)) {
                log_1 << "cant open" << serial->portName();
                break;
            }
            nbfi_set_FastDL();

            emit signal_connect(server_addr(), ui->comboBox_client_addr->currentData().toUInt(), ui->lineEdit_pass->text().toLocal8Bit());
            break;
        }
        case SWITCH_CONNECT_rs485: {
            if (serial->isOpen()) {
                serial->close();
            }
            serial->setPortName(ui->comboBox_com_port->currentData().toString());
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setBaudRate(9600);
            if (!serial->open(QIODevice::ReadWrite)) {
                log_1 << "cant open" << serial->portName();
                break;
            }
            emit signal_connect(server_addr(), ui->comboBox_client_addr->currentData().toUInt(), ui->lineEdit_pass->text().toLocal8Bit());
            break;
        }
        case SWITCH_CONNECT_opto_HDLC: {
            if (serial->isOpen()) {
                serial->close();
            }
            serial->setPortName(ui->comboBox_com_port->currentData().toString());
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setBaudRate(9600);
            if (!serial->open(QIODevice::ReadWrite)) {
                log_1 << "cant open" << serial->portName();
                break;
            }
//            static type_slip_buf slip_buf;

            QByteArray arr = ELECTRO5_to_HDLC(QByteArray::fromHex("EF06"));
//            log_1 << arr.toHex().toUpper();
//            QByteArray arr_upack = HDLC_to_ELECTRO5(&slip_buf, arr);
//            log_1 << arr_upack.toHex().toUpper();
            serial->write(arr);
//            emit signal_connect(server_addr(), ui->comboBox_client_addr->currentData().toUInt(), ui->lineEdit_pass->text().toLocal8Bit());
            break;
        }
        case SWITCH_CONNECT_radio_FASTDL_electro: {
            if (serial->isOpen()) {
                serial->close();
            }
            serial->setPortName(ui->comboBox_com_port->currentData().toString());
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            serial->setBaudRate(115200);
            if (!serial->open(QIODevice::ReadWrite)) {
                log_1 << "cant open" << serial->portName();
                break;
            }
            nbfi_set_FastDL();
            log_1 << "send";
            slot_HDLC_to_device(QByteArray::fromHex("EF06"));
            break;
        }
        default: break;
        }
    } else {
//        emit signal_hide_widget_info();
//        emit signal_hide_widget_pulse();
//        emit signal_hide_point_power();
//        emit signal_hide_power_data();
//        emit signal_hide_power_data_1f();
        emit signal_disable_tab_kn(0, 0);
        slot_disable_tab_kn(0, 0);
        emit signal_tab_hide();
        ui->pushButton_ReadData->hide();

        is_connected = false;
        update_button();
//        if (serial->isOpen()) {
//            serial->close();
//        }
        emit signal_disconnect();
        switch (sconnect) {
        case SWITCH_CONNECT_UDP_HDLC: {
//            emit signal_connect(server_addr(), ui->comboBox_client_addr->currentData().toUInt(), ui->lineEdit_pass->text().toLocal8Bit());
            break;
        }
        case SWITCH_CONNECT_radio_FASTDL:
        case SWITCH_CONNECT_radio_FASTDL_HDLC:
        case SWITCH_CONNECT_radio_FASTDL_electro: {
            if (serial->isOpen()) {
                slot_HDLC_to_device(QByteArray::fromHex("EF02"));
                serial->waitForReadyRead(1000);
                serial->close();
            }
            break;
        }
        case SWITCH_CONNECT_rs485: {
            if (serial->isOpen()) {
                serial->close();
            }
            break;
        }
        case SWITCH_CONNECT_opto_HDLC: {
            if (serial->isOpen()) {
                serial->close();
            }
            break;
        }
        default: break;
        }
    }
}

void widget_connect::on_comboBox_client_addr_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    uint32_t client_addr = ui->comboBox_client_addr->currentData().toUInt();
    ui->lineEdit_pass->hide();
    ui->label_pass->hide();
    switch (client_addr) {
        case 0x10: break;
        case 0x20: {
            ui->lineEdit_pass->show();
            ui->label_pass->show();
         //   ui->lineEdit_pass->setText("Reader");
            break;
        }
        case 0x30: {
            ui->lineEdit_pass->show();
            ui->label_pass->show();
            ui->lineEdit_pass->setText("SettWaviotPhobos");
            break;
        }
        default: break;
    }
}

void widget_connect::on_spinBox_modem_dec_valueChanged(int arg1)
{
    ui->spinBox_modem_hex->setValue(arg1);
}

void widget_connect::on_spinBox_modem_hex_valueChanged(int arg1)
{
    ui->spinBox_modem_dec->setValue(arg1);
}

void widget_connect::on_pushButton_ReadData_clicked()
{
    bn_fl = 2;
    on_pushButton_connect_clicked(true);
}

void widget_connect::on_pushButton_clicked()
{
    update_com_ports();
}

void widget_connect::on_pushButton_2_clicked()
{
    bn_fl = 1;
    on_pushButton_connect_clicked(true);
}

void widget_connect::slot_view_log_hide_show(bool hide_show){
    if (hide_show) ui->pushButton_2->show();
    else ui->pushButton_2->hide();
}

void widget_connect::slot_disable_tab_kn(bool fl, int){
    if (fl) ui->pushButton_ReadData->setEnabled(false);
    else ui->pushButton_ReadData->setEnabled(true);
    if (fl) ui->pushButton_2->setEnabled(false);
    else ui->pushButton_2->setEnabled(true);
}
