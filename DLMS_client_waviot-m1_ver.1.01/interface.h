#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdint.h>
#include <QList>
#include <QVariant>
#include <QJsonDocument>
#include "DLMS_obis_pack.h"

class OBIS_cpp
{
public:
    OBIS_cpp();
    OBIS_cpp(OBIS obis) : obis(obis) {}
    OBIS_cpp(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F = 255) {
        obis.A = A;
        obis.B = B;
        obis.C = C;
        obis.D = D;
        obis.E = E;
        obis.F = F;
    }
    OBIS_cpp(uint8_t C, uint8_t D, uint8_t E) {
        obis.A = 0;
        obis.B = 0;
        obis.C = C;
        obis.D = D;
        obis.E = E;
        obis.F = 255;
    }
    const QString toString() {
//        return QString("OBIS_%1_%2_%3_%4_%5_%6").arg(obis.A).arg(obis.B).arg(obis.C).arg(obis.D).arg(obis.E).arg(obis.F);
        return QString("%1.%2.%3.%4.%5.%6").arg(obis.A).arg(obis.B).arg(obis.C).arg(obis.D).arg(obis.E).arg(obis.F);
    }
    const QByteArray toHEX() {
        return QByteArray((const char *)&obis, 6).toHex().toUpper();
    }
    OBIS obis;
    inline bool operator<(const OBIS_cpp &s2) const {
        uint64_t val1 = this->obis.A;
        val1 <<= 8;
        val1 += this->obis.B;
        val1 <<= 8;
        val1 += this->obis.C;
        val1 <<= 8;
        val1 += this->obis.D;
        val1 <<= 8;
        val1 += this->obis.E;
        val1 <<= 8;
        val1 += this->obis.F;

        uint64_t val2 = s2.obis.A;
        val2 <<= 8;
        val2 += s2.obis.B;
        val2 <<= 8;
        val2 += s2.obis.C;
        val2 <<= 8;
        val2 += s2.obis.D;
        val2 <<= 8;
        val2 += s2.obis.E;
        val2 <<= 8;
        val2 += s2.obis.F;

        return val1 < val2;
    }
};

class Rabbit_ul_app  {
public:
    int16_t bs_tz;
    uint16_t bs_id;
    uint32_t modem_id;
    uint32_t ts;
    QString hw_type;
    QByteArray payload;
    // uint8_t phy;
    // QByteArray protocol;
    // int8_t rssi;
    // int8_t snr;
};

class Rabbit_dl_status  {
public:
//    uint16_t bs_id;
    bool is_success;
    uint32_t modem_id;
    uint32_t cmd_id;
    // uint8_t phy;
    // int8_t noise;
    // int8_t snr;
};

class Parser_ul_data {
public:
    Parser_ul_data() : ts(0), index(0), index_ext(65535) {}
    uint32_t ts;
    uint16_t index;
    uint16_t index_ext;
    QMap<OBIS_cpp, QVariant> data;
};

class Parser_ul_event {
public:
    Parser_ul_event() : ts(0), work(0), index(0), index_ext(65535), event(0) {}
    uint32_t ts;
    uint32_t work;
    uint16_t index;
    uint16_t index_ext;
    uint8_t event;
    OBIS obis;
    QMap<OBIS_cpp, QVariant> event_ext;
};

class Parser_ul_setting {
public:
//    Parser_ul_setting();
    Parser_ul_setting(uint32_t ts, QString setting, QVariant value) : ts(ts), setting(setting), value(value) { }
    uint32_t ts;
    QString setting;
    QVariant value;
};

class Parser_ul_app {
public:
    Rabbit_ul_app ul;
    uint8_t header;
    QList<Parser_ul_data> ul_datas;
    QList<Parser_ul_event> ul_events;
    QList<Parser_ul_setting> ul_settings;

    QStringList set_cmd_success;
    QStringList set_cmd_fail;

    void add_setting_with_cmd_success(Parser_ul_setting ul_settings) {
        this->ul_settings << ul_settings;
        set_cmd_success << ul_settings.setting;
    }
};

class API_dl_app {
public:
    API_dl_app() {}
    API_dl_app(uint32_t modem_id, uint32_t ts, QString cmd, QVariant value) : modem_id(modem_id), ts(ts), cmd(cmd), value(value) {}
    uint32_t modem_id;
    uint32_t ts;
    QString cmd;
    QVariant value;
};

class Stringify_dl_app {
public:
    typedef enum {
        DL_STATE_ack_only = 0,          // дождаться только акка
        DL_STATE_ack_AND_wait_data = 1, // дождаться акка, дождаться данных
        DL_STATE_wait_data = 2,         // дождаться данных
        DL_STATE_success = 3,           // успешно доставлен
        DL_STATE_fail = 4,              // ошибка доставки
        DL_STATE_ack_copy = 5,          // дождаться акка, скопировать значение в сеттинг
    } DL_STATE;
    Stringify_dl_app() {}
    Stringify_dl_app(API_dl_app api_dl_app) : api_dl_app(api_dl_app), cmd_id(0), dl_state(DL_STATE_ack_AND_wait_data), mess_is_not_hex(false) {}
    API_dl_app api_dl_app;
    QByteArray mess;
    uint32_t cmd_id;
    DL_STATE dl_state;
    bool mess_is_not_hex;
};

class Driver_static {
public:
    static QVariant setting_value_from_string(QVariant value_db)
    {
        QByteArray arr = value_db.toString().toLocal8Bit();
        if (!QJsonDocument::fromJson(arr).isEmpty()) {
            value_db = QJsonDocument::fromJson(arr).toVariant();
        }
        return value_db;
    }
};

#endif // INTERFACE_H
