#ifndef WIDGET_PULSE_OUTPUTS_H
#define WIDGET_PULSE_OUTPUTS_H

#include <stdint.h>
#include <QWidget>

namespace Ui {
class widget_pulse_outputs;
}

class widget_pulse_outputs : public QWidget
{
    Q_OBJECT

public:
    explicit widget_pulse_outputs(QWidget *parent = nullptr);
    ~widget_pulse_outputs();

private slots:
    void on_pushButton_clicked();

private:
    Ui::widget_pulse_outputs *ui;
    bool transmit = false;
signals:
    void signal_write_data_(QByteArray data);
    void signal_updateGeometry();
    void signal_min_window();
    void signal_start_pdata();
    void signal_start_pdata_1f();
//public signals:
    void signal_bar(int data);
public slots:
    void slot_read_data_(QByteArray data);
    void slot_show_widget_pulse();
    void slot_hide_widget_pulse();
    void slot_start_pulse();
};


#endif // WIDGET_PULSE_OUTPUTS_H
