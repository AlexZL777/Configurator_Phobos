#ifndef _DLMS_DLMS_PDU_BUF_H_
#define _DLMS_DLMS_PDU_BUF_H_

#include <stdint.h>
#include "DLMS_HDLC.h"
//#include "DLMS_COSEM_objects.h"
//#include "DLMS_enums.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t year_highbyte;
    uint8_t year_lowbyte;
    uint8_t month;
    uint8_t day_of_month;
    uint8_t day_of_week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t hundredths_of_second;
    uint8_t deviation_highbyte;
    uint8_t deviation_lowbyte;
    uint8_t clock_status;
} COSEM_date_time_struct;

typedef struct {
    uint8_t year_highbyte;
    uint8_t year_lowbyte;   // 0…big 0xFFFF = not specified
    uint8_t month;          // 1…12, 0xFD, 0xFE, 0xFF // 1 is January // 0xFD = daylight_savings_end // 0xFE = daylight_savings_begin // 0xFF = not specified
    uint8_t day_of_month;   // 1…31, 0xFD, 0xFE, 0xFF // 0xFD = 2nd last day of month // 0xFE = last day of month // 0xE0 to 0xFC = reserved // 0xFF = not specified
    uint8_t day_of_week;    // 1…7, 0xFF // 1 is Monday // 0xFF = not specified
} COSEM_date_struct;

typedef struct {
    uint8_t hour;                   // 0…23, 0xFF,
    uint8_t minute;                 // 0…59, 0xFF,
    uint8_t second;                 // 0…59, 0xFF,
    uint8_t hundredths_of_second;   // 0…99, 0xFF
} COSEM_time_struct;

typedef struct {
    uint8_t * data;         // curr point to write
    uint8_t * data_start;   // start point buf
    int16_t len;            // can read len / max len to write
    int32_t block_index;    // index to write, -1 = TYPE_NORMAL, other = TYPE_NEXT_DATA_BLOCK
    int32_t block_index_max;// max index block
    uint8_t * data_back;    // point for next block;
    uint8_t * is_last_block;// point for set FF when lasn block
    uint8_t * block_len;    // uint16 - count byte block
} DLMS_PDU_BUF;

//typedef struct {
////    DLMS_PDU_DATA_TYPE dtype;
//    uint16_t len;
//    uint8_t *data;
//} DLMS_PDU_Data;

void DLMS_PDU_BUF_init(HDLC_BUF *hdlc, DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_init_RESPONSE(DLMS_PDU_BUF * pb, PDU_header *pduHeader);
PDU_DataAccessResult DLMS_PDU_BUF_to_HDLC(HDLC_BUF *hdlc, DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_move_to_main(DLMS_PDU_BUF *pb_dst, DLMS_PDU_BUF *pb_src);

int32_t DLMS_PDU_BUF_GetInt(DLMS_PDU_BUF *pb);

uint8_t DLMS_PDU_BUF_GetUInt8(DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_SetUInt8(DLMS_PDU_BUF *pb, uint8_t val);
uint16_t DLMS_PDU_BUF_GetUInt16(DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_SetUInt16(DLMS_PDU_BUF *pb, uint16_t val);
uint32_t DLMS_PDU_BUF_GetUInt32(DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_SetUInt32(DLMS_PDU_BUF *pb, uint32_t val);
void DLMS_PDU_BUF_SetData(DLMS_PDU_BUF *pb, const uint8_t *data, uint8_t datalen);
OBIS DLMS_PDU_BUF_GetOBIS(DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_AddNone(DLMS_PDU_BUF *pb);
void DLMS_PDU_BUF_AddArray(DLMS_PDU_BUF *pb, const uint8_t count); // 1
void DLMS_PDU_BUF_AddStruct(DLMS_PDU_BUF *pb, const uint8_t count); // 2
void DLMS_PDU_BUF_AddBool(DLMS_PDU_BUF *pb, const uint8_t val); // 3
void DLMS_PDU_BUF_AddBitString(DLMS_PDU_BUF *pb, const uint8_t count); // 4
void DLMS_PDU_BUF_AddInt32(DLMS_PDU_BUF *pb, const int32_t val); // 5
void DLMS_PDU_BUF_AddUInt32(DLMS_PDU_BUF *pb, const uint32_t val); // 6
void DLMS_PDU_BUF_AddInt8(DLMS_PDU_BUF *pb, const int8_t val); // 0x0F 15
void DLMS_PDU_BUF_AddInt16(DLMS_PDU_BUF *pb, const int16_t val); // 0x10 16
void DLMS_PDU_BUF_AddUInt8(DLMS_PDU_BUF *pb, const uint8_t val); // 0x11 17
void DLMS_PDU_BUF_AddUInt16(DLMS_PDU_BUF *pb, const uint16_t val); // 0x12 18
void DLMS_PDU_BUF_AddUInt64(DLMS_PDU_BUF *pb, const uint64_t val); // 0x15 21
void DLMS_PDU_BUF_AddEnum(DLMS_PDU_BUF *pb, const uint8_t val); // 0x16 22
void DLMS_PDU_BUF_AddOctetString(DLMS_PDU_BUF *pb, const uint8_t *str, const uint8_t str_len); // 9
void DLMS_PDU_BUF_AddDateTime(DLMS_PDU_BUF *pb, uint32_t NOW, uint32_t tz_minutes, uint8_t type); // 0x19 25
void DLMS_PDU_BUF_Read(DLMS_PDU_BUF *pb, DLMS_PDU_BUF *pdu_data);
uint8_t DLMS_PDU_Data_type(DLMS_PDU_DATA_TYPE dtype);

void DLMS_PDU_BUF_start_GET_RESPONSE(HDLC_BUF *hdlc, DLMS_PDU_BUF * pb, PDU_header *pduHeader);
void DLMS_PDU_BUF_start_SET_RESPONSE(HDLC_BUF *hdlc, DLMS_PDU_BUF * pb, PDU_header *pduHeader);

#define pb_temp_buf_len (256)
#define PDU_BUF_temp_BEGIN(pb_temp, a) \
    DLMS_PDU_BUF pb_temp; \
    uint8_t pb_temp_buf[pb_temp_buf_len]; \
    pb_temp.data_start = pb_temp_buf; \
    pb_temp.data = pb_temp.data_start; \
    pb_temp.len = pb_temp_buf_len; \
    if (a->block_index == -1 || (a->block_index != -2 && a->block_index <= a->block_index_max)) {
#define PDU_BUF_temp_END(pb_temp, a) \
        DLMS_PDU_BUF_move_to_main(pb, &pb_temp); \
    }

#ifdef __cplusplus
}
#endif

#endif // _DLMS_DLMS_PDU_BUF_H_
