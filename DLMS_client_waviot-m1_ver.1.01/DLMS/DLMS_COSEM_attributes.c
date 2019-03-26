#include "DLMS_COSEM_objects.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "DLMS_HDLC.h"
#include "DLMS_PDU.h"
#include "DLMS_AES.h"
#include "DLMS_arch.h"
#include "DLMS_tariff.h"
#include "meter.h"
#include "meter_DLMS.h"

//#include "radio.h"
#include "defines_HW.h"

#ifndef UNUSED
#define UNUSED(expr) do { (void)(expr); } while (0)
#endif

uint32_t obis_rwm_val(OBIS *obis, uint8_t rw_attr, uint8_t * buf, uint32_t buf_len_in, uint32_t buf_len_max)
{
    uint32_t obis_attr = OBIS_ATTR_to_uint(obis, rw_attr & 0x3F);
    uint8_t rw = (rw_attr & 0x80) ? 1 : 0;
    uint8_t metod = (rw_attr & 0x40) ? 1 : 0;
    if (buf_len_max < 64) return 0;
    uint32_t res_len = 0;
//    uint32_t res_val = 0x7FFFFFFF;
    switch (obis_attr) {
    case 0x60010002: { // Серийный номер счетчика 0.0.96.1.0.255_2
        if (rw) break;
        if (metod) break;
        res_len = snprintf((char*)buf + 2, buf_len_max - 2, "%d", METER_id());
        buf[0] = DLMS_PDU_DATA_TYPE_OCTET_STRING;
        buf[1] = res_len;
        res_len += 2;
        break;
    }
    case 0x60010102: { // Тип счетчика 0.0.96.1.1.255_2
        if (rw) break;
        if (metod) break;
        res_len = snprintf((char*)buf + 2, buf_len_max - 2, "%d.%d", DEV_HW_id >> 4, DEV_HW_id & 0xF);
        buf[0] = DLMS_PDU_DATA_TYPE_OCTET_STRING;
        buf[1] = res_len;
        res_len += 2;
        break;
    }
    case 0x60010202: { // Версия метрологического ПО 0.0.96.1.2.255_2
        if (rw) break;
        if (metod) break;
#ifdef DD_ADE7868A
        const char mver[] = "53E8";
#else
        const char mver[] = "A455";
#endif
        res_len = snprintf((char*)buf + 2, buf_len_max - 2, "%s", mver);
        buf[0] = DLMS_PDU_DATA_TYPE_OCTET_STRING;
        buf[1] = res_len;
        res_len += 2;
        break;
    }
    case 0x60010302: { // Версия коммуникационного ПО 0.0.96.1.3.255_2
        if (rw) break;
        if (metod) break;
        res_len = snprintf((char*)buf + 2, buf_len_max - 2, "%d.%d.%d.%d", DEV_SW_rev >> 4, DEV_SW_rev & 0xF, dev_SW_sub >> 4, dev_SW_sub & 0xF);
        buf[0] = DLMS_PDU_DATA_TYPE_OCTET_STRING;
        buf[1] = res_len;
        res_len += 2;
        break;
    }
    case 0x60010A02: { // Данные точки учета (до 64 байт) 0.0.96.1.10.255_2
        if (rw) {
            if (buf[0] != DLMS_PDU_DATA_TYPE_OCTET_STRING) break;
            if (buf[1] > buf_len_in) break;
            memset(meter.settings.passport.point_name, 0, sizeof(meter.settings.passport.point_name));
            memmove(meter.settings.passport.point_name, &buf[2], sizeof(meter.settings.passport.point_name) > buf_len_in - 1 ? buf_len_in - 1 : sizeof(meter.settings.passport.point_name));
        }
        if (metod) break;
        buf[0] = DLMS_PDU_DATA_TYPE_OCTET_STRING;
        buf[1] = res_len - 2 < sizeof(meter.settings.passport.point_name) ? (res_len - 2) : sizeof(meter.settings.passport.point_name);
        memmove(buf + 2, meter.settings.passport.point_name, buf[1]);
        res_len = buf[1] + 2;
        break;
    }
    default: {
        uint32_t val = 0;
        uint8_t * packet = buf;
        if (buf_len_in) {
            uint8_t val_type = *packet++;
            switch (val_type) {
                case DLMS_PDU_DATA_TYPE_INT8:
                case DLMS_PDU_DATA_TYPE_UINT8: {
                    val += *packet++;
                    obis_attr |= 0x80;
                    break;
                }
                case DLMS_PDU_DATA_TYPE_INT16:
                case DLMS_PDU_DATA_TYPE_UINT16: {
                    val += *packet++; val <<= 8;
                    val += *packet++;
                    obis_attr |= 0x80;
                    break;
                }
                case DLMS_PDU_DATA_TYPE_INT32:
                case DLMS_PDU_DATA_TYPE_UINT32: {
                    val += *packet++; val <<= 8;
                    val += *packet++; val <<= 8;
                    val += *packet++; val <<= 8;
                    val += *packet++;
                    obis_attr |= 0x80;
                    break;
                }
                default: break;
            }
        } else {
            rw_attr &= 0x7F;
        }
        val = obis_attr_val_int(obis, rw_attr, val);
        uint8_t * drbuffer_head = buf;
        if (val <= 0xFF) {
            *drbuffer_head++ = DLMS_PDU_DATA_TYPE_UINT8;
            *drbuffer_head++ = (val >>  0) & 0xFF;
        } else if (val <= 0xFFFF) {
            *drbuffer_head++ = DLMS_PDU_DATA_TYPE_UINT16;
            *drbuffer_head++ = (val >>  8) & 0xFF;
            *drbuffer_head++ = (val >>  0) & 0xFF;
        } else if (val != 0x7FFFFFFF) {
            *drbuffer_head++ = DLMS_PDU_DATA_TYPE_UINT32;
            *drbuffer_head++ = (val >> 24) & 0xFF;
            *drbuffer_head++ = (val >> 16) & 0xFF;
            *drbuffer_head++ = (val >>  8) & 0xFF;
            *drbuffer_head++ = (val >>  0) & 0xFF;
        }
        res_len = drbuffer_head - buf;
        break;
    }
    }
    if (rw && res_len) {
        //todo send event;
    }
    return  res_len;
}

uint32_t obis_attr_val_int(OBIS *obis, uint8_t rw_attr, uint32_t val)
{
    uint32_t obis_attr = OBIS_ATTR_to_uint(obis, rw_attr & 0x3F);
    uint8_t rw = (rw_attr & 0x80) ? 1 : 0;
//    uint8_t metod = (rw_attr & 0x40) ? 1 : 0;
    uint32_t res_val = 0x7FFFFFFF;
    switch (obis_attr) {
    case 0x01000002: { // Текущее время 0.0.1.0.0.255
        res_val = METER_now();
        break;
    }
    case 0x01000003: { // Часовой пояс 0.0.1.0.0.255
        if (rw) meter.settings.clock.time_zone = val;
        res_val = meter.settings.clock.time_zone;
        break;
    }
    case 0x01000007: { // Сдвиг летнего времени 0.0.1.0.0.255
        if (rw) meter.settings.clock.shift_summer = val;
        res_val = meter.settings.clock.shift_summer;
        break;
    }
    case 0x01000008: { // Разрешение перевода на летнее время 0.0.1.0.0.255
        if (rw) meter.settings.clock.is_use_summer = val;
        res_val = meter.settings.clock.is_use_summer;
        break;
    }
    case 0x00040202: { // Коэффициент трансформации по току 1.0.0.4.2.255
        if (rw) meter.settings.passport.Internal_CT_ratio = val;
        res_val = meter.settings.passport.Internal_CT_ratio;
        break;
    }
    case 0x00040302: { // Коэффициент трансформации по напряжению 1.0.0.4.3.255
        if (rw) meter.settings.passport.Internal_PT_ratio = val;
        res_val = meter.settings.passport.Internal_PT_ratio;
        break;
    }
    case 0x00080402: { // Период записи в профиль 1
        if (rw) meter.settings.arch_hour.timeout = val;
        res_val = meter.settings.arch_hour.timeout;
        break;
    }
    case 0x00080502: { // Период записи в профиль 2
        if (rw) meter.settings.arch_set.timeout = val;
        res_val = meter.settings.arch_set.timeout;
        break;
    }
    case 0x00080902: { // Период отправки профиля мгновенных
        if (rw) meter.settings.profile_curr.timeout_send = val;
        res_val = meter.settings.profile_curr.timeout_send;
        break;
    }
    case 0x000A0202: { // Активное сопротивление линии 1.0.0.10.2.255
        if (rw) meter.settings.passport.r_line = val;
        res_val = meter.settings.passport.r_line;
        break;
    }
    case 0x0C270002: { // Пороговое напряжение для фиксации перерыва питания 1.0.12.39.0.255
        if (rw) meter.settings.limit.u_off = val;
        res_val = meter.settings.limit.u_off;
        break;
    }
    case 0x01040002: { // Период интегрирования максимальной мощности 1.0.1.4.0.255 2 Текущее среднее значение
        res_val = (uint32_t)(meter.vars.P_max.itg.p_acc / meter.vars.P_max.itg.p_counter);
        break;
    }
    case 0x01040003: { // Период интегрирования максимальной мощности 1.0.1.4.0.255 3 Последнее среднее значение
        res_val = (uint32_t)meter.vars.P_max.itg.P;
        break;
    }
    case 0x01040007: { // Период интегрирования максимальной мощности 1.0.1.4.0.255 7 Время старта
        uint32_t val = meter.curr.timestamp;
        val /= meter.settings.energy_max.period_min * 60;
        val *= meter.settings.energy_max.period_min * 60;
        res_val = val;
        break;
    }
    case 0x01040008: { // Период интегрирования максимальной мощности 1.0.1.4.0.255 8 Длительность периода усреднения
        if (rw) meter.settings.energy_max.period_min = val;
        res_val = meter.settings.energy_max.period_min;
        break;
    }
    case 0x0C230002: { // Порог для фиксации перенапряжения 1.0.12.35.0.255
        if (rw) meter.settings.limit.u_up = val;
        res_val = meter.settings.limit.u_up;
        break;
    }
    case 0x0C1F0002: { // Порог для фиксации провала напряжения 1.0.12.31.0.255
        if (rw) meter.settings.limit.u_down = val;
        res_val = meter.settings.limit.u_down;
        break;
    }
    case 0x0C2B0002: { // Время перехода напряжения через нижний порог 1.0.12.43.0.255
        if (rw) meter.settings.limit.u_down_time = val;
        res_val = meter.settings.limit.u_down_time;
        break;
    }
    case 0x0C2C0002: { // Время перехода напряжения через верхний порог 1.0.12.44.0.255
        if (rw) meter.settings.limit.u_up_time = val;
        res_val = meter.settings.limit.u_up_time;
        break;
    }
    case 0x0C2D0002: { // Время пропадания напряжения 1.0.12.45.0.255
        if (rw) meter.settings.limit.u_off_time = val;
        res_val = meter.settings.limit.u_off_time;
        break;
    }
    case 0x83230002: { // Порог для фиксации превышения тангенса нагрузки 1.0.131.35.0.255
        if (rw) meter.settings.limit.tg = val;
        res_val = meter.settings.limit.tg;
        break;
    }
    case 0x85230002: { // Порог для фиксации коэффициента несимметрии напряжений 1.0.133.35.0.255
        if (rw) meter.settings.limit.u_ansymmetry = val;
        res_val = meter.settings.limit.u_ansymmetry;
        break;
    }
    case 0x00060402: { // Согласованное напряжение электропитания 1.0.0.6.4.255 Опорное напряжение для измерения качества электроэнергии
        if (rw) meter.settings.passport.u_op = val;
        res_val = meter.settings.passport.u_op;
        break;
    }
    case 0x11000003: { // {{0,0,17,0,0,255} // мощность для отключения // Активный порог
        if (rw) meter.settings.limit_off.P_val = val;
        res_val = meter.settings.limit_off.P_val;
        break;
    }
    case 0x11000006: { // {{0,0,17,0,0,255} // мощность для отключения // Мин. длительность превышения порога
        if (rw) meter.settings.limit_off.P_time_to_off = val;
        if (meter.settings.limit_off.P_time_to_off < METER_settings_limit_off_P_time_to_off_min) {
            meter.settings.limit_off.P_time_to_off = METER_settings_limit_off_P_time_to_off_min;
        }
        res_val = meter.settings.limit_off.P_time_to_off;
        break;
    }
    case 0x11000007: { // {{0,0,17,0,0,255} // мощность для отключения //  Мин. длительность снижения ниже порога
        if (rw) meter.settings.limit_off.P_time_to_on = val;
        if (meter.settings.limit_off.P_time_to_on < METER_settings_limit_off_P_time_to_on_min) {
            meter.settings.limit_off.P_time_to_on = METER_settings_limit_off_P_time_to_on_min;
        }
        res_val = meter.settings.limit_off.P_time_to_on;
        break;
    }
    
    case 0x11000103: { // {{0,0,17,0,1,255} // ток для отключения // Активный порог
        if (rw) meter.settings.limit_off.I_val = val;
        res_val = meter.settings.limit_off.I_val;
        break;
    }
    case 0x11000106: { // {{0,0,17,0,1,255} // ток для отключения // Мин. длительность превышения порога
        if (rw) meter.settings.limit_off.I_time_to_off = val;
        res_val = meter.settings.limit_off.I_time_to_off;
        break;
    }
    case 0x11000107: { // {{0,0,17,0,1,255} // ток для отключения //  Мин. длительность снижения ниже порога
        if (rw) meter.settings.limit_off.I_time_to_on = val;
        res_val = meter.settings.limit_off.I_time_to_on;
        break;
    }
    
    case 0x11000203: { // {{0,0,17,0,2,255} // напряжения для отключения // Активный порог
        if (rw) meter.settings.limit_off.U_val = val;
        res_val = meter.settings.limit_off.U_val;
        break;
    }
    case 0x11000206: { // {{0,0,17,0,2,255} // напряжения для отключения // Мин. длительность превышения порога
        if (rw) meter.settings.limit_off.U_time_to_off = val;
        res_val = meter.settings.limit_off.U_time_to_off;
        break;
    }
    case 0x11000207: { // {{0,0,17,0,2,255} // напряжения для отключения //  Мин. длительность снижения ниже порога
        if (rw) meter.settings.limit_off.U_time_to_on = val;
        res_val = meter.settings.limit_off.U_time_to_on;
        break;
    }
    
    case 0x11000303: { // {{0,0,17,0,3,255} // воздействия магнитного поля для отключения // Активный порог
        if (rw) meter.settings.limit_off.M_val = val;
        res_val = meter.settings.limit_off.M_val;
        break;
    }
    case 0x11000306: { // {{0,0,17,0,3,255} // воздействия магнитного поля для отключения // Мин. длительность превышения порога
        if (rw) meter.settings.limit_off.M_time_to_off = val;
        res_val = meter.settings.limit_off.M_time_to_off;
        break;
    }
    case 0x11000307: { // {{0,0,17,0,3,255} // воздействия магнитного поля для отключения //  Мин. длительность снижения ниже порога
        if (rw) meter.settings.limit_off.M_time_to_on = val;
        res_val = meter.settings.limit_off.M_time_to_on;
        break;
    }
    
    case 0x11000403: { // {{0,0,17,0,4,255} // разбаланс токов для отключения // Активный порог
        if (rw) meter.settings.limit_off.dI_val = val;
        res_val = meter.settings.limit_off.dI_val;
        break;
    }
    case 0x11000406: { // {{0,0,17,0,4,255} // разбаланс токов для отключения // Мин. длительность превышения порога
        if (rw) meter.settings.limit_off.dI_time_to_off = val;
        res_val = meter.settings.limit_off.dI_time_to_off;
        break;
    }
    case 0x11000407: { // {{0,0,17,0,4,255} // разбаланс токов для отключения //  Мин. длительность снижения ниже порога
        if (rw) meter.settings.limit_off.dI_time_to_on = val;
        res_val = meter.settings.limit_off.dI_time_to_on;
        break;
    }
    
    case 0x11000503: { // {{0,0,17,0,5,255} // превышение температуры для отключения // Активный порог
        if (rw) meter.settings.limit_off.T_val = val;
        res_val = meter.settings.limit_off.T_val;
        break;
    }
    case 0x11000506: { // {{0,0,17,0,5,255} // превышение температуры для отключения // Мин. длительность превышения порога
        if (rw) meter.settings.limit_off.T_time_to_off = val;
        res_val = meter.settings.limit_off.T_time_to_off;
        break;
    }
    case 0x11000507: { // {{0,0,17,0,5,255} // превышение температуры для отключения //  Мин. длительность снижения ниже порога
        if (rw) meter.settings.limit_off.T_time_to_on = val;
        res_val = meter.settings.limit_off.T_time_to_on;
        break;
    }
    case 0x60030A03: { // {{0,0,96,3,10,255} // Режим управления реле отключения абонента // state
        if (rw) {
            switch (val) {
            case 0: METER_disconnect_control_setState(DLMS_EVENT_rele_radio_off); break; // off
            case 1: METER_disconnect_control_setState(DLMS_EVENT_rele_radio_on ); break; // on
            case 2: METER_disconnect_control_setState(DLMS_EVENT_rele_access_on); break; // ready
            default: break;
            }
        }
        res_val = meter.settings.disconnect_control.state;
        break;
    }
    case 0x60030A04: { // {{0,0,96,3,10,255} // Режим управления реле отключения абонента // mode
        if (rw) meter.settings.disconnect_control.mode = val;
        res_val = meter.settings.disconnect_control.mode;
        break;
    }
    case 0x60030A02: { // {{0,0,96,3,10,255} // Режим управления реле отключения абонента // output_state
        res_val = meter.vars.disconnect_control.output_state;
        break;
    }
    case 0x60010402: { // Год выпуска счетчика 0.0.96.1.4.255_2
        res_val = 2019;
        break;
    }
    case 0x60040102: { // Режим подсветки ЖКИ 0.0.96.4.1.255_2
        res_val = 0;
        break;
    }
    case 0x60040202: { // Режим телеметрии 0.0.96.4.2.255_2
        res_val = 0;
        break;
    }
    case 0x60050302: { // 0,0,96,5,3,255
        res_val = 0;
        break;
    }
    case 0x60080002: { // 0,0,96,8,0,255 // Время работы счетчика
        if (rw) METER_set_work(val);
        res_val = METER_work();
        break;
    }
    default: break;
    }
    if (rw && (res_val != 0x7FFFFFFF)) {
        DLMS_ARCH_write_settings();
        //todo send event;
    }
    return  res_val;
}

