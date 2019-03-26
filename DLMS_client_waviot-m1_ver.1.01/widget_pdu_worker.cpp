#include "widget_pdu_worker.h"
#include "ui_widget_pdu_worker.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QVariantMap>
#include <Logger/Logger.h>

widget_PDU_worker::widget_PDU_worker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget_PDU_worker)
{
    ui->setupUi(this);
    QFile file(qApp->applicationFilePath().replace(".exe", ".json"));
    if (!file.open(QIODevice::ReadOnly)) {
        log_1 << "cant open file" << file.fileName();
    } else {
        cmds = QJsonDocument::fromJson(file.readAll()).toVariant().toMap().value("standart_request", QVariantMap()).toMap();
    }
}

widget_PDU_worker::~widget_PDU_worker()
{
    delete ui;
}

void widget_PDU_worker::slot_PDU_from_device(QVariant vpdu)
{
    QVariantMap pdu = vpdu.toMap();
//    log_1 << qPrintable(QJsonDocument::fromVariant(vpdu).toJson(QJsonDocument::Compact));
    ui->plainTextEdit_log->setPlainText(QJsonDocument::fromVariant(vpdu).toJson(QJsonDocument::Indented));
    if (pdu.contains("UA")) {
        QVariantMap vmp;
        vmp = cmds.value("AARQ", QVariantMap()).toMap();
        emit signal_PDU_to_device(vmp);
        return;
    }
    if (pdu.contains("aare")) {
        curr_cmd = "ReadInfo";
        objs_list.clear();
        read_obj_list.clear();
        read_obj_curr.clear();
        read_attr_list.clear();
        read_attr_curr.clear();
//        emit signal_PDU_to_device(cmds.value("ReadInfo", QVariantMap()).toMap());
        return;
    }
//    log_1 << curr_cmd << pdu;
    if (curr_cmd == "ReadInfo") {
        QVariantMap vm = pdu.value("get-response", QVariantMap()).toMap();
        vm = vm.value("get-response-normal", QVariantMap()).toMap();
        vm = vm.value("result", QVariantMap()).toMap();
        vm = vm.value("data", QVariantMap()).toMap();
        objs_list = vm.value("array", QVariantList()).toList();
//        log_1 << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Compact));
        read_obj_list = objs_list;
        curr_cmd = "ReadObjAttr__";
    }
    if (curr_cmd == "ReadObjAttr") {
        log_1 << "ReadObjAttr";
        if (!read_attr_curr.isEmpty()) {
            // todo save val;
            log_1 << objs_list.size();
        }
        if (read_attr_list.isEmpty()) {
//            log_1 << read_obj_list;
            if (!read_obj_list.isEmpty()) {
//                log_1;
                read_obj_curr = read_obj_list.takeFirst().toMap();
//                read_obj_curr = read_obj_list.takeFirst().toMap();
//                log_1 << qPrintable(QJsonDocument::fromVariant(read_obj_curr).toJson(QJsonDocument::Compact));
                read_attr_list.clear();
                QVariantList vlist = read_obj_curr.value("structure", QVariantList()).toList();
                vlist = vlist.at(3).toMap().value("structure", QVariantList()).toList();
                if (!vlist.isEmpty()) {
                    read_attr_list = vlist.at(0).toMap().value("array", QVariantList()).toList();
                }
            }
        }
        if (!read_attr_list.isEmpty() && !read_obj_curr.isEmpty()) {
//            log_1 << read_attr_list << read_obj_curr;
            read_attr_curr = read_attr_list.takeFirst().toMap();
//            log_1 << qPrintable(QJsonDocument::fromVariant(read_attr_curr).toJson(QJsonDocument::Compact));
            uint32_t attr = read_attr_curr.value("structure", QVariantList()).toList().at(0).toMap().value("integer", 0).toUInt();
            if (attr == 1) { // info skip
                slot_PDU_from_device(QVariant());
                return;
            }
            QVariantList vlist = read_obj_curr.value("structure", QVariantList()).toList();
            uint32_t cosem_class = vlist.at(0).toMap().value("long-unsigned", 0).toUInt();
            QString cosem_obis = vlist.at(2).toMap().value("octet-string", "").toString();
//            log_1 << cosem_class << cosem_obis;
            QVariantMap vm_cmd = cmds.value("ReadInfo", QVariantMap()).toMap();
//            log_1 << vm_cmd.count() << qPrintable(QJsonDocument::fromVariant(vm_cmd).toJson(QJsonDocument::Indented));
            QVariantMap vm_cmd_get_request = vm_cmd.value("get-request", QVariantMap()).toMap();
//            log_1 << vm_cmd_get_request.count() << qPrintable(QJsonDocument::fromVariant(vm_cmd_get_request).toJson(QJsonDocument::Indented));
            QVariantMap vm_cmd_get_request_normal = vm_cmd_get_request.value("get-request-normal", QVariantMap()).toMap();
//            log_1 << vm_cmd_get_request_normal.count() << qPrintable(QJsonDocument::fromVariant(vm_cmd_get_request_normal).toJson(QJsonDocument::Indented));
            QVariantMap vm_cmd_cosem_attribute_descriptor = vm_cmd_get_request_normal.value("cosem-attribute-descriptor", QVariantMap()).toMap();
//            log_1 << vm_cmd_cosem_attribute_descriptor.count();
            vm_cmd_cosem_attribute_descriptor.insert("attribute-id", attr);
            vm_cmd_cosem_attribute_descriptor.insert("class-id", cosem_class);
            vm_cmd_cosem_attribute_descriptor.insert("instance-id", cosem_obis);
            vm_cmd_get_request_normal.insert("cosem-attribute-descriptor", vm_cmd_cosem_attribute_descriptor);
            vm_cmd_get_request.insert("get-request-normal", vm_cmd_get_request_normal);
            vm_cmd.insert("get-request", vm_cmd_get_request);
//            log_1 << qPrintable(QJsonDocument::fromVariant(vm_cmd).toJson(QJsonDocument::Indented));
            emit signal_PDU_to_device(vm_cmd);
            return;
        }
    }
    if (curr_cmd == "radio_bridge") {
        QVariantMap vm = pdu.value("set-response", QVariantMap()).toMap();
        vm = vm.value("set-response-normal", QVariantMap()).toMap();
        vm = vm.value("data", QVariantMap()).toMap();
        if (vm.contains("octet-string")) {
            QByteArray arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
            if (!arr.isEmpty()) {
                emit signal_electro5_from_device(arr);
                ui->lineEdit_radio_out->setText(arr.toHex().toUpper());
            }
        }
//        {
//            "set-response": {
//                "set-response-normal": {
//                    "data": {
//                        "octet-string": "EE00312031400071C5C9"
//                    },
//                    "invoke-id-and-priority": 193,
//                    "result": "success"
//                }
//            }
//        }
        return;
    }
}

