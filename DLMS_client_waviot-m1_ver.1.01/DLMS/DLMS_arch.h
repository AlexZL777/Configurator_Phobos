#ifndef _DLMS_ARCH_H_
#define _DLMS_ARCH_H_

#include "DLMS_HDLC.h"
#include "DLMS_radio.h"
#include "flash_ext.h"
#include "flash_int.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DLMS_ARCH_page_size         (FLASH_EXT_page_size)
#define DLMS_ARCH_start_addr        (FLASH_EXT_start_arch)

#define DLMS_addr_calib_size_max    (128)
#define DLMS_addr_cur_size_max      (1024 - DLMS_addr_calib_size_max)
#define DLMS_addr_settings_size_max (1024*2)

//#ifdef  EEPROM_INT_start_arch 
#define DLMS_addr_calib_start       (EEPROM_INT_start_arch)
#define DLMS_addr_cur_start         (DLMS_addr_calib_start + DLMS_addr_calib_size_max)
#define DLMS_addr_settings_start    (DLMS_addr_cur_start + DLMS_addr_cur_size_max)
#define EEPROM_INT_nbfi_data        (EEPROM_INT_start_arch + 1024*5)
#define DLMS_addr_cur_part_start    (EEPROM_INT_nbfi_data + 256)
//#else
//#define DLMS_addr_calib_start       (FLASH_INT_start_arch) // todo
//#define DLMS_addr_cur_start         (FLASH_INT_start_arch)
//#define DLMS_addr_settings_start    (DLMS_ARCH_settings_start)
//#define EEPROM_INT_nbfi_data        (EEPROM_INT_start_arch + 1024*5)
//#endif
    
typedef enum {
    DLMS_ARCH_event_U       = 0,
    DLMS_ARCH_event_I       = 1,
    DLMS_ARCH_event_rele    = 2,
    DLMS_ARCH_event_prog    = 3,
    DLMS_ARCH_event_ext     = 4,
    DLMS_ARCH_event_com     = 5,
    DLMS_ARCH_event_access  = 6,
    DLMS_ARCH_event_diagnos = 7,
    DLMS_ARCH_event_tg_pow  = 8,
    DLMS_ARCH_event_quality = 9,
    DLMS_ARCH_event_IO      =10,
    DLMS_ARCH_telesignaling =11,
    DLMS_ARCH_profile_year  =12,
    DLMS_ARCH_profile_month =13,
    DLMS_ARCH_profile_day   =14,
    DLMS_ARCH_profile_hour  =15,
    DLMS_ARCH_profile_set   =16,
    DLMS_ARCH_profile_NONE =255,
} DLMS_ARCH_index;

