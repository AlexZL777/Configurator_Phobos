#include "DLMS_tariff.h"

#include <string.h>
#include <time.h>

#include "meter.h"

const uint8_t TARIFF_default[] = {0x80,0x00,0x00,0xC0,0x7F,0x00,0x50,0x08,0x40}; // дефолтное расписание с 0 единственным тарифом

void TARIFF_block_to_u8(void *b, uint8_t *first, uint8_t *second)
{
    if (!first || !second || !b) return;
    (*first) = *((uint8_t *)b + 1);
    (*second) = *((uint8_t *)b + 0);
}

void TARIFF_block_from_u8(void *b, uint8_t first, uint8_t second)
{
    if (!b) return;
    *((uint8_t *)b + 1) = first;
    *((uint8_t *)b + 0) = second;
}

DLMS_tariff_index tariff_index;

void DLMS_tariff_clear_start_index(DLMS_tariff_index * ti)
{
    memset(ti, DLMS_tariff_index_init_val, sizeof(DLMS_tariff_index));
}

void DLMS_tariff_search_start_index_active(void)
{
    DLMS_tariff_search_start_index(meter.settings.tariff.activ, &tariff_index);
}

void DLMS_tariff_search_start_index(uint8_t *tt, DLMS_tariff_index *ti)
{
    DLMS_tariff_clear_start_index(ti);
    uint16_t index = 0;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_header th;
        *((uint8_t*)&th) = tt[index];
        uint8_t flag = 0;
        switch (th.activate.id_block) {
        case 2: { if (ti->days  == DLMS_tariff_index_init_val) ti->days  = index; break; }
        case 3: { if (ti->weeks == DLMS_tariff_index_init_val) ti->weeks = index; break; }
        case 1: {
            switch (th.activate.id_sub_block) {
            case 1: { if (ti->season == DLMS_tariff_index_init_val)    ti->season = index; break; }
            case 2: { if (ti->special == DLMS_tariff_index_init_val)   ti->special = index; break; }
            case 3: { if (ti->activate == DLMS_tariff_index_init_val)  ti->activate = index; flag = 1; break; }
            default: return;
            }
            break;
        }
        default:
            return;
        }
        index++;
        if (!flag) {
            while (index < DLMS_tariff_size - 1) {
                if ((tt[index] & 0x80)) {
                    index += 2; // next
                } else {
                    index += 2; // last
                    break;
                }
            }
        } else if (flag == 1) {
            index += 4;
        } else {
            break;
        }
    }
}

uint32_t DLMS_tariff_search_activate(uint8_t * tt)
{
    uint16_t index = 0;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_header th;
        *((uint8_t*)&th) = tt[index];
        index++;
//        log_1 << index << th.activate.id_block << th.activate.id_sub_block << QByteArray((const char*)&tt[index], tt_size-index).toHex().toUpper();
        switch (th.activate.id_block) {
        case 2: break;
        case 3: break;
        case 1: {
            switch (th.activate.id_sub_block) {
            case 1: break;
            case 2: break;
            case 3: return *(uint32_t*)&tt[index];
            default: return 0xFFFFFFFF;
            }
            break;
        }
        default: return 0xFFFFFFFF;
        }
        while (index < DLMS_tariff_size - 1) {
            if ((tt[index] & 0x80)) {
                index += 2; // next
            } else {
                index += 2; // last
                break;
            }
        }
    }
    return 0xFFFFFFFF;
}

