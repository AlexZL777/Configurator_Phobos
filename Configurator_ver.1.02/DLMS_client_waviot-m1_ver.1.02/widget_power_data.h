#ifndef WIDGET_POWER_DATA_H
#define WIDGET_POWER_DATA_H

#include <QWidget>
#include <QVariant>
#include <QTimer>

#include "point_power.h"

namespace Ui {
class widget_power_data;
}

class widget_power_data : public QWidget
{
    Q_OBJECT
    QTimer *tmr_tout;
public:
    explicit widget_power_data(QWidget *parent = nullptr);
    ~widget_power_data();
    int count;
    int count_tout;
    bool transmitt();
private:
    Ui::widget_power_data *ui;

    float reactPowA;
    float reactPowB;
    float reactPowC;
    float actPowA;
    float actPowB;
    float actPowC;
    bool transmit = false;
    QByteArray obis_buf[255];
    float data_buf[255];
 //  QByteArray buf_block;

    point_power * point_p;

signals:
    void signal_write_data_PDU (QByteArray);
    void signal_repaint();
    void signal_bar(int data);
    void signal_timeout_start(int);
    void signal_disable_tab_kn(bool, int);
    void signal_on_pushButton_connect_clicked(bool);
public slots:
    void slot_disconnect();
    void slot_show_widget_power_data();
    void slot_start_pdata();
    void slot_read_data(QVariant);
    void slot_hide_power_data();
    void timeout();
};

#endif // WIDGET_POWER_DATA_H
