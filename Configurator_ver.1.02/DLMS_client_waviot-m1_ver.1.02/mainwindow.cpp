#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hdlc_dlms_exchange.h"

#include "display_obis.h"

#include <Logger/Logger.h>
#include <QJsonDocument>

#include <widget_info.h>
#include <QTableView>
#include <QVariant>
#include <QStandardItemModel>
#include <QDate>
#include <QLabel>
#include <qdesktopwidget.h>

#ifndef TS_BUILD
#define TS_BUILD (QLocale(QLocale::C).toDateTime(__TIMESTAMP__, "ddd MMM d hh:mm:ss yyyy").toTime_t())
#endif

extern int type_counter;
extern int count_bar;
extern QByteArray sn;
extern int bn_fl;
bool not_tab_select = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    progressBar->setAlignment(Qt::AlignTop);
    ui->statusBar->addPermanentWidget(progressBar);
    progressBar->setValue(0);
    int log_level = 0;
    QStringList slist = qApp->arguments();
    if (slist.contains("--log_level")) {
        int pos = slist.indexOf("--log_level");
        if (slist.size() > pos+1) {
            log_level = QString(slist[pos+1]).toInt();
        }
    }
    initializeLogger(qApp->applicationDirPath()+"/log", log_level, true);
   // initializeLogger(qApp->applicationDirPath()+"/log", 6, true);
    setWindowTitle("Конфигуратор счетчиков Phobos");
/*QDateTime::fromTime_t(TS_BUILD).toString("yyyy.MM.dd hh:mm:ss")+")*/



    new HDLC_DLMS_exchange(this);

    pdu_w = new pdu_worker(this);

    wconnect = new widget_connect(this);
    ui->verticalLayout->addWidget(wconnect);
  //  wconnect->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    connect(pdu_w, &pdu_worker::signal_PDU_to_device, hdlc_exch, &HDLC_DLMS_exchange::slot_vPDU_to_device, Qt::QueuedConnection);
    connect(hdlc_exch, &HDLC_DLMS_exchange::signal_PDU_from_device, pdu_w, &pdu_worker::slot_PDU_from_device, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_connect, hdlc_exch, &HDLC_DLMS_exchange::slot_connect, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_connect, pdu_w, &pdu_worker::slot_test_pass, Qt::QueuedConnection);
    connect(hdlc_exch, &HDLC_DLMS_exchange::signal_HDLC_to_device, wconnect, &widget_connect::slot_HDLC_to_device, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_HDLC_from_device, hdlc_exch, &HDLC_DLMS_exchange::slot_HDLC_from_device, Qt::QueuedConnection);

    w_tarifs = new widget_tarifs(this);
    w_current = new widget_current(true, this);
    winfo = new widget_info(this);
    w_pulse = new widget_pulse_outputs(this);
    w_pdata = new widget_power_data();
    w_pdata_1f = new widget_power_data_1f(this);
    w_log = new widget_log(this);
    w_log_event = new widget_log_event(this);

    tab.addTab( winfo, "Информация" );
    tab.addTab( w_pulse, "Настройки" );
    tab.addTab( w_pdata, "Мгновенные показания 3ф" );
    tab.addTab( w_pdata_1f, "Мгновенные показания 1ф" );
    tab.addTab( w_tarifs, "Тарифное расписание" );
    tab.addTab( w_log, "Данные" );
    tab.addTab( w_log_event, "Журналы событий" );
    ui->verticalLayout->addWidget( &tab );
//    tab.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tab.hide();
 //   ui->verticalLayout->addStretch(50);
 //   ui->verticalLayout->setSpacing(0);
 //   ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
 //   tab.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    w_update_fw = new widget_update_fw(this);
//    ui->mainLayout->addWidget(w_update_fw);
    f_log = new Form_log();

    tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(timeout_disconnect()));
    tmr2 = new QTimer();
    connect(tmr2, SIGNAL(timeout()), this, SLOT(slot_tabSelected()));
    wconnect->start_write_pass();

    connect(winfo, &widget_info::signal_main_window_sn, this, &MainWindow::slot_main_window_sn, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);

    connect(w_log, &widget_log::signal_timeout_stop, this, &MainWindow::slot_timeout_stop, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_timeout_stop, this, &MainWindow::slot_timeout_stop, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_disconnect, w_log, &widget_log::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, w_log_event, &widget_log_event::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, wconnect, &widget_connect::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, w_pdata, &widget_power_data::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, w_pdata_1f, &widget_power_data_1f::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, winfo, &widget_info::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, w_pulse, &widget_pulse_outputs::slot_disconnect, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, w_tarifs, &widget_tarifs::slot_disconnect, Qt::QueuedConnection);

