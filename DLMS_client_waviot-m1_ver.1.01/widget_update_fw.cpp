#include "widget_update_fw.h"
#include "ui_widget_update_fw.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "widget_current.h"
#include "widget_pdu_worker.h"
#include "interface.h"
#include "Logger/Logger.h"
#include <DLMS_CRC.h>

#ifndef TS_BUILD
#define TS_BUILD (QLocale(QLocale::C).toDateTime(__TIMESTAMP__, "ddd MMM d hh:mm:ss yyyy").toTime_t())
#endif

uint16_t CRC_calc(uint8_t *start, uint8_t *end);

#define UPGRADE_BLOCK_SIZE       (80)

widget_update_fw::widget_update_fw(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget_update_fw)
{
    ui->setupUi(this);
    is_connected = false;
    use_auto_update = 0;
    ui->progressBar->setValue(0);
    timer_fw = new QTimer(this);
    connect(timer_fw, SIGNAL(timeout()), this, SLOT(slot_timer_fw()));

    ui->pushButton_auto_update->hide();
    ui->pushButton_file_fw_update->hide();
    add_text_log("Версия ПО: "+QDateTime::fromTime_t(TS_BUILD).toString("yyyy.MM.dd hh:mm:ss"));
    search_fw(qApp->applicationDirPath());
}

widget_update_fw::~widget_update_fw()
{
    delete ui;
}

void widget_update_fw::add_text_log(QString str_log)
{
    uint32_t ts = QDateTime::currentDateTime().toTime_t();
    QString str = //QString("%1").arg(modem, 7, 10, QChar('0')).toUpper()+" "+
            QDateTime::fromTime_t(ts).toString("hh:mm:ss")+" "+str_log;
    ui->textBrowser_log->append("<div>"+str+"</div>");
    log_1 << str;
}

void widget_update_fw::search_fw(QString path)
{
    QDir dir(path);
    QStringList slist_dirs = dir.entryList(QStringList() << "x.x.*");
    if (slist_dirs.isEmpty()) {
        add_text_log("нет доступных прошивок");
        return;
    }
    dir.setPath(path + "/" + slist_dirs.takeLast());
    QStringList slist_fw = dir.entryList(QStringList() << "ph[0-9][0-9][0-9][0-9]_*_*.bin");
    if (slist_fw.isEmpty()) {
        add_text_log("нет доступных прошивок");
        return;
    }
    foreach (QString fw_name, slist_fw) {
        QRegExp re("ph(\\d{4,4})_\\w+_\\w+.bin");
        if (re.indexIn(fw_name) > -1) {
            QString fw_ver = re.cap(1);
            fw_map.insert(fw_ver, dir.path() + "/" + fw_name);
            fw_ver.insert(3, ".");
            fw_ver.insert(2, ".");
            fw_ver.insert(1, ".");
            add_text_log("найдена прошивка - " + fw_ver);
        }
    }
    if (fw_map.isEmpty()) {
        add_text_log("нет доступных прошивок");
        return;
    }
}

bool widget_update_fw::send_block()
{
    QByteArray arr = wbin.mid(block_index * UPGRADE_BLOCK_SIZE, UPGRADE_BLOCK_SIZE);
    if (arr.isEmpty()) {
        return false;
    }
    uint16_t crc = DLMS_crc_buff((uint8_t *)arr.data(), arr.size());
    QByteArray arr_out;
    arr_out.append(0xEF);
    arr_out.append(0x31);
//    arr_out.append(0xFF);
    arr_out.append(qrand()%255);
    arr_out.append(block_index & 0xFF);
    arr_out.append(block_index >> 8);
    arr_out.append(crc & 0xFF);
    arr_out.append(crc >> 8);
    arr_out.append(arr);
    emit signal_write_data(arr_out);
    return true;
}

