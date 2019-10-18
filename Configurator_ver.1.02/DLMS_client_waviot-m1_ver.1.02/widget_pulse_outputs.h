#ifndef WIDGET_PULSE_OUTPUTS_H
#define WIDGET_PULSE_OUTPUTS_H

#include <stdint.h>
#include <QWidget>
#include <QTimer>
#include <QSlider>
#include <QVariant>
#include <QLabel>
#include <QMouseEvent>

class ClickableLabel1;
class ClickableLabel2;
class ClickableLabel3;
class ClickableLabel4;
class ClickableLabel5;
class ClickableLabel6;

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
    QByteArray data_temp;
    ClickableLabel1* clickLabel1;
    ClickableLabel2* clickLabel2;
    ClickableLabel3* clickLabel3;
    ClickableLabel4* clickLabel4;
    ClickableLabel5* clickLabel5;
    ClickableLabel6* clickLabel6;
    bool transmit = false;
    void disable_bn();
private slots:
    void on_pushButton_clicked();
    void setValue(int);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();

private:
    Ui::widget_pulse_outputs *ui;

    int count_tout;
    int ant = 0;
    bool bn_click;
    int transmit_next = 0;

signals:
    void signal_show_form_log();
    void signal_write_data_PDU (QByteArray data);
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
    void signal_dialog_low_pass();
    void signal_dialog_high_pass();
public slots:
    void slot_data_PDU(QVariant);
    void slot_read_data_(QByteArray data);
    void slot_show_widget_pulse();
    void slot_hide_widget_pulse();
    void slot_start_pulse();
    void timeout();
    void slot_disconnect();
    void clickLabel(int);
};

class ClickableLabel1 : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel1( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel1();
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class ClickableLabel2 : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel2( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel2();
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class ClickableLabel3 : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel3( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel3();
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class ClickableLabel4 : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel4( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel4();
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class ClickableLabel5 : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel5( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel5();
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

class ClickableLabel6 : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel6( const QString& text="", QWidget* parent=0 );
    ~ClickableLabel6();
signals:
    void clicked(int);
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // WIDGET_PULSE_OUTPUTS_H