typedef enum {
    DLMS_EVENT_U_A_off              = 0x0001, //+Фаза А - пропадание напряжения
    DLMS_EVENT_U_A_on               = 0x0002, //+Фаза А - восстановление напряжения
    DLMS_EVENT_U_B_off              = 0x0003, //+Фаза В - пропадание напряжения
    DLMS_EVENT_U_B_on               = 0x0004, //+Фаза В - восстановление напряжения
    DLMS_EVENT_U_C_off              = 0x0005, //+Фаза С - пропадание напряжения
    DLMS_EVENT_U_C_on               = 0x0006, //+Фаза С - восстановление напряжения
    DLMS_EVENT_U_lmt_up_start       = 0x0007, // Превышение напряжения любой фазы
    DLMS_EVENT_U_lmt_up_stop        = 0x0008, // Окончание перенапряжения любой фазы
    DLMS_EVENT_U_lmt_down_start     = 0x0009, // Низкое напряжение любой фазы - начало
    DLMS_EVENT_U_lmt_down_stop      = 0x000A, // Низкое напряжение любой фазы - окончание
    DLMS_EVENT_U_asymmetry_start    = 0x000B, // Превышение коэффициента несимметрии напряжений по обратной последовательности - начало
    DLMS_EVENT_U_asymmetry_stop     = 0x000C, // Превышение коэффициента несимметрии напряжений по обратной последовательности - окончание
    DLMS_EVENT_U_A_lmt_up_start     = 0x000D, //+Фаза А - перенапряжение начало
    DLMS_EVENT_U_A_lmt_up_stop      = 0x000E, //+Фаза А - перенапряжение окончание
    DLMS_EVENT_U_B_lmt_up_start     = 0x000F, //+Фаза В - перенапряжение начало
    DLMS_EVENT_U_B_lmt_up_stop      = 0x0010, //+Фаза В - перенапряжение окончание
    DLMS_EVENT_U_C_lmt_up_start     = 0x0011, //+Фаза С - перенапряжение начало
    DLMS_EVENT_U_C_lmt_up_stop      = 0x0012, //+Фаза С - перенапряжение окончание
    DLMS_EVENT_U_A_lmt_down_start   = 0x0013, //+Фаза А - провал начало
    DLMS_EVENT_U_A_lmt_down_stop    = 0x0014, //+Фаза А - провал окончание
    DLMS_EVENT_U_B_lmt_down_start   = 0x0015, //+Фаза В - провал начало
    DLMS_EVENT_U_B_lmt_down_stop    = 0x0016, //+Фаза В - провал окончание
    DLMS_EVENT_U_C_lmt_down_start   = 0x0017, //+Фаза С - провал начало
    DLMS_EVENT_U_C_lmt_down_stop    = 0x0018, //+Фаза С - провал окончание
    DLMS_EVENT_U_ACB_start          = 0x0019, //+Неправильная последовательность фаз начало
    DLMS_EVENT_U_ACB_stop           = 0x001A, //+Неправильная последовательность фаз окончание

    DLMS_EVENT_I_A_back_start       = 0x0101, //+Фаза А - экспорт начало
    DLMS_EVENT_I_A_back_stop        = 0x0102, //+Фаза А - экспорт окончание
    DLMS_EVENT_I_B_back_start       = 0x0103, //+Фаза В - экспорт начало
    DLMS_EVENT_I_B_back_stop        = 0x0104, //+Фаза В - экспорт окончание
    DLMS_EVENT_I_C_back_start       = 0x0105, //+Фаза С - экспорт начало
    DLMS_EVENT_I_C_back_stop        = 0x0106, //+Фаза С - экспорт окончание
    DLMS_EVENT_I_A_tt_start         = 0x0107, // Обрыв трансформатора тока фазы А
    DLMS_EVENT_I_A_tt_stop          = 0x0108, // Восстановление трансформатора тока фазы А
    DLMS_EVENT_I_B_tt_start         = 0x0109, // Обрыв трансформатора тока фазы В
    DLMS_EVENT_I_B_tt_stop          = 0x010A, // Восстановление трансформатора тока фазы В
    DLMS_EVENT_I_C_tt_start         = 0x010B, // Обрыв трансформатора тока фазы С
    DLMS_EVENT_I_C_tt_stop          = 0x010C, // Восстановление трансформатора тока фазы С
    DLMS_EVENT_I_delta_start        = 0x010D, //+Разбаланс токов - начало
    DLMS_EVENT_I_delta_stop         = 0x010E, //+Разбаланс токов - окончание
    DLMS_EVENT_I_kz_tt_start        = 0x010F, // Замыкание трансформатора тока — начало
    DLMS_EVENT_I_kz_tt_stop         = 0x0110, // Окончание замыкания трансформатора тока
    DLMS_EVENT_I_limit_start        = 0x0111, // Превышение тока любой фазы — начало
    DLMS_EVENT_I_limit_stop         = 0x0112, // Окончание превышения тока любой фазы
    DLMS_EVENT_I_A_InoU_start       = 0x0113, //+Фаза А - наличие тока при отсутствии напряжения начало
    DLMS_EVENT_I_A_InoU_stop        = 0x0114, //+Фаза А - наличие тока при отсутствии напряжения окончание
    DLMS_EVENT_I_B_InoU_start       = 0x0115, //+Фаза В - наличие тока при отсутствии напряжения начало
    DLMS_EVENT_I_B_InoU_stop        = 0x0116, //+Фаза В - наличие тока при отсутствии напряжения окончание
    DLMS_EVENT_I_C_InoU_start       = 0x0117, //+Фаза С - наличие тока при отсутствии напряжения начало
    DLMS_EVENT_I_C_InoU_stop        = 0x0118, //+Фаза С - наличие тока при отсутствии напряжения окончание
    DLMS_EVENT_I_A_limit_start      = 0x0119, //+Фаза А - превышение максимального тока начало
    DLMS_EVENT_I_A_limit_stop       = 0x011A, //+Фаза А - превышение максимального тока окончание
    DLMS_EVENT_I_B_limit_start      = 0x011B, //+Фаза В - превышение максимального тока начало
    DLMS_EVENT_I_B_limit_stop       = 0x011C, //+Фаза В - превышение максимального тока окончание
    DLMS_EVENT_I_C_limit_start      = 0x011D, //+Фаза С - превышение максимального тока начало
    DLMS_EVENT_I_C_limit_stop       = 0x011E, //+Фаза С - превышение максимального тока окончание
    DLMS_EVENT_I_n                  = 0x011F, // Наличие тока при отсутствии напряжения (обрыв нейтрали)

    DLMS_EVENT_rele_power_off       = 0x0201, // Выключение питания счетчика
    DLMS_EVENT_rele_power_on        = 0x0202, // Включение питания счетчика
    DLMS_EVENT_rele_radio_off       = 0x0203, // Выключение абонента дистанционное
    DLMS_EVENT_rele_radio_on        = 0x0204, // Включение абонента дистанционное
    DLMS_EVENT_rele_access_on       = 0x0205, // Получение разрешения на включение абоненту
    DLMS_EVENT_rele_local_off       = 0x0206, // Выключение реле нагрузки абонентом
    DLMS_EVENT_rele_local_on        = 0x0207, // Включение реле нагрузки абонентом
    DLMS_EVENT_rele_limit_P_off     = 0x0208, // Выключение локальное по превышению лимита мощности
    DLMS_EVENT_rele_limit_I_off     = 0x0209, // Выключение локальное по превышению максимального тока
    DLMS_EVENT_rele_magnetic_off    = 0x020A, // Выключение локальное при воздействии магнитного поля
    DLMS_EVENT_rele_limit_U_off     = 0x020B, // Выключение локальное по превышению напряжения
    DLMS_EVENT_rele_limit_U_on      = 0x020C, // Включение локальное при возвращение напряжения в норму
    DLMS_EVENT_rele_InoU_off        = 0x020D, // Выключение локальное по наличию тока при отсутствии напряжения
    DLMS_EVENT_rele_delta_off       = 0x020E, // Выключение локальное по разбалансу токов
    DLMS_EVENT_rele_T_off           = 0x020F, // Выключение локальное по температуре
    DLMS_EVENT_rele_ext_power_on    = 0x0210, // Включение резервного питания
    DLMS_EVENT_rele_ext_power_off   = 0x0211, // Отключение резервного питания
    DLMS_EVENT_rele_timer_on        = 0x0212, // Включение локальное по времени

    DLMS_EVENT_prog_RS485_1         = 0x0301, //Изменение адреса или скорости обмена RS-485-1
    DLMS_EVENT_prog_RS485_2         = 0x0302, //Изменение адреса или скорости обмена RS-485-2
    DLMS_EVENT_prog_set_time        = 0x0303, //Установка времени
    DLMS_EVENT_prog_set_summer      = 0x0304, //Изменение параметров перехода на летнее время
    DLMS_EVENT_prog_tariff_season   = 0x0305, //Изменение сезонного профиля тарифного расписания (ТР)
    DLMS_EVENT_prog_tariff_week     = 0x0306, //Изменение недельного профиля ТР
    DLMS_EVENT_prog_tariff_day      = 0x0307, //Изменение суточного профиля ТР
    DLMS_EVENT_prog_tariff_start_dt = 0x0308, //Изменение даты активации ТР
    DLMS_EVENT_prog_tariff_activ    = 0x0309, //Активация ТР
    DLMS_EVENT_prog_day_hour_month  = 0x030A, //Изменение  расчетного дня/часа (РДЧ)
//    DLMS_EVENT_prog_ligth_manual    = 0x030B, //Изменение режима индикации (параметры)
//    DLMS_EVENT_prog_ligth_auto      = 0x030C, //Изменение режима индикации (автопереключение)
    DLMS_EVENT_prog_pass_low        = 0x030D, //Изменение пароля низкой секретности (на чтение)
    DLMS_EVENT_prog_pass_high       = 0x030E, //Изменение пароля высокой секретности (на запись)
    DLMS_EVENT_prog_data_point      = 0x030F, //Изменение данных точки учета
    DLMS_EVENT_prog_ti              = 0x0310, //Изменение коэффициента трансформации по току
    DLMS_EVENT_prog_tu              = 0x0311, //Изменение коэффициента трансформации по напряжению
//    DLMS_EVENT_prog_LEP             = 0x0312, //Изменение параметров линии для вычисления потерь в ЛЭП
    DLMS_EVENT_prog_power_P         = 0x0313, //Изменение лимита мощности для отключения
    DLMS_EVENT_prog_timeout_P       = 0x0314, //Изменение интервала времени на отключение по мощности
    DLMS_EVENT_prog_timeout_I       = 0x0315, //Изменение интервала времени на отключение по превышению максимального тока
    DLMS_EVENT_prog_timeout_U       = 0x0316, //Изменение интервала времени на отключение по максимальному напряжению
//    DLMS_EVENT_prog_timeout_magnetic= 0x0317, //Изменение интервала времени на отключение по воздействию магнитного поля
    DLMS_EVENT_prog_limit_U_off     = 0x0318, //Изменение порога для фиксации перерыва в питании
    DLMS_EVENT_prog_limit_U_up      = 0x0319, //Изменение порога для фиксации перенапряжения
    DLMS_EVENT_prog_limit_U_down    = 0x031A, //Изменение порога для фиксации провала напряжения
    DLMS_EVENT_prog_limit_tg        = 0x031B, //Изменение порога для фиксации превышения тангенса
//    DLMS_EVENT_prog_limit_U_delta   = 0x031C, //Изменение порога для фиксации  коэффициента несимметрии напряжений
//    DLMS_EVENT_prog_let_U           = 0x031D, //Изменение согласованного напряжения
    DLMS_EVENT_prog_timeout_Pmax    = 0x031E, //Изменение интервала интегрирования пиковой мощности
    DLMS_EVENT_prog_dt_profile_1    = 0x031F, //Изменение периода захвата профиля 1
    DLMS_EVENT_prog_dt_profile_2    = 0x0320, //Изменение периода захвата профиля 2
//    DLMS_EVENT_prog_LCD_ligth       = 0x0321, //Изменение режима подсветки LCD
//    DLMS_EVENT_prog_         = 0x0322, // 34	Изменение режима телеметрии
    DLMS_EVENT_prog_clear_month     = 0x0323, //Очистка месячного журнала
    DLMS_EVENT_prog_clear_day       = 0x0324, //Очистка суточного журнала
    DLMS_EVENT_prog_clear_U         = 0x0325, //Очистка журнала напряжения
    DLMS_EVENT_prog_clear_I         = 0x0326, //Очистка журнала тока
    DLMS_EVENT_prog_clear_rele      = 0x0327, //Очистка журнала вкл/выкл
    DLMS_EVENT_prog_clear_ext       = 0x0328, //Очистка журнала внешних воздействий
    DLMS_EVENT_prog_clear_com       = 0x0329, //Очистка журнала соединений
    DLMS_EVENT_prog_clear_access    = 0x032A, //Очистка журнала несанкционированного доступа
    DLMS_EVENT_prog_clear_diagnos   = 0x032B, //Очистка журнала качества сети
    DLMS_EVENT_prog_clear_tg        = 0x032C, //Очистка журнала тангенса
    DLMS_EVENT_prog_clear_IO        = 0x032D, //Очистка журнала входов/выходов
    DLMS_EVENT_prog_clear_profile_1 = 0x032E, //Очистка профиля 1
    DLMS_EVENT_prog_clear_profile_2 = 0x032F, //Очистка профиля 2
//    DLMS_EVENT_prog_clear_profile_3 = 0x0330, //Очистка профиля 3
    DLMS_EVENT_prog_spec_days       = 0x0331, //Изменение таблицы специальных дней
//    DLMS_EVENT_prog_rele            = 0x0332, //Изменение режима управления реле
//    DLMS_EVENT_prog_write_month     = 0x0333, //Фиксация показаний в месячном журнале
//    DLMS_EVENT_prog_         = 0x0334, // 52	Изменение режима инициативного выхода
//    DLMS_EVENT_prog_         = 0x0335, // 53	Изменение одноадресного ключа шифрования для низкой секретности
//    DLMS_EVENT_prog_         = 0x0336, // 54	Изменение широковещательного ключа шифрования для низкой секретности
//    DLMS_EVENT_prog_         = 0x0337, // 55	Изменение одноадресного ключа шифрования для высокой секретности
//    DLMS_EVENT_prog_         = 0x0338, // 56	Изменение широковещательного ключа шифрования для высокой секретности
//    DLMS_EVENT_prog_         = 0x0339, // 57	Изменение ключа аутентификации для высокой секретности
//    DLMS_EVENT_prog_         = 0x033A, // 58	Изменение мастер-ключа
//    DLMS_EVENT_prog_         = 0x033B, // 59	Изменение уровня безопасности для низкой секретности
//    DLMS_EVENT_prog_         = 0x033C, // 60	Изменение уровня безопасности для низкой секретности
//    DLMS_EVENT_prog_display         = 0x033D, //Изменение номера дистанционного дисплея
//    DLMS_EVENT_prog_mode_P          = 0x033E, //Изменение режима учета активной энергии
//    DLMS_EVENT_prog_set_time_GPS    = 0x033F, //Установка времени по GPS/ГЛОНАСС
//    DLMS_EVENT_prog_         = 0x0340, // 64	Изменение режима отключения по обрыву нейтрали
    DLMS_EVENT_prog_update_SW       = 0x0341, //Обновление ПО
//    DLMS_EVENT_prog_         = 0x0342, // 66	Изменение режима отключения по разбалансу токов
//    DLMS_EVENT_prog_         = 0x0343, // 67	Изменение режима отключения по температуре
    DLMS_EVENT_prog_shift_time      = 0x0344, //Коррекция времени

    DLMS_EVENT_ext_magnetic_start   = 0x0401, //Магнитное поле - начало
    DLMS_EVENT_ext_magnetic_stop    = 0x0402, //Магнитное поле - окончание
    DLMS_EVENT_ext_cover            = 0x0403, //Срабатывание электронной пломбы крышки клеммников
    DLMS_EVENT_ext_body             = 0x0404, //Срабатывание электронной пломбы корпуса

    DLMS_EVENT_com_connect          = 0x0501, //Разорвано соединение (интерфейс)
    DLMS_EVENT_com_disconnect       = 0x0502, //Установлено соединение (интерфейс)

    DLMS_EVENT_access_false         = 0x0601, //Попытка несанкционированного доступа (интерфейс)
    DLMS_EVENT_access_protocol      = 0x0602, //Нарушение требований протокола

    DLMS_EVENT_diagnos_init         = 0x0701, //Инициализация счетчика
    DLMS_EVENT_diagnos_meterage_fail= 0x0702, //Измерительный блок — ошибка
    DLMS_EVENT_diagnos_meterage_ok  = 0x0703, //Измерительный блок — норма
    DLMS_EVENT_diagnos_calc_ok      = 0x0704, //Вычислительный блок — ошибка
    DLMS_EVENT_diagnos_RTC_fail     = 0x0705, //Часы реального времени — ошибка
    DLMS_EVENT_diagnos_RTC_ok       = 0x0706, //Часы реального времени — норма
    DLMS_EVENT_diagnos_POW_fial     = 0x0707, //Блок питания - ошибка
    DLMS_EVENT_diagnos_POW_ok       = 0x0708, //Блок питания - норма
    DLMS_EVENT_diagnos_display_fail = 0x0709, //Дисплей — ошибка
    DLMS_EVENT_diagnos_display_ok   = 0x070A, //Дисплей — норма
    DLMS_EVENT_diagnos_FLASH_fail   = 0x070B, //Блок памяти — ошибка
    DLMS_EVENT_diagnos_FLASH_ok     = 0x070C, //Блок памяти - норма

    DLMS_EVENT_tg_pow_start         = 0x0801, //Превышение установленного порога - начало
    DLMS_EVENT_tg_pow_stop          = 0x0802, //Превышение установленного порога - окончание
} DLMS_EVENT;

