#include "dialog_disconnect.h"
#include "ui_dialog_disconnect.h"

Dialog_disconnect::Dialog_disconnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_disconnect)
{
    ui->setupUi(this);
}

Dialog_disconnect::~Dialog_disconnect()
{
    delete ui;
}

void Dialog_disconnect::on_pushButton_clicked()
{
    emit signal();
    close();
}
