#ifndef WIDGET_POWER_DATA_1F_H
#define WIDGET_POWER_DATA_1F_H

#include <QWidget>
#include <QVariant>

namespace Ui {
class widget_power_data_1f;
}

class widget_power_data_1f : public QWidget
{
    Q_OBJECT

public:
    explicit widget_power_data_1f(QWidget *parent = nullptr);
    ~widget_power_data_1f();
    int count;
private:
    Ui::widget_power_data_1f *ui;
    bool transmit = false;
    QByteArray obis_buf[255];
    float data_buf[255];
signals:
    void signal_write_data_PDU_1f (QByteArray);

public slots:
    void slot_show_widget_power_data_1f();
    void slot_hide_power_data_1f();
    void slot_start_pdata_1f();
    void slot_read_data (QVariant data);


};

#endif // WIDGET_POWER_DATA_1F_H