void widget_update_fw::file_fw_update_read_data(QByteArray data)
{
    is_connected = true;
    if (wbin.size() < UPGRADE_BLOCK_SIZE) return;
    if (data.size() < 2) return;
    uint8_t * buf = (uint8_t *)data.data();
    if (*buf++ != 0xEF) return;
    uint8_t sub_header = *buf++;
    log_1 << data.toHex().toUpper();
    switch (sub_header) {
    case 0x30: {
        block_index = 0;
        send_block();
        ui->progressBar->setValue(1);
        timer_fw->start(1000);
        break;
    }
    case 0x31: {
        uint8_t res31 = *buf++;
        if (!res31) {
            block_index++;
        }
        if (!send_block()) {
            emit signal_write_data(QByteArray::fromHex("EF32"));
            ui->progressBar->setValue(99);
            break;
        }
        ui->progressBar->setValue(block_index * 98 / (wbin.size()/UPGRADE_BLOCK_SIZE + 1) + 1);
        timer_fw->start(1000);
        break;
    }
    case 0x32: {
        uint8_t res32 = *buf++;
        ui->progressBar->setValue(100);
        timer_fw->stop();
        switch (res32) {
        case 0x00: {
            emit signal_write_data(QByteArray::fromHex("EF82A0F5"));
            add_text_log("Применение прошивки, перезапуск устройства");
            break;
        }
        case 0x01: {
            add_text_log("Ошибка чтения заголовка обновления");
            break;
        }
        case 0x02: {
            add_text_log("Ошибка CRC заголовка. Повторите обновление");
            break;
        }
        case 0x03: {
            add_text_log("Уже обновлено на текущую версию");
            break;
        }
        case 0x04: {
            add_text_log("Ошибка CRC заголовка обновления. Повторите обновление");
            break;
        }
        default: {
            add_text_log("Ошибка обновления");
            break;
        }
        }
        break;
    }
    default: break;
    }
}

void widget_update_fw::on_pushButton_file_fw_update_clicked()
{
    QString f_name = QFileDialog::getOpenFileName(this, "", qApp->applicationDirPath(), "fw (*.bin)");
    if (f_name.isEmpty()) return;
    slot_start_fw(f_name);
}

