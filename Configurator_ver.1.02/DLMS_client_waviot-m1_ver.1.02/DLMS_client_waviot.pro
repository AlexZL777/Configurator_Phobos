include(Logger/Logger.pri)
include(QtXlsx/src/xlsx/qtxlsx.pri)

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
    DLMS/DLMS_AES.c \
    DLMS/DLMS_CRC.c \
    DLMS/DLMS_obis_pack.c \
    widget_info.cpp \
    widget_pulse_outputs.cpp \
    dialog_disconnect.cpp \
    dialog_error_pass.cpp \
    widget_power_data.cpp \
    widget_power_data_1f.cpp \
    widget_tarifs.cpp \
    dialog_insert_date_season.cpp \
    dialog_date_spec.cpp \
    point_power.cpp \
    dialog_profile_break.cpp \
    dialog_error_profils_seasons.cpp \
    dialog_err_profil_spec.cpp \
    dialog_err_date_spec.cpp \
    dialog_err_date_seasons.cpp \
    dialog_err_del_profil.cpp \
    widget_log.cpp \
    widget_log_event.cpp \
    dialog_error_sn.cpp \
    DLMS/DLMS_PDU_buf.c \
    dialog_change_low_pass.cpp \
    dialog_change_high_pass.cpp \
    form_log.cpp
#    hdlc_dlms_exchange_.cpp \
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
    DLMS/DLMS_AES.h \
    DLMS/DLMS_CRC.h \
    DLMS/DLMS_obis_pack.h \
    widget_info.h \
    widget_pulse_outputs.h \
    dialog_disconnect.h \
    dialog_error_pass.h \
    widget_power_data.h \
    point_power.h \
    widget_power_data_1f.h \
    widget_tarifs.h \
    dialog_insert_date_season.h \
    dialog_date_spec.h \
    dialog_profile_break.h \
    dialog_error_profils_seasons.h \
    dialog_err_profil_spec.h \
    dialog_err_date_spec.h \
    dialog_err_date_seasons.h \
    dialog_err_del_profil.h \
    widget_log.h \
    interface.h \
    widget_log_event.h \
    dialog_error_sn.h \
    main.h \
    NBFi_settings.h \
    DLMS/DLMS_enums.h \
    display_obis.h \
    DLMS/DLMS_PDU_buf.h \
    dialog_change_low_pass.h \
    dialog_change_high_pass.h \
    form_log.h
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
    widget_power_data_1f.ui \
    widget_tarifs.ui \
    dialog_insert_date_season.ui \
    dialog_date_spec.ui \
    dialog_profile_break.ui \
    dialog_error_profils_seasons.ui \
    dialog_err_profil_spec.ui \
    dialog_err_date_spec.ui \
    dialog_err_date_seasons.ui \
    dialog_err_del_profil.ui \
    widget_log.ui \
    widget_log_event.ui \
    dialog_error_sn.ui \
    dialog_change_low_pass.ui \
    dialog_change_high_pass.ui \
    form_log.ui

RESOURCES += \
    res.qrc
