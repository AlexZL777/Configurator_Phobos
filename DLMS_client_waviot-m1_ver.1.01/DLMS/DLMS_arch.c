#include "DLMS_arch.h"

#include "DLMS_CRC.h"
#include "DLMS_obis_pack.h"
#include "check_power.h"
#include "flash_ext.h"
#include "hal.h"

#include <string.h>

#define WRITE_ARCH_fail_replay (2)
#define PAGES_COUNT_MIN (2)
#define DLMS_ARCH_CRC_size (sizeof(uint16_t))

#define DLMS_ARCH_event_U_count         (100) // 11.0
#define DLMS_ARCH_event_U_size          (sizeof(DLMS_ARCH_data_event_U))//(DLMS_ARCH_CRC_size + 4+1+2+2+4+4) //
#define DLMS_ARCH_event_U_start         DLMS_ARCH_start_addr
#define DLMS_ARCH_event_U_stop          DLMS_ARCH_event_U_start + (((uint32_t)(DLMS_ARCH_event_U_count*DLMS_ARCH_event_U_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_I_count         (100) // 11.1
#define DLMS_ARCH_event_I_size          (sizeof(DLMS_ARCH_data_event_I))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_I_start         DLMS_ARCH_event_U_stop
#define DLMS_ARCH_event_I_stop          DLMS_ARCH_event_I_start + (((uint32_t)(DLMS_ARCH_event_I_count*DLMS_ARCH_event_I_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_rele_count      (100) // 11.2
#define DLMS_ARCH_event_rele_size       (sizeof(DLMS_ARCH_data_event_rele))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_rele_start      DLMS_ARCH_event_I_stop
#define DLMS_ARCH_event_rele_stop       DLMS_ARCH_event_rele_start + (((uint32_t)(DLMS_ARCH_event_rele_count*DLMS_ARCH_event_rele_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_prog_count      (100) // 11.3
#define DLMS_ARCH_event_prog_size       (sizeof(DLMS_ARCH_data_event_prog))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_prog_start      DLMS_ARCH_event_rele_stop
#define DLMS_ARCH_event_prog_stop       DLMS_ARCH_event_prog_start + (((uint32_t)(DLMS_ARCH_event_prog_count*DLMS_ARCH_event_prog_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_ext_count       (100) // 11.4
#define DLMS_ARCH_event_ext_size        (sizeof(DLMS_ARCH_data_event_ext))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_ext_start       DLMS_ARCH_event_prog_stop
#define DLMS_ARCH_event_ext_stop        DLMS_ARCH_event_ext_start + (((uint32_t)(DLMS_ARCH_event_ext_count*DLMS_ARCH_event_ext_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_com_count       (100) // 11.5
#define DLMS_ARCH_event_com_size        (sizeof(DLMS_ARCH_data_event_com))//(DLMS_ARCH_CRC_size + 4+1+2+4)
#define DLMS_ARCH_event_com_start       DLMS_ARCH_event_ext_stop
#define DLMS_ARCH_event_com_stop        DLMS_ARCH_event_com_start + (((uint32_t)(DLMS_ARCH_event_com_count*DLMS_ARCH_event_com_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_access_count    (100) // 11.6
#define DLMS_ARCH_event_access_size     (sizeof(DLMS_ARCH_data_event_access))//(DLMS_ARCH_CRC_size + 4+1+2+4)
#define DLMS_ARCH_event_access_start    DLMS_ARCH_event_com_stop
#define DLMS_ARCH_event_access_stop     DLMS_ARCH_event_access_start + (((uint32_t)(DLMS_ARCH_event_access_count*DLMS_ARCH_event_access_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_diagnos_count   (100) // 11.7
#define DLMS_ARCH_event_diagnos_size    (DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_diagnos_start   DLMS_ARCH_event_access_stop
#define DLMS_ARCH_event_diagnos_stop    DLMS_ARCH_event_diagnos_start + (((uint32_t)(DLMS_ARCH_event_diagnos_count*DLMS_ARCH_event_diagnos_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_tg_pow_count    (100) // 11.8
#define DLMS_ARCH_event_tg_pow_size     (sizeof(DLMS_ARCH_data_event_tg_pow))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_tg_pow_start    DLMS_ARCH_event_diagnos_stop
#define DLMS_ARCH_event_tg_pow_stop     DLMS_ARCH_event_tg_pow_start + (((uint32_t)(DLMS_ARCH_event_tg_pow_count*DLMS_ARCH_event_tg_pow_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_quality_count   (100) // 98.9
#define DLMS_ARCH_event_quality_size    (sizeof(DLMS_ARCH_data_event_quality))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_quality_start   DLMS_ARCH_event_tg_pow_stop
#define DLMS_ARCH_event_quality_stop    DLMS_ARCH_event_quality_start + (((uint32_t)(DLMS_ARCH_event_quality_count*DLMS_ARCH_event_quality_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_event_IO_count        (100) // 98.10
#define DLMS_ARCH_event_IO_size         (sizeof(DLMS_ARCH_data_event_IO))//(DLMS_ARCH_CRC_size + 4+1+4)
#define DLMS_ARCH_event_IO_start        DLMS_ARCH_event_quality_stop
#define DLMS_ARCH_event_IO_stop         DLMS_ARCH_event_IO_start + (((uint32_t)(DLMS_ARCH_event_IO_count*DLMS_ARCH_event_IO_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_telesignaling_count   (5) // 94.7.6
#define DLMS_ARCH_telesignaling_size    (sizeof(DLMS_ARCH_data_telesignaling))//(DLMS_ARCH_CRC_size + 4+1+1+1)
#define DLMS_ARCH_telesignaling_start   DLMS_ARCH_event_IO_stop
#define DLMS_ARCH_telesignaling_stop    DLMS_ARCH_telesignaling_start + (((uint32_t)(DLMS_ARCH_telesignaling_count*DLMS_ARCH_telesignaling_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_profile_year_count    (2+1)
#define DLMS_ARCH_profile_year_size     (sizeof(DLMS_ARCH_data_profile_year))//(DLMS_ARCH_CRC_size + 4*(1+4*4+1+1)) // 0.0.1.0.0.255 1.0.1.8.1,2,3,4.255 1.0.2.8.1,2,3,4.255 1.0.3.8.1,2,3,4.255 1.0.4.8.1,2,3,4.255 пикА+ время_работы
#define DLMS_ARCH_profile_year_start    DLMS_ARCH_telesignaling_stop
#define DLMS_ARCH_profile_year_stop     DLMS_ARCH_profile_year_start + (((uint32_t)(DLMS_ARCH_profile_year_count*DLMS_ARCH_profile_year_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_profile_month_count   (36+1)
#define DLMS_ARCH_profile_month_size    (sizeof(DLMS_ARCH_data_profile_month))//(DLMS_ARCH_CRC_size + 4*(1+4*4+1+1)) // 0.0.1.0.0.255 1.0.1.8.1,2,3,4.255 1.0.2.8.1,2,3,4.255 1.0.3.8.1,2,3,4.255 1.0.4.8.1,2,3,4.255 пикА+ время_работы
#define DLMS_ARCH_profile_month_start   DLMS_ARCH_profile_year_stop
#define DLMS_ARCH_profile_month_stop    DLMS_ARCH_profile_month_start + (((uint32_t)(DLMS_ARCH_profile_month_count*DLMS_ARCH_profile_month_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_profile_day_count     (120)
#define DLMS_ARCH_profile_day_size      (sizeof(DLMS_ARCH_data_profile_day))//(DLMS_ARCH_CRC_size + 4*(1+4*4+1+1)) // 0.0.1.0.0.255 1.0.1.8.1,2,3,4.255 1.0.2.8.1,2,3,4.255 1.0.3.8.1,2,3,4.255 1.0.4.8.1,2,3,4.255 пикА+ время_работы
#define DLMS_ARCH_profile_day_start     DLMS_ARCH_profile_month_stop
#define DLMS_ARCH_profile_day_stop      DLMS_ARCH_profile_day_start + (((uint32_t)(DLMS_ARCH_profile_day_count*DLMS_ARCH_profile_day_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_profile_hour_count    (123*24) //2952
#define DLMS_ARCH_profile_hour_size     (sizeof(DLMS_ARCH_data_profile_hour))//(DLMS_ARCH_CRC_size + 4*(1+4+1)) // 0.0.1.0.0.255 1.0.1.29.0.255 1.0.2.29.0.255 1.0.3.29.0.255 1.0.4.29.0.255 пикА+
#define DLMS_ARCH_profile_hour_start    DLMS_ARCH_profile_day_stop
#define DLMS_ARCH_profile_hour_stop     DLMS_ARCH_profile_hour_start + (((uint32_t)(DLMS_ARCH_profile_hour_count*DLMS_ARCH_profile_hour_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

