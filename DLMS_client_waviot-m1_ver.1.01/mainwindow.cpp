#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hdlc_dlms_exchange.h"

#include "display_obis.h"

#include <Logger/Logger.h>

#include <widget_info.h>


#ifndef TS_BUILD
#define TS_BUILD (QLocale(QLocale::C).toDateTime(__TIMESTAMP__, "ddd MMM d hh:mm:ss yyyy").toTime_t())
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    progressBar->setAlignment(Qt::AlignTop);
    ui->statusBar->addPermanentWidget(progressBar);
    progressBar->setValue(0);
    initializeLogger(qApp->applicationDirPath()+"/log", 6, true);
    setWindowTitle("Конфигуратор счетчиков("+QDateTime::fromTime_t(TS_BUILD).toString("yyyy.MM.dd hh:mm:ss")+")");

    new HDLC_DLMS_exchange(this);

    pdu_w = new pdu_worker(this);

    wconnect = new widget_connect(this);
    ui->mainLayout->addWidget(wconnect);

    connect(pdu_w, &pdu_worker::signal_PDU_to_device, hdlc_exch, &HDLC_DLMS_exchange::slot_PDU_to_device, Qt::QueuedConnection);
    connect(hdlc_exch, &HDLC_DLMS_exchange::signal_PDU_from_device, pdu_w, &pdu_worker::slot_PDU_from_device, Qt::QueuedConnection);

    connect(wconnect, &widget_connect::signal_connect, hdlc_exch, &HDLC_DLMS_exchange::slot_connect, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_connect, pdu_w, &pdu_worker::slot_test_pass, Qt::QueuedConnection);
    connect(hdlc_exch, &HDLC_DLMS_exchange::signal_HDLC_to_device, wconnect, &widget_connect::slot_HDLC_to_device, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_HDLC_from_device, hdlc_exch, &HDLC_DLMS_exchange::slot_HDLC_from_device, Qt::QueuedConnection);


    w_current = new widget_current(true, this);
    ui->mainLayout->addWidget(w_current);

    winfo = new widget_info(this);
    ui->mainLayout->addWidget(winfo);

    w_pulse = new widget_pulse_outputs(this);
    ui->mainLayout->addWidget(w_pulse);

    point_p = new point_power(this);
    ui->mainLayout->addWidget(point_p);

    w_pdata = new widget_power_data(this);
    ui->mainLayout->addWidget(w_pdata);

    w_pdata_1f = new widget_power_data_1f(this);
    ui->mainLayout->addWidget(w_pdata_1f);



  //  ui->mainLayout->addStretch(0);
    ui->mainLayout->minimumHeightForWidth(true);

