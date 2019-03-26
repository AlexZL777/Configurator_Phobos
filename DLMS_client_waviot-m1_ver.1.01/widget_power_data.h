#ifndef WIDGET_POWER_DATA_H
#define WIDGET_POWER_DATA_H

#include <QWidget>
#include <QVariant>

namespace Ui {
class widget_power_data;
}

class widget_power_data : public QWidget
{
    Q_OBJECT

public:
    explicit widget_power_data(QWidget *parent = nullptr);
    ~widget_power_data();
    int count;
private:
    Ui::widget_power_data *ui;

    float reactPowA;
    float reactPowB;
    float reactPowC;
    float actPowA;
    float actPowB;
    float actPowC;
    void turn (void);
    bool transmit = false;
    QByteArray obis_buf[255];
    float data_buf[255];
 //  QByteArray buf_block;
signals:
    void signal_write_data_PDU (QByteArray);
    void signal_repaint();
public slots:
    void slot_show_widget_power_data();
    void slot_start_pdata();
    void slot_view_pdata(QVariant);
    void slot_read_data(QVariant);
    void slot_hide_power_data();
};

#endif // WIDGET_POWER_DATA_H
