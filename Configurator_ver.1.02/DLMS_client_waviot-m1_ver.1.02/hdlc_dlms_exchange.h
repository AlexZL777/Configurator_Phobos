#ifndef HDLC_DLMS_EXCHANGE_H
#define HDLC_DLMS_EXCHANGE_H

#include <QObject>
#include <QVariant>
#include "DLMS_enums.h"

#define DLMS_MaxServerPDUSize (0x200)
#define DLMS_MaxServerPDUSizeGet (0x80)
#define HDLC_PACKET_SIZE (128)
#define HDLC_TIMEOUT_FRAME (600 - 50)

typedef void (*HDLC_BUF_TX)(uint8_t);

typedef enum {
    //commands / responses
    cf_SSS_RR = 0x0, // Receive ready
    cf_SSS_RNR= 0x2, // Receive ready
    cf_I    = 0x10,   // Information
    cf_RR   = 0x11,   // Receive ready
    cf_RNR  = 0x15,   // Receive not ready
//    REJ - Reject
//    SREJ - Selective reject
    cf_UI   = 0x13,   // Unnumbered information
//    XID - Exchange identification
//    TEST - Test
//    UIH - Unnumbered information with header check

    //commands
    cf_SNRM = 0x93,   // Set normal response mode
//    SARM - Set asynchronous response mode
//    SABM - Set asynchronous balanced mode
    cf_DISC = 0x53,   // Disconnect
//    SNRME - Set normal response mode extended
//    SARME - Set asynchronous response mode extended
//    SABME - Set asynchronous balanced mode extended
//    SIM - Set initialization mode
//    UP - Unnumbered poll
//    RSET - Reset
//    SM - Set Mode

    //responses
    cf_UA   = 0x73,   // Unnumbered acknowledgement
    cf_DM   = 0x1F,   // Disconnected mode
//    RIM - Request initialization mode
//    RD - Request disconnect
    cf_FRMR = 0x97,   // Frame reject
} control_field_enum;

//#pragma pack(push, 1)
typedef struct {
    uint8_t A;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t F;
} OBIS;
//#pragma pack(pop)

typedef struct {
    DLMS_COMMAND cmd;
    DLMS_GET_COMMAND_TYPE type;
    uint8_t invoke_id_and_priority;
    DLMS_OBJECT_TYPE ci;
    OBIS obis;
    uint8_t attributeIndex;
    uint8_t selection;
    int32_t block_index;
} PDU_header;

//#pragma pack(push, 1)
typedef union {
    uint8_t control;
    struct {
        uint8_t is_n_I          : 1;    // i bit
        uint8_t SSS             : 3;    // send sequence number N(S)
        uint8_t P_F             : 1;    // poll/final bit (last=1, cont=0, Poll clint->server/Final server->client)
        uint8_t RRR             : 3;    // receive sequence number N(R)
    } bits;
} HDLC_control_field;

typedef union {
    uint32_t addr;
    struct {
        uint32_t flag           : 4;    // флаг адреса в пакете
        uint32_t addr           :28;    // старший 1 или 2х байтный адрес, младший 2х байтный адрес в 4х байтной адресации
    } bytes4;
    struct {
        uint32_t flag           : 4;    // флаг адреса в пакете
        uint32_t addr_up        :14;    // старший 1 или 2х байтный адрес
        uint32_t addr_lo        :14;    // младший 2х байтный адрес в 4х байтной адресации
    } bytes2;
    struct {
        uint32_t flag           : 4;    // флаг адреса в пакете
        uint32_t addr_up_hi     : 7;    // старший 1 байтный адрес
        uint32_t addr_up_lo     : 7;    // старший 2 байтный адрес
        uint32_t addr_lo_hi     : 7;    // младший 1 байтный адрес в 4х байтной адресации
        uint32_t addr_lo_lo     : 7;    // младший 2 байтный адрес в 4х байтной адресации
    } bytes1;
} HDLC_addr_field;

typedef struct {
    uint8_t CtoS_challenge[64]; // 16 real
    uint8_t CtoS_challenge_len;
    uint8_t StoC_challenge[64]; // 16 real
    uint8_t StoC_challenge_len;

    PDU_DLMS_AUTHENTICATION authentication;
    uint8_t authentication_ok;
    PDU_DLMS_CONFORMANCE conformance;
} PDU_channel;

