#include "DLMS_HDLC.h"

#include <string.h>
#include <stdio.h>

#include "DLMS_CRC.h"
#include "meter.h"

#define FORMAT_TYPE_HDLC (0xA)
#define FORMAT_TYPE_ELECTRO5 (0xC)

void DLMS_HDLC_Init(HDLC_BUF *hdlc)
{
    memset(hdlc, 0, sizeof(HDLC_BUF));
    hdlc->crc = 0xFFFF;
    hdlc->timeout_frame = HDLC_TIMEOUT_FRAME;
    hdlc->timeout_connect = HDLC_TIMEOUT_CONNECT;
}

void DLMS_IEC61107_Init(HDLC_BUF *hdlc)
{
    DLMS_HDLC_Init(hdlc);
    hdlc->IEC61107_is_use = 1;
    hdlc->IEC61107_now = 1;
}

void DLMS_HDLC_Clear(HDLC_BUF *hdlc)
{
    if (!hdlc->segmentation) {
        hdlc->data_len = 0;
        hdlc->data_index = 0;
    }
    hdlc->mode_frame = 0;
    hdlc->LLC_flag = 0;
    hdlc->crc = 0xFFFF;
    hdlc->frame_byte_counter = 0;
    hdlc->format_type = 0;
    hdlc->segmentation = 0;
    hdlc->frame_length = 0;
    hdlc->serv.addr = 0;
    hdlc->clnt.addr = 0;
    hdlc->control.control = 0;
    hdlc->HCS = 0;
    hdlc->FCS = 0;
}

void DLMS_HDLC_MAC_LLC_parser(HDLC_BUF *hdlc, uint8_t c, DLMS_HDLC_Dispatcher_cb cb, DLMS_PDU_Dispatcher_cb DLMS_pdu, DLMS_PDU_Dispatcher_cb ELECTRO5_pdu)
{
    hdlc->last_time_data = hdlc->last_now;
    if (!hdlc->mode_frame) {
        if (c == 0x7E) {
            hdlc->mode_frame++;
        } else if (c == 0x2F && hdlc->IEC61107_is_use) {
            hdlc->IEC61107_now = 1;
            hdlc->IEC61107_cmd = c;
            if (hdlc->set_baud) {
                hdlc->set_baud(0);
            }
        }
        return;
    }
    hdlc->frame_byte_counter++;
    if (c == 0x7E && hdlc->mode_frame > 1 && hdlc->frame_length < hdlc->frame_byte_counter) { // end packet
        hdlc->crc ^= 0xFFFF;
        if (hdlc->format_type == FORMAT_TYPE_HDLC) {
            if (cb && (hdlc->HCS == hdlc->calc_HCS) && (hdlc->crc == hdlc->FCS) && (hdlc->control.control || hdlc->data_len > 2)) {
                if (hdlc->mode_frame == 7) {
                    if (hdlc->data_len > 2) hdlc->data_len -= 2;
                }
                cb(hdlc, DLMS_pdu);
            }
        } else {
            if (ELECTRO5_pdu && (hdlc->crc == hdlc->FCS) && hdlc->data_len) {
                if (hdlc->data_len > 2) hdlc->data_len -= 2;
                ELECTRO5_pdu(hdlc);
            }
        }
        DLMS_HDLC_Clear(hdlc);
        return;
    }
    hdlc->FCS >>= 8;
    hdlc->FCS += (c << 8);
    if ((hdlc->mode_frame <= 2) || (hdlc->frame_byte_counter + 2 <= hdlc->frame_length)) {
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
        if (hdlc->format_type == FORMAT_TYPE_HDLC || hdlc->format_type == FORMAT_TYPE_ELECTRO5) {
            hdlc->segmentation = (c >> 3) & 0x1;
            hdlc->frame_length = (c & 0x7) << 8;
            hdlc->mode_frame++;
        } else {
            DLMS_HDLC_Clear(hdlc);
        }
        break;
    }
    case 2: {   // Frame format 2byte
        hdlc->frame_length += c;
        if (hdlc->format_type == FORMAT_TYPE_HDLC) {
            hdlc->mode_frame++;
        } else 
            hdlc->mode_frame = 7;
        break;
    }
    case 3: {   // Dest.address
        hdlc->serv.bytes4.flag++;
        if (c & 0x1) {
            hdlc->mode_frame++;
        }
        hdlc->serv.bytes4.addr <<= 7;
        hdlc->serv.bytes4.addr += c >> 0x1;
        if (hdlc->serv.bytes4.flag > 4) {
            DLMS_HDLC_Clear(hdlc);
            break;
        }
        break;
    }
    case 4: {   // Src. address
        hdlc->clnt.bytes4.flag++;
        if (c & 0x1) {
            hdlc->mode_frame++;
        }
        hdlc->clnt.bytes4.addr <<= 7;
        hdlc->clnt.bytes4.addr += c >> 0x1;
//        if (hdlc->serv.bytes4.flag <= 1) { // fix spodes
//            DLMS_HDLC_Clear(hdlc);
//            break;
//        }
        if (hdlc->clnt.bytes4.flag > 1) { // fix spodes
            DLMS_HDLC_Clear(hdlc);
        }
        break;
    }
    case 5: {   // Control
        hdlc->control.control = c;
        hdlc->calc_HCS = hdlc->crc ^ 0xFFFF;
        hdlc->mode_frame++;
        break;
    }
    case 6: {   // HFS
        if (hdlc->frame_byte_counter == 2 + hdlc->serv.bytes4.flag + hdlc->clnt.bytes4.flag + 1 + 2) {
            if (hdlc->frame_length != hdlc->frame_byte_counter) {
                hdlc->mode_frame++;
            }
            hdlc->HCS = hdlc->FCS;
        }
        break;
    }
    case 7: {   // data
        if (hdlc->format_type == FORMAT_TYPE_HDLC && !hdlc->control.bits.is_n_I && !hdlc->data_len) {
            if ((c == 0xE6 && hdlc->LLC_flag == 0) ||
                (c == 0xE6 && hdlc->LLC_flag == 1) ||
                (c == 0x00 && hdlc->LLC_flag == 2)) {
                hdlc->LLC_flag++;
                break;
            }
        }
        if (hdlc->data_len < DLMS_MaxServerPDUSize) {
            hdlc->data_buf[hdlc->data_len++] = c;
            hdlc->data_index = 0;
        }
        break;
    }
    default: break;
    }
}

