#include "display_obis.h"
#include "DLMS_obis_pack.h"
#include "Logger/Logger.h"

display_obis::display_obis(QObject *parent) : QObject(parent)
{
//    OBIS obis_arr[] = { // display 3ph manual
////        {0,0,96,1,5,255},    // Meter ext device number
//        {0,0,96,1,0,255},    // Meter serial number
//        {0,0,0,2,1,255},     // (SW) Firmware version
//        {0,0,0,2,5,255},     // HW version
//        {0,0,96,1,2,255},    // Meter metrolog ver
//        {0,0,0,0,0,0},
//        {1,0,1,8,0,255},    // A+T0
//        {1,0,1,8,1,255},    // A+T1
//        {1,0,1,8,2,255},    // A+T2
//        {1,0,1,8,3,255},    // A+T3
//        {1,0,1,8,4,255},    // A+T4
//        {1,0,2,8,0,255},    // A-T0
//        {1,0,3,8,0,255},    // R+T0
//        {1,0,4,8,0,255},    // R-T0
//        {0,0,0,0,0,0},
//        {1,0,11+00,7,0,255}, // I
//        {1,0,1+00,7,0,255},  // P
//        {1,0,3+00,7,0,255},  // Q
//        {1,0,9+00,7,0,255},  // S
//        {1,0,14,7,0,255},    // F
//        {1,0,13,7,0,255},    // cosfi
//        {0,0,0,0,0,0},
//        {1,0,11+20,7,0,255}, // IA
//        {1,0,11+40,7,0,255}, // IB
//        {1,0,11+60,7,0,255}, // IC
//        {1,0,12+20,7,0,255}, // UA
//        {1,0,12+40,7,0,255}, // UB
//        {1,0,12+60,7,0,255}, // UC
//        {1,0,1+20,7,0,255},  // PA
//        {1,0,1+40,7,0,255},  // PB
//        {1,0,1+60,7,0,255},  // PC
//        {1,0,3+20,7,0,255},  // QA
//        {1,0,3+40,7,0,255},  // QB
//        {1,0,3+60,7,0,255},  // QC
//        {0,0,0,0,0,0},
//        {0,0,0,9,1,255},     // time
//        {0,0,0,9,2,255},     // date
//    };
//    meter   // 0x04,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x06,0x8B,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x0C,0x9F,0x78,0xB3,0x78,0xC7,0x78,0xA0,0x78,0xB4,0x78,0xC8,0x78,0x95,0x78,0xA9,0x78,0xBD,0x78,0x97,0x78,0xAB,0x78,0xBF,0x78,0x02,0x80,0x91,0x80,0x92
//    meter   // 0x04,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x06,0x8B,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x0C,0x9F,0x78,0xB3,0x78,0xC7,0x78,0xA0,0x78,0xB4,0x78,0xC8,0x78,0x95,0x78,0xA9,0x78,0xBD,0x78,0x97,0x78,0xAB,0x78,0xBF,0x78,0x02,0x80,0x91,0x80,0x92
//    display // 0x05,0xE0,0x15,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x06,0x8B,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x0C,0x9F,0x78,0xB3,0x78,0xC7,0x78,0xA0,0x78,0xB4,0x78,0xC8,0x78,0x95,0x78,0xA9,0x78,0xBD,0x78,0x97,0x78,0xAB,0x78,0xBF,0x78,0x02,0x80,0x91,0x80,0x92

//    OBIS obis_arr[] = { // display 3ph auto
//        {0,0,96,1,0,255},    // Meter serial number
////        {0,0,96,1,5,255},    // Meter ext device number
//        {1,0,1,8,0,255},    // A+T0
//        {1,0,1,8,1,255},    // A+T1
//        {1,0,1,8,2,255},    // A+T2
//        {1,0,1,8,3,255},    // A+T3
//        {1,0,1,8,4,255},    // A+T4
//        {1,0,11+00,7,0,255}, // I
//        {1,0,1+00,7,0,255},  // P
//        {1,0,12+20,7,0,255}, // UA
//        {1,0,12+40,7,0,255}, // UB
//        {1,0,12+60,7,0,255}, // UC
//        {0,0,0,9,1,255},     // time
//        {0,0,0,9,2,255},     // date
//    };
//    meter   // 0xE010,0x8188,0x8189,0x818A,0x818B,0x818C,0x8B78,0x8178,0xA078,0xB478,0xC878,0x8091,0x8092
//    display // 0xE015,0x8188,0x8189,0x818A,0x818B,0x818C,0x8B78,0x8178,0xA078,0xB478,0xC878,0x8091,0x8092

    OBIS obis_arr[] = { // display 1ph manual
//        {0,0,96,1,5,255},    // Meter ext device number
        {0,0,96,1,0,255},    // Meter serial number
        {0,0,0,2,1,255},     // (SW) Firmware version
        {0,0,0,2,5,255},     // HW version
        {0,0,96,1,2,255},    // Meter metrolog ver
        {0,0,0,0,0,0},
        {1,0,1,8,0,255},    // A+T0
        {1,0,1,8,1,255},    // A+T1
        {1,0,1,8,2,255},    // A+T2
        {1,0,1,8,3,255},    // A+T3
        {1,0,1,8,4,255},    // A+T4
        {1,0,2,8,0,255},    // A-T0
        {1,0,3,8,0,255},    // R+T0
        {1,0,4,8,0,255},    // R-T0
        {0,0,0,0,0,0},
        {1,0,11+00,7,0,255}, // I
        {1,0,12+00,7,0,255}, // U *
        {1,0,1+00,7,0,255},  // P
        {1,0,3+00,7,0,255},  // Q
        {1,0,9+00,7,0,255},  // S
        {1,0,14,7,0,255},    // F
        {1,0,13,7,0,255},    // cosfi
        {0,0,0,0,0,0},
        {0,0,0,9,1,255},     // time
        {0,0,0,9,2,255},     // date
    };
//    meter   // 0x04,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x07,0x8B,0x78,0x8C,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x02,0x80,0x91,0x80,0x92
//    display // 0x05,0xE0,0x15,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x07,0x8B,0x78,0x8C,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x02,0x80,0x91,0x80,0x92

//    OBIS obis_arr[] = { // display 1ph auto
//        {0,0,96,1,0,255},    // Meter serial number
////        {0,0,96,1,5,255},    // Meter ext device number
//        {1,0,1,8,0,255},    // A+T0
//        {1,0,1,8,1,255},    // A+T1
//        {1,0,1,8,2,255},    // A+T2
//        {1,0,1,8,3,255},    // A+T3
//        {1,0,1,8,4,255},    // A+T4
//        {1,0,11+00,7,0,255}, // I
//        {1,0,1+00,7,0,255},  // P
//        {1,0,12+00,7,0,255}, // U
//        {0,0,0,9,1,255},     // time
//        {0,0,0,9,2,255},     // date
//    };
//    meter   // 0xE010,0x8188,0x8189,0x818A,0x818B,0x818C,0x8B78,0x8178,0x8C78,0x8091,0x8092
//    display // 0xE015,0x8188,0x8189,0x818A,0x818B,0x818C,0x8B78,0x8178,0x8C78,0x8091,0x8092

//    OBIS obis_arr[] = {
//        {0,0,96,1,0,255},    // Meter serial number
//        {0,0,96,1,2,255},    // Meter serial number
////        {0,0,96,1,5,255},    // Meter serial number
//        {0,0,0,2,1,255},     // (SW) Firmware version
//        {0,0,0,2,5,255},     // HW version
//        {0,0,0,0,0,0},
//        {1,0,12+20,7,0,255}, // UA
//        {1,0,11+00,7,0,255}, // I
//        {1,0,1+00,7,0,255},  // P
//        {1,0,3+00,7,0,255},  // Q
//        {1,0,9+00,7,0,255},  // S
//        {1,0,14,7,0,255},    // F
//        {1,0,11+40,7,0,255}, // IB
//        {1,0,1+40,7,0,255},  // PB
//        {1,0,3+40,7,0,255},  // QB
//        {0,0,0,0,0,0},
//        {1,0,1,8,0,255},    // A+T0
//        {1,0,1,8,1,255},    // A+T1
//        {1,0,1,8,2,255},    // A+T2
//        {1,0,1,8,3,255},    // A+T3
//        {1,0,1,8,4,255},    // A+T4
//        {1,0,2,8,0,255},    // A-T0
//        {1,0,3,8,0,255},    // R+T0
//        {1,0,4,8,0,255},    // R-T0
//        {0,0,0,0,0,0},
//        {0,0,0,9,1,255},     // time
//        {0,0,0,9,2,255},     // date
//    };

//    OBIS obis_arr[] = { // display old manual
//        {0,0,96,1,0,255},    // Meter serial number
//        {0,0,0,9,1,255},     // time
//        {0,0,0,9,2,255},     // date
//        {0,0,0,0,0,0},
//        {1,0,1,8,0,255},    // A+T0
//        {1,0,1,8,1,255},    // A+T1
//        {1,0,1,8,2,255},    // A+T2
//        {1,0,1,8,3,255},    // A+T3
//        {1,0,1,8,4,255},    // A+T4
//        {1,0,2,8,0,255},    // A-T0
//        {1,0,3,8,0,255},    // R+T0
//        {1,0,4,8,0,255},    // R-T0
////        {1,0,1+00,7,0,255},  // P
////        {1,0,3+00,7,0,255},  // Q
//    };
//    meter   // 0x04,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x07,0x8B,0x78,0x8C,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x02,0x80,0x91,0x80,0x92
//    display // 0x05,0xE0,0x15,0xE0,0x10,0x80,0x21,0x80,0x25,0xE0,0x12,0x08,0x81,0x88,0x81,0x89,0x81,0x8A,0x81,0x8B,0x81,0x8C,0x82,0x88,0x83,0x88,0x84,0x88,0x07,0x8B,0x78,0x8C,0x78,0x81,0x78,0x83,0x78,0x89,0x78,0x8E,0x78,0x8D,0x78,0x02,0x80,0x91,0x80,0x92

//    OBIS obis_arr[] = { // display old auto
//        {0,0,96,1,0,255},    // Meter serial number
//        {0,0,0,9,1,255},     // time
//        {0,0,0,9,2,255},     // date
//        {1,0,1,8,0,255},    // A+T0
//        {1,0,1,8,1,255},    // A+T1
//        {1,0,1,8,2,255},    // A+T2
//        {1,0,1,8,3,255},    // A+T3
//        {1,0,1,8,4,255},    // A+T4
//    };
//    meter   // 0xE010,0x8188,0x8189,0x818A,0x818B,0x818C,0x8B78,0x8178,0x8C78,0x8091,0x8092
//    display // 0xE015,0x8188,0x8189,0x818A,0x818B,0x818C,0x8B78,0x8178,0x8C78,0x8091,0x8092


    if (1) {
        uint8_t tbuf[250];
        uint8_t tbuf_len = 1;
        uint8_t * tbuf_addr = &tbuf[0];
        memset(tbuf, 0, 250);
        int obis_arr_len = sizeof(obis_arr) / sizeof(OBIS);
        for (int i = 0; i < obis_arr_len; ++i) {
            OBIS *obis = &obis_arr[i];
            if (!obis->F) {
                tbuf_addr = &tbuf[tbuf_len];
                tbuf_len++;
                continue;
            }
            uint8_t t_len = ElectroAdd_OBIS(tbuf+tbuf_len, obis);
            log_1 << t_len;
            tbuf_len += t_len;
            (*tbuf_addr)++;
        }
        QByteArray arr_out = QByteArray((const char*)tbuf, tbuf_len).toHex().toUpper();

        QString out;
        for (int i = 0; i < tbuf_len; ++i) {
            out += "0x"+QString("%1,").arg(tbuf[i], 2, 16, QChar('0')).toUpper();
        }
        log_1 << out;

        arr_out = QByteArray::fromHex(arr_out);
//        arr_out = arr_out.mid(1);
//        arr_out.prepend((char)0x00);
//        arr_out.prepend((char)0x91);
        log_1 << arr_out.toHex().toUpper();
        uint8_t buf_size = arr_out.size();
        uint8_t * buf_start = (uint8_t *)arr_out.data();
        uint8_t * buf = buf_start;

        uint8_t group_len = 0;
        while (buf + 1 - buf_start < buf_size) {
            if (!group_len) {
                group_len = *buf++;
                if (!group_len) break;
                log_1 << QString("0.0.0.0.0.0") << group_len;
                continue;
            }
            group_len--;
            if (!buf[0] && !buf[1] && !buf[2] && !buf[3] && !buf[4] && !buf[5]) break;
            OBIS obis;
            uint8_t len = ElectroGet_OBIS(buf, &obis);
            OBIS16 *o16 = (OBIS16 *)buf;
            log_1 << len << buf[0] << buf[1];
            log_1 << o16->is_ext;
            buf += len;
            log_1 << QString("%1.%2.%3.%4.%5.%6").arg(obis.A).arg(obis.B).arg(obis.C).arg(obis.D).arg(obis.E).arg(obis.F);
        }

    }

    if (0) {
        int obis_arr_len = sizeof(obis_arr) / sizeof(OBIS);
        log_1 << obis_arr_len;
        uint8_t tbuf[250];
        uint8_t tbuf_len = 0;
        memset(tbuf, 0, 250);
        for (int i = 0; i < obis_arr_len; ++i) {
            uint8_t t_len = ElectroAdd_OBIS(tbuf+tbuf_len, &obis_arr[i]);
            log_1 << t_len;
            tbuf_len += t_len;
        }
        log_1 << QByteArray((const char*)tbuf, tbuf_len).toHex().toUpper();
        uint16_t screen_arr[128];
        uint8_t screen_arr_len = 0;
        for (int i = 0; i < tbuf_len/2; ++i) {
            screen_arr[i] = (tbuf[i*2]<<8) + tbuf[i*2+1];
            screen_arr_len++;
        }

        QString screen_arr_hex;
        for (uint i = 0; i < screen_arr_len; ++i) {
            screen_arr_hex += "0x"+QString("%1,").arg(screen_arr[i], 4, 16, QChar('0')).toUpper();
        }
        log_1 << screen_arr_hex;
    }

}
