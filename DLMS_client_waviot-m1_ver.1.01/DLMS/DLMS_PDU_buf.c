#include "DLMS_PDU_buf.h"
#include <string.h>
#include <time.h>

void DLMS_PDU_BUF_init(HDLC_BUF *hdlc, DLMS_PDU_BUF *pb)
{
    pb->data_start = hdlc->data_buf;
    pb->data = pb->data_start;
    pb->len = hdlc->data_len;
    pb->block_index_max = hdlc->pduHeader.block_index;
    pb->block_index = pb->block_index_max;
    if (pb->block_index > 0) pb->block_index = 0;
}

void DLMS_PDU_BUF_init_RESPONSE(DLMS_PDU_BUF * pb, PDU_header *pduHeader)
{
    pb->len = DLMS_MaxServerPDUSize;
    if (pb->block_index == -1) {
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
        DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
        DLMS_PDU_BUF_SetUInt8(pb, 0x00);
        return;
    }
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK);
    DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
    DLMS_PDU_BUF_SetUInt8(pb, 0xFF);
    pb->is_last_block = pb->data - 1;
    DLMS_PDU_BUF_SetUInt32(pb, pduHeader->block_index + 1);
    DLMS_PDU_BUF_SetUInt8(pb, 0);
    DLMS_PDU_BUF_SetUInt8(pb, 0x82); // next 2 byte
    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
    pb->block_len = pb->data - 2;
    pb->data_back = pb->data;
}

PDU_DataAccessResult DLMS_PDU_BUF_to_HDLC(HDLC_BUF *hdlc, DLMS_PDU_BUF *pb)
{
    if (!pb) return PDU_DataAccessResult_ReadWriteDenied;
    if (pb->block_index == -2 && hdlc->pduHeader.block_index < 0) {
        hdlc->pduHeader.block_index = 0;
//        pduHeader->block_index = 0;
//        log_1 << "repeat";
        return PDU_DataAccessResult_need_use_block;
    }
    if (pb->block_index >=0 ) {
        uint16_t block_len = pb->data - pb->data_back;
        *pb->block_len++ = block_len >> 8;
        *pb->block_len++ = block_len & 0xFF;
        if (pb->block_index > pb->block_index_max) {
//            log_1 << "will next";
            *pb->is_last_block = 0;
        }
    }
    hdlc->data_len = pb->data - hdlc->data_buf;
    return PDU_DataAccessResult_Success;
}

void DLMS_PDU_BUF_move_to_main(DLMS_PDU_BUF *pb_dst, DLMS_PDU_BUF *pb_src)
{
    uint16_t src_len = pb_src->data - pb_src->data_start;
    uint16_t dct_free = pb_dst->len - (pb_dst->data - pb_dst->data_start);
    if (pb_dst->block_index == -1) { // normal resp
        if (dct_free < src_len) {
            pb_dst->block_index = -2; // overflow normal resp
            return;
        }
        memmove(pb_dst->data, pb_src->data_start, src_len); pb_dst->data += src_len; // copy
        return;
    }
    if (pb_dst->block_index == -2) return; // overflow normal resp
    if (pb_dst->block_index > pb_dst->block_index_max) return; // last block full
    if (pb_dst->block_index == pb_dst->block_index_max) { // last block
        if (dct_free < src_len) { // last block full
            pb_dst->block_index++;
            return;
        }
        memmove(pb_dst->data, pb_src->data_start, src_len); pb_dst->data += src_len; // copy
        return;
    }
    if (dct_free < src_len) {
        pb_dst->data = pb_dst->data_back;
        pb_dst->block_index++;
        DLMS_PDU_BUF_move_to_main(pb_dst, pb_src);
        return;
    }
    memmove(pb_dst->data, pb_src->data_start, src_len); pb_dst->data += src_len; // copy
}