//    Скорость обмена по умолчанию – определяет скорость обмена одним из символов:
//    (0) 300 бод;
//    (1) 600 бод;
//    (2) 1200 бод;
//    (3) 2400 бод;
//    (4) 4800 бод;
//    (5) 9600 бод;
//    (6) 19200 бод;
//    (7) 38400 бод;
//    (8) 57600 бод;
//    (9) 115200 бод.
void DLMS_IEC61107_parser(HDLC_BUF *hdlc, uint8_t c, DLMS_HDLC_Dispatcher_cb cb, DLMS_PDU_Dispatcher_cb DLMS_pdu, DLMS_PDU_Dispatcher_cb ELECTRO5_pdu)
{
    hdlc->last_time_data = hdlc->last_now;
//    log_1 << hdlc->IEC61107_is_use << hdlc->IEC61107_now << hdlc->IEC61107_cmd;
    if (!hdlc->IEC61107_is_use || (hdlc->IEC61107_is_use && !hdlc->IEC61107_now)) {
        DLMS_HDLC_MAC_LLC_parser(hdlc, c, cb, DLMS_pdu, ELECTRO5_pdu);
        return;
    }
    if (!hdlc->IEC61107_cmd) {
        if (c == 0x7E) {
            hdlc->IEC61107_now = 0;
            if (!hdlc->mode_frame) {
                hdlc->mode_frame++;
                return;
            }
        } else {
            hdlc->IEC61107_cmd = c;
        }
    }
    if ((c & 0x7F) == 0x0A) {
        switch (hdlc->IEC61107_cmd) {
        case 0x2F: {
//            2F 3F 21 0D 0A 
            hdlc->tx(0x3F);
            hdlc->tx(0x3F);
            hdlc->tx(0x2F);
            for (uint8_t i = 0; i < 3; ++i) {
                hdlc->tx(meter.settings.passport.Device_3[i]);
            }
            hdlc->tx('5');
            hdlc->tx(0x5C);
            hdlc->tx(0x32);
//            uint8_t buf[14];
//            uint8_t buf_len = snprintf((char*)buf, sizeof(buf), "%d", meter.settings.passport.Meter_Serial_Number);
//            for (uint8_t i = 0; i < buf_len; ++i) {
//                hdlc->tx(buf[i]);
//            }
            hdlc->tx(0x0D);
            hdlc->tx(0x0A);
            break;
        }
        case 0x06: {
//            06 B2 35 B2 8D 0A
//            06 32 35 32 0D 0A 
            if (hdlc->set_baud) {
                hdlc->set_baud(5);
            }
            if (hdlc->waiting_10mc) {
                hdlc->waiting_10mc(60);
            }
            hdlc->tx(0x06);
            hdlc->tx(0x32);
            hdlc->tx(0x35);
            hdlc->tx(0x32);
            hdlc->tx(0x0D);
            hdlc->tx(0x0A);
            hdlc->IEC61107_now = 0;
            break;
        }
        }
        hdlc->IEC61107_cmd = 0;
    }
//    ..\GuruxDLMS\DataExchange.cpp { 324} "19.37.27_077" in  "2F3F210D0A2F3F210D0A" 10
//    ..\GuruxDLMS\DataExchange.cpp { 334} "19.37.27_077" out "3F3F2F564D51355C320D0A3F3F2F564D51355C320D0A" 22
//    ..\GuruxDLMS\DataExchange.cpp { 324} "19.37.27_079" in  "063235320D0A" 6
//    ..\GuruxDLMS\DataExchange.cpp { 334} "19.37.27_079" out "06B235B28D0A0A" 7
//    ..\GuruxDLMS\DataExchange.cpp { 324} "19.37.27_580" in  "7EA0070321930F017E" 9
//    ..\GuruxDLMS\DataExchange.cpp { 334} "19.37.27_580" out "" 0
//    ..\GuruxDLMS\DataExchange.cpp { 324} "19.37.27_883" in  "7EA0070321930F017E" 9
//    log_1 << QByteArray::number(c, 16).toUpper() << QByteArray::number(c>>1, 16).toUpper();
}

