#include "hdlc_electro5_exchange.h"

#include "DLMS_CRC.h"
#include <QJsonDocument>
#include <QBitArray>
#include <Logger/Logger.h>

#define HDLC_PACKET_SIZE___ (HDLC_PACKET_SIZE - 2)

HDLC_ELECTRO5_exchange * hdlc_el5_exch = 0;

HDLC_ELECTRO5_exchange::HDLC_ELECTRO5_exchange(QObject *parent)
    : QObject(parent)
{
    hdlc_el5_exch = this;
    hbuf_out = new HDLC_BUF;
    hbuf_in = new HDLC_BUF;
    hdlc_out_buf.reserve(256);
//    0.0.40.0.0.255
//    0000280000FF
//    QByteArray arr = "{\"get-request\":{\"get-request-normal\":{\"invoke-id-and-priority\":129,\
//                \"cosem-attribute-descriptor\":{\"class-id\":15,\"instance-id\":\"0.0.40.0.0.255\",\"attribute-id\":2}}}}";

//    QVariantMap vm = QJsonDocument::fromJson(arr).toVariant().toMap();
//    log_1 << qPrintable(QJsonDocument::fromVariant(vm).toJson());
//    log_1 << DLMS_QVariantMap_to_PDU(vm).toHex().toUpper();
//    log_1 << " C00181000F0000280000FF0200";
//    slot_HDLC_from_device(QByteArray::fromHex("7EA87E2103528C89E6E700C401810001820003020412000F110109060000280000FF0202010902030F0116010002030F0216010002030F0316010002030F0416010002030F0516010002030F0616000002030F0716000002030F0816000002030F09160000010402020F01160002020F02160002020F03160002020F04F0A07E"));
//    QByteArray arr = QByteArray::fromHex("601DA109060760857405080101BE10040E01000000065F1F0400001E1DFFFF");
//    log_1 << arr.toHex().toUpper();
//    QVariantMap vm = DLMS_PDU_to_QVariantMap(arr);
//    log_1 << qPrintable(QJsonDocument::fromVariant(vm).toJson());
//    log_1 << DLMS_QVariantMap_to_PDU(vm).toHex().toUpper();


//    QByteArray arr("C4 01 81 00 01 05 02 04 12 00 08 11 00 09 06 00 00 01 00 00 FF 02 02 01 09 02 03 0F 01 16 01 00 02 03 0F 02 16 01 00 02 03 0F 03 16 01 00 02 03 0F 04 16 01 00 02 03 0F 05 16 01 00 02 03 0F 06 16 01 00 02 03 0F 07 16 01 00 02 03 0F 08 16 01 00 02 03 0F 09 16 01 00 01 06 02 02 0F 01 16 00 02 02 0F 02 16 00 02 02 0F 03 16 00 02 02 0F 04 16 00 02 02 0F 05 16 00 02 02 0F 06 16 00 02 04 12 00 0F 11 01 09 06 00 00 28 00 00 FF 02 02 01 09 02 03 0F 01 16 01 00 02 03 0F 02 16 01 00 02 03 0F 03 16 01 00 02 03 0F 04 16 01 00 02 03 0F 05 16 01 00 02 03 0F 06 16 00 00 02 03 0F 07 16 00 00 02 03 0F 08 16 00 00 02 03 0F 09 16 00 00 01 00 02 04 12 00 0F 11 01 09 06 00 00 28 00 01 FF 02 02 01 09 02 03 0F 01 16 01 00 02 03 0F 02 16 01 00 02 03 0F 03 16 01 00 02 03 0F 04 16 01 00 02 03 0F 05 16 01 00 02 03 0F 06 16 00 00 02 03 0F 07 16 00 00 02 03 0F 08 16 00 00 02 03 0F 09 16 00 00 01 00 02 04 12 00 01 11 00 09 06 00 00 2A 00 00 FF 02 02 01 02 02 03 0F 01 16 01 00 02 03 0F 02 16 01 00 01 00 02 04 12 00 40 11 01 09 06 00 00 2B 00 00 FF 02 02 01 06 02 03 0F 01 16 01 00 02 03 0F 02 16 00 00 02 03 0F 03 16 00 00 02 03 0F 04 16 00 00 02 03 0F 05 16 00 00 02 03 0F 06 16 00 00 01 00");

//    QByteArray arr("6034A1090607608574050801018A0207808B0760857405080201AC088006526561646572BE10040E01000000065F1F0400001E1DFFFF");
//    QByteArray arr("603EA1090607608574050801018A0207808B0760857405080202AC128010764A0C440F4F603810255D5511371108BE10040E01000000065F1F0400001E1DFFFF");
//    arr = QByteArray::fromHex(QString(arr).replace(" ","").toLocal8Bit());
//    QVariantMap vm = DLMS_PDU_to_QVariantMap(arr);
//    log_1 << qPrintable(QJsonDocument::fromVariant(vm).toJson());

}

