#include "pdu_worker.h"

#include <QJsonDocument>
#include <QVariantMap>

#include "Logger/Logger.h"

#include "widget_connect.h"

extern int type_counter;

extern bool pulse_write_bar;

QByteArray passw;

pdu_worker::pdu_worker(QObject *parent)
    : QObject(parent)
{

}

void pdu_worker::slot_test_pass(uint32_t server, uint32_t client, QByteArray pass){
    passw = pass;
}

void pdu_worker::slot_PDU_from_device(QVariant vpdu)
{
    QVariantMap pdu = vpdu.toMap();
    log_1 << qPrintable(QJsonDocument::fromVariant(vpdu).toJson(QJsonDocument::Indented));
    if (pdu.contains("UA")) {
        QVariantMap vmp = QJsonDocument::fromJson(R"!!!({"aarq":{"application-context-name": 1,"user-information":"01000000065F1F0400001E1DFFFF"}})!!!").toVariant().toMap();
        emit signal_PDU_to_device(vmp);
        return;
    }
    if (pdu.contains("aare")) {
        QVariantMap vm = pdu.value("aare", QVariantMap()).toMap();
       // log_1 << QString::number(vm["result"].toInt());
//        if (passw.toHex().toUpper() == "") {log_1 << "0000000000000000000";}
//        else {log_1 << "11111111111111111";}
        if (vm["result"].toInt() == 0 && passw.toHex().toUpper() != ""){
            emit signal_show_widget_info();
            emit signal_show_widget_pulse();
            emit signal_write_pass(passw, true);
        }
        else {
            emit signal_error_pass();
            emit signal_write_pass(passw, false);
        }
        //slot_electro5_to_device(QByteArray::fromHex("EF06"));
        return;
    }
    if (pdu.contains("set-response")) {
        QVariantMap vm = pdu.value("set-response", QVariantMap()).toMap();
        vm = vm.value("set-response-normal", QVariantMap()).toMap();
        vm = vm.value("data", QVariantMap()).toMap();
        if (vm.contains("octet-string")) {
            QByteArray arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
            if (!arr.isEmpty()) {
//                log_1 << this << "RXe5" << arr.toHex().toUpper();
                emit signal_electro5_from_device(arr);
            }
        }
        if (pulse_write_bar){
            pulse_write_bar = false;
            emit signal_bar(100);
        }
        return;
    }
    if (pdu.contains("get-response")) {
        QVariantMap vm = pdu.value("get-response", QVariantMap()).toMap();
        if (vm.contains("get-response-normal")){
            vm = vm.value("get-response-normal", QVariantMap()).toMap();
            vm = vm.value("result", QVariantMap()).toMap();
            vm = vm.value("data", QVariantMap()).toMap();
            emit signal_data(vm);
        }
//        if (vm.contains("get-response-with-data-block")){
//            vm = vm.value("get-response-with-data-block", QVariantMap()).toMap();
//            int block_number = vm["block-number"].toInt();
//            int last_block = vm["last-block"].toInt();
//            vm = vm.value("result", QVariantMap()).toMap();

//        //    vm = vm.value("data", QVariantMap()).toMap();
//            emit signal_get_respons_with_data_block(vm, block_number, last_block);
//        }
        return;
    }
}

void pdu_worker::slot_electro5_to_device(QByteArray arr)
{
    log_1 << this << "TXe5" << arr.toHex().toUpper();
    QVariantMap vm_set_request;
    QVariantMap vm_set_request_normal;
    vm_set_request_normal.insert("invoke-id-and-priority", 0xC1);
    QVariantMap vm_cosem_attribute_descriptor;
    vm_cosem_attribute_descriptor.insert("class-id", 1);
    vm_cosem_attribute_descriptor.insert("instance-id", "00006001FEFF");
    vm_cosem_attribute_descriptor.insert("attribute-id", 2);
    vm_set_request_normal.insert("cosem-attribute-descriptor", vm_cosem_attribute_descriptor);
    QVariantMap vm_value;
    vm_value.insert("octet-string", arr.toHex().toUpper());
    vm_set_request_normal.insert("value", vm_value);
    vm_set_request.insert("set-request-normal", vm_set_request_normal);
    QVariantMap vm_out;
    vm_out.insert("set-request", vm_set_request);
    log_1 << qPrintable(QJsonDocument::fromVariant(vm_out).toJson(QJsonDocument::Indented));
    emit signal_PDU_to_device(vm_out);
}
