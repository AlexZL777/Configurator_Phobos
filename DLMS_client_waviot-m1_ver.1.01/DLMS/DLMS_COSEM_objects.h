#ifndef _DLMS_COSEM_OBJECTS_H_
#define _DLMS_COSEM_OBJECTS_H_

#include <stdint.h>
#include "DLMS_enums.h"
#include "DLMS_HDLC.h"
#include "DLMS_PDU_buf.h"
//#include "enums.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

//typedef struct  {
//    DLMS_ACCESS_MODE access;
//    DLMS_METHOD_ACCESS_MODE methodAccess;
//    DLMS_DATA_TYPE type;
//    DLMS_OBJECT_TYPE otype;
//} COSEM_OBJECT_Attribute____rem;

//typedef PDU_DataAccessResult (*COA_rw)(HDLC_BUF *hdlc, PDU_header *pduHeader, COSEM_OBJECT *cobj, DLMS_PDU_BUF * pduData); // COSEM_OBJECT_attr_rw
typedef PDU_DataAccessResult (*COA_rw)(void *v_hdlc, void *v_pduHeader, const void *cobj, void *v_pduData); // COSEM_OBJECT_attr_rw

typedef struct  {
    uint8_t access_public;          // DLMS_ACCESS_MODE
    uint8_t access_reader;          // DLMS_ACCESS_MODE
    uint16_t access_config;          // DLMS_ACCESS_MODE
    COA_rw rw;    // function
} COSEM_OBJECT_Attribute;

#pragma pack(pop)

typedef struct  {
    OBIS obis;
    uint16_t version;
    uint16_t type;               // DLMS_OBJECT_TYPE
    uint16_t access_min_lvl;     // DLMS_ACCESS_MODE
    const COSEM_OBJECT_Attribute * attr;
    const COSEM_OBJECT_Attribute * method;
} COSEM_OBJECT;

uint32_t obis_attr_val_int(OBIS *obis, uint8_t rw_attr, uint32_t val);
void ELECTRO5_HDLC_PDU_controller(HDLC_BUF *hdlc);