int32_t DLMS_PDU_BUF_GetInt(DLMS_PDU_BUF *pb)
{
    switch (DLMS_PDU_BUF_GetUInt8(pb)) {
//    case DLMS_PDU_DATA_TYPE_NONE:
//    case DLMS_PDU_DATA_TYPE_BOOLEAN:
//    case DLMS_PDU_DATA_TYPE_BIT_STRING:
    case DLMS_PDU_DATA_TYPE_INT32:
    case DLMS_PDU_DATA_TYPE_UINT32: return DLMS_PDU_BUF_GetUInt32(pb);
    case DLMS_PDU_DATA_TYPE_OCTET_STRING: { // datetime
        if (DLMS_PDU_BUF_GetUInt8(pb) != sizeof(COSEM_date_time_struct)) return 0;
        COSEM_date_time_struct *cdt = (COSEM_date_time_struct *)pb->data;
//        log_1 << QByteArray((const char*)pb->data, sizeof(COSEM_date_time_struct)).toHex().toUpper();
        pb->data += sizeof(COSEM_date_time_struct);
        pb->len -= sizeof(COSEM_date_time_struct);
        struct tm tm_val;
        uint16_t y = (cdt->year_highbyte << 8) + cdt->year_lowbyte;
        tm_val.tm_year = y - 1900;
        tm_val.tm_mon  = cdt->month - 1;
        tm_val.tm_mday = cdt->day_of_month;
        tm_val.tm_wday = cdt->day_of_week < 7 ? cdt->day_of_week : 0;
        tm_val.tm_hour = cdt->hour;
        tm_val.tm_min  = cdt->minute;
        tm_val.tm_sec  = cdt->second;
//        log_1 << tm_val.tm_year << tm_val.tm_mon << tm_val.tm_mday << tm_val.tm_wday << tm_val.tm_hour << tm_val.tm_min << tm_val.tm_sec;
        time_t ts = mktime(&tm_val);
        return ts;
    }
//    case DLMS_PDU_DATA_TYPE_STRING:
//    case DLMS_PDU_DATA_TYPE_BINARY_CODED_DESIMAL:
//    case DLMS_PDU_DATA_TYPE_STRING_UTF8:
    case DLMS_PDU_DATA_TYPE_ENUM:
    case DLMS_PDU_DATA_TYPE_INT8:
    case DLMS_PDU_DATA_TYPE_UINT8: return DLMS_PDU_BUF_GetUInt8(pb);
    case DLMS_PDU_DATA_TYPE_INT16:
    case DLMS_PDU_DATA_TYPE_UINT16: return DLMS_PDU_BUF_GetUInt16(pb);
//    case DLMS_PDU_DATA_TYPE_INT64:
//    case DLMS_PDU_DATA_TYPE_UINT64:
//    case DLMS_PDU_DATA_TYPE_FLOAT32:
//    case DLMS_PDU_DATA_TYPE_FLOAT64:
//    case DLMS_PDU_DATA_TYPE_DATETIME:
//    case DLMS_PDU_DATA_TYPE_DATE:
//    case DLMS_PDU_DATA_TYPE_TIME:
    case DLMS_PDU_DATA_TYPE_ARRAY:
    case DLMS_PDU_DATA_TYPE_STRUCTURE: return DLMS_PDU_BUF_GetUInt8(pb);
//    case DLMS_PDU_DATA_TYPE_COMPACT_ARRAY:
    default: break;
    }
    return -1;
}

uint8_t DLMS_PDU_BUF_GetUInt8(DLMS_PDU_BUF *pb)
{
    uint8_t res = *pb->data++;
    pb->len--;
    return res;
}

void DLMS_PDU_BUF_SetUInt8(DLMS_PDU_BUF *pb, uint8_t val)
{
    *pb->data++ = val;
}

uint16_t DLMS_PDU_BUF_GetUInt16(DLMS_PDU_BUF *pb)
{
    uint16_t res = *pb->data++;
    res <<= 8;
    res += *pb->data++;
    pb->len -= 2;
    return res;
}

void DLMS_PDU_BUF_SetUInt16(DLMS_PDU_BUF *pb, uint16_t val)
{
    *pb->data++ = val >> 8;
    *pb->data++ = val & 0xFF;
}

uint32_t DLMS_PDU_BUF_GetUInt32(DLMS_PDU_BUF *pb)
{
    uint32_t res = *pb->data++;
    res <<= 8;
    res += *pb->data++;
    res <<= 8;
    res += *pb->data++;
    res <<= 8;
    res += *pb->data++;
    pb->len -= 4;
    return res;
}

