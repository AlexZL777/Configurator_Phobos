#include "dialog_err_date_seasons.h"
#include "ui_dialog_err_date_seasons.h"

Dialog_err_date_seasons::Dialog_err_date_seasons(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_err_date_seasons)
{
    ui->setupUi(this);
}

Dialog_err_date_seasons::~Dialog_err_date_seasons()
{
    delete ui;
}
