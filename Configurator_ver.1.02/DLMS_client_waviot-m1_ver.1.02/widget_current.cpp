#include "widget_current.h"
#include "ui_widget_current.h"

#include <Logger/Logger.h>
#include <QJsonDocument>

#include "DLMS_obis_pack.h"
#include "DLMS_PDU.h"

typedef struct {
    uint8_t timestamp_flag : 1;
    uint8_t obis_C : 7; //param + phase
    uint8_t rezerv : 1;
    uint8_t obis_E : 3; //tariff
    uint8_t obis_B : 2; //channel = 0
    uint8_t obis_A : 1;
    uint8_t obis_D : 1; //cur = 0, intgr = 1
} PARAM_IDENTIFIER;

model_current::model_current(bool is_calib, uint8_t dev_HW_id, QObject *parent)
    : QAbstractTableModel(parent)
    , is_calib(is_calib)
    , dev_HW_id(dev_HW_id)
{

}

int model_current::rowCount(const QModelIndex &parent) const
{
    return 5;
}

int model_current::columnCount(const QModelIndex &parent) const
{
    return 4+3;
}

QVariant model_current::cal_show(uint32_t cal_data) const
{
//    log_1 << QString::number(dev_HW_id, 16).toUpper();
    if ((dev_HW_id & 0x30) == 0x30) {
        int32_t cald = cal_data << 8;
        float cal = ((float) cald / 0x80000000) + 1.0;
        return QString::number(cal, 'g', 6);
    } else {
        uint32_t cald = cal_data << 9;
        float cal = ((float) cald / 0x80000000) + 0.0;
        return QString::number(cal, 'g', 6);
    }
}

uint32_t model_current::show_cal(QVariant data)
{
//    log_1 << QString::number(dev_HW_id, 16).toUpper();
    if ((dev_HW_id & 0x30) == 0x30) {
        float f = data.toFloat();
//        log_1 << f << data.toFloat();
        f -= 1.0;
        f *= 0x80000000;
        int32_t cald = f;
        uint32_t cal_data = cald;
        cal_data >>= 8;
        if (cal_data > 0x800000) cal_data |= 0xF000000;
        return cal_data;
    } else {
        float f = data.toFloat();
        f -= 0.0;
        f *= 0x80000000;
        uint32_t cal_data = f;
        cal_data >>= 9;
        return cal_data;
    }
}


QVariant model_current::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole: {
        QVariantMap vm = curr_data.value("data", QVariantMap()).toMap();
        int col = index.column();
        ADE_cal cal;
        memset(&cal, 0, sizeof(ADE_cal));
        cal = cal_data.value(col - 4, cal);
        switch (index.row()) {
        case 0: { // U
//            EF09 00 F1D2B80F C97DF40F 00021C0000021C0001616DB80F3995F40F00021C0000021C000231F8B70F1591F40F00021C0000021C00031FEFF60FFEFFFF0F0000000000000000
//0FF47DC9
//            uint32_t cal_data = vmcal.value("v", 0).toInt();
            switch (col) {
            case 1: return vm.value("0100200700FF", "").toString();
            case 2: return vm.value("0100340700FF", "").toString();
            case 3: return vm.value("0100480700FF", "").toString();
//            case 4: {log_1 << QString::number(vmcal.value("v", 0).toInt(), 16).toUpper(); return cal;}
            case 4: return cal_show(cal.v);
            case 5: return cal_show(cal.v);
            case 6: return cal_show(cal.v);
            default: break;
            }
        }
        case 1: { // I
//            uint32_t cal_data = vmcal.value("i", 0).toInt();
            switch (col) {
            case 1: if (vm.contains("01001F0701FF")) return vm.value("01001F0701FF", "").toString(); else return vm.value("01001F0700FF", "").toString();
            case 2: if (vm.contains("0100330701FF")) return vm.value("0100330701FF", "").toString(); else return vm.value("0100330700FF", "").toString();
            case 3: if (vm.contains("0100470701FF")) return vm.value("0100470701FF", "").toString(); else return vm.value("0100470700FF", "").toString();
            case 4: return cal_show(cal.i);
            case 5: return cal_show(cal.i);
            case 6: return cal_show(cal.i);
            default: break;
            }
        }
        case 2: { // P
//            uint32_t cal_data = vmcal.value("w", 0).toInt();
            switch (col) {
            case 1: return vm.value("0100150700FF", "").toString();
            case 2: return vm.value("0100290700FF", "").toString();
            case 3: return vm.value("01003D0700FF", "").toString();
            case 4: return cal_show(cal.w);
            case 5: return cal_show(cal.w);
            case 6: return cal_show(cal.w);
            default: break;
            }
        }
        case 3: { // Q
//            uint32_t cal_data = vmcal.value("var", 0).toInt();
            switch (col) {
            case 1: return vm.value("0100170700FF", "").toString();
            case 2: return vm.value("01002B0700FF", "").toString();
            case 3: return vm.value("01003F0700FF", "").toString();
            case 4: return cal_show(cal.var);
            case 5: return cal_show(cal.var);
            case 6: return cal_show(cal.var);
            default: break;
            }
        }
        default:
            break;
        }
        break;
    }
    default: break;
    }
    return QVariant();
}

