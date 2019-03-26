#ifndef _DLMS_OBIS_PACK_H_
#define _DLMS_OBIS_PACK_H_

#include "DLMS_HDLC.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
    struct {
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
        uint8_t b4;
    } bits;
    uint32_t u32;
    float f;
} pack_32bit;

#pragma pack(push, 1)
typedef struct { // 2 байта
    uint8_t obis_C : 7;
    uint8_t is_ext : 1; // = 1b
    uint8_t obis_E : 3;
    uint8_t obis_A : 1;
    uint8_t obis_D : 4;
} OBIS16;

typedef struct { // 4 байта
    uint8_t obis_B : 3;
    uint8_t obis_A : 3;
    uint8_t is_ext : 2; // = 01b
    uint8_t obis_C : 8;
    uint8_t obis_D : 8;
    uint8_t obis_E : 8;
} OBIS32;

typedef struct { // 6 байт
    uint8_t obis_A : 6;
    uint8_t is_ext : 2; // = 00b
    uint8_t obis_B : 8;
    uint8_t obis_C : 8;
    uint8_t obis_D : 8;
    uint8_t obis_E : 8;
    uint8_t obis_F : 8;
} OBIS48;
#pragma pack(pop)

uint16_t OBIS_p16(const OBIS *obis);
uint32_t OBIS_p32(const OBIS * obis);
uint64_t OBIS_p48(const OBIS * obis);

OBIS OBIS_up16(uint16_t obis_pack);
OBIS OBIS_up32(uint32_t obis_pack);
OBIS OBIS_up48(uint64_t obis_pack);

uint8_t cmp_OBIS_obj(const OBIS * obis1, const OBIS * obis2); // F skip
uint8_t cmp_full_OBIS_obj(const OBIS * obis1, const OBIS * obis2);

uint8_t ElectroAdd_OBIS(uint8_t *buf, const OBIS *obis);
uint8_t ElectroGet_OBIS(uint8_t *buf, OBIS *obis);

#ifdef __cplusplus
}
#endif

#endif // _DLMS_OBIS_PACK_H_