void DLMS_tariff_active_passive()
{
    uint8_t * passiv = meter.settings.tariff.passiv;
    uint8_t * activ  = meter.settings.tariff.activ;
    uint8_t buff[DLMS_tariff_size];
    memset(buff, 0, DLMS_tariff_size);

    uint16_t index = 0;
    uint16_t index_buff = 0;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_header th;
        *((uint8_t*)&th) = activ[index];
        uint8_t flag = 0;
        switch (th.activate.id_block) {
        case 2: buff[index_buff++] = activ[index++]; break;
        case 3: buff[index_buff++] = activ[index++]; break;
        case 1: {
            switch (th.activate.id_sub_block) {
            case 1: buff[index_buff++] = activ[index++]; break;
            case 2: buff[index_buff++] = activ[index++]; break;
            case 3: index += 5; flag = 1; break;
            default: flag = 2;
            }
            break;
        }
        default: flag = 2;
        }
        if (flag == 2) break;
        if (!flag) {
            while (index < DLMS_tariff_size - 1) {
                if ((activ[index] & 0x80)) {
                    buff[index_buff++] = activ[index++]; // next
                    buff[index_buff++] = activ[index++];
                } else {
                    buff[index_buff++] = activ[index++]; // last
                    buff[index_buff++] = activ[index++];
                    break;
                }
            }
        }
    }
    memmove(activ, passiv, DLMS_tariff_size);
    memmove(passiv,  buff, DLMS_tariff_size);
    DLMS_tariff_search_start_index_active();
}

uint16_t DLMS_tariff_get_size(uint8_t * tt)
{
    uint16_t index = 0;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_header th;
        *((uint8_t*)&th) = tt[index];
        uint8_t flag = 0;
        switch (th.activate.id_block) {
        case 2: break;
        case 3: break;
        case 1: {
            switch (th.activate.id_sub_block) {
            case 1: break;
            case 2: break;
            case 3: flag = 1; break;
            default: return index;
            }
            break;
        }
        default: return index;
        }
        index++;
        if (!flag) {
            while (index < DLMS_tariff_size - 1) {
                if ((tt[index] & 0x80)) {
                    index += 2; // next
                } else {
                    index += 2; // last
                    break;
                }
            }
        } else {
            index += 4;
        }
    }
    return index - 1;
}

uint8_t DLMS_tariff_dayid_from_special(uint8_t month, uint8_t day)
{
    if (tariff_index.special == DLMS_tariff_index_init_val) {
//        log_1 << "no special";
        return DLMS_tariff_index_init_val;
    }
    uint8_t * tt = meter.settings.tariff.activ;
    uint16_t index = tariff_index.special + 1;
    TARIFF_special_day tsd;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_block_from_u8(&tsd, tt[index], tt[index+1]); index += 2;
        if (tsd.month == month && tsd.day == day) {
            return tsd.day_id;
        }
        if (!tsd.next) break;
    }
    return DLMS_tariff_index_init_val;
}

uint8_t DLMS_tariff_start_zone_from_dayid(uint8_t day_id)
{
    if (tariff_index.days == DLMS_tariff_index_init_val) {
//        log_1 << "no days";
        return DLMS_tariff_index_init_val;
    }
    uint8_t * tt = meter.settings.tariff.activ;
    uint16_t index = tariff_index.days;
    TARIFF_header th;
    while (index < DLMS_tariff_size - 1) {
        *((uint8_t*)&th) = tt[index]; index++;
        if (th.days.id_block != 2) return DLMS_tariff_index_init_val;
        if (th.days.day_id == day_id) return index;
        TARIFF_zone tz;
        while (index < DLMS_tariff_size - 1) {
            TARIFF_block_from_u8(&tz, tt[index], tt[index+1]); index += 2;
            if (!tz.next) break;
        }
    }
    return DLMS_tariff_index_init_val;
}

uint8_t DLMS_tariff_weekid_from_season(uint8_t month, uint8_t day)
{
    if (tariff_index.season == DLMS_tariff_index_init_val) {
//        log_1 << "no season";
        return DLMS_tariff_index_init_val;
    }
    uint8_t * tt = meter.settings.tariff.activ;
    uint16_t index = tariff_index.season + 1;
    TARIFF_season ts;
    uint8_t week_id = DLMS_tariff_index_init_val;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_block_from_u8(&ts, tt[index], tt[index+1]); index += 2;
        if (ts.month < month) {
            week_id = ts.week_id;
        } else
        if (ts.month == month && ts.day <= day) {
            week_id = ts.week_id;
        }
        if (!ts.next) {
            if (week_id == DLMS_tariff_index_init_val) {
                week_id = ts.week_id;
            }
            break;
        }
    }
    return week_id;
}

