#include "dialog_error_sn.h"
#include "ui_dialog_error_sn.h"

Dialog_error_sn::Dialog_error_sn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_error_sn)
{
    ui->setupUi(this);
}

Dialog_error_sn::~Dialog_error_sn()
{
    delete ui;
}

void Dialog_error_sn::on_pushButton_clicked()
{
    close();
}
