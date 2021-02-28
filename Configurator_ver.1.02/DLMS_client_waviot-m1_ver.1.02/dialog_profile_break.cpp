#include "dialog_profile_break.h"
#include "ui_dialog_profile_break.h"

Dialog_profile_break::Dialog_profile_break(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_profile_break)
{
    ui->setupUi(this);
}

Dialog_profile_break::~Dialog_profile_break()
{
    delete ui;
}

void Dialog_profile_break::on_pushButton_clicked()
{
    close();
}
