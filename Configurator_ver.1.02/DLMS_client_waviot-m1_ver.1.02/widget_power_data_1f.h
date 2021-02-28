#ifndef WIDGET_POWER_DATA_1F_H
#define WIDGET_POWER_DATA_1F_H

#include <QWidget>
#include <QVariant>
#include <QTimer>

namespace Ui {
class widget_power_data_1f;
}

class widget_power_data_1f : public QWidget
{
    Q_OBJECT
    QTimer *tmr_tout;
public:
    explicit widget_power_data_1f(QWidget *parent = nullptr);
    ~widget_power_data_1f();
    int count;
    int count_tout;
    bool transmitt();
private:
    Ui::widget_power_data_1f *ui;
    float reactPow;
    float actPow;
    bool transmit = false;
    QByteArray obis_buf[255];
    float data_buf[255];
signals:
    void signal_write_data_PDU_1f (QByteArray);
    void signal_bar(int data);
    void signal_timeout_start(int);
    void signal_disable_tab_kn(bool, int);
    void signal_on_pushButton_connect_clicked(bool);
public slots:
    void slot_disconnect();
    void slot_show_widget_power_data_1f();
    void slot_hide_power_data_1f();
    void slot_start_pdata_1f();
    void slot_read_data (QVariant data);
    void timeout();

};

#endif // WIDGET_POWER_DATA_1F_H
