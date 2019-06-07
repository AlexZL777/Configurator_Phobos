#ifndef WIDGET_PULSE_OUTPUTS_H
#define WIDGET_PULSE_OUTPUTS_H

#include <stdint.h>
#include <QWidget>
#include <QTimer>
#include <QSlider>

namespace Ui {
class widget_pulse_outputs;
}

class widget_pulse_outputs : public QWidget
{
    Q_OBJECT
    QTimer *tmr_tout_pulse;
    QTimer *tmr_t;
public:
    explicit widget_pulse_outputs(QWidget *parent = nullptr);
    ~widget_pulse_outputs();
    bool transmitt();
private slots:
    void on_pushButton_clicked();
    void setValue(int);
private:
    Ui::widget_pulse_outputs *ui;
    bool transmit = false;
    int count_tout;
    bool ant;
    bool bn_click;

signals:
    void signal_write_data_(QByteArray data);
    void signal_updateGeometry();
    void signal_min_window();
    void signal_start_pdata();
    void signal_start_pdata_1f();
    void signal_timeout_start(int);
    void signal_bar(int data);
    void signal_disable_tab_kn(bool, int);
    void signal_on_pushButton_connect_clicked(bool);
    void signal_write_data(QByteArray);
public slots:
    void slot_read_data_(QByteArray data);
    void slot_show_widget_pulse();
    void slot_hide_widget_pulse();
    void slot_start_pulse();
    void timeout();
    void slot_disconnect();
};


#endif // WIDGET_PULSE_OUTPUTS_H