bool model_current::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!is_calib) return false;
    if (role != Qt::EditRole) return QAbstractTableModel::setData(index, value, role);
    int col = index.column();
    if (col && col < 4) {
        uint8_t obis_c = 0;
        if (index.row() == 0) obis_c = 12; // U
        if (index.row() == 1) obis_c = 11; // I
        if (!obis_c) return false;
        obis_c += index.column() * 20;
        if (obis_c < 20) return false;
        float val = value.toFloat();
        if (!val) return false;

        QByteArray arr_out((int)20, 0x00);
        uint8_t * buf = (uint8_t *)arr_out.data();
        OBIS obis;
        obis.A = 1;
        obis.B = 0;
        obis.C = obis_c;
        obis.D = 7;
        obis.E = 0;
        obis.F = 255;
        *buf++ = 0xEF;
        *buf++ = 0x1A;
        buf += ElectroAdd_OBIS(buf, &obis);
        memmove(buf, &val, 4);
        buf += 4;

        arr_out = arr_out.mid(0, buf - (uint8_t *)arr_out.data());
        log_1 << arr_out.toHex().toUpper();

        emit signal_write_data(arr_out);

        return true;

//        EF0900D7BCF10FC07DF40F1AC01B001AC01B00016FE5F00F1895F40F1AC01B001AC01B00020A21F00FB684F40F1AC01B001AC01B00031FEFF60FFEFFFF0F0000000000000000

//        float val_old = data(index).toFloat();
//        log_1 << val_old << val;
//        QVariantMap vm = cal_data.value(QString::number(index.column() - 1), "").toMap();
//        uint32_t cal_old  = 0;
//        switch (index.row()) {
//        case 0: { // U
//            cal_old = vm.value("v", 0).toUInt();
//            break;
//        }
//        case 1: { // I
//            cal_old = vm.value("i", 0).toUInt();
//            break;
//        }
//        case 2: { // P
//            cal_old = vm.value("w", 0).toUInt();
//            break;
//        }
//        case 3: { // Q
//            cal_old = vm.value("var", 0).toUInt();
//            break;
//        }
//        default: break;
//        }
//        float calf_old = cal_show(cal_old).toFloat();
//        float calf = calf_old * val / val_old;
//        uint32_t cal = show_cal(calf);
//        log_1 << "val" << val_old << val
//              << "calf" << calf_old << calf
//              << "cal" << QString::number(cal_old, 16).toUpper() << QString::number(cal, 16).toUpper();

//        return false;
    }
    if (col >= 4 && col <= 6) {
        if (!cal_data.contains(col - 4)) return false;
//        QVariantMap vm = cal_data.value(QString::number(index.column() - 4), "").toMap();
        ADE_cal cal;
        memset(&cal, 0, sizeof(ADE_cal));
        cal = cal_data.take(col - 4);

        log_1 << col - 4;
        log_1 << cal_show(cal.v) << cal_show(cal.i) << cal_show(cal.w) << cal_show(cal.var);
//        if (vm.isEmpty()) return false;
        uint32_t val = show_cal(value);
//        int32_t ival = value.toInt();
//        uint32_t val = ival > 0 ? ival : ival & 0xFFFFFFF;
        switch (index.row()) {
        case 0: { // U
            log_1 << cal.v << " to " << val;
            cal.v = val;
//            vm.insert("v", val);
            break;
        }
        case 1: { // I
            log_1 << QString::number(cal.i, 16).toUpper() << " to " << QString::number(val, 16).toUpper();
            cal.i = val;
            log_1 << cal_show(val);
//            vm.insert("i", val);
            break;
        }
        case 2: { // P
            log_1 << cal.w << " to " << val;
            cal.w = val;
//            vm.insert("w", val);
            break;
        }
        case 3: { // Q
            log_1 << cal.var << " to " << val;
            cal.var = val;
//            vm.insert("var", val);
            break;
        }
        default: break;
        }
        log_1 << col - 4;
        cal_data.insert(col - 4, cal);

        QByteArray arr_out((int)256, 0);
        uint8_t *buf = (uint8_t *)arr_out.data();
        *buf++ = 0xEF;
        *buf++ = 0x09;
        for (QMap<uint32_t, ADE_cal>::iterator cal_iter = cal_data.begin(); cal_iter != cal_data.end(); ++cal_iter) {
            *buf++ = cal_iter.key();
            ADE_cal ade_cal = cal_iter.value();
//            QVariantMap vm = QVariant(cal_iter.value()).toMap();
//            ADE_cal ade_cal;
//            ade_cal.i = vm.value("i", 0).toInt(); // ADE_Cal_phase[phase].aigain;
//            ade_cal.v = vm.value("v", 0).toInt(); // ADE_Cal_phase[phase].avgain;
//            ade_cal.w = vm.value("w", 0).toInt(); // ADE_Cal_phase[phase].awgain;
//            ade_cal.var = vm.value("var", 0).toInt(); // ADE_Cal_phase[phase].avargain;
            memmove(buf, &ade_cal, sizeof(ADE_cal));
            buf += sizeof(ADE_cal);
        }
        arr_out = arr_out.mid(0, buf - (uint8_t *)arr_out.data());

        emit signal_write_data(arr_out);

// 72C1A2   EF09003E4EBB0FF3A6F40F00021C0000021C00017007BB0F38A5F40F00021C0000021C00023369BB0F4D6DF40F00021C0000021C00031FEFF60F000000000000000000000000
//EF09003E4EBB0FF3A6F40F6CE71B006CE71B00017007BB0F38A5F40F6CE71B006CE71B00023369BB0F4D6DF40F6CE71B006CE71B00031FEFF60F000000000000000000000000
//EF0900A500BC0FAEE4F50F6CE71B006CE71B000135ACBB0FF0D1F50F6CE71B006CE71B000242E6BB0F63D1F50F6CE71B006CE71B00031FEFF60F000000000000000000000000

//EF0900D057BB0FF3A6F40F6CE71B006CE71B0001570EBB0F35AEF40F6CE71B006CE71B0002E56FBB0F6377F40F6CE71B006CE71B00031FEFF60F000000000000000000000000

//        1.99618   E3A51B00
//EF09000673F60FF3A6F40FE3A51B00E3A51B0001EBE2F50F35AEF40FE3A51B00E3A51B0002A6A5F60F6377F40FE3A51B00E3A51B00031FEFF60F000000000000000000000000


//753862        EF09006C6DB80FB9F0F40F00021C0000021C00010478B80FBDC7F40F00021C0000021C0002C43BB80F20B1F40F00021C0000021C00031FEFF60F000000000000000000000000

//        EF09006C6DB80FB9F0F40F00021C0000021C00010478B80FBDC7F40F00021C0000021C0002C43BB80F20B1F40F00021C0000021C00031FEFF60F000000000000000000000000

//72C21C        EF09001BF2F10F22DAF50F6CE71B006CE71B00011B3DF20FF19CF50F6CE71B006CE71B0002E698F10F5B82F50F6CE71B006CE71B00031FEFF60F000000006CE71B006CE71B00
        return true;
    }
    return false;
}

