#include "DLMS_radio.h"

#include <string.h>
#include "DLMS_HDLC.h"
#include "DLMS_CRC.h"
#include "DLMS_PDU.h"
#include "DLMS_arch.h"
#include "DLMS_obis_pack.h"
#include "defines_HW.h"
#include "meter.h"

#ifdef DD_ADE7868A
const OBIS arch_objs_instant[] = {
    {1,0,32,7,0,255}, // Напряжение фазы А
    {1,0,52,7,0,255}, // Напряжение фазы B
    {1,0,72,7,0,255}, // Напряжение фазы C
    {1,0,91,7,0,255}, // Ток нейтрали
    {1,0,14,7,0,255}, // Частота сети
    {1,0,21,7,0,255}, // Активная мощность фазы А
    {1,0,41,7,0,255}, // Активная мощность фазы B
    {1,0,61,7,0,255}, // Активная мощность фазы C
    {1,0,23,7,0,255}, // Реактивная мощность фазы А
    {1,0,43,7,0,255}, // Реактивная мощность фазы B
    {1,0,63,7,0,255}, // Реактивная мощность фазы C
    {1,0,81,7,10,255},// Угол А-В
    {1,0,81,7,21,255},// Угол В-С
    {1,0,81,7, 2,255},// Угол С-А
    {1,0, 1,8,1,255}, // Активная энергия +, импорт по 1 тарифу
    {1,0, 1,8,2,255}, // Активная энергия +, импорт по 2 тарифу
    {1,0, 1,8,3,255}, // Активная энергия +, импорт по 3 тарифу
    {1,0, 1,8,4,255}, // Активная энергия +, импорт по 4 тарифу
    {1,0, 2,8,0,255}, // Активная энергия -, экспорт сумме тарифов
    {1,0, 3,8,0,255}, // Реактивная энергия +, импорт сумме тарифов
    {1,0, 4,8,0,255}, // Реактивная энергия -, экспорт сумме тарифов
};
const OBIS arch_objs_instant7[] = {
    {1,0,32,7,0,255}, // Напряжение фазы А
    {1,0,52,7,0,255}, // Напряжение фазы B
    {1,0,72,7,0,255}, // Напряжение фазы C
    {1,0,31,7,1,255}, // Ток фазы А
    {1,0,51,7,1,255}, // Ток фазы B
    {1,0,71,7,1,255}, // Ток фазы C
    {1,0,91,7,0,255}, // Ток нейтрали
    {1,0,14,7,0,255}, // Частота сети
    {1,0,21,7,0,255}, // Активная мощность фазы А
    {1,0,41,7,0,255}, // Активная мощность фазы B
    {1,0,61,7,0,255}, // Активная мощность фазы C
    {1,0,23,7,0,255}, // Реактивная мощность фазы А
    {1,0,43,7,0,255}, // Реактивная мощность фазы B
    {1,0,63,7,0,255}, // Реактивная мощность фазы C
    {1,0,81,7,10,255},// Угол А-В
    {1,0,81,7,21,255},// Угол В-С
    {1,0,81,7, 2,255},// Угол С-А
#ifdef CURR_ADDR_EXT_SENSORS
    {0,0,96,3,0,255}, // State of input/output control signals, global
#endif
};
const OBIS arch_objs_instant104[] = {
    {0,0,96,3,0,255}, // State of input/output control signals, global
};
#else
const OBIS arch_objs_instant[] = {
    {1,0,32,7,0,255}, // Напряжение фазы А
    {1,0,14,7,0,255}, // Частота сети
    {1,0,21,7,0,255}, // Активная мощность фазы А
    {1,0,41,7,0,255}, // Активная мощность фазы B
    {1,0,23,7,0,255}, // Реактивная мощность фазы А
    {1,0,43,7,0,255}, // Реактивная мощность фазы B
    {1,0, 1,8,1,255}, // Активная энергия +, импорт по 1 тарифу
    {1,0, 1,8,2,255}, // Активная энергия +, импорт по 2 тарифу
    {1,0, 1,8,3,255}, // Активная энергия +, импорт по 3 тарифу
    {1,0, 1,8,4,255}, // Активная энергия +, импорт по 4 тарифу
    {1,0, 2,8,0,255}, // Активная энергия -, экспорт сумме тарифов
    {1,0, 3,8,0,255}, // Реактивная энергия +, импорт сумме тарифов
    {1,0, 4,8,0,255}, // Реактивная энергия -, экспорт сумме тарифов
};
const OBIS arch_objs_instant7[] = {
    {1,0,32,7,0,255}, // Напряжение фазы А
    {1,0,31,7,1,255}, // Ток фазы А
    {1,0,51,7,1,255}, // Ток фазы B
    {1,0,14,7,0,255}, // Частота сети
    {1,0,21,7,0,255}, // Активная мощность фазы А
    {1,0,41,7,0,255}, // Активная мощность фазы B
    {1,0,23,7,0,255}, // Реактивная мощность фазы А
    {1,0,43,7,0,255}, // Реактивная мощность фазы B
#ifdef CURR_ADDR_EXT_SENSORS
    {0,0,96,3,0,255}, // State of input/output control signals, global
#endif
};
const OBIS arch_objs_instant104[] = {
    {0,0,96,3,0,255}, // State of input/output control signals, global
};
#endif
const OBIS arch_objs_instant8[] = {
    {1,0, 1,8,1,255}, // Активная энергия +, импорт по 1 тарифу
    {1,0, 1,8,2,255}, // Активная энергия +, импорт по 2 тарифу
    {1,0, 1,8,3,255}, // Активная энергия +, импорт по 3 тарифу
    {1,0, 1,8,4,255}, // Активная энергия +, импорт по 4 тарифу
    {1,0, 2,8,1,255}, // Активная энергия -, импорт по 1 тарифу
    {1,0, 2,8,2,255}, // Активная энергия -, импорт по 2 тарифу
    {1,0, 2,8,3,255}, // Активная энергия -, импорт по 3 тарифу
    {1,0, 2,8,4,255}, // Активная энергия -, импорт по 4 тарифу
    {1,0, 3,8,1,255}, // Реактивная энергия +, импорт по 1 тарифу
    {1,0, 3,8,2,255}, // Реактивная энергия +, импорт по 2 тарифу
    {1,0, 3,8,3,255}, // Реактивная энергия +, импорт по 3 тарифу
    {1,0, 3,8,4,255}, // Реактивная энергия +, импорт по 4 тарифу
    {1,0, 4,8,1,255}, // Реактивная энергия -, импорт по 1 тарифу
    {1,0, 4,8,2,255}, // Реактивная энергия -, импорт по 2 тарифу
    {1,0, 4,8,3,255}, // Реактивная энергия -, импорт по 3 тарифу
    {1,0, 4,8,4,255}, // Реактивная энергия -, импорт по 4 тарифу
};