#define DLMS_ARCH_profile_set_count     (5)
#define DLMS_ARCH_profile_set_size      (sizeof(DLMS_ARCH_data_profile_set))//(DLMS_ARCH_CRC_size + (4+2)*(1+8)) // 0.0.1.0.0.255 I3 U3 A R
#define DLMS_ARCH_profile_set_start     DLMS_ARCH_profile_hour_stop
#define DLMS_ARCH_profile_set_stop      DLMS_ARCH_profile_set_start + (((uint32_t)(DLMS_ARCH_profile_set_count*DLMS_ARCH_profile_set_size/DLMS_ARCH_page_size)+PAGES_COUNT_MIN)*DLMS_ARCH_page_size)

//#define STR_HELPER(x) #x
//#define STR(x) STR_HELPER(x)
//#pragma message(STR(DLMS_ARCH_profile_set_stop))

//#define DLMS_ARCH_settings_size         DLMS_ARCH_page_size * 2
//#define DLMS_ARCH_settings_start        DLMS_ARCH_profile_set_stop
//#define DLMS_ARCH_settings_stop         DLMS_ARCH_settings_start + DLMS_ARCH_settings_size

const DLMS_ARCH_settings arch_settings[17] = {
    {DLMS_ARCH_event_U_start,          DLMS_ARCH_event_U_stop,         DLMS_ARCH_event_U_size,         60, Electro_make_event_U         },
    {DLMS_ARCH_event_I_start,          DLMS_ARCH_event_I_stop,         DLMS_ARCH_event_I_size,         60, Electro_make_event_I         },
    {DLMS_ARCH_event_rele_start,       DLMS_ARCH_event_rele_stop,      DLMS_ARCH_event_rele_size,      60, Electro_make_event_rele      },
    {DLMS_ARCH_event_prog_start,       DLMS_ARCH_event_prog_stop,      DLMS_ARCH_event_prog_size,      60, Electro_make_event_prog      },
    {DLMS_ARCH_event_ext_start,        DLMS_ARCH_event_ext_stop,       DLMS_ARCH_event_ext_size,       60, Electro_make_event_ext       },
    {DLMS_ARCH_event_com_start,        DLMS_ARCH_event_com_stop,       DLMS_ARCH_event_com_size,       60, Electro_make_event_com       },
    {DLMS_ARCH_event_access_start,     DLMS_ARCH_event_access_stop,    DLMS_ARCH_event_access_size,    60, Electro_make_event_access    },
    {DLMS_ARCH_event_diagnos_start,    DLMS_ARCH_event_diagnos_stop,   DLMS_ARCH_event_diagnos_size,   60, Electro_make_event_diagnos   },
    {DLMS_ARCH_event_tg_pow_start,     DLMS_ARCH_event_tg_pow_stop,    DLMS_ARCH_event_tg_pow_size,    60, Electro_make_event_tg_pow    },
    {DLMS_ARCH_event_quality_start,    DLMS_ARCH_event_quality_stop,   DLMS_ARCH_event_quality_size,   60, Electro_make_event_quality   },
    {DLMS_ARCH_event_IO_start,         DLMS_ARCH_event_IO_stop,        DLMS_ARCH_event_IO_size,        60, Electro_make_event_IO        },
    {DLMS_ARCH_telesignaling_start,    DLMS_ARCH_telesignaling_stop,   DLMS_ARCH_telesignaling_size,   60, Electro_make_telesignaling   },

    {DLMS_ARCH_profile_year_start,     DLMS_ARCH_profile_year_stop,    DLMS_ARCH_profile_year_size,   60*60*18, Electro_make_profile_year },
    {DLMS_ARCH_profile_month_start,    DLMS_ARCH_profile_month_stop,   DLMS_ARCH_profile_month_size,  60*60*18, Electro_make_profile_month},
    {DLMS_ARCH_profile_day_start,      DLMS_ARCH_profile_day_stop,     DLMS_ARCH_profile_day_size,    60*60*12, Electro_make_profile_day  },
    {DLMS_ARCH_profile_hour_start,     DLMS_ARCH_profile_hour_stop,    DLMS_ARCH_profile_hour_size,   50*60, Electro_make_profile_hour    },
    {DLMS_ARCH_profile_set_start,      DLMS_ARCH_profile_set_stop,     DLMS_ARCH_profile_set_size,    50*60, Electro_make_profile_set     },
};

