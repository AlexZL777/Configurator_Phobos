#include "hdlc_dlms_exchange.h"

#include "DLMS_CRC.h"
#include <QJsonDocument>
#include <QBitArray>
#include <Logger/Logger.h>

#include <QDataStream>

#define HDLC_PACKET_SIZE___ (HDLC_PACKET_SIZE - 2)

HDLC_DLMS_exchange * hdlc_exch = 0;

HDLC_DLMS_exchange::HDLC_DLMS_exchange(QObject *parent)
    : QObject(parent)
{
    hdlc_exch = this;
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

HDLC_DLMS_exchange::~HDLC_DLMS_exchange()
{
    delete hbuf_in;
    delete hbuf_out;
}

void HDLC_DLMS_exchange::slot_HDLC_MAC_stringify_controller_PDU(QByteArray pdu)
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
    log_1 << "HDLC_MAC_stringify_controller_PDU: " << hdlc_out_buf.left(250).toHex().toUpper();
    hbuf_out->control.bits.RRR = ++hbuf_out->control_clt.bits.RRR;
    hbuf_out->control.bits.SSS = hbuf_out->control_clt.bits.SSS++;
//    log_1 << QByteArray::fromHex("7EA02B032110FBAFE6E600601DA109060760857405080101BE10040E01000000065F1F0400001E1DFFFFC5E47E").toHex().toUpper();
    if (hdlc_out_buf.size() > 250) return;
    emit signal_HDLC_to_device(hdlc_out_buf);
}