void widget_update_fw::slot_read_data(QByteArray data)
{
    if (data.isEmpty()) return;
    uint8_t * buf = (uint8_t *)data.data();
    uint8_t * buf_start = buf;
    if (data.size() >= 10 && buf[0] == 0xEE && buf[1] == 0x00) {
        ui->progressBar->setValue(0);
        *buf++;
        *buf++;
        dev_HW_id = *buf++; *buf++;
        *buf++; sw = *buf++;
        uint32_t modem = data.mid(buf - buf_start, 4).toHex().toInt(0,16);
        QString fw_ver = QString::number(dev_HW_id, 16) + QString::number(sw, 16);
        fw_ver = fw_ver.toUpper();
        QByteArray CRC_ARR;
        {
            QByteArray arr_fw;
            QFile file(fw_map.value(fw_ver));
            if (file.open(QIODevice::ReadOnly)) {
                arr_fw = file.readAll();
                file.close();
            }
            CRC_ARR = QByteArray::number(CRC_calc((uint8_t *)arr_fw.data(), (uint8_t *)arr_fw.data() + arr_fw.size()), 16).toUpper();
        }
        fw_ver.insert(3, ".");
        fw_ver.insert(2, ".");
        fw_ver.insert(1, ".");
        add_text_log("счетчик найден - ID:" + QString::number(modem, 10).toUpper()+"  VER:" + fw_ver);

        bool need_update = true;
        if (data.size() == 12) {
            QByteArray CRC_VER = data.mid(10).toHex().toUpper();
            if (!CRC_ARR.isEmpty()) {
                if (CRC_ARR == CRC_VER) {
                    add_text_log("совпадение контрольной суммы");
                    add_text_log("обновление не требуется");
                    need_update = false;
                    ui->progressBar->setValue(100);
                    emit signal_disconnect();
                }
            }
        }
        if (need_update) {
            for (auto iter = fw_map.begin(); iter != fw_map.end(); ++iter) {
                QString str = iter.key();
                log_1 << (str.toUInt(0, 16) >> 8) << dev_HW_id;
                log_1 << (str.toUInt(0, 16) & 0xFF) << sw;
                if ((str.toUInt(0, 16) >> 8) == dev_HW_id) {
                    if ((str.toUInt(0, 16) & 0xFF) >= sw) {
                        log_1 << iter.value();
                        add_text_log("обновление прошивкой " + iter.value());
                        slot_start_fw(iter.value());
                    }
                }
            }
        }
    }
    file_fw_update_read_data(data);
    return;

//    if (0)
//    if (!use_auto_update) {
//        file_fw_update_read_data(data);
//        return;
//    }
//    if (cur_packets_list.size() > curr_index) {
//        if (data.left(5) == cur_packets_list.at(curr_index).exec_key.left(5)) {
//            curr_index++;
//            slot_timer_fw();
//            return;
//        }
//    }
//    uint8_t buf_size = data.size();
//    if (!buf_size) return;
//    uint8_t * buf_start = (uint8_t *)data.data();
//    uint8_t * buf = buf_start;
//    switch (*buf++) {
//    case 0x40: {
//        if (buf_size < 1 + 2 + 4) {
//            break;
//        }
//        bool is_iters_packet = false;
//        Parser_ul_data ul_data;
//        ul_data.index = *buf++;
//        ul_data.index <<= 4;
//        ul_data.index_ext = *buf++;
//        ul_data.index += (ul_data.index_ext >> 4) & 0xF;
//        ul_data.index_ext &= 0xF;
//        uint32_t timestamp;
//        timestamp = *buf++; timestamp <<= 8;
//        timestamp+= *buf++; timestamp <<= 8;
//        timestamp+= *buf++; timestamp <<= 8;
//        timestamp+= *buf++;
//        while (buf - buf_start + 6 <= buf_size) {
//            OBIS obis;
//            buf += ElectroGet_OBIS(buf, &obis);
//            if (obis.C == 4 && obis.D == 8 && obis.E == 4) {
//                is_iters_packet = true;
//            }
//            uint32_t val;
//            if (buf - buf_start + 4 > buf_size) break;
//            val = *buf++; val <<= 8;
//            val+= *buf++; val <<= 8;
//            val+= *buf++; val <<= 8;
//            val+= *buf++;
//            if (obis.D == 7) {
//                int32_t ival = *(int32_t*)&val;
//                ul_data.data.insert(obis, ((double)ival)/1000);
//            } else if (obis.D == 3) {
//                ul_data.data.insert(obis, val);
//            } else {
//                ul_data.data.insert(obis, ((double)val)/1000);
//            }
//        }
//        if (is_iters_packet) {
//            for (QMap<OBIS_cpp, QVariant>::iterator iter = ul_data.data.begin(); iter != ul_data.data.end(); ++iter) {
//                float val = iter.value().toFloat();
//                OBIS_cpp obis = iter.key();
//                if (!val) continue;
//                QByteArray arr;
//                uint8_t tariff = obis.obis.E - 1;
//                uint8_t phase = 0;
//                uint8_t mdt = obis.obis.C;
//                float value = val / 4 * 1000;
//                arr = QByteArray::fromHex("EF1D00000000000000");
//                arr[2] = tariff;
//                arr[3] = phase;
//                arr[4] = mdt;
//                memmove(arr.data()+5, &value, 4);
//                SEND_PACKET_model spmod;
//                spmod.payload = arr;
//                spmod.exec_key = arr.left(5);
//                cur_packets_list << spmod;
//            }
//            if (!cur_packets_list.isEmpty()) {
//                curr_index = 0;
//                use_auto_update = 3;
//                timer_fw->start(5000);
//                slot_timer_fw();
//            }
//        }
//        break;
//    }
//    case 0xEF: {
//        uint8_t sub_header = *buf++;
//        if (sub_header == 0x09) {
//            if (use_auto_update != 3) break;
//            uint8_t b_len = data.size() - 2;
//            uint8_t * b = buf;
//            QMap<uint32_t, ADE_cal> cals;
//            while (b_len > (b - buf) && b_len - (b - buf) >= sizeof(ADE_cal)) {
//                uint8_t phase = *b++;
//                ADE_cal ade_cal;
//                memmove(&ade_cal, b, sizeof(ADE_cal));
//                b += sizeof(ADE_cal);
//                cals.insert(phase, ade_cal);
//            }

//            if (!dev_HW_id) break;
//            log_1 << QString::number(dev_HW_id, 16).toUpper();
//            model_current mc(true, dev_HW_id);
//            mc.set_cal(cals);

//            for (QMap<uint32_t, ADE_cal>::iterator iter = mc.cal_data.begin(); iter != mc.cal_data.end(); ++iter) {
//                log_1 << iter.key();
//                if (iter.key() >= 0x03) continue;
//                float ii = mc.cal_show(iter->i).toFloat();
//                log_1 << ii;
//                if (ii > 0.6) {
//                    use_auto_update = 0;
//                    ui->progressBar->setValue(ui->progressBar->maximum());
//                    log_1 << "уже обновлено";
//                    return;
//                }
//                iter->i = mc.show_cal((ii * 1.99618));
//                iter->w = 0x001BA5E3;
//                iter->var = iter->w;
//            }

//            QByteArray arr_out((int)256, 0);
//            uint8_t *buf = (uint8_t *)arr_out.data();
//            *buf++ = 0xEF;
//            *buf++ = 0x09;
//            for (QMap<uint32_t, ADE_cal>::iterator cal_iter = mc.cal_data.begin(); cal_iter != mc.cal_data.end(); ++cal_iter) {
//                *buf++ = cal_iter.key();
//                ADE_cal ade_cal = cal_iter.value();
//                memmove(buf, &ade_cal, sizeof(ADE_cal));
//                buf += sizeof(ADE_cal);
//            }
//            arr_out = arr_out.mid(0, buf - (uint8_t *)arr_out.data());
//            timer_fw->start(2000);
//            emit signal_write_data(arr_out); // отправка пакета
//            emit signal_write_data(QByteArray::fromHex("EF0308")); // отправка пакета
//        }
//        break;
//    }
//    case 0xEE: {
////        log_1 << QString::number(modem_id,16).toUpper() << "unknow header" << QString::number(header, 16).toUpper() << payload.toHex().toUpper();
//        if (buf_size < 6) break;
//        uint8_t sub_header = *buf++;
//        switch (sub_header) {
//        case 0x00: { // version
//            timer_fw->stop();
//            if (!use_auto_update) {
//                ui->progressBar->setValue(0);
//                use_auto_update = 1;
//                cur_packets_list.clear();
//            }
//            if (!(use_auto_update == 1 || use_auto_update == 2)) break;
////            uint8_t dev_HW_id;
////            uint8_t sw;
//            dev_HW_id = *buf++; *buf++;
//            *buf++; sw = *buf++;

//            log_1 << QString::number(dev_HW_id, 16).toUpper() << QString::number(sw, 16).toUpper();
//            QString oldFile_filename;
//            QString newFile_filename;
////            if (dev_HW_id == 0x11 && sw < 0x43) {
////                log_1;
////                newFile_filename = "x.x.4.3/ph1143_c400a1fd_4f2e7b72.bin";
////            }
//            if (dev_HW_id == 0x11 && sw == 0x41) {
//                oldFile_filename = "x.x.4.1/ph1141_72fdd9c0_657c424a.bin";
//                newFile_filename = "x.x.4.2/ph1142_72fdd9c0_657c424a.bin";
//            }
//            if (dev_HW_id == 0x19 && sw == 0x41) {
//                oldFile_filename = "x.x.4.1/ph1941_72fdd9c0_dcab17c7.bin";
//                newFile_filename = "x.x.4.2/ph1942_72fdd9c0_dcab17c7.bin";
//            }
//            if (dev_HW_id == 0x31 && sw == 0x41) {
//                oldFile_filename = "x.x.4.1/ph3141_72fdd9c0_dcab17c7.bin";
//                newFile_filename = "x.x.4.2/ph3142_a66f6274_dcab17c7_fix.bin";
//            }
//            if (dev_HW_id == 0x39 && sw == 0x41) {
//                oldFile_filename = "x.x.4.1/ph3941_72fdd9c0_dcab17c7.bin";
//                newFile_filename = "x.x.4.2/ph3942_a66f6274_dcab17c7_fix.bin";
//            }
////            if (dev_HW_id == 0x31 && sw == 0x41) {
////                oldFile_filename = "x.x.4.1/ph3141_72fdd9c0_dcab17c7_kz.bin";
////                newFile_filename = "x.x.4.2/ph3142_a66f6274_dcab17c7_kz_fix.bin";
////            }
////            if (dev_HW_id == 0x39 && sw == 0x41) {
////                oldFile_filename = "x.x.4.1/ph3941_72fdd9c0_dcab17c7_kz.bin";
////                newFile_filename = "x.x.4.2/ph3942_a66f6274_dcab17c7_kz_fix.bin";
////            }
//            if (dev_HW_id == 0x31 && sw == 0x40) {
//                oldFile_filename = "x.x.4.0/ph3140_50dc72e0.bin";
//                newFile_filename = "x.x.3.F/ph313F_546c9af5.bin";
//            }
//            if (dev_HW_id == 0x39 && sw == 0x40) {
//                oldFile_filename = "x.x.4.0/ph3940_50dc72e0.bin";
//                newFile_filename = "x.x.3.F/ph393F_546c9af5.bin";
//            }
//            QByteArray new_ba;
//            QByteArray old_ba;
//            if (!newFile_filename.isEmpty()) {
//                QFile newFile(newFile_filename);
//                if (newFile.open(QIODevice::ReadOnly)) {
//                    new_ba = newFile.readAll();
//                    newFile.close();
//                }
//            }
//            if (!oldFile_filename.isEmpty()) {
//                QFile oldFile(oldFile_filename);
//                if (oldFile.open(QIODevice::ReadOnly)) {
//                    old_ba = oldFile.readAll();
//                    oldFile.close();
//                }
//            }
//            if (!new_ba.isEmpty() && !old_ba.isEmpty()) {
//                curr_index = 0;
//                cur_packets_list = widget_update_fw::make_diff_flash_session(new_ba, old_ba);
//                log_1 << cur_packets_list.size();
//                ui->progressBar->setValue(1);
//                ui->progressBar->setMaximum(cur_packets_list.size() * 2);
//                timer_fw->start(5000);
//                slot_timer_fw();
//                break;
//            } else if (!new_ba.isEmpty()) {
//                curr_index = 0;
//                cur_packets_list = widget_update_fw::make_flash_session(new_ba);
//                log_1 << cur_packets_list.size();
//                ui->progressBar->setValue(1);
//                ui->progressBar->setMaximum(cur_packets_list.size() * 2);
//                timer_fw->start(5000);
//                slot_timer_fw();
//                break;
//            }
//            if ((dev_HW_id == 0x31 && sw == 0x42) ||
//                (dev_HW_id == 0x39 && sw == 0x42) ||
//                (dev_HW_id == 0x31 && sw == 0x3F) ||
//                (dev_HW_id == 0x39 && sw == 0x3F)) {
//                emit signal_write_data(QByteArray::fromHex("EF09"));
//                ui->progressBar->setValue(ui->progressBar->maximum() / 6 * 5);
//                use_auto_update = 3;
//                timer_fw->start(2000);
//                break;
//            }
////            if (sw == 0x43) {
////                emit signal_write_data(QByteArray::fromHex("EF0308")); // отправка пакета

////            }
//            break;
//        }
//        case 0x01: { // serial
//            break;
//        }
//        default: {
//        }
//        }
//        break;
//    }
//    default: break;
//    }
}

