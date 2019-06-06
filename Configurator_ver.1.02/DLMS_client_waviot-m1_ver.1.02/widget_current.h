#ifndef WIDGET_CURRENT_H
#define WIDGET_CURRENT_H

#include <stdint.h>
#include <QWidget>
#include <QVariantMap>
#include <QAbstractTableModel>

namespace Ui {
class widget_current;
}

typedef struct {
    uint32_t i;
    uint32_t v;
    uint32_t w;
    uint32_t var;
} ADE_cal;

class model_current : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit model_current(bool is_calib, uint8_t dev_HW_id, QObject *parent = 0);
    virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
//    virtual void update_data(QVariantMap lic_data);
//    QVariantMap get_row(int row);
//    void clear();
    void set_curr(QVariantMap vm);
    void set_cal(QMap<uint32_t, ADE_cal> cals);
    QVariant cal_show(uint32_t cal_data) const;
    uint32_t show_cal(QVariant data);
    bool is_calib;
    uint8_t dev_HW_id;
    QMap<uint32_t, ADE_cal> cal_data;
protected:
    QVariantMap curr_data;
//    QVariantMap cal_data;
signals:
    void signal_write_data(QByteArray data);
};

class widget_current : public QWidget
{
    Q_OBJECT

public:
    explicit widget_current(bool is_calib,QWidget *parent = 0);
    ~widget_current();
//    QVariantMap curr_data;
    model_current * mc;
    bool is_calib;
private slots:
    void on_pushButton_EF0A_clicked();
    void on_pushButton_ADE_read_clicked();
    void on_pushButton_ADE_write_clicked();
//    void on_pushButton_phase_calib_A_read_clicked();
//    void on_pushButton_phase_calib_B_read_clicked();
//    void on_pushButton_phase_calib_A_write_clicked();
//    void on_pushButton_phase_calib_B_write_clicked();
//    void on_pushButton_phase_calib_C_read_clicked();
//    void on_pushButton_phase_calib_C_write_clicked();
    void on_pushButton_display_read_clicked();
    void on_pushButton_display_write_clicked();
    void on_pushButton_set_Fast_DL_clicked();
    void on_pushButton_set_Time_clicked();
    void on_pushButton_rele_on_clicked();
    void on_pushButton_rele_off_clicked();
    void on_lineEdit_in_returnPressed();
    void on_pushButton_clicked();
    void on_lineEdit_out_returnPressed();

private:
    Ui::widget_current *ui;
signals:
    void signal_write_data(QByteArray data);
public slots:
    void slot_read_data(QByteArray data);
    void slot_connect(uint32_t server, uint32_t client, QByteArray pass);
};

#endif // WIDGET_CURRENT_H