uint8_t ElectroAdd_index_header(uint8_t *buf, uint16_t index_head, uint16_t index_send)
{
    *buf++ = (index_send >> 4) & 0xFF;
    *buf++ = ((index_send << 4) & 0xF0) + (index_head & 0x0F);
    return 2;
}
            
uint8_t ElectroAdd_OBIS_valU32(uint8_t *buf, uint32_t val)
{
    pack_32bit p32b;
    p32b.u32 = val;
    *buf++ = p32b.bits.b4;
    *buf++ = p32b.bits.b3;
    *buf++ = p32b.bits.b2;
    *buf++ = p32b.bits.b1;
    return 4;
}
uint8_t ElectroAdd_OBIS_valF32(uint8_t *buf, float val)
{
    pack_32bit p32b;
    p32b.f = val;
    *buf++ = p32b.bits.b4;
    *buf++ = p32b.bits.b3;
    *buf++ = p32b.bits.b2;
    *buf++ = p32b.bits.b1;
    return 4;
}
uint8_t Electro_make_instant(uint8_t* buf, uint8_t type_data)
{
    uint8_t * b = buf;
    *b++ = ELECTRO_header_instant;
    *b++ = meter.vars.ADE_counter;//0x00;
    switch (type_data) {
    case 0: {
        *b++ = type_data;
        const OBIS *obis = 0;
        b += ElectroAdd_OBIS_valU32(b, METER_now());
        for (uint8_t i = 0; i < sizeof(arch_objs_instant)/sizeof(OBIS); ++i) {
            obis = &arch_objs_instant[i];
            b += ElectroAdd_OBIS(b, obis);
            b += ElectroAdd_OBIS_valU32(b, METER_A1CxDx_u32data(obis->C, obis->D, obis->E));
        }
        for (uint8_t phase = 0; phase < 3; phase++) {
            if (meter.curr.phase[phase].I > 0.1 && meter.curr.phase[phase].U < meter.settings.limit.u_off) {
                OBIS obis__ = {1,0,31,7,0,255};
                obis__.C = 11 + 20 * (phase + 1);
                obis = &obis__;
                b += ElectroAdd_OBIS(b, obis);
                b += ElectroAdd_OBIS_valU32(b, METER_A1CxDx_u32data(obis->C, obis->D, obis->E));
            }
        }
        return b - buf;
    }
    case 104: {
        *b++ = type_data;
        const OBIS *obis = 0;
        b += ElectroAdd_OBIS_valU32(b, METER_now());
        for (uint8_t i = 0; i < sizeof(arch_objs_instant104)/sizeof(OBIS); ++i) {
            obis = &arch_objs_instant104[i];
            b += ElectroAdd_OBIS(b, obis);
            b += ElectroAdd_OBIS_valU32(b, METER_A1CxDx_u32data(obis->C, obis->D, obis->E));
        }
        return b - buf;
    }
    case 7: {
        *b++ = type_data;
        const OBIS *obis = 0;
        b += ElectroAdd_OBIS_valU32(b, METER_now());
        for (uint8_t i = 0; i < sizeof(arch_objs_instant7)/sizeof(OBIS); ++i) {
            obis = &arch_objs_instant7[i];
            b += ElectroAdd_OBIS(b, obis);
            b += ElectroAdd_OBIS_valU32(b, METER_A1CxDx_u32data(obis->C, obis->D, obis->E));
        }
        return b - buf;
    }
    case 8: {
        *b++ = type_data;
        const OBIS *obis = 0;
        b += ElectroAdd_OBIS_valU32(b, METER_now());
        for (uint8_t i = 0; i < sizeof(arch_objs_instant8)/sizeof(OBIS); ++i) {
            obis = &arch_objs_instant8[i];
            b += ElectroAdd_OBIS(b, obis);
            b += ElectroAdd_OBIS_valU32(b, METER_A1CxDx_u32data(obis->C, obis->D, obis->E));
        }
        return b - buf;
    }
    default: break;
    }
    return b - buf;
}
uint8_t Electro_make_event_U(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_U e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_U, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_U;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    *b++ = (e.U >> 8) & 0xFF;
    *b++ = (e.U >> 0) & 0xFF;
    *b++ = (e.dU>> 8) & 0xFF;
    *b++ = (e.dU>> 0) & 0xFF;
    return b - buf;
}
uint8_t Electro_make_event_I(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_I e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_I, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_I;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_event_rele(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_rele e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_rele, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_rele;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_event_prog(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_prog e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_prog, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_prog;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    *b++ = e.res;
    return b - buf;
}
uint8_t Electro_make_event_ext(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_ext e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_ext, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_ext;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_event_com(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_com e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_com, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_com;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    *b++ = e.channel;
    *b++ = e.addr;
    return b - buf;
}
uint8_t Electro_make_event_access(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_access e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_access, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_access;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    *b++ = e.channel;
    *b++ = e.addr;
    return b - buf;
}
uint8_t Electro_make_event_diagnos(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_diagnos e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_diagnos, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_diagnos;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_event_tg_pow(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_tg_pow e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_tg_pow, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_tg_pow;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_event_quality(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_quality e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_quality, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_quality;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_event_IO(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_event_IO e;
    if (DLMS_ARCH_read(DLMS_ARCH_event_IO, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_event_IO;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    return b - buf;
}
uint8_t Electro_make_telesignaling(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_telesignaling e;
    if (DLMS_ARCH_read(DLMS_ARCH_telesignaling, &e, index_send)) return 0;
    if (!shift) {
        *b++ = ELECTRO_header_event;
        b += ElectroAdd_index_header(b, index_head, index_send);
//        *b++ = index_send;
//        *b++ = index_head;
        *b++ = DLMS_ARCH_telesignaling;
        b += ElectroAdd_OBIS_valU32(b, e.work);
    }
    b += ElectroAdd_OBIS_valU32(b, e.dt);
    *b++ = e.event;
    *b++ = e.channel;
    *b++ = e.addr;
    return b - buf;
}

uint8_t Electro_make_profile_year(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf;
    DLMS_ARCH_data_profile_year dp;
    if (DLMS_ARCH_read(DLMS_ARCH_profile_year, &dp, index_send)) return 0;
    *b++ = ELECTRO_header_year;
    b += ElectroAdd_index_header(b, index_head, index_send);
    OBIS obis;
    obis.A = 1; obis.B = 0; obis.C = 1; obis.D = 8; obis.E = 1; obis.F = 255;
    b += ElectroAdd_OBIS_valU32(b, dp.dt);
    for (uint8_t i = 0; i < 4; ++i) {
        obis.C = 1; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Ap[i]);
        obis.C = 2; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.An[i]);
        obis.C = 3; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rp[i]);
        obis.C = 4; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rn[i]);
    }
    obis.C = 1; obis.D = 6; obis.E = 0; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.P_max);
    return b - buf;
}
uint8_t Electro_make_profile_month(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf;
    DLMS_ARCH_data_profile_month dp;
    if (DLMS_ARCH_read(DLMS_ARCH_profile_month, &dp, index_send)) return 0;
    *b++ = ELECTRO_header_month;
    b += ElectroAdd_index_header(b, index_head, index_send);
    OBIS obis;
    obis.A = 1; obis.B = 0; obis.C = 1; obis.D = 8; obis.E = 1; obis.F = 255;
    b += ElectroAdd_OBIS_valU32(b, dp.dt);
    for (uint8_t i = 0; i < 4; ++i) {
        obis.C = 1; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Ap[i]);
        obis.C = 2; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.An[i]);
        obis.C = 3; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rp[i]);
        obis.C = 4; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rn[i]);
    }
    obis.C = 1; obis.D = 6; obis.E = 0; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.P_max);
    return b - buf;
}
uint8_t Electro_make_profile_day(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf;
    DLMS_ARCH_data_profile_day dp;
    if (DLMS_ARCH_read(DLMS_ARCH_profile_day, &dp, index_send)) return 0;
    *b++ = ELECTRO_header_day;
    b += ElectroAdd_index_header(b, index_head, index_send);
    OBIS obis;
    obis.A = 1; obis.B = 0; obis.C = 1; obis.D = 8; obis.E = 1; obis.F = 255;
    b += ElectroAdd_OBIS_valU32(b, dp.dt);
    for (uint8_t i = 0; i < 4; ++i) {
        obis.C = 1; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Ap[i]);
        obis.C = 2; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.An[i]);
        obis.C = 3; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rp[i]);
        obis.C = 4; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rn[i]);
    }
    obis.C = 1; obis.D = 6; obis.E = 0; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.P_max);
    return b - buf;
}
uint8_t Electro_make_profile_hour(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf;
    DLMS_ARCH_data_profile_hour dp;
    DLMS_ARCH_data_profile_hour dp_before;
    if (DLMS_ARCH_read(DLMS_ARCH_profile_hour, &dp, index_send)) return 0;
    if (!index_send || !shift) {
        memset(&dp_before, 0, sizeof(DLMS_ARCH_data_profile_hour));
    } else {
        if (DLMS_ARCH_read(DLMS_ARCH_profile_hour, &dp_before, index_send - 1)) {
            memset(&dp_before, 0, sizeof(DLMS_ARCH_data_profile_hour));
        }
    }
    *b++ = ELECTRO_header_hour;
    b += ElectroAdd_index_header(b, index_head, index_send);
    OBIS obis;
    obis.A = 1; obis.B = 0; obis.C = 1; obis.D = 8; obis.E = 1; obis.F = 255;
    b += ElectroAdd_OBIS_valU32(b, dp.dt);
    for (uint8_t i = 0; i < 4; ++i) {
        if (dp.Ap[i] - dp_before.Ap[i] > 1) { obis.C = 1; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Ap[i]); }
        if (dp.An[i] - dp_before.An[i] > 1) { obis.C = 2; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.An[i]); }
        if (dp.Rp[i] - dp_before.Rp[i] > 1) { obis.C = 3; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rp[i]); }
        if (dp.Rn[i] - dp_before.Rn[i] > 1) { obis.C = 4; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rn[i]); }
    }
    if (dp.P_max) { obis.C = 1; obis.D = 6; obis.E = 0; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.P_max); }
    return b - buf;
}
//uint8_t Electro_make_profile_hour_pack(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
//{
//    uint8_t * b = buf + shift;
//    DLMS_ARCH_data_profile_hour dp;
//    DLMS_ARCH_data_profile_hour dp_before;
//    if (DLMS_ARCH_read(DLMS_ARCH_profile_hour, &dp, index_send)) return 0;
//    if (!index_send) {
//        memset(&dp_before, 0, sizeof(DLMS_ARCH_data_profile_hour));
//    } else {
//        if (DLMS_ARCH_read(DLMS_ARCH_profile_hour, &dp_before, index_send - 1)) {
//            memset(&dp_before, 0, sizeof(DLMS_ARCH_data_profile_hour));
//        }
//    }
//    *b++ = ELECTRO_header_hour;
//    b += ElectroAdd_index_header(b, index_head, index_send);
//    OBIS obis;
//    obis.A = 1; obis.B = 0; obis.C = 1; obis.D = 8; obis.E = 1; obis.F = 255;
//    b += ElectroAdd_OBIS_valU32(b, dp.dt);
//    for (uint8_t i = 0; i < 4; ++i) {
//        if (dp.Ap[i] != dp_before.Ap[i]) { obis.C = 1; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Ap[i]); }
//        if (dp.An[i] != dp_before.An[i]) { obis.C = 2; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.An[i]); }
//        if (dp.Rp[i] != dp_before.Rp[i]) { obis.C = 3; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rp[i]); }
//        if (dp.Rn[i] != dp_before.Rn[i]) { obis.C = 4; obis.E = i+1; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.Rn[i]); }
//    }
//    if (dp.P_max) { obis.C = 1; obis.D = 6; obis.E = 0; b += ElectroAdd_OBIS(b, &obis); b += ElectroAdd_OBIS_valU32(b, dp.P_max); }
//    return b - buf;
//}
uint8_t Electro_make_profile_set(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift)
{
    uint8_t * b = buf + shift;
    DLMS_ARCH_data_profile_set dp;
    if (DLMS_ARCH_read(DLMS_ARCH_profile_set, &dp, index_send)) return 0;
    *b++ = ELECTRO_header_set;
    b += ElectroAdd_index_header(b, index_head, index_send);
//    *b++ = index_send;
//    *b++ = index_head;
    OBIS obis;
    b += ElectroAdd_OBIS_valU32(b, dp.dt);
    for (uint8_t i = 0; i < 8; ++i) {
        obis = OBIS_up32(dp.data[i].obis);
        b += ElectroAdd_OBIS(b, &obis);
        b += ElectroAdd_OBIS_valU32(b, dp.data[i].val);
    }
    return b - buf;
}
