#include "dialog_err_del_profil.h"
#include "ui_dialog_err_del_profil.h"

Dialog_err_del_profil::Dialog_err_del_profil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_err_del_profil)
{
    ui->setupUi(this);
}

Dialog_err_del_profil::~Dialog_err_del_profil()
{
    delete ui;
}

void Dialog_err_del_profil::on_pushButton_clicked()
{
    close();
}