void UART_HDLC_MAC_controller(HDLC_BUF *hdlc, DLMS_PDU_Dispatcher_cb DLMS_pdu)
{
    //    if (0) { // log
    //    QString str("H(%1 %2) Len(%3) SaddrF(%4) Caddr(%5) Ctrl(%6 %7 %8 %9 = %10) Len(%11) HCS(%12 %13) FCS(%14 %15)");
    //    QString cntrl;
    //    switch (hdlc->control.control) {
    //    case cf_SNRM: cntrl="SNRM"; break;
    //    case cf_DISC: cntrl="DISC"; break;
    //    case cf_UA:   cntrl="UA";   break;
    //    case cf_DM:   cntrl="DM";   break;
    //    case cf_FRMR: cntrl="FRMR"; break;
    //    case cf_UI:   cntrl="UI";   break;
    //    default:
    //        if (!hdlc->control.bits.is_n_I) cntrl="I"; else
    //        if (hdlc->control.bits.SSS == 0) cntrl="RR"; else
    //        if (hdlc->control.bits.SSS == 2) cntrl="RNR";
    //        break;
    //    }
    //    QString saddr;
    //    switch (hdlc->serv.bytes4.flag) {
    //    case 1: saddr = QString::number(hdlc->serv.bytes1.addr_up_hi,16); break;
    //    case 2: saddr = QString::number(hdlc->serv.bytes1.addr_up_lo,16) + " " + QString::number(hdlc->serv.bytes1.addr_up_hi,16); break;
    //    case 4: saddr = QString::number(hdlc->serv.bytes2.addr_lo,16) + " " + QString::number(hdlc->serv.bytes2.addr_up,16); break;
    //    default: saddr = QString::number(hdlc->serv.bytes4.addr,16); break;
    //    }
    //    QString caddr;
    //    switch (hdlc->clnt.bytes4.flag) {
    //    case 1: caddr = QString::number(hdlc->clnt.bytes1.addr_up_hi,16); break;
    //    case 2: caddr = QString::number(hdlc->clnt.bytes1.addr_up_lo,16) + " " + QString::number(hdlc->clnt.bytes1.addr_up_hi,16); break;
    //    case 4: caddr = QString::number(hdlc->clnt.bytes2.addr_lo,16) + " " + QString::number(hdlc->clnt.bytes2.addr_up,16); break;
    //    default: caddr = QString::number(hdlc->clnt.bytes4.addr,16); break;
    //    }

    //    log_2 << str.arg(hdlc->format_type, 0, 16).arg(hdlc->segmentation).arg(hdlc->frame_length).arg(saddr).arg(caddr)
    //             .arg(hdlc->control.bits.RRR).arg(hdlc->control.bits.P_F).arg(hdlc->control.bits.SSS).arg(hdlc->control.bits.is_n_I)
    //             .arg(cntrl).arg(hdlc->frame_byte_counter)
    //             .arg(hdlc->HCS,0,16).arg(hdlc->calc_HCS,0,16).arg(hdlc->FCS,0,16).arg(hdlc->crc,0,16);
    //    log_2 << "req " << QByteArray((const char*)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
    ////    log_1 << hdlc->format_type << hdlc->segmentation << hdlc->frame_length;
    ////    log_1 << hdlc->segmentation;
    //    }

    for (;;) {
        if (hdlc->frame_byte_counter >= HDLC_PACKET_SIZE) { // long packet
            hdlc->control.control = cf_FRMR;
            hdlc->data_len = 0;
            break;
        }
        if (hdlc->segmentation) {
            hdlc->control.bits.RRR = ++hdlc->control_srv.bits.RRR;
            hdlc->control.bits.SSS = cf_SSS_RR;
            hdlc->control.bits.is_n_I = 1;
            break;
        }
        if (hdlc->control.bits.is_n_I) { // cmd
            switch (hdlc->control.bits.SSS) {
            case cf_SSS_RR: {
                if (hdlc->mode_connect) {
                    if (hdlc->control.bits.RRR == hdlc->control_clt.bits.RRR) {
                        if (hdlc->data_index == hdlc->data_len) {
                            hdlc->control.bits.SSS = cf_SSS_RR;
                        } else {
                            hdlc->control.bits.is_n_I = 0;
                            hdlc->control_clt.bits.RRR++;
                            hdlc->control.bits.SSS = hdlc->control_srv.bits.SSS++;
                            hdlc->control.bits.RRR = ++hdlc->control_srv.bits.RRR;
                        }
                    } else {
                        hdlc->control.control = cf_FRMR;
                        hdlc->data_len = 0;
                        hdlc->data_index = 0;
                    }
                } else {
                    hdlc->control.control = cf_FRMR;
                    hdlc->data_len = 0;
                    hdlc->data_index = 0;
                }
                break;
            }
            case cf_SSS_RNR: {
                hdlc->control_clt.bits.RRR++;
//                printf("RNR");//log_1 << QString::number(hdlc->control.control, 16).toUpper() << "RNR";
                break;
            }
            default: {
                switch (hdlc->control.control | 0x10) {
                case cf_SNRM: {
                    hdlc->mode_connect = 1;
                    hdlc->data_len = 0;
                    hdlc->control.control = cf_UA;
                    hdlc->data_buf[hdlc->data_len++] = 0x81; // format identifier
                    hdlc->data_buf[hdlc->data_len++] = 0x80; // group identifier
                    uint8_t * data_group_len = &hdlc->data_buf[hdlc->data_len++]; *data_group_len = 0;
                    const uint8_t ua_HDLC_parameter[] = {0x05,0x02,0x00,0x80,0x06,0x02,0x00,0x80,0x07,0x04,0x00,0x00,0x00,0x01,0x08,0x04,0x00,0x00,0x00,0x01};
                    memmove(&hdlc->data_buf[hdlc->data_len], ua_HDLC_parameter, sizeof(ua_HDLC_parameter));
                    hdlc->data_len+=sizeof(ua_HDLC_parameter);
                    (*data_group_len) = sizeof(ua_HDLC_parameter);

                    hdlc->control_srv.control = 0;
                    hdlc->control_clt.control = 0;
                    break;
                }
                case cf_DISC: {
                    hdlc->data_len = 0;
                    switch (hdlc->mode_connect) {
                    case 1: hdlc->control.control = cf_UA; hdlc->mode_connect = 0; break;
                    default: hdlc->control.control = cf_DM; break;
                    }
                    hdlc->mode_connect = 0;
                    memset(&hdlc->pdu_ch, 0, sizeof(PDU_channel));
                    break;
                }
                default: {
//                    printf("control unknow");//log_1 << QString::number(hdlc->control.control, 16).toUpper() << "control unknow";
                    hdlc->control.control = cf_FRMR;
                    hdlc->data_len = 0;
                }
                }
                break;
            }
            }
            break;
        }
        if (!hdlc->mode_connect) {
//            printf("error mode_connect\r\n");
            hdlc->control.control = cf_DM;
            hdlc->data_len = 0;
            hdlc->data_index = 0;
            return;
            //break;
        }
        if (hdlc->control.bits.RRR != hdlc->control_clt.bits.RRR) {
//            printf("RRR != RRR get\r\n");// << hdlc->control.bits.RRR << "need" << hdlc->control_clt.bits.RRR;
            hdlc->control.bits.SSS = cf_SSS_RR;
            hdlc->control.bits.is_n_I = 1;
            hdlc->data_len = 0;
            hdlc->data_index = 0;
            break;
        }
        if (hdlc->control.bits.SSS != hdlc->control_clt.bits.SSS) {
//            printf("SSS != SSS get\r\n");// << hdlc->control.bits.SSS << "need" << hdlc->control_clt.bits.SSS;
            hdlc->control.bits.SSS = cf_SSS_RR;
            hdlc->control.bits.is_n_I = 1;
            hdlc->data_len = 0;
            hdlc->data_index = 0;
            break;
        }
        hdlc->control_clt.bits.RRR++;
        hdlc->control_clt.bits.SSS++;
//        log_1 << "pdu in " << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).size() << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
        if (DLMS_pdu) {
            DLMS_pdu(hdlc);
        }
//        log_1 << "pdu out" << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).size() << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
        hdlc->control.bits.RRR = ++hdlc->control_srv.bits.RRR;
        hdlc->control.bits.SSS = hdlc->control_srv.bits.SSS++;
        break;
    }
    if (!hdlc->mode_connect) {
        hdlc->control_srv.control = 0;
        hdlc->control_clt.control = 0;
    }
    if (hdlc->control.control == cf_FRMR) {
        hdlc->control_srv.control = 0;
    }
    //    log_2 << "resp" << QByteArray((const char*)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
    DLMS_HDLC_Send(hdlc);
}

