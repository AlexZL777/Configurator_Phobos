#include "DLMS_PDU.h"
#include <string.h>
#include <stdio.h>
#include "DLMS_AES.h"
#include "DLMS_obis_pack.h"
#include "meter.h"

typedef enum {
    PDU_DLMS_SOURCE_DIAGNOSTIC_NONE = 0,
    PDU_DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN = 1,
    PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED = 2,
    PDU_DLMS_SOURCE_DIAGNOSTIC_3 = 3,
    PDU_DLMS_SOURCE_DIAGNOSTIC_4 = 4,
    PDU_DLMS_SOURCE_DIAGNOSTIC_5 = 5,
    PDU_DLMS_SOURCE_DIAGNOSTIC_6 = 6,
    PDU_DLMS_SOURCE_DIAGNOSTIC_7 = 7,
    PDU_DLMS_SOURCE_DIAGNOSTIC_8 = 8,
    PDU_DLMS_SOURCE_DIAGNOSTIC_9 = 9,
    PDU_DLMS_SOURCE_DIAGNOSTIC_10 = 10,
    PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_NOT_RECOGNISED = 11,
    PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_MECHANISM_NAME_REQUIRED = 12,
    PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE = 13,
    PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED = 14,
} PDU_DLMS_SOURCE_DIAGNOSTIC;

typedef enum {
    DLMS_BER_TYPE_EOC = 0x00,
    DLMS_BER_TYPE_BOOLEAN = 0x1,
    DLMS_BER_TYPE_INTEGER = 0x2,
    DLMS_BER_TYPE_BIT_STRING = 0x3,
    DLMS_BER_TYPE_OCTET_STRING = 0x4,
    DLMS_BER_TYPE_NULL = 0x5,
    DLMS_BER_TYPE_OBJECT_IDENTIFIER = 0x6,
    DLMS_BER_TYPE_OBJECT_DESCRIPTOR = 7,
    DLMS_BER_TYPE_EXTERNAL = 8,
    DLMS_BER_TYPE_REAL = 9,
    DLMS_BER_TYPE_ENUMERATED = 10,
    DLMS_BER_TYPE_UTF8_STRING = 12,
    DLMS_BER_TYPE_NUMERIC_STRING = 18,
    DLMS_BER_TYPE_PRINTABLE_STRING = 19,
    DLMS_BER_TYPE_TELETEX_STRING = 20,
    DLMS_BER_TYPE_VIDEOTEX_STRING = 21,
    DLMS_BER_TYPE_IA5_STRING = 22,
    DLMS_BER_TYPE_UTC_TIME = 23,
    DLMS_BER_TYPE_GENERALIZED_TIME = 24,
    DLMS_BER_TYPE_GRAPHIC_STRING = 25,
    DLMS_BER_TYPE_VISIBLE_STRING = 26,
    DLMS_BER_TYPE_GENERAL_STRING = 27,
    DLMS_BER_TYPE_UNIVERSAL_STRING = 28,
    DLMS_BER_TYPE_BMP_STRING = 30,
    DLMS_BER_TYPE_APPLICATION = 0x40,
    DLMS_BER_TYPE_CONTEXT = 0x80,
    DLMS_BER_TYPE_PRIVATE = 0xc0,
    DLMS_BER_TYPE_CONSTRUCTED = 0x20
} DLMS_BER_TYPE;

typedef enum {
    DLMS_PDU_TYPE_PROTOCOL_VERSION = 0,
    DLMS_PDU_TYPE_APPLICATION_CONTEXT_NAME = 1,
    DLMS_PDU_TYPE_CALLED_AP_TITLE = 2,
    DLMS_PDU_TYPE_CALLED_AE_QUALIFIER = 3,
    DLMS_PDU_TYPE_CALLED_AP_INVOCATION_ID = 4,
    DLMS_PDU_TYPE_CALLED_AE_INVOCATION_ID = 5,
    DLMS_PDU_TYPE_CALLING_AP_TITLE = 6,
    DLMS_PDU_TYPE_CALLING_AE_QUALIFIER = 7,
    DLMS_PDU_TYPE_CALLING_AP_INVOCATION_ID = 8,
    DLMS_PDU_TYPE_CALLING_AE_INVOCATION_ID = 9,
    DLMS_PDU_TYPE_SENDER_ACSE_REQUIREMENTS = 10,
    DLMS_PDU_TYPE_MECHANISM_NAME = 11,
    DLMS_PDU_TYPE_CALLING_AUTHENTICATION_VALUE = 12,
    DLMS_PDU_TYPE_IMPLEMENTATION_INFORMATION = 29,
    DLMS_PDU_TYPE_USER_INFORMATION = 30
} DLMS_PDU_TYPE;

uint8_t COSEM_GET_AttributeAccess(PDU_channel *pdu_ch, const COSEM_OBJECT_Attribute *attr)
{
    if (!attr) return DLMS_ACCESS_MODE_NONE;
    if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_NONE) {
        return attr->access_public;
    }
    if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_LOW) {
        return attr->access_reader;
    }
    return attr->access_config;
}

uint32_t COSEM_OBIS_to_uint(const COSEM_OBJECT * obj)
{
    uint32_t res = 0;
    res += obj->obis.B;
    res <<= 8;
    res += obj->obis.C;
    res <<= 8;
    res += obj->obis.D;
    res <<= 8;
    res += obj->obis.E;
    return res;
}

uint32_t OBIS_ATTR_to_uint(const OBIS * obis, uint8_t attr)
{
    uint32_t res = 0;
    res += obis->C;
    res <<= 8;
    res += obis->D;
    res <<= 8;
    res += obis->E;
    res <<= 8;
    res += attr;
    return res;
}

