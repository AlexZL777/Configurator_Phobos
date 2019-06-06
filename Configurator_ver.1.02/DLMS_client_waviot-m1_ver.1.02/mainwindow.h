#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include "widget_connect.h"
#include "widget_pdu_worker.h"
#include "widget_current.h"
#include "widget_config_obj.h"
#include "widget_update_fw.h"
#include "pdu_worker.h"
#include "widget_info.h"
#include "widget_pulse_outputs.h"
#include "dialog_disconnect.h"
#include "dialog_error_pass.h"
#include "widget_power_data.h"
#include "widget_power_data_1f.h"
//#include "point_power.h"
#include "widget_tarifs.h"
#include "dialog_insert_date_season.h"
#include "dialog_date_spec.h"
#include <dialog_profile_break.h>
#include <dialog_error_profils_seasons.h>
#include <dialog_err_profil_spec.h>
#include <dialog_err_date_spec.h>
#include <dialog_err_del_profil.h>
#include <dialog_error_sn.h>
#include <widget_log.h>
#include <widget_log_event.h>

#include <QTimer>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    widget_connect * wconnect;
    widget_PDU_worker * wpdu_work;
    widget_current * w_current;
    widget_config_obj * w_config_obj;
    widget_update_fw * w_update_fw;
    widget_info * winfo;
    widget_pulse_outputs * w_pulse;
    widget_power_data * w_pdata;
    widget_power_data_1f * w_pdata_1f;
    widget_tarifs * w_tarifs;
    widget_log * w_log;
    widget_log_event * w_log_event;
    pdu_worker * pdu_w;

 //   Dialog_disconnect * disconnect;
 //   Dialog_error_pass * error_pass;
 //   point_power * point_p;
 //   Dialog_insert_date_season * dial_season;
 //   Dialog_date_spec * dial_spec;
 //   Dialog_profile_break * profile_break;
 //   Dialog_error_profils_seasons * err_profils_seasons;
 //   Dialog_err_profil_spec * err_profil_spec;
 //   Dialog_err_date_spec * err_date_spec;
 //   Dialog_err_del_profil * err_del_profil;

    QProgressBar * progressBar = new QProgressBar(this);


    QTabWidget tab;
    bool transmit = false;
    bool change_tab = false;
    void tabSelected_sn_ok();
    bool tab0, tab1, tab2, tab3, tab4, tab5, tab6;
    bool disable_tab = false;
//    QVBoxLayout* lay = new QVBoxLayout;
//    QWidget* w1 = new QWidget;
private:
    Ui::MainWindow *ui;
    QTimer *tmr;
    QTimer *tmr2;
    void tab_show();
    bool tmr2_fl = false;
signals:
    void signal_disconnect();
    void signal_start_write_pass();
    void signal_date_season(QDate, QHash<int,int>);
    void signal_date_spec(int, QDate);
    void signal_tab_1(int);
    void signal_tab_2(int);
    void signal_show_widget_power_data();
    void signal_start_pdata();
    void signal_show_widget_power_data_1f();
    void signal_start_pdata_1f();
    void signal_show_widget_info();
    void signal_show_widget_pulse();
    void signal_start_pulse();
    void signal_pushButton_ReadData_show();
    void signal_read_tarifs();
    void signal_test_profils_seasons(QHash<int,int>, QDate);
    void signal_read_log();
    void signal_read_log_event();
    void signal_stop_read_log();
    void signal_log_read(QByteArray);
    void signal_view_log_hide_show(bool);
    void signal_view_log();
    void signal_view_log_event();
    void signal_write_data_PDU (QByteArray);
    void signal_pushButton_connect(bool);
    void signal_view_log_to_screen();
    void signal_disable_tab_kn(bool, int);
private slots:
    void slot_tabSelected();
public slots:
    void slot_control_sn(QVariant);
    void slot_bar (int data);
    void slot_min_window();
    void timeout_disconnect();
    void slot_timeout_start(int);
    void slot_error_pass();
    void dial_date_season();
    void date_spec();
    void slot_tabb();
    void slot_tab_hide();
    void slot_fase(int);
    void slot_profile_break();
    void slot_error_profils_seasons();
    void slot_err_profil_spec();
    void slot_err_date_spec();
    void slot_err_date_seasons();
    void slot_err_del_profil();
    void slot_tabSelected_button();
    void slot_log_read(QByteArray);
    void slot_timeout_stop();
    void slot_bn_view_log();
    void slot_main_window_sn(QByteArray);
    void slot_disable_tab_kn(bool, int);
};

#endif // MAINWINDOW_H
