#include "DLMS_obis_pack.h"

#include <string.h>

uint16_t OBIS_p16(const OBIS * obis)
{
    OBIS16 ou16;
    ou16.is_ext = 1; // 1 bit
    ou16.obis_A = obis->A;
    ou16.obis_C = obis->C;
    ou16.obis_D = obis->D;
    ou16.obis_E = obis->E;
    uint16_t *p= (uint16_t*)&ou16;
    return *p;
}
uint32_t OBIS_p32(const OBIS * obis)
{
    OBIS32 ou32;
    ou32.is_ext = 1; // 2 bit
    ou32.obis_A = obis->A;
    ou32.obis_B = obis->B;
    ou32.obis_C = obis->C;
    ou32.obis_D = obis->D;
    ou32.obis_E = obis->E;
    uint32_t *p = (uint32_t*)&ou32;
    return *p;
}
uint64_t OBIS_p48(const OBIS * obis)
{
    OBIS48 ou48;
    ou48.is_ext = 0; // 2 bit
    ou48.obis_A = obis->A;
    ou48.obis_B = obis->B;
    ou48.obis_C = obis->C;
    ou48.obis_D = obis->D;
    ou48.obis_E = obis->E;
    ou48.obis_F = obis->F;
    uint64_t *p = (uint64_t*)&ou48;
    return *p;
}
OBIS OBIS_up16(uint16_t obis_pack)
{
    OBIS16 * opack = (OBIS16 *)&obis_pack;
    OBIS obis;
    if (!opack->is_ext) {
        memset(&obis, 0, sizeof(OBIS));
        return obis;
    }
    obis.A = opack->obis_A;
    obis.B = 0;
    obis.C = opack->obis_C;
    obis.D = opack->obis_D;
    obis.E = opack->obis_E;
    obis.F = 255;
    return obis;
}
OBIS OBIS_up32(uint32_t obis_pack)
{
    OBIS32 * opack = (OBIS32 *)&obis_pack;
    OBIS obis;
    if (opack->is_ext != 1) {
        memset(&obis, 0, sizeof(OBIS));
        return obis;
    }
    obis.A = opack->obis_A;
    obis.B = opack->obis_B;
    obis.C = opack->obis_C;
    obis.D = opack->obis_D;
    obis.E = opack->obis_E;
    obis.F = 255;
    return obis;
}
OBIS OBIS_up48(uint64_t obis_pack)
{
    OBIS48 * opack = (OBIS48 *)&obis_pack;
    OBIS obis;
    if (opack->is_ext) {
        memset(&obis, 0, sizeof(OBIS));
        return obis;
    }
    obis.A = opack->obis_A;
    obis.B = opack->obis_B;
    obis.C = opack->obis_C;
    obis.D = opack->obis_D;
    obis.E = opack->obis_E;
    obis.F = opack->obis_F;
    return obis;
}

uint8_t cmp_OBIS_obj(const OBIS * obis1, const OBIS * obis2)
{
    if (obis1->A == obis2->A &&
        obis1->B == obis2->B &&
        obis1->C == obis2->C &&
        obis1->D == obis2->D &&
        obis1->E == obis2->E
       ) return 1;
    return 0;
}

uint8_t cmp_full_OBIS_obj(const OBIS *obis1, const OBIS *obis2)
{
    if (obis1->A == obis2->A &&
        obis1->B == obis2->B &&
        obis1->C == obis2->C &&
        obis1->D == obis2->D &&
        obis1->E == obis2->E &&
        obis1->F == obis2->F
       ) return 1;
    return 0;
}

uint8_t ElectroAdd_OBIS(uint8_t *buf, const OBIS *obis)
{
    uint16_t op16 = OBIS_p16(obis);
    uint32_t op32 = OBIS_p32(obis);
    OBIS ou16 = OBIS_up16(op16);
    OBIS ou32 = OBIS_up32(op32);
    if (cmp_full_OBIS_obj(&ou16, obis)) {
        memmove(buf, &op16, sizeof(op16));
        return sizeof(op16);
    }
    if (cmp_full_OBIS_obj(&ou32, obis)) {
        memmove(buf, &op32, sizeof(op32));
        return sizeof(op32);
    }
    *buf++ = obis->A;
    *buf++ = obis->B;
    *buf++ = obis->C;
    *buf++ = obis->D;
    *buf++ = obis->E;
    *buf++ = obis->F;
    return sizeof(OBIS);
}

uint8_t ElectroGet_OBIS(uint8_t *buf, OBIS *obis)
{
    OBIS16 *o16 = (OBIS16 *)buf;
    OBIS32 *o32 = (OBIS32 *)buf;
    OBIS48 *o48 = (OBIS48 *)buf;
    if (o16->is_ext == 1) {
        obis->A = o16->obis_A;
        obis->B = 0;
        obis->C = o16->obis_C;
        obis->D = o16->obis_D;
        obis->E = o16->obis_E;
        obis->F = 255;
        return 2;
    }
    if (o32->is_ext == 1) {
        obis->A = o32->obis_A;
        obis->B = o32->obis_B;
        obis->C = o32->obis_C;
        obis->D = o32->obis_D;
        obis->E = o32->obis_E;
        obis->F = 255;
        return 4;
    }
    if (o48->is_ext == 0) {
        obis->A = o48->obis_A;
        obis->B = o48->obis_B;
        obis->C = o48->obis_C;
        obis->D = o48->obis_D;
        obis->E = o48->obis_E;
        obis->F = o48->obis_F;
        return 6;
    }
    return 0;
}