void widget_update_fw::slot_disconnect()
{
    log_1 << "stop";
    timer_fw->stop();
    ui->progressBar->setValue(0);
    is_connected = false;
}

void widget_update_fw::slot_start_fw(QString fileName)
{
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray arr = file.readAll();
    file.close();
    ui->progressBar->setValue(0);
    wbin = widget_PDU_worker::bin_to_wbin(arr);
    log_1 << wbin.size();
    block_index = 0;
    emit signal_write_data(QByteArray::fromHex("EF30"));
    timer_fw->start(10000);
}

void widget_update_fw::slot_timer_fw()
{
    switch (use_auto_update) {
    case 0: {
        if (is_connected) {
            QByteArray arr = wbin.mid(block_index * UPGRADE_BLOCK_SIZE, UPGRADE_BLOCK_SIZE);
            if (arr.isEmpty()) {
                timer_fw->stop();
                return;
            }
            send_block();
        }
        break;
    }
    case 1: {
        if (cur_packets_list.size() > curr_index) {
            timer_fw->stop();
            timer_fw->start(5000);
            ui->progressBar->setValue(curr_index + 1);
            SEND_PACKET_model spm = cur_packets_list.at(curr_index);
//            log_1 << "noack" << spm.noack << "system" << spm.system << spm.packet_id << "/" << cur_packets_list.size() << (float)spm.packet_id / (float)cur_packets_list.size() * 100 << "%" << spm.exec_key.toHex().toUpper();
            log_1 << spm.packet_id << "/" << cur_packets_list.size() << (float)spm.packet_id / (float)cur_packets_list.size() * 100 << "%" << spm.exec_key.toHex().toUpper();
            emit signal_write_data(spm.payload);
            if (spm.exec_key.toHex() == "30") {
                curr_index++;
                timer_fw->start(10);
            }
            return;
        } else {

            timer_fw->stop();
            log_1 << "end";
            cur_packets_list.clear();
            curr_index = 0;
            ui->progressBar->setValue(100);
            timer_fw->stop();
            log_1 << "end";


//            timer_fw->stop();
//            log_1 << "end";
//            cur_packets_list.clear();
//            curr_index = 0;
//            ui->progressBar->setValue(ui->progressBar->maximum() / 6 * 4);
//            emit signal_write_data(QByteArray::fromHex("EF82A0F5"));
//            timer_fw->start(3000);
//            use_auto_update = 2;
        }
        break;
    }
    case 2: {
        emit signal_write_data(QByteArray::fromHex("EF06"));
        break;
    }
    case 3: {
        if (cur_packets_list.size() > curr_index) {
            timer_fw->stop();
            timer_fw->start(5000);
            ui->progressBar->setValue(curr_index + 1);
            SEND_PACKET_model spm = cur_packets_list.at(curr_index);
            log_1 << "noack" << spm.noack << "system" << spm.system << spm.packet_id << "/" << cur_packets_list.size() << (float)spm.packet_id / (float)cur_packets_list.size() * 100 << "%" << spm.exec_key.toHex().toUpper();
            emit signal_write_data(spm.payload);
            if (spm.exec_key.toHex() == "30") {
                curr_index++;
                timer_fw->start(10);
            }
            return;
        } else {
            timer_fw->stop();
            log_1 << "end";
            cur_packets_list.clear();
            curr_index = 0;
            ui->progressBar->setValue(100);
            timer_fw->stop();
            log_1 << "end";
        }
        break;
    }
    default: break;
    }
}