void DLMS_PDU_BUF_SetUInt32(DLMS_PDU_BUF *pb, uint32_t val)
{
    *pb->data++ = (val >>24) & 0xFF;
    *pb->data++ = (val >>16) & 0xFF;
    *pb->data++ = (val >> 8) & 0xFF;
    *pb->data++ = (val >> 0) & 0xFF;
}

void DLMS_PDU_BUF_SetData(DLMS_PDU_BUF *pb, const uint8_t *data, uint8_t datalen)
{
    memmove(pb->data, data, datalen);
    pb->data += datalen;
}

OBIS DLMS_PDU_BUF_GetOBIS(DLMS_PDU_BUF *pb)
{
    OBIS obis;
    obis.A = *pb->data++;
    obis.B = *pb->data++;
    obis.C = *pb->data++;
    obis.D = *pb->data++;
    obis.E = *pb->data++;
    obis.F = *pb->data++;
    pb->len -= 6;
    return obis;
}

void DLMS_PDU_BUF_AddNone(DLMS_PDU_BUF *pb)
{
    DLMS_PDU_BUF_SetUInt8(pb, 0);
}

void DLMS_PDU_BUF_AddArray(DLMS_PDU_BUF *pb, const uint8_t count) // 1
{
    DLMS_PDU_BUF_SetUInt8(pb, 1);
    DLMS_PDU_BUF_SetUInt8(pb, count);
}

void DLMS_PDU_BUF_AddStruct(DLMS_PDU_BUF *pb, const uint8_t count) // 2
{
    DLMS_PDU_BUF_SetUInt8(pb, 2);
    DLMS_PDU_BUF_SetUInt8(pb, count);
}

void DLMS_PDU_BUF_AddBool(DLMS_PDU_BUF *pb, const uint8_t val) // 3
{
    DLMS_PDU_BUF_SetUInt8(pb, 3);
    DLMS_PDU_BUF_SetUInt8(pb, val);
}

void DLMS_PDU_BUF_AddBitString(DLMS_PDU_BUF *pb, const uint8_t count) // 4
{
    DLMS_PDU_BUF_SetUInt8(pb, 4);
    DLMS_PDU_BUF_SetUInt8(pb, count);
}

void DLMS_PDU_BUF_AddInt32(DLMS_PDU_BUF *pb, const int32_t val) // 5
{
    DLMS_PDU_BUF_SetUInt8(pb, 5);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(3*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(2*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(1*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(0*8)) & 0xFF);
}

void DLMS_PDU_BUF_AddUInt32(DLMS_PDU_BUF *pb, const uint32_t val) // 6
{
    DLMS_PDU_BUF_SetUInt8(pb, 6);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(3*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(2*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(1*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(0*8)) & 0xFF);
}

void DLMS_PDU_BUF_AddInt8(DLMS_PDU_BUF *pb, const int8_t val) // 0x0F 15
{
    DLMS_PDU_BUF_SetUInt8(pb, 15);
    DLMS_PDU_BUF_SetUInt8(pb, val);
}

void DLMS_PDU_BUF_AddInt16(DLMS_PDU_BUF *pb, const int16_t val) // 0x10 16
{
    DLMS_PDU_BUF_SetUInt8(pb, 16);
    DLMS_PDU_BUF_SetUInt8(pb, (val >> 8) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >> 0) & 0xFF);
}
void DLMS_PDU_BUF_AddUInt8(DLMS_PDU_BUF *pb, const uint8_t val) // 0x11 17
{
    DLMS_PDU_BUF_SetUInt8(pb, 17);
    DLMS_PDU_BUF_SetUInt8(pb, val);
}

void DLMS_PDU_BUF_AddUInt16(DLMS_PDU_BUF *pb, const uint16_t val) // 0x12 18
{
    DLMS_PDU_BUF_SetUInt8(pb, 18);
    DLMS_PDU_BUF_SetUInt8(pb, (val >> 8) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >> 0) & 0xFF);
}

