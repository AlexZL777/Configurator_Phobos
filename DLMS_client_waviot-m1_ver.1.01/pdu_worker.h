#ifndef PDU_WORKER_H
#define PDU_WORKER_H

#include <QObject>
#include <QVariant>

class pdu_worker : public QObject
{
    Q_OBJECT
public:
    explicit pdu_worker(QObject *parent = nullptr);
signals:
    void signal_PDU_to_device(QVariant vpdu);
    void signal_electro5_from_device(QByteArray arr);
    void signal_data(QVariant arr);
    void signal_get_respons_with_data_block(QVariant, int, int);
    void signal_show_widget_info();
    void signal_show_widget_pulse();
    void signal_bar(int data);
    void signal_write_pass(QByteArray pass, bool);
    void signal_error_pass();
public slots:
    void slot_PDU_from_device(QVariant vpdu);
    void slot_electro5_to_device(QByteArray arr);
    void slot_test_pass(uint32_t server, uint32_t client, QByteArray pass);
};

#endif // PDU_WORKER_H
