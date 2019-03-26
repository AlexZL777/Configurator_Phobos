#ifndef WIDGET_INFO_H
#define WIDGET_INFO_H

#include <QWidget>
#include <QVariant>

namespace Ui {
class widget_info;
}

class widget_info : public QWidget
{
    Q_OBJECT

public:
    explicit widget_info(QWidget *parent = nullptr);
    ~widget_info();

public:

    void view_data_first (void);
    uint8_t count = 0;

private:
    void turn (void);
    bool transmit = false;
    Ui::widget_info *ui;
    uint8_t dev;
    uint8_t y;
    uint8_t h;
    uint8_t min;
    uint8_t sec;
    uint8_t msec;
    QString str_d;
    QString str_m;
    QString str_y;
    QString str_h;
    QString str_min;
    QString str_sec;
    QString str_msec;
    QString str_dev;
    QString str_status;
    QString str_dpo = "Понедельник";
    QString str_dvt = "Вторник";
    QString str_dsr = "Среда";
    QString str_dch = "Четверг";
    QString str_dpt = "Пятница";
    QString str_dsu = "Суббота";
    QString str_dvo = "Воскресенье";

public slots:
    void slot_view_data (QVariant data);
    void slot_show_widget_info();
    void slot_hide_widget_info();
signals:
    void signal_write_data_PDU (QByteArray data);
    void signal_start_pulse();
    void signal_bar(int data);
    void signal_min_window();
    void signal_show_widget_power_data();
    void signal_show_widget_power_data_1f();
    void signal_show_point_power();
//private slots:
//    void on_pushButton_clicked();
};

#endif // WIDGET_INFO_H