void UART_HDLC_TX_add_byte(HDLC_BUF *hdlc, uint8_t c)
{
    hdlc->crc = DLMS_crc_byte(hdlc->crc, c);
//    hdlc->crc = (hdlc->crc >> 8) ^ fcstab[(hdlc->crc ^ c) & 0xff];
    hdlc->tx(c);
}

#define HDLC_PACKET_SIZE___ (HDLC_PACKET_SIZE - 2)
//#define HDLC_PACKET_SIZE___ (35)

void DLMS_HDLC_Send__old(HDLC_BUF *hdlc)
{
    uint8_t segmentation = 0;
    uint16_t data_len = 0;
    hdlc->frame_length = 2 + hdlc->serv.bytes4.flag + hdlc->clnt.bytes4.flag + 1 + 2;
    if (!hdlc->segmentation) {
        hdlc->frame_length += (hdlc->data_len?2:0);
        if (!hdlc->data_index) {
            hdlc->frame_length += ((hdlc->LLC_flag && !hdlc->control.bits.is_n_I)?3:0);
        }
        if (hdlc->frame_length + hdlc->data_len - hdlc->data_index > HDLC_PACKET_SIZE___) {
            data_len = HDLC_PACKET_SIZE___ - hdlc->frame_length;
            segmentation = 1;
        } else {
            data_len = hdlc->data_len - hdlc->data_index;
        }
        if (data_len > HDLC_PACKET_SIZE___) { // fix
            data_len = 0;
        }
        hdlc->frame_length += data_len;
    }
    hdlc->tx(0x7E);
    hdlc->crc = 0xFFFF;
    UART_HDLC_TX_add_byte(hdlc, 0xA0 + ((hdlc->frame_length >> 8) & 0x7) + (segmentation << 3));
    UART_HDLC_TX_add_byte(hdlc, hdlc->frame_length & 0xFF);
    for (int i = hdlc->clnt.bytes4.flag - 1; i != -1; i--) {
        UART_HDLC_TX_add_byte(hdlc, (((hdlc->clnt.bytes4.addr >> (7 * i)) & 0x7F) << 1) + (i?0:1) );
    }
    for (int i = hdlc->serv.bytes4.flag - 1; i != -1; i--) {
        UART_HDLC_TX_add_byte(hdlc, (((hdlc->serv.bytes4.addr >> (7 * i)) & 0x7F) << 1) + (i?0:1) );
    }
    UART_HDLC_TX_add_byte(hdlc, hdlc->control.control);
    if (!hdlc->segmentation && data_len) {
        hdlc->HCS = hdlc->crc ^ 0xFFFF;
        UART_HDLC_TX_add_byte(hdlc, (hdlc->HCS >> 0) & 0xFF);
        UART_HDLC_TX_add_byte(hdlc, (hdlc->HCS >> 8) & 0xFF);
        if (!hdlc->data_index) {
            if (hdlc->LLC_flag && !hdlc->control.bits.is_n_I) {
                UART_HDLC_TX_add_byte(hdlc, 0xE6);
                UART_HDLC_TX_add_byte(hdlc, 0xE7);
                UART_HDLC_TX_add_byte(hdlc, 0x00);
            }
        }
        for (int i = 0; i < data_len; ++i) {
            UART_HDLC_TX_add_byte(hdlc, hdlc->data_buf[i + hdlc->data_index]);
        }
        hdlc->data_index += data_len;
    }
    hdlc->FCS = hdlc->crc ^ 0xFFFF;
    UART_HDLC_TX_add_byte(hdlc, (hdlc->FCS >> 0) & 0xFF);
    UART_HDLC_TX_add_byte(hdlc, (hdlc->FCS >> 8) & 0xFF);
    hdlc->tx(0x7E);
    if (hdlc->segmentation < segmentation) {
        hdlc->segmentation = segmentation;
    }
    if (!hdlc->mode_connect) {
        if (hdlc->IEC61107_is_use) {
            hdlc->IEC61107_now = 1;
            if (hdlc->set_baud) {
                hdlc->set_baud(0);
            }
        }
    }
}