typedef uint8_t (*electro_make_packet)(uint8_t *buf, uint16_t index_head, uint16_t index_send, uint8_t shift);

#pragma pack(push, 1)
typedef struct {
    uint32_t mem_start;
    uint32_t mem_end;
    uint16_t rec_size;
    uint16_t default_sec_before_send_max;
    electro_make_packet emp;
} DLMS_ARCH_settings;

typedef struct {
    const DLMS_ARCH_settings * settings;
    uint16_t index_head;            // индекс свободной первой свободной записи
    uint16_t index_send;            // индекс записи требующей отправки
    uint16_t index_last;            // индекс первой записи с данными
    uint16_t sec_before_send_max;   // время до отправки
    uint16_t sec_before_send;       // время до отправки - таймер
    uint32_t timestamp_last;        // время последней записи архива
} DLMS_ARCH_info;

typedef struct {
    uint32_t dt;    // время - всегда первое в структуре
    uint32_t Ap[4];
    uint32_t An[4];
    uint32_t Rp[4];
    uint32_t Rn[4];
    uint32_t P_max;
    uint32_t work;
    uint16_t res;
    uint16_t CRC_val;
//} DLMS_ARCH_data_profile_year, DLMS_ARCH_data_profile_month, DLMS_ARCH_data_profile_day;
} DLMS_ARCH_data_profile_year, DLMS_ARCH_data_profile_month, DLMS_ARCH_data_profile_day, DLMS_ARCH_data_profile_hour;

