#include "dialog_err_profil_spec.h"
#include "ui_dialog_err_profil_spec.h"

Dialog_err_profil_spec::Dialog_err_profil_spec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_err_profil_spec)
{
    ui->setupUi(this);
}

Dialog_err_profil_spec::~Dialog_err_profil_spec()
{
    delete ui;
}

void Dialog_err_profil_spec::on_pushButton_clicked()
{
    close();
}
