#ifndef DIALOG_ERR_DATE_SPEC_H
#define DIALOG_ERR_DATE_SPEC_H

#include <QDialog>

namespace Ui {
class Dialog_err_date_spec;
}

class Dialog_err_date_spec : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_err_date_spec(QWidget *parent = nullptr);
    ~Dialog_err_date_spec();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_err_date_spec *ui;
};

#endif // DIALOG_ERR_DATE_SPEC_H