//typedef struct {
//    uint32_t dt;    // время - всегда первое в структуре
//    uint32_t Ap;
//    uint32_t An;
//    uint32_t Rp;
//    uint32_t Rn;
//    uint32_t P_max;
//    uint16_t res;
//    uint16_t CRC_val;
//} DLMS_ARCH_data_profile_hour;

typedef struct {
    uint32_t dt;    // время - всегда первое в структуре
    struct {
        uint32_t obis;
        uint32_t val;
    } data[8];
    uint16_t res;
    uint16_t CRC_val;
} DLMS_ARCH_data_profile_set;

typedef struct {    // 0.b.99.98.0.255
    uint32_t dt;    // время - всегда первое в структуре
    uint8_t  event;
    uint16_t U;
    uint16_t dU;
    uint32_t dt_U;
    uint32_t work;
    uint8_t  res;
    uint16_t CRC_val;
} DLMS_ARCH_data_event_U;

typedef struct {    // 0.b.99.98.1.255 0.b.99.98.2.255 0.b.99.98.3.255 0.b.99.98.4.255 0.b.99.98.7.255 0.b.99.98.8.255 0.b.99.98.9.255 0.b.99.98.10.255
    uint32_t dt;    // время - всегда первое в структуре
    uint32_t work;
    uint8_t  event;
    uint8_t  res;
    uint16_t CRC_val;
} DLMS_ARCH_data_event_I, DLMS_ARCH_data_event_rele, DLMS_ARCH_data_event_prog, DLMS_ARCH_data_event_ext, DLMS_ARCH_data_event_diagnos, DLMS_ARCH_data_event_tg_pow, DLMS_ARCH_data_event_quality, DLMS_ARCH_data_event_IO;

