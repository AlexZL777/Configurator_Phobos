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

//    QGridLayout* lay = new QGridLayout;
//    QWidget* w1 = new QWidget;

    pdu_w = new pdu_worker(this);

    wconnect = new widget_connect(this);
    ui->mainLayout->addWidget(wconnect);

    connect(pdu_w, &pdu_worker::signal_PDU_to_device, hdlc_exch, &HDLC_DLMS_exchange::slot_vPDU_to_device, Qt::QueuedConnection);
    connect(hdlc_exch, &HDLC_DLMS_exchange::signal_PDU_from_device, pdu_w, &pdu_worker::slot_PDU_from_device, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_connect, hdlc_exch, &HDLC_DLMS_exchange::slot_connect, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_connect, pdu_w, &pdu_worker::slot_test_pass, Qt::QueuedConnection);
    connect(hdlc_exch, &HDLC_DLMS_exchange::signal_HDLC_to_device, wconnect, &widget_connect::slot_HDLC_to_device, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_HDLC_from_device, hdlc_exch, &HDLC_DLMS_exchange::slot_HDLC_from_device, Qt::QueuedConnection);

    w_tarifs = new widget_tarifs(this);
//    ui->mainLayout->addWidget(w_tarifs);

    w_current = new widget_current(true, this);
    ui->mainLayout->addWidget(w_current);

    winfo = new widget_info(this);
 //   ui->mainLayout->addWidget(winfo);

    w_pulse = new widget_pulse_outputs(this);
 //   ui->mainLayout->addWidget(w_pulse);

  //  point_p = new point_power();
//    ui->mainLayout->addWidget(point_p);

    w_pdata = new widget_power_data();
 //   ui->mainLayout->addWidget(w_pdata);

    w_pdata_1f = new widget_power_data_1f(this);
//    ui->mainLayout->addWidget(w_pdata_1f);

    w_log = new widget_log(this);
    w_log_event = new widget_log_event(this);


    tab.addTab( winfo, "Информация" );
    ui->mainLayout->addWidget( &tab );
    tab.addTab( w_pulse, "Настройки" );
    ui->mainLayout->addWidget( &tab );
    tab.addTab( w_pdata, "Мгновенные показания 3ф" );
    ui->mainLayout->addWidget( &tab );
    tab.addTab( w_pdata_1f, "Мгновенные показания 1ф" );
    ui->mainLayout->addWidget( &tab );
    tab.addTab( w_tarifs, "Тарифное расписание" );
    ui->mainLayout->addWidget( &tab );
    tab.addTab( w_log, "Данные" );
    ui->mainLayout->addWidget( &tab );
    tab.addTab( w_log_event, "Журналы событий" );
    ui->mainLayout->addWidget( &tab );

    tab.hide();

  //  ui->mainLayout->addStretch(0);
    ui->mainLayout->minimumHeightForWidth(true);

//    w_update_fw = new widget_update_fw(this);
//    ui->mainLayout->addWidget(w_update_fw);

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
  //  connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_pulse, &widget_pulse_outputs::slot_data_from_electro5, Qt::QueuedConnection);

    connect(winfo, &widget_info::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_write_data_PDU_1f, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);

 //   connect(wconnect, &widget_connect::signal_view_data_first, winfo, &widget_info::slot_view_data_first, Qt::QueuedConnection);
    connect(w_current, &widget_current::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_tarifs, &widget_tarifs::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_write_data_, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_log, &widget_log::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_log_event, &widget_log_event::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);


    connect(pdu_w, &pdu_worker::signal_data, winfo, &widget_info::slot_view_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pdata, &widget_power_data::slot_read_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pdata_1f, &widget_power_data_1f::slot_read_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, this, &MainWindow::slot_control_sn, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_show_widget_info, winfo, &widget_info::slot_show_widget_info, Qt::QueuedConnection);
  //  connect(wconnect, &widget_connect::signal_show_widget_info, winfo, &widget_info::slot_show_widget_info, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_widget_info, winfo, &widget_info::slot_hide_widget_info, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_show_widget_pulse, w_pulse, &widget_pulse_outputs::slot_show_widget_pulse, Qt::QueuedConnection);
//    connect(wconnect, &widget_connect::signal_show_widget_pulse, w_pulse, &widget_pulse_outputs::slot_show_widget_pulse, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_widget_pulse, w_pulse, &widget_pulse_outputs::slot_hide_widget_pulse, Qt::QueuedConnection);

    connect(this, &MainWindow::signal_show_widget_power_data, w_pdata, &widget_power_data::slot_show_widget_power_data, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_show_widget_power_data_1f, w_pdata_1f, &widget_power_data_1f::slot_show_widget_power_data_1f, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_power_data, w_pdata, &widget_power_data::slot_hide_power_data, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_power_data_1f, w_pdata_1f, &widget_power_data_1f::slot_hide_power_data_1f, Qt::QueuedConnection);