//    w_update_fw = new widget_update_fw(this);
//    ui->mainLayout->addWidget(w_update_fw);

    tmr = new QTimer();

    wconnect->start_write_pass();

   connect(tmr, SIGNAL(timeout()), this, SLOT(timeout_disconnect()));
    connect(wconnect, &widget_connect::signal_timeout_start, this, &MainWindow::slot_timeout_start, Qt::QueuedConnection);
 //   connect(this, &MainWindow::signal_disconnect, wconnect, &widget_connect::on_pushButton_connect_clicked, Qt::QueuedConnection);
    connect(this, &MainWindow::signal_disconnect, wconnect, &widget_connect::slot_disconnect, Qt::QueuedConnection);

    connect (w_pdata, &widget_power_data::signal_repaint, point_p, &point_power::slot_repaint, Qt::QueuedConnection);

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

    connect(winfo, &widget_info::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_HDLC_MAC_stringify_controller_PDU, Qt::QueuedConnection);
    connect(w_pdata, &widget_power_data::signal_write_data_PDU, hdlc_exch, &HDLC_DLMS_exchange::slot_HDLC_MAC_stringify_controller_PDU, Qt::QueuedConnection);
    connect(w_pdata_1f, &widget_power_data_1f::signal_write_data_PDU_1f, hdlc_exch, &HDLC_DLMS_exchange::slot_HDLC_MAC_stringify_controller_PDU, Qt::QueuedConnection);

 //   connect(wconnect, &widget_connect::signal_view_data_first, winfo, &widget_info::slot_view_data_first, Qt::QueuedConnection);
    connect(w_current, &widget_current::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, winfo, &widget_info::slot_view_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pdata, &widget_power_data::slot_read_data, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_data, w_pdata_1f, &widget_power_data_1f::slot_read_data, Qt::QueuedConnection);


    connect(pdu_w, &pdu_worker::signal_show_widget_info, winfo, &widget_info::slot_show_widget_info, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_widget_info, winfo, &widget_info::slot_hide_widget_info, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_show_widget_pulse, w_pulse, &widget_pulse_outputs::slot_show_widget_pulse, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_widget_pulse, w_pulse, &widget_pulse_outputs::slot_hide_widget_pulse, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_show_widget_power_data, w_pdata, &widget_power_data::slot_show_widget_power_data, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_show_widget_power_data_1f, w_pdata_1f, &widget_power_data_1f::slot_show_widget_power_data_1f, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_power_data, w_pdata, &widget_power_data::slot_hide_power_data, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_power_data_1f, w_pdata_1f, &widget_power_data_1f::slot_hide_power_data_1f, Qt::QueuedConnection);
    connect(wconnect, &widget_connect::signal_hide_point_power, point_p, &point_power::slot_hide_point_power, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_show_point_power, point_p, &point_power::slot_show_point_power, Qt::QueuedConnection);

    connect(w_pulse, &widget_pulse_outputs::signal_write_data_, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_start_pulse, w_pulse, &widget_pulse_outputs::slot_start_pulse, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_start_pdata, w_pdata, &widget_power_data::slot_start_pdata, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_start_pdata_1f, w_pdata_1f, &widget_power_data_1f::slot_start_pdata_1f, Qt::QueuedConnection);


    connect(winfo, &widget_info::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_bar, this, &MainWindow::slot_bar, Qt::QueuedConnection);
    connect(winfo, &widget_info::signal_min_window, this, &MainWindow::slot_min_window, Qt::QueuedConnection);
    connect(w_pulse, &widget_pulse_outputs::signal_min_window, this, &MainWindow::slot_min_window, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_write_pass, wconnect, &widget_connect::slot_write_pass, Qt::QueuedConnection);
    connect(pdu_w, &pdu_worker::signal_error_pass, this, &MainWindow::slot_error_pass, Qt::QueuedConnection);


//    connect(pdu_w, &pdu_worker::signal_electro5_from_device, w_update_fw, &widget_update_fw::slot_read_data, Qt::QueuedConnection);
//    connect(wconnect, &widget_connect::signal_disconnect, w_update_fw, &widget_update_fw::slot_disconnect, Qt::QueuedConnection);
//    connect(w_update_fw, &widget_update_fw::signal_write_data, pdu_w, &pdu_worker::slot_electro5_to_device, Qt::QueuedConnection);





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

void MainWindow::slot_error_pass(){
    emit signal_disconnect();
    log_1 << "stop_timer";
    tmr->stop();
    Dialog_error_pass er_pass;
    er_pass.exec();
}

void MainWindow::slot_timeout_start(int interval){
    log_1 << "start_timer";
    tmr->start(interval);
}

void MainWindow::timeout_disconnect(){
    emit signal_disconnect();
    log_1 << "stop_timer";
    tmr->stop();
    Dialog_disconnect dial;
    dial.exec();
}

void MainWindow::slot_bar (int data){
    progressBar->setValue(data);
    if (data >= 100){
        tmr->stop();
    }
}

void MainWindow::slot_min_window(){
    ui->mainLayout->minimumHeightForWidth(true);
}