DLMS_UNIT OBIS_to_unit(uint8_t C, uint8_t D)
{
    switch (D) {
    case 7: { // Мгновенное значение
        switch (C) {
        case 11:
        case 31: // 1.0.31.7.0.255 L1 Ток | Мгновенное значение
        case 51: // 1.0.51.7.0.255 L2 Ток | Мгновенное значение
        case 71: // 1.0.71.7.0.255 L3 Ток | Мгновенное значение
        case 91: return DLMS_UNIT_CURRENT; // 1.0.91.7.0.255 L0 Ток нейтрал | Мгновенное значение
        case 12:
        case 32: // 1.0.32.7.0.255 L1 Напряжение | Мгновенное значение
        case 52: // 1.0.52.7.0.255 L2 Напряжение | Мгновенное значение
        case 72: return DLMS_UNIT_VOLTAGE; // 1.0.72.7.0.255 L3 Напряжение | Мгновенное значение
        case 13: // 1.0.13.7.0.255 L0 коэффициент мощности | Мгновенное значение
        case 33: // 1.0.33.7.0.255 L1 коэффициент мощности | Мгновенное значение
        case 53: // 1.0.53.7.0.255 L2 коэффициент мощности | Мгновенное значение
        case 73: return DLMS_UNIT_NO_UNIT; // 1.0.73.7.0.255 L3 коэффициент мощности | Мгновенное значение
        case 14: return DLMS_UNIT_FREQUENCY; // 1.0.14.7.0.255 Частота сети | Мгновенное значение
        case  9: // 1.0.9.7.0.255  Ls Полная мощность | Мгновенное значение
        case 29: // 1.0.29.7.0.255 L1 Полная мощность | Мгновенное значение
        case 49: // 1.0.49.7.0.255 L2 Полная мощность | Мгновенное значение
        case 69: return DLMS_UNIT_APPARENT_POWER; // 1.0.69.7.0.255 L3 Полная мощность | Мгновенное значение
        case  1: // 1.0.1.7.0.255  Ls Активная мощность | Мгновенное значение
        case 21: // 1.0.21.7.0.255 L1 Активная мощность | Мгновенное значение
        case 41: // 1.0.41.7.0.255 L2 Активная мощность | Мгновенное значение
        case 61: return DLMS_UNIT_ACTIVE_POWER; // 1.0.61.7.0.255 L3 Активная мощность | Мгновенное значение
        case  3: // 1.0.3.7.0.255  Ls Реактивная мощность | Мгновенное значение
        case 23: // 1.0.23.7.0.255 L1 Реактивная мощность | Мгновенное значение
        case 43: // 1.0.43.7.0.255 L2 Реактивная мощность | Мгновенное значение
        case 63: return DLMS_UNIT_REACTIVE_POWER; // 1.0.63.7.0.255 L3 Реактивная мощность | Мгновенное значение
        case 81: return DLMS_UNIT_PHASE_ANGLEGEGREE; // 1.0.81.7.10.255 Угол A-B | Мгновенное значение
        default: break;
        }
        break;
    }
    case 8: { // Накопленные  Time integral of the quantity calculated from the origin (first start of measurement) to the instantaneous time point
        switch (C) {
        case  1: return DLMS_UNIT_ACTIVE_ENERGY; // 1.0.1.8.0.255  Сум Li Активная мощность + (QI+QIV)   | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case  2: return DLMS_UNIT_ACTIVE_ENERGY; // 1.0.2.8.0.255  Сум Li Активная мощность - (QII+QIII) | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case  3: return DLMS_UNIT_REACTIVE_ENERGY; // 1.0.3.8.0.255  Сум Li Реактивная мощность + (QI+QII) | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case  4: return DLMS_UNIT_REACTIVE_ENERGY; // 1.0.4.8.0.255  Сум Li Реактивная мощность -(QIII+QIV)| Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case 88: return DLMS_UNIT_A260; // 1.0.88.8.0.255 Сум Li A2ч QI+QII+QIII+QIV            | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case 89: return DLMS_UNIT_V260; // 1.0.89.8.0.255 Сум Li V2ч QI+QII+QIII+QIV            | Интеграл по времени 1 | Тариф 0 (0 - суммарно) |
        default: break;
        }
        break;
    }
    default: break;
    }
    return DLMS_UNIT_NONE;
}

#define ATTRIBUTE_COUNTER_MAX (25)
const COSEM_OBJECT * COSEM_Find_OBJECT(OBIS * obis)
{
//    if (obis->F != 255) {
//        printf("%d.%d.%d.%d.%d.%d\r\n", obis->A, obis->B, obis->C, obis->D, obis->E, obis->F);
//    }
    const COSEM_OBJECT * obj;
    for (int i = 0; i < 255; ++i) {
        obj = (const COSEM_OBJECT *)&cosem_objcts[i];
        if (!obj->attr && !obj->method) break;
        if (cmp_OBIS_obj(&obj->obis, obis)) {
            return obj;
        }
    }
    for (int i = 1; i < 255; ++i) { // skip clock
        obj = (const COSEM_OBJECT *)&cosem_objcts_1_0_94_7_0_255[i];
        if (!obj->attr && !obj->method) break;
        if (cmp_OBIS_obj(&obj->obis, obis)) {
            return obj;
        }
    }
    for (int i = 1; i < 255; ++i) { // skip clock
        obj = (const COSEM_OBJECT *)&cosem_objcts_1_0_98_2_0_255[i];
        if (!obj->attr && !obj->method) break;
        if (cmp_OBIS_obj(&obj->obis, obis)) {
            return obj;
        }
    }
    for (int i = 1; i < 255; ++i) { // skip clock
        obj = (const COSEM_OBJECT *)&cosem_objcts_1_0_99_1_0_255[i];
        if (!obj->attr && !obj->method) break;
        if (cmp_OBIS_obj(&obj->obis, obis)) {
            return obj;
        }
    }
    return 0; // can't find
}
const COSEM_OBJECT_Attribute * COSEM_Find_Attribute(const COSEM_OBJECT * obj, uint8_t attr_index)
{
//    char (*__kaboom)[sizeof( COSEM_OBJECT_Attribute )] = 1;
//#warning sizeof(COSEM_OBJECT_Attribute)
    const COSEM_OBJECT_Attribute * attr;
    if (!obj->attr) return 0;
    for (int i = 0; i < ATTRIBUTE_COUNTER_MAX; ++i) {
        attr = (const COSEM_OBJECT_Attribute *)&obj->attr[i];
        if (!attr) return 0;
        if (!attr->access_config && !attr->rw) {
            return 0; // can't find
        }
        if (attr_index == i+1) {
            return attr;
        }
    }
    return 0; // can't find
}
const COSEM_OBJECT_Attribute * COSEM_Find_Method(const COSEM_OBJECT * obj, uint8_t method_index)
{
    const COSEM_OBJECT_Attribute * method;
    if (!obj->method) return 0;
    for (int i = 0; i < 255; ++i) {
        method = (const COSEM_OBJECT_Attribute *)&obj->method[i];
        if (!method) return 0;
        if (!method->access_config && !method->rw) {
            return 0; // can't find
        }
        if (method_index == i+1) {
            return method;
        }
    }
    return 0; // can't find
}

