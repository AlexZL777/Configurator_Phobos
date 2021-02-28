#ifndef DIALOG_CHANGE_HIGH_PASS_H
#define DIALOG_CHANGE_HIGH_PASS_H

#include <QDialog>

namespace Ui {
class Dialog_change_high_pass;
}

class Dialog_change_high_pass : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_change_high_pass(QWidget *parent = nullptr);
    ~Dialog_change_high_pass();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_change_high_pass *ui;
signals:
    void signal_write_data(QByteArray);
};

#endif // DIALOG_CHANGE_HIGH_PASS_H