typedef struct {    // 0.b.99.98.5.255 0.b.99.98.6.255 1.0.94.07.6.255
    uint32_t dt;    // время - всегда первое в структуре
    uint32_t work;
    uint8_t  event;
    uint8_t  channel;   // rele
    uint8_t  addr;      // extern event
    uint8_t  res;
    uint16_t CRC_val;
} DLMS_ARCH_data_event_com, DLMS_ARCH_data_event_access, DLMS_ARCH_data_telesignaling;
#pragma pack(pop)

extern DLMS_ARCH_info arch_info[17];

uint16_t DLMS_ARCH_info_count_max(DLMS_ARCH_info * ainfo);

uint8_t DLMS_ARCH_write(DLMS_ARCH_index ai, void* data);
uint8_t DLMS_ARCH_read(DLMS_ARCH_index ai, void* data, uint16_t index);
uint8_t DLMS_ARCH_read_next(DLMS_ARCH_index ai, void *data);
uint8_t DLMS_ARCH_init_Newton(DLMS_ARCH_index ai);
uint8_t DLMS_ARCH_init_Line(DLMS_ARCH_index ai, uint32_t * ts_update);
uint16_t DLMS_ARCH_max_count(DLMS_ARCH_index ai);
uint16_t DLMS_ARCH_fill_count(DLMS_ARCH_index ai);