PDU_DataAccessResult attr_0_0_40_0_0_255___1(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // клиент от авторизации
{
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
    switch (pduHeader->attributeIndex) {
    case 1: { // Логическое имя объекта
        OBIS obis_t = cobj->obis;
        if (hdlc->pdu_ch.authentication_ok != 1) {
            obis_t.E = 1;
        }
        DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)&obis_t, sizeof(obis_t));
        break;
    }
    case 3: { // Идентификатор партнера
        DLMS_PDU_BUF_AddStruct(pb, 2);
        DLMS_PDU_BUF_AddInt8(pb, hdlc->clnt.bytes4.addr); // client_SAP: integer,
        DLMS_PDU_BUF_AddUInt16(pb, hdlc->serv.bytes4.addr); // server_SAP: long-unsigned
        break;
    }
    case 4: { // Имя контекста приложения
        const uint8_t application_context_name[] = {0x60, 0x85, 0x74, 0x05, 0x08, 0x01, 0x01};
        DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)application_context_name, sizeof(application_context_name));
        break;
    }
    case 5: { // xDLMS_context_info
        DLMS_PDU_BUF_AddStruct(pb, 6);
        DLMS_PDU_BUF_AddBitString(pb, 24); // conformance: bitstring(24),
        DLMS_PDU_BUF_SetUInt8(pb, (hdlc->pdu_ch.conformance >> 16) & 0xFF);
        DLMS_PDU_BUF_SetUInt8(pb, (hdlc->pdu_ch.conformance >>  8) & 0xFF);
        DLMS_PDU_BUF_SetUInt8(pb, (hdlc->pdu_ch.conformance >>  0) & 0xFF);
        DLMS_PDU_BUF_AddUInt16(pb, 4096); // max_receive_pdu_size: long-unsigned,
        DLMS_PDU_BUF_AddUInt16(pb, 4096); // max_send_pdu_size: long-unsigned,
        DLMS_PDU_BUF_AddUInt8(pb, 6); // dlms_version_number: unsigned,
        DLMS_PDU_BUF_AddInt8(pb, 0); // quality_of_service: integer,
        DLMS_PDU_BUF_AddOctetString(pb, 0, 0); // quality_of_service: integer, // todo
        break;
    }
    case 6: { // Имя алгоритма проверки подлинности
        const uint8_t authentication_mechanism_name[] = {0x60, 0x85, 0x74, 0x05, 0x08, 0x02, 0x00};
        DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)authentication_mechanism_name, sizeof(authentication_mechanism_name));
        uint8_t *a = pb->data - 1;
        *a = hdlc->pdu_ch.authentication;
        break;
    }
    case 7: { // Секрет (пароль)
        DLMS_PDU_BUF_AddNone(pb);
        break;
    }
    case 8: { // Статус соединения
        switch (hdlc->pdu_ch.authentication_ok) {
        case 0: {
            DLMS_PDU_BUF_AddEnum(pb, 0); //non-associated,
            break;
        }
        case 1: {
            DLMS_PDU_BUF_AddEnum(pb, 2); //associated
            break;
        }
        default: {
            DLMS_PDU_BUF_AddEnum(pb, 1); //association-pending,
        }
        }
        break;
    }
    case 9: { // Ссылка на объект «Настройки безопасности»
        DLMS_PDU_BUF_AddNone(pb);
        break;
    }
    default:
        //log_1 << pduHeader->attributeIndex;
        break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);

    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult meth_0_0_40_0_0_255___1(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // клиент от авторизации
{
    UNUSED(cobj);

    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    if (pduHeader->selection == 1 && hdlc->pdu_ch.authentication_ok == 2) {
        switch (hdlc->pdu_ch.authentication) {
        case PDU_DLMS_AUTHENTICATION_HIGH: {
            uint8_t data[16];
            DLMS_Aes1Encrypt(hdlc->pdu_ch.StoC_challenge, meter.settings.passwords.high, data);
            //log_1 << "get tst" << QByteArray((const char *)data, 16).toHex().toUpper();
            //log_1 << *pduData->data << QByteArray((const char *)pduData->data+2, 16).toHex().toUpper();
            if (*pduData->data == 9 && memcmp(data, pduData->data+2, sizeof(data))) {
                //log_1 << "authentication tst" << false;
                hdlc->pdu_ch.authentication_ok = 0;
                DLMS_PDU_BUF_init(hdlc, pb);
                DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_METHOD_RESPONSE);
                DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
                DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
                DLMS_PDU_BUF_SetUInt8(pb, 0);
                DLMS_PDU_BUF_SetUInt8(pb, 1);
                DLMS_PDU_BUF_SetUInt8(pb, 0);
//                        DLMS_PDU_BUF_SetUInt8(pb, 0);
                DLMS_PDU_BUF_AddBool(pb, 0);
                DLMS_PDU_BUF_to_HDLC(hdlc, pb);
                return PDU_DataAccessResult_Success;
            }
//                60 36 A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 01 AC 0A 80 08 P8 P7 P6 P5 P4 P3 P2 P1 BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 00 7E 1F 04 B0
//                60 36 A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 05 AC 0A 80 10 K16 K15 K14 K13 K12 K11 K10 K9 K8 K7 K6 K5 K4 K3 K2 K1 BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 00 7E 04 B0
            //60 3E A1 09 06 07 60 85 74 05 08 01 01 8A 02 07 80 8B 07 60 85 74 05 08 02 02 AC 12 80 10 20 6B 0F 74 51 03 6B 5B 07 5F 2C 48 38 1E 29 0B BE 10 04 0E 01 00 00 00 06 5F 1F 04 00 95 87 7E 40 1E 1C FF FF
            //61 4B A1 09 06 07 60 85 74 05 08 01 01 A2 03 02 01 00 A3 05 A1 03 02 01 0E 88 02 07 80 89 07 60 85 74 05 08 02 02 AA 12 80 10 D4 9F D4 A4 59 7E 35 CF 32 22 F4 CC CF D3 90 2D BE 11 04 0F 08 01 00 06 5F 1F 04 00 40 1E 1C 04 00 00 07
            //C3 01 C1 00 0F 00 00 28 00 00 FF 01 01 09 10 C0 37 F5 BC 3C 07 C7 2B 8A 98 0F 34 9C C1 C1 42
            //C7 01 C1 00 01 00 09 10 40 38 E8 19 FA D5 EC 57 C3 DC E2 AC ED 66 62 0B
            //C7 01 C1 00 01 00 00 - false
            DLMS_Aes1Encrypt(hdlc->pdu_ch.CtoS_challenge, meter.settings.passwords.high, data);
            //log_1 << "out" << QByteArray((const char *)data, pdu_ch->CtoS_challenge_len).toHex().toUpper();
            DLMS_PDU_BUF_init(hdlc, pb);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_METHOD_RESPONSE);
            DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
            DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
            DLMS_PDU_BUF_SetUInt8(pb, 0);
            DLMS_PDU_BUF_SetUInt8(pb, 1);
            DLMS_PDU_BUF_SetUInt8(pb, 0);
            DLMS_PDU_BUF_AddOctetString(pb, data, sizeof(data));
            DLMS_PDU_BUF_to_HDLC(hdlc, pb);
            hdlc->pdu_ch.authentication_ok = 1;
//                    pdu_ch->security = DLMS_SECURITY_AUTHENTICATION_ENCRYPTION;
            return PDU_DataAccessResult_Success;
        }
        default: {
            //log_1 << "authentication" << pdu_ch->authentication;
        }
        }
    }

    return PDU_DataAccessResult_HardwareFault;
}
PDU_DataAccessResult attr_obj_list___2(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // список объектов от авторизации
{
    PDU_channel *pdu_ch = &hdlc->pdu_ch;
    UNUSED(cobj);
    UNUSED(pduData);

    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_init(hdlc, pb);
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
    DLMS_PDU_BUF_init_RESPONSE(pb, pduHeader);

    DLMS_PDU_BUF_AddArray(pb, 0x82);  // next 2 byte
    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
    uint8_t *p_array_count = pb->data - 1;
    for (int obj_iter = 0; obj_iter < 255; ++obj_iter) {
        if (!COSEM_obj_to_list_count(&cosem_objcts[obj_iter], pdu_ch, p_array_count)) break;
    }
    for (int obj_iter = 1; obj_iter < 255; ++obj_iter) {
        if (!COSEM_obj_to_list_count(&cosem_objcts_1_0_94_7_0_255[obj_iter], pdu_ch, p_array_count)) break;
    }
    for (int obj_iter = 1; obj_iter < 255; ++obj_iter) {
        if (!COSEM_obj_to_list_count(&cosem_objcts_1_0_98_2_0_255[obj_iter], pdu_ch, p_array_count)) break;
    }
    for (int obj_iter = 1; obj_iter < 255; ++obj_iter) {
        if (!COSEM_obj_to_list_count(&cosem_objcts_1_0_99_1_0_255[obj_iter], pdu_ch, p_array_count)) break;
    }
//    log_1 << pdu_ch->authentication << pb->block_index << pb->block_index_max << pb->data - pb->data_start << pb->len;
    for (int obj_iter = 0; obj_iter < 255; ++obj_iter) {
        PDU_BUF_temp_BEGIN(pb_temp, pb)
        if (!COSEM_obj_to_list(&cosem_objcts[obj_iter], pdu_ch, &pb_temp, 0)) break;
        PDU_BUF_temp_END(pb_temp, pb)
    }
    for (int obj_iter = 1; obj_iter < 255; ++obj_iter) {
        PDU_BUF_temp_BEGIN(pb_temp, pb)
        if (!COSEM_obj_to_list(&cosem_objcts_1_0_94_7_0_255[obj_iter], pdu_ch, &pb_temp, 0)) break;
        PDU_BUF_temp_END(pb_temp, pb)
    }
    for (int obj_iter = 1; obj_iter < 255; ++obj_iter) {
        PDU_BUF_temp_BEGIN(pb_temp, pb)
        if (!COSEM_obj_to_list(&cosem_objcts_1_0_98_2_0_255[obj_iter], pdu_ch, &pb_temp, 0)) break;
        PDU_BUF_temp_END(pb_temp, pb)
    }
    for (int obj_iter = 1; obj_iter < 255; ++obj_iter) {
        PDU_BUF_temp_BEGIN(pb_temp, pb)
        if (!COSEM_obj_to_list(&cosem_objcts_1_0_99_1_0_255[obj_iter], pdu_ch, &pb_temp, 0)) break;
        PDU_BUF_temp_END(pb_temp, pb)
    }
    return DLMS_PDU_BUF_to_HDLC(hdlc, pb);
}
PDU_DataAccessResult attr_logical_name___1(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Логическое имя объекта
{
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
    DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)&cobj->obis, sizeof(OBIS));
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_dev_name___2(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Имя устройства
{
    UNUSED(cobj);
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
//    const uint8_t name[] = "VMQ123456789"; // need 3+13 byte
    //todo copy modem_id;
    uint8_t buf[3+14];
//    snprintf((char*)buf, sizeof(buf), "%s%013d", meter.settings.passport.Device_3, meter.settings.passport.Meter_Serial_Number);
    DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)buf, sizeof(buf)-1);
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_reg_value___2_data(DLMS_PDU_BUF * pb, const COSEM_OBJECT *cobj)
{
    switch (cobj->obis.D) {
    case 0: {
        switch (cobj->obis.C) {
        case 1: { DLMS_PDU_BUF_AddDateTime(pb, METER_now(), meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING); break; } // 0.0.1.0.0.255 время записи
        }
        break;
    }
    case 4: {
        DLMS_PDU_BUF_AddUInt32(pb, 0); // todo
        break;
    }
    case 6: {
        DLMS_PDU_BUF_AddUInt32(pb, METER_A1CxDx_u32data(cobj->obis.C, cobj->obis.D, cobj->obis.E));
        break;
    }
    case 7: {
        DLMS_PDU_BUF_AddInt32(pb, METER_A1CxDx_u32data(cobj->obis.C, cobj->obis.D, cobj->obis.E));
        break;
    }
    case 8: {
        DLMS_PDU_BUF_AddUInt32(pb, METER_A1CxDx_u32data(cobj->obis.C, cobj->obis.D, cobj->obis.E)); //return PDU_DataAccessResult_ReadWriteDenied;
        break;
    }
    case 9: {
        DLMS_PDU_BUF_AddUInt32(pb, 0);
        break;
    }
    case 29: {
        DLMS_PDU_BUF_AddUInt32(pb, 0);
        break;
    }
    default: return PDU_DataAccessResult_ReadWriteDenied;
    }
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_reg_value___2(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
    if (attr_reg_value___2_data(pb, cobj) != PDU_DataAccessResult_Success) {
        return PDU_DataAccessResult_ReadWriteDenied;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
void attr_reg_value___3_data_scale_unit(DLMS_PDU_BUF * pb, int8_t scale, uint8_t unit)
{
    DLMS_PDU_BUF_AddStruct(pb, 2);
    DLMS_PDU_BUF_AddInt8(pb, scale);
    DLMS_PDU_BUF_AddEnum(pb, unit);
}
PDU_DataAccessResult attr_reg_value___3_data(DLMS_PDU_BUF * pb, const COSEM_OBJECT *cobj)
{
    switch (cobj->obis.D) {
    case 0: {
        switch (cobj->obis.C) {
        case 1: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_SECOND); break; } // 0.0.1.0.0.255 время записи
        }
        break;
    }
    case 4: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_ACTIVE_POWER); break; }
    case 6: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_ACTIVE_POWER); break; }// пик
    case 7: { // Мгновенное значение
        switch (cobj->obis.C) {
        case 11: // 1.0.31.7.0.255 Ls Ток | Мгновенное значение
        case 31: // 1.0.31.7.0.255 L1 Ток | Мгновенное значение
        case 51: // 1.0.51.7.0.255 L2 Ток | Мгновенное значение
        case 71: // 1.0.71.7.0.255 L3 Ток | Мгновенное значение
        case 91: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_CURRENT);       break; } // 1.0.91.7.0.255 L0 Ток нейтрал | Мгновенное значение
        case 32: // 1.0.32.7.0.255 L1 Напряжение | Мгновенное значение
        case 52: // 1.0.52.7.0.255 L2 Напряжение | Мгновенное значение
        case 72: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_VOLTAGE);       break; } // 1.0.72.7.0.255 L3 Напряжение | Мгновенное значение
        case 33: // 1.0.33.7.0.255 L1 коэффициент мощности | Мгновенное значение
        case 53: // 1.0.53.7.0.255 L2 коэффициент мощности | Мгновенное значение
        case 73: // 1.0.73.7.0.255 L3 коэффициент мощности | Мгновенное значение
        case 13: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_NO_UNIT);       break; } // 1.0.73.7.0.255 L0 коэффициент мощности | Мгновенное значение
        case 14: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_FREQUENCY);     break; } // 1.0.14.7.0.255 Частота сети | Мгновенное значение
        case  9: // 1.0.9.7.0.255  Ls Полная мощность | Мгновенное значение
        case 29: // 1.0.29.7.0.255 L1 Полная мощность | Мгновенное значение
        case 49: // 1.0.49.7.0.255 L2 Полная мощность | Мгновенное значение
        case 69: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_APPARENT_POWER);break; } // 1.0.69.7.0.255 L3 Полная мощность | Мгновенное значение
        case  1: // 1.0.1.7.0.255  Ls Активная мощность | Мгновенное значение
        case 21: // 1.0.21.7.0.255 L1 Активная мощность | Мгновенное значение
        case 41: // 1.0.41.7.0.255 L2 Активная мощность | Мгновенное значение
        case 61: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_ACTIVE_POWER);  break; } // 1.0.61.7.0.255 L3 Активная мощность | Мгновенное значение
        case  3: // 1.0.3.7.0.255  Ls Реактивная мощность | Мгновенное значение
        case 23: // 1.0.23.7.0.255 L1 Реактивная мощность | Мгновенное значение
        case 43: // 1.0.43.7.0.255 L2 Реактивная мощность | Мгновенное значение
        case 63: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_REACTIVE_POWER);break; } // 1.0.63.7.0.255 L3 Реактивная мощность | Мгновенное значение
        case 81: { // degree
            switch (cobj->obis.E) {
            case 10: // 1.0.81.7.10.255 Угол A-B | Мгновенное значение
            case 21: // 1.0.81.7.21.255 Угол B-C | Мгновенное значение
            case  2: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_PHASE_ANGLEGEGREE);break; } // 1.0.81.7.2.255  Угол C-A | Мгновенное значение
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 12: { // U line
            switch (cobj->obis.E) {
            case 0: // 1.0.12.7.0.255 Ls Напряжение | Мгновенное значение
            case 1: // Межфазное напряжение АВ | Мгновенное значение
            case 2: // Межфазное напряжение ВС | Мгновенное значение
            case 3: { attr_reg_value___3_data_scale_unit(pb, -3, DLMS_UNIT_VOLTAGE); break; } // Межфазное напряжение АС | Мгновенное значение
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case 8: { // Накопленные  Time integral of the quantity calculated from the origin (first start of measurement) to the instantaneous time point
        switch (cobj->obis.C) {
        case  1: // 1.0.1.8.0.255  Сум Li Активная мощность + (QI+QIV)   | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case  2: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_ACTIVE_ENERGY);  break; } // 1.0.2.8.0.255  Сум Li Активная мощность - (QII+QIII) | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case  3: // 1.0.3.8.0.255  Сум Li Реактивная мощность + (QI+QII) | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case  4: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_REACTIVE_ENERGY);break; } // 1.0.4.8.0.255  Сум Li Реактивная мощность -(QIII+QIV)| Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case 88: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_A260);           break; } // 1.0.88.8.0.255 Сум Li A2ч QI+QII+QIII+QIV            | Интеграл по времени 1 | Тариф 0 (0 - суммарно)
        case 89: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_V260);           break; } // 1.0.89.8.0.255 Сум Li V2ч QI+QII+QIII+QIV            | Интеграл по времени 1 | Тариф 0 (0 - суммарно) |
        default: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_ACTIVE_POWER);   break; }
        }
        break;
    }
    case 9: {
        if (cobj->obis.C == 96 && cobj->obis.E == 0) {
            attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_TEMPERATURE);
        } else {
            attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_ACTIVE_ENERGY);
        }
        break;
    }
    case 29: { // дельты
        switch (cobj->obis.C) {
        case  1:
        case  2: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_ACTIVE_ENERGY); break; }
        case  3:
        case  4: { attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_REACTIVE_ENERGY); break; }
        default:   attr_reg_value___3_data_scale_unit(pb, 0, DLMS_UNIT_ACTIVE_POWER); break;
        }
        break;
    }
    default: return PDU_DataAccessResult_ReadWriteDenied;
    }
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_reg_value___3(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Масштаб и ед. измерения
{
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
    if (attr_reg_value___3_data(pb, cobj) != PDU_DataAccessResult_Success) {
        return PDU_DataAccessResult_ReadWriteDenied;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_reg_ext_value___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData)
{
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
    switch (pduHeader->attributeIndex) {
    case 2: { // Текущее значение
        DLMS_PDU_BUF_AddUInt32(pb, (uint32_t)METER_A1C1D6_data(DLMS_ARCH_profile_month));
        if (attr_reg_value___2_data(pb, cobj) != PDU_DataAccessResult_Success) {
            return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case 3: { // Масштаб и ед. измерения
        if (attr_reg_value___3_data(pb, cobj) != PDU_DataAccessResult_Success) {
            return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case 4: { // status CHOICE
        DLMS_PDU_BUF_AddNone(pb);
        break;
    }
    case 5: { // capture_time octet-string
        DLMS_PDU_BUF_AddDateTime(pb, 0, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_DATETIME);
        break;
    }
    default: return PDU_DataAccessResult_ReadWriteDenied;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_reg_demand___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    UNUSED(pduData);
    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { // Текущее среднее значение
            DLMS_PDU_BUF_AddUInt32(pb, (uint32_t)(meter.vars.P_max.itg.p_acc / meter.vars.P_max.itg.p_counter));
            break;
        }
        case 3: { // Последнее среднее значение
            DLMS_PDU_BUF_AddUInt32(pb, (uint32_t)(meter.vars.P_max.itg.P));
            break;
        }
        case 4: { // Масштаб и ед. измерения
            DLMS_PDU_BUF_AddStruct(pb, 2);
            DLMS_PDU_BUF_AddInt8(pb, 0);
            DLMS_PDU_BUF_AddEnum(pb, 27);
            break;
        }
        case 5: { // Статус
            DLMS_PDU_BUF_AddNone(pb);
            break;
        }
        case 6: { // Время фиксации
            DLMS_PDU_BUF_AddDateTime(pb, meter.curr.timestamp, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_DATETIME);
            break;
        }
        case 7: { // Время старта
            uint32_t val = meter.curr.timestamp;
            val /= meter.settings.energy_max.period_min * 60;
            val *= meter.settings.energy_max.period_min * 60;
            DLMS_PDU_BUF_AddDateTime(pb, val, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_DATETIME);
            break;
        }
        case 8: { // Длительность периода усреднения
            DLMS_PDU_BUF_AddUInt32(pb, meter.settings.energy_max.period_min);
            break;
        }
        case 9: { // Количество периодов
            DLMS_PDU_BUF_AddUInt16(pb, 60);
            break;
        }
        default: break;
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
        break;
    }
    default: return PDU_DataAccessResult_ReadWriteDenied;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_clock___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Часы
{
    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_init(hdlc, pb);
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { // Время
            DLMS_PDU_BUF_AddDateTime(pb, METER_now(), meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_DATETIME);
            break;
        }
        case 3: { // Часовой пояс
            DLMS_PDU_BUF_AddInt16(pb, meter.settings.clock.time_zone);
            break;
        }
        case 4: { // Статус
            DLMS_PDU_BUF_AddUInt8(pb, 0);
            break;
        }
        case 5: { // Дата перехода на летнее время
            DLMS_PDU_BUF_AddOctetString(pb, meter.settings.clock.time_summer_from, sizeof(meter.settings.clock.time_summer_from));
//            const uint8_t time_summer_from[] = {0xFF,0xFF,0x03,0xFE,0x07,0x02,0x00,0x00,0x00,0x80,0x00,0xFF};
//            DLMS_PDU_BUF_AddOctetString(pb, time_summer_from, sizeof(time_summer_from));
            break;
        }
        case 6: { // Дата перехода на зимнее время
            DLMS_PDU_BUF_AddOctetString(pb, meter.settings.clock.time_summer_to, sizeof(meter.settings.clock.time_summer_to));
//            const uint8_t time_summer_to[] = {0xFF,0xFF,0x0A,0xFE,0x07,0x03,0x00,0x00,0x00,0x80,0x00,0xFF};
//            DLMS_PDU_BUF_AddOctetString(pb, time_summer_to, sizeof(time_summer_to));
            break;
        }
        case 7: { // Сдвиг летнего времени
            DLMS_PDU_BUF_AddInt8(pb, meter.settings.clock.shift_summer);
//            DLMS_PDU_BUF_AddInt8(pb, 0);
            break;
        }
        case 8: { // Разрешение перевода на летнее время
            DLMS_PDU_BUF_AddBool(pb, meter.settings.clock.is_use_summer);
//            DLMS_PDU_BUF_AddBool(pb, 0);
            break;
        }
        case 9: { // Источник времени
            DLMS_PDU_BUF_AddEnum(pb, 1);
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { // Время
            break;
        }
        case 3: { // Часовой пояс
            meter.settings.clock.time_zone = DLMS_PDU_BUF_GetInt(pduData);
            break;
        }
        case 5: { // Дата перехода на летнее время
            break;
        }
        case 6: { // Дата перехода на зимнее время
            break;
        }
        case 7: { // Сдвиг летнего времени
            break;
        }
        case 8: { // Разрешение перевода на летнее время
            break;
        }
        case 9: { // Источник времени
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult meth_clock___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // клиент от авторизации
{
    PDU_channel *pdu_ch = &hdlc->pdu_ch;
    UNUSED(cobj);
    UNUSED(pdu_ch);
    UNUSED(pduHeader);
    UNUSED(pduData);
    return PDU_DataAccessResult_HardwareFault;
}
PDU_DataAccessResult attr_passport_data(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    UNUSED(pduData);
    uint32_t obis = COSEM_OBIS_to_uint(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
//    //log_1 << QByteArray::number(obis, 16).toUpper() << QByteArray::number(pduHeader->cmd, 16).toUpper();
    DLMS_PDU_BUF_init(hdlc, pb);
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (obis) {
        case 0x600100: { //Серийный номер счетчика 0.0.96.1.0.255
            uint8_t buf[8];
            memset(buf, 0, sizeof(buf));
            int res = snprintf((char*)buf, sizeof(buf), "%d", METER_id());
//            snprintf((char*)buf, sizeof(buf), "%d", meter.settings.passport.Meter_Serial_Number);
            DLMS_PDU_BUF_AddOctetString(pb, buf, res);
            break;
        }
        case 0x600101: { //Тип счетчика 0.0.96.1.1.255
            uint8_t buf[10];
            memset(buf, 0, sizeof(buf));
            int res = snprintf((char*)buf, sizeof(buf), "%d.%d", DEV_HW_id >> 4, DEV_HW_id & 0xF);
            DLMS_PDU_BUF_AddOctetString(pb, buf, sizeof(buf));
//            DLMS_PDU_BUF_AddOctetString(pb, meter.settings.passport.Device_Type, sizeof(meter.settings.passport.Device_Type));
            break;
        }
        case 0x600102: { //Версия метрологического ПО 0.0.96.1.2.255
            uint8_t buf[4];
            memset(buf, 0, sizeof(buf));
#ifdef DD_ADE7868A
            buf[0] = '5';
            buf[1] = '3';
            buf[2] = 'E';
            buf[3] = '8';
#else
            buf[0] = 'A';
            buf[1] = '4';
            buf[2] = '5';
            buf[3] = '5';
#endif
//            snprintf((char*)buf, sizeof(buf), "%d", meter.settings.passport.Firmware_Version_for_meter);
            DLMS_PDU_BUF_AddOctetString(pb, buf, sizeof(buf));
            break;
        }
        case 0x600103: { //Версия коммуникационного ПО 0.0.96.1.2.255
            uint8_t buf[20];
            memset(buf, 0, sizeof(buf));
            int res = snprintf((char*)buf, sizeof(buf), "%d.%d.%d.%d", DEV_SW_rev >> 4, DEV_SW_rev & 0xF, dev_SW_sub >> 4, dev_SW_sub & 0xF);
//            snprintf((char*)buf, sizeof(buf), "%d", meter.settings.passport.Firmware_Version_for_communications);
            DLMS_PDU_BUF_AddOctetString(pb, buf, sizeof(buf));
            break;
        }
        case 0x600104: { //Год выпуска счетчика
            DLMS_PDU_BUF_AddUInt16(pb, 2019);
//            DLMS_PDU_BUF_AddUInt16(pb, meter.settings.passport.Meter_year_of_manufacture);
            break;
        }
        case 0x000402: { // Коэффициент трансформации по току 1.0.0.4.2.255
            DLMS_PDU_BUF_AddUInt16(pb, meter.settings.passport.Internal_CT_ratio);
            break;
        }
        case 0x000403: { // Коэффициент трансформации по напряжению 1.0.0.4.3.255
            DLMS_PDU_BUF_AddUInt16(pb, meter.settings.passport.Internal_PT_ratio);
            break;
        }
        case 0x60010A: { // Данные точки учета (до 64 байт) 0.0.96.1.10.255
            uint8_t buf[64];
            memset(buf, 0, sizeof(buf));
//            DLMS_PDU_BUF_AddOctetString(pb, buf, sizeof(buf));
            DLMS_PDU_BUF_AddOctetString(pb, meter.settings.passport.point_name, sizeof(meter.settings.passport.point_name));
            break;
        }
        case 0x000804: { // Период записи в профиль 1
            DLMS_PDU_BUF_AddUInt32(pb, meter.settings.arch_hour.timeout);
//            DLMS_PDU_BUF_AddUInt32(pb, meter.settings.passport.period_profile_1);
            break;
        }
        case 0x000805: { // Период записи в профиль 2
            DLMS_PDU_BUF_AddUInt32(pb, meter.settings.arch_set.timeout);
//            DLMS_PDU_BUF_AddUInt32(pb, meter.settings.passport.period_profile_2);
            break;
        }
        case 0x600401: { // Режим подсветки ЖКИ
            DLMS_PDU_BUF_AddUInt8(pb, 0);
//            DLMS_PDU_BUF_AddUInt8(pb, meter.settings.passport.light);
            break;
        }
        case 0x600402: { // Режим телеметрии
            DLMS_PDU_BUF_AddUInt8(pb, 0);
//            DLMS_PDU_BUF_AddUInt8(pb, meter.settings.passport.telemeria);
            break;
        }
        case 0x600503: { // 0,0,96,5,3,255
            DLMS_PDU_BUF_AddUInt8(pb, 0);
            break;
        }
        case 0x60030A: { // 96,3,10
            DLMS_PDU_BUF_AddUInt8(pb, 0);
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
        switch (obis) {
        case 0x000402: { // Коэффициент трансформации по току
            meter.settings.passport.Internal_CT_ratio = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x000403: { // Коэффициент трансформации по напряжению
            meter.settings.passport.Internal_PT_ratio = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x60010A: { // Данные точки учета (до 64 байт)
            //todo
//            DLMS_PDU_BUF_SetUInt8(pb, 0); // ok
            break;
        }
        case 0x000804: { // Период записи в профиль 1
            meter.settings.arch_hour.timeout = DLMS_PDU_BUF_GetInt(pb);
//            meter.settings.passport.period_profile_1 = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x000805: { // Период записи в профиль 2
            meter.settings.arch_set.timeout = DLMS_PDU_BUF_GetInt(pb);
//            meter.settings.passport.period_profile_2 = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x600401: { // Режим подсветки ЖКИ
            //todo
//            DLMS_PDU_BUF_SetUInt8(pb, 0); // ok
            break;
        }
        case 0x600402: { // Режим телеметрии
            //todo
//            DLMS_PDU_BUF_SetUInt8(pb, 0); // ok
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_event_data___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    UNUSED(pduData);
    uint32_t obis = COSEM_OBIS_to_uint(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
//    //log_1 << QByteArray::number(obis, 16).toUpper() << QByteArray::number(pduHeader->cmd, 16).toUpper();
//    DLMS_PDU_BUF_init(hdlc, pb);
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
//        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
//        DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
//        DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
//        DLMS_PDU_BUF_SetUInt8(pb, 0);
        switch (obis) {
        case 0x600200: {
            DLMS_PDU_BUF_AddUInt32(pb, 0);
            break;
        }
        case 0x601400:
        case 0x601402:
        case 0x601403:
        case 0x601405:
        case 0x601407:
        case 0x601408:
        case 0x60140F:
        case 0x601411:
        case 0x601412: {
            DLMS_PDU_BUF_AddUInt32(pb, 0);
            break;
        }
        default: DLMS_PDU_BUF_AddOctetString(pb, 0, 0);
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
//        DLMS_PDU_BUF_init(hdlc, pb);
//        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_SET_RESPONSE);
//        DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
//        DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
//        DLMS_PDU_BUF_SetUInt8(pb, 0); // ok
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_rs___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // RS
{
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { // Скорость обмена
            if (cobj->obis.B == 1) {
                DLMS_PDU_BUF_AddEnum(pb, meter.settings.rs1.speed);
                break;
            }
            DLMS_PDU_BUF_AddEnum(pb, meter.settings.rs2.speed);
            break;
        }
        case 3: { // Размер окна передачи
            DLMS_PDU_BUF_AddUInt8(pb, 1);
            break;
        }
        case 4: { // Размер окна приема
            DLMS_PDU_BUF_AddUInt8(pb, 1);
            break;
        }
        case 5: { // Максимальная длина поля данных при передаче
            DLMS_PDU_BUF_AddUInt16(pb, 128);
            break;
        }
        case 6: { // Максимальная длина поля данных при приеме
            DLMS_PDU_BUF_AddUInt16(pb, 128);
            break;
        }
        case 7: { // Межсимвольный таймаут
            DLMS_PDU_BUF_AddUInt16(pb, hdlc->timeout_frame);
            break;
        }
        case 8: { // Межкадровый таймаут
            DLMS_PDU_BUF_AddUInt16(pb, hdlc->timeout_connect);
            break;
        }
        case 9: { // Адрес устройства
            if (cobj->obis.B == 1) {
                DLMS_PDU_BUF_AddEnum(pb, meter.settings.rs1.addr);
                break;
            }
            DLMS_PDU_BUF_AddEnum(pb, meter.settings.rs2.addr);
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        uint32_t in_val = 0;
        for (;pduData && pduData->len;) {
            in_val = DLMS_PDU_BUF_GetInt(pduData);
            break;
        }
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { // Скорость обмена
            if (cobj->obis.B == 1) {
                meter.settings.rs1.speed = in_val;
                break;
            }
            meter.settings.rs2.speed = in_val;
            break;
        }
        case 9: { // Адрес устройства
            if (cobj->obis.B == 1) {
                meter.settings.rs1.addr = in_val;
                break;
            }
            meter.settings.rs2.addr = in_val;
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_register_rw___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // настройки
{
    UNUSED(pduData);
    uint32_t obis = COSEM_OBIS_to_uint(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_init(hdlc, pb);
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (obis) {
        case 0x000A02: { // Активное сопротивление линии 1.0.0.10.2.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt16(pb, meter.settings.passport.r_line); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, -2);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_RESISTANCE);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x0C2700: { // Пороговое напряжение для фиксации перерыва питания 1.0.12.39.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt8(pb, meter.settings.limit.u_off); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, 0);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_PERCENTAGE);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x0C2300: { // Порог для фиксации перенапряжения 1.0.12.35.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt8(pb, meter.settings.limit.u_up); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, 0x00);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_PERCENTAGE);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x0C1F00: { // Порог для фиксации провала напряжения 1.0.12.31.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt8(pb, meter.settings.limit.u_down); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, 0);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_PERCENTAGE);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x0C2B00: { // Время перехода напряжения через нижний порог 1.0.12.43.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit.u_down_time); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, -3);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_SECOND);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x0C2C00: { // Время перехода напряжения через верхний порог 1.0.12.44.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit.u_up_time); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, -3);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_SECOND);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x0C2D00: { // Время пропадания напряжения 1.0.12.45.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit.u_off_time); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, -3);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_SECOND);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x832300: { // Порог для фиксации превышения тангенса нагрузки 1.0.131.35.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit.tg); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, -3);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_NO_UNIT);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x852300: { // Порог для фиксации коэффициента несимметрии напряжений 1.0.133.35.0.255
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt8(pb, meter.settings.limit.u_ansymmetry); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, 0);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_PERCENTAGE);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        case 0x000604: { // Согласованное напряжение электропитания 1.0.0.6.4.255 Опорное напряжение для измерения качества электроэнергии
            switch (pduHeader->attributeIndex) {
            case 2: DLMS_PDU_BUF_AddUInt16(pb, meter.settings.passport.u_op); break;
            case 3: {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddInt8(pb, -2);
                DLMS_PDU_BUF_AddEnum(pb, DLMS_UNIT_VOLTAGE);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
        if (pduHeader->attributeIndex != 2) {
             return PDU_DataAccessResult_ReadWriteDenied;
        }
        switch (obis) {
        case 0x000A02: { // Активное сопротивление линии 1.0.0.10.2.255
            meter.settings.passport.r_line = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x0C2700: { // Пороговое напряжение для фиксации перерыва питания 1.0.12.39.0.255
            meter.settings.limit.u_off = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x0C2300: { // Порог для фиксации перенапряжения 1.0.12.35.0.255
            meter.settings.limit.u_up = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x0C1F00: { // Порог для фиксации провала напряжения 1.0.12.31.0.255
            meter.settings.limit.u_down = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x0C2B00: { // Время перехода напряжения через нижний порог 1.0.12.43.0.255
            meter.settings.limit.u_down_time = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x0C2C00: { // Время перехода напряжения через верхний порог 1.0.12.44.0.255
            meter.settings.limit.u_up_time = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x0C2D00: { // Время пропадания напряжения 1.0.12.45.0.255
            meter.settings.limit.u_off_time = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x832300: { // Порог для фиксации превышения тангенса нагрузки 1.0.131.35.0.255
            meter.settings.limit.tg = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x852300: { // Порог для фиксации коэффициента несимметрии напряжений 1.0.133.35.0.255
            meter.settings.limit.u_ansymmetry = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        case 0x000604: { // Согласованное напряжение электропитания 1.0.0.6.4.255 Опорное напряжение для измерения качества электроэнергии
            meter.settings.passport.u_op = DLMS_PDU_BUF_GetInt(pb);
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_profile_0___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    int8_t selection_type = 0;
    uint32_t row_start = 0;
    uint32_t row_end = 0;
    for (;pduHeader->selection && pduData->len;) {
        selection_type = DLMS_PDU_BUF_GetUInt8(pduData);
//        log_1 << pduHeader->selection << selection_type;
        if (selection_type == 2) { // records
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 2) { selection_type = -1; break; }
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 4) { selection_type = -1; break; }
            row_start = DLMS_PDU_BUF_GetInt(pduData);
            row_end = DLMS_PDU_BUF_GetInt(pduData);
            uint32_t column_start = DLMS_PDU_BUF_GetInt(pduData);
            uint32_t column_end = DLMS_PDU_BUF_GetInt(pduData);
            if (pduData->len) {
//                log_1 << "error read";
                selection_type = -1; break;
            }
            if (column_start != 1) { selection_type = -1; break; }
            if (column_end != 0) { selection_type = -1; break; }
            break;
        }
        if (selection_type == 1) { // datetimes
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 2) { selection_type = -1; break; }
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 4) { selection_type = -1; break; }
            {
                if (DLMS_PDU_BUF_GetUInt8(pduData) != 2) { selection_type = -1; break; }
                if (DLMS_PDU_BUF_GetUInt8(pduData) != 4) { selection_type = -1; break; }
                const uint8_t req_data[] = {0x12,0x00,0x08,0x09,0x06,0x00,0x00,0x01,0x00,0x00,0xFF,0x0F,0x02,0x12,0x00,0x00};
                if (memcmp(pduData->data, req_data, sizeof(req_data))) { selection_type = -1; break; }
                pduData->data += sizeof(req_data); pduData->len -= sizeof(req_data);
            }
            row_start = DLMS_PDU_BUF_GetInt(pduData) + 3*60*60; // GMT + 0
            row_end   = DLMS_PDU_BUF_GetInt(pduData) + 3*60*60; // GMT + 0
            if (DLMS_PDU_BUF_GetInt(pduData) != 0) { selection_type = -1; break; }
            if (pduData->len) {
//                log_1 << "error read";
                selection_type = -1; break;
            }
            break;
        }
        break;
    }
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_init(hdlc, pb);
        pb->len = DLMS_MaxServerPDUSize;
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
        DLMS_PDU_BUF_init_RESPONSE(pb, pduHeader);
        if (cobj->obis.C == 94 && cobj->obis.D == 7 && cobj->obis.E == 0) { // мгновенные
            switch (pduHeader->attributeIndex) {
            case 2: { // buffer            // Буфер данных
                DLMS_PDU_BUF_AddArray(pb, 0); // arr records
                uint8_t *p_array_count = pb->data - 1;
                DLMS_PDU_BUF_AddStruct(pb, 0); // record
                uint8_t *p_record_count = pb->data - 1;
                for (uint8_t i = 0; i < 255; ++i) {
                    const COSEM_OBJECT * obj = &cosem_objcts_1_0_94_7_0_255[i];
                    if (!obj->attr && !obj->method) break;
                    (*p_record_count)++;
                }
                (*p_array_count)++;
                for (uint8_t i = 0; i < 255; ++i) {
                    const COSEM_OBJECT * obj = &cosem_objcts_1_0_94_7_0_255[i];
                    if (!obj->attr && !obj->method) break;
                    PDU_BUF_temp_BEGIN(pb_temp, pb)
                    attr_reg_value___2_data(&pb_temp, obj);
                    PDU_BUF_temp_END(pb_temp, pb)
                }
                break;
            }
            case 3: { // capture_objects   // Список захватываемых объектов
                DLMS_PDU_BUF_AddArray(pb, 0);
                uint8_t *p_array_count = pb->data - 1;
                for (uint8_t i = 0; i < 255; ++i) {
                    const COSEM_OBJECT * obj = &cosem_objcts_1_0_94_7_0_255[i];
                    if (!obj->attr && !obj->method) break;
                    (*p_array_count)++;
                }
                for (uint8_t i = 0; i < 255; ++i) {
                    const COSEM_OBJECT * obj = &cosem_objcts_1_0_94_7_0_255[i];
                    if (!obj->attr && !obj->method) break;
                    PDU_BUF_temp_BEGIN(pb_temp, pb)
                    COSEM_profile_array_name(&pb_temp, obj, 2);
                    PDU_BUF_temp_END(pb_temp, pb)
                }
                break;
            }
            case 4: { // capture_period    // Период захвата
                DLMS_PDU_BUF_AddUInt32(pb, 1);   // need 0
                break;
            }
            case 5: { // sort_method       // Метод сортировки
                DLMS_PDU_BUF_AddEnum(pb, 1);
                break;
            }
            case 6: { // sort_object       // Метод сортировки
                DLMS_PDU_BUF_AddStruct(pb, 4);
                DLMS_PDU_BUF_AddUInt16(pb, 0);
                OBIS obis_tmp = {0,0,0,0,0,0};
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 0);
                DLMS_PDU_BUF_AddUInt16(pb, 0);
                break;
            }
            case 7: { // entries_in_use    // Занятых записей
                DLMS_PDU_BUF_AddUInt32(pb, 1);
                break;
            }
            case 8: { // profile_entries   // Всего записей
                DLMS_PDU_BUF_AddUInt32(pb, 1);
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        // данные профилей
        DLMS_ARCH_index aindex = DLMS_ARCH_profile_NONE;
        const COSEM_OBJECT * obj_arr = 0;
        if (cobj->obis.C == 99 && cobj->obis.D == 1 && cobj->obis.E == 0) { // профиль
            aindex = DLMS_ARCH_profile_hour;
            obj_arr = cosem_objcts_1_0_99_1_0_255;
        } else
        if (cobj->obis.C == 98 && cobj->obis.D == 1 && cobj->obis.E == 0) { // месячные
            aindex = DLMS_ARCH_profile_month;
            obj_arr = cosem_objcts_1_0_98_2_0_255;
        } else
        if (cobj->obis.C == 98 && cobj->obis.D == 2 && cobj->obis.E == 0) { // суточные
            aindex = DLMS_ARCH_profile_day;
            obj_arr = cosem_objcts_1_0_98_2_0_255;
        } else
        if (cobj->obis.C == 99 && cobj->obis.D == 2 && cobj->obis.E == 0) { // суточные
            aindex = DLMS_ARCH_profile_day;
            obj_arr = cosem_objcts_1_0_98_2_0_255;
        }

        if (aindex != 255 && obj_arr) {
            switch (pduHeader->attributeIndex) {
            case 2: { // buffer            // Буфер данных
//                log_1 << "select profile" << selection_type << row_start << row_end << pb->block_index << pb->block_index_max;
//                log_1 << "data" << QByteArray((const char*) pduData->data, pduData->len).toHex().toUpper() << pduHeader->selection;
                switch (selection_type) {
                case 0:
                case 2: {
//                    log_1 << "start profile" << selection_type << row_start << row_end;
                    if (!row_end) row_end = DLMS_ARCH_fill_count(aindex);
                    DLMS_PDU_BUF_AddArray(pb, 0x82);  // next 2 byte
                    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                    uint8_t *p_array_count = pb->data - 2;

                    DLMS_ARCH_info * ainfo = &arch_info[aindex];
                    uint16_t max_count = DLMS_ARCH_info_count_max(ainfo); //(ainfo->settings.mem_end - ainfo->settings.mem_start) / ainfo->settings.rec_size;
                    uint16_t start_index = ainfo->index_last + row_start;
                    while (start_index > max_count) {
                        start_index -= max_count;
                    }
                    if (ainfo->index_last < ainfo->index_head) {
                        if (start_index > ainfo->index_head) break;
                    } else {
                        if (start_index - max_count > ainfo->index_head) break;
                    }
                    uint16_t stop_index = ainfo->index_last + row_start + row_end;
                    if (ainfo->index_last <= ainfo->index_head) {
                        if (stop_index > ainfo->index_head) stop_index = ainfo->index_head;
                    } else {
                        if (stop_index > ainfo->index_head + max_count) stop_index = ainfo->index_head + max_count;
                    }
                    while (stop_index > max_count) {
                        stop_index -= max_count;
                    }
                    if (stop_index < start_index) stop_index += max_count;
                    uint16_t array_count = stop_index - start_index;
//                    log_1 << "read rec" << array_count << start_index << stop_index;
                    *p_array_count++ = array_count >> 8;
                    *p_array_count++ = array_count & 0xFF;
                    for (uint16_t index = start_index; index < stop_index; ++index) {
                        uint16_t index_arch = index;
                        if (index_arch >= max_count) {
                            index_arch -= max_count;
                        }
                        PDU_BUF_temp_BEGIN(pb_temp, pb)
                            switch (aindex) {
                            case DLMS_ARCH_profile_hour: {
                                DLMS_ARCH_data_profile_hour ph;
                                if (!DLMS_ARCH_read(aindex, &ph, index_arch)) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 5);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, ph.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.Ap[0]+ph.Ap[1]+ph.Ap[2]+ph.Ap[3]);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.An[0]+ph.An[1]+ph.An[2]+ph.An[3]);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.Rp[0]+ph.Rp[1]+ph.Rp[2]+ph.Rp[3]);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.Rn[0]+ph.Rn[1]+ph.Rn[2]+ph.Rn[3]);
                                } else {
                                    DLMS_PDU_BUF_AddNone(&pb_temp);
                                }
                                break;
                            }
                            case DLMS_ARCH_profile_month:
                            case DLMS_ARCH_profile_day: {
                                DLMS_ARCH_data_profile_day pd;
                                if (!DLMS_ARCH_read(aindex, &pd, index_arch)) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 26);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, pd.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[0] + pd.Ap[1] + pd.Ap[2] + pd.Ap[3]); // Активная энергия +, импорт сумме тарифов
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[0]); // Активная энергия +, импорт по 1 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[1]); // Активная энергия +, импорт по 2 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[2]); // Активная энергия +, импорт по 3 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[3]); // Активная энергия +, импорт по 4 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 5 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 6 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 7 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 8 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[0] + pd.An[1] + pd.An[2] + pd.An[3]); // Активная энергия -, экспорт сумме тарифов
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[0]); // Активная энергия -, экспорт по 1 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[1]); // Активная энергия -, экспорт по 2 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[2]); // Активная энергия -, экспорт по 3 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[3]); // Активная энергия -, экспорт по 4 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[0] + pd.Rp[1] + pd.Rp[2] + pd.Rp[3]); // Реактивная энергия +, импорт сумме тарифов
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[0]); // Реактивная энергия +, импорт по 1 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[1]); // Реактивная энергия +, импорт по 2 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[2]); // Реактивная энергия +, импорт по 3 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[3]); // Реактивная энергия +, импорт по 4 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[0] + pd.Rn[1] + pd.Rn[2] + pd.Rn[3]); // Реактивная энергия -, экспорт сумме тарифов
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[0]); // Реактивная энергия -, экспорт по 1 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[1]); // Реактивная энергия -, экспорт по 2 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[2]); // Реактивная энергия -, экспорт по 3 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[3]); // Реактивная энергия -, экспорт по 4 тарифу
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.P_max); // Максимальная мощность за месяц и время пика мощности
                                } else {
                                    DLMS_PDU_BUF_AddNone(&pb_temp);
                                }
                                break;
                            }
                            default:break;
                            }
                        PDU_BUF_temp_END(pb_temp, pb)
                    }
                    break;
                }
                case 1: {
                    DLMS_PDU_BUF_AddArray(pb, 0x82);  // next 2 byte
                    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                    DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                    uint8_t *p_array_count = pb->data - 2;
                    DLMS_ARCH_info * ainfo = &arch_info[aindex];
                    uint16_t max_count = DLMS_ARCH_info_count_max(ainfo); //(ainfo->settings.mem_end - ainfo->settings.mem_start) / ainfo->settings.rec_size;
                    uint16_t array_count = 0;
                    uint16_t stop_index = ainfo->index_head;
                    if (ainfo->index_head < ainfo->index_last) stop_index += max_count;
                    for (uint16_t index = ainfo->index_last; index < stop_index; ++index) {
                        uint16_t index_arch = index;
                        if (index_arch >= max_count) {
                            index_arch -= max_count;
                        }
                        switch (aindex) {
                        case DLMS_ARCH_profile_hour: {
                            DLMS_ARCH_data_profile_hour ph;
                            if (!DLMS_ARCH_read(aindex, &ph, index_arch)) {
                                if (ph.dt >= row_start && ph.dt <= row_end) {
                                    array_count++;
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_profile_month:
                        case DLMS_ARCH_profile_day: {
                            DLMS_ARCH_data_profile_day pd;
                            if (!DLMS_ARCH_read(aindex, &pd, index_arch)) {
                                if (pd.dt >= row_start && pd.dt <= row_end) {
                                    array_count++;
                                }
                            }
                            break;
                        }
                        default:break;
                        }
                    }
//                    log_1 << "array_count" << array_count;
                    *p_array_count++ = array_count >> 8;
                    *p_array_count++ = array_count & 0xFF;
                    for (uint16_t index = ainfo->index_last; index < stop_index; ++index) {
                        uint16_t index_arch = index;
                        if (index_arch >= max_count) {
                            index_arch -= max_count;
                        }
                        PDU_BUF_temp_BEGIN(pb_temp, pb)
                            switch (aindex) {
                            case DLMS_ARCH_profile_hour: {
                                DLMS_ARCH_data_profile_hour ph;
                                if (!DLMS_ARCH_read(aindex, &ph, index_arch)) {
                                    if (ph.dt >= row_start && ph.dt <= row_end) {
                                        DLMS_PDU_BUF_AddStruct(&pb_temp, 5);
                                        DLMS_PDU_BUF_AddDateTime(&pb_temp, ph.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.Ap[0]+ph.Ap[1]+ph.Ap[2]+ph.Ap[3]);
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.An[0]+ph.An[1]+ph.An[2]+ph.An[3]);
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.Rp[0]+ph.Rp[1]+ph.Rp[2]+ph.Rp[3]);
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, ph.Rn[0]+ph.Rn[1]+ph.Rn[2]+ph.Rn[3]);
                                    }
                                }
                                break;
                            }
                            case DLMS_ARCH_profile_month:
                            case DLMS_ARCH_profile_day: {
                                DLMS_ARCH_data_profile_day pd;
                                if (!DLMS_ARCH_read(aindex, &pd, index_arch)) {
                                    if (pd.dt >= row_start && pd.dt <= row_end) {
                                        DLMS_PDU_BUF_AddStruct(&pb_temp, 26);
                                        DLMS_PDU_BUF_AddDateTime(&pb_temp, pd.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[0] + pd.Ap[1] + pd.Ap[2] + pd.Ap[3]); // Активная энергия +, импорт сумме тарифов
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[0]); // Активная энергия +, импорт по 1 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[1]); // Активная энергия +, импорт по 2 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[2]); // Активная энергия +, импорт по 3 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Ap[3]); // Активная энергия +, импорт по 4 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 5 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 6 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 7 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, 0); // Активная энергия +, импорт по 8 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[0] + pd.An[1] + pd.An[2] + pd.An[3]); // Активная энергия -, экспорт сумме тарифов
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[0]); // Активная энергия -, экспорт по 1 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[1]); // Активная энергия -, экспорт по 2 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[2]); // Активная энергия -, экспорт по 3 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.An[3]); // Активная энергия -, экспорт по 4 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[0] + pd.Rp[1] + pd.Rp[2] + pd.Rp[3]); // Реактивная энергия +, импорт сумме тарифов
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[0]); // Реактивная энергия +, импорт по 1 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[1]); // Реактивная энергия +, импорт по 2 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[2]); // Реактивная энергия +, импорт по 3 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rp[3]); // Реактивная энергия +, импорт по 4 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[0] + pd.Rn[1] + pd.Rn[2] + pd.Rn[3]); // Реактивная энергия -, экспорт сумме тарифов
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[0]); // Реактивная энергия -, экспорт по 1 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[1]); // Реактивная энергия -, экспорт по 2 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[2]); // Реактивная энергия -, экспорт по 3 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.Rn[3]); // Реактивная энергия -, экспорт по 4 тарифу
                                        DLMS_PDU_BUF_AddUInt32(&pb_temp, pd.P_max); // Максимальная мощность за месяц и время пика мощности
                                    }
                                }
                                break;
                            }
                            default:break;
                            }
                        PDU_BUF_temp_END(pb_temp, pb)
                    }
                    break;
                }
                default: {
//                    log_1 << "error selection_type" << selection_type;
                    DLMS_PDU_BUF_AddArray(pb, 0);
                }
                }
                break;
            }
            case 3: { // capture_objects   // Список захватываемых объектов
                DLMS_PDU_BUF_AddArray(pb, 0);
                uint8_t *p_array_count = pb->data - 1;
                for (uint8_t i = 0; i < 255; ++i) {
                    const COSEM_OBJECT * obj = &obj_arr[i];
                    if (!obj->attr && !obj->method) break;
                    (*p_array_count)++;
                }
                for (uint8_t i = 0; i < 255; ++i) {
                    const COSEM_OBJECT * obj = &obj_arr[i];
                    if (!obj->attr && !obj->method) break;
                    PDU_BUF_temp_BEGIN(pb_temp, pb)
                    COSEM_profile_array_name(&pb_temp, obj, 2);
                    PDU_BUF_temp_END(pb_temp, pb)
                }
                break;
            }
            case 4: { // capture_period    // Период захвата
                DLMS_PDU_BUF_AddUInt32(pb, 1);   // need 0
                break;
            }
            case 5: { // sort_method       // Метод сортировки
                DLMS_PDU_BUF_AddEnum(pb, 1);
                break;
            }
            case 6: { // sort_object       // Метод сортировки
                DLMS_PDU_BUF_AddStruct(pb, 4);
                DLMS_PDU_BUF_AddUInt16(pb, 0);
                OBIS obis_tmp = {0,0,0,0,0,0};
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 0);
                DLMS_PDU_BUF_AddUInt16(pb, 0);
                break;
            }
            case 7: { // entries_in_use    // Занятых записей
                DLMS_PDU_BUF_AddUInt32(pb, DLMS_ARCH_fill_count(aindex));
                break;
            }
            case 8: { // profile_entries   // Всего записей
                DLMS_PDU_BUF_AddUInt32(pb, DLMS_ARCH_max_count(aindex));
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        // масштаб
        if (cobj->obis.C == 94 && cobj->obis.D == 7 && cobj->obis.E == 3) { obj_arr = cosem_objcts_1_0_94_7_0_255; // мгновенные масштаб
        } else
        if (cobj->obis.C == 94 && cobj->obis.D == 7 && cobj->obis.E == 4) { obj_arr = cosem_objcts_1_0_99_1_0_255; // профиль масштаб
        } else
        if (cobj->obis.C == 94 && cobj->obis.D == 7 && cobj->obis.E == 1) { obj_arr = cosem_objcts_1_0_98_2_0_255; // месячные масштаб
        } else
        if (cobj->obis.C == 94 && cobj->obis.D == 7 && cobj->obis.E == 2) { obj_arr = cosem_objcts_1_0_98_2_0_255; // суточные масштаб
        }
        if (!obj_arr) return PDU_DataAccessResult_ReadWriteDenied;
        switch (pduHeader->attributeIndex) {
        case 2: { // buffer            // Буфер данных
            DLMS_PDU_BUF_AddArray(pb, 0);
            uint8_t *p_array_count = pb->data - 1;
            DLMS_PDU_BUF_AddStruct(pb, 0);
            uint8_t *p_record_count = pb->data - 1;
            for (uint8_t i = 0; i < 255; ++i) {
                const COSEM_OBJECT * obj = &obj_arr[i];
                if (!obj->attr && !obj->method) break;
                (*p_record_count)++;
            }
            (*p_array_count)++;
            for (uint8_t i = 0; i < 255; ++i) {
                const COSEM_OBJECT * obj = &obj_arr[i];
                if (!obj->attr && !obj->method) break;
                PDU_BUF_temp_BEGIN(pb_temp, pb)
                attr_reg_value___3_data(&pb_temp, obj);
                PDU_BUF_temp_END(pb_temp, pb)
            }
            break;
        }
        case 3: { // capture_objects   // Список захватываемых объектов
            DLMS_PDU_BUF_AddArray(pb, 0);
            uint8_t *p_array_count = pb->data - 1;
            for (uint8_t i = 0; i < 255; ++i) {
                const COSEM_OBJECT * obj = &obj_arr[i];
                if (!obj->attr && !obj->method) break;
                (*p_array_count)++;
            }
            for (uint8_t i = 0; i < 255; ++i) {
                const COSEM_OBJECT * obj = &obj_arr[i];
                if (!obj->attr && !obj->method) break;
                PDU_BUF_temp_BEGIN(pb_temp, pb)
                COSEM_profile_array_name(&pb_temp, obj, 3);
                PDU_BUF_temp_END(pb_temp, pb)
            }
            break;
        }
        case 4: { // capture_period    // Период захвата
            DLMS_PDU_BUF_AddUInt32(pb, 0);   // need 0
            break;
        }
        case 5: { // sort_method       // Метод сортировки
            DLMS_PDU_BUF_AddEnum(pb, 1);
            break;
        }
        case 6: { // sort_object       // Метод сортировки
            DLMS_PDU_BUF_AddStruct(pb, 4);
            DLMS_PDU_BUF_AddUInt16(pb, 0);
            OBIS obis_tmp = {0,0,0,0,0,0};
            DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
            DLMS_PDU_BUF_AddInt8(pb, 0);
            DLMS_PDU_BUF_AddUInt16(pb, 0);
            break;
        }
        case 7: { // entries_in_use    // Занятых записей
            DLMS_PDU_BUF_AddUInt32(pb, 1);
            break;
        }
        case 8: { // profile_entries   // Всего записей
            DLMS_PDU_BUF_AddUInt32(pb, 1);
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    return DLMS_PDU_BUF_to_HDLC(hdlc, pb);
}
PDU_DataAccessResult attr_profile_display___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    UNUSED(pduData);
    uint32_t obis = COSEM_OBIS_to_uint(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    //log_1 << QByteArray::number(obis, 16).toUpper() << QByteArray::number(pduHeader->cmd, 16).toUpper() << pduHeader->attributeIndex;
//    DLMS_PDU_BUF_init(hdlc, pb);
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (obis) {
        case 0x0C0002: { // дисплей по кнопкам
            switch (pduHeader->attributeIndex) {
            case 3: { // capture_objects   // Список захватываемых объектов
                DLMS_PDU_BUF_AddArray(pb, 0);
                break;
            }
            case 4: { // capture_period    // Период захвата
                DLMS_PDU_BUF_AddUInt32(pb, 0);   // need 0
                break;
            }
            default: return PDU_DataAccessResult_ReadWriteDenied;
            }
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_profile_event___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    int8_t selection_type = 0;
    uint32_t row_start = 0;
    uint32_t row_end = 0;
    for (;pduHeader->selection && pduData->len;) {
        selection_type = DLMS_PDU_BUF_GetUInt8(pduData);
//        log_1 << pduHeader->selection << selection_type;
        if (selection_type == 2) { // records
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 2) { selection_type = -1; break; }
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 4) { selection_type = -1; break; }
            row_start = DLMS_PDU_BUF_GetInt(pduData);
            row_end = DLMS_PDU_BUF_GetInt(pduData);
            uint32_t column_start = DLMS_PDU_BUF_GetInt(pduData);
            uint32_t column_end = DLMS_PDU_BUF_GetInt(pduData);
            if (pduData->len) {
//                log_1 << "error read";
                selection_type = -1; break;
            }
            if (column_start != 1) { selection_type = -1; break; }
            if (column_end != 0) { selection_type = -1; break; }
            break;
        }
        if (selection_type == 1) { // datetimes
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 2) { selection_type = -1; break; }
            if (DLMS_PDU_BUF_GetUInt8(pduData) != 4) { selection_type = -1; break; }
            {
                if (DLMS_PDU_BUF_GetUInt8(pduData) != 2) { selection_type = -1; break; }
                if (DLMS_PDU_BUF_GetUInt8(pduData) != 4) { selection_type = -1; break; }
                const uint8_t req_data[] = {0x12,0x00,0x08,0x09,0x06,0x00,0x00,0x01,0x00,0x00,0xFF,0x0F,0x02,0x12,0x00,0x00};
                if (memcmp(pduData->data, req_data, sizeof(req_data))) { selection_type = -1; break; }
                pduData->data += sizeof(req_data); pduData->len -= sizeof(req_data);
            }
            row_start = DLMS_PDU_BUF_GetInt(pduData) + 3*60*60; // GMT + 0
            row_end   = DLMS_PDU_BUF_GetInt(pduData) + 3*60*60; // GMT + 0
            if (DLMS_PDU_BUF_GetInt(pduData) != 0) { selection_type = -1; break; }
            if (pduData->len) {
//                log_1 << "error read";
                selection_type = -1; break;
            }
            break;
        }
        break;
    }
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_init(hdlc, pb);
        pb->len = DLMS_MaxServerPDUSize;
        DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_GET_RESPONSE);
        DLMS_PDU_BUF_init_RESPONSE(pb, pduHeader);

        if (cobj->obis.C != 99 || cobj->obis.D != 98) return PDU_DataAccessResult_ReadWriteDenied;
        DLMS_ARCH_index aindex = DLMS_ARCH_profile_NONE;
        const COSEM_OBJECT * obj_arr = 0;
        switch (cobj->obis.E) {
        case 0: aindex = DLMS_ARCH_event_U;         obj_arr = cosem_objcts_0_0_99_98_0_255; break; // Журнал событий (напряжение)
        case 1: aindex = DLMS_ARCH_event_I;         obj_arr = cosem_objcts_0_0_99_98_1_255; break; // Журнал событий (ток)
        case 2: aindex = DLMS_ARCH_event_rele;      obj_arr = cosem_objcts_0_0_99_98_2_255; break; // Журнал событий (вкл./откл.)
        case 3: aindex = DLMS_ARCH_event_prog;      obj_arr = cosem_objcts_0_0_99_98_3_255; break; // Журнал событий (коррекция данных)
        case 4: aindex = DLMS_ARCH_event_ext;       obj_arr = cosem_objcts_0_0_99_98_4_255; break; // Журнал событий (внешние воздействия)
        case 5: aindex = DLMS_ARCH_event_com;       obj_arr = cosem_objcts_0_0_99_98_5_255; break; // Журнал событий (коммуникационные события)
        case 6: aindex = DLMS_ARCH_event_access;    obj_arr = cosem_objcts_0_0_99_98_6_255; break; // Журнал событий (контроль доступа)
        case 7: aindex = DLMS_ARCH_event_diagnos;   obj_arr = cosem_objcts_0_0_99_98_7_255; break; // Журнал событий (самодиагностика)
        case 8: aindex = DLMS_ARCH_event_tg_pow;    obj_arr = cosem_objcts_0_0_99_98_8_255; break; // Журнал событий (превышение тангенса)
        case 9: aindex = DLMS_ARCH_event_quality;   obj_arr = cosem_objcts_0_0_99_98_9_255; break; // Журнал событий (качество сети)
        case 10:aindex = DLMS_ARCH_event_IO;        obj_arr = cosem_objcts_0_0_99_98_10_255;break; // Журнал событий (дискретные входы и выходы)
        }
        if (aindex == DLMS_ARCH_profile_NONE || !obj_arr) return PDU_DataAccessResult_ReadWriteDenied;

        switch (pduHeader->attributeIndex) {
        case 2: { // buffer            // Буфер данных
//            log_1 << "select profile" << selection_type << row_start << row_end << pb->block_index << pb->block_index_max;
//                log_1 << "data" << QByteArray((const char*) pduData->data, pduData->len).toHex().toUpper() << pduHeader->selection;
            switch (selection_type) {
            case 0:
            case 2: {
//                    log_1 << "start profile" << selection_type << row_start << row_end;
                if (!row_end) row_end = DLMS_ARCH_fill_count(aindex);
                DLMS_PDU_BUF_AddArray(pb, 0x82);  // next 2 byte
                DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                uint8_t *p_array_count = pb->data - 2;

                DLMS_ARCH_info * ainfo = &arch_info[aindex];
                uint16_t max_count = DLMS_ARCH_info_count_max(ainfo); //(ainfo->settings.mem_end - ainfo->settings.mem_start) / ainfo->settings.rec_size;
                uint16_t start_index = ainfo->index_last + row_start;
                while (start_index > max_count) {
                    start_index -= max_count;
                }
                if (ainfo->index_last < ainfo->index_head) {
                    if (start_index > ainfo->index_head) break;
                } else {
                    if (start_index - max_count > ainfo->index_head) break;
                }
                uint16_t stop_index = ainfo->index_last + row_start + row_end;
                if (ainfo->index_last <= ainfo->index_head) {
                    if (stop_index > ainfo->index_head) stop_index = ainfo->index_head;
                } else {
                    if (stop_index > ainfo->index_head + max_count) stop_index = ainfo->index_head + max_count;
                }
                while (stop_index > max_count) {
                    stop_index -= max_count;
                }
                if (stop_index < start_index) stop_index += max_count;
                uint16_t array_count = stop_index - start_index;
//                log_1 << "read rec" << array_count << start_index << stop_index;
                *p_array_count++ = array_count >> 8;
                *p_array_count++ = array_count & 0xFF;
                for (uint16_t index = start_index; index < stop_index; ++index) {
                    uint16_t index_arch = index;
                    if (index_arch >= max_count) {
                        index_arch -= max_count;
                    }
                    PDU_BUF_temp_BEGIN(pb_temp, pb)
                        switch (aindex) {
                        case DLMS_ARCH_event_U: {
                            DLMS_ARCH_data_event_U de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 6);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt16(&pb_temp, de.U);
                                DLMS_PDU_BUF_AddUInt16(&pb_temp, de.dU);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.dt_U);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_I: {
                            DLMS_ARCH_data_event_I de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_rele: {
                            DLMS_ARCH_data_event_rele de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_prog: {
                            DLMS_ARCH_data_event_prog de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 4);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.res);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_ext: {
                            DLMS_ARCH_data_event_ext de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_com: {
                            DLMS_ARCH_data_event_com de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 5);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.channel);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.addr);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_access: {
                            DLMS_ARCH_data_event_access de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 5);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.channel);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.addr);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_diagnos: {
                            DLMS_ARCH_data_event_diagnos de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_tg_pow: {
                            DLMS_ARCH_data_event_tg_pow de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_quality: {
                            DLMS_ARCH_data_event_tg_pow de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        case DLMS_ARCH_event_IO: {
                            DLMS_ARCH_data_event_tg_pow de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                            } else {
                                DLMS_PDU_BUF_AddNone(&pb_temp);
                            }
                            break;
                        }
                        default:break;
                        }
                    PDU_BUF_temp_END(pb_temp, pb)
                }
                break;
            }
            case 1: {
                DLMS_PDU_BUF_AddArray(pb, 0x82);  // next 2 byte
                DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                DLMS_PDU_BUF_SetUInt8(pb, 0x00);
                uint8_t *p_array_count = pb->data - 2;
                DLMS_ARCH_info * ainfo = &arch_info[aindex];
                uint16_t max_count = DLMS_ARCH_info_count_max(ainfo); //(ainfo->settings.mem_end - ainfo->settings.mem_start) / ainfo->settings.rec_size;
                uint16_t array_count = 0;
                uint16_t stop_index = ainfo->index_head;
                if (ainfo->index_head < ainfo->index_last) stop_index += max_count;
                for (uint16_t index = ainfo->index_last; index < stop_index; ++index) {
                    uint16_t index_arch = index;
                    if (index_arch >= max_count) {
                        index_arch -= max_count;
                    }
                    switch (aindex) {
                    case DLMS_ARCH_event_U: {
                        DLMS_ARCH_data_event_U de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_I: {
                        DLMS_ARCH_data_event_I de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_rele: {
                        DLMS_ARCH_data_event_rele de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_prog: {
                        DLMS_ARCH_data_event_prog de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_ext: {
                        DLMS_ARCH_data_event_ext de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_com: {
                        DLMS_ARCH_data_event_com de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_access: {
                        DLMS_ARCH_data_event_access de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_diagnos: {
                        DLMS_ARCH_data_event_diagnos de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_tg_pow: {
                        DLMS_ARCH_data_event_tg_pow de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_quality: {
                        DLMS_ARCH_data_event_tg_pow de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    case DLMS_ARCH_event_IO: {
                        DLMS_ARCH_data_event_tg_pow de;
                        if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                            if (de.dt >= row_start && de.dt <= row_end) {
                                array_count++;
                            }
                        }
                        break;
                    }
                    default:break;
                    }
                }
//                log_1 << "array_count" << array_count;
                *p_array_count++ = array_count >> 8;
                *p_array_count++ = array_count & 0xFF;
                for (uint16_t index = ainfo->index_last; index < stop_index; ++index) {
                    uint16_t index_arch = index;
                    if (index_arch >= max_count) {
                        index_arch -= max_count;
                    }
                    PDU_BUF_temp_BEGIN(pb_temp, pb)
                        switch (aindex) {
                        case DLMS_ARCH_event_U: {
                            DLMS_ARCH_data_event_U de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 6);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt16(&pb_temp, de.U);
                                    DLMS_PDU_BUF_AddUInt16(&pb_temp, de.dU);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.dt_U);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_I: {
                            DLMS_ARCH_data_event_I de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_rele: {
                            DLMS_ARCH_data_event_rele de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_prog: {
                            DLMS_ARCH_data_event_prog de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 4);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.res);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_ext: {
                            DLMS_ARCH_data_event_ext de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_com: {
                            DLMS_ARCH_data_event_com de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 5);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.channel);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.addr);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_access: {
                            DLMS_ARCH_data_event_access de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 5);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.channel);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.addr);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_diagnos: {
                            DLMS_ARCH_data_event_diagnos de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_tg_pow: {
                            DLMS_ARCH_data_event_tg_pow de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_quality: {
                            DLMS_ARCH_data_event_tg_pow de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        case DLMS_ARCH_event_IO: {
                            DLMS_ARCH_data_event_tg_pow de;
                            if (!DLMS_ARCH_read(aindex, &de, index_arch)) {
                                if (de.dt >= row_start && de.dt <= row_end) {
                                    DLMS_PDU_BUF_AddStruct(&pb_temp, 3);
                                    DLMS_PDU_BUF_AddDateTime(&pb_temp, de.dt, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
                                    DLMS_PDU_BUF_AddUInt8(&pb_temp, de.event);
                                    DLMS_PDU_BUF_AddUInt32(&pb_temp, de.work);
                                }
                            }
                            break;
                        }
                        default:break;
                        }
                    PDU_BUF_temp_END(pb_temp, pb)
                }
                break;
            }
            default: {
//                log_1 << "error selection_type" << selection_type;
                DLMS_PDU_BUF_AddArray(pb, 0);
            }
            }
            break;
        }
        case 3: { // capture_objects   // Список захватываемых объектов
            DLMS_PDU_BUF_AddArray(pb, 0);
            uint8_t *p_array_count = pb->data - 1;
            for (uint8_t i = 0; i < 255; ++i) {
                const COSEM_OBJECT * obj = &obj_arr[i];
                if (!obj->attr && !obj->method && !obj->type) break;
                (*p_array_count)++;
            }
            for (uint8_t i = 0; i < 255; ++i) {
                const COSEM_OBJECT * obj = &obj_arr[i];
                if (!obj->attr && !obj->method && !obj->type) break;
                PDU_BUF_temp_BEGIN(pb_temp, pb)
                COSEM_profile_array_name(&pb_temp, obj, 2);
                PDU_BUF_temp_END(pb_temp, pb)
            }
            break;
        }
        case 4: { // capture_period    // Период захвата
            DLMS_PDU_BUF_AddUInt32(pb, 1);   // need 0
            break;
        }
        case 5: { // sort_method       // Метод сортировки
            DLMS_PDU_BUF_AddEnum(pb, 1);
            break;
        }
        case 6: { // sort_object       // Метод сортировки
            DLMS_PDU_BUF_AddStruct(pb, 4);
            DLMS_PDU_BUF_AddUInt16(pb, 0);
            OBIS obis_tmp = {0,0,0,0,0,0};
            DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
            DLMS_PDU_BUF_AddInt8(pb, 0);
            DLMS_PDU_BUF_AddUInt16(pb, 0);
            break;
        }
        case 7: { // entries_in_use    // Занятых записей
            DLMS_PDU_BUF_AddUInt32(pb, DLMS_ARCH_fill_count(aindex));
            break;
        }
        case 8: { // profile_entries   // Всего записей
            DLMS_PDU_BUF_AddUInt32(pb, DLMS_ARCH_max_count(aindex));
            break;
        }
        default: return PDU_DataAccessResult_ReadWriteDenied;
        }
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    return DLMS_PDU_BUF_to_HDLC(hdlc, pb);
}
PDU_DataAccessResult attr_tariff___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData)  // tariff
{
    UNUSED(cobj);
    UNUSED(pduData);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2:     // Имя активного календаря
        case 6: {   // Имя пассивного календаря
            const uint8_t str_tariff_2[] = {0x00};
            DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)str_tariff_2, sizeof(str_tariff_2));
            break;
        }
        case 3:     // Таблица активных сезонных профилей
        case 7: {   // Таблица пассивных сезонных профилей
            DLMS_PDU_BUF_AddArray(pb, 0);
            uint8_t *p_array_count = pb->data - 1;

            uint8_t * tt = meter.settings.tariff.activ;
            if (pduHeader->attributeIndex == 7) tt = meter.settings.tariff.passiv;
            DLMS_tariff_index ti;
            DLMS_tariff_search_start_index(tt, &ti);
            TARIFF_season ts;
            uint16_t index = ti.season;
            while (index < DLMS_tariff_size - 1) {
                TARIFF_header th;
                th.data = tt[index]; index++;
                if (th.seasons.id_block != 1 || th.seasons.id_sub_block != 1) break;

                while (index < DLMS_tariff_size - 1) {
                    TARIFF_block_from_u8(&ts, tt[index], tt[index+1]); index += 2;
                    (*p_array_count)++;
                    DLMS_PDU_BUF_AddStruct(pb, 3);
                    uint8_t data = *p_array_count;
                    DLMS_PDU_BUF_AddOctetString(pb, &data, 1);
                    {
                        DLMS_PDU_BUF_SetUInt8(pb, 9);
                        DLMS_PDU_BUF_SetUInt8(pb, sizeof(COSEM_date_time_struct));
                        COSEM_date_time_struct *cdt = (COSEM_date_time_struct *)pb->data;
                        cdt->year_highbyte = 0xFF;
                        cdt->year_lowbyte  = 0xFF;
                        cdt->month = ts.month;
                        cdt->day_of_month = ts.day;
                        cdt->day_of_week = 0xFF;
                        cdt->hour = 0xFF;
                        cdt->minute = 0xFF;
                        cdt->second = 0xFF;
                        cdt->hundredths_of_second = 0xFF;
                        cdt->deviation_highbyte = 0x80;
                        cdt->deviation_lowbyte = 0x00;
                        cdt->clock_status = 0xFF;
                        pb->data += sizeof(COSEM_date_time_struct);
                    }
                    data = ts.week_id;
                    DLMS_PDU_BUF_AddOctetString(pb, &data, 1);
                    if (!ts.next) {
                        break;
                    }
                }
            }
            break;
        }
        case 4:     // Таблица активных недельных профилей
        case 8: {   // Таблица пассивных недельных профилей
            DLMS_PDU_BUF_AddArray(pb, 0);
            uint8_t *p_array_count = pb->data - 1;

            uint8_t * tt = meter.settings.tariff.activ;
            if (pduHeader->attributeIndex == 8) tt = meter.settings.tariff.passiv;
            DLMS_tariff_index ti;
            DLMS_tariff_search_start_index(tt, &ti);
            TARIFF_week tw;
            uint16_t index = ti.weeks;
            while (index < DLMS_tariff_size - 1) {
                TARIFF_header th;
                th.data = tt[index]; index++;
                if (th.weeks.id_block != 3) break;
                (*p_array_count)++;
                uint8_t week_days[7];
                while (index < DLMS_tariff_size - 1) {
                    TARIFF_block_from_u8(&tw, tt[index], tt[index+1]); index += 2;
                    for (int i = 0; i < 7; ++i) {
                        if ((1 << i) & tw.mask_week) {
                            week_days[i] = tw.day_id;
                        }
                    }
                    if (!tw.next) {
                        break;
                    }
                }
                DLMS_PDU_BUF_AddStruct(pb, 8);
                uint8_t week_id = th.weeks.week_id;
                DLMS_PDU_BUF_AddOctetString(pb, &week_id, 1);
                for (int i = 0; i < 7; ++i) {
                    DLMS_PDU_BUF_AddUInt8(pb, week_days[i]);
                }
            }
            break;
        }
        case 5:     // Таблица активных суточных профилей
        case 9: {   // Таблица пассивных суточных профилей
            DLMS_PDU_BUF_AddArray(pb, 0);
            uint8_t *p_array_count = pb->data - 1;

            uint8_t * tt = meter.settings.tariff.activ;
            if (pduHeader->attributeIndex == 9) tt = meter.settings.tariff.passiv;
            DLMS_tariff_index ti;
            DLMS_tariff_search_start_index(tt, &ti);
            TARIFF_zone tz;
            uint16_t index = ti.days;
            while (index < DLMS_tariff_size - 1) {
                TARIFF_header th;
                th.data = tt[index]; index++;
                if (th.days.id_block != 2) break;
                (*p_array_count)++;

                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddUInt8(pb, th.days.day_id);
                DLMS_PDU_BUF_AddArray(pb, 0);
                uint8_t *p_array_count_zone = pb->data - 1;

                while (index < DLMS_tariff_size - 1) {
                    TARIFF_block_from_u8(&tz, tt[index], tt[index+1]); index += 2;
                    DLMS_PDU_BUF_AddStruct(pb, 3);
                    {
                        DLMS_PDU_BUF_SetUInt8(pb, 9);
                        DLMS_PDU_BUF_SetUInt8(pb, sizeof(COSEM_time_struct));
                        COSEM_time_struct *ct = (COSEM_time_struct *)pb->data;
                        ct->hour = tz.start_zone / 60;
                        ct->minute = tz.start_zone % 60;
                        ct->second = 0;
                        ct->hundredths_of_second = 0;
                        pb->data += sizeof(COSEM_time_struct);
                    }
                    OBIS obis_tmp;
                    obis_tmp.A = 0; obis_tmp.B = 0; obis_tmp.C = 10; obis_tmp.D = 0; obis_tmp.E = 100; obis_tmp.F = 255; // 0.0.10.0.100.255
                    DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                    DLMS_PDU_BUF_AddUInt8(pb, tz.tariff);
//                    day_profile_action ::= structure {
//                      start_time: octet-string,
//                      script_logical_name: octet-string,
//                      script_selector: long-unsigned
//                    }
                    (*p_array_count_zone)++;
                    if (!tz.next) {
                        break;
                    }
                }
            }
            break;
        }
        case 10: {  // Дата активирования пассивного календаря
            uint8_t * tt = meter.settings.tariff.passiv;
            uint32_t ts = DLMS_tariff_search_activate(tt); // получить время активации
            if (ts != 0xFFFFFFFF) {
                DLMS_PDU_BUF_AddDateTime(pb, ts, meter.settings.clock.time_zone, DLMS_PDU_DATA_TYPE_OCTET_STRING);
            } else {
                DLMS_PDU_BUF_AddNone(pb);
            }
//            const uint8_t str_tariff_2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0xFF};
//            DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t *)str_tariff_2, sizeof(str_tariff_2));
            break;
        }
        default: break;
        }
        break;
    }
    default: break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_limit___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData)
{
    UNUSED(pduData);
    UNUSED(cobj);
//    uint32_t obis = COSEM_OBIS_to_uint(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (cobj->obis.E) {
        case 0: { // {{0,0,17,0,0,255} // мощность для отключения
            switch (pduHeader->attributeIndex) {
            case 2: { // Контролируемая величина
                DLMS_PDU_BUF_AddStruct(pb, 3);
                DLMS_PDU_BUF_AddUInt16(pb, 0x03);
                OBIS obis_tmp = {1,0,15,7,0,255}; // 1.0.15.7.0.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 2);
                break;
            }
            case 3: { // Активный порог
                DLMS_PDU_BUF_AddUInt16(pb, meter.settings.limit_off.P_val);
                break;
            }
            case 6: { // Мин. длительность превышения порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.P_time_to_off);
                break;
            }
            case 7: { // Мин. длительность снижения ниже порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.P_time_to_on);
                break;
            }
            case 11: { // Действия
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp1 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp1, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp2 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp2, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                break;
            }
            default: break;
            }
            break;
        }
        case 1: { // {{0,0,17,0,1,255} // ток для отключения
            switch (pduHeader->attributeIndex) {
            case 2: { // Контролируемая величина
                DLMS_PDU_BUF_AddStruct(pb, 3);
                DLMS_PDU_BUF_AddUInt16(pb, 0x03);
                OBIS obis_tmp = {1,0,11,7,0,255}; // 1.0.11.7.0.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 2);
                break;
            }
            case 3: { // Активный порог
                DLMS_PDU_BUF_AddUInt16(pb, meter.settings.limit_off.I_val);
                break;
            }
            case 6: { // Мин. длительность превышения порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.I_time_to_off);
                break;
            }
            case 7: { // Мин. длительность снижения ниже порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.I_time_to_on);
                break;
            }
            case 11: { // Действия
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp1 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp1, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp2 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp2, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                break;
            }
            default: break;
            }
            break;
        }
        case 2: { // {{0,0,17,0,2,255} // напряжения для отключения
            switch (pduHeader->attributeIndex) {
            case 2: { // Контролируемая величина
                DLMS_PDU_BUF_AddStruct(pb, 3);
                DLMS_PDU_BUF_AddUInt16(pb, 0x03);
                OBIS obis_tmp = {1,0,12,7,0,255}; // 1.0.12.7.0.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 2);
                break;
            }
            case 3: { // Активный порог
                DLMS_PDU_BUF_AddUInt16(pb, meter.settings.limit_off.U_val);
                break;
            }
            case 6: { // Мин. длительность превышения порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.U_time_to_off);
                break;
            }
            case 7: { // Мин. длительность снижения ниже порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.U_time_to_on);
                break;
            }
            case 11: { // Действия
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp1 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp1, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp2 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp2, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                break;
            }
            default: break;
            }
            break;
        }
        case 3: { // {{0,0,17,0,3,255} // воздействия магнитного поля для отключения
            switch (pduHeader->attributeIndex) {
            case 2: { // Контролируемая величина
                DLMS_PDU_BUF_AddStruct(pb, 3);
                DLMS_PDU_BUF_AddUInt16(pb, 0x03);
                OBIS obis_tmp = {0,0,96,20,15,255}; // 0.0.96.20.15.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 2);
                break;
            }
            case 3: { // Активный порог
                DLMS_PDU_BUF_AddUInt16(pb, meter.settings.limit_off.M_val);
                break;
            }
            case 6: { // Мин. длительность превышения порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.M_time_to_off);
                break;
            }
            case 7: { // Мин. длительность снижения ниже порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.M_time_to_on);
                break;
            }
            case 11: { // Действия
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp1 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp1, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp2 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp2, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                break;
            }
            default: break;
            }
            break;
        }
        case 4: { // {{0,0,17,0,4,255} // разбаланс токов для отключения
            switch (pduHeader->attributeIndex) {
            case 2: { // Контролируемая величина
                DLMS_PDU_BUF_AddStruct(pb, 3);
                DLMS_PDU_BUF_AddUInt16(pb, 0x03);
                OBIS obis_tmp = {1,0,91,7,0,255}; // 1.0.91.7.0.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 2);
                break;
            }
            case 3: { // Активный порог
                DLMS_PDU_BUF_AddUInt16(pb, meter.settings.limit_off.dI_val);
                break;
            }
            case 6: { // Мин. длительность превышения порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.dI_time_to_off);
                break;
            }
            case 7: { // Мин. длительность снижения ниже порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.dI_time_to_on);
                break;
            }
            case 11: { // Действия
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp1 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp1, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp2 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp2, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                break;
            }
            default: break;
            }
            break;
        }
        case 5: { // {{0,0,17,0,5,255} // превышение температуры для отключения
            switch (pduHeader->attributeIndex) {
            case 2: { // Контролируемая величина
                DLMS_PDU_BUF_AddStruct(pb, 3);
                DLMS_PDU_BUF_AddUInt16(pb, 0x03);
                OBIS obis_tmp = {0,0,96,9,0,255}; // 0.0.96.9.0.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 2);
                break;
            }
            case 3: { // Активный порог
                DLMS_PDU_BUF_AddUInt16(pb, meter.settings.limit_off.T_val);
                break;
            }
            case 6: { // Мин. длительность превышения порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.T_time_to_off);
                break;
            }
            case 7: { // Мин. длительность снижения ниже порога
                DLMS_PDU_BUF_AddUInt32(pb, meter.settings.limit_off.T_time_to_on);
                break;
            }
            case 11: { // Действия
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp1 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp1, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 2);
                OBIS obis_tmp2 = {0,0,10,0,106,255}; // 0.0.10.0.106.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp2, sizeof(OBIS));
                DLMS_PDU_BUF_AddUInt16(pb, 1);
                break;
            }
            default: break;
            }
            break;
        }
        default: break;
        }
        break;
    }
    default: break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_script___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // script
{
    UNUSED(pduData);
    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { //
            //0.0.10.0.100.255
            DLMS_PDU_BUF_AddArray(pb, 8);
            for (uint8_t i = 0; i < 8; ++i) {
                uint8_t data = i + 1;
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddUInt16(pb, data);
                DLMS_PDU_BUF_AddArray(pb, 1);
                DLMS_PDU_BUF_AddStruct(pb, 5);
                DLMS_PDU_BUF_AddEnum(pb, 1);
                DLMS_PDU_BUF_AddUInt16(pb, 6);
                OBIS obis_tmp;
                obis_tmp.A = 0; obis_tmp.B = 0; obis_tmp.C = 14; obis_tmp.D = 0; obis_tmp.E = 0; obis_tmp.F = 255; // 0.0.14.0.0.255
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
                DLMS_PDU_BUF_AddInt8(pb, 4);
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&data, 1);
            }
            break;
        }
        default: break;
        }
        break;
    }
    default: break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_reg_active___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // active
{
    UNUSED(pduData);
    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { //0.0.14.0.0.255
            DLMS_PDU_BUF_AddArray(pb, 8);
            for (uint8_t i = 0; i < 8; ++i) {
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddUInt16(pb, 3);
                OBIS obis_tmp;
                obis_tmp.A = 1; obis_tmp.B = 0; obis_tmp.C = 1; obis_tmp.D = 8; obis_tmp.E = i+1; obis_tmp.F = 255;
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&obis_tmp, sizeof(OBIS));
            }
            break;
        }
        case 3: { //0.0.14.0.0.255
            DLMS_PDU_BUF_AddArray(pb, 8);
            for (uint8_t i = 0; i < 8; ++i) {
                uint8_t data = i + 1;
                DLMS_PDU_BUF_AddStruct(pb, 2);
                DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&data, 1);
                DLMS_PDU_BUF_AddArray(pb, 1);
                DLMS_PDU_BUF_AddUInt8(pb, data);
            }
            break;
        }
        case 4: { //0.0.14.0.0.255
            uint8_t data = meter.vars.tariff_curr + 1; //DLMS_tariff_from_timestamp(METER_now()) + 1;
            DLMS_PDU_BUF_AddOctetString(pb, (const uint8_t*)&data, 1);
            break;
        }
        default: break;
        }
        break;
    }
    default: break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult attr_spec_days___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // spec_days
{
    UNUSED(pduData);
    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        DLMS_PDU_BUF_AddArray(pb, 0);
        uint8_t *p_array_count = pb->data - 1;
        uint8_t * tt = meter.settings.tariff.activ;
//        uint8_t * tt = meter.settings.tariff.passiv;
        DLMS_tariff_index ti;
        DLMS_tariff_search_start_index(tt, &ti);
        TARIFF_special_day ts;
        uint16_t index = ti.special;
        while (index < DLMS_tariff_size - 1) {
            TARIFF_header th;
            th.data = tt[index]; index++;
            if (th.special_day.id_block != 1 || th.special_day.id_sub_block != 2) break;
            while (index < DLMS_tariff_size - 1) {
                TARIFF_block_from_u8(&ts, tt[index], tt[index+1]); index += 2;
                (*p_array_count)++;
                DLMS_PDU_BUF_AddStruct(pb, 3);
                uint8_t data = *p_array_count;
                DLMS_PDU_BUF_AddUInt16(pb, data);
                {
                    DLMS_PDU_BUF_SetUInt8(pb, 9);
                    DLMS_PDU_BUF_SetUInt8(pb, sizeof(COSEM_date_struct));
                    COSEM_date_struct *cd = (COSEM_date_struct *)pb->data;
                    cd->year_highbyte = 0xFF;
                    cd->year_lowbyte  = 0xFF;
                    cd->month = ts.month;
                    cd->day_of_month = ts.day;
                    cd->day_of_week = 0xFF;
                    pb->data += sizeof(COSEM_date_struct);
                }
                DLMS_PDU_BUF_AddUInt8(pb, ts.day_id);
                if (!ts.next) {
                    break;
                }
            }
        }
        break;
    }
    default: break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}

PDU_DataAccessResult attr_img_transf___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Image Transfer
{
//    UNUSED(pduData);
//    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        switch (pduHeader->attributeIndex) {
        case 2: { // Размер блока данных  06, 32-р. без знака
            DLMS_PDU_BUF_AddUInt32(pb, UPGRADE_BLOCK_SIZE);
            break;
        }
        case 3: { // Статус передачи блоков данных 04, строка битов
            DLMS_PDU_BUF_AddBitString(pb, 0);
            break;
        }
        case 4: { // Номер первого непереданного блока 06, 32-р. без знака
            DLMS_PDU_BUF_AddUInt32(pb, meter.vars.img_transf.last_block_index);
            break;
        }
        case 5: { // Разрешение передачи данных 03, логическая
//            DLMS_PDU_BUF_AddBool(pb, meter.vars.img_transf.status <= 1);
            DLMS_PDU_BUF_AddBool(pb, 1);
            break;
        }
        case 6: { // Статус блока данных 22, из списка
            DLMS_PDU_BUF_AddEnum(pb, meter.vars.img_transf.status);
            //(0) Image transfer not initiated,
            //(1) Image transfer initiated,
            //(2) Image verification initiated,
            //(3) Image verification successful,
            //(4) Image verification failed,
            //(5) Image activation initiated,
            //(6) Image activation successful,
            //(7) Image activation failed
            break;
        }
        case 7: { // Информация для активации 01, массив
            DLMS_PDU_BUF_AddArray(pb, 0);
            break;
        }
        default: break;
        }
        break;
    }
    default: break;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}
PDU_DataAccessResult meth_img_transf___x(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Image Transfer
{
//    UNUSED(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
    DLMS_PDU_BUF_init(hdlc, pb);
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_COMMAND_METHOD_RESPONSE);
    DLMS_PDU_BUF_SetUInt8(pb, DLMS_GET_COMMAND_TYPE_NORMAL);
    DLMS_PDU_BUF_SetUInt8(pb, pduHeader->invoke_id_and_priority);
    DLMS_PDU_BUF_SetUInt8(pb, 0);
    switch (pduHeader->attributeIndex) {
    case 1: { // Инициализация передачи
        for (int i = 0; i < 32; ++i) {
            FLASH_EXT_erase_page(UPGRADE_START_ADR + i * DLMS_ARCH_page_size);
        }
        meter.vars.img_transf.status = 1;
        meter.vars.img_transf.last_block_index = 0;
        break;
    }
    case 2: { // Передача блока данных
        uint32_t struct_len = DLMS_PDU_BUF_GetInt(pduData);
        if (struct_len != 2) return PDU_DataAccessResult_HardwareFault;
        uint32_t block_index = DLMS_PDU_BUF_GetInt(pduData);
//        log_1 << "block_index" << block_index;
        if (meter.vars.img_transf.last_block_index != block_index) return PDU_DataAccessResult_DataBlockNumberInvalid;
        meter.vars.img_transf.last_block_index++;
        if (DLMS_PDU_BUF_GetUInt8(pduData) != 9) return PDU_DataAccessResult_HardwareFault;
        uint16_t data_len = DLMS_PDU_BUF_GetUInt8(pduData);
//        log_1 << "data_len" << data_len << (pduData->len == data_len);
        if (pduData->len != data_len) return PDU_DataAccessResult_LongSetOrWriteAborted;
        FLASH_EXT_write(UPGRADE_START_ADR + block_index * UPGRADE_BLOCK_SIZE, pduData->data, pduData->len);
//        log_1 << QByteArray((const char*)pduData->data, pduData->len).toHex().toUpper();
        break;
    }
    case 3: { // Проверка файла
        meter.vars.img_transf.status = 2;
        uint8_t res = FLASH_EXT_check_update(UPGRADE_START_ADR, 0);
//        log_1 << res;
        meter.vars.img_transf.status = 3;
        if (res) {
            meter.vars.img_transf.status = 4;
            //return PDU_DataAccessResult_OtherReason;
        }
        break;
    }
    case 4: { // Активирование файла
        meter.vars.img_transf.status = 6;
        // todo reboot   NVIC_SystemReset();
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }

    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}

#include "MODEM_radio.h"
uint8_t * pb_data_bridge = 0;
nbfi_status_t Electro_send_radio_bridge(uint8_t* payload, uint8_t length)
{
    memmove(pb_data_bridge, payload, length);
    *(pb_data_bridge-1) = length;
    pb_data_bridge += length;
    return OK;
}

PDU_DataAccessResult attr_radio_bridge_data(HDLC_BUF *hdlc, PDU_header *pduHeader, const COSEM_OBJECT *cobj, DLMS_PDU_BUF *pduData) // Значение
{
    UNUSED(pduData);
    uint32_t obis = COSEM_OBIS_to_uint(cobj);
    DLMS_PDU_BUF _pb;
    DLMS_PDU_BUF * pb = &_pb;
//    //log_1 << QByteArray::number(obis, 16).toUpper() << QByteArray::number(pduHeader->cmd, 16).toUpper();
    DLMS_PDU_BUF_init(hdlc, pb);
    switch (pduHeader->cmd) {
    case DLMS_COMMAND_GET_REQUEST: {
        DLMS_PDU_BUF_start_GET_RESPONSE(hdlc, pb, pduHeader);
        uint8_t buf[8];
        memset(buf, 0, sizeof(buf));
//            snprintf((char*)buf, sizeof(buf), "%d", meter.settings.passport.Meter_Serial_Number);
        DLMS_PDU_BUF_AddOctetString(pb, buf, sizeof(buf));
        break;
    }
    case DLMS_COMMAND_SET_REQUEST: {
        if (!pduData || pduData->len < 2) return PDU_DataAccessResult_HardwareFault;
        uint8_t tmp = DLMS_PDU_BUF_GetUInt8(pduData);
        if (tmp != DLMS_PDU_DATA_TYPE_OCTET_STRING) return PDU_DataAccessResult_HardwareFault;
        tmp = DLMS_PDU_BUF_GetUInt8(pduData);
        if (tmp != pduData->len) return PDU_DataAccessResult_HardwareFault;
        
        DLMS_PDU_BUF_start_SET_RESPONSE(hdlc, pb, pduHeader);
        DLMS_PDU_BUF_AddOctetString(pb, 0, 0);
        pb_data_bridge = pb->data;
        Electro_get(pduData->data, pduData->len, Electro_send_radio_bridge);
        pb->data += pb_data_bridge - pb->data;
//        pb->len += pb_data_bridge - pb->data;
        break;
    }
    default: return PDU_DataAccessResult_HardwareFault;
    }
    DLMS_PDU_BUF_to_HDLC(hdlc, pb);
    return PDU_DataAccessResult_Success;
}

void ELECTRO5_HDLC_PDU_controller(HDLC_BUF *hdlc)
{
    pb_data_bridge = hdlc->data_buf;
    Electro_get(hdlc->data_buf, hdlc->data_len, Electro_send_radio_bridge);
    if (pb_data_bridge != hdlc->data_buf) {
        hdlc->data_len = pb_data_bridge - hdlc->data_buf;
        DLMS_HDLC_Send(hdlc);
    }
}
