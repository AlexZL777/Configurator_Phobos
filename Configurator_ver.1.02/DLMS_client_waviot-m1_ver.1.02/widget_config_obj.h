#ifndef WIDGET_CONFIG_OBJ_H
#define WIDGET_CONFIG_OBJ_H

#include <QWidget>

namespace Ui {
class widget_config_obj;
}

class widget_config_obj : public QWidget
{
    Q_OBJECT

public:
    explicit widget_config_obj(QWidget *parent = 0);
    ~widget_config_obj();
private:
    Ui::widget_config_obj *ui;
signals:
    void signal_write_data(QByteArray data);
public slots:
    void slot_read_data(QByteArray data);
private slots:
    void on_pushButton_rele_read_clicked();
    void on_pushButton_rele_write_clicked();
};

#endif // WIDGET_CONFIG_OBJ_H