//    connect (w_pdata, &widget_power_data::signal_repaint, point_p, &point_power::slot_repaint, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_read_tarifs, w_tarifs, &widget_tarifs::slot_read_tarifs, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_read_log, w_log, &widget_log::slot_read_log, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_read_log_event, w_log_event, &widget_log_event::slot_read_log_event, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_view_log, w_log, &widget_log::slot_view_log, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_view_log_event, w_log_event, &widget_log_event::slot_view_log_event, Qt::QueuedConnection);


//    connect(wconnect, &widget_connect::signal_connect, w_current, &widget_current::slot_connect, Qt::QueuedConnection);
//    connect(wconnect, &widget_connect::signal_read_data, w_current, &widget_current::slot_read_data, Qt::QueuedConnection);
//    connect(w_current, &widget_current::signal_write_data, wconnect, &widget_connect::slot_HDLC_to_device, Qt::QueuedConnection);


//    connect(wconnect, &widget_connect::signal_read_data, w_update_fw, &widget_update_fw::slot_read_data, Qt::QueuedConnection);
//    connect(wconnect, &widget_connect::signal_disconnect, w_update_fw, &widget_update_fw::slot_disconnect, Qt::QueuedConnection);
//    connect(w_update_fw, &widget_update_fw::signal_write_data, wconnect, &widget_connect::slot_HDLC_to_device, Qt::QueuedConnection);
//    connect(w_update_fw, &widget_update_fw::signal_disconnect, wconnect, &widget_connect::slot_disconnect, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_connect, w_current, &widget_current::slot_connect, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_current, &widget_current::slot_read_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_pulse, &widget_pulse_outputs::slot_read_data_, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_tarifs, &widget_tarifs::slot_tariff_json_unpack, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device, this, &MainWindow::slot_log_read, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_log_read, w_log, &widget_log::slot_log_read, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_log_event, &widget_log_event::slot_log_event_read, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device_empty_arr, w_log_event, &widget_log_event::slot_log_event_empty_arr, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_electro5_from_device_empty_arr, w_log, &widget_log::slot_log_event_empty_arr, Qt::QueuedConnection);

    connect(winfo, &widget_info::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_write_data_PDU_1f, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);

    connect(w_current, &widget_current::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_write_data_, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);

    connect(w_pulse, &widget_pulse_outputs::signal_dialog_low_pass, this, &MainWindow::slot_dialog_low_pass, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_dialog_high_pass, this, &MainWindow::slot_dialog_high_pass, Qt::QueuedConnection);

    connect(pdu_w, &pdu_worker::signal_data, winfo, &widget_info::slot_view_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pulse, &widget_pulse_outputs::slot_data_PDU, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pdata, &widget_power_data::slot_read_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pdata_1f, &widget_power_data_1f::slot_read_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, this, &MainWindow::slot_control_sn, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_show_widget_info, winfo, &widget_info::slot_show_widget_info, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_widget_info, winfo, &widget_info::slot_hide_widget_info, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_show_widget_pulse, w_pulse, &widget_pulse_outputs::slot_show_widget_pulse, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_widget_pulse, w_pulse, &widget_pulse_outputs::slot_hide_widget_pulse, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_log, f_log, &Form_log::slot_log, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_form_log_close, this, &MainWindow::slot_form_log_close, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_show_form_log, this, &MainWindow::slot_show_form_log, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_show_widget_power_data, w_pdata, &widget_power_data::slot_show_widget_power_data, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_show_widget_power_data_1f, w_pdata_1f, &widget_power_data_1f::slot_show_widget_power_data_1f, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_power_data, w_pdata, &widget_power_data::slot_hide_power_data, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_power_data_1f, w_pdata_1f, &widget_power_data_1f::slot_hide_power_data_1f, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_pushButton_ReadData_show, wconnect, &widget_connect::slot_pushButton_ReadData_show, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_pushButton_connect, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_on_pushButton_connect_clicked, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_start_pulse, w_pulse, &widget_pulse_outputs::slot_start_pulse, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_start_pdata, w_pdata, &widget_power_data::slot_start_pdata, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_start_pdata_1f, w_pdata_1f, &widget_power_data_1f::slot_start_pdata_1f, Qt::QueuedConnection);

    connect(winfo, &widget_info::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);

    connect(pdu_w, &pdu_worker::signal_write_pass, wconnect, &widget_connect::slot_write_pass, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_error_pass, this, &MainWindow::slot_error_pass, Qt::QueuedConnection);

    connect(w_tarifs, &widget_tarifs::signal_dial_date_season, this, &MainWindow::dial_date_season, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_date_season, w_tarifs, &widget_tarifs::slot_date_season, Qt::QueuedConnection);

    connect(w_tarifs, &widget_tarifs::signal_date_spec, this, &MainWindow::date_spec, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_date_spec, w_tarifs, &widget_tarifs::slot_date_spec, Qt::QueuedConnection);

    connect(pdu_w, &pdu_worker::tabb_Connect, this, &MainWindow::slot_tabb, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_tab_hide, this, &MainWindow::slot_tab_hide, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_view_log_to_screen, this, &MainWindow::slot_bn_view_log, Qt::QueuedConnection);

    connect(winfo, &widget_info::signal_fase, this, &MainWindow::slot_fase, Qt::QueuedConnection);

    //    connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_update_fw, &widget_update_fw::slot_read_data, Qt::QueuedConnection);