DLMS_ARCH_info arch_info[17];

uint16_t DLMS_ARCH_info_count_max(DLMS_ARCH_info * ainfo)
{
    return (ainfo->settings->mem_end - ainfo->settings->mem_start) / ainfo->settings->rec_size;
}

uint8_t DLMS_ARCH_write(DLMS_ARCH_index ai, void *data)
{
    if (!ispower()) {
        return 5;
    }
    if (ai > sizeof(arch_info) / sizeof(DLMS_ARCH_info)) {
        return 1;
    }
    DLMS_ARCH_info * ainf = &arch_info[ai];
    uint8_t * d = (uint8_t *)data;
    uint8_t d_len = ainf->settings->rec_size - 2;
    d += d_len;
    uint16_t dcrc = DLMS_crc_buff((uint8_t *)data, d_len);
    memmove(d, &dcrc, 2); // fix

    uint16_t count_recs = (ainf->settings->mem_end - ainf->settings->mem_start) / ainf->settings->rec_size;
    uint8_t temp_buff_read[sizeof(DLMS_ARCH_data_profile_day)];
    for (uint8_t i = 0; i < WRITE_ARCH_fail_replay; i++) { // if fail replay 1 time
        // write
        if (ainf->index_head > count_recs) {
            ainf->index_head = 0;
        }
//        log_1 << ainf->index_head;
        uint32_t addr = ainf->settings->mem_start + ainf->settings->rec_size * ainf->index_head;
        uint8_t need_shift_last = 0;
        if (addr + ainf->settings->rec_size > ainf->settings->mem_end) {
            ainf->index_head = 0;
            addr = ainf->settings->mem_start;
            need_shift_last = 1;
        }
        uint8_t need_erase = 0;
        if (addr == ainf->settings->mem_start) { // first page
            need_erase = 1;
        } else if (addr/DLMS_ARCH_page_size != (addr + ainf->settings->rec_size)/DLMS_ARCH_page_size) { // next page
            need_erase = 1;
            //need_shift_last = 1;
        }
        if (need_erase) {
            FLASH_EXT_erase_page(addr + ainf->settings->rec_size);
        }
//        if (0) { // test can write
//            uint8_t tbuf[255];
//            FLASH_EXT_read(addr, tbuf, ainf->settings->rec_size);
//            for (int i = 0; i < ainf->settings->rec_size; i++) {
//                if (tbuf[i] != 0xFF) {
//                    while(1) {}
//                }
//            }
//        }
        FLASH_EXT_write(addr, data, ainf->settings->rec_size);

        // verification
        if (!DLMS_ARCH_read(ai, temp_buff_read, ainf->index_head)) {
            if (++ainf->index_head > count_recs) {
                ainf->index_head = 0;
            }
            // shift tail
            if (ainf->index_head == ainf->index_last || need_shift_last) {
                addr = ainf->settings->mem_start + ainf->settings->rec_size * ainf->index_last;
                while (addr/DLMS_ARCH_page_size == (addr + ainf->settings->rec_size)/DLMS_ARCH_page_size) {
                    if (++ainf->index_last > count_recs) {
                        ainf->index_last = 0;
                    }
                    addr = ainf->settings->mem_start + ainf->settings->rec_size * ainf->index_last;
                }
                if (++ainf->index_last > count_recs) {
                    ainf->index_last = 0;
                }
            }
//            log_1 << ainf->index_head;
            return 0;
        }
        // error verification
        FLASH_EXT_restart();
        if (++ainf->index_head > count_recs) {
            ainf->index_head = 0;
        }
        // shift tail
        if (ainf->index_head == ainf->index_last || need_shift_last) {
            addr = ainf->settings->mem_start + ainf->settings->rec_size * ainf->index_last;
            while (addr/DLMS_ARCH_page_size == (addr + ainf->settings->rec_size)/DLMS_ARCH_page_size) {
                if (++ainf->index_last > count_recs) {
                    ainf->index_last = 0;
                }
                addr = ainf->settings->mem_start + ainf->settings->rec_size * ainf->index_last;
            }
            if (++ainf->index_last > count_recs) {
                ainf->index_last = 0;
            }
        }
//        log_1 << ainf->index_head;
    }
    return 2;
}