void COSEM_profile_array_name(DLMS_PDU_BUF * pb, const COSEM_OBJECT * cobj, uint8_t attr)
{
    DLMS_PDU_BUF_AddStruct(pb, 4); // +2
    DLMS_PDU_BUF_AddUInt16(pb, cobj->type); // +5
    DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&cobj->obis, sizeof(OBIS)); // +8
    DLMS_PDU_BUF_AddInt8(pb, attr); // +2
    DLMS_PDU_BUF_AddUInt16(pb, 0); // +3   = +20
}
uint8_t COSEM_obj_to_list_count(const COSEM_OBJECT *obj, PDU_channel *pdu_ch, uint8_t *p_array_count)
{
    if (!obj->attr && !obj->method) {
        return 0;
    }
    if (obj->access_min_lvl > pdu_ch->authentication) { // test access
        return 1;
    }
    if (obj->obis.C == 96 && obj->obis.D == 1 && obj->obis.E == 254) {
        return 1;
    }
    if (p_array_count) {
        (*p_array_count)++;
    }
    return 1;
}
uint8_t COSEM_obj_to_list(const COSEM_OBJECT *obj, PDU_channel *pdu_ch, DLMS_PDU_BUF * pb, uint8_t *p_array_count)
{
    if (!obj->attr && !obj->method) {
        return 0;
    }
    if (obj->access_min_lvl > pdu_ch->authentication) { // test access
        return 1;
    }
    if (obj->obis.C == 96 && obj->obis.D == 1 && obj->obis.E == 254) {
        return 1;
    }
    DLMS_PDU_BUF_AddStruct(pb, 4);
    DLMS_PDU_BUF_AddUInt16(pb, obj->type);
    DLMS_PDU_BUF_AddUInt8(pb, obj->version);
    DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obj->obis, sizeof(OBIS));
    DLMS_PDU_BUF_AddStruct(pb, 2);
    DLMS_PDU_BUF_AddArray(pb, 0);
    uint8_t *p_attr_count = pb->data - 1;
    if (obj->attr) {
        ////log_1 << pdu_ch->authentication;
        for (int attr_iter = 0; attr_iter < ATTRIBUTE_COUNTER_MAX; ++attr_iter) {
            const COSEM_OBJECT_Attribute * attr = (COSEM_OBJECT_Attribute *)&obj->attr[attr_iter];
            if (!attr->access_config && !attr->rw) {
                break; // last
            }
            uint8_t access = 0;
            if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_NONE) {
                access = attr->access_public;
            } else if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_LOW) {
                access = attr->access_reader;
            } else {
                access = attr->access_config;
            }
//            if (access == DLMS_ACCESS_MODE_NONE) {
//                continue;
//            }
            DLMS_PDU_BUF_AddStruct(pb, 3);
            DLMS_PDU_BUF_AddInt8(pb, attr_iter + 1);
            DLMS_PDU_BUF_AddEnum(pb, access);
            DLMS_PDU_BUF_AddNone(pb);
            (*p_attr_count)++;
        }
    }
    DLMS_PDU_BUF_AddArray(pb, 0);
    p_attr_count = pb->data - 1;
    if (obj->method) {
        for (int attr_iter = 0; attr_iter < ATTRIBUTE_COUNTER_MAX; ++attr_iter) {
            const COSEM_OBJECT_Attribute * attr = (COSEM_OBJECT_Attribute *)&obj->method[attr_iter];
            if (!attr->access_config && !attr->rw) {
                break; // last
            }
            uint8_t access = 0;
            if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_NONE) {
                access = attr->access_public;
            } else if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_LOW) {
                access = attr->access_reader;
            } else {
                access = attr->access_config;
            }
//            if (access == DLMS_METHOD_ACCESS_MODE_NONE) {
//                continue;
//            }
            DLMS_PDU_BUF_AddStruct(pb, 2);
            DLMS_PDU_BUF_AddInt8(pb, attr_iter + 1);
            DLMS_PDU_BUF_AddEnum(pb, access);
            (*p_attr_count)++;
        }
    }
    if (p_array_count) {
        (*p_array_count)++;
    }
    return 1;
}