//    connect(wconnect, &widget_connect::signal_hide_point_power, point_p, &point_power::slot_hide_point_power, Qt::QueuedConnection);
//    connect(winfo, &widget_info::signal_show_point_power, point_p, &point_power::slot_show_point_power, Qt::QueuedConnection);
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

    connect(winfo, &widget_info::signal_min_window, this, &MainWindow::slot_min_window, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_min_window, this, &MainWindow::slot_min_window, Qt::QueuedConnection);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_disable_tab_kn(bool fl, int act_tab) {
    if (fl) {
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
    if ( !tab.isVisible() ) {
        tab.setCurrentIndex(0);
        tab.show();
        emit signal_show_widget_info();
    }
    else {
        transmit = true;
        emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000600100FF0200"));
    }
}

void MainWindow::slot_control_sn(QVariant data){
    if (transmit){
        transmit = false;
        QByteArray arr;
        int a;
        QVariantMap vm = data.toMap();
      //  log_1 << "222" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        if (vm.contains("long-unsigned")) a = vm["long-unsigned"].toInt();
        if (vm.contains("octet-string")) arr = QByteArray::fromHex(vm.value("octet-string", "").toString().toLocal8Bit());
        if (vm.contains("date-time")) arr = QByteArray::fromHex(vm.value("date-time", "").toString().toLocal8Bit());
        tmr->stop();
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
    if( tab.currentIndex() == 5 ){
        emit signal_view_log();
    }
    else if( tab.currentIndex() == 6 ){
        emit signal_view_log_event();
    }
}

void MainWindow::slot_tabSelected_button(){
 //   log_1 << "reboot";
    if ( change_tab || bn_fl == 2 ){
 //       log_1 << "reboottttttttttt";
        progressBar->setValue(0);
        count_bar = 0;
    }
    bn_fl = 0;
    if( tab.currentIndex() == 5 ){
        emit signal_disable_tab_kn(1, 5);
        if (!disable_tab) slot_disable_tab_kn(1, 5);
        emit signal_read_log();
    }
    else if( tab.currentIndex() == 6 ){
        emit signal_disable_tab_kn(1, 6);
        if (!disable_tab) slot_disable_tab_kn(1, 6);
        emit signal_read_log_event();
    }
    else tabSelected_sn_ok();
}

void MainWindow::slot_tabSelected(){
    log_1 << "not_tab_select" << not_tab_select;
    if (!not_tab_select) {
        transmit = true;
        change_tab = true;
        signal_pushButton_connect(true);
        log_1 << "transmitt";
    }
    not_tab_select = false;
}

void MainWindow::tabSelected_sn_ok(){
    if ( ( w_log->transmitt() ||
           winfo->transmitt() ||
           w_pdata->transmitt() ||
           w_pdata_1f->transmitt() ||
           w_pulse->transmitt() ||
           w_tarifs->transmitt() ||
           w_log_event->transmitt() ) && !tmr2_fl ){
   //     log_1 << "xxxxxxxxx";
        count_bar = 0;
        progressBar->setValue(0);
        tmr2->start(500);
        tmr2_fl = true;
        emit signal_stop_read_log();
    }
    else {
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
    emit signal_pushButton_ReadData_show();
    tab_show();
}

void MainWindow::slot_error_pass(){
    emit signal_disconnect();
 //   log_1 << "stop_timer";
    tmr->stop();
    Dialog_error_pass er_pass;
    er_pass.exec ();
}

void MainWindow::slot_timeout_start(int interval){
    log_1 << "start_timer" << interval;
    tmr->start(interval);
}

void MainWindow::slot_timeout_stop(){
    log_1 << "stop_timer";
   // emit signal_view_log_hide_show(0);
    if (disable_tab) slot_disable_tab_kn(0, 0);
    tmr->stop();
}

void MainWindow::timeout_disconnect(){
    progressBar->setValue(0);
    emit signal_disconnect();
    emit signal_view_log_hide_show(0);
    if (disable_tab) slot_disable_tab_kn(0, 0);
    log_1 << "stop_timer disconnect";
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

void MainWindow::slot_min_window(){
    ui->mainLayout->minimumHeightForWidth(true);
}