QVariant model_current::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Сумма";
            case 1: return "Фаза А";
            case 2: return "Фаза B";
            case 3: return "Фаза C";
            case 4: return "gain А";
            case 5: return "gain B";
            case 6: return "gain C";
            default: break;
            }
        } else {
            switch (section) {
            case 0: return "U[B]";
            case 1: return "I[A]";
            case 2: return "P[W]";
            case 3: return "Q[var]";
            case 4: return "S[BA]";
            case 5: return "F[Hz]";
            case 6: return "In[A]";
            default: break;
            }
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags model_current::flags(const QModelIndex &index) const
{
    if (!is_calib) return QAbstractTableModel::flags(index);
    if (index.row() <= 1 && index.column()) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    if (index.row() <= 3 && index.column() > 3) {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
    return QAbstractTableModel::flags(index);
}

void model_current::set_curr(QVariantMap vm)
{
    emit layoutAboutToBeChanged();
    curr_data = vm;
//    log_1 << qPrintable(QJsonDocument::fromVariant(curr_data).toJson());
    emit layoutChanged();
    //    log_1 << qPrintable(QJsonDocument::fromVariant(curr_data).toJson());
}

void model_current::set_cal(QMap<uint32_t, ADE_cal> cals)
{
    emit layoutAboutToBeChanged();
    cal_data = cals;
    emit layoutChanged();
}

widget_current::widget_current(bool is_calib, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget_current)
    , is_calib(is_calib)
{
    ui->setupUi(this);
    hide();
    mc = new model_current(is_calib, 0x31, this);
    connect(mc, model_current::signal_write_data, this, widget_current::signal_write_data);
  //  ui->tableView->setModel(mc);

    ui->comboBox_ADE_Pulse0_energy_type->addItem("Активка", 0);
    ui->comboBox_ADE_Pulse0_energy_type->addItem("Реактивка", 1);
    ui->comboBox_ADE_Pulse0_energy_type->addItem("Активка В", 4);
    ui->comboBox_ADE_Pulse0_energy_type->addItem("Реактивка В", 5);
    ui->comboBox_ADE_Pulse0_energy_type->addItem("Часы", 0x81);
    ui->comboBox_ADE_Pulse1_energy_type->addItem("Активка", 0);
    ui->comboBox_ADE_Pulse1_energy_type->addItem("Реактивка", 1);
    ui->comboBox_ADE_Pulse1_energy_type->addItem("Активка В", 4);
    ui->comboBox_ADE_Pulse1_energy_type->addItem("Реактивка В", 5);
    ui->comboBox_ADE_Pulse1_energy_type->addItem("Часы", 0x81);
}

widget_current::~widget_current()
{
    delete ui;
}

void widget_current::on_pushButton_EF0A_clicked()
{
    emit signal_write_data(QByteArray::fromHex("EF0A07"));
}

void widget_current::slot_read_data(QByteArray data)
{
    ui->lineEdit_out->setText(data.toHex().toUpper());
    uint8_t buf_size = data.size();
    uint8_t * buf_start = (uint8_t *)data.data();
    uint8_t * buf = buf_start;
    if (buf_size < 1) {
//    if (buf_size < 1 + 2 + 4) {
//        vmap_packet.insert("error", "no header data");
        return;
    }
    QVariantMap vmap_packet;
    uint8_t header = *buf++;
    if (header == 0x31) {
        uint32_t timestamp = 0;
        QVariantMap vmap_data;
        while(buf - buf_start + 6 <= buf_size) {
            PARAM_IDENTIFIER pi;
            *((uint8_t*)&pi + 0) = *buf++;
            *((uint8_t*)&pi + 1) = *buf++;
            if (pi.timestamp_flag) {
                timestamp = (*buf++) << 24;
                timestamp+= (*buf++) << 16;
                timestamp+= (*buf++) << 8;
                timestamp+= (*buf++);
            }
            OBIS obis;
            obis.A = 1;
            obis.B = 0;
            obis.C = pi.obis_C;
            obis.D = pi.obis_D ? 8 : 7;
            obis.E = pi.obis_E;
            obis.F = 255;
            if (obis.D == 8 && obis.C > 8) obis.D =7;
            if (buf - buf_start + 4 > buf_size) break;
            uint32_t val;
            val = *buf++; val <<= 8;
            val+= *buf++; val <<= 8;
            val+= *buf++; val <<= 8;
            val+= *buf++;
            if (obis.D == 7 && ((obis.C % 20) == 2 || (obis.C % 20) == 4)) {
                obis.C -= 1;
                int32_t ival = *(int32_t*)&val;
                QByteArray arr((const char *)&obis, 6);
                vmap_data.insert(arr.toHex().toUpper(), ((double)(-ival))/1000);
                continue;
            }
            QByteArray arr((const char *)&obis, 6);
            if (obis.C == 81 && obis.D == 7 && obis.E == 0) {
//                log_1 << "angle";
                uint16_t a_ab = (val >> 16) & 0x7FFF;
                uint16_t a_bc = (val >> 0) & 0x7FFF;
                float a_abf = (float)a_ab;
                a_abf *= 14.1;
                float a_bcf = (float)a_bc;
                a_bcf *= 14.1;
                obis.E = 10;
                arr = QByteArray((const char *)&obis, 6);
                val = a_abf;
                vmap_data.insert(arr.toHex().toUpper(), ((double)val)/1000);
                obis.E = 21;
                arr = QByteArray((const char *)&obis, 6);
                val = a_bcf;
            }
            vmap_data.insert(arr.toHex().toUpper(), ((double)val)/1000);
        }

        vmap_packet.insert("timestamp", timestamp);
    //        log_1 << header << index_send << index_head << timestamp;
        if (vmap_data.isEmpty()) { // no electro 5 data
            return;
        }
        vmap_packet.insert("data", vmap_data);
        if (buf - buf_start != buf_size) {
//            log_1 << (buf - buf_start) << buf_size;
            vmap_packet.insert("error", "not null tail");
        }
    //    log_1 << data.toHex().toUpper();
        mc->set_curr(vmap_packet);
//        curr_data = vmap_packet;
//        emit signal_write_data(QByteArray::fromHex("EF01"));
        emit signal_write_data(QByteArray::fromHex("EF09"));

        if (vmap_data.isEmpty()) { // no electro 5 data
            return;
        }
        vmap_packet.insert("data", vmap_data);
        if (buf - buf_start != buf_size) {
            vmap_packet.insert("error", "not null tail");
        }
        mc->set_curr(vmap_packet);
//        emit signal_write_data(QByteArray::fromHex("EF01"));
        emit signal_write_data(QByteArray::fromHex("EF09"));
    } else if (header == 0x40) {
        uint16_t index_send;
        uint16_t index_head;
        index_send = *buf++;
        index_send <<= 4;
        index_head = *buf++;
        index_send += (index_head >> 4) & 0xF;
        index_head &= 0xF;
//        vmap_packet.insert("index_send", index_send);
//        vmap_packet.insert("index_head", index_head);
        uint32_t timestamp;
        timestamp = *buf++; timestamp <<= 8;
        timestamp+= *buf++; timestamp <<= 8;
        timestamp+= *buf++; timestamp <<= 8;
        timestamp+= *buf++;
    //        log_1 << "time" << QString::number(header, 16).toUpper() << modem_id
    //              << QString::number(timestamp, 16).toUpper() << timestamp
    //              << QDateTime::fromTime_t(timestamp).toString("yyyy.MM.dd hh:mm:ss");
        vmap_packet.insert("timestamp", timestamp);
    //        log_1 << header << index_send << index_head << timestamp;
        QVariantMap vmap_data;
        while (buf - buf_start + 6 <= buf_size) {
//            log_1 << (buf - buf_start) << buf_size;
            OBIS16 *o16 = (OBIS16 *)buf;
            OBIS32 *o32 = (OBIS32 *)buf;
            OBIS48 *o48 = (OBIS48 *)buf;
            OBIS obis;
            uint32_t val;
            if (o16->is_ext == 1) {
                obis.A = o16->obis_A;
                obis.B = 0;
                obis.C = o16->obis_C;
                obis.D = o16->obis_D;
                obis.E = o16->obis_E;
                obis.F = 255;
                buf += 2;
            } else
            if (o32->is_ext == 1) {
                obis.A = o32->obis_A;
                obis.B = o32->obis_B;
                obis.C = o32->obis_C;
                obis.D = o32->obis_D;
                obis.E = o32->obis_E;
                obis.F = 255;
                buf += 4;
            } else
            if (o48->is_ext == 0) {
                obis.A = o48->obis_A;
                obis.B = o48->obis_B;
                obis.C = o48->obis_C;
                obis.D = o48->obis_D;
                obis.E = o48->obis_E;
                obis.F = o48->obis_F;
                buf += 6;
            } else {
                vmap_packet.insert("error", "obis fail");
                break;
            }
            if (buf - buf_start + 4 > buf_size) break;
            QByteArray arr((const char *)&obis, 6);
            val = *buf++; val <<= 8;
            val+= *buf++; val <<= 8;
            val+= *buf++; val <<= 8;
            val+= *buf++;
            if (obis.D == 7) {
                int32_t ival = *(int32_t*)&val;
                vmap_data.insert(arr.toHex().toUpper(), ((double)ival)/1000);
            } else {
                vmap_data.insert(arr.toHex().toUpper(), ((double)val)/1000);
            }
        }
        if (vmap_data.isEmpty()) { // no electro 5 data
            return;
        }
        vmap_packet.insert("data", vmap_data);
        if (buf_size - (buf - buf_start) == 2) {
//            uint16_t *crc_packet = (uint16_t *)buf;
            buf += 2;
//            if (*crc_packet != DLMS_crc_buff(buf_start, buf_size - 2)) {
//                vmap_packet.clear();
//                vmap_packet.insert("error", "crc");
//                break;
//            }
        }
        if (buf - buf_start != buf_size) {
//            log_1 << (buf - buf_start) << buf_size;
            vmap_packet.insert("error", "not null tail");
        }
    //    log_1 << data.toHex().toUpper();
        mc->set_curr(vmap_packet);
//        curr_data = vmap_packet;
//        emit signal_write_data(QByteArray::fromHex("EF01"));
        emit signal_write_data(QByteArray::fromHex("EF09"));
    } else if (header == 0xEF) {
        uint8_t sub_header = *buf++;
//        log_1 << sub_header;
        switch (sub_header) {
        case 0x09: {
            uint8_t b_len = data.size() - 2;
            uint8_t * b = buf;
//            QVariantMap vmap_cal;
            QMap<uint32_t, ADE_cal> cals;
            while (b_len > (b - buf) && b_len - (b - buf) >= sizeof(ADE_cal)) {
                uint8_t phase = *b++;
                ADE_cal ade_cal;
                memmove(&ade_cal, b, sizeof(ADE_cal));
                b += sizeof(ADE_cal);
                cals.insert(phase, ade_cal);
            }
            mc->set_cal(cals);
//            emit signal_write_data(QByteArray::fromHex("EF01"));
            break;
        }
        case 0x17: {
            if (data.size() < 8) break;
            uint32_t Pulse0_energy_type = *buf++;
            uint32_t Pulse1_energy_type = *buf++;
            uint32_t Pulse0_freq  = *buf++;
            Pulse0_freq += (*buf++) << 8;
            uint32_t Pulse1_freq  = *buf++;
            Pulse1_freq += (*buf++) << 8;
            ui->comboBox_ADE_Pulse0_energy_type->setCurrentIndex(ui->comboBox_ADE_Pulse0_energy_type->findData(Pulse0_energy_type));
            ui->comboBox_ADE_Pulse1_energy_type->setCurrentIndex(ui->comboBox_ADE_Pulse1_energy_type->findData(Pulse1_energy_type));
            ui->spinBox_ADE_Pulse0_freq->setValue(Pulse0_freq);
            ui->spinBox_ADE_Pulse1_freq->setValue(Pulse1_freq);
            break;
        }
        case 0x41: {
            if (buf_size < 6) break;
            uint32_t delay_min = (*buf++) << 0;
            delay_min += (*buf++) << 8;
            ui->spinBox_display_min->setValue(delay_min);
            uint32_t delay_max = (*buf++) << 0;
            delay_max += (*buf++) << 8;
            ui->spinBox_display_max->setValue(delay_max);
//            1E00 2D00
            break;
        }
        case 0x42: {
            log_1 << data.size();
            if (data.size() < 5) break;
            uint32_t phase  = *buf++;
            uint32_t uval  = *buf++;
            uval += (*buf++) << 8;
            int16_t val = 0;
            if (uval <= 383) {
                val = uval;
            } else {
                val = - (uval & 0x1FF);
            }
            log_1 << val;
            phase &= 0xF;
            if (phase == 0) {
//                ui->spinBox_phase_calib_A->setValue(val);
            } else if (phase == 1) {
//                ui->spinBox_phase_calib_B->setValue(val);
            } else {
//                ui->spinBox_phase_calib_C->setValue(val);
            }
            break;
        }
        default: break;
        }
    } else if (header == 0xEE) {
        uint8_t sub_header = *buf++;
        uint8_t b;
        QString hw;
        b = *buf++;
        mc->dev_HW_id = b;
        hw  = QString("%1.%2.").arg((b >> 4) & 0xF).arg((b >> 0) & 0xF);
        b = *buf++;
        hw += QString("%1.%2" ).arg((b >> 4) & 0xF).arg((b >> 0) & 0xF);

        QString sw;
        b = *buf++;
        sw  = QString("%1.%2.").arg((b >> 4) & 0xF).arg((b >> 0) & 0xF);
        b = *buf++;
        sw += QString("%1.%2" ).arg((b >> 4) & 0xF).arg((b >> 0) & 0xF);

        QVariantMap vmap;
        vmap.insert("sw", sw);
        vmap.insert("hw", hw);

        uint32_t modem = 0;
        if (buf - buf_start + 4 <= data.size()) {
            modem = data.mid(buf - buf_start, 4).toHex().toInt(0,16);
        }
//        mc->dev_HW_id = buf[0];
        ui->label_info->setText("HW:"+hw+" SW:"+sw+" ID:"+QString::number(modem)+" ID:"+QString::number(modem, 16).toUpper());
    }
}

void widget_current::slot_connect(uint32_t server, uint32_t client, QByteArray pass)
{
   // emit signal_write_data(QByteArray::fromHex("EF06"));
}

void widget_current::on_pushButton_ADE_read_clicked()
{
    emit signal_write_data(QByteArray::fromHex("EF17"));
}

void widget_current::on_pushButton_ADE_write_clicked()
{
    QByteArray arr = QByteArray::fromHex("EF17000000000000000000000000000000000000000000000000");
    uint8_t * buf = (uint8_t *)arr.data();
    buf += 2;

    uint32_t Pulse0_energy_type = ui->comboBox_ADE_Pulse0_energy_type->currentData().toUInt();
    uint32_t Pulse1_energy_type = ui->comboBox_ADE_Pulse1_energy_type->currentData().toUInt();
    uint32_t Pulse0_freq = ui->spinBox_ADE_Pulse0_freq->value();
    uint32_t Pulse1_freq = ui->spinBox_ADE_Pulse1_freq->value();

    *buf++ = Pulse0_energy_type;
    *buf++ = Pulse1_energy_type;
    *buf++ = (Pulse0_freq >> 0) & 0xFF;
    *buf++ = (Pulse0_freq >> 8) & 0xFF;
    *buf++ = (Pulse1_freq >> 0) & 0xFF;
    *buf++ = (Pulse1_freq >> 8) & 0xFF;

    arr = arr.mid(0, buf - (uint8_t *)arr.data());

    emit signal_write_data(arr);
}

//void widget_current::on_pushButton_phase_calib_A_read_clicked()
//{
//    emit signal_write_data(QByteArray::fromHex("EF42000000"));
//}

//void widget_current::on_pushButton_phase_calib_A_write_clicked()
//{
//    if (!is_calib) return;
//    QByteArray arr = QByteArray::fromHex("EF42800000000000000000000000000000000000000000000000");
//    uint8_t * buf = (uint8_t *)arr.data();
//    buf += 3;
//    int16_t val = 0;//ui->spinBox_phase_calib_A->value();
//    uint16_t uval = 0;
//    if (val >= 0) {
//        if (val <= 383) uval = val;
//    } else {
//        if (val >= -383) uval = -val + 0x200;
//    }
//    *buf++ = (uval >> 0) & 0xFF;
//    *buf++ = (uval >> 8) & 0xFF;
//    arr = arr.mid(0, buf - (uint8_t *)arr.data());
//    emit signal_write_data(arr);
//}

//void widget_current::on_pushButton_phase_calib_B_read_clicked()
//{
//    emit signal_write_data(QByteArray::fromHex("EF42010000"));
//}

//void widget_current::on_pushButton_phase_calib_B_write_clicked()
//{
//    if (!is_calib) return;
//    QByteArray arr = QByteArray::fromHex("EF42810000000000000000000000000000000000000000000000");
//    uint8_t * buf = (uint8_t *)arr.data();
//    buf += 3;
//    int16_t val = 0;//ui->spinBox_phase_calib_B->value();
//    uint16_t uval = 0;
//    if (val >= 0) {
//        if (val <= 383) uval = val;
//    } else {
//        if (val >= -383) uval = -val + 0x200;
//    }
//    *buf++ = (uval >> 0) & 0xFF;
//    *buf++ = (uval >> 8) & 0xFF;
//    arr = arr.mid(0, buf - (uint8_t *)arr.data());
//    emit signal_write_data(arr);
//}

//void widget_current::on_pushButton_phase_calib_C_read_clicked()
//{
//    emit signal_write_data(QByteArray::fromHex("EF42020000"));
//}

//void widget_current::on_pushButton_phase_calib_C_write_clicked()
//{
//    if (!is_calib) return;
//    QByteArray arr = QByteArray::fromHex("EF42820000000000000000000000000000000000000000000000");
//    uint8_t * buf = (uint8_t *)arr.data();
//    buf += 3;
//    int16_t val = 0;//ui->spinBox_phase_calib_C->value();
//    uint16_t uval = 0;
//    if (val >= 0) {
//        if (val <= 383) uval = val;
//    } else {
//        if (val >= -383) uval = -val + 0x200;
//    }
//    *buf++ = (uval >> 0) & 0xFF;
//    *buf++ = (uval >> 8) & 0xFF;
//    arr = arr.mid(0, buf - (uint8_t *)arr.data());
//    emit signal_write_data(arr);
//}

void widget_current::on_pushButton_display_read_clicked()
{
    QByteArray arr = QByteArray::fromHex("EF41");
    emit signal_write_data(arr);
}

void widget_current::on_pushButton_display_write_clicked()
{
    uint8_t min = ui->spinBox_display_min->value();
    uint8_t max = ui->spinBox_display_max->value();
    QByteArray arr = QByteArray::fromHex("EF4100000000");
    arr[2] = min & 0xFF;
    arr[3] = (min >> 8) & 0xFF;
    arr[4] = max & 0xFF;
    arr[5] = (max >> 8) & 0xFF;
    emit signal_write_data(arr);
}

void widget_current::on_pushButton_set_Fast_DL_clicked()
{
    QByteArray arr = QByteArray::fromHex("EF01");
    emit signal_write_data(arr);
}

void widget_current::on_pushButton_set_Time_clicked()
{
    QByteArray arr = QByteArray::fromHex("F500000000000000");
    QDateTime dt = QDateTime::currentDateTime();
    dt.setTimeSpec(Qt::UTC);
    uint32_t ts = dt.toTime_t();
    arr[1] = (ts >> 24) & 0xFF;
    arr[2] = (ts >> 16) & 0xFF;
    arr[3] = (ts >> 8) & 0xFF;
    arr[4] = (ts >> 0) & 0xFF;
    log_1 << "set ts" << ts;
    emit signal_write_data(arr);
}

void widget_current::on_pushButton_rele_on_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED4060030A031101");
    emit signal_write_data(arr);
}

void widget_current::on_pushButton_rele_off_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED4060030A031102");
    emit signal_write_data(arr);
}

