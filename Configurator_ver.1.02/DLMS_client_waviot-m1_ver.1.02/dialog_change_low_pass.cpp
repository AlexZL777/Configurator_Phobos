#include "dialog_change_low_pass.h"
#include "ui_dialog_change_low_pass.h"
#include <Logger/Logger.h>

extern QByteArray pass_hi_level;

Dialog_change_low_pass::Dialog_change_low_pass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_change_low_pass)
{
    ui->setupUi(this);
}

Dialog_change_low_pass::~Dialog_change_low_pass()
{
    delete ui;
}

void Dialog_change_low_pass::on_buttonBox_rejected()
{
    close();
}

void Dialog_change_low_pass::on_buttonBox_accepted()
{
    ui->label_5->setText("");
    if ( ui->lineEdit->text() != ui->lineEdit_2->text() ){
        ui->label_5->setText("Ошибка! Введены разные значения в поля ввода нового пароля!");
        ui->label_5->setStyleSheet("QLabel {color : red}");
    }
    if ( ui->lineEdit_3->text() != pass_hi_level ){
        ui->label_5->setText("Ошибка! Введен неверный пароль Высокого уровня безопасности!");
        ui->label_5->setStyleSheet("QLabel {color : red}");
    }
    log_1 << "pass" << ui->lineEdit->text() << ui->lineEdit_2->text() << ui->lineEdit_3->text() << pass_hi_level;
    if ( ui->lineEdit->text() == ui->lineEdit_2->text() && ui->lineEdit_3->text() == pass_hi_level ){
        ui->label_5->setText("");
        QByteArray ba = QByteArray::fromHex("EF22");
        QByteArray ba1 = ui->lineEdit->text().toLocal8Bit();
        ba = ba.append(ba1);
        ba1 =  QByteArray::fromHex("0000000000000000000000000000000000000000");
        ba = ba.append(ba1);
        ba = ba.mid(0, 18);
        emit signal_write_data(ba);
        log_1 << "ba" << ba.toHex().toUpper();
        close();
    }
}
