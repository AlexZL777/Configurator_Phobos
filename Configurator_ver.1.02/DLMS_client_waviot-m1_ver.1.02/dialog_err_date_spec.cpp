#include "dialog_err_date_spec.h"
#include "ui_dialog_err_date_spec.h"

Dialog_err_date_spec::Dialog_err_date_spec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_err_date_spec)
{
    ui->setupUi(this);
}

Dialog_err_date_spec::~Dialog_err_date_spec()
{
    delete ui;
}

void Dialog_err_date_spec::on_pushButton_clicked()
{
    close();
}