HDLC_ELECTRO5_exchange::~HDLC_ELECTRO5_exchange()
{
    delete hbuf_in;
    delete hbuf_out;
}

void HDLC_ELECTRO5_exchange::HDLC_Clear(HDLC_BUF *hdlc)
{
//    log_1 << "clear hdlc";
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
void HDLC_ELECTRO5_exchange::HDLC_TX_add_byte(HDLC_BUF *hdlc, uint8_t c)
{
    hdlc->crc = DLMS_crc_byte(hdlc->crc, c);
//    hdlc->crc = (hdlc->crc >> 8) ^ fcstab[(hdlc->crc ^ c) & 0xff];
//    hdlc->tx(c);
    hdlc_out_buf.append(c);
}
void HDLC_ELECTRO5_exchange::HDLC_Send()
{
    hdlc_out_buf.clear();
    HDLC_BUF *hdlc = hbuf_out;

    hdlc_out_buf.append(0x7E);
    hdlc->crc = 0xFFFF;
    HDLC_TX_add_byte(hdlc, 0xC0 + ((hdlc->frame_length >> 8) & 0x7));
    HDLC_TX_add_byte(hdlc, hdlc->frame_length & 0xFF);
    for (int i = 0; i < hdlc->data_len; ++i) {
        HDLC_TX_add_byte(hdlc, hdlc->data_buf[i + hdlc->data_index]);
    }
    hdlc->FCS = hdlc->crc ^ 0xFFFF;
    HDLC_TX_add_byte(hdlc, (hdlc->FCS >> 0) & 0xFF);
    HDLC_TX_add_byte(hdlc, (hdlc->FCS >> 8) & 0xFF);
    hdlc_out_buf.append(0x7E);
}
void HDLC_ELECTRO5_exchange::HDLC_MAC_stringify_controller_cmd(control_field_enum cf)
{
    switch (cf) {
    case cf_SNRM: {
        hbuf_out->control.control = cf_SNRM;
        break;
    }
    case cf_SSS_RR: {
        hbuf_out->segmentation = 1;
//        hbuf_out->data_len = 0;
//        hbuf_out->control.bits.RRR = ++hbuf_out->control_srv.bits.RRR;
        hbuf_out->control.bits.SSS = cf_SSS_RR;
        hbuf_out->control.bits.is_n_I = 1;
        break;
    }
    default: break;
    }
}
void HDLC_ELECTRO5_exchange::HDLC_MAC_stringify_controller_PDU(QByteArray pdu)
{
//    log_1 << pdu.toHex().toUpper();
//    HDLC_Clear(hbuf_in);
    hbuf_out->segmentation = 0;
    hbuf_out->control.bits.is_n_I = 0;
    hbuf_out->control.bits.P_F = 1;
    hbuf_out->LLC_flag = 1;
    hbuf_out->control.bits.RRR = hbuf_out->control_clt.bits.RRR;
    hbuf_out->control.bits.SSS = hbuf_out->control_clt.bits.SSS;
    hbuf_out->data_len = pdu.size();
    hbuf_out->data_index = 0;
    memmove(hbuf_out->data_buf, pdu.data(), hbuf_out->data_len);
    HDLC_Send();
    log_1 << hdlc_out_buf.left(250).toHex().toUpper();
    hbuf_out->control.bits.RRR = ++hbuf_out->control_clt.bits.RRR;
    hbuf_out->control.bits.SSS = hbuf_out->control_clt.bits.SSS++;
//    log_1 << QByteArray::fromHex("7EA02B032110FBAFE6E600601DA109060760857405080101BE10040E01000000065F1F0400001E1DFFFFC5E47E").toHex().toUpper();
    if (hdlc_out_buf.size() > 250) return;
    emit signal_HDLC_to_device(hdlc_out_buf);
}
void HDLC_ELECTRO5_exchange::HDLC_MAC_LLC_parser(uint8_t c)
{
    HDLC_BUF *hdlc = hbuf_in;

    hdlc->last_time_data = hdlc->last_now;
    if (!hdlc->mode_frame) {
        if (c == 0x7E) {
            hdlc->mode_frame++;
        } else if (c == 0x2F && hdlc->IEC61107_is_use) {
            hdlc->IEC61107_now = 1;
            hdlc->IEC61107_cmd = c;
//            if (hdlc->set_baud) {
//                hdlc->set_baud(0);
//            }
        }
        return;
    }
    if (c == 0x7E && hdlc->mode_frame > 2 && hdlc->frame_length - hdlc->frame_byte_counter < 1) { // end packet
        hdlc->crc ^= 0xFFFF;
//        log_1 << hdlc->mode_frame << (hdlc->HCS == hdlc->calc_HCS) << (hdlc->crc == hdlc->FCS) << (hdlc->control.control || hdlc->data_len);
        if ((hdlc->HCS == hdlc->calc_HCS) && (hdlc->crc == hdlc->FCS) && (hdlc->control.control || hdlc->data_len)) {
            //log_1 << "pdu";// << (hdlc->HCS == hdlc->calc_HCS) << (hdlc->crc == hdlc->FCS) << (hdlc->control.control || hdlc->data_len);
            HDLC_MAC_parser_controller(hdlc);
        }
//        if (cb && (hdlc->HCS == hdlc->calc_HCS) && (hdlc->crc == hdlc->FCS) && (hdlc->control.control || hdlc->data_len)) {
//            cb(hdlc, DLMS_pdu);
//        }
        HDLC_Clear(hdlc);
        return;
    }
    hdlc->frame_byte_counter++;
    if (hdlc->frame_length < 2 || (hdlc->frame_length - hdlc->frame_byte_counter) >= 2) {
        hdlc->crc = DLMS_crc_byte(hdlc->crc, c);//hdlc->crc >> 8) ^ fcstab[(hdlc->crc ^ c) & 0xff];
    }
    // flag | frame format | dest.addr | src.addr | control | HSC | information | FCS | flag
    switch (hdlc->mode_frame) {
    case 1: {   // Frame format 1byte
        if (c == 0x7E) {
            hdlc->frame_byte_counter--;
            hdlc->crc = 0xFFFF;
            break;
        }
        if ((c >> 4) != 0xA) {
            HDLC_Clear(hdlc);
        }
        hdlc->format_type = c >> 4;
        hdlc->segmentation = (c >> 3) & 0x1;
        hdlc->frame_length = (c & 0x7) << 8;
        hdlc->mode_frame++;
        break;
    }
    case 2: {   // Frame format 2byte
        hdlc->frame_length += c;
        hdlc->mode_frame++;
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
            HDLC_Clear(hdlc);
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
//            HDLC_Clear(hdlc);
//            break;
//        }
        if (hdlc->clnt.bytes4.flag > 4) {
            HDLC_Clear(hdlc);
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
        if (hdlc->frame_length - hdlc->frame_byte_counter < 2) {
            hdlc->FCS >>= 8;
            hdlc->FCS += (c << 8);
            hdlc->HCS = hdlc->FCS;
            break;
        }
        hdlc->HCS >>= 8;
        hdlc->HCS += (c << 8);
        if (hdlc->frame_byte_counter == 2 + hdlc->serv.bytes4.flag + hdlc->clnt.bytes4.flag + 1 + 2) {
            hdlc->mode_frame++;
        }
        break;
    }
    case 7: {   // data
        if (hdlc->frame_length - hdlc->frame_byte_counter < 2) {
            hdlc->FCS >>= 8;
            hdlc->FCS += (c << 8);
            break;
        }
        if (!hdlc->control.bits.is_n_I && !hdlc->data_len) {
            if ((c == 0xE6 && hdlc->LLC_flag == 0) ||
                (c == 0xE7 && hdlc->LLC_flag == 1) ||
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

void HDLC_ELECTRO5_exchange::slot_connect(uint32_t server, uint32_t client, QByteArray pass)
{
    memset(hbuf_out, 0, sizeof(HDLC_BUF));
    hbuf_out->crc = 0xFFFF;
//    hbuf_out->timeout_frame = HDLC_TIMEOUT_FRAME;
//    hbuf_out->timeout_connect = HDLC_TIMEOUT_CONNECT;

    log_1 << server << client;
    this->pass = pass;
    hbuf_out->clnt.bytes4.addr = client;
    hbuf_out->clnt.bytes4.flag = 0;
    if (hbuf_out->clnt.bytes4.addr) hbuf_out->clnt.bytes4.flag = 1;
    if (hbuf_out->clnt.bytes4.addr > 0x7F) hbuf_out->clnt.bytes4.flag = 2;
    if (hbuf_out->clnt.bytes4.addr > 0x3FFF) hbuf_out->clnt.bytes4.flag = 4;
    hbuf_out->serv.bytes4.addr = server;
    hbuf_out->serv.bytes4.flag = 0;
    if (hbuf_out->serv.bytes4.addr) hbuf_out->serv.bytes4.flag = 1;
    if (hbuf_out->serv.bytes4.addr > 0x7F) hbuf_out->serv.bytes4.flag = 2;
    if (hbuf_out->serv.bytes4.addr > 0x3FFF) hbuf_out->serv.bytes4.flag = 4;
//    log_1 << hbuf->clnt.bytes4.addr << hbuf->clnt.bytes4.flag;
//    log_1 << hbuf->serv.bytes4.addr << hbuf->serv.bytes4.flag;
    HDLC_Clear(hbuf_in);
    HDLC_MAC_stringify_controller_cmd(cf_SNRM);
    HDLC_Send();
    log_1 << hdlc_out_buf.toHex().toUpper();
//    log_1 << QByteArray::fromHex("7EA0070321930F017E").toHex().toUpper();

//    emit signal_HDLC_to_device(QByteArray::fromHex("7EA0070321930F017E"));
    emit signal_HDLC_to_device(hdlc_out_buf);
}

void HDLC_ELECTRO5_exchange::slot_PDU_to_device(QVariant vpdu)
{
    QVariantMap vm = vpdu.toMap();
    if (vm.contains("aarq") && hbuf_out->clnt.bytes4.addr > 0x10) {
        QVariantMap vm_aarq = vm.value("aarq", QVariantMap()).toMap();
        vm_aarq.insert("sender-acse-requirements", 1);
        vm_aarq.insert("mechanism-name", 1);
        if (hbuf_out->clnt.bytes4.addr == 0x30) {
            vm_aarq.insert("mechanism-name", 2);
        }
        QVariantMap vm_charstring;
        vm_charstring.insert("charstring", pass.toHex().toUpper());
        vm_aarq.insert("calling-authentication-value", vm_charstring);
        vm.insert("aarq", vm_aarq);
    }
    QByteArray arr = DLMS_QVariantMap_to_PDU(vm);
    log_1 << arr.toHex().toUpper();
    HDLC_MAC_stringify_controller_PDU(arr);
}

void HDLC_ELECTRO5_exchange::slot_HDLC_from_device(QByteArray data)
{
    log_1 << data.toHex().toUpper() << data.size();
    for (int i = 0; i < data.size(); ++i) {
//        log_1 << hbuf_in->mode_frame;
        HDLC_MAC_LLC_parser(data[i]);
    }
}