void DLMS_PDU_controller(HDLC_BUF *hdlc)
{
    PDU_channel * pdu_ch = &hdlc->pdu_ch;
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_init(hdlc, pb);
    PDU_header pduHeader;
    memset(&pduHeader, 0, sizeof(PDU_header));
    pduHeader.cmd = (DLMS_COMMAND)DLMS_PDU_BUF_GetUInt8(pb);
    switch (pduHeader.cmd) {
    case DLMS_COMMAND_AARQ: {
        //log_2 << "AARQ";
        DLMS_PDU_BUF_GetUInt8(pb); // len_aarq

        const uint8_t cmp_arr_8B[]   = {0x60,0x85,0x74,0x05,0x08,0x02};
        const uint8_t cmp_arr_A1[]   = {0x06,0x07,0x60,0x85,0x74,0x05,0x08,0x01};

//        //log_1 << "clnt" << hdlc->clnt.bytes4.addr << QByteArray::number(hdlc->clnt.bytes4.addr, 16);
        uint8_t counter_tag = 0;
        pdu_ch->authentication_ok = 0;
        PDU_DLMS_SOURCE_DIAGNOSTIC diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_NONE;
        DLMS_ASSOCIATION_RESULT result = DLMS_ASSOCIATION_RESULT_ACCEPTED;
        uint8_t ver_protocol = 0x84;
        while (pb->len) {
            uint8_t tag;
            uint8_t size;
            tag = DLMS_PDU_BUF_GetUInt8(pb);
//            //log_1 << QByteArray::number(tag, 16).toUpper() << QByteArray((const char*)pb->data + 1, *pb->data).toHex().toUpper();
            size = DLMS_PDU_BUF_GetUInt8(pb);
            counter_tag++;
            switch (tag) {
            case DLMS_BER_TYPE_CONTEXT: { // 0x80
                ver_protocol = *(pb->data + 1);
                counter_tag--;
                break;
            }
            case DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_APPLICATION_CONTEXT_NAME: { // 0xA1
                if (memcmp(pb->data, cmp_arr_A1, sizeof(cmp_arr_A1)) || (*(pb->data + 8) > 4)) {
                    //log_1 << "error A1 tag data";
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
                    break;
                }
                if (*(pb->data + 8) != 1) {
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
                    break;
                }
                break;
            }
            case (uint8_t)DLMS_BER_TYPE_CONTEXT | (uint8_t)DLMS_PDU_TYPE_SENDER_ACSE_REQUIREMENTS: { // 0x8A
                if (size != 2 || (*pb->data != 0x07) || (*(pb->data+1) != 0x80)) {
                    //log_1 << "error 8A tag data";
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
                    break;
                }
                break;
            }
            case (uint8_t)DLMS_BER_TYPE_CONTEXT | (uint8_t)DLMS_PDU_TYPE_MECHANISM_NAME: { // 0x8B
                if (memcmp(pb->data, cmp_arr_8B, sizeof(cmp_arr_8B)) || (*(pb->data + 6) > 5)) {
                    //log_1 << "error 8B tag data";
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
                    break;
                }
                pdu_ch->authentication = (PDU_DLMS_AUTHENTICATION)*(pb->data + 6);
                //log_1 << "authentication " << QString::number(pdu_ch->authentication, 16);
                switch ((uint8_t)pdu_ch->authentication) {
                case PDU_DLMS_AUTHENTICATION_LOW:
                case PDU_DLMS_AUTHENTICATION_HIGH:
                case PDU_DLMS_AUTHENTICATION_HIGH_GMAC: {
                    pdu_ch->authentication_ok = 2;
                    break;
                }
                }
                break;
            }
            case DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_CALLING_AUTHENTICATION_VALUE: { // 0xAC
                if ((*pb->data) != 0x80) {
                    //log_1 << "error AC tag data";
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
                    break;
                }
                uint8_t pass_len = *(pb->data + 1);
                if (pass_len > sizeof(pdu_ch->CtoS_challenge)) {
                    //log_1 << "error AC tag data len";
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
                    break;
                }
                pdu_ch->CtoS_challenge_len = pass_len;
                memmove(pdu_ch->CtoS_challenge, pb->data + 2, pass_len);
                //log_1 << "pass" << QByteArray((const char*)pdu_ch->CtoS_challenge, pass_len).toHex().toUpper() << pass_len;
                if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_LOW) {
                    if (!memcmp(pdu_ch->CtoS_challenge, meter.settings.passwords.low, (pass_len < sizeof(meter.settings.passwords.low)) ? pass_len : sizeof(meter.settings.passwords.low))) {
                        pdu_ch->authentication_ok = 1;
                    } else {
                        pdu_ch->authentication_ok = 0;
                        result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                        diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                    }
                } else if (pdu_ch->authentication == PDU_DLMS_AUTHENTICATION_HIGH) {
                    if ((pass_len % 16)) {
                        pdu_ch->authentication_ok = 0;
                        result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                        diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                    }
                }
                //log_1 << "state pass" << pdu_ch->authentication_ok;
                break;
            }
            case DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_USER_INFORMATION: { // 0xBE
                if (*pb->data != 0x04) {
                    //log_1 << "error BE tag data";
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                    break;
                }
                uint32_t bit_str = 0;
                uint16_t need_buf_size = 0;
                pdu_ch->conformance = (PDU_DLMS_CONFORMANCE)0x7E1F;

                uint8_t len_BE = *(pb->data+1);
                uint8_t i_BE = 1;
                if (*(pb->data+(++i_BE)) == DLMS_COMMAND_INITIATE_REQUEST) {
                    uint8_t tag;
                    tag = *(pb->data+(++i_BE));
                    if (tag) { // CtoS
                        uint8_t len_tag = *(pb->data+(++i_BE));
                        //log_1 << "BE CtoS" << QByteArray((const char*)(pb->data+(i_BE)), len_tag).toHex().toUpper();
                        i_BE += len_tag;
                        if (len_tag % 16) {
                            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                            diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                        }
                    }
                    tag = *(pb->data+(++i_BE));
                    if (tag) { // Skip if used
                        uint8_t len_tag = *(pb->data+(++i_BE)) - 1;
                        //log_1 << "BE skip 1" << QByteArray((const char*)(pb->data+(i_BE)), len_tag).toHex().toUpper();
                        i_BE += len_tag;
                    }
                    tag = *(pb->data+(++i_BE));
                    if (tag) { // Skip if used
                        uint8_t len_tag = *(pb->data+(++i_BE)) - 1;
                        //log_1 << "BE skip 2" << QByteArray((const char*)(pb->data+(i_BE)), len_tag).toHex().toUpper();
                        i_BE += len_tag;
                    }
                }
                uint8_t ver_BE = tag = *(pb->data+(++i_BE));
                if (ver_BE < 0x06) {
                    //log_1 << "ver_BE low" << ver_BE;
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_3;
                    break;
                }
                tag = *(pb->data+(++i_BE));
                if (tag != 0x5F) {
                    //log_1 << "5F" << QByteArray::number(tag, 16);
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                    break;
                }
                tag = *(pb->data+(++i_BE));
                if (tag != 0x1F) {
                    //log_1 << "1F" << QByteArray::number(tag, 16);
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                    break;
                }
                ++i_BE;
                ++i_BE;

                bit_str += *(pb->data + (++i_BE)); bit_str <<= 8;
                bit_str += *(pb->data + (++i_BE)); bit_str <<= 8;
                bit_str += *(pb->data + (++i_BE));

                need_buf_size += *(pb->data + (++i_BE)); need_buf_size <<= 8;
                need_buf_size += *(pb->data + (++i_BE));
                if (need_buf_size < 0x400) {
                    //log_1 << need_buf_size;
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                }
                if (len_BE != i_BE-1) {
                    //log_1 << "len_BE != i_BE" << len_BE << i_BE;
                    result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                    diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
                }

//                if (0) {
//                    if (bit_str & (1 <<23)) { //log_1 << "reserved-0";}
//                    if (bit_str & (1 <<22)) { //log_1 << "reserved-1";}
//                    if (bit_str & (1 <<21)) { //log_1 << "reserved-2";}
//                    if (bit_str & (1 <<20)) { //log_1 << "SN read";}
//                    if (bit_str & (1 <<19)) { //log_1 << "SN write";}
//                    if (bit_str & (1 <<18)) { //log_1 << "unconfirmed-write";}
//                    if (bit_str & (1 <<17)) { //log_1 << "reserved-6";}
//                    if (bit_str & (1 <<16)) { //log_1 << "reserved-7";}
//                    if (bit_str & (1 <<15)) { //log_1 << "LN attribute0-supported-with-set";}
//                    if (bit_str & (1 <<14)) { //log_1 << "LN priority-mgmt-supported";}
//                    if (bit_str & (1 <<13)) { //log_1 << "LN attribute0-supported-with-get";}
//                    if (bit_str & (1 <<12)) { //log_1 << "LN block-transfer-with-get-or-read";}
//                    if (bit_str & (1 <<11)) { //log_1 << "LN block-transfer-with-set-or-write";}
//                    if (bit_str & (1 <<10)) { //log_1 << "LN block-transfer-with-action";}
//                    if (bit_str & (1 << 9)) { //log_1 << "LN/SN multiple-references";}
//                    if (bit_str & (1 << 8)) { //log_1 << "LN information-report";}
//                    if (bit_str & (1 << 7)) { //log_1 << "reserved-16";}
//                    if (bit_str & (1 << 6)) { //log_1 << "reserved-17";}
//                    if (bit_str & (1 << 5)) { //log_1 << "SN parameterized-access";}
//                    if (bit_str & (1 << 4)) { //log_1 << "LN get";}
//                    if (bit_str & (1 << 3)) { //log_1 << "LN set";}
//                    if (bit_str & (1 << 2)) { //log_1 << "LN selective-access";}
//                    if (bit_str & (1 << 1)) { //log_1 << "LN event-notification";}
//                    if (bit_str & (1 << 0)) { //log_1 << "LN action";}
//                }
//                //log_1 << "mask" << QByteArray::number(bit_str, 16).toUpper() << QByteArray::number(bit_str & 0x7E1F, 16).toUpper();

//                pdu_ch->conformance = (DLMS_CONFORMANCE) (bit_str &
//                        (DLMS_CONFORMANCE_ACTION | DLMS_CONFORMANCE_EVENT_NOTIFICATION | DLMS_CONFORMANCE_SELECTIVE_ACCESS |
//                         DLMS_CONFORMANCE_SET | DLMS_CONFORMANCE_GET | DLMS_CONFORMANCE_INFORMATION_REPORT |
//                         DLMS_CONFORMANCE_MULTIPLE_REFERENCES | DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_ACTION | DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_SET_OR_WRITE |
//                         DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_GET_OR_READ | DLMS_CONFORMANCE_ATTRIBUTE_0_SUPPORTED_WITH_GET | DLMS_CONFORMANCE_PRIORITY_MGMT_SUPPORTED |
//                         DLMS_CONFORMANCE_ATTRIBUTE_0_SUPPORTED_WITH_SET));
                pdu_ch->conformance = (PDU_DLMS_CONFORMANCE) (bit_str & 0x7E1F);
                break;
            }
            default: {
                //log_1 << "unknow tag" << QByteArray::number(tag, 16);
                counter_tag--;
            }
            }
            pb->data += size; pb->len -= size;
        }

        if (counter_tag == 2 && pdu_ch->authentication_ok == 0) {
            if (hdlc->clnt.bytes4.addr == 0x10) {
                pdu_ch->authentication_ok = 1;
//                pdu_ch->security = DLMS_SECURITY_AUTHENTICATION;
            } else {
                pdu_ch->authentication_ok = 0;
                result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
                diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
            }
        } else if (counter_tag == 5 &&
                   (pdu_ch->authentication_ok == 2 || pdu_ch->authentication_ok == 1) &&
                   (hdlc->clnt.bytes4.addr == 0x20 || hdlc->clnt.bytes4.addr == 0x30)) {
            //
        } else {
            pdu_ch->authentication_ok = 0;
            diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
        }
        if (pdu_ch->authentication > PDU_DLMS_AUTHENTICATION_LOW) {
            pdu_ch->StoC_challenge_len = 16;
            for (int pos = 0; pos < pdu_ch->StoC_challenge_len; ++pos) {
                pdu_ch->StoC_challenge[pos] = 0x01;//rand();
            }
        }
//        else if (pdu_ch->authentication == DLMS_AUTHENTICATION_NONE) {
//            pdu_ch->authentication = DLMS_AUTHENTICATION_LOW;
//        }

        if (ver_protocol != 0x84) {
            diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_4;//PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
        }
        if (diagnostic != PDU_DLMS_SOURCE_DIAGNOSTIC_NONE && result == DLMS_ASSOCIATION_RESULT_ACCEPTED) {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
        }
        if (!pdu_ch->conformance) {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
            diagnostic = PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED;
        }
        //log_1 << "counter_tag" << counter_tag << "ok" << pdu_ch->authentication_ok << result << diagnostic << "clnt" << QByteArray::number(hdlc->clnt.bytes4.addr, 16);

        hdlc->pduHeader.block_index = -1;
        DLMS_PDU_BUF_init(hdlc, pb);
        pb->len = DLMS_MaxServerPDUSize - 128;
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_APPLICATION | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_APPLICATION_CONTEXT_NAME);
        uint8_t * packet_len = pb->data;
        DLMS_PDU_BUF_SetUInt8(pb, 0); // len update later
        // A1
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_APPLICATION_CONTEXT_NAME); // A1
        DLMS_PDU_BUF_SetUInt8(pb, 0x09);
        DLMS_PDU_BUF_SetData(pb, cmp_arr_A1, sizeof(cmp_arr_A1));
        DLMS_PDU_BUF_SetUInt8(pb, 0x01);
        // A2
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_BER_TYPE_INTEGER);
        DLMS_PDU_BUF_SetUInt8(pb, 3); // len
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_INTEGER); // Tag
        DLMS_PDU_BUF_SetUInt8(pb, 1); // Len // Choice for result (INTEGER, universal)
        DLMS_PDU_BUF_SetUInt8(pb, result);
        // A3
        DLMS_PDU_BUF_SetUInt8(pb, 0xA3);
        DLMS_PDU_BUF_SetUInt8(pb, 5); // len
        if (diagnostic == PDU_DLMS_SOURCE_DIAGNOSTIC_4) {
            DLMS_PDU_BUF_SetUInt8(pb, 0xA2); // Tag
        } else {
            DLMS_PDU_BUF_SetUInt8(pb, 0xA1); // Tag
        }
        DLMS_PDU_BUF_SetUInt8(pb, 3); // len
        DLMS_PDU_BUF_SetUInt8(pb, 2); // Tag
        DLMS_PDU_BUF_SetUInt8(pb, 1); // Len // Choice for result (INTEGER, universal)
        // diagnostic
        if (diagnostic != PDU_DLMS_SOURCE_DIAGNOSTIC_NONE) {
            if (diagnostic == PDU_DLMS_SOURCE_DIAGNOSTIC_3) {
                DLMS_PDU_BUF_SetUInt8(pb, PDU_DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN);
            } else if (diagnostic == PDU_DLMS_SOURCE_DIAGNOSTIC_4) {
                DLMS_PDU_BUF_SetUInt8(pb, PDU_DLMS_SOURCE_DIAGNOSTIC_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED);
            } else {
                DLMS_PDU_BUF_SetUInt8(pb, diagnostic);
            }
        } else {
            if (pdu_ch->authentication <= PDU_DLMS_AUTHENTICATION_LOW) {
                DLMS_PDU_BUF_SetUInt8(pb, DLMS_SOURCE_DIAGNOSTIC_NONE);
            } else {
                DLMS_PDU_BUF_SetUInt8(pb, DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED);
                // 88
                DLMS_PDU_BUF_SetUInt8(pb, 0x88); // Add server ACSE-requirenents field component.
                DLMS_PDU_BUF_SetUInt8(pb, 0x02); // Len.
                DLMS_PDU_BUF_SetUInt16(pb, 0x0780);
                // 89
                DLMS_PDU_BUF_SetUInt8(pb, 0x89); // // Add tag.
                DLMS_PDU_BUF_SetUInt8(pb, 0x07); // Len
                DLMS_PDU_BUF_SetUInt8(pb, 0x60);
                DLMS_PDU_BUF_SetUInt8(pb, 0x85);
                DLMS_PDU_BUF_SetUInt8(pb, 0x74);
                DLMS_PDU_BUF_SetUInt8(pb, 0x05);
                DLMS_PDU_BUF_SetUInt8(pb, 0x08);
                DLMS_PDU_BUF_SetUInt8(pb, 0x02);
                DLMS_PDU_BUF_SetUInt8(pb, pdu_ch->authentication);
                // AA
                DLMS_PDU_BUF_SetUInt8(pb, 0xAA); // Add tag.
                DLMS_PDU_BUF_SetUInt8(pb, 2 + pdu_ch->StoC_challenge_len); // Len
                DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_CONTEXT);
                DLMS_PDU_BUF_SetUInt8(pb, pdu_ch->StoC_challenge_len); // Len
                DLMS_PDU_BUF_SetData(pb, pdu_ch->StoC_challenge, pdu_ch->StoC_challenge_len);
            }
        }
        // BE
        if (diagnostic == PDU_DLMS_SOURCE_DIAGNOSTIC_3) {
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_USER_INFORMATION);
            DLMS_PDU_BUF_SetUInt8(pb, 2 + 0x04);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_OCTET_STRING);
            DLMS_PDU_BUF_SetUInt8(pb, 0x04);
            DLMS_PDU_BUF_SetUInt8(pb, 0x0E);
            DLMS_PDU_BUF_SetUInt8(pb, 0x01);
            DLMS_PDU_BUF_SetUInt8(pb, 0x06);
            DLMS_PDU_BUF_SetUInt8(pb, 0x01);
        } else {
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_CONTEXT | DLMS_BER_TYPE_CONSTRUCTED | DLMS_PDU_TYPE_USER_INFORMATION);
            DLMS_PDU_BUF_SetUInt8(pb, 2 + 0x0E);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_BER_TYPE_OCTET_STRING);
            DLMS_PDU_BUF_SetUInt8(pb, 0x0E);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_INITIATE_RESPONSE); // Tag for xDLMS-Initiate
            DLMS_PDU_BUF_SetUInt8(pb, 0x00); // Usage field for the response allowed component
            DLMS_PDU_BUF_SetUInt8(pb, 06); // DLMS Version Number
            DLMS_PDU_BUF_SetUInt8(pb, 0x5F);
            DLMS_PDU_BUF_SetUInt8(pb, 0x1F);
            DLMS_PDU_BUF_SetUInt8(pb, 0x04); // length of the conformance block
            // encoding the number of unused bits in the bit string
            for (int i = 0; i < 4; ++i) {
                DLMS_PDU_BUF_SetUInt8(pb, (pdu_ch->conformance >> (8*(3-i))) & 0xFF);
            }
    //        DLMS_PDU_BUF_SetUInt8(pb, 0x00);
    //        CGXByteBuffer bb(4);
    //        bb.SetUInt32((unsigned long)settings.GetNegotiatedConformance());
    //        data.Set(&bb, 1, 3);
            DLMS_PDU_BUF_SetUInt16(pb, 0x1000); // settings.GetMaxPduSize()
            DLMS_PDU_BUF_SetUInt16(pb, 0x0007); // VAA Name VAA name (0x0007 for LN referencing and 0xFA00 for SN)
        }
        *packet_len = pb->data - hdlc->data_buf - 2;
        DLMS_PDU_BUF_to_HDLC(hdlc, pb);
        return;

