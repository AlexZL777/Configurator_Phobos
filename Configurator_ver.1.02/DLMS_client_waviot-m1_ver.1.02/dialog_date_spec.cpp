#include "dialog_date_spec.h"
#include "ui_dialog_date_spec.h"

Dialog_date_spec::Dialog_date_spec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_date_spec)
{
    ui->setupUi(this);
    connect( ui->pushButton, SIGNAL( clicked() ), SLOT( accept() ) );
}

Dialog_date_spec::~Dialog_date_spec()
{
    delete ui;
}

QDate Dialog_date_spec::getData()
{
    return ui->calendarWidget->selectedDate();
}

int Dialog_date_spec::getprofile(){
    if (ui->lineEdit->text() != ""){
        return(ui->lineEdit->text().toInt());
    }
    else return(-1);
}
