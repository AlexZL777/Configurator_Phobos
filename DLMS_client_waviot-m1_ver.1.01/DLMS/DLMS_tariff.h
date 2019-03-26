#ifndef _DLMS_TARIFF_H_
#define _DLMS_TARIFF_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)
//zone:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    4бита - номер тарифа
//    11бит - время с начала суток в минутах когда начитается зона
typedef struct {
    uint16_t start_zone: 11;
    uint16_t tariff: 4;
    uint16_t next: 1;
} TARIFF_zone;

//week:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    7бит  - маска дней недели когда активено расписание данного дня (старший?младший - пн)
//    2бита - резерв
//    6бит  - id дня
typedef struct {
    uint16_t day_id: 6;
    uint16_t reserv: 2;
    uint16_t mask_week: 7;
    uint16_t next: 1;
} TARIFF_week;

//season:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    4бита - месяц
//    5бит  - число месяца
//    6бит  - id недели
typedef struct {
    uint16_t week_id: 6;
    uint16_t day: 5;
    uint16_t month: 4;
    uint16_t next: 1;
} TARIFF_season;

//special_day:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    4бита - месяц
//    5бит  - число месяца
//    6бит  - id дня
typedef struct {
    uint16_t day_id: 6;
    uint16_t day: 5;
    uint16_t month: 4;
    uint16_t next: 1;
} TARIFF_special_day;

//самостоятельные блоки:
//days:
//    2бита - заголовок элемента дней = 2
//    6бит  - id дня
//    zone,[zone,...]

//weeks:
//    2бита - заголовок элемента недель = 3
//    6бит  - id недели
//    week,[week,...]

//seasons:
//    2бита - заголовок расширенного элемента = 1
//    2бита - подзаголовок элемента сезонов = 1
//    4бита - резерв
//    season,[season,...]

//special_day:
//    2бита - заголовок расширенного элемента = 1
//    2бита - подзаголовок элемента специальных дней = 2
//    4бита - резерв
//    special_day,[special_day,...]

//activate:
//    2бита - заголовок расширенного элемента = 1
//    2бита - подзаголовок элемента даты активации = 3
//    4бита - резерв
//    32бита- timestamp активации расписания, если блок отсутсвует или время в прошлом - теекущее расписание
typedef union {
    struct {
        uint8_t day_id:         6;
        uint8_t id_block:       2; // = 2
    } days;
    struct {
        uint8_t week_id:        6;
        uint8_t id_block:       2; // = 3
    } weeks;
    struct {
        uint8_t res:            4;
        uint8_t id_sub_block:   2; // = 1
        uint8_t id_block:       2; // = 1
    } seasons;
    struct {
        uint8_t res:            4;
        uint8_t id_sub_block:   2; // = 2
        uint8_t id_block:       2; // = 1
    } special_day;
    struct {
        uint8_t res:            4;
        uint8_t id_sub_block:   2; // = 3
        uint8_t id_block:       2; // = 1
    } activate;
    uint8_t data;
} TARIFF_header;

//reserv:
//    2бита - резерв = 0
//    или
//    2бита - заголовок расширенного элемента = 1
//    2бита - подзаголовок элемента даты активации = 0
#pragma pack(pop)

typedef struct {
    uint8_t days;
    uint8_t weeks;
    uint8_t season;
    uint8_t special;
    uint8_t activate;
} DLMS_tariff_index;

#define DLMS_tariff_index_init_val (0xFF)
#define DLMS_tariff_size (256)

extern const uint8_t TARIFF_default[]; // дефолтное расписание с 0 единственным тарифом

void TARIFF_block_to_u8(void *b, uint8_t *first, uint8_t *second);
void TARIFF_block_from_u8(void *b, uint8_t first, uint8_t second);
void DLMS_tariff_clear_start_index(DLMS_tariff_index * ti);
void DLMS_tariff_search_start_index(uint8_t *tt, DLMS_tariff_index *ti); // обновить индексы после применения индексов
void DLMS_tariff_search_start_index_active(void);
uint32_t DLMS_tariff_search_activate(uint8_t *tt); // получить время активации
void DLMS_tariff_active_passive(void); // переключение расписаний
uint16_t DLMS_tariff_get_size(uint8_t * tt); // получить длинну расписания для отправки по радио
uint8_t DLMS_tariff_test_buf(uint8_t* buff, uint16_t buff_len); // тест корректности данных // 0 - нет ошибок

uint8_t DLMS_tariff_dayid_from_special(uint8_t month, uint8_t day); // специальный день
uint8_t DLMS_tariff_dayid_from_week(uint8_t week_id, uint8_t wday); // день из недели
uint8_t DLMS_tariff_weekid_from_season(uint8_t month, uint8_t day); // неделя от сизона
uint8_t DLMS_tariff_start_zone_from_dayid(uint8_t day_id); // зона от дня
uint8_t DLMS_tariff_zone_start_index_from_timestamp(uint32_t timestamp); // зона от времени, не учитывает начало дня
uint8_t DLMS_tariff_from_zone(uint8_t zone_index, uint32_t timestamp_zone); // тариф из зоны

uint8_t DLMS_tariff_from_timestamp(uint32_t timestamp); // 0 = first

#ifdef __cplusplus
}
#endif

#endif // _DLMS_TARIFF_H_