struct rfl_binary_part
{
    quint32 address;
    QByteArray data;
};

bool peek_to_next_diff(const QByteArray &new_ba, const QByteArray &old_ba, quint32 &pos)
{
    while((pos < new_ba.size()) && (pos < old_ba.size()))
    {
        if(new_ba[pos] != old_ba[pos]) break;
        pos++;
    }
    if((pos >= new_ba.size()) || (pos >= old_ba.size())) return false;

    return true;
}

#define RFL_MIN_HOLE_LEN 32
QByteArray peek_to_end_of_block(const QByteArray &new_ba, const QByteArray &old_ba, quint32 &pos)
{
    quint32 hole = 0;
    quint32 start_pos = pos;
    while(pos < new_ba.size())
    {
        if((old_ba.size() >= pos) && (new_ba[pos] == old_ba[pos]))
        {
            if(++hole >= RFL_MIN_HOLE_LEN)
            {
                pos -= RFL_MIN_HOLE_LEN;
                pos++;
                return new_ba.mid(start_pos, pos - start_pos);
            }
        }
        else
        {
            hole = 0;
        }
        pos++;
    }

    return new_ba.right(pos - start_pos);
}

#define LINE_SIZE   128

#define RFL_FULL_ERASE_CMD                      (1<<5)
#define RFL_WRITE_HEADER_CMD                    (2<<5)
#define RFL_WRITE_CMD                           (3<<5)
#define RFL_READ_CURRENT_FIRMWARE_CRC_CMD       (4<<5)
#define RFL_CHECK_IF_CRC_OK_CMD                 (5<<5)
#define RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD      (6<<5)
#define RFL_READ_EXT_FLASH_CRC                  (7<<5)