//        28.08.2017 11:20:04:436 |-- Посылаем AARQ запрос
//        7E A0 4D 02 21 61 10 86 C6 E6 E6 00 60 3E A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 02 AC 12 80 10 45 BE ED DB 5D C8 EC C5 2D 3E 29 9D EE A3 12 E5 BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 00 78 1D 10 00 40 B4 7E
//        7E A0 42 02 21 61 10 7A AC E6 E6 00 60 33 A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 02 AC 07 80 05 2B CE 51 B0 A4 BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 00 78 1D 10 00 CB 83 7E
//        28.08.2017 11:20:04:439 |-- Ответ прибора учета
//        7E A0 59 61 02 21 30 C4 68 E6 E7 00 61 4A A1 09 06 07 60 85 74 05 08 01 01 A2 03 02 01 00 A3 05 A1 03 02 01 0E 88 02 07 80 89 07 60 85 74 05 08 02 02 AA 12 80 10 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 BE 10 04 0E 08 00 06 5F 1F 04 00 00 78 1D 10 00 00 07 56 AD 7E
//        28.08.2017 11:20:04:440 |-- Чтение логического имени объекта текущей ассоциации
//        7E A0 1A 02 21 61 32 28 81 E6 E6 00 C0 01 81 00 0F 00 00 28 00 00 FF 01 00 FC B4 7E
//        28.08.2017 11:20:04:441 |-- Ответ прибора учета
//        7E A0 19 61 02 21 52 F2 E9 E6 E7 00 C4 01 81 00 09 06 00 00 28 00 01 FF 15 26 7E

