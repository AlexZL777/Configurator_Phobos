#ifndef AXSEM_SETTINGS_H
#define AXSEM_SETTINGS_H

#include <stdint.h>

typedef enum {
    DL_PSK_200              = 0,
    DL_PSK_500              = 1,
    DL_PSK_5000             = 2,
    DL_PSK_FASTDL           = 3,
    UL_DBPSK_50_PROT_C      = 20,
    UL_DBPSK_50_PROT_D      = 21,
    UL_PSK_200              = 22,
    UL_DBPSK_400_PROT_C     = 23,
    UL_DBPSK_400_PROT_D     = 24,
    UL_PSK_500              = 25,
    UL_DBPSK_3200_PROT_D    = 26,
    UL_PSK_5000             = 27,
    UL_DBPSK_25600_PROT_D   = 28,
    UL_PSK_FASTDL           = 29,
    UL_CARRIER              = 50
} nbfi_phy_channel_t;

typedef enum {
    MACK_0      = 0,//no ack
    MACK_1      = 1,//0x1,
    MACK_2      = 2,//0x3,
    MACK_4      = 4,//0x0f,
    MACK_8      = 8,//0xff,
    MACK_16     = 16,//0xffff,
    MACK_32     = 32,//0,
} nbfi_mack_mode_t;

typedef enum {
    DRX         =   1,
    CRX         =   2,
    TRANSPARENT =   3,
} nbfi_mode_t;

typedef enum {
    HANDSHAKE_NONE      = 0,
    HANDSHAKE_SIMPLE    = 1,
    HANDSHAKE_TRIPPLE   = 2,
} nbfi_handshake_t;

typedef struct {
    nbfi_mode_t         mode;               //+режим связи DRX CRX TRANSPARENT
    nbfi_phy_channel_t  tx_phy_channel;     //+скорость UL
    nbfi_phy_channel_t  rx_phy_channel;     //+скорость DL
    nbfi_handshake_t    handshake_mode;     //+требование ACK
    nbfi_mack_mode_t    mack_mode;          //+
    uint8_t             num_of_retries;     //+кол-во повторов
    uint8_t             max_payload_len;    //+
    uint32_t            dl_ID;              //+
    uint8_t             temp_ID[3];         //
    uint8_t             broadcast_ID[3];    //
    uint8_t             full_ID[6];         // chipID
    uint32_t            tx_freq;            //+частота UL
    uint32_t            rx_freq;            //+частота DL
    uint8_t             tx_antenna;         //+выход UL антены
    uint8_t             rx_antenna;         //+выход DL антены
    int8_t              tx_pwr;             //+мощность передачи
    uint16_t            heartbeat_interval; //+
    uint8_t             heartbeat_num;      //+
    uint8_t             additional_flags;   //
    //nbfi_attach_state_t  attach_state;
} nbfi_settings_t;

#define READ_PARAM_CMD              0x00
#define WRITE_PARAM_CMD             0x01
#define WRITE_PARAM_WITH_ACK_CMD    0x02

#define NBFI_PARAM_MODE             0x00
#define NBFI_PARAM_HANDSHAKE        0x01
#define NBFI_PARAM_MAXLEN           0x02
#define NBFI_PARAM_TXFREQ           0x03
#define NBFI_PARAM_RXFREQ           0x04
#define NBFI_PARAM_ANT              0x05
#define NBFI_PARAM_DL_ADD           0x06
#define NBFI_PARAM_HEART_BEAT       0x07
#define NBFI_PARAM_TX_BRATES        0x08
#define NBFI_PARAM_RX_BRATES        0x09
#define NBFI_PARAM_VERSION          0x0A
#define NBFI_ADD_FLAGS              0x0B

#endif // AXSEM_SETTINGS_H