QPair<uint32_t, QVariant> pdu_data_reader(QByteArray pdu)
{
  //  log_1 << pdu.toHex().toUpper();
    QPair<uint32_t, QVariant> out;
    if (pdu.isEmpty()) return out;
    uint8_t * pb_data = (uint8_t *)pdu.data();
    uint8_t pdu_data_type = *pb_data++; // DLMS_PDU_DATA_TYPE
//    log_1 << pdu_data_type << pdu.size() << pdu.toHex().toUpper().left(20);
    switch (pdu_data_type) {
    case DLMS_PDU_DATA_TYPE_NONE: {
//        log_1 << "NONE" << pdu_data_type << pdu.size() << QByteArray(pdu.mid(pb_data - (uint8_t *)pdu.data(), 10)).toHex().toUpper();
//        *pb_data++;
        QVariantMap val_map;
        val_map.insert("null-data", QVariant());
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_BOOLEAN: {
        int8_t val = *pb_data++;
        QVariantMap val_map;
        val_map.insert("boolean", (bool)val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_BIT_STRING: {
        uint8_t len = *pb_data++;
        len /= 8;
        QByteArray byteArray = QByteArray(pdu.mid(pb_data - (uint8_t *)pdu.data(), len));
        QString bits;
        for (int i = 0; i < byteArray.count(); ++i) {
            char bt = byteArray.at(i);
            for (int b = 0; b < 8; b++) {
                bits.append(((bt << b) & 0x80)?"1":"0");
            }
        }
        QVariantMap val_map;
        val_map.insert("bit-string", bits);
        out.second = val_map;
        pb_data += len;
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT32: {
        uint32_t val = 0;
        val += *pb_data++;
        val <<= 8;
        val += *pb_data++;
        val <<= 8;
        val += *pb_data++;
        val <<= 8;
        val += *pb_data++;
        QVariantMap val_map;
        val_map.insert("double-long", (int32_t)val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT32: {
        uint32_t val = 0;
        val += *pb_data++;
        val <<= 8;
        val += *pb_data++;
        val <<= 8;
        val += *pb_data++;
        val <<= 8;
        val += *pb_data++;
        QVariantMap val_map;
        val_map.insert("double-long-unsigned", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_OCTET_STRING: {
        uint8_t len = *pb_data++;
        QVariantMap val_map;
        val_map.insert("octet-string", QByteArray(pdu.mid(pb_data - (uint8_t *)pdu.data(), len)).toHex().toUpper());
        out.second = val_map;
        pb_data += len;
        break;
    }
    case DLMS_PDU_DATA_TYPE_STRING: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_BINARY_CODED_DESIMAL: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_STRING_UTF8:{ log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_INT8: {
        int8_t val = *pb_data++;
        QVariantMap val_map;
        val_map.insert("integer", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT16: {
        uint16_t val = (*pb_data++) << 8;
        val += *pb_data++;
        QVariantMap val_map;
        val_map.insert("long", (int16_t)val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT8: {
        uint8_t val = *pb_data++;
        QVariantMap val_map;
        val_map.insert("unsigned", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT16: {
        uint16_t val = (*pb_data++) << 8;
        val += *pb_data++;
        QVariantMap val_map;
        val_map.insert("long-unsigned", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT64: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_UINT64: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_ENUM: {
//        log_1 << pdu_data_type << pdu.size() << QByteArray(pdu.mid(pb_data - (uint8_t *)pdu.data(), 10)).toHex().toUpper();
        uint8_t val = *pb_data++;
//        log_1 << val;
        QVariantMap val_map;
        val_map.insert("enum", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_FLOAT32: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_FLOAT64: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_DATETIME: {
        uint8_t len = QByteArray::fromHex("07E6090F0407320000FF4C00").size();
        QVariantMap val_map;
        val_map.insert("date-time", QByteArray(pdu.mid(pb_data - (uint8_t *)pdu.data(), len)).toHex().toUpper());
        out.second = val_map;
        pb_data += len;
//        log_1 << "unknow" << pdu_data_type;
        break;
    }
    case DLMS_PDU_DATA_TYPE_DATE: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_TIME: { log_1 << "unknow" << pdu_data_type; break; }
    case DLMS_PDU_DATA_TYPE_ARRAY: {
        uint32_t arr_len = *pb_data++;
        if (arr_len == 0x82) {
            arr_len = (*pb_data++) << 8;
            arr_len += *pb_data++;
        }
        QVariantList val;
        for (uint32_t i = 0; i < arr_len; ++i) {
            QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(pdu.mid(pb_data - (uint8_t *)pdu.data(), -1));
            pb_data += out_pdu_data_reader.first;
            val.append(out_pdu_data_reader.second);
        }
        QVariantMap val_map;
        val_map.insert("array", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_STRUCTURE: {
        uint32_t struct_len = *pb_data++;
        if (struct_len == 0x82) {
            struct_len = (*pb_data++) << 8;
            struct_len += *pb_data++;
        }
//        QVariantMap val;
        QVariantList val;
        for (uint32_t i = 0; i < struct_len; ++i) {
            QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(pdu.mid(pb_data - (uint8_t *)pdu.data(), -1));
            pb_data += out_pdu_data_reader.first;
            val.append(out_pdu_data_reader.second);
//            QVariantMap val_tmp_map;
//            val_tmp_map = out_pdu_data_reader.second.toMap();
//            for (auto iter = val_tmp_map.begin(); iter != val_tmp_map.end(); ++iter) {
//                if (!val.contains(iter.key())) {
//                    val.insert(iter.key(), iter.value());
//                } else {
//                    val.insert(iter.key()+"!", iter.value());
//                }
//            }
        }
        QVariantMap val_map;
        val_map.insert("structure", val);
        out.second = val_map;
        break;
    }
    case DLMS_PDU_DATA_TYPE_COMPACT_ARRAY: { log_1 << "unknow" << pdu_data_type; break; }
    default: { log_1 << "unknow !!!!! " << pdu_data_type << pdu.toHex().toUpper(); break; }
    }
    out.first = pb_data - (uint8_t *)pdu.data();
//    out.first = pdu.mid(pb_data - (uint8_t *)pdu.data(), -1);
    log_1 << qPrintable(QJsonDocument::fromVariant(out.second).toJson());
    return out;
}

QByteArray HDLC_DLMS_exchange::DLMS_QVariantMap_to_PDU(QVariantMap vpdu)
{
    QByteArray out;
    if (vpdu.contains("get-request")) {
        out += DLMS_COMMAND_GET_REQUEST;
        vpdu = vpdu.value("get-request").toMap();
        if (vpdu.contains("get-request-normal")) {
            out += DLMS_GET_COMMAND_TYPE_NORMAL;
            vpdu = vpdu.value("get-request-normal").toMap();
            if (vpdu.contains("invoke-id-and-priority")) {
                out += (char)((vpdu.take("invoke-id-and-priority").toUInt()) & 0xFF);
            }
            if (vpdu.contains("cosem-attribute-descriptor")) {
                QVariantMap vpdu_cad = vpdu.take("cosem-attribute-descriptor").toMap();
                if (vpdu_cad.contains("class-id")) {
                    uint16_t class_id = vpdu_cad.take("class-id").toUInt();
                    out += (class_id >> 8) & 0xFF;
                    out += (class_id >> 0) & 0xFF;
                }
                if (vpdu_cad.contains("instance-id")) {
                    QString instance_id = vpdu_cad.take("instance-id").toString();
                    if (instance_id.contains(".")) {
                        QByteArray arr;
                        foreach (QString str, instance_id.split(".")) {
                            arr += (char)str.toUInt();
                        }
                        out += arr;
                    } else {
                        QByteArray arr = QByteArray::fromHex(instance_id.toLocal8Bit());
                        if (arr.size() != 6) {
                            log_1 << "error len OBIS" << arr.size() << arr.toHex().toUpper();
                            return QByteArray();
                        }
                        out += arr;
                    }
                }
                if (vpdu_cad.contains("attribute-id")) {
                    uint8_t attribute_id = vpdu_cad.take("attribute-id").toUInt();
                    out += (char)attribute_id;
                }
                if (!vpdu_cad.isEmpty()) {
                    log_1 << qPrintable(QJsonDocument::fromVariant(vpdu_cad).toJson());
                }
            }
            if (vpdu.contains("access-selection")) {
                //todo

        //        <x:access-selection>
        //          <x:access-selector>2</x:access-selector>
        //          <x:access-parameters>
        //            <x:structure>
        //              <x:double-long-unsigned>0</x:double-long-unsigned>
        //              <x:double-long-unsigned>1</x:double-long-unsigned>
        //              <x:long-unsigned>1</x:long-unsigned>
        //              <x:long-unsigned>0</x:long-unsigned>
        //            </x:structure>
        //          </x:access-parameters>
        //        </x:access-selection>

        //        <x:access-selection>
        //          <x:access-selector>1</x:access-selector>
        //          <x:access-parameters>
        //            <x:structure>
        //              <x:structure>
        //                <x:long-unsigned>8</x:long-unsigned>
        //                <!--0.0.1.0.0.255-->
        //                <x:octet-string>0000010000FF</x:octet-string>
        //                <x:integer>2</x:integer>
        //                <x:long-unsigned>0</x:long-unsigned>
        //              </x:structure>
        //              <!--2018-04-02 00:00:00-->
        //              <x:octet-string>07E204020100000000FF4C00</x:octet-string>
        //              <!--2018-04-03 23:59:59-->
        //              <x:octet-string>07E2040302173B3B00FF4C00</x:octet-string>
        //              <x:array>
        //              </x:array>
        //            </x:structure>
        //          </x:access-parameters>
        //        </x:access-selection>
            } else {
                out += (char)0x00;
            }
        } else
        if (vpdu.contains("get-request-next")) {
            out += DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK;
            vpdu = vpdu.value("get-request-next").toMap();
            if (vpdu.contains("invoke-id-and-priority")) {
                out += (char)((vpdu.take("invoke-id-and-priority").toUInt()) & 0xFF);
            }
            if (vpdu.contains("block-number")) {
                uint32_t block_number = vpdu.take("block-number").toUInt();
                out += (block_number >> 24) & 0xFF;
                out += (block_number >> 16) & 0xFF;
                out += (block_number >>  8) & 0xFF;
                out += (block_number >>  0) & 0xFF;
            }
        }
    }
    if (vpdu.contains("set-request")) {
        out += DLMS_COMMAND_SET_REQUEST;
        vpdu = vpdu.value("set-request").toMap();
        if (vpdu.contains("set-request-normal")) {
            out += DLMS_GET_COMMAND_TYPE_NORMAL;
            vpdu = vpdu.value("set-request-normal").toMap();
            if (vpdu.contains("invoke-id-and-priority")) {
                out += (char)((vpdu.take("invoke-id-and-priority").toUInt()) & 0xFF);
            }
            if (vpdu.contains("cosem-attribute-descriptor")) {
                QVariantMap vpdu_cad = vpdu.take("cosem-attribute-descriptor").toMap();
                if (vpdu_cad.contains("class-id")) {
                    uint16_t class_id = vpdu_cad.take("class-id").toUInt();
                    out += (class_id >> 8) & 0xFF;
                    out += (class_id >> 0) & 0xFF;
                }
                if (vpdu_cad.contains("instance-id")) {
                    QString instance_id = vpdu_cad.take("instance-id").toString();
                    if (instance_id.contains(".")) {
                        QByteArray arr;
                        foreach (QString str, instance_id.split(".")) {
                            arr += (char)str.toUInt();
                        }
                        out += arr;
                    } else {
                        QByteArray arr = QByteArray::fromHex(instance_id.toLocal8Bit());
                        if (arr.size() != 6) {
                            log_1 << "error len OBIS" << arr.size() << arr.toHex().toUpper();
                            return QByteArray();
                        }
                        out += arr;
                    }
                }
                if (vpdu_cad.contains("attribute-id")) {
                    uint8_t attribute_id = vpdu_cad.take("attribute-id").toUInt();
                    out += (char)attribute_id;
                }
                if (!vpdu_cad.isEmpty()) {
                    log_1 << qPrintable(QJsonDocument::fromVariant(vpdu_cad).toJson());
                }
            }
            if (vpdu.contains("value")) {
                out += (char)0x00;
                QVariantMap vpdu_value = vpdu.take("value").toMap();
                if (vpdu_value.contains("octet-string")) {
                    QByteArray arr = QByteArray::fromHex(vpdu_value.value("octet-string").toString().toLocal8Bit());
                    out += (char)0x09;
                    out += (char)arr.size();
                    out += arr;
                }
            } else {
                out += (char)0x00;
            }
        }
        //    C1 01 C1 00 01 00 00 60 01 FE FF 02 00 09 02 EF 06
        //    <x:set-request>
        //      <x:set-request-normal>
        //        <x:invoke-id-and-priority>193</x:invoke-id-and-priority>
        //        <x:cosem-attribute-descriptor>
        //          <!--DATA-->
        //          <x:class-id>1</x:class-id>
        //          <!--0.0.96.1.254.255-->
        //          <x:instance-id>00006001FEFF</x:instance-id>
        //          <x:attribute-id>2</x:attribute-id>
        //        </x:cosem-attribute-descriptor>
        //        <x:value>
        //          <x:octet-string>EF06</x:octet-string>
        //        </x:value>
        //      </x:set-request-normal>
        //    </x:set-request>
//        log_1 << out.toHex().toUpper();
    }
    if (vpdu.contains("aarq")) {
        out += DLMS_COMMAND_AARQ;
        vpdu = vpdu.value("aarq").toMap();
        //601DA109060760857405080101BE10040E01000000065F1F0400001E1DFFFF
        QByteArray arr_tmp;
        if (vpdu.contains("application-context-name")) {
            arr_tmp += 0xA1;
            arr_tmp += 0x09;
            arr_tmp += QByteArray::fromHex("0607608574050801");
            arr_tmp += (char)vpdu.value("application-context-name", 0).toUInt();
        }
        if (vpdu.contains("sender-acse-requirements")) {
            arr_tmp += 0x8A;
            arr_tmp += 0x02;
            arr_tmp += 0x07;
            arr_tmp += 0x80;
        }
        if (vpdu.contains("mechanism-name")) {
            arr_tmp += QByteArray::fromHex("8B07608574050802");
            arr_tmp += (char)vpdu.value("mechanism-name", 0).toUInt();
        }
        if (vpdu.contains("calling-authentication-value")) {
            QByteArray pass = QByteArray::fromHex(vpdu.value("calling-authentication-value", QVariantMap()).toMap().value("charstring", QString()).toString().toLocal8Bit());
            arr_tmp += 0xAC;
            arr_tmp += pass.size()+2;
            arr_tmp += 0x80;
            arr_tmp += pass.size();
            arr_tmp += pass;
        }
        if (vpdu.contains("user-information")) {
            arr_tmp += 0xBE;
            QByteArray arr_tmp_2 = QByteArray::fromHex(vpdu.value("user-information", "").toString().toLocal8Bit());
            arr_tmp += arr_tmp_2.size()+2;
            arr_tmp += 0x04;
            arr_tmp += arr_tmp_2.size();
            arr_tmp += arr_tmp_2;
        }
        out += arr_tmp.size();
        out += arr_tmp;
    }

//    if (!vpdu.isEmpty()) {
//        log_1 << qPrintable(QJsonDocument::fromVariant(vpdu).toJson());
//    }
    return out;
}
QVariantMap HDLC_DLMS_exchange::DLMS_PDU_to_QVariantMap(QByteArray pdu)
{
    log_1 << "PDU" << pdu.toHex().toUpper();

    QVariantMap vout;
    uint8_t * pb_data = (uint8_t *)pdu.data();
    uint8_t header = *pb_data++;
    switch (header) {
    case DLMS_COMMAND_AARQ: {
        pb_data++; // get len;

        uint8_t tag;
        uint8_t size;
        QVariantMap vmap_aarq;
        while (pdu.size() > (pb_data - (uint8_t *)pdu.data())) {
            tag = *pb_data++;
            size = *pb_data++;
            switch (tag) {
            case 0x8A: {
                if (size != 2 || (*pb_data != 0x07) || (*(pb_data+1) != 0x80)) {
                    log_1 << "error 8A tag data";
                    break;
                }
                vmap_aarq.insert("sender-acse-requirements", 1);
                break;
            }
            case 0x8B: {
                if (size == 7) {
                    uint8_t auth_lvl = *(pb_data + 6);
                    vmap_aarq.insert("mechanism-name", auth_lvl);
                }
                break;
            }
            case 0xA1: {
                if (size == 9) {
                    uint8_t val = *(pb_data+8);
                    vmap_aarq.insert("application-context-name", val);
                }
                break;
            }
            case 0xAC: {
                if (size < 2) {
                    break;
                }
                QByteArray arr_val((const char*)pb_data+2, size-2);
                QVariantMap vmap_aarq_ext;
                vmap_aarq_ext.insert("charstring", QString(arr_val.toHex().toUpper()));
                vmap_aarq.insert("calling-authentication-value", vmap_aarq_ext);
                break;
            }
            case 0xBE: {
                if (size == 16) {
                    QByteArray arr_val((const char*)pb_data+2, size-2);
                    vmap_aarq.insert("user-information", QString(arr_val.toHex().toUpper()));
                }
                break;
            }
            default:
                log_1 << "unknow header AARQ" << QString::number(tag, 16) << QByteArray((const char*)pb_data, size).toHex(' ').toUpper();
                break;
            }
//            log_1 << tag << size << QByteArray((const char*)pb_data, size).toHex().toUpper();
            pb_data += size;
        }
//        <x:aarq>
//          <x:application-context-name>1</x:application-context-name>
//          <x:sender-acse-requirements>1</x:sender-acse-requirements>
//          <x:mechanism-name>1</x:mechanism-name>
//          <x:calling-authentication-value>
//            <x:charstring>526561646572</x:charstring>
//          </x:calling-authentication-value>
//          <x:user-information>01000000065F1F0400001E1DFFFF</x:user-information>
//        </x:aarq>
        vout.insert("aarq", vmap_aarq);
//        log_1 << QByteArray((const char*)pb_data, pdu.size() - (pb_data - (uint8_t *)pdu.data())).toHex().toUpper();
        break;
    }
    case DLMS_COMMAND_AARE: {
        pb_data++; // get len;
        uint8_t tag;
        uint8_t size;
        QVariantMap vmap_aare;
        while (pdu.size() > (pb_data - (uint8_t *)pdu.data())) {
            tag = *pb_data++;
            size = *pb_data++;
            switch (tag) {
            case 0xA1: {
                if (size == 9) {
                    uint8_t val = *(pb_data+size-1);
                    vmap_aare.insert("application-context-name", val);
                }
                break;
            }
            case 0xA2: {
                if (size == 3) {
                    uint8_t val = *(pb_data+size-1);
                    vmap_aare.insert("result", val);
                }
                break;
            }
            case 0xA3: {
                if (size == 5) {
                    uint8_t val = *(pb_data+size-1);
                    QVariantMap vm;
                    vm.insert("acse-service-user", val);
                    if (*pb_data == 0xA1) {
                        vmap_aare.insert("result-source-diagnostic", vm);
                    }
                }
//                log_1 << QString::number(tag, 16).toUpper() << size << QByteArray((const char*)pb_data, size).toHex().toUpper();
                break;
            }
            case 0xBE: {
                if (size == 16) {
                    QByteArray arr_val((const char*)pb_data+2, size-2);
                    vmap_aare.insert("user-information", QString(arr_val.toHex().toUpper()));
                }
                break;
            }
            default:
                log_1 << "unknow header AARE" << QString::number(tag, 16).toUpper();
                break;
            }
//            log_1 << tag << size << QByteArray((const char*)pb_data, size).toHex().toUpper();
            pb_data += size;
        }
        vout.insert("aare", vmap_aare);
        break;
    }

    case DLMS_COMMAND_GET_REQUEST: {
        QVariantMap vm_GET_REQUEST;
        uint8_t sub_header = *pb_data++;
        switch (sub_header) {
        case DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK: {
            QVariantMap vm_GET_COMMAND_TYPE_NEXT_DATA_BLOCK;
            uint8_t invoke_id_and_priority = *pb_data++;
            vm_GET_COMMAND_TYPE_NEXT_DATA_BLOCK.insert("invoke-id-and-priority", invoke_id_and_priority);
            uint32_t block_number = *pb_data++;
            block_number <<= 8;
            block_number += *pb_data++;
            block_number <<= 8;
            block_number += *pb_data++;
            block_number <<= 8;
            block_number += *pb_data++;
            vm_GET_COMMAND_TYPE_NEXT_DATA_BLOCK.insert("block-number", block_number);
            vm_GET_REQUEST.insert("get-request-next", vm_GET_COMMAND_TYPE_NEXT_DATA_BLOCK);
            break;
        }
        default: break;
        }
        vout.insert("get-request", vm_GET_REQUEST);
        break;
    }
//        <x:get-request>
//          <x:get-request-next>
//            <x:invoke-id-and-priority>129</x:invoke-id-and-priority>
//            <x:block-number>1</x:block-number>
//          </x:get-request-next>
//        </x:get-request>
    case DLMS_COMMAND_GET_RESPONSE: {
        QVariantMap vm_GET_RESPONSE;
        uint8_t sub_header = *pb_data++;
        switch (sub_header) {
        case DLMS_GET_COMMAND_TYPE_NORMAL: {
            QVariantMap vm_GET_COMMAND_TYPE_NORMAL;
            uint8_t invoke_id_and_priority = *pb_data++;
            vm_GET_COMMAND_TYPE_NORMAL.insert("invoke-id-and-priority", invoke_id_and_priority);
            uint8_t pdu_result = *pb_data++;
            QVariantMap vm_result;
            if (pdu_result) {
                pdu_result = *pb_data++;
                switch (pdu_result) {
                case PDU_DataAccessResult_Success:                      vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_HardwareFault:                vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_TemporaryFailure:             vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ReadWriteDenied:              vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ObjectUndefined:              vm_result.insert("data-access-result", "object-undefined"); break;
                case PDU_DataAccessResult_ObjectClassInconsistent:      vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ObjectUnavailable:            vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_TypeUnmatched:                vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ScopeOfAccessViolated:        vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_DataBlockUnavailable:         vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_LongGetOrReadAborted:         vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_NoLongGetOrReadInProgress:    vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_LongSetOrWriteAborted:        vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_NoLongSetOrWriteInProgress:   vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_DataBlockNumberInvalid:       vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_OtherReason:                  vm_result.insert("data-access-result", pdu_result); break;
                default: break;
                }
            } else {
                QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(pdu.mid(pb_data - (uint8_t *)pdu.data(), -1));
//                log_1 << out_pdu_data_reader.first << qPrintable(QJsonDocument::fromVariant(out_pdu_data_reader.second).toJson());
                vm_result.insert("data", out_pdu_data_reader.second);
            }
            vm_GET_COMMAND_TYPE_NORMAL.insert("result", vm_result);
            vm_GET_RESPONSE.insert("get-response-normal", vm_GET_COMMAND_TYPE_NORMAL);
            break;
        }
        case DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK: {
            QVariantMap vm_GET_COMMAND_NEXT_DATA_BLOCK;
            uint8_t invoke_id_and_priority = *pb_data++;
            vm_GET_COMMAND_NEXT_DATA_BLOCK.insert("invoke-id-and-priority", invoke_id_and_priority);
            uint8_t last_block = *pb_data++;
            vm_GET_COMMAND_NEXT_DATA_BLOCK.insert("last-block", last_block);
            uint32_t block_index = 0;
            block_index += *pb_data++;
            block_index <<= 8;
            block_index += *pb_data++;
            block_index <<= 8;
            block_index += *pb_data++;
            block_index <<= 8;
            block_index += *pb_data++;
            log_1 << "last_block" << last_block;
            log_1 << "block_index" << block_index;
            vm_GET_COMMAND_NEXT_DATA_BLOCK.insert("block-number", block_index);
            uint8_t pdu_result = *pb_data++;
            QVariantMap vm_result;
            if (pdu_result) {
                pdu_result = *pb_data++;
                switch (pdu_result) {
                case PDU_DataAccessResult_Success:                      vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_HardwareFault:                vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_TemporaryFailure:             vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ReadWriteDenied:              vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ObjectUndefined:              vm_result.insert("data-access-result", "object-undefined"); break;
                case PDU_DataAccessResult_ObjectClassInconsistent:      vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ObjectUnavailable:            vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_TypeUnmatched:                vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ScopeOfAccessViolated:        vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_DataBlockUnavailable:         vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_LongGetOrReadAborted:         vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_NoLongGetOrReadInProgress:    vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_LongSetOrWriteAborted:        vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_NoLongSetOrWriteInProgress:   vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_DataBlockNumberInvalid:       vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_OtherReason:                  vm_result.insert("data-access-result", pdu_result); break;
                default: break;
                }
            } else {
                uint16_t len = *pb_data++;
                if (len == 0x82) {
                    len = *pb_data++;
                    len <<= 8;
                    len += *pb_data++;
                }

                vm_GET_COMMAND_NEXT_DATA_BLOCK.insert("block-len", len);

             //   log_1 << "pdu.mid" << pdu.mid(pb_data - (uint8_t *)pdu.data(), 20).toHex().toUpper();
             //   QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(pdu.mid(pb_data - (uint8_t *)pdu.data(), -1));
                QByteArray arr = pdu.mid(pb_data - (uint8_t *)pdu.data(), -1).toHex();
           //     log_1 << "out_pdu_data_reader" << out_pdu_data_reader.first << qPrintable(QJsonDocument::fromVariant(out_pdu_data_reader.second).toJson());
                vm_result.insert("data", arr);
            }
            vm_GET_COMMAND_NEXT_DATA_BLOCK.insert("result", vm_result);
            vm_GET_RESPONSE.insert("get-response-with-data-block", vm_GET_COMMAND_NEXT_DATA_BLOCK);
            break;
        }
        default: break;
        }
        vout.insert("get-response", vm_GET_RESPONSE);
//        log_1 << QByteArray::number(header, 16).toUpper() << pdu.toHex().toUpper();
        break;
    }
    case DLMS_COMMAND_SET_RESPONSE: {
        QVariantMap vm_GET_RESPONSE;
        uint8_t sub_header = *pb_data++;
//        log_1 << sub_header;
        switch (sub_header) {
        case DLMS_GET_COMMAND_TYPE_NORMAL: {
            QVariantMap vm_GET_COMMAND_TYPE_NORMAL;
            uint8_t invoke_id_and_priority = *pb_data++;
            vm_GET_COMMAND_TYPE_NORMAL.insert("invoke-id-and-priority", invoke_id_and_priority);
            uint8_t pdu_result = *pb_data++;
            QVariantMap vm_result;
            if (pdu_result) {
                pdu_result = *pb_data++;
                switch (pdu_result) {
                case PDU_DataAccessResult_Success:                      vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_HardwareFault:                vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_TemporaryFailure:             vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ReadWriteDenied:              vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ObjectUndefined:              vm_result.insert("data-access-result", "object-undefined"); break;
                case PDU_DataAccessResult_ObjectClassInconsistent:      vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ObjectUnavailable:            vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_TypeUnmatched:                vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_ScopeOfAccessViolated:        vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_DataBlockUnavailable:         vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_LongGetOrReadAborted:         vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_NoLongGetOrReadInProgress:    vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_LongSetOrWriteAborted:        vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_NoLongSetOrWriteInProgress:   vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_DataBlockNumberInvalid:       vm_result.insert("data-access-result", pdu_result); break;
                case PDU_DataAccessResult_OtherReason:                  vm_result.insert("data-access-result", pdu_result); break;
                default: break;
                }
                vm_GET_COMMAND_TYPE_NORMAL.insert("result", vm_result);
            } else {
                vm_GET_COMMAND_TYPE_NORMAL.insert("result", "success");
                if (pb_data - (uint8_t *)pdu.data()) {
                    QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(pdu.mid(pb_data - (uint8_t *)pdu.data(), -1));
//                    log_1 << out_pdu_data_reader.first << qPrintable(QJsonDocument::fromVariant(out_pdu_data_reader.second).toJson());
                    vm_GET_COMMAND_TYPE_NORMAL.insert("data", out_pdu_data_reader.second);
                }
            }
            vm_GET_RESPONSE.insert("set-response-normal", vm_GET_COMMAND_TYPE_NORMAL);
            break;
        }
        default: break;
        }
        vout.insert("set-response", vm_GET_RESPONSE);
//        log_1 << QByteArray::number(header, 16).toUpper() << pdu.toHex().toUpper();
        break;
    }
    default: {
        log_1 << "unknow" << QByteArray::number(header, 16).toUpper() << pdu.toHex().toUpper();
        break;
    }
    }
   // log_1 << qPrintable(QJsonDocument::fromVariant(vout).toJson());

    return vout;
}

QVariantMap HDLC_DLMS_exchange::DLMS_PDU_to_QVariantMap_append(QByteArray pdu, QByteArray data1)
{
  //  log_1 << "PDU1" << pdu.toHex().toUpper();
  //  log_1 << "DATA" << data1.toHex().toUpper();

    QVariantMap vout;
    uint8_t * pb_data = (uint8_t *)pdu.data();
    uint8_t * pb_data1 = (uint8_t *)data1.data();
    uint8_t header = *pb_data++;
    QVariantMap vm_GET_RESPONSE;
    uint8_t sub_header = *pb_data++;
    QVariantMap vm_GET_COMMAND_TYPE_NORMAL;
    uint8_t invoke_id_and_priority = *pb_data++;
    vm_GET_COMMAND_TYPE_NORMAL.insert("invoke-id-and-priority", invoke_id_and_priority);
    uint8_t pdu_result = *pb_data++;
    QVariantMap vm_result;
    QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(data1.mid(pb_data1 - (uint8_t *)data1.data(), -1));
  //  log_1 << out_pdu_data_reader.second << qPrintable(QJsonDocument::fromVariant(out_pdu_data_reader.second).toJson());
    vm_result.insert("data", out_pdu_data_reader.second);
    vm_GET_COMMAND_TYPE_NORMAL.insert("result", vm_result);
    vm_GET_RESPONSE.insert("get-response-normal", vm_GET_COMMAND_TYPE_NORMAL);
    vout.insert("get-response", vm_GET_RESPONSE);
//    log_1 << qPrintable(QJsonDocument::fromVariant(vout).toJson());
    return vout;
}


void HDLC_DLMS_exchange::HDLC_Clear(HDLC_BUF *hdlc)
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
void HDLC_DLMS_exchange::HDLC_TX_add_byte(HDLC_BUF *hdlc, uint8_t c)
{
    hdlc->crc = DLMS_crc_byte(hdlc->crc, c);
//    hdlc->crc = (hdlc->crc >> 8) ^ fcstab[(hdlc->crc ^ c) & 0xff];
//    hdlc->tx(c);
    hdlc_out_buf.append(c);
}
void HDLC_DLMS_exchange::HDLC_Send()
{
    hdlc_out_buf.clear();
    HDLC_BUF *hdlc = hbuf_out;

    uint8_t segmentation = 0;
    uint16_t data_len = 0;
    hdlc->frame_length = 2 + hdlc->serv.bytes4.flag + hdlc->clnt.bytes4.flag + 1 + 2;
//    log_1 << hdlc->frame_length;
    if (!hdlc->segmentation) {
        hdlc->frame_length += (hdlc->data_len?2:0);
        if (!hdlc->data_index) {
            hdlc->frame_length += ((hdlc->LLC_flag && !hdlc->control.bits.is_n_I)?3:0);
        }
//        log_1 << hdlc->frame_length;
//        log_1 << hdlc->frame_length<<hdlc->data_len<<hdlc->data_index << HDLC_PACKET_SIZE___;
        if (hdlc->frame_length + hdlc->data_len - hdlc->data_index > HDLC_PACKET_SIZE___) {
            data_len = HDLC_PACKET_SIZE___ - hdlc->frame_length;
            segmentation = 1;
        } else {
            data_len = hdlc->data_len - hdlc->data_index;
        }
//        log_1 << data_len <<  hdlc->data_len << hdlc->data_index;
        hdlc->frame_length += data_len;
    }
//    log_1 << hdlc->frame_length;
    hdlc_out_buf.append(0x7E);// hdlc->tx(0x7E);
    hdlc->crc = 0xFFFF;
    HDLC_TX_add_byte(hdlc, 0xA0 + ((hdlc->frame_length >> 8) & 0x7) + (segmentation << 3));
    HDLC_TX_add_byte(hdlc, hdlc->frame_length & 0xFF);
    for (int i = hdlc->serv.bytes4.flag - 1; i != -1; i--) {
//        log_1 << "serv" << i;
        HDLC_TX_add_byte(hdlc, (((hdlc->serv.bytes4.addr >> (7 * i)) & 0x7F) << 1) + (i?0:1) );
    }
    for (int i = hdlc->clnt.bytes4.flag - 1; i != -1; i--) {
//        log_1 << "clnt" << i;
        HDLC_TX_add_byte(hdlc, (((hdlc->clnt.bytes4.addr >> (7 * i)) & 0x7F) << 1) + (i?0:1) );
    }
    HDLC_TX_add_byte(hdlc, hdlc->control.control);
    if (!hdlc->segmentation && data_len) {
        hdlc->HCS = hdlc->crc ^ 0xFFFF;
        HDLC_TX_add_byte(hdlc, (hdlc->HCS >> 0) & 0xFF);
        HDLC_TX_add_byte(hdlc, (hdlc->HCS >> 8) & 0xFF);
        if (!hdlc->data_index) {
            if (hdlc->LLC_flag && !hdlc->control.bits.is_n_I) {
                HDLC_TX_add_byte(hdlc, 0xE6);
                HDLC_TX_add_byte(hdlc, 0xE6);
                HDLC_TX_add_byte(hdlc, 0x00);
            }
        }
        for (int i = 0; i < data_len; ++i) {
            HDLC_TX_add_byte(hdlc, hdlc->data_buf[i + hdlc->data_index]);
        }
        hdlc->data_index += data_len;
    }
    hdlc->FCS = hdlc->crc ^ 0xFFFF;
    HDLC_TX_add_byte(hdlc, (hdlc->FCS >> 0) & 0xFF);
    HDLC_TX_add_byte(hdlc, (hdlc->FCS >> 8) & 0xFF);
    hdlc_out_buf.append(0x7E); //hdlc->tx(0x7E);
    if (hdlc->segmentation < segmentation) {
        hdlc->segmentation = segmentation;
    }
    if (!hdlc->mode_connect) {
        if (hdlc->IEC61107_is_use) {
            hdlc->IEC61107_now = 1;
//            if (hdlc->set_baud) {
//                hdlc->set_baud(0);
//            }
        }
    }
}
void HDLC_DLMS_exchange::HDLC_MAC_stringify_controller_cmd(control_field_enum cf)
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
void HDLC_DLMS_exchange::HDLC_MAC_stringify_controller_PDU(QByteArray pdu)
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
void HDLC_DLMS_exchange::HDLC_MAC_LLC_parser(uint8_t c)
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
void HDLC_DLMS_exchange::HDLC_MAC_parser_controller(HDLC_BUF *hdlc)
{
//    log_1 << QString::number(hdlc->control.control, 16).toUpper() << hdlc->segmentation;

    if (0) { // log
        QString str("in  H(%1 %2) Len(%3) SaddrF(%4) Caddr(%5) Ctrl(%6 %7 %8 %9 = %10) Len(%11) HCS(%12 %13) FCS(%14 %15)");
        QString cntrl;
        switch (hdlc->control.control) {
        case cf_SNRM: cntrl="SNRM"; break;
        case cf_DISC: cntrl="DISC"; break;
        case cf_UA:   cntrl="UA";   break;
        case cf_DM:   cntrl="DM";   break;
        case cf_FRMR: cntrl="FRMR"; break;
        case cf_UI:   cntrl="UI";   break;
        default:
            if (!hdlc->control.bits.is_n_I) cntrl="I"; else
            if (hdlc->control.bits.SSS == 0) cntrl="RR"; else
            if (hdlc->control.bits.SSS == 2) cntrl="RNR";
            break;
        }
        QString saddr;
        switch (hdlc->serv.bytes4.flag) {
        case 1: saddr = QString::number(hdlc->serv.bytes1.addr_up_hi,16); break;
        case 2: saddr = QString::number(hdlc->serv.bytes1.addr_up_lo,16) + " " + QString::number(hdlc->serv.bytes1.addr_up_hi,16); break;
        case 4: saddr = QString::number(hdlc->serv.bytes2.addr_lo,16) + " " + QString::number(hdlc->serv.bytes2.addr_up,16); break;
        default: saddr = QString::number(hdlc->serv.bytes4.addr,16); break;
        }
        QString caddr;
        switch (hdlc->clnt.bytes4.flag) {
        case 1: caddr = QString::number(hdlc->clnt.bytes1.addr_up_hi,16); break;
        case 2: caddr = QString::number(hdlc->clnt.bytes1.addr_up_lo,16) + " " + QString::number(hdlc->clnt.bytes1.addr_up_hi,16); break;
        case 4: caddr = QString::number(hdlc->clnt.bytes2.addr_lo,16) + " " + QString::number(hdlc->clnt.bytes2.addr_up,16); break;
        default: caddr = QString::number(hdlc->clnt.bytes4.addr,16); break;
        }

        log_2 << str.arg(hdlc->format_type, 0, 16).arg(hdlc->segmentation).arg(hdlc->frame_length).arg(saddr).arg(caddr)
                 .arg(hdlc->control.bits.RRR).arg(hdlc->control.bits.P_F).arg(hdlc->control.bits.SSS).arg(hdlc->control.bits.is_n_I)
                 .arg(cntrl).arg(hdlc->frame_byte_counter)
                 .arg(hdlc->HCS,0,16).arg(hdlc->calc_HCS,0,16).arg(hdlc->FCS,0,16).arg(hdlc->crc,0,16) << "data_len" << hdlc->data_len;
//        log_2 << "req " << QByteArray((const char*)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
//        log_1 << hdlc->format_type << hdlc->segmentation << hdlc->frame_length;
//        log_1 << hdlc->segmentation;
    }

    hdlc_in_buf_data += QByteArray((const char*)hdlc->data_buf, hdlc->data_len);
    if (hdlc->segmentation) {
        hbuf_out->control.bits.RRR = hbuf_in->control.bits.RRR;
        hbuf_out->control_clt.bits.RRR++;
        HDLC_Clear(hbuf_in);
        HDLC_MAC_stringify_controller_cmd(cf_SSS_RR);
        HDLC_Send();
        log_1 << hdlc_out_buf.toHex().toUpper();
        emit signal_HDLC_to_device(hdlc_out_buf);

//        HDLC_MAC_stringify_controller_cmd(cf_SSS_RR);
        return;
    }
    if (hdlc->control.control == cf_UA) {
        log_1 << "cf_UA";
        QVariantMap vpdu;
        vpdu.insert("UA", QVariantMap());
        emit signal_PDU_from_device(vpdu);
        hdlc_in_buf_data.clear();
        return;
    }
    if (!hdlc->control.bits.is_n_I) {
//        emit signal_PDU_from_device(DLMS_PDU_to_QVariantMap(QByteArray((const char *)hdlc->data_buf, hdlc->data_len)));
        log_1 << hdlc_in_buf_data.toHex().toUpper();
        QVariantMap vm = DLMS_PDU_to_QVariantMap(hdlc_in_buf_data);
     //   log_1 << qPrintable(QJsonDocument::fromVariant(vm).toJson());
        QVariantMap vm1 = vm;
        if (vm.contains("get-response")){
            vm = vm.value("get-response", QVariantMap()).toMap();
            if (vm.contains("get-response-with-data-block")){
                vm = vm.value("get-response-with-data-block", QVariantMap()).toMap();
                int block_number = vm["block-number"].toInt();
                int last_block = vm["last-block"].toInt();
                if (last_block == 0){
                    vm = vm.value("result", QVariantMap()).toMap();
                    if (vm.contains("data")) buf_block = QByteArray::fromHex(vm.value("data", "").toString().toLocal8Bit());
                    log_1 << "buf_block 1" << buf_block.toHex().toUpper();
                    QByteArray arr_send = QByteArray::fromHex("C00281000000");
                    arr_send = arr_send.append(block_number);
                    slot_HDLC_MAC_stringify_controller_PDU (arr_send);
                }
                else{
                    vm = vm.value("result", QVariantMap()).toMap();
                    QByteArray arr;
                    if (vm.contains("data")) arr = QByteArray::fromHex(vm.value("data", "").toString().toLocal8Bit());
                    log_1 << "buf_block 2" << arr.toHex().toUpper();
                    buf_block = buf_block.append(arr);
                    log_1 << "buf_block summ" << buf_block.toHex().toUpper();
                    uint8_t * pb_data = (uint8_t *)buf_block.data();
                    QPair<uint32_t, QVariant> out_pdu_data_reader = pdu_data_reader(buf_block.mid(pb_data - (uint8_t *)buf_block.data(), -1));
                    vm.insert("data", out_pdu_data_reader.second);
                    vm = vm.value("data", QVariantMap()).toMap();
                 //   log_1 << hdlc_in_buf_data.toHex().toUpper();
                    emit signal_PDU_from_device(DLMS_PDU_to_QVariantMap_append(hdlc_in_buf_data, buf_block));
                }
            }
            else emit signal_PDU_from_device(vm1);
        }
        else emit signal_PDU_from_device(vm);
        hdlc_in_buf_data.clear();
    }
//    for (;;) {
//        if (hdlc->frame_byte_counter >= HDLC_PACKET_SIZE) { // long packet
//            hdlc->control.control = cf_FRMR;
//            hdlc->data_len = 0;
//            break;
//        }
//        if (hdlc->segmentation) {
//            hdlc->control.bits.RRR = ++hdlc->control_srv.bits.RRR;
//            hdlc->control.bits.SSS = cf_SSS_RR;
//            hdlc->control.bits.is_n_I = 1;
//            break;
//        }
//        if (hdlc->control.bits.is_n_I) { // cmd
//            switch (hdlc->control.bits.SSS) {
//            case cf_SSS_RR: {
//                if (hdlc->mode_connect) {
//                    if (hdlc->control.bits.RRR == hdlc->control_clt.bits.RRR) {
//                        if (hdlc->data_index == hdlc->data_len) {
//                            hdlc->control.bits.SSS = cf_SSS_RR;
//                        } else {
//                            hdlc->control.bits.is_n_I = 0;
//                            hdlc->control_clt.bits.RRR++;
//                            hdlc->control.bits.SSS = hdlc->control_srv.bits.SSS++;
//                            hdlc->control.bits.RRR = ++hdlc->control_srv.bits.RRR;
//                        }
//                    } else {
//                        hdlc->control.control = cf_FRMR;
//                        hdlc->data_len = 0;
//                        hdlc->data_index = 0;
//                    }
//                } else {
//                    hdlc->control.control = cf_FRMR;
//                    hdlc->data_len = 0;
//                    hdlc->data_index = 0;
//                }
//                break;
//            }
//            case cf_SSS_RNR: {
//                hdlc->control_clt.bits.RRR++;
////                printf("RNR");//log_1 << QString::number(hdlc->control.control, 16).toUpper() << "RNR";
//                break;
//            }
//            default: {
//                switch (hdlc->control.control | 0x10) {
//                case cf_SNRM: {
//                    hdlc->mode_connect = 1;
//                    hdlc->data_len = 0;
//                    hdlc->control.control = cf_UA;
//                    hdlc->data_buf[hdlc->data_len++] = 0x81; // format identifier
//                    hdlc->data_buf[hdlc->data_len++] = 0x80; // group identifier
//                    uint8_t * data_group_len = &hdlc->data_buf[hdlc->data_len++]; *data_group_len = 0;
//                    const uint8_t ua_HDLC_parameter[] = {0x05,0x02,0x00,0x80,0x06,0x02,0x00,0x80,0x07,0x04,0x00,0x00,0x00,0x01,0x08,0x04,0x00,0x00,0x00,0x01};
//                    memmove(&hdlc->data_buf[hdlc->data_len], ua_HDLC_parameter, sizeof(ua_HDLC_parameter));
//                    hdlc->data_len+=sizeof(ua_HDLC_parameter);
//                    (*data_group_len) = sizeof(ua_HDLC_parameter);

//                    hdlc->control_srv.control = 0;
//                    hdlc->control_clt.control = 0;
//                    break;
//                }
//                case cf_DISC: {
//                    hdlc->data_len = 0;
//                    switch (hdlc->mode_connect) {
//                    case 1: hdlc->control.control = cf_UA; hdlc->mode_connect = 0; break;
//                    default: hdlc->control.control = cf_DM; break;
//                    }
//                    hdlc->mode_connect = 0;
//                    memset(&hdlc->pdu_ch, 0, sizeof(PDU_channel));
//                    break;
//                }
//                default: {
////                    printf("control unknow");//log_1 << QString::number(hdlc->control.control, 16).toUpper() << "control unknow";
//                    hdlc->control.control = cf_FRMR;
//                    hdlc->data_len = 0;
//                }
//                }
//                break;
//            }
//            }
//            break;
//        }
//        if (!hdlc->mode_connect) {
////            printf("error mode_connect\r\n");
//            hdlc->control.control = cf_DM;
//            hdlc->data_len = 0;
//            hdlc->data_index = 0;
//            return;
//            //break;
//        }
//        if (hdlc->control.bits.RRR != hdlc->control_clt.bits.RRR) {
////            printf("RRR != RRR get\r\n");// << hdlc->control.bits.RRR << "need" << hdlc->control_clt.bits.RRR;
//            hdlc->control.bits.SSS = cf_SSS_RR;
//            hdlc->control.bits.is_n_I = 1;
//            hdlc->data_len = 0;
//            hdlc->data_index = 0;
//            break;
//        }
//        if (hdlc->control.bits.SSS != hdlc->control_clt.bits.SSS) {
////            printf("SSS != SSS get\r\n");// << hdlc->control.bits.SSS << "need" << hdlc->control_clt.bits.SSS;
//            hdlc->control.bits.SSS = cf_SSS_RR;
//            hdlc->control.bits.is_n_I = 1;
//            hdlc->data_len = 0;
//            hdlc->data_index = 0;
//            break;
//        }
//        hdlc->control_clt.bits.RRR++;
//        hdlc->control_clt.bits.SSS++;
////        log_1 << "pdu in " << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).size() << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
//        if (DLMS_pdu) {
//            DLMS_pdu(hdlc);
//        }
////        log_1 << "pdu out" << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).size() << QByteArray((const char *)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
//        hdlc->control.bits.RRR = ++hdlc->control_srv.bits.RRR;
//        hdlc->control.bits.SSS = hdlc->control_srv.bits.SSS++;
//        break;
//    }
//    if (!hdlc->mode_connect) {
//        hdlc->control_srv.control = 0;
//        hdlc->control_clt.control = 0;
//    }
//    if (hdlc->control.control == cf_FRMR) {
//        hdlc->control_srv.control = 0;
//    }
//    //    log_2 << "resp" << QByteArray((const char*)hdlc->data_buf, hdlc->data_len).toHex().toUpper();
//    DLMS_HDLC_Send(hdlc);
}

void HDLC_DLMS_exchange::slot_connect(uint32_t server, uint32_t client, QByteArray pass)
{
    memset(hbuf_out, 0, sizeof(HDLC_BUF));
    memset(hbuf_in, 0, sizeof(HDLC_BUF));
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

void HDLC_DLMS_exchange::slot_PDU_to_device(QVariant vpdu)
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

void HDLC_DLMS_exchange::slot_HDLC_from_device(QByteArray data)
{
    log_1 << data.toHex().toUpper() << data.size();
    for (int i = 0; i < data.size(); ++i) {
//        log_1 << hbuf_in->mode_frame;
        HDLC_MAC_LLC_parser(data[i]);
    }
}