uint8_t DLMS_ARCH_read(DLMS_ARCH_index ai, void *data, uint16_t index)
{
    if (!ispower()) {
        return 5;
    }
    if (ai > sizeof(arch_info) / sizeof(DLMS_ARCH_info)) {
        return 1;
    }
    DLMS_ARCH_info * ainf = &arch_info[ai];
    uint32_t addr = ainf->settings->mem_start + ainf->settings->rec_size * index;
    if (addr >= ainf->settings->mem_end) {
        return 2;
    }
//    FLASH_EXT_init();
    if (FLASH_EXT_read(addr, data, ainf->settings->rec_size)) {
        return 3;
    }
    uint8_t * d = data;
    uint8_t d_len = ainf->settings->rec_size - 2;
    d += d_len;
    uint16_t crc_arch;
    memmove(&crc_arch, d, 2); // fix
    if (crc_arch != DLMS_crc_buff(data, d_len)) {
        return 4;
    }
    return 0;
}

uint8_t DLMS_ARCH_read_next(DLMS_ARCH_index ai, void *data)
{
    DLMS_ARCH_info * ainf = &arch_info[ai];
    for (;;) {
        if (ainf->index_head == ainf->index_send) {
            return 1;
        }
        uint8_t res = DLMS_ARCH_read(ai, data, ainf->index_send);
        if (++ainf->index_send > (ainf->settings->mem_end - ainf->settings->mem_start) / ainf->settings->rec_size) {
            ainf->index_send = 0;
        }
        if (!res) {
            return 0;
        }
    }
}