void DLMS_HDLC_Send(HDLC_BUF *hdlc)
{
    if (hdlc->format_type == FORMAT_TYPE_ELECTRO5) {
        hdlc->tx(0x7E);
        hdlc->crc = 0xFFFF;
        hdlc->frame_length = hdlc->data_len + 2 + 2;
        UART_HDLC_TX_add_byte(hdlc, (FORMAT_TYPE_ELECTRO5 << 4) + ((hdlc->frame_length >> 8) & 0x7));
        UART_HDLC_TX_add_byte(hdlc, hdlc->frame_length & 0xFF);
        for (int i = 0; i < hdlc->data_len; ++i) {
            UART_HDLC_TX_add_byte(hdlc, hdlc->data_buf[i]);
        }
        hdlc->FCS = hdlc->crc ^ 0xFFFF;
        hdlc->tx((hdlc->FCS >> 0) & 0xFF);
        hdlc->tx((hdlc->FCS >> 8) & 0xFF);
        hdlc->tx(0x7E);
        return;
    }
    uint8_t segmentation = 0;
    uint16_t data_len = 0;
    hdlc->frame_length = 2 + hdlc->serv.bytes4.flag + hdlc->clnt.bytes4.flag + 1 + 2; // HDLC header
    if (!hdlc->segmentation) {
        hdlc->frame_length += (hdlc->data_len?2:0); // crc size
        if (!hdlc->data_index) {
            hdlc->frame_length += ((hdlc->LLC_flag && !hdlc->control.bits.is_n_I)?3:0); // llc for first packet
        }
        if (hdlc->frame_length + hdlc->data_len - hdlc->data_index > HDLC_PACKET_SIZE___) {
            data_len = HDLC_PACKET_SIZE___ - hdlc->frame_length;
            segmentation = 1;
        } else {
            data_len = hdlc->data_len - hdlc->data_index;
        }
        if (data_len > HDLC_PACKET_SIZE___) { // fix
            data_len = 0;
        }
        hdlc->frame_length += data_len;
    }
    hdlc->tx(0x7E);
    hdlc->crc = 0xFFFF;
    UART_HDLC_TX_add_byte(hdlc, 0xA0 + ((hdlc->frame_length >> 8) & 0x7) + (segmentation << 3));
    UART_HDLC_TX_add_byte(hdlc, hdlc->frame_length & 0xFF);
    for (int i = hdlc->clnt.bytes4.flag - 1; i != -1; i--) {
        UART_HDLC_TX_add_byte(hdlc, (((hdlc->clnt.bytes4.addr >> (7 * i)) & 0x7F) << 1) + (i?0:1) );
    }
    for (int i = hdlc->serv.bytes4.flag - 1; i != -1; i--) {
        UART_HDLC_TX_add_byte(hdlc, (((hdlc->serv.bytes4.addr >> (7 * i)) & 0x7F) << 1) + (i?0:1) );
    }
    UART_HDLC_TX_add_byte(hdlc, hdlc->control.control);
    if (!hdlc->segmentation && data_len) {
        hdlc->HCS = hdlc->crc ^ 0xFFFF;
        UART_HDLC_TX_add_byte(hdlc, (hdlc->HCS >> 0) & 0xFF);
        UART_HDLC_TX_add_byte(hdlc, (hdlc->HCS >> 8) & 0xFF);
        if (!hdlc->data_index) {
            if (hdlc->LLC_flag && !hdlc->control.bits.is_n_I) {
                UART_HDLC_TX_add_byte(hdlc, 0xE6);
                UART_HDLC_TX_add_byte(hdlc, 0xE7);
                UART_HDLC_TX_add_byte(hdlc, 0x00);
            }
        }
        for (int i = 0; i < data_len; ++i) {
            UART_HDLC_TX_add_byte(hdlc, hdlc->data_buf[i + hdlc->data_index]);
        }
        hdlc->data_index += data_len;
    }
    hdlc->FCS = hdlc->crc ^ 0xFFFF;
    hdlc->tx((hdlc->FCS >> 0) & 0xFF);
    hdlc->tx((hdlc->FCS >> 8) & 0xFF);
    hdlc->tx(0x7E);
    if (hdlc->segmentation < segmentation) {
        hdlc->segmentation = segmentation;
    }
    if (!hdlc->mode_connect) {
        if (hdlc->IEC61107_is_use) {
            hdlc->IEC61107_now = 1;
            if (hdlc->set_baud) {
                hdlc->set_baud(0);
            }
        }
    }
}

void DLMS_HDLC_Dispatcher(HDLC_BUF *hdlc, uint32_t now)
{
    hdlc->last_now = now;
    if (hdlc->mode_frame && hdlc->last_now - hdlc->last_time_data > hdlc->timeout_frame) {
//        printf("reset mode\r\n");
        DLMS_HDLC_Clear(hdlc);
        hdlc->control_srv.control = 0;
    }
    if (hdlc->timeout_connect) {
        if (hdlc->mode_connect && hdlc->last_now - hdlc->last_time_data > hdlc->timeout_connect * 1000) {
    //        printf("reset mode, reset connect\r\n");
            hdlc->mode_connect = 0;
            DLMS_HDLC_Clear(hdlc);
            hdlc->control_srv.control = 0;
            if (hdlc->IEC61107_is_use) {
                hdlc->IEC61107_now = 1;
                if (hdlc->set_baud) {
                    hdlc->set_baud(0);
                }
            }
        }
    }
}
