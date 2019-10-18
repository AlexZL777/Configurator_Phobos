#ifndef DIALOG_CHANGE_LOW_PASS_H
#define DIALOG_CHANGE_LOW_PASS_H

#include <QDialog>

namespace Ui {
class Dialog_change_low_pass;
}

class Dialog_change_low_pass : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_change_low_pass(QWidget *parent = nullptr);
    ~Dialog_change_low_pass();

private slots:

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::Dialog_change_low_pass *ui;
signals:
    void signal_write_data(QByteArray);
};

#endif // DIALOG_CHANGE_LOW_PASS_H