uint8_t DLMS_ARCH_init_Newton(DLMS_ARCH_index ai)
{
    uint32_t r_h_index;
    uint32_t r_h_timestamp;
    uint32_t r_l_index;
    uint32_t r_l_timestamp;
    uint32_t r_cur_index;
    uint32_t r_cur_timestamp;
    DLMS_ARCH_info * ainfo = &arch_info[ai];
    uint8_t buf[256]; // должно хватить)
    if (ainfo->settings->mem_end < ainfo->settings->mem_start) { while(1); }// assert
    if (sizeof(buf) < ainfo->settings->rec_size) { while(1); }// assert
    ainfo->index_head = -1;
    r_h_index = (ainfo->settings->mem_end - ainfo->settings->mem_start) / ainfo->settings->rec_size - 1;
    if (DLMS_ARCH_read(ai, buf, r_h_index)) {
        r_h_timestamp = 0xFFFFFFFF;
    } else {
        memmove(&r_h_timestamp, buf, sizeof(uint32_t));
    }

    r_l_index = 0;
    if (DLMS_ARCH_read(ai, buf, r_l_index)) {
        r_l_timestamp = 0xFFFFFFFF;
    } else {
        memmove(&r_l_timestamp, buf, sizeof(uint32_t));
    }

    r_cur_index = 0;
    if (r_l_timestamp == 0xFFFFFFFF && r_h_timestamp == 0xFFFFFFFF) {
        ainfo->index_head = 0;//r_h_index;
        ainfo->index_send = ainfo->index_head;
        return 1;
    }

    while (r_cur_index != (r_h_index + r_l_index) / 2) {
        r_cur_index = (r_h_index + r_l_index ) / 2;
        if (DLMS_ARCH_read(ai, buf, r_cur_index)) {
            r_cur_timestamp = 0xFFFFFFFF;
        } else {
            memmove(&r_cur_timestamp, buf, sizeof(uint32_t));
        }

        if (r_cur_timestamp == 0xFFFFFFFF) {
            r_h_index = r_cur_index;
            r_h_timestamp = r_cur_timestamp;
        } else
        if (r_l_timestamp < r_cur_timestamp) {
            r_l_index = r_cur_index;
            r_l_timestamp = r_cur_timestamp;
        } else {
            r_h_index = r_cur_index;
            r_h_timestamp = r_cur_timestamp;
        }
    }
    ainfo->index_head = r_cur_index;
    if (DLMS_ARCH_read(ai, buf, ainfo->index_head)) {
        ainfo->index_head = 0;
    } else {
        if (++ainfo->index_head > (ainfo->settings->mem_end - ainfo->settings->mem_start) / ainfo->settings->rec_size - 1) {
            ainfo->index_head = 0;
        }
    }
    ainfo->index_send = ainfo->index_head;
    return 0;
}

uint8_t DLMS_ARCH_init_Line(DLMS_ARCH_index ai, uint32_t * ts_update)
{
    uint32_t r_h_index;
    uint32_t r_l_index;
    uint32_t r_l_timestamp;
    uint32_t r_last_index;
    uint32_t r_last_timestamp;
    uint32_t r_cur_index;
    uint32_t r_cur_timestamp;
    DLMS_ARCH_info * ainfo = &arch_info[ai];
    ainfo->settings = &arch_settings[ai];
    
    uint8_t buf[256]; // должно хватить)
    if (ainfo->settings->mem_end < ainfo->settings->mem_start) { while(1); }// assert
    if (sizeof(buf) < ainfo->settings->rec_size) { while(1); }// assert
    ainfo->index_head = -1;
    ainfo->index_last = -1;
    r_h_index = DLMS_ARCH_info_count_max(ainfo) - 1;//(ainfo->settings->mem_end - ainfo->settings->mem_start) / ainfo->settings->rec_size - 1;
    r_l_index = 0;
    r_l_timestamp = 0;
    r_last_index = 0;
    r_last_timestamp = 0;
    for (r_cur_index = 0; r_cur_index <= r_h_index; ++r_cur_index) {
        if (DLMS_ARCH_read(ai, buf, r_cur_index)) {
            r_cur_timestamp = 0xFFFFFFFF;
        } else {
            memmove(&r_cur_timestamp, buf, sizeof(uint32_t));
            if (r_cur_timestamp > r_l_timestamp) {
                r_l_timestamp = r_cur_timestamp;
                r_l_index = r_cur_index;
            }
            if (r_cur_timestamp < r_last_timestamp) {
                r_last_timestamp = r_cur_timestamp;
                r_last_index = r_cur_index;
            }
        }
    }
    if (r_l_timestamp) {
        if (++r_l_index > r_h_index) {
            r_l_index = 0;
        }
        ainfo->timestamp_last = r_l_timestamp;
        if (ts_update) {
            *ts_update = r_l_timestamp;
        }
    }
    ainfo->index_last = r_last_index;
    ainfo->index_head = r_l_index;
    ainfo->index_send = ainfo->index_head;
    return 0;
}