//    connect(wconnect, &widget_connect::signal_disconnect, w_update_fw, &widget_update_fw::slot_disconnect, Qt::QueuedConnection);
//    connect(w_update_fw, &widget_update_fw::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);

    connect(&tab, SIGNAL(currentChanged(int)), this, SLOT(slot_tabSelected()));

    connect(w_tarifs, &widget_tarifs::signal_profile_break, this, &MainWindow::slot_profile_break, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_error_profils_seasons, this, &MainWindow::slot_error_profils_seasons, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_err_profil_spec, this, &MainWindow::slot_err_profil_spec, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_error_data_spec, this, &MainWindow::slot_err_date_spec, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_error_data_seasons, this, &MainWindow::slot_err_date_seasons, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_err_del_profil, this, &MainWindow::slot_err_del_profil, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_test_profils_seasons, w_tarifs, &widget_tarifs::slot_test_profils_seasons, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_stop_read_log, w_log, &widget_log::slot_stop_read_log, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_view_log_hide_show, wconnect, &widget_connect::slot_view_log_hide_show, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_stop_read_log, w_log_event, &widget_log_event::slot_stop_read_log_event, Qt::QueuedConnection);

    connect(winfo, &widget_info::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disable_tab_kn, wconnect, &widget_connect::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_disable_tab_kn, this, &MainWindow::slot_disable_tab_kn, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_disable_tab_kn, this, &MainWindow::slot_enable_tab_kn, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_min_max_window, this, &MainWindow::slot_min_max_window, Qt::QueuedConnection);

  //  connect(wconnect, &widget_connect::signal_save_xls, w_log, &widget_log::slot_save_xls, Qt::QueuedConnection);

    //    wpdu_work = new widget_PDU_worker(this);
    //    ui->mainLayout->addWidget(wpdu_work);

    //    w_config_obj = new widget_config_obj(this);
    //    ui->mainLayout->addWidget(w_config_obj);

    //    connect(wconnect, widget_connect::signal_JsonPDU_to_device, hdlc_exch, HDLC_DLMS_exchange::slot_JsonPDU_to_device, Qt::QueuedConnection);

    //    connect(hdlc_exch, HDLC_DLMS_exchange::signal_PDU_from_device, wpdu_work, widget_PDU_worker::slot_PDU_from_device);
    //    connect(wpdu_work, widget_PDU_worker::signal_PDU_to_device, hdlc_exch, HDLC_DLMS_exchange::slot_PDU_to_device);

    //    connect(wconnect, widget_connect::signal_read_data, w_config_obj, widget_config_obj::slot_read_data, Qt::QueuedConnection);
    //    connect(w_config_obj, widget_config_obj::signal_write_data, wconnect, widget_connect::slot_HDLC_to_device, Qt::QueuedConnection);