uint8_t DLMS_tariff_dayid_from_week(uint8_t week_id, uint8_t wday)
{
    // wday 1=monday..7=sunday
    if (tariff_index.weeks == DLMS_tariff_index_init_val) {
//        log_1 << "no weeks";
        return DLMS_tariff_index_init_val;
    }
    uint8_t * tt = meter.settings.tariff.activ;
    uint16_t index = tariff_index.weeks;
    TARIFF_header th;
    while (index < DLMS_tariff_size - 1) {
        *((uint8_t*)&th) = tt[index]; index++;
        if (th.weeks.id_block != 3) return DLMS_tariff_index_init_val;
        if (th.weeks.week_id == week_id) {
//            log_1 << th.weeks.week_id;
            TARIFF_week tw;
            while (index < DLMS_tariff_size - 1) {
                TARIFF_block_from_u8(&tw, tt[index], tt[index+1]); index += 2;
//                if (tw.mask_week & (0x80 >> wday)) {
                if (tw.mask_week & (1 << (wday - 1))) {
//                    log_1 << QString::number(tw.mask_week, 2) << wday << tw.day_id;
                    return tw.day_id;
                }
                if (!tw.next) break;
            }
            return DLMS_tariff_index_init_val;
        }
        TARIFF_week tw;
        while (index < DLMS_tariff_size - 1) {
            TARIFF_block_from_u8(&tw, tt[index], tt[index+1]); index += 2;
            if (!tw.next) break;
        }
    }
    return DLMS_tariff_index_init_val;
}

uint8_t DLMS_tariff_zone_start_index_from_timestamp(uint32_t timestamp)
{
//    uint8_t * tt = meter.settings.tariff.activ;
    struct tm * tm_old;
    tm_old = localtime((time_t*)&timestamp);
    uint8_t month = tm_old->tm_mon + 1;
    uint8_t day = tm_old->tm_mday;
//    log_1 << tm_old->tm_mon + 1 << tm_old->tm_mday;
    uint8_t dayid = DLMS_tariff_index_init_val;
    dayid = DLMS_tariff_dayid_from_special(month, day);
    if (dayid != DLMS_tariff_index_init_val) {
//        log_1 << "special day_id" << dayid;
        return DLMS_tariff_start_zone_from_dayid(dayid);
    }
    uint8_t weekid = DLMS_tariff_weekid_from_season(month, day);
    if (weekid == DLMS_tariff_index_init_val) return DLMS_tariff_index_init_val;
    uint8_t wday = tm_old->tm_wday;
    if (!wday || wday > 7) wday = 7;
//    log_1 << "week_id" << weekid << "wday" << wday;
    dayid = DLMS_tariff_dayid_from_week(weekid, wday);
    if (dayid != DLMS_tariff_index_init_val) {
//        log_1 << "day_id" << dayid;
        return DLMS_tariff_start_zone_from_dayid(dayid);
    }
    return DLMS_tariff_index_init_val;
}

uint8_t DLMS_tariff_from_zone(uint8_t zone_index, uint32_t timestamp_zone)
{
    uint8_t * tt = meter.settings.tariff.activ;
    uint16_t index = zone_index;
    TARIFF_zone tz;
    uint8_t tariff = DLMS_tariff_index_init_val;
    while (index < DLMS_tariff_size - 1) {
        TARIFF_block_from_u8(&tz, tt[index], tt[index+1]); index += 2;
        if (tz.start_zone <= timestamp_zone) {
            tariff = tz.tariff;
        }
//        log_1 << tz.start_zone << tz.tariff << timestamp_zone << tariff;
        if (!tz.next) break;
    }
    return tariff;
}