void widget_PDU_worker::slot_electro5_to_device(QByteArray arr)
{
    QVariantMap vm_cmd = electro5_to_PDU(arr);
//    log_1 << qPrintable(QJsonDocument::fromVariant(vm_cmd).toJson(QJsonDocument::Compact));
    curr_cmd = "radio_bridge";
    emit signal_PDU_to_device(vm_cmd);
}

QVariantMap widget_PDU_worker::electro5_to_PDU(QByteArray el5)
{
    //    C1 01 C1 00 01 00 00 60 01 FE FF 02 00 09 02 EF 06
    //    <x:set-request>
    //      <x:set-request-normal>
    //        <x:invoke-id-and-priority>193</x:invoke-id-and-priority>
    //        <x:cosem-attribute-descriptor>
    //          <!--DATA-->
    //          <x:class-id>1</x:class-id>
    //          <!--0.0.96.1.254.255-->
    //          <x:instance-id>00006001FEFF</x:instance-id>
    //          <x:attribute-id>2</x:attribute-id>
    //        </x:cosem-attribute-descriptor>
    //        <x:value>
    //          <x:octet-string>EF06</x:octet-string>
    //        </x:value>
    //      </x:set-request-normal>
    //    </x:set-request>
    QVariantMap vm_set_request;
    QVariantMap vm_set_request_normal;
    vm_set_request_normal.insert("invoke-id-and-priority", 0xC1);
    QVariantMap vm_cosem_attribute_descriptor;
    vm_cosem_attribute_descriptor.insert("class-id", 1);
    vm_cosem_attribute_descriptor.insert("instance-id", "00006001FEFF");
    vm_cosem_attribute_descriptor.insert("attribute-id", 2);
    vm_set_request_normal.insert("cosem-attribute-descriptor", vm_cosem_attribute_descriptor);
    QVariantMap vm_value;
    vm_value.insert("octet-string", el5.toHex().toUpper());
    vm_set_request_normal.insert("value", vm_value);
    vm_set_request.insert("set-request-normal", vm_set_request_normal);
    QVariantMap vm_out;
    vm_out.insert("set-request", vm_set_request);
    return vm_out;
}

