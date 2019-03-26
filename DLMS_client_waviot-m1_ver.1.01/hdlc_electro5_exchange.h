#ifndef HDLC_ELECTRO5_EXCHANGE_H
#define HDLC_ELECTRO5_EXCHANGE_H

#include <QObject>
#include <QVariant>
#include "DLMS_enums.h"
#include "hdlc_dlms_exchange.h"

#define DLMS_MaxServerPDUSize (0x200)
#define DLMS_MaxServerPDUSizeGet (0x80)
#define HDLC_PACKET_SIZE (128)
#define HDLC_TIMEOUT_FRAME (600 - 50)

class HDLC_ELECTRO5_exchange : public QObject
{
    Q_OBJECT
public:
    explicit HDLC_ELECTRO5_exchange(QObject *parent = nullptr);
    ~HDLC_ELECTRO5_exchange();
    static QByteArray DLMS_QVariantMap_to_PDU(QVariantMap vpdu);
    static QVariantMap DLMS_PDU_to_QVariantMap(QByteArray pdu);
signals:
    void signal_HDLC_to_device(QByteArray data);
    void signal_PDU_from_device(QVariant vpdu);
public slots:
    void slot_connect(uint32_t server, uint32_t client, QByteArray pass);
    void slot_PDU_to_device(QVariant vpdu);
    void slot_HDLC_from_device(QByteArray data);
protected:
    void HDLC_Clear(HDLC_BUF *hdlc);
    void HDLC_TX_add_byte(HDLC_BUF *hdlc, uint8_t c);
    void HDLC_Send();
    void HDLC_MAC_stringify_controller_cmd(control_field_enum cf);
    void HDLC_MAC_stringify_controller_PDU(QByteArray pdu);
    void HDLC_MAC_LLC_parser(uint8_t c);
    void HDLC_MAC_parser_controller(HDLC_BUF *hdlc);
    HDLC_BUF * hbuf_out;
    HDLC_BUF * hbuf_in;
    QByteArray hdlc_out_buf;
    QByteArray hdlc_in_buf_data;
    QByteArray pass;
    DLMS_global_CMD global_cmd;
    int global_cmd_index;
};

extern HDLC_ELECTRO5_exchange * hdlc_el5_exch;

#endif // HDLC_ELECTRO5_EXCHANGE_H
