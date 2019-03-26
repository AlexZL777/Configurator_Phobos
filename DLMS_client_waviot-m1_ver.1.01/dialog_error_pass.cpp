#include "dialog_error_pass.h"
#include "ui_dialog_error_pass.h"

Dialog_error_pass::Dialog_error_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_error_pass)
{
    ui->setupUi(this);
}

Dialog_error_pass::~Dialog_error_pass()
{
    delete ui;
}

void Dialog_error_pass::on_pushButton_clicked()
{
    close();
}