void widget_PDU_worker::on_pushButton_electro_spec_clicked()
{
    slot_electro5_to_device(QByteArray::fromHex(ui->lineEdit_radio_in->text().toLocal8Bit()));
}

#pragma pack(push, 1)
typedef struct {
  uint16_t      ver;
  uint16_t      ver_ext;
  uint32_t      start_add;
  uint32_t      end_add;
  uint16_t      crc;
  uint16_t      reserved[2];
  uint16_t      crc_of_this_struct;
} soft_update;
#pragma pack(pop)

uint16_t CRC_calc(uint8_t *start, uint8_t *end)
{
  uint16_t crc = 0x0;
  uint8_t  *data;

  for (data = start; data < end; data++)
  {
    crc  = (crc >> 8) | (crc << 8);
    crc ^= *data;
    crc ^= (crc & 0xff) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0xff) << 5;
  }
  return crc;
}

void widget_PDU_worker::on_pushButton_fw_clicked()
{
    QString f_name = QFileDialog::getOpenFileName(this, "", qApp->applicationDirPath());
    if (f_name.isEmpty()) return;
    QFile file(f_name);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray arr = file.readAll();
    file.close();
    arr = bin_to_wbin(arr);
//    QByteArray arr_header((int)(sizeof(soft_update)), 0);
//    soft_update * su = (soft_update *)arr_header.data();
//    su->ver = 1;
//    su->ver_ext = 1;
//    su->start_add = 0x08000000 + 0x1000;
//    su->end_add = su->start_add + arr.size();
//    su->crc = CRC_calc((uint8_t *)arr.data(), (uint8_t *)arr.data() + arr.size());
//    su->reserved[0] = 0;
//    su->reserved[1] = 0;
//    su->crc_of_this_struct = CRC_calc((uint8_t *)su, (uint8_t *)(&su->crc_of_this_struct));

    file.setFileName(f_name+".wbin");
    if (!file.open(QIODevice::WriteOnly)) return;
//    file.write(arr_header);
    file.write(arr);
    file.close();
    log_1 << "save fw" << file.fileName();
}

QByteArray widget_PDU_worker::bin_to_wbin(QByteArray bin)
{
    QByteArray arr_header((int)(sizeof(soft_update)), 0);
    soft_update * su = (soft_update *)arr_header.data();
    su->ver = 1;
    su->ver_ext = 1;
    su->start_add = 0x08000000 + 0x1000;
    su->end_add = su->start_add + bin.size();
    su->crc = CRC_calc((uint8_t *)bin.data(), (uint8_t *)bin.data() + bin.size());
    su->reserved[0] = 0;
    su->reserved[1] = 0;
    su->crc_of_this_struct = CRC_calc((uint8_t *)su, (uint8_t *)(&su->crc_of_this_struct));
    return arr_header+bin;
}