#define RFL_ERR_NO_ERR  0
#define RFL_ERR_INDEX_MISSED  0x80

QList<SEND_PACKET_model> widget_update_fw::make_diff_flash_session(QByteArray new_ba, QByteArray old_ba, const QList<quint32> &modems, quint16 ver, quint16 subver, quint32 offset)
{
    QList<SEND_PACKET_model> packets_list;

    auto insertPacket = [&] (SEND_PACKET_model spm) -> void {
        packets_list << spm;
    };
//    QFile newFile(new_binary_filename);
//    if(!newFile.open(QIODevice::ReadOnly)) return -1;
//    QByteArray new_ba = newFile.readAll();
//    newFile.close();
//    QFile oldFile(old_binary_filename);
//    if(!oldFile.open(QIODevice::ReadOnly)) return -1;
//    QByteArray old_ba = oldFile.readAll();
//    oldFile.close();

    QList<rfl_binary_part> parts;

    quint32 pos = 0;

    while(pos < new_ba.size())
    {
        rfl_binary_part part;
        if(!peek_to_next_diff(new_ba, old_ba, pos)) break;;
        part.address = pos;
        part.data = peek_to_end_of_block(new_ba, old_ba, pos);
        parts.append(part);
    }


    quint16 index = 1;
//    transaction();

    //prepare header
    QByteArray arr_header((int)(sizeof(soft_update)), 0);
    soft_update * su = (soft_update *)arr_header.data();
    su->ver = ver;
    su->ver_ext = subver;
    su->start_add = offset;
    su->end_add = su->start_add + new_ba.size();
    su->crc = CRC_calc((uint8_t *)new_ba.data(), (uint8_t *)(&(new_ba.data()[new_ba.size()])));
    su->reserved[0] = 0;
    su->reserved[1] = 0;
    su->crc_of_this_struct = CRC_calc((uint8_t *)su, (uint8_t *)(&su->crc_of_this_struct));



    quint16 old_crc = CRC_calc((uint8_t *)old_ba.data(), (uint8_t *)(&(old_ba.data()[old_ba.size()])));

    //Reset index
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD5;
        pkt.exec_key[0] = 0xD5;
        pkt.exec_key[1] = 0;
        pkt.packet_id = 0;
        insertPacket(pkt);
    }

    //check current firmware CRC
    for(const auto modem:modems)
    {

        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
        pkt.payload[4] = (su->start_add>>16)&0xff;
        pkt.payload[5] = (su->start_add>>8)&0xff;
        pkt.payload[6] = (su->start_add)&0xff;
        pkt.payload[7] = (su->end_add>>16)&0xff;
        pkt.payload[8] = (su->end_add>>8)&0xff;
        pkt.payload[9] = (su->end_add)&0xff;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
        pkt.exec_key[2] = (((quint32)old_crc)>>8)&0xff;
        pkt.exec_key[3] = (((quint32)old_crc))&0xff;
        pkt.packet_id = index;
        insertPacket(pkt);


    }
    index++;

    //Full erase
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    index++;

    //Write header
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_WRITE_HEADER_CMD;
        pkt.payload.append(arr_header);
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_WRITE_HEADER_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);

    }
    index++;

    for(const auto & part:parts)
    {
        quint32 address = part.address;
        //Write all lines
        for(uint i = 0; i < part.data.size()/LINE_SIZE; i++)
        {
            QByteArray line;
            //address = i*LINE_SIZE;
            line[0] = 0xD4;
            line[1] = (index>>8)&0xff;
            line[2] = index&0xff;
            line[3] = RFL_WRITE_CMD  + ((address>>16)&0x1f);
            line[4] = (address>>8)&0xff;
            line[5] = address&0xff;
            line.append(part.data.mid(i*LINE_SIZE, LINE_SIZE));
            for(const auto modem:modems)
            {
                SEND_PACKET_model pkt;
                pkt.modem_id = modem;
                pkt.payload = line;
                insertPacket(pkt);
                pkt.packet_id = index;
            }
            address += LINE_SIZE;
            index++;
        }

        //Write tail
        if(part.data.size()%LINE_SIZE)
        {
            QByteArray line;
            line[0] = 0xD4;
            line[1] = (index>>8)&0xff;
            line[2] = index&0xff;
            //address = part.data.size()/LINE_SIZE*LINE_SIZE;
            line[3] = RFL_WRITE_CMD  + ((address>>16)&0x0f);
            line[4] = (address>>8)&0xff;
            line[5] = address&0xff;
            line.append(part.data.mid(address - part.address, part.data.size()%LINE_SIZE));
            for(const auto modem:modems)
            {
                SEND_PACKET_model pkt;
                pkt.modem_id = modem;
                pkt.payload = line;
                pkt.packet_id = index;
                insertPacket(pkt);
            }
            index++;
        }
    }

    //Write last one byte
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        quint32 address = new_ba.size() - 1;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_WRITE_CMD  + ((address>>16)&0x0f);
        pkt.payload[4] = (address>>8)&0xff;
        pkt.payload[5] = address&0xff;
        pkt.payload[6] = 0xff;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
     index++;

    //Check CRC and reboot
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_CHECK_IF_CRC_OK_CMD;//RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_CHECK_IF_CRC_OK_CMD;//RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    return packets_list;
//    commit();
//    return true;
}

