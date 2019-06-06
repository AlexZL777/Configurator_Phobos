#include "dialog_error_profils_seasons.h"
#include "ui_dialog_error_profils_seasons.h"

Dialog_error_profils_seasons::Dialog_error_profils_seasons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_error_profils_seasons)
{
    ui->setupUi(this);
}

Dialog_error_profils_seasons::~Dialog_error_profils_seasons()
{
    delete ui;
}

void Dialog_error_profils_seasons::on_pushButton_clicked()
{
    close();
}