uint8_t DLMS_ARCH_write_settings();
uint8_t DLMS_ARCH_load_settings();
uint8_t DLMS_ARCH_write_cur_part();
uint8_t DLMS_ARCH_load_cur_part();
uint8_t DLMS_ARCH_write_cur();
uint8_t DLMS_ARCH_load_cur();
uint8_t DLMS_ARCH_write_calib();
uint8_t DLMS_ARCH_load_calib();

uint8_t DLMS_ARCH_write_event_U(uint16_t event, float Ucurr, float dU, uint32_t dt_U);
uint8_t DLMS_ARCH_write_event_I(uint16_t event);
#define DLMS_ARCH_write_event_rele DLMS_ARCH_write_event_I
uint8_t DLMS_ARCH_write_event_prog(uint16_t event, uint8_t channel); // Номер канала (интерфейс)
#define DLMS_ARCH_write_event_ext DLMS_ARCH_write_event_I
uint8_t DLMS_ARCH_write_event_com(uint16_t event, uint8_t channel, uint8_t client); // Номер канала (интерфейс) // Адрес (клиента)
#define DLMS_ARCH_write_event_access DLMS_ARCH_write_event_com
#define DLMS_ARCH_write_event_diagnos DLMS_ARCH_write_event_I
#define DLMS_ARCH_write_event_tg_pow DLMS_ARCH_write_event_I // Статус входов/выходов 0.0.96.3.0.255
#define DLMS_ARCH_write_event_quality DLMS_ARCH_write_event_I // Статус качества сети 0.0.96.5.1.255
#define DLMS_ARCH_write_event_IO DLMS_ARCH_write_event_I // Статус входов/выходов 0.0.96.3.0.255
uint8_t DLMS_ARCH_write_telesignaling(uint16_t event, uint8_t rele, uint8_t ext); // Код события по напряжению //  Срабатывание силового реле // Внешних воздействий

#ifdef __cplusplus
}
#endif

#endif // _DLMS_ARCH_H_