//        28.08.2017 11:20:04:821 |-- Посылаем AARQ запрос
//        7E A0 42 02 21 61 10 7A AC E6 E6 00 60 33 A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 02 AC 07 80 05 2B CE 51 B0 A4 BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 00 78 1D 10 00 CB 83 7E
//        28.08.2017 11:20:04:824 |-- Ответ прибора учета
//        7E A0 59 61 02 21 30 C4 68 E6 E7 00 61 4A A1 09 06 07 60 85 74 05 08 01 01 A2 03 02 01 00 A3 05 A1 03 02 01 0E 88 02 07 80 89 07 60 85 74 05 08 02 02 AA 12 80 10 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 01 BE 10 04 0E 08 00 06 5F 1F 04 00 00 78 1D 10 00 00 07 56 AD 7E
//        28.08.2017 11:20:04.826 |-- РЕЗУЛЬТАТ: НЕУДАЧА [Получен AARE.Result: Accepted]

    }
    case DLMS_COMMAND_RELEASE_REQUEST: {
        DLMS_PDU_BUF_init(hdlc, pb);
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_RELEASE_RESPONSE);
        DLMS_PDU_BUF_SetUInt8(pb, 0x03);
        DLMS_PDU_BUF_SetUInt8(pb, 0x80);
        DLMS_PDU_BUF_SetUInt8(pb, 0x01);
        DLMS_PDU_BUF_SetUInt8(pb, 0x00);
        DLMS_PDU_BUF_to_HDLC(hdlc, pb);
        return;
    }
    case DLMS_COMMAND_GET_REQUEST: {
        pduHeader.type = (DLMS_GET_COMMAND_TYPE)DLMS_PDU_BUF_GetUInt8(pb); // Get type.
        pduHeader.invoke_id_and_priority = DLMS_PDU_BUF_GetUInt8(pb); // Get invoke ID and priority.
        switch (pduHeader.type) {
        case DLMS_GET_COMMAND_TYPE_NORMAL: {
            pduHeader.ci = (DLMS_OBJECT_TYPE)DLMS_PDU_BUF_GetUInt16(pb); // class
            pduHeader.obis = DLMS_PDU_BUF_GetOBIS(pb);
            pduHeader.attributeIndex = DLMS_PDU_BUF_GetUInt8(pb);
            pduHeader.selection = DLMS_PDU_BUF_GetUInt8(pb);
            pduHeader.block_index = -1;
            memmove(&hdlc->pduHeader, &pduHeader, sizeof(PDU_header));
            if (pb->len >= 0) {
                if (pb->len < DLMS_MaxServerPDUSizeGet) {
                    hdlc->data_block_len = pb->len;
                } else {
                    hdlc->data_block_len = DLMS_MaxServerPDUSizeGet;
                }
                memmove(hdlc->data_block_buf, pb->data, hdlc->data_block_len);
            }
            //log_2 << "Get request" << "auth:"<< pdu_ch->authentication << "class:" << pduHeader.ci << QString("%1-%2:%3.%4.%5*%6").arg(pduHeader.obis.A).arg(pduHeader.obis.B).arg(pduHeader.obis.C).arg(pduHeader.obis.D).arg(pduHeader.obis.E).arg(pduHeader.obis.F) << pduHeader.attributeIndex << pduHeader.selection;
            PDU_DataAccessResult dar = PDU_DataAccessResult_Success;
            for (;;) {
                if (pb->len < 0) { dar = PDU_DataAccessResult_LongGetOrReadAborted; break; }
//                if (obis.A == 0xFF && obis.B == 0xFF) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT * cobj = COSEM_Find_OBJECT(&pduHeader.obis);
                if (!cobj) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT_Attribute * attr = COSEM_Find_Attribute(cobj, pduHeader.attributeIndex);
                if (!attr) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                if (!attr->rw) {
                    //log_1 << "not search func";
                    dar = PDU_DataAccessResult_ObjectUndefined;
                    break;
                }
                if (COSEM_GET_AttributeAccess(pdu_ch, attr) == DLMS_ACCESS_MODE_NONE) {
                    dar = PDU_DataAccessResult_ReadWriteDenied;
                    break;
                }
                dar = attr->rw(hdlc, &pduHeader, cobj, pb);
                if (dar == PDU_DataAccessResult_need_use_block) {
                    pduHeader.block_index = 0;
                    pb->len = hdlc->data_block_len;
                    memmove(pb->data, hdlc->data_block_buf, pb->len);
                    continue;
                }
                break;
            }
            if (dar == PDU_DataAccessResult_Success) {
                return;
            }
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader.invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, dar);
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            return;
        }
        case DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK: {
            hdlc->pduHeader.type = pduHeader.type;
            hdlc->pduHeader.invoke_id_and_priority = pduHeader.invoke_id_and_priority;
            hdlc->pduHeader.block_index = DLMS_PDU_BUF_GetUInt32(pb); // Get type.
//            if (!hdlc->pduHeader.block_index) hdlc->pduHeader.block_index++;
            //log_1 << "Get request" << "auth:"<< pdu_ch->authentication << "type" << pduHeader.type;
            PDU_DataAccessResult dar = PDU_DataAccessResult_Success;
            for (;;) {
                if (pb->len < 0) { dar = PDU_DataAccessResult_LongGetOrReadAborted; break; }
                pb->len = hdlc->data_block_len;
                memmove(pb->data, hdlc->data_block_buf, pb->len);
//                if (obis.A == 0xFF && obis.B == 0xFF) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT * cobj = COSEM_Find_OBJECT(&hdlc->pduHeader.obis);
                if (!cobj) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT_Attribute * attr = COSEM_Find_Attribute(cobj, hdlc->pduHeader.attributeIndex);
                if (!attr) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                if (!attr->rw) {
                    //log_1 << "not search func";
                    dar = PDU_DataAccessResult_ObjectUndefined;
                    break;
                }
                if (COSEM_GET_AttributeAccess(pdu_ch, attr) == DLMS_ACCESS_MODE_NONE) {
                    dar = PDU_DataAccessResult_ReadWriteDenied;
                    break;
                }
                dar = attr->rw(hdlc, &hdlc->pduHeader, cobj, pb);
                break;
            }
            if (dar == PDU_DataAccessResult_Success) {
                return;
            }
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader.invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, dar);
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            return;
        }
        case DLMS_GET_COMMAND_TYPE_WITH_LIST: {
            //log_1 << "Get request" << "auth:"<< pdu_ch->authentication << "type" << pduHeader.type;
            break;
        }
        default: {
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader.invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, PDU_DataAccessResult_TypeUnmatched);
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            return;
        }
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        pduHeader.type = (DLMS_GET_COMMAND_TYPE)DLMS_PDU_BUF_GetUInt8(pb); // Get type.
        pduHeader.invoke_id_and_priority = DLMS_PDU_BUF_GetUInt8(pb); // Get invoke ID and priority.
        switch (pduHeader.type) {
        case DLMS_GET_COMMAND_TYPE_NORMAL: {
            pduHeader.ci = (DLMS_OBJECT_TYPE)DLMS_PDU_BUF_GetUInt16(pb); // class
            pduHeader.obis = DLMS_PDU_BUF_GetOBIS(pb);
            pduHeader.attributeIndex = DLMS_PDU_BUF_GetUInt8(pb);
            pduHeader.selection = DLMS_PDU_BUF_GetUInt8(pb);
            //log_2 << "Set request" << "auth:"<< pdu_ch->authentication << "class:" << pduHeader.ci << QString("%1-%2:%3.%4.%5*%6").arg(pduHeader.obis.A).arg(pduHeader.obis.B).arg(pduHeader.obis.C).arg(pduHeader.obis.D).arg(pduHeader.obis.E).arg(pduHeader.obis.F) << pduHeader.attributeIndex << pduHeader.selection;
//            DLMS_PDU_Data pdu_data;
//            pdu_data.data = pb->data;
//            pdu_data.len = pb->len;
//            DLMS_PDU_BUF_Read(pb, &pdu_data);
//            //log_1 << pdu_data.dtype << PDU_Data_type(&pdu_data);
            PDU_DataAccessResult dar = PDU_DataAccessResult_Success;
            for (;;) {
                if (pb->len < 0) { dar = PDU_DataAccessResult_LongGetOrReadAborted; break; }
//                if (obis.A == 0xFF && obis.B == 0xFF) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT * cobj = COSEM_Find_OBJECT(&pduHeader.obis);
                if (!cobj) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT_Attribute * attr = COSEM_Find_Attribute(cobj, pduHeader.attributeIndex);
                if (!attr) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
//                if (!selection || PDU_Data_type(&pdu_data) == 255) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                if (DLMS_PDU_Data_type((DLMS_PDU_DATA_TYPE)*pb->data) == 255) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                if (!attr->rw) {
                    //log_1 << "not search func";
                    dar = PDU_DataAccessResult_ObjectUndefined;
                    break;
                }
                uint8_t access = COSEM_GET_AttributeAccess(pdu_ch, attr);
                if (access == DLMS_ACCESS_MODE_NONE || access == DLMS_ACCESS_MODE_READ || access == DLMS_ACCESS_MODE_AUTHENTICATED_READ) {
                    dar = PDU_DataAccessResult_ReadWriteDenied;
                    break;
                }
                dar = attr->rw(hdlc, &pduHeader, cobj, pb);
                break;
            }
            if (dar == PDU_DataAccessResult_Success) {
                return;
            }
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_SET_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader.invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, dar);
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            return;
        }
        case DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK: {
            //log_1 << "type" << pduHeader.type;
            break;
        }
        case DLMS_GET_COMMAND_TYPE_WITH_LIST: {
            //log_1 << "type" << pduHeader.type;
            break;
        }
        default: {
            //log_1 << "unknow type" << pduHeader.type;
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_SET_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader.invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, PDU_DataAccessResult_ObjectUndefined);
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            return;
        }
        }
        break;
    }
    case DLMS_COMMAND_METHOD_REQUEST: { // Action request
        //log_2 << "Action request";
        pduHeader.type = (DLMS_GET_COMMAND_TYPE)DLMS_PDU_BUF_GetUInt8(pb); // Get type.
        pduHeader.invoke_id_and_priority = DLMS_PDU_BUF_GetUInt8(pb); // Get invoke ID and priority.
//        DLMS_GET_COMMAND_TYPE type = (DLMS_GET_COMMAND_TYPE)DLMS_PDU_BUF_GetUInt8(pb); // Get type.
//        uint8_t invoke_id_and_priority = DLMS_PDU_BUF_GetUInt8(pb); // Get invoke ID and priority.
        switch (pduHeader.type) {
        case DLMS_GET_COMMAND_TYPE_NORMAL: {
            pduHeader.ci = (DLMS_OBJECT_TYPE)DLMS_PDU_BUF_GetUInt16(pb);
            pduHeader.obis = DLMS_PDU_BUF_GetOBIS(pb);
            pduHeader.attributeIndex = DLMS_PDU_BUF_GetUInt8(pb);
            pduHeader.selection = DLMS_PDU_BUF_GetUInt8(pb);
            //log_2 << pduHeader.ci << QString("%1-%2:%3.%4.%5*%6").arg(pduHeader.obis.A).arg(pduHeader.obis.B).arg(pduHeader.obis.C).arg(pduHeader.obis.D).arg(pduHeader.obis.E).arg(pduHeader.obis.F) << pduHeader.attributeIndex << pduHeader.selection;
            PDU_DataAccessResult dar = PDU_DataAccessResult_Success;
            for (;;) {
                if (pb->len < 0) { dar = PDU_DataAccessResult_LongGetOrReadAborted; break; }
//                if (obis.A == 0xFF && obis.B == 0xFF) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT * cobj = COSEM_Find_OBJECT(&pduHeader.obis);
                if (!cobj) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                const COSEM_OBJECT_Attribute * meth = COSEM_Find_Method(cobj, pduHeader.attributeIndex);
                if (!meth) { dar = PDU_DataAccessResult_ObjectUndefined; break; }
                if (!meth->rw) {
                    //log_1 << "not search func";
                    dar = PDU_DataAccessResult_ObjectUndefined;
                    break;
                }
//                if (COSEM_GET_AttributeAccess(pdu_ch, attr) == DLMS_ACCESS_MODE_NONE) {
//                    dar = PDU_DataAccessResult_ReadWriteDenied;
//                    break;
//                }
                dar = meth->rw(hdlc, &pduHeader, cobj, pb);
                break;
            }
            if (dar == PDU_DataAccessResult_Success) {
                return;
            }
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader.invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, dar);
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            break;
        }
        default: {
            //log_1 << "type" << pduHeader.type;
            break;
        }
        }
        break;
    }
    default: {
        //log_1 << "cmd error" << QString::number(pduHeader.cmd, 16).toUpper();
        DLMS_PDU_BUF_init(hdlc, pb);
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_CONFIRMED_SERVICE_ERROR);
        DLMS_PDU_BUF_SetUInt8(pb, pduHeader.cmd);
        DLMS_PDU_BUF_SetUInt8(pb, 3);
        DLMS_PDU_BUF_SetUInt8(pb, 2);
        DLMS_PDU_BUF_to_HDLC(hdlc, pb);
        return;
    }
    }
    { // no ack fix
        DLMS_PDU_BUF_init(hdlc, pb);
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
        DLMS_PDU_BUF_SetUInt8(pb, 0);
        DLMS_PDU_BUF_SetUInt8(pb, 1);
        DLMS_PDU_BUF_SetUInt8(pb, PDU_DataAccessResult_TemporaryFailure);
        DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    }
}

