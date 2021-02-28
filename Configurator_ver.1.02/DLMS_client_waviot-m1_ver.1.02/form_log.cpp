#include "form_log.h"
#include "ui_form_log.h"

#include "QScrollBar"

Form_log::Form_log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_log)
{
    ui->setupUi(this);
}

Form_log::~Form_log()
{
    delete ui;
}

void Form_log::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
}

void Form_log::slot_log(QString str){
    QDateTime qdt = QDateTime::currentDateTime();
    ui->plainTextEdit->appendPlainText(qdt.toString("hh:mm:ss.zzz") + "  " + str);
    ui->plainTextEdit->verticalScrollBar()->setValue(ui->plainTextEdit->verticalScrollBar()->maximum());
}
