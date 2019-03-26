include(Logger/Logger.pri)

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DLMS_client_waviot
#TARGET = DLMS_client_waviot_upd_4.1
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = ../qtbin/dlms_client_waviot

INCLUDEPATH += "DLMS"
#INCLUDEPATH += "../Phobos_STM/user"
#INCLUDEPATH += "../Phobos_STM/user/MAIN"
#INCLUDEPATH += "../Phobos_STM/user/EXT_HW"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
#    ../Phobos_STM/user/MAIN/meter.c \
#    ../Phobos_STM/user/DLMS/DLMS_AES.c \
#    ../Phobos_STM/user/DLMS/DLMS_COSEM_attributes.c \
#    ../Phobos_STM/user/DLMS/DLMS_COSEM_objects.c \
#    ../Phobos_STM/user/DLMS/DLMS_HDLC.c \
#    ../Phobos_STM/user/DLMS/DLMS_PDU.c \
#    ../Phobos_STM/user/DLMS/DLMS_PDU_buf.c \
#    ../Phobos_STM/user/DLMS/DLMS_radio.c \
#    ../Phobos_STM/user/DLMS/DLMS_arch.c \
#    ../Phobos_STM/user/DLMS/DLMS_obis_pack.c \
#    ../Phobos_STM/user/DLMS/DLMS_tariff.c \
#    ../Phobos_STM/user/DLMS/DLMS_CRC.c \
    widget_connect.cpp \
    hdlc_dlms_exchange.cpp \
    widget_pdu_worker.cpp \
    widget_current.cpp \
#    ../Phobos_STM/user/DLMS/DLMS_obis_pack.c \
    widget_config_obj.cpp \
    widget_update_fw.cpp \
    pdu_worker.cpp \
    display_obis.cpp \
    DLMS/DLMS_AES.c \
    DLMS/DLMS_CRC.c \
    DLMS/DLMS_obis_pack.c \
    widget_info.cpp \
    widget_pulse_outputs.cpp \
    dialog_disconnect.cpp \
    dialog_error_pass.cpp \
    widget_power_data.cpp \
    point_power.cpp \
    widget_power_data_1f.cpp
#    ../Phobos_STM/user/DLMS/DLMS_HDLC.c \
#    ../Phobos_STM/user/DLMS/DLMS_obis_pack.c \
#    ../Phobos_STM/user/DLMS/DLMS_PDU.c \
#    ../Phobos_STM/user/DLMS/DLMS_PDU_buf.c

HEADERS += \
        mainwindow.h \
#    ../Phobos_STM/user/MAIN/meter.h \
#    ../Phobos_STM/user/DLMS/DLMS_AES.h \
#    ../Phobos_STM/user/DLMS/DLMS_COSEM_objects.h \
#    ../Phobos_STM/user/DLMS/DLMS_enums.h \
#    ../Phobos_STM/user/DLMS/DLMS_HDLC.h \
#    ../Phobos_STM/user/DLMS/DLMS_PDU.h \
#    ../Phobos_STM/user/DLMS/DLMS_PDU_buf.h \
#    ../Phobos_STM/user/DLMS/DLMS_radio.h \
#    ../Phobos_STM/user/DLMS/DLMS_arch.h \
#    ../Phobos_STM/user/DLMS/DLMS_obis_pack.h \
#    ../Phobos_STM/user/DLMS/DLMS_tariff.h \
#    ../Phobos_STM/user/DLMS/DLMS_CRC.h \
#    ../Phobos_STM/user/EXT_HW/flash_ext.h \
    widget_connect.h \
    hdlc_dlms_exchange.h \
    widget_pdu_worker.h \
    widget_current.h \
#    ../Phobos_STM/user/DLMS/DLMS_obis_pack.h \
    widget_config_obj.h \
    widget_update_fw.h \
    pdu_worker.h \
    display_obis.h \
    DLMS/DLMS_AES.h \
    DLMS/DLMS_CRC.h \
    DLMS/DLMS_obis_pack.h \
    widget_info.h \
    widget_pulse_outputs.h \
    dialog_disconnect.h \
    dialog_error_pass.h \
    widget_power_data.h \
    point_power.h \
    widget_power_data_1f.h
#    ../Phobos_STM/user/DLMS/DLMS_HDLC.h \
#    ../Phobos_STM/user/DLMS/DLMS_obis_pack.h \
#    ../Phobos_STM/user/DLMS/DLMS_PDU.h \
#    ../Phobos_STM/user/DLMS/DLMS_PDU_buf.h

FORMS += \
        mainwindow.ui \
    widget_connect.ui \
    widget_pdu_worker.ui \
    widget_current.ui \
    widget_config_obj.ui \
    widget_update_fw.ui \
    widget_info.ui \
    widget_pulse_outputs.ui \
    dialog_disconnect.ui \
    dialog_error_pass.ui \
    widget_power_data.ui \
    point_power.ui \
    widget_power_data_1f.ui
