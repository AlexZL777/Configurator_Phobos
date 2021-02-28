#include "dialog_insert_date_season.h"
#include "ui_dialog_insert_date_season.h"

#include <Logger/Logger.h>
#include <QDate>
#include <QIntValidator>

Dialog_insert_date_season::Dialog_insert_date_season(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_insert_date_season)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator( new QIntValidator(1, 64, this) );
    ui->lineEdit_2->setValidator( new QIntValidator(1, 64, this) );
    ui->lineEdit_3->setValidator( new QIntValidator(1, 64, this) );
    ui->lineEdit_4->setValidator( new QIntValidator(1, 64, this) );
    ui->lineEdit_5->setValidator( new QIntValidator(1, 64, this) );
    ui->lineEdit_6->setValidator( new QIntValidator(1, 64, this) );
    ui->lineEdit_7->setValidator( new QIntValidator(1, 64, this) );
    connect( ui->pushButton, SIGNAL( clicked() ), SLOT( accept() ) );
}

Dialog_insert_date_season::~Dialog_insert_date_season()
{
    delete ui;
}


QDate Dialog_insert_date_season::getData()
{
    return ui->calendarWidget->selectedDate();
}

QHash<int,int> Dialog_insert_date_season::getprofile(){
    QHash<int,int> data;
    if (ui->lineEdit->text() != "" &&
        ui->lineEdit_2->text() != "" &&
        ui->lineEdit_3->text() != "" &&
        ui->lineEdit_4->text() != "" &&
        ui->lineEdit_5->text() != "" &&
        ui->lineEdit_6->text() != "" &&
        ui->lineEdit_7->text() != "")
    {
        data[0] = ui->lineEdit->text().toInt();
        data[1] = ui->lineEdit_2->text().toInt();
        data[2] = ui->lineEdit_3->text().toInt();
        data[3] = ui->lineEdit_4->text().toInt();
        data[4] = ui->lineEdit_5->text().toInt();
        data[5] = ui->lineEdit_6->text().toInt();
        data[6] = ui->lineEdit_7->text().toInt();
        return(data);
    }
    else return(data);
}

void Dialog_insert_date_season::on_pushButton_2_clicked()
{
    close();
}
