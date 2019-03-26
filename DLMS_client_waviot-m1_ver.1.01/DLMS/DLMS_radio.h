#ifndef _DLMS_RADIO_H_
#define _DLMS_RADIO_H_

#include "DLMS_HDLC.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ELECTRO_header_instant  = 0x40,
    ELECTRO_header_hour     = 0x42,
    ELECTRO_header_day      = 0x44,
    ELECTRO_header_month    = 0x46,
    ELECTRO_header_year     = 0x48,
    ELECTRO_header_set      = 0x4A,
    ELECTRO_header_event    = 0x4F,
} ELECTRO_header;

uint8_t ElectroAdd_OBIS_valU32(uint8_t *buf, uint32_t val);
uint8_t ElectroAdd_OBIS_valF32(uint8_t *buf, float val);

uint8_t Electro_make_instant(       uint8_t* buf, uint8_t type_data);

uint8_t Electro_make_event_U(       uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_I(       uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_rele(    uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_prog(    uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_ext(     uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_com(     uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_access(  uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_diagnos( uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_tg_pow(  uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_quality( uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_event_IO(      uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_telesignaling( uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);

uint8_t Electro_make_profile_year(  uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_profile_month( uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_profile_day(   uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_profile_hour(  uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
//uint8_t Electro_make_profile_hour_pack(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);
uint8_t Electro_make_profile_set(   uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);

#ifdef __cplusplus
}
#endif

#endif // _DLMS_RADIO_H_