QList<SEND_PACKET_model> widget_update_fw::make_flash_session(QByteArray ba, const QList<quint32> & modems, quint16 ver, quint16 subver, quint32 offset, qint32 check_crc)
{
    QList<SEND_PACKET_model> packets_list;

    auto insertPacket = [&] (SEND_PACKET_model spm) -> void {
        packets_list << spm;
    };

    quint16 index = 1;

    //prepare header
    QByteArray arr_header((int)(sizeof(soft_update)), 0);
    soft_update * su = (soft_update *)arr_header.data();
    su->ver = ver;
    su->ver_ext = subver;
    su->start_add = offset;
    su->end_add = su->start_add + ba.size();
    su->crc = CRC_calc((uint8_t *)ba.data(), (uint8_t *)ba.data() + ba.size());
    su->reserved[0] = 0;
    su->reserved[1] = 0;
    su->crc_of_this_struct = CRC_calc((uint8_t *)su, (uint8_t *)(&su->crc_of_this_struct));


    //Reset index
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD5;
        pkt.exec_key[0] = 0xD5;
        pkt.exec_key[1] = 0;
        pkt.packet_id = 0;
        insertPacket(pkt);
    }

    if(check_crc < 0x10000)
    {
        //check current firmware CRC
        for(const auto modem:modems)
        {
                SEND_PACKET_model pkt;
                pkt.modem_id = modem;
                pkt.payload[0] = 0xD4;
                pkt.payload[1] = (index>>8)&0xff;
                pkt.payload[2] = index&0xff;
                pkt.payload[3] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
                pkt.payload[4] = (su->start_add>>16)&0xff;
                pkt.payload[5] = (su->start_add>>8)&0xff;
                pkt.payload[6] = (su->start_add)&0xff;
                pkt.payload[7] = (su->end_add>>16)&0xff;
                pkt.payload[8] = (su->end_add>>8)&0xff;
                pkt.payload[9] = (su->end_add)&0xff;
                pkt.exec_key[0] = 0xD4;
                pkt.exec_key[1] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
                pkt.exec_key[2] = (((quint32)check_crc)>>8)&0xff;
                pkt.exec_key[3] = (((quint32)check_crc))&0xff;
                pkt.packet_id = index;
                insertPacket(pkt);
        }
        index++;
    }

    //Full erase
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    index++;

    //Write header
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_WRITE_HEADER_CMD;
        pkt.payload.append(arr_header);
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_WRITE_HEADER_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);

    }
    index++;

    quint32 address = 0;

    //Write all lines
    for(uint i = 0; i < ba.size()/LINE_SIZE; i++)
    {
        QByteArray line;
        //address = i*LINE_SIZE;
        line[0] = 0xD4;
        line[1] = (index>>8)&0xff;
        line[2] = index&0xff;
        line[3] = RFL_WRITE_CMD  + ((address>>16)&0x1f);
        line[4] = (address>>8)&0xff;
        line[5] = address&0xff;
        line.append(ba.mid(i*LINE_SIZE, LINE_SIZE));
        for(const auto modem:modems)
        {
            SEND_PACKET_model pkt;
            pkt.modem_id = modem;
            pkt.payload = line;
            insertPacket(pkt);
            pkt.packet_id = index;
        }
        address += LINE_SIZE;
        index++;
    }

    //Write tail
    if(ba.size()%LINE_SIZE)
    {
        QByteArray line;
        line[0] = 0xD4;
        line[1] = (index>>8)&0xff;
        line[2] = index&0xff;
        //address = ba.size()/LINE_SIZE*LINE_SIZE;
        line[3] = RFL_WRITE_CMD  + ((address>>16)&0x0f);
        line[4] = (address>>8)&0xff;
        line[5] = address&0xff;
        line.append(ba.mid(address, ba.size()%LINE_SIZE));
        for(const auto modem:modems)
        {
            SEND_PACKET_model pkt;
            pkt.modem_id = modem;
            pkt.payload = line;
            pkt.packet_id = index;
            insertPacket(pkt);
        }
        index++;
    }

    //Check CRC and reboot
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_CHECK_IF_CRC_OK_CMD;//RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_CHECK_IF_CRC_OK_CMD;//RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    return packets_list;
}

void widget_update_fw::on_pushButton_auto_update_clicked()
{
    ui->progressBar->setValue(0);
    use_auto_update = 1;
    cur_packets_list.clear();
    emit signal_write_data(QByteArray::fromHex("EF06"));
}
