#ifndef DIALOG_ERROR_SN_H
#define DIALOG_ERROR_SN_H

#include <QDialog>

namespace Ui {
class Dialog_error_sn;
}

class Dialog_error_sn : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_error_sn(QWidget *parent = nullptr);
    ~Dialog_error_sn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_error_sn *ui;
};

#endif // DIALOG_ERROR_SN_H