typedef struct {
//    HDLC_BUF_RX rx_isEpmty;             // буфер приема пуст
//    HDLC_BUF_RX rx;                     // читать буфер приема
    HDLC_BUF_TX tx;                     // писать в буфер отправки
//    HDLC_BUF_TX set_baud;               // 0 = 300, 5 = 9600 // IEC61107
//    HDLC_BUF_TX waiting_10mc;             // пауза в мс
    uint8_t  mode_frame         : 3;    // флаг управления преобразованием пакета, используется парсером
    uint8_t  mode_connect       : 1;    // текущий режим работы
    uint8_t  LLC_flag           : 2;    // LLC в data
    uint8_t  IEC61107_is_use    : 1;    // оптопорт
    uint8_t  IEC61107_now       : 1;    // используется в текущий момент IEC61107
    uint8_t  IEC61107_cmd;
    uint16_t crc;                       // рассчитываемая конрольная сумма, используется парсером
    uint16_t calc_HCS;                  // рассчитываемая конрольная сумма заголовка, используется парсером
    uint16_t frame_byte_counter;        // счетчик байтов из пакета
    uint32_t last_time_data;            // время последнего прихода символа в мс
    uint32_t last_now;                  // время
    uint16_t timeout_frame;             // Межсимвольный таймаут в мсек const
    uint16_t timeout_connect;           // Межкадровый таймаут в сек
    HDLC_control_field control_srv;     // хранилка счетчиков пакета сервера
    HDLC_control_field control_clt;     // хранилка счетчиков пакета клиента

    uint16_t format_type        : 4;    //+2  формат пакета = 0xA
    uint16_t segmentation       : 1;    //+2  флаг дробления пакета
    uint16_t frame_length       :11;    //+2  длина всего пакета без флагов управления пакетами
    HDLC_addr_field serv;               //+6  адрес сервера
    HDLC_addr_field clnt;               //+10 адрес клиента
    HDLC_control_field  control;        //+12 байт управления
    uint16_t HCS;                       //+14 Header check sequence  заголовка при наличии данных
    uint16_t data_len;
    uint16_t data_index;
    uint8_t  data_buf[DLMS_MaxServerPDUSize];
    uint16_t FCS;                       //+xx Frame check sequence из пакета

    PDU_channel pdu_ch;
    PDU_header pduHeader;
    uint16_t data_block_len;
    uint8_t  data_block_buf[DLMS_MaxServerPDUSizeGet]; // хранилка первого запроса при работе с блоками
} HDLC_BUF;

typedef enum {
    DLMS_global_CMD_none,
    DLMS_global_CMD_connect,
} DLMS_global_CMD;

class HDLC_DLMS_exchange : public QObject
{
    Q_OBJECT
public:
    explicit HDLC_DLMS_exchange(QObject *parent = nullptr);
    ~HDLC_DLMS_exchange();
    static QByteArray DLMS_QVariantMap_to_PDU(QVariantMap vpdu);
    static QVariantMap DLMS_PDU_to_QVariantMap(QByteArray pdu);
    static QVariantMap DLMS_PDU_to_QVariantMap_append(QByteArray pdu, QByteArray data);
    QByteArray buf_block;

    QByteArray tx_buf;
    void HDLC_MAC_parser_controller(HDLC_BUF *hdlc);
signals:
    void signal_HDLC_to_device(QByteArray data);
    void signal_PDU_from_device(QVariant vpdu);
  //  void signal_write_data_PDU(QByteArray);
public slots:
    void slot_connect(uint32_t server, uint32_t client, QByteArray pass);
    void slot_vPDU_to_device(QVariant vpdu);
    void slot_HDLC_from_device(QByteArray data);
    void slot_PDU_to_device(QByteArray pdu);
protected:
//    void HDLC_Clear(HDLC_BUF *hdlc);
//    void HDLC_TX_add_byte(HDLC_BUF *hdlc, uint8_t c);
//    void HDLC_Send();
//    void HDLC_MAC_stringify_controller_cmd(control_field_enum cf);
//    void HDLC_MAC_stringify_controller_PDU(QByteArray pdu);
//    void HDLC_MAC_LLC_parser(uint8_t c);
//    void HDLC_MAC_stringify_controller_PDU(HDLC_BUF *hdlc, QByteArray pdu);
//    HDLC_BUF * hbuf_out;
//    HDLC_BUF * hbuf_in;
    QByteArray pass;

//    QByteArray hdlc_out_buf;
//    QByteArray hdlc_in_buf_data;
//    QByteArray pass;
//    DLMS_global_CMD global_cmd;
//    int global_cmd_index;
};

extern HDLC_DLMS_exchange * hdlc_exch;

#endif // HDLC_DLMS_EXCHANGE_H