uint16_t DLMS_ARCH_max_count(DLMS_ARCH_index ai)
{
    return DLMS_ARCH_info_count_max(&arch_info[ai]);
//    DLMS_ARCH_info * ainfo = &arch_info[ai];
//    return (ainfo->settings->mem_end - ainfo->settings->mem_start) / ainfo->settings->rec_size;
}

uint16_t DLMS_ARCH_fill_count(DLMS_ARCH_index ai)
{
    DLMS_ARCH_info * ainfo = &arch_info[ai];
    uint16_t max_count = DLMS_ARCH_max_count(ai);
    if (ainfo->index_head >= ainfo->index_last) {
        return ainfo->index_head - ainfo->index_last;
    }
    return (max_count - ainfo->index_last) + ainfo->index_head;
}

#include "meter.h"
uint8_t DLMS_ARCH_write_settings()
{
    EEPROM_INT_init();
    uint32_t shift = DLMS_addr_settings_start;
    uint64_t ts = 0x0102;
    EEPROM_INT_write(shift, &ts, sizeof(uint64_t));
    shift += sizeof(uint64_t);
    EEPROM_INT_write(shift, &meter.settings, sizeof(METER_settings));
    shift += sizeof(METER_settings);
    uint16_t dcrc = DLMS_crc_buff((uint8_t *)&meter.settings, sizeof(METER_settings));
    EEPROM_INT_write(shift, &dcrc, sizeof(uint64_t));
    shift += sizeof(uint64_t);
    EEPROM_INT_deinit();
    return 0;
}

uint8_t DLMS_ARCH_load_settings()
{
    uint32_t shift = DLMS_addr_settings_start;
    uint16_t temp_data;
    memmove(&temp_data, (void*)shift, 2);
    if (temp_data != 0x0102) return 1;
    shift += sizeof(uint64_t);

    uint16_t dcrc = DLMS_crc_buff((uint8_t *)shift, sizeof(METER_settings));
    memmove(&temp_data, (void*)(shift + sizeof(METER_settings)), 2);
    if (temp_data != dcrc) return 2;
    
    memmove(&meter.settings, (void*)shift, sizeof(METER_settings));
    shift += sizeof(METER_settings);
    return 0;
}

#pragma pack(push, 1)
typedef struct {
    uint16_t header;    //+2    //+2
    uint16_t crc;       //+2    //+4
    uint32_t ts;        //+4    //+8
    uint32_t work;      //+4    //+12
    uint32_t res;       //+4    //+16
    float itgr[4][4];   //+64   //+80
} DLMS_ARCH_write_cur_data;

typedef struct {
    uint16_t header;    //+2    //+2
    uint16_t crc;       //+2    //+4
    float ApT1;         //+4    //+8
    float ApT2;         //+4    //+12
} DLMS_ARCH_write_cur_data_part;
#pragma pack(pop)

#define DLMS_addr_cur_count_max (DLMS_addr_cur_size_max / sizeof(DLMS_ARCH_write_cur_data))
#define DLMS_addr_cur_HEADER (0xA152)
#define DLMS_addr_cur_part_HEADER (0xA158)

uint8_t DLMS_ARCH_write_cur_part()
{
//    gpio_SET_RELE_OFF;
//	NOP_Delay(NOP_DELAY_MS_TICK/10);
//	gpio_RES_RELE_OFF;

    EEPROM_INT_init();
    uint32_t shift = DLMS_addr_cur_part_start;
    
    DLMS_ARCH_write_cur_data_part cur_d;
    cur_d.header = DLMS_addr_cur_part_HEADER;
    cur_d.ApT1 = METER_A1CxD8_data(1, 1);
    cur_d.ApT2 = METER_A1CxD8_data(1, 2);
    cur_d.crc = DLMS_crc_buff(((uint8_t *)&cur_d) + 4, sizeof(DLMS_ARCH_write_cur_data_part) - 4);
    EEPROM_INT_write(shift, &cur_d, sizeof(DLMS_ARCH_write_cur_data_part));

    EEPROM_INT_deinit();
    
//    gpio_SET_RELE_OFF;
//	NOP_Delay(NOP_DELAY_MS_TICK/10);
//	gpio_RES_RELE_OFF;

    return 0;
}

