#include "dialog_insert_data_season.h"
#include "ui_dialog_insert_data_season.h"

dialog_insert_data_season::dialog_insert_data_season(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dialog_insert_data_season)
{
    ui->setupUi(this);
}

dialog_insert_data_season::~dialog_insert_data_season()
{
    delete ui;
}

void dialog_insert_data_season::on_pushButton_clicked()
{

}
