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
#include "point_power.h"

#include <QTimer>

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
    pdu_worker * pdu_w;
    Dialog_disconnect * disconnect;
    Dialog_error_pass * error_pass;
    point_power * point_p;

    QProgressBar * progressBar = new QProgressBar(this);

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
signals:
    void signal_disconnect();
    void signal_start_write_pass();
public slots:
    void slot_bar (int data);
    void slot_min_window();
    void timeout_disconnect();
    void slot_timeout_start(int);
    void slot_error_pass();
};

#endif // MAINWINDOW_H