//    display_obis();
    slot_min_max_window(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_show_form_log(){
    f_log->show();
}

void MainWindow::slot_form_log_close(){
  //  f_log->close();
}

void MainWindow::slot_enable_tab_kn() {
    log_1 << "slot_enable_tab_kn";
    disable_tab = false;
    tab.setTabEnabled(0, true);
    tab.setTabEnabled(1, true);
    tab.setTabEnabled(2, true);
    tab.setTabEnabled(3, true);
    tab.setTabEnabled(4, true);
    tab.setTabEnabled(5, true);
    tab.setTabEnabled(6, true);
    tab0 = true;
    tab1 = true;
    tab2 = true;
    tab3 = true;
    tab4 = true;
    tab5 = true;
    tab6 = true;
}

void MainWindow::slot_disable_tab_kn(bool fl, int act_tab) {
    log_1 << "tab" << tab0 << tab1 << tab2 << tab3 << tab4 << tab5 << tab6 << "|fl-" << fl << "| disable_tab-" << disable_tab << "|";
    if (fl) {
        if (!disable_tab){
            disable_tab = true;
            tab0 = tab.isTabEnabled(0);
            tab1 = tab.isTabEnabled(1);
            tab2 = tab.isTabEnabled(2);
            tab3 = tab.isTabEnabled(3);
            tab4 = tab.isTabEnabled(4);
            tab5 = tab.isTabEnabled(5);
            tab6 = tab.isTabEnabled(6);
            if (act_tab != 0) tab.setTabEnabled(0, false);
            if (act_tab != 1) tab.setTabEnabled(1, false);
            if (act_tab != 2) tab.setTabEnabled(2, false);
            if (act_tab != 3) tab.setTabEnabled(3, false);
            if (act_tab != 4) tab.setTabEnabled(4, false);
            if (act_tab != 5) tab.setTabEnabled(5, false);
            if (act_tab != 6) tab.setTabEnabled(6, false);
        }
    }
    else {
        disable_tab = false;
        if (tab0) tab.setTabEnabled(0, true);
        if (tab1) tab.setTabEnabled(1, true);
        if (tab2) tab.setTabEnabled(2, true);
        if (tab3) tab.setTabEnabled(3, true);
        if (tab4) tab.setTabEnabled(4, true);
        if (tab5) tab.setTabEnabled(5, true);
        if (tab6) tab.setTabEnabled(6, true);
    }
}

void MainWindow::slot_main_window_sn(QByteArray sn){
    setWindowTitle("Конфигуратор счетчиков Phobos (SN "+sn.toUpper()+")");
}

void MainWindow::slot_err_del_profil(){
    Dialog_err_del_profil d_err_date_profile;
    d_err_date_profile.exec();
}

void MainWindow::slot_err_date_seasons(){
    Dialog_err_date_spec d_err_date_spec;
    d_err_date_spec.exec();
}

void MainWindow::slot_err_date_spec(){
    Dialog_err_date_spec d_err_date_spec;
    d_err_date_spec.exec();
}

void MainWindow::slot_err_profil_spec(){
    Dialog_err_profil_spec d_err_pr_spec;
    d_err_pr_spec.exec();
}

void MainWindow::slot_error_profils_seasons(){
    Dialog_error_profils_seasons d_err_pr_seasons;
    d_err_pr_seasons.exec();
    dial_date_season();
}

void MainWindow::slot_profile_break(){
    Dialog_profile_break d_profile_break;
    d_profile_break.exec();
}

void MainWindow::tab_show(){
    log_1 << "tab_show" << "!tab.isVisible()-" << !tab.isVisible();
    if ( !tab.isVisible() ) {
        tab.setCurrentIndex(0);
        tab.show();
     //   wconnect->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    //    tab.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        emit signal_show_widget_info();
        not_tab_select = false;
    }
    else {
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600100FF0200"));
    }
}

void MainWindow::slot_control_sn(QVariant data){
    log_1 << "slot_control_sn" << "transmit-" << transmit;
    if (transmit){
        transmit = false;
        QByteArray arr;
        int a;
        QVariantMap vm = data.toMap();
        log_1 << "sn" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        if (vm.contains("long-unsigned")) a = vm["long-unsigned"].toInt();
        if (vm.contains("octet-string")) arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
        if (vm.contains("date-time")) arr = QByteArray::fromHex(vm.value("date-time", "").toString().toLocal8Bit());
        tmr->stop();
        log_1 << "arr_sn-" << arr.toHex().toUpper() << "|  sn-" << sn.toHex().toUpper();
        if ( arr == sn){
            if ( change_tab ) {
                change_tab = false;
                tabSelected_sn_ok();
            }
            else{
                if ( bn_fl == 1 ){
                    emit signal_view_log_to_screen();
                }
                else slot_tabSelected_button();
            }
        }
        else {
            emit signal_view_log_hide_show(0);
            emit signal_disconnect();
            log_1 << "da nu nafig!!!";
            Dialog_error_sn d_err_sn;
            d_err_sn.exec();
        }
    }
}

void MainWindow::slot_tab_hide(){
    log_1 << "slot_tab_hide";
    emit signal_view_log_hide_show(0);
    emit signal_disconnect();
    if (disable_tab) slot_disable_tab_kn(0, 0);
    not_tab_select = true;
    tab.setCurrentIndex(0);
    tab.hide();
    progressBar->setValue(0);
    count_bar = 0;
    tmr->stop();
}

void MainWindow::slot_fase(int data){
    if (data == 51){        //Трёхфазный счётчик
        tab.setTabEnabled(3, false);
        tab.setTabEnabled(2, true);
    }
    else if (data == 49){   //Однофазный счётчик
        tab.setTabEnabled(2, false);
        tab.setTabEnabled(3, true);
    }
}

void MainWindow::slot_log_read(QByteArray data){
    if( tab.currentIndex() == 5 ){
        emit signal_log_read(data);
    }
}

void MainWindow::slot_bn_view_log(){
    log_1 << "slot_bn_view_log";
    if( tab.currentIndex() == 5 ){
        emit signal_view_log();
    }
    else if( tab.currentIndex() == 6 ){
        emit signal_view_log_event();
    }
}

void MainWindow::slot_tabSelected_button(){
    log_1 << "slot_tabSelected_button" << "change_tab-" << change_tab << "bn_fl-" << bn_fl << "tab.currentIndex()-" << tab.currentIndex();
    if ( change_tab || bn_fl == 2 ){
        progressBar->setValue(0);
        count_bar = 0;
    }
    bn_fl = 0;
    if( tab.currentIndex() == 5 ){
        log_1 << "test_2";
        emit signal_disable_tab_kn(1, 5);
        if (!disable_tab) slot_disable_tab_kn(1, 5);
        emit signal_read_log();
    }
    else if( tab.currentIndex() == 6 ){
        log_1 << "test_3";
        emit signal_disable_tab_kn(1, 6);
        if (!disable_tab) slot_disable_tab_kn(1, 6);
        emit signal_read_log_event();
    }
    else tabSelected_sn_ok();
}

void MainWindow::slot_tabSelected(){
    log_1 << "slot_tabSelected" << "not_tab_select-" << not_tab_select;;
    if (!not_tab_select) {
        transmit = true;
        change_tab = true;
        signal_pushButton_connect(true);
        log_1 << "transmitt";
    }
    not_tab_select = false;
}

void MainWindow::tabSelected_sn_ok(){
    log_1 << "tabSelected_sn_ok";
    if ( ( w_log->transmitt() ||
           winfo->transmitt() ||
           w_pdata->transmitt() ||
           w_pdata_1f->transmitt() ||
           w_pulse->transmitt() ||
           w_tarifs->transmitt() ||
           w_log_event->transmitt() )/* && !tmr2_fl*/ ){
        log_1 << "tabSelected_sn_ok 1";
        count_bar = 0;
        progressBar->setValue(0);
        tmr2->start(500);
        tmr2_fl = true;
        emit signal_stop_read_log();
    }
    else {
        log_1 << "tabSelected_sn_ok 2";
        tmr2_fl = false;
        tmr2->stop();
        tmr->stop();
        if( tab.currentIndex() == 0 ){
            emit signal_disable_tab_kn(1, 0);
            emit signal_show_widget_info();
            emit signal_view_log_hide_show(0);
        }
        if( tab.currentIndex() == 1 ){
            emit signal_disable_tab_kn(1, 1);
            if (!disable_tab) slot_disable_tab_kn(1, 1);
            emit signal_view_log_hide_show(0);
            emit signal_show_widget_pulse();
            emit signal_start_pulse();
        }
        if( tab.currentIndex() == 2 || tab.currentIndex() == 3 ){
            emit signal_view_log_hide_show(0);
            if (type_counter == 51){        //Трёхфазный счётчик
                tab.setTabEnabled(3, false);
                tab.setTabEnabled(2, true);
                emit signal_disable_tab_kn(1, 2);
                if (!disable_tab) slot_disable_tab_kn(1, 2);
                emit signal_show_widget_power_data();
                emit signal_start_pdata();
            }
            else if (type_counter == 49){   //Однофазный счётчик
                tab.setTabEnabled(2, false);
                tab.setTabEnabled(3, true);
                emit signal_disable_tab_kn(1, 3);
                if (!disable_tab) slot_disable_tab_kn(1, 3);
                emit signal_show_widget_power_data_1f();
                emit signal_start_pdata_1f();
            }
        }
        if( tab.currentIndex() == 4 ){
            emit signal_disable_tab_kn(1, 4);
            if (!disable_tab) slot_disable_tab_kn(1, 4);
            emit signal_view_log_hide_show(0);
            emit signal_read_tarifs();
        }
        if( tab.currentIndex() == 5 ){
            emit signal_view_log_hide_show(1);
        }
        if( tab.currentIndex() == 6 ){
            emit signal_view_log_hide_show(1);
        }
    }
}

void MainWindow::slot_tabb(){
    log_1 << "slot_tabb";
    tmr->stop();
    emit signal_pushButton_ReadData_show();
    slot_min_max_window(1);
    tab_show();
}

void MainWindow::slot_error_pass(){
    log_1 << "slot_error_pass";
    emit signal_disconnect();
    tmr->stop();
    Dialog_error_pass er_pass;
    er_pass.exec();
}

void MainWindow::slot_dialog_low_pass(){
    Dialog_change_low_pass change_low_pass;
    connect(&change_low_pass, SIGNAL(signal_write_data(QByteArray)), this, SLOT(slot_write_data(QByteArray)));
    change_low_pass.exec();
}

void MainWindow::slot_write_data(QByteArray data){
    log_1 << "slot_write_data";
    emit signal_write_data(data);
}

void MainWindow::slot_dialog_high_pass(){
    Dialog_change_high_pass change_high_pass;
    connect(&change_high_pass, SIGNAL(signal_write_data(QByteArray)), this, SLOT(slot_write_data(QByteArray)));
    change_high_pass.exec();
}

void MainWindow::slot_timeout_start(int interval){
    log_1 << "slot_timeout_start interval-" << interval;
    tmr->start(interval);
}

void MainWindow::slot_timeout_stop(){
    log_1 << "slot_timeout_stop";
    if (disable_tab) slot_disable_tab_kn(0, -1);
    tmr->stop();
}

void MainWindow::timeout_disconnect(){
    log_1 << "timeout_disconnect";
    progressBar->setValue(0);
    emit signal_disconnect();
    emit signal_view_log_hide_show(0);
    if (disable_tab) slot_disable_tab_kn(0, -1);
    tmr->stop();
    Dialog_disconnect dial;
    dial.exec();
}

void MainWindow::dial_date_season(){
    Dialog_insert_date_season dial_season;
    if (dial_season.exec() == QDialog::Accepted){
        if (dial_season.getprofile().isEmpty()){return;}
        else{
            emit signal_test_profils_seasons(dial_season.getprofile(), dial_season.getData());
        }
    }
}

void MainWindow::date_spec(){
    Dialog_date_spec dial_spec;
    if (dial_spec.exec() == QDialog::Accepted){
        if (dial_spec.getprofile() == -1){return;}
        else emit signal_date_spec(dial_spec.getprofile(), dial_spec.getData());
    }
}

void MainWindow::slot_bar (int data){
    progressBar->setValue(data);
    if (data >= 100){
        progressBar->setValue(100);
        tmr->stop();
        count_bar = 0;
    }
}

void MainWindow::slot_min_max_window(bool fl){
    if (fl && !maximized_window){
        log_1 << "slot_min_max_window" << fl;
        maximized_window = true;
        QDesktopWidget desktop;
        QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
        QPoint topleft = rect.topLeft(); //координаты центра экрана
        int x = topleft.x() /*- (this->width()/2)*/;  // учитываем половину ширины окна
        int y = topleft.y() /*- (this->height()/2)*/; // .. половину высоты
        topleft.setX(x);
        topleft.setY(y);
        this->move(topleft);
        QRect screenGeometry = QApplication::desktop()->availableGeometry();
        resize(screenGeometry.width(), screenGeometry.height());
        showMaximized ();
    }
    else if (!fl){
        log_1 << "slot_min_max_window" << fl;
        maximized_window = false;
        this->resize(400, 500);
        showNormal();
        QDesktopWidget desktop;
        QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
        QPoint center = rect.center(); //координаты центра экрана
        int x = center.x() - (this->width()/2);  // учитываем половину ширины окна
        int y = center.y() - (this->height()/2); // .. половину высоты
        center.setX(x);
        center.setY(y);
        this->move(center);
    }
}
