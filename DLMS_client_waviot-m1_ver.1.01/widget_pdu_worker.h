#ifndef WIDGET_PDU_WORKER_H
#define WIDGET_PDU_WORKER_H

#include <QWidget>
#include <QVariant>

namespace Ui {
class widget_PDU_worker;
}

class widget_PDU_worker : public QWidget
{
    Q_OBJECT

public:
    explicit widget_PDU_worker(QWidget *parent = 0);
    ~widget_PDU_worker();
    QVariantMap cmds;
    QString curr_cmd;
    QVariantList objs_list;

    QVariantList read_obj_list;
    QVariantMap  read_obj_curr;
    QVariantList read_attr_list;
    QVariantMap  read_attr_curr;

    static QVariantMap electro5_to_PDU(QByteArray el5);
    static QByteArray bin_to_wbin(QByteArray bin);
signals:
    void signal_PDU_to_device(QVariant vpdu);
    void signal_electro5_from_device(QByteArray arr);
public slots:
    void slot_PDU_from_device(QVariant vpdu);
    void slot_electro5_to_device(QByteArray arr);
private slots:
    void on_pushButton_fw_clicked();

    void on_pushButton_electro_spec_clicked();

private:
    Ui::widget_PDU_worker *ui;
};

#endif // WIDGET_PDU_WORKER_H