PDU_DataAccessResult attr_0_0_40_0_0_255___1(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Логическое имя объекта
PDU_DataAccessResult meth_0_0_40_0_0_255___1(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Логическое имя объекта
PDU_DataAccessResult attr_obj_list___2(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // список объектов от авторизации
extern const COSEM_OBJECT_Attribute attr_0_0_40_0_0_255[]; // Объект текущего соединения (ОТС)
extern const COSEM_OBJECT_Attribute meth_0_0_40_0_0_255[]; // Объект текущего соединения (ОТС)

PDU_DataAccessResult attr_logical_name___1(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Логическое имя объекта
PDU_DataAccessResult attr_dev_name___2(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Имя устройства
extern const COSEM_OBJECT_Attribute attr_0_0_42_0_0_255[]; // Логическое имя устройства

PDU_DataAccessResult attr_clock___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Логическое имя объекта
PDU_DataAccessResult meth_clock___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Логическое имя объекта
extern const COSEM_OBJECT_Attribute attr_clock[]; // Часы
extern const COSEM_OBJECT_Attribute meth_clock[]; // Часы

PDU_DataAccessResult attr_reg_value___2_data(DLMS_PDU_BUF * pb, const COSEM_OBJECT *cobj);
PDU_DataAccessResult attr_reg_value___2(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
PDU_DataAccessResult attr_reg_value___3_data(DLMS_PDU_BUF * pb, const COSEM_OBJECT *cobj);
PDU_DataAccessResult attr_reg_value___3(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Масштаб и ед. измерения
extern const COSEM_OBJECT_Attribute attr_reg_value[]; // мгновенные

PDU_DataAccessResult attr_reg_ext_value___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); //
extern const COSEM_OBJECT_Attribute attr_reg_ext_value[]; //

PDU_DataAccessResult attr_reg_demand___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
extern const COSEM_OBJECT_Attribute attr_reg_demand[]; //
extern const COSEM_OBJECT_Attribute meth_reg_demand[]; //

PDU_DataAccessResult attr_profile_display___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
extern const COSEM_OBJECT_Attribute attr_profile_display[]; // профиль

PDU_DataAccessResult attr_profile_0___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
extern const COSEM_OBJECT_Attribute attr_profile_0[]; // профиль
extern const COSEM_OBJECT_Attribute meth_profile_0[]; // профиль

PDU_DataAccessResult attr_profile_event___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
extern const COSEM_OBJECT_Attribute attr_profile_event[]; // профиль событий
extern const COSEM_OBJECT_Attribute meth_profile_event[]; // профиль событий

PDU_DataAccessResult attr_passport_data(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
extern const COSEM_OBJECT_Attribute attr_passport[]; // паспорт
extern const COSEM_OBJECT_Attribute attr_passport_rw[]; // паспорт

PDU_DataAccessResult attr_event_data___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Значение
extern const COSEM_OBJECT_Attribute attr_event[];

PDU_DataAccessResult attr_rs___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // RS
extern const COSEM_OBJECT_Attribute attr_rs[]; // RS

PDU_DataAccessResult attr_register_rw___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // настройки
extern const COSEM_OBJECT_Attribute attr_register_rw[]; // настройки

PDU_DataAccessResult attr_tariff___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // tariff
extern const COSEM_OBJECT_Attribute attr_tariff[]; // tariff
extern const COSEM_OBJECT_Attribute meth_tariff[]; // tariff

PDU_DataAccessResult attr_spec_days___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // spec_days
extern const COSEM_OBJECT_Attribute attr_spec_days[]; // spec_days
extern const COSEM_OBJECT_Attribute meth_spec_days[]; // spec_days

PDU_DataAccessResult attr_script___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // script
extern const COSEM_OBJECT_Attribute attr_script[]; // script
extern const COSEM_OBJECT_Attribute meth_script[]; // script

PDU_DataAccessResult attr_reg_active___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // active
extern const COSEM_OBJECT_Attribute attr_reg_active[]; // active
extern const COSEM_OBJECT_Attribute meth_reg_active[]; // active

PDU_DataAccessResult attr_limit___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); //
extern const COSEM_OBJECT_Attribute attr_limit[]; //
extern const COSEM_OBJECT_Attribute meth_limit[]; //

PDU_DataAccessResult attr_img_transf___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Image Transfer
PDU_DataAccessResult meth_img_transf___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // Image Transfer
extern const COSEM_OBJECT_Attribute attr_img_transf[]; // Image Transfer
extern const COSEM_OBJECT_Attribute meth_img_transf[]; // Image Transfer

PDU_DataAccessResult attr_radio_bridge_data(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData); // radio
extern const COSEM_OBJECT_Attribute attr_radio_bridge[]; // radio


extern const COSEM_OBJECT cosem_objcts_1_0_94_7_0_255[]; // А2.1 мгновенные (текущие) параметры

extern const COSEM_OBJECT cosem_objcts_1_0_99_1_0_255[]; // А2.2 параметры профиля нагрузки

extern const COSEM_OBJECT cosem_objcts_1_0_98_2_0_255[]; // А2.3 параметры ежесуточного профиля

extern const COSEM_OBJECT cosem_objcts_1_0_94_7_5_255[]; // А2.3 параметры телеизмерений профиля

extern const COSEM_OBJECT cosem_objcts_0_0_99_98_0_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_1_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_2_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_3_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_4_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_5_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_6_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_7_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_8_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_9_255[];
extern const COSEM_OBJECT cosem_objcts_0_0_99_98_10_255[];

extern const COSEM_OBJECT cosem_objcts[];

//Соединение типа «Публичный клиент» должно содержать следующие объекты:
//	Логическое имя устройства;
//	Значение часов реального времени в счётчике;
//	Соединение типа «Считыватель показаний» должно содержать следующие объекты:
//	Профили объектов, позволяющие накапливать данные, определенные списком па-раметров из приложений A2, A3, A4, A5, A6.
//	Объекты, предоставляющие оперативный доступ к элементам в текущем списке па-раметров. Обязателен селективный доступ к объектам профилей.
//	Сервис «Action» должен использовать только 2 метода:
//	Метод 6 (сдвиг времени) класса 0008 объекта 0.0.1.0.0.255 (локальное время счетчика). Метод можно использовать не чаще, чем 1 раз в сутки;
//	Метод 2 (захват) класса 0007 объекта 1.0.94.07.0.255 (профиль текущих значений).
//	Соединение типа «Конфигуратор» должно содержать следующие объекты:
//	На чтение - все объекты.
//	На запись - объекты, указанные в приложении А4.
//Перечень объектов для каждого типа соединения подробно описан в приложениях A2, A3, A4, A5.
//	Права доступа к каждому объекту данных также описаны в приложениях A2, A3, A4, A5.

// Image transfer (class_id = 18, version = 0) обновление прошивки

#ifdef __cplusplus
}
#endif

#endif // _COSEM_OBJECTS_H_