void DLMS_PDU_BUF_AddUInt64(DLMS_PDU_BUF *pb, const uint64_t val) // 0x15 21
{
    DLMS_PDU_BUF_SetUInt8(pb, 21);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(7*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(6*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(5*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(4*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(3*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(2*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(1*8)) & 0xFF);
    DLMS_PDU_BUF_SetUInt8(pb, (val >>(0*8)) & 0xFF);
}

void DLMS_PDU_BUF_AddEnum(DLMS_PDU_BUF *pb, const uint8_t val) // 0x16 22
{
    DLMS_PDU_BUF_SetUInt8(pb, 22);
    DLMS_PDU_BUF_SetUInt8(pb, val);
}

void DLMS_PDU_BUF_AddOctetString(DLMS_PDU_BUF *pb, const uint8_t *str, const uint8_t str_len) // 9
{
    DLMS_PDU_BUF_SetUInt8(pb, 9);
    DLMS_PDU_BUF_SetUInt8(pb, str_len);
    for (int i = 0; i < str_len; ++i) {
        DLMS_PDU_BUF_SetUInt8(pb, str[i] & 0xFF);
    }
}

void DLMS_PDU_BUF_AddDateTime(DLMS_PDU_BUF *pb, uint32_t NOW, uint32_t tz_minutes, uint8_t type) // 0x19 25
{
    struct tm * tm_val;
    tm_val = gmtime((time_t*)&NOW);
//    tm_val = localtime((time_t*)&NOW);
    if (type == DLMS_PDU_DATA_TYPE_OCTET_STRING) {
        DLMS_PDU_BUF_SetUInt8(pb, 9);
        DLMS_PDU_BUF_SetUInt8(pb, sizeof(COSEM_date_time_struct));
    } else
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_PDU_DATA_TYPE_DATETIME);
    COSEM_date_time_struct *cdt = (COSEM_date_time_struct *)pb->data;
    uint16_t y = tm_val->tm_year + 1900;
    cdt->year_highbyte = (y >> 8) & 0xFF;
    cdt->year_lowbyte  = (y >> 0) & 0xFF;
    cdt->month = tm_val->tm_mon + 1;
    cdt->day_of_month = tm_val->tm_mday;
    cdt->day_of_week = tm_val->tm_wday ? tm_val->tm_wday : 7;
    cdt->hour = tm_val->tm_hour;
    cdt->minute = tm_val->tm_min;
    cdt->second = tm_val->tm_sec;
    cdt->hundredths_of_second = 0;
    cdt->deviation_highbyte = (tz_minutes >> 8) & 0xFF;
    cdt->deviation_lowbyte = (tz_minutes >> 0) & 0xFF;
    cdt->clock_status = 0;
    pb->data += sizeof(COSEM_date_time_struct);
}

void DLMS_PDU_BUF_Read(DLMS_PDU_BUF *pb, DLMS_PDU_BUF *pdu_data)
{
//    memset(pdu_data, 0, sizeof(DLMS_PDU_Data));
    //log_1 << "pdu data" << QByteArray((const char*)pb->data, pb->len).toHex().toUpper() << pb->len;
//    pdu_data->dtype = (DLMS_PDU_DATA_TYPE)DLMS_PDU_BUF_GetUInt8(pb);
    //log_1 << "DLMS_PDU_BUF_Read" << pdu_data->dtype;
    switch ((DLMS_PDU_DATA_TYPE)*pdu_data->data) {
    case DLMS_PDU_DATA_TYPE_NONE: { // 0,
        break;
    }
    case DLMS_PDU_DATA_TYPE_BOOLEAN: { // 3,
        break;
    }
    case DLMS_PDU_DATA_TYPE_BIT_STRING: { // 4,
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT32: { // 5,
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT32: { // 6,
        break;
    }
    case DLMS_PDU_DATA_TYPE_OCTET_STRING: { // 9,
        pdu_data->len = DLMS_PDU_BUF_GetUInt8(pb);
        for (int i = 0; i < pdu_data->len; ++i) {
            pdu_data->data[i] = DLMS_PDU_BUF_GetUInt8(pb);
        }
        break;
    }
    case DLMS_PDU_DATA_TYPE_STRING: { // 10,
        break;
    }
    case DLMS_PDU_DATA_TYPE_BINARY_CODED_DESIMAL: { // 13,
        break;
    }
    case DLMS_PDU_DATA_TYPE_STRING_UTF8: { // 12,
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT8: { // 15,
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT16: { // 16,
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT8: { // 17,
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT16: { // 18,
        break;
    }
    case DLMS_PDU_DATA_TYPE_INT64: { // 20,
        break;
    }
    case DLMS_PDU_DATA_TYPE_UINT64: { // 21,
        break;
    }
    case DLMS_PDU_DATA_TYPE_ENUM: { // 22,
        break;
    }
    case DLMS_PDU_DATA_TYPE_FLOAT32: { // 23,
        break;
    }
    case DLMS_PDU_DATA_TYPE_FLOAT64: { // 24,
        break;
    }
    case DLMS_PDU_DATA_TYPE_DATETIME: { // 25,
        break;
    }
    case DLMS_PDU_DATA_TYPE_DATE: { // 26,
        break;
    }
    case DLMS_PDU_DATA_TYPE_TIME: { // 27,
        break;
    }
    case DLMS_PDU_DATA_TYPE_ARRAY: { // 1,
        break;
    }
    case DLMS_PDU_DATA_TYPE_STRUCTURE: { // 2,
        break;
    }
    case DLMS_PDU_DATA_TYPE_COMPACT_ARRAY: { // 19,
        break;
    }
    default:
        break;
    }
}

uint8_t DLMS_PDU_Data_type(DLMS_PDU_DATA_TYPE dtype)
{
    switch (dtype) {
    case DLMS_PDU_DATA_TYPE_NONE:
    case DLMS_PDU_DATA_TYPE_BOOLEAN:
    case DLMS_PDU_DATA_TYPE_BIT_STRING:
    case DLMS_PDU_DATA_TYPE_INT32:
    case DLMS_PDU_DATA_TYPE_UINT32:
    case DLMS_PDU_DATA_TYPE_OCTET_STRING:
    case DLMS_PDU_DATA_TYPE_STRING:
    case DLMS_PDU_DATA_TYPE_BINARY_CODED_DESIMAL:
    case DLMS_PDU_DATA_TYPE_STRING_UTF8:
    case DLMS_PDU_DATA_TYPE_INT8:
    case DLMS_PDU_DATA_TYPE_INT16:
    case DLMS_PDU_DATA_TYPE_UINT8:
    case DLMS_PDU_DATA_TYPE_UINT16:
    case DLMS_PDU_DATA_TYPE_INT64:
    case DLMS_PDU_DATA_TYPE_UINT64:
    case DLMS_PDU_DATA_TYPE_ENUM:
    case DLMS_PDU_DATA_TYPE_FLOAT32:
    case DLMS_PDU_DATA_TYPE_FLOAT64:
    case DLMS_PDU_DATA_TYPE_DATETIME:
    case DLMS_PDU_DATA_TYPE_DATE:
    case DLMS_PDU_DATA_TYPE_TIME:
    case DLMS_PDU_DATA_TYPE_ARRAY:
    case DLMS_PDU_DATA_TYPE_STRUCTURE:
    case DLMS_PDU_DATA_TYPE_COMPACT_ARRAY:
        return dtype;
    default: break;
    }
    return 255;
}

void DLMS_PDU_BUF_start_GET_RESPONSE(HDLC_BUF *hdlc, DLMS_PDU_BUF *pb, PDU_header *pduHeader)
{
    DLMS_PDU_BUF_init(hdlc, pb);
    pb->len = DLMS_MaxServerPDUSize - 128;
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
    DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
    DLMS_PDU_BUF_SetUInt8(pb, 0);
}

void DLMS_PDU_BUF_start_SET_RESPONSE(HDLC_BUF *hdlc, DLMS_PDU_BUF *pb, PDU_header *pduHeader)
{
    DLMS_PDU_BUF_init(hdlc, pb);
    pb->len = DLMS_MaxServerPDUSize - 128;
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_SET_RESPONSE);
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
    DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
    DLMS_PDU_BUF_SetUInt8(pb, 0);
}