uint8_t DLMS_ARCH_load_cur_part()
{
//    uint32_t shift = DLMS_addr_cur_part_start;
    DLMS_ARCH_write_cur_data_part * cur_d = (DLMS_ARCH_write_cur_data_part *)(DLMS_addr_cur_part_start);
    if (cur_d->header != DLMS_addr_cur_part_HEADER) {
        return 1;
    }
    if (cur_d->crc != DLMS_crc_buff(((uint8_t *)cur_d) + 4, sizeof(DLMS_ARCH_write_cur_data_part) - 4)) {
        return 1;
    }
    float val;
    uint64_t val64;
    val = cur_d->ApT1;
    val /= meter.vars.K;
    val64 = (uint64_t)val;
    if (meter.itgr[0].Ap < val64) meter.itgr[0].Ap = val64;
    val = cur_d->ApT2;
    val /= meter.vars.K;
    val64 = (uint64_t)val;
    if (meter.itgr[1].Ap < val64) meter.itgr[1].Ap = val64;
    return 0;
}

uint8_t DLMS_ARCH_write_cur()
{
//    gpio_SET_RELE_OFF;
//	NOP_Delay(NOP_DELAY_MS_TICK/10);
//	gpio_RES_RELE_OFF;

    EEPROM_INT_init();
    uint32_t shift = DLMS_addr_cur_start;
    
    {// calc empty rec
        uint8_t save_index = 0;
        uint32_t ts_low = 0xFFFFFFFF;
        for (int i = 0; i < DLMS_addr_cur_count_max; i++) {
            DLMS_ARCH_write_cur_data * cur_d = (DLMS_ARCH_write_cur_data *)(shift + (i * sizeof(DLMS_ARCH_write_cur_data)));
            if (cur_d->header != DLMS_addr_cur_HEADER) {
                save_index = i;
                break;
            }
            if (cur_d->ts < ts_low) {
                ts_low = cur_d->ts;
                save_index = i;
            }
        }
        shift += save_index * sizeof(DLMS_ARCH_write_cur_data);
    }
    {// write data
        DLMS_ARCH_write_cur_data cur_d;
        cur_d.header = DLMS_addr_cur_HEADER;
        cur_d.ts = METER_now();
        cur_d.work = METER_work();
        cur_d.res = 0;
        for (uint8_t OBIS_E = 1; OBIS_E <= 4; OBIS_E++) {
            for (uint8_t OBIS_C = 1; OBIS_C <= 4; OBIS_C++) {
                cur_d.itgr[OBIS_E - 1][OBIS_C - 1] = METER_A1CxD8_data(OBIS_C, OBIS_E);
            }
        }
        cur_d.crc = DLMS_crc_buff(((uint8_t *)&cur_d) + 4, sizeof(DLMS_ARCH_write_cur_data) - 4);
        EEPROM_INT_write(shift, &cur_d, sizeof(DLMS_ARCH_write_cur_data));
    }
    
    EEPROM_INT_deinit();
    
//    gpio_SET_RELE_OFF;
//	NOP_Delay(NOP_DELAY_MS_TICK/10);
//	gpio_RES_RELE_OFF;

    return 0;
}