void widget_current::on_lineEdit_in_returnPressed()
{
    QByteArray arr = QByteArray::fromHex(ui->lineEdit_in->text().toLocal8Bit());
    emit signal_write_data(arr);
}

void widget_current::on_pushButton_clicked()
{
    for (QMap<uint32_t, ADE_cal>::iterator iter = mc->cal_data.begin(); iter != mc->cal_data.end(); ++iter) {
        if (iter.key() >= 0x10) continue;
        iter->i = mc->show_cal((mc->cal_show(iter->i).toFloat() * 1.99618));
        iter->w = 0x001BA5E3;
        iter->var = iter->w;
    }

    QByteArray arr_out((int)256, 0);
    uint8_t *buf = (uint8_t *)arr_out.data();
    *buf++ = 0xEF;
    *buf++ = 0x09;
    for (QMap<uint32_t, ADE_cal>::iterator cal_iter = mc->cal_data.begin(); cal_iter != mc->cal_data.end(); ++cal_iter) {
        *buf++ = cal_iter.key();
        ADE_cal ade_cal = cal_iter.value();
        memmove(buf, &ade_cal, sizeof(ADE_cal));
        buf += sizeof(ADE_cal);
    }
    arr_out = arr_out.mid(0, buf - (uint8_t *)arr_out.data());
    emit signal_write_data(arr_out);

//    1.99618   E3A51B00
}

void widget_current::on_lineEdit_out_returnPressed()
{
    QByteArray arr = QByteArray::fromHex(ui->lineEdit_out->text().toLocal8Bit());
    slot_read_data(arr);
}