uint8_t DLMS_tariff_test_buf(uint8_t* buff, uint16_t buff_len)
{
    uint8_t * tt = buff;
    uint16_t index = 0;
    uint8_t day_ids[64];
    uint8_t week_ids[64];
    uint8_t day_ids_index = 0;
    uint8_t week_ids_index = 0;
    memset(day_ids,  DLMS_tariff_index_init_val, sizeof(day_ids));
    memset(week_ids, DLMS_tariff_index_init_val, sizeof(week_ids));
    while (index < buff_len - 1) {
        TARIFF_header th;
        *((uint8_t*)&th) = tt[index];
        index++;
        switch (th.activate.id_block) {
        case 2: { // days
            day_ids[day_ids_index++] = th.days.day_id;
            TARIFF_zone tz;
            while (index < buff_len - 1) {
                TARIFF_block_from_u8(&tz, tt[index], tt[index+1]); index += 2;
                if (tz.start_zone >= 60*24) return 0x21;
                if (tz.tariff >= 4) return 0x22;
                if (!tz.next) break;
            }
            break;
        }
        case 3: { // weeks
            week_ids[week_ids_index++] = th.weeks.week_id;
            uint8_t mask_week = 0x7F;
            TARIFF_week tw;
            while (index < buff_len - 1) {
                TARIFF_block_from_u8(&tw, tt[index], tt[index+1]); index += 2;
                if (tw.reserv) return 0x31;
                mask_week ^= tw.mask_week;
                {
                    uint8_t flag = 0;
                    for (uint8_t i = 0; i < day_ids_index; ++i) {
                        if (day_ids[i] == tw.day_id) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) return 0x32;
                }
                if (!tw.next) break;
            }
            if (mask_week) return 0x33;
            break;
        }
        case 1: { // ext
            switch (th.activate.id_sub_block) {
            case 1: { // seasons
                if (th.seasons.res) return 0x91;
                TARIFF_season ts;
                while (index < buff_len - 1) {
                    TARIFF_block_from_u8(&ts, tt[index], tt[index+1]); index += 2;
                    if (ts.day > 31 || !ts.day) return 0x92;
                    if (ts.month > 12 || !ts.month) return 0x93;
                    {
                        uint8_t flag = 0;
                        for (uint8_t i = 0; i < week_ids_index; ++i) {
                            if (week_ids[i] == ts.week_id) {
                                flag = 1;
                                break;
                            }
                        }
                        if (!flag) return 0x94;
                    }
                    if (!ts.next) break;
                }
                break;
            }
            case 2: { // special_day
                if (th.special_day.res) return 0xA1;
                TARIFF_special_day tsd;
                while (index < buff_len - 1) {
                    TARIFF_block_from_u8(&tsd, tt[index], tt[index+1]); index += 2;
                    if (tsd.day > 31 || !tsd.day) return 0xA2;
                    if (tsd.month > 12 || !tsd.month) return 0xA3;
                    {
                        uint8_t flag = 0;
                        for (uint8_t i = 0; i < day_ids_index; ++i) {
                            if (day_ids[i] == tsd.day_id) {
                                flag = 1;
                                break;
                            }
                        }
                        if (!flag) return 0xA4;
                    }
                    if (!tsd.next) break;
                }
                break;
            }
            case 3: {
                if (th.activate.res) return 0xB1;
                index += 4;
                break;
            }
            default: return 0xC1;
            }
            break;
        }
        default:
            return 0x01;
        }
    }
    return 0;
}

uint8_t DLMS_tariff_from_timestamp(uint32_t timestamp)
{
    uint32_t timestamp_zone = ((timestamp / 60) % (60*24));
//    log_1 << QDateTime::fromTime_t(timestamp - 60*60*3).toString("dd hh:mm:ss") << (timestamp_zone / 60) << (timestamp_zone % 60) << timestamp_zone;
    uint8_t start_zone = DLMS_tariff_zone_start_index_from_timestamp(timestamp);
//    log_1 << start_zone;
    uint8_t tariff = DLMS_tariff_from_zone(start_zone, timestamp_zone);
//    log_1 << tariff;
    if (tariff == DLMS_tariff_index_init_val) {
        tariff = DLMS_tariff_from_zone(start_zone, 0x7FF);
//        if (timestamp < 60*60*24) timestamp += 60*60*24;
//        start_zone = DLMS_tariff_zone_start_index_from_timestamp(timestamp - 60*60*24);
//        log_1 << start_zone;
//        tariff = DLMS_tariff_from_zone(start_zone, 60*60*24);
    }
//    log_1 << tariff;
    if (tariff >= 4) tariff = 0;
    return tariff;
}