uint8_t DLMS_ARCH_load_cur()
{
    uint32_t shift = DLMS_addr_cur_start;
    uint16_t temp_data;
    memmove(&temp_data, (void*)shift, 2);
    if (temp_data == 0x0101) {
        shift += sizeof(uint64_t);
        memmove(&meter.itgr[0], (void*)shift, sizeof(METER_itgrator)*TARIFF_ITGR_MAX);
        shift += sizeof(METER_itgrator)*TARIFF_ITGR_MAX;
        uint64_t ts;
        memmove(&ts, (void*)shift, 4);
        METER_set_now(ts);
        shift += sizeof(uint64_t);
        memmove(&ts, (void*)shift, 4);
        METER_set_work(ts);
        shift += sizeof(uint64_t);
        return 0;
    }
    if (temp_data == DLMS_addr_cur_HEADER) {
        uint8_t is_load = 0;
        for (int i = 0; i < DLMS_addr_cur_count_max; i++) {
            DLMS_ARCH_write_cur_data * cur_d = (DLMS_ARCH_write_cur_data *)(shift + (i * sizeof(DLMS_ARCH_write_cur_data)));
            if (cur_d->header != DLMS_addr_cur_HEADER) {
                continue;
            }
            if (cur_d->ts < METER_now()) {
                continue;
            }
            if (cur_d->crc != DLMS_crc_buff(((uint8_t *)cur_d) + 4, sizeof(DLMS_ARCH_write_cur_data) - 4)) {
                continue;
            }
            is_load++;
            
            METER_set_now(cur_d->ts);
            METER_set_work(cur_d->work);
            uint64_t val64;
            for (uint8_t OBIS_E = 1; OBIS_E <= 4; OBIS_E++) {
                for (uint8_t OBIS_C = 1; OBIS_C <= 4; OBIS_C++) {
                    float val = cur_d->itgr[OBIS_E - 1][OBIS_C - 1];
                    val /= meter.vars.K;
                    val64 = (uint64_t)val;
                    switch (OBIS_C) {
                    case  1: meter.itgr[OBIS_E-1].Ap = val64; break;
                    case  2: meter.itgr[OBIS_E-1].An = val64; break;
                    case  3: meter.itgr[OBIS_E-1].Rp = val64; break;
                    case  4: meter.itgr[OBIS_E-1].Rn = val64; break;
                    default: break;
                    }
                }
            }
        }
        if (is_load) return 0;
        //char (*__kaboom)[sizeof( DLMS_ARCH_write_cur_data )] = 1
            
//        shift += sizeof(uint16_t);
//        memmove(&temp_data, (void*)shift, 2);
//        shift += sizeof(uint16_t);
//        uint16_t dcrc = DLMS_crc_buff((uint8_t *)(DLMS_addr_cur_start + sizeof(uint32_t)), DLMS_addr_cur_size_rec - 4);
//        if (dcrc != temp_data) {
//            return 2;
//        }
//        uint64_t val64;
//        for (uint8_t OBIS_E = 1; OBIS_E <= 4; OBIS_E++) {
//            for (uint8_t OBIS_C = 1; OBIS_C <= 4; OBIS_C++) {
//                float val = *((float*)shift);
//                val /= meter.vars.K;
//                val64 = (uint64_t)val;
//                switch (OBIS_C) {
//                case  1: meter.itgr[OBIS_E-1].Ap = val64; break;
//                case  2: meter.itgr[OBIS_E-1].An = val64; break;
//                case  3: meter.itgr[OBIS_E-1].Rp = val64; break;
//                case  4: meter.itgr[OBIS_E-1].Rn = val64; break;
//                default: break;
//                }
//                shift += sizeof(uint32_t);
//            }
//        }
//        METER_set_now(*((uint32_t*)shift));  shift += sizeof(uint32_t);
//        METER_set_work(*((uint32_t*)shift)); shift += sizeof(uint32_t);
//        return 0;
    }
    return 0;
}

#include "defines_HW.h"
uint8_t DLMS_ARCH_write_calib()
{
    uint8_t buf_out[128];
    uint8_t buf_len = ADE_make_calib(buf_out, 0);
    EEPROM_INT_init();
    uint32_t shift = DLMS_addr_calib_start;
    uint32_t ts = 0;
    ts += 0xEF << 0;
    ts += 0x09 << 8;
    //ts += 0x00 << 16;
    ts += buf_len << 24;
    EEPROM_INT_write(shift, &ts, sizeof(uint32_t));
    shift += sizeof(uint32_t);
    EEPROM_INT_write(shift, buf_out, buf_len);
    shift += buf_len;
    return 0;
}

uint8_t DLMS_ARCH_load_calib()
{
    uint32_t shift = DLMS_addr_calib_start;
    uint16_t temp_data;
    memmove(&temp_data, (void*)shift, 2);
    if (temp_data != 0x09EF) return 1;
    shift += sizeof(uint16_t);
    shift += sizeof(uint8_t);
    temp_data = 0;
    memmove(&temp_data, (void*)shift, 1);
    shift += sizeof(uint8_t);
    ADE_use_calib((void*)shift, temp_data);
    shift += temp_data;
    return 0;
}

uint8_t DLMS_ARCH_write_event_U(uint16_t event, float Ucurr, float dU, uint32_t dt_U)
{
    DLMS_ARCH_data_event_U eU;
    eU.dt = METER_now();
    eU.event = event & 0xFF;
    eU.U  = (uint32_t)(Ucurr * 100);
    eU.dU = (uint32_t)(dU * 100);
    eU.dt_U = dt_U;
    eU.work = METER_work();
    return DLMS_ARCH_write((DLMS_ARCH_index)(event >> 8), &eU);
}

uint8_t DLMS_ARCH_write_event_I(uint16_t event)
{
    DLMS_ARCH_data_event_I eI;
    eI.dt = METER_now();
    eI.event = event & 0xFF;
    eI.work = METER_work();
    return DLMS_ARCH_write((DLMS_ARCH_index)(event >> 8), &eI);
}

uint8_t DLMS_ARCH_write_telesignaling(uint16_t event, uint8_t rele, uint8_t ext)
{
    DLMS_ARCH_data_telesignaling tsig;
    tsig.dt = METER_now();
    tsig.work = METER_work();
    tsig.event = event & 0xFF;
    tsig.channel = rele;
    tsig.addr = ext;
    return DLMS_ARCH_write((DLMS_ARCH_index)(event >> 8), &tsig);
}
