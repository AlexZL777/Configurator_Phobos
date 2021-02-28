#include "widget_pulse_outputs.h"
#include "ui_widget_pulse_outputs.h"

#include <Logger/Logger.h>
#include <QJsonDocument>

#include "DLMS_obis_pack.h"
#include "DLMS_PDU.h"

#include <widget_info.h>

#include <QMessageBox>
#include <QLineEdit>
#include <QScrollArea>
#include <QPalette>

extern int count_bar;
bool pulse_write_bar;
extern int type_counter;
extern int ver_po[2];
extern uint32_t client_addr;
extern int type[2];
extern bool servis_pass;
extern bool servis_pass2;

widget_pulse_outputs::widget_pulse_outputs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_pulse_outputs)
{
    ui->setupUi(this);
    ui->gridLayout->setAlignment( Qt::AlignLeft );
    ui->comboBox_ADE_Pulse0_Energy_type->addItem("Активная", 0);
    ui->comboBox_ADE_Pulse0_Energy_type->addItem("Реактивная", 1);
  //  ui->comboBox_ADE_Pulse0_Energy_type->addItem("Активка В", 4);
  //  ui->comboBox_ADE_Pulse0_Energy_type->addItem("Реактивка В", 5);
  //  ui->comboBox_ADE_Pulse0_Energy_type->addItem("Часы", 0x81);
    ui->comboBox_ADE_Pulse1_Energy_type->addItem("Активная", 0);
    ui->comboBox_ADE_Pulse1_Energy_type->addItem("Реактивная", 1);
 //   ui->comboBox_ADE_Pulse1_Energy_type->addItem("Активка В", 4);
 //   ui->comboBox_ADE_Pulse1_Energy_type->addItem("Реактивка В", 5);
    ui->comboBox_ADE_Pulse1_Energy_type->addItem("Часы", 0x81);

    tmr_tout_pulse = new QTimer();
    tmr_t = new QTimer();
    connect(tmr_tout_pulse, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(tmr_t, SIGNAL(timeout()), this, SLOT(tmr_time()));
    connect( ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

//    if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
//        ui->horizontalSlider->setTracking(true);
//        ui->horizontalSlider->setEnabled(true);
//        ui->pushButton_2->setEnabled(true);
//        ui->pushButton_3->setEnabled(true);
//    }
//    if ( client_addr == 0x30 ){
//        ui->pushButton_4->setEnabled(true);
//        ui->pushButton_5->setEnabled(true);
//    }
    ui->horizontalSlider->setTracking(false);
    ui->horizontalSlider->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->label_10->setEnabled(false);
    ui->label_11->setEnabled(false);
    ui->label_14->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);
    ui->pushButton_14->setEnabled(false);
    ui->pushButton_15->setEnabled(false);
    ui->pushButton_16->setEnabled(false);
    ui->dateTimeEdit->setEnabled(false);
 //   ui->radioButton_10->setChecked(false);
 //   ui->radioButton_11->setChecked(false);
 //   ui->radioButton_12->setChecked(false);
 //   ui->radioButton_13->setChecked(false);
 //   ui->radioButton_14->setChecked(false);

    clickLabel1 = new ClickableLabel1;
    clickLabel2 = new ClickableLabel2;
    clickLabel3 = new ClickableLabel3;
    clickLabel4 = new ClickableLabel4;
    clickLabel5 = new ClickableLabel5;
    clickLabel6 = new ClickableLabel6;
    ui->verticalLayout_5->addWidget( clickLabel1 );
    ui->verticalLayout_5->addWidget( clickLabel2 );
    ui->verticalLayout_5->addWidget( clickLabel3 );
    ui->verticalLayout_5->addWidget( clickLabel4 );
    ui->verticalLayout_5->addWidget( clickLabel5 );
    ui->verticalLayout_5->addWidget( clickLabel6 );
    ui->verticalLayout_5->addStretch(10);
    clickLabel1->setText("Настройки импульсных выходов");
    clickLabel1->setStyleSheet(QString("font-size: %1px").arg(17));
    clickLabel2->setText("Выбор антенны");
    clickLabel2->setStyleSheet(QString("font-size: %1px").arg(17));
    clickLabel3->setText("Смена пароля");
    clickLabel3->setStyleSheet(QString("font-size: %1px").arg(17));
    clickLabel4->setText("Поправка точности хода часов");
    clickLabel4->setStyleSheet(QString("font-size: %1px").arg(17));
    clickLabel5->setText("Установка даты и времени");
    clickLabel5->setStyleSheet(QString("font-size: %1px").arg(17));
    clickLabel6->setText("Управление нагрузкой");
    clickLabel6->setStyleSheet(QString("font-size: %1px").arg(17));
    connect(clickLabel1, SIGNAL(clicked(int)), this, SLOT(clickLabel(int)));
    connect(clickLabel2, SIGNAL(clicked(int)), this, SLOT(clickLabel(int)));
    connect(clickLabel3, SIGNAL(clicked(int)), this, SLOT(clickLabel(int)));
    connect(clickLabel4, SIGNAL(clicked(int)), this, SLOT(clickLabel(int)));
    connect(clickLabel5, SIGNAL(clicked(int)), this, SLOT(clickLabel(int)));
    connect(clickLabel6, SIGNAL(clicked(int)), this, SLOT(clickLabel(int)));
    clickLabel(1);
}

widget_pulse_outputs::~widget_pulse_outputs()
{
    delete ui;
}

void widget_pulse_outputs::clickLabel(int n){
    switch (n) {
        case 1:{
            clickLabel1->setStyleSheet("QLabel { background-color : #C0C0C0; }");
            clickLabel2->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel3->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel4->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel5->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel6->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            //ПОКАЗАТЬ
            //Настройка импульсных выходов
            ui->widget->show();
//            ui->label->show();
//            ui->label_4_->show();ui->textEdit->show();ui->comboBox_ADE_Pulse0_Energy_type->show();ui->pushButton->show();
//            ui->label_3_->show();ui->textEdit_2->show();ui->comboBox_ADE_Pulse1_Energy_type->show();
            //СПРЯТАТЬ
            //выбор антенны
            ui->widget_2->hide();
//            ui->label_14->hide();
//            ui->pushButton_2->hide();ui->label_10->hide();ui->horizontalSlider->hide();ui->label_11->hide();ui->pushButton_3->hide();
            //Смена пароля
            ui->widget_3->hide();
//            ui->label_2->hide();
//            ui->pushButton_4->hide();ui->pushButton_5->hide();
            //Поправка точности хода часов
            ui->widget_4->hide();
//            ui->label_5->hide();
//            ui->pushButton_12->hide();ui->spinBox_4->hide();ui->pushButton_13->hide();
            //Установка даты и времени
            ui->widget_5->hide();
//            ui->label_21->hide();
//            ui->pushButton_14->hide();ui->dateTimeEdit->hide();ui->pushButton_15->hide();ui->pushButton_16->hide();
            //управление нагрузкой
            ui->widget_6->hide();
//            ui->label_19->hide();
//            ui->pushButton_9->hide();ui->label_18->hide();ui->pushButton_10->hide();
//            ui->label_20->hide();
//            ui->radioButton->hide();ui->label_3->hide();
//            ui->radioButton_2->hide();ui->label_4->hide();
//            ui->radioButton_3->hide();ui->label_6->hide();
//            ui->radioButton_4->hide();ui->label_7->hide();
//            ui->radioButton_5->hide();ui->label_8->hide();
//            ui->radioButton_6->hide();ui->label_9->hide();
//            ui->radioButton_7->hide();ui->label_12->hide();
//            ui->radioButton_8->hide();ui->label_13->hide();
//            ui->pushButton_11->hide();
//            ui->label_15->hide();ui->spinBox->hide();ui->pushButton_6->hide();
//            ui->label_16->hide();ui->spinBox_2->hide();ui->pushButton_7->hide();
//            ui->label_17->hide();ui->spinBox_3->hide();ui->pushButton_8->hide();
            break;
        }
        case 2:{
            clickLabel2->setStyleSheet("QLabel { background-color : #C0C0C0; }");
            clickLabel1->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel3->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel4->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel5->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel6->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            //ПОКАЗАТЬ
            //выбор антенны
            ui->widget_2->show();
//            ui->label_14->show();
//            ui->pushButton_2->show();ui->label_10->show();ui->horizontalSlider->show();ui->label_11->show();ui->pushButton_3->show();
            //СПРЯТАТЬ
            //Настройка импульсных выходов
            ui->widget->hide();
//            ui->label->hide();
//            ui->label_4_->hide();ui->textEdit->hide();ui->comboBox_ADE_Pulse0_Energy_type->hide();ui->pushButton->hide();
//            ui->label_3_->hide();ui->textEdit_2->hide();ui->comboBox_ADE_Pulse1_Energy_type->hide();
            //Смена пароля
            ui->widget_3->hide();
//            ui->label_2->hide();
//            ui->pushButton_4->hide();ui->pushButton_5->hide();
            //Поправка точности хода часов
            ui->widget_4->hide();
//            ui->label_5->hide();
//            ui->pushButton_12->hide();ui->spinBox_4->hide();ui->pushButton_13->hide();
            //Установка даты и времени
            ui->widget_5->hide();
//            ui->label_21->hide();
//            ui->pushButton_14->hide();ui->dateTimeEdit->hide();ui->pushButton_15->hide();ui->pushButton_16->hide();
            //управление нагрузкой
            ui->widget_6->hide();
//            ui->label_19->hide();
//            ui->pushButton_9->hide();ui->label_18->hide();ui->pushButton_10->hide();
//            ui->label_20->hide();
//            ui->radioButton->hide();ui->label_3->hide();
//            ui->radioButton_2->hide();ui->label_4->hide();
//            ui->radioButton_3->hide();ui->label_6->hide();
//            ui->radioButton_4->hide();ui->label_7->hide();
//            ui->radioButton_5->hide();ui->label_8->hide();
//            ui->radioButton_6->hide();ui->label_9->hide();
//            ui->radioButton_7->hide();ui->label_12->hide();
//            ui->radioButton_8->hide();ui->label_13->hide();
//            ui->pushButton_11->hide();
//            ui->label_15->hide();ui->spinBox->hide();ui->pushButton_6->hide();
//            ui->label_16->hide();ui->spinBox_2->hide();ui->pushButton_7->hide();
//            ui->label_17->hide();ui->spinBox_3->hide();ui->pushButton_8->hide();
            break;
        }
        case 3:{
            clickLabel3->setStyleSheet("QLabel { background-color : #C0C0C0; }");
            clickLabel1->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel2->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel4->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel5->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel6->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            //ПОКАЗАТЬ
            //Смена пароля
            ui->widget_3->show();
//            ui->label_2->show();
//            ui->pushButton_4->show();ui->pushButton_5->show();
            //СПРЯТАТЬ
            //Настройка импульсных выходов
            ui->widget->hide();
//            ui->label->hide();
//            ui->label_4_->hide();ui->textEdit->hide();ui->comboBox_ADE_Pulse0_Energy_type->hide();ui->pushButton->hide();
//            ui->label_3_->hide();ui->textEdit_2->hide();ui->comboBox_ADE_Pulse1_Energy_type->hide();
            //выбор антенны
            ui->widget_2->hide();
//            ui->label_14->hide();
//            ui->pushButton_2->hide();ui->label_10->hide();ui->horizontalSlider->hide();ui->label_11->hide();ui->pushButton_3->hide();
            //Поправка точности хода часов
            ui->widget_4->hide();
//            ui->label_5->hide();
//            ui->pushButton_12->hide();ui->spinBox_4->hide();ui->pushButton_13->hide();
            //Установка даты и времени
            ui->widget_5->hide();
//            ui->label_21->hide();
//            ui->pushButton_14->hide();ui->dateTimeEdit->hide();ui->pushButton_15->hide();ui->pushButton_16->hide();
            //управление нагрузкой
            ui->widget_6->hide();
//            ui->label_19->hide();
//            ui->pushButton_9->hide();ui->label_18->hide();ui->pushButton_10->hide();
//            ui->label_20->hide();
//            ui->radioButton->hide();ui->label_3->hide();
//            ui->radioButton_2->hide();ui->label_4->hide();
//            ui->radioButton_3->hide();ui->label_6->hide();
//            ui->radioButton_4->hide();ui->label_7->hide();
//            ui->radioButton_5->hide();ui->label_8->hide();
//            ui->radioButton_6->hide();ui->label_9->hide();
//            ui->radioButton_7->hide();ui->label_12->hide();
//            ui->radioButton_8->hide();ui->label_13->hide();
//            ui->pushButton_11->hide();
//            ui->label_15->hide();ui->spinBox->hide();ui->pushButton_6->hide();
//            ui->label_16->hide();ui->spinBox_2->hide();ui->pushButton_7->hide();
//            ui->label_17->hide();ui->spinBox_3->hide();ui->pushButton_8->hide();
            break;
        }
        case 4:{
            clickLabel4->setStyleSheet("QLabel { background-color : #C0C0C0; }");
            clickLabel1->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel2->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel3->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel5->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel6->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            //ПОКАЗАТЬ
            //Поправка точности хода часов
            ui->widget_4->show();
//            ui->label_5->show();
//            ui->pushButton_12->show();ui->spinBox_4->show();ui->pushButton_13->show();
            //СПРЯТАТЬ
            //Настройка импульсных выходов
            ui->widget->hide();
//            ui->label->hide();
//            ui->label_4_->hide();ui->textEdit->hide();ui->comboBox_ADE_Pulse0_Energy_type->hide();ui->pushButton->hide();
//            ui->label_3_->hide();ui->textEdit_2->hide();ui->comboBox_ADE_Pulse1_Energy_type->hide();
            //выбор антенны
            ui->widget_2->hide();
//            ui->label_14->hide();
//            ui->pushButton_2->hide();ui->label_10->hide();ui->horizontalSlider->hide();ui->label_11->hide();ui->pushButton_3->hide();
            //Смена пароля
            ui->widget_3->hide();
//            ui->label_2->hide();
//            ui->pushButton_4->hide();ui->pushButton_5->hide();
            //Установка даты и времени
            ui->widget_5->hide();
//            ui->label_21->hide();
//            ui->pushButton_14->hide();ui->dateTimeEdit->hide();ui->pushButton_15->hide();ui->pushButton_16->hide();
            //управление нагрузкой
            ui->widget_6->hide();
//            ui->label_19->hide();
//            ui->pushButton_9->hide();ui->label_18->hide();ui->pushButton_10->hide();
//            ui->label_20->hide();
//            ui->radioButton->hide();ui->label_3->hide();
//            ui->radioButton_2->hide();ui->label_4->hide();
//            ui->radioButton_3->hide();ui->label_6->hide();
//            ui->radioButton_4->hide();ui->label_7->hide();
//            ui->radioButton_5->hide();ui->label_8->hide();
//            ui->radioButton_6->hide();ui->label_9->hide();
//            ui->radioButton_7->hide();ui->label_12->hide();
//            ui->radioButton_8->hide();ui->label_13->hide();
//            ui->pushButton_11->hide();
//            ui->label_15->hide();ui->spinBox->hide();ui->pushButton_6->hide();
//            ui->label_16->hide();ui->spinBox_2->hide();ui->pushButton_7->hide();
//            ui->label_17->hide();ui->spinBox_3->hide();ui->pushButton_8->hide();
            break;
        }
        case 5:{
            clickLabel5->setStyleSheet("QLabel { background-color : #C0C0C0; }");
            clickLabel1->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel2->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel3->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel4->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel6->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            //ПОКАЗАТЬ
            //Установка даты и времени
            ui->widget_5->show();
//            ui->label_21->show();
//            ui->pushButton_14->show();ui->dateTimeEdit->show();ui->pushButton_15->show();ui->pushButton_16->show();
            //СПРЯТАТЬ
            //Настройка импульсных выходов
            ui->widget->hide();
//            ui->label->hide();
//            ui->label_4_->hide();ui->textEdit->hide();ui->comboBox_ADE_Pulse0_Energy_type->hide();ui->pushButton->hide();
//            ui->label_3_->hide();ui->textEdit_2->hide();ui->comboBox_ADE_Pulse1_Energy_type->hide();
            //выбор антенны
            ui->widget_2->hide();
//            ui->label_14->hide();
//            ui->pushButton_2->hide();ui->label_10->hide();ui->horizontalSlider->hide();ui->label_11->hide();ui->pushButton_3->hide();
            //Смена пароля
            ui->widget_3->hide();
//            ui->label_2->hide();
//            ui->pushButton_4->hide();ui->pushButton_5->hide();
            //Поправка точности хода часов
            ui->widget_4->hide();
//            ui->label_5->hide();
//            ui->pushButton_12->hide();ui->spinBox_4->hide();ui->pushButton_13->hide();
            //управление нагрузкой
            ui->widget_6->hide();
//            ui->label_19->hide();
//            ui->pushButton_9->hide();ui->label_18->hide();ui->pushButton_10->hide();
//            ui->label_20->hide();
//            ui->radioButton->hide();ui->label_3->hide();
//            ui->radioButton_2->hide();ui->label_4->hide();
//            ui->radioButton_3->hide();ui->label_6->hide();
//            ui->radioButton_4->hide();ui->label_7->hide();
//            ui->radioButton_5->hide();ui->label_8->hide();
//            ui->radioButton_6->hide();ui->label_9->hide();
//            ui->radioButton_7->hide();ui->label_12->hide();
//            ui->radioButton_8->hide();ui->label_13->hide();
//            ui->pushButton_11->hide();
//            ui->label_15->hide();ui->spinBox->hide();ui->pushButton_6->hide();
//            ui->label_16->hide();ui->spinBox_2->hide();ui->pushButton_7->hide();
//            ui->label_17->hide();ui->spinBox_3->hide();ui->pushButton_8->hide();
            break;
        }
        case 6:{
            clickLabel6->setStyleSheet("QLabel { background-color : #C0C0C0; }");
            clickLabel1->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel2->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel3->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel4->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            clickLabel5->setStyleSheet("QLabel { background-color : #FFFFFF; }");
            //ПОКАЗАТЬ
            //управление нагрузкой
            ui->widget_6->show();
//            ui->label_19->show();
//            ui->pushButton_9->show();ui->label_18->show();ui->pushButton_10->show();
//            ui->label_20->show();
//            ui->radioButton->show();ui->label_3->show();
//            ui->radioButton_2->show();ui->label_4->show();
//            ui->radioButton_3->show();ui->label_6->show();
//            ui->radioButton_4->show();ui->label_7->show();
//            ui->radioButton_5->show();ui->label_8->show();
//            ui->radioButton_6->show();ui->label_9->show();
//            ui->radioButton_7->show();ui->label_12->show();
//            ui->radioButton_8->show();ui->label_13->show();
//            ui->pushButton_11->show();
//            ui->label_15->show();ui->spinBox->show();ui->pushButton_6->show();
//            ui->label_16->show();ui->spinBox_2->show();ui->pushButton_7->show();
//            ui->label_17->show();ui->spinBox_3->show();ui->pushButton_8->show();
            //СПРЯТАТЬ
            //Настройка импульсных выходов
            ui->widget->hide();
//            ui->label->hide();
//            ui->label_4_->hide();ui->textEdit->hide();ui->comboBox_ADE_Pulse0_Energy_type->hide();ui->pushButton->hide();
//            ui->label_3_->hide();ui->textEdit_2->hide();ui->comboBox_ADE_Pulse1_Energy_type->hide();
            //выбор антенны
            ui->widget_2->hide();
//            ui->label_14->hide();
//            ui->pushButton_2->hide();ui->label_10->hide();ui->horizontalSlider->hide();ui->label_11->hide();ui->pushButton_3->hide();
            //Смена пароля
            ui->widget_3->hide();
//            ui->label_2->hide();
//            ui->pushButton_4->hide();ui->pushButton_5->hide();
            //Поправка точности хода часов
            ui->widget_4->hide();
//            ui->label_5->hide();
//            ui->pushButton_12->hide();ui->spinBox_4->hide();ui->pushButton_13->hide();
            //Установка даты и времени
            ui->widget_5->hide();
//            ui->label_21->hide();
//            ui->pushButton_14->hide();ui->dateTimeEdit->hide();ui->pushButton_15->hide();ui->pushButton_16->hide();
            break;
        }
    }
    ui->verticalLayout_2->addStretch(1);
}

ClickableLabel1::ClickableLabel1(const QString& text, QWidget* parent) : QLabel(parent){
}
ClickableLabel1::~ClickableLabel1(){
}
void ClickableLabel1::mousePressEvent(QMouseEvent* event){
    emit clicked(1);
}
ClickableLabel2::ClickableLabel2(const QString& text, QWidget* parent) : QLabel(parent){
}
ClickableLabel2::~ClickableLabel2(){
}
void ClickableLabel2::mousePressEvent(QMouseEvent* event){
    emit clicked(2);
}
ClickableLabel3::ClickableLabel3(const QString& text, QWidget* parent) : QLabel(parent){
}
ClickableLabel3::~ClickableLabel3(){
}
void ClickableLabel3::mousePressEvent(QMouseEvent* event){
    emit clicked(3);
}
ClickableLabel4::ClickableLabel4(const QString& text, QWidget* parent) : QLabel(parent){
}
ClickableLabel4::~ClickableLabel4(){
}
void ClickableLabel4::mousePressEvent(QMouseEvent* event){
    emit clicked(4);
}
ClickableLabel5::ClickableLabel5(const QString& text, QWidget* parent) : QLabel(parent){
}
ClickableLabel5::~ClickableLabel5(){
}
void ClickableLabel5::mousePressEvent(QMouseEvent* event){
    emit clicked(5);
}
ClickableLabel6::ClickableLabel6(const QString& text, QWidget* parent) : QLabel(parent){
}
ClickableLabel6::~ClickableLabel6(){
}
void ClickableLabel6::mousePressEvent(QMouseEvent* event){
    emit clicked(6);
}

void widget_pulse_outputs::setValue(int val){
    if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
        ui->horizontalSlider->setValue(val);
    }
    else{
        ui->horizontalSlider->setTracking(false);
        ui->horizontalSlider->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
//    if ( client_addr == 0x30 ){
//        ui->pushButton_4->setEnabled(true);
//        ui->pushButton_5->setEnabled(true);
//    }
//    else{
//        ui->pushButton_4->setEnabled(false);
//        ui->pushButton_5->setEnabled(false);
//    }
}

bool widget_pulse_outputs::transmitt(){
    return transmit;
}

void widget_pulse_outputs::timeout(){
    log_1 << "count_tout" << count_tout;
    if (count_tout < 2){
        count_tout++;
        transmit = true;
        if ( ant == 1 ) {
            emit signal_write_data_(QByteArray::fromHex("EF4405FFFFFF000000")); //Запрос: подключена внутр. или внеш. антенна счётчика
            tmr_tout_pulse->start(3000);
        }
        else if (bn_click){
            QByteArray arr = QByteArray::fromHex("EF17000000000000000000000000000000000000000000000000");
            uint8_t * buf = (uint8_t *)arr.data();
            buf += 2;
            uint32_t Pulse0_energy_type = ui->comboBox_ADE_Pulse0_Energy_type->currentData().toUInt();
            uint32_t Pulse1_energy_type = ui->comboBox_ADE_Pulse1_Energy_type->currentData().toUInt();
            QString s = ui->textEdit->toPlainText();
            uint32_t Pulse0_freq = s.toInt();
            s = ui->textEdit_2->toPlainText();
            uint32_t Pulse1_freq = s.toInt();
            *buf++ = Pulse0_energy_type;
            *buf++ = Pulse1_energy_type;
            *buf++ = (Pulse0_freq >> 0) & 0xFF;
            *buf++ = (Pulse0_freq >> 8) & 0xFF;
            *buf++ = (Pulse1_freq >> 0) & 0xFF;
            *buf++ = (Pulse1_freq >> 8) & 0xFF;
            arr = arr.mid(0, buf - (uint8_t *)arr.data());
            emit signal_write_data_(arr);
            tmr_tout_pulse->start(3000);
        }
        else emit signal_write_data_(QByteArray::fromHex("EF17"));
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider->setTracking(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_12->setEnabled(false);
        ui->pushButton_13->setEnabled(false);
        ui->pushButton_14->setEnabled(false);
        ui->pushButton_15->setEnabled(false);
        ui->pushButton_16->setEnabled(false);
        ui->dateTimeEdit->setEnabled(false);
    }
    else if ( count_tout == 2 ) {
        count_tout++;
        transmit = 0;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout_pulse->start(3000);
    }
    else if ( count_tout == 3 ) {
        count_tout++;
        transmit = 0;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout_pulse->start(6000);
    }
    else if ( count_tout == 4 ) {
        count_tout++;
        transmit = 0;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout_pulse->start(12000);
    }
    else if ( count_tout > 4 ) {
        transmit = false;
        tmr_tout_pulse->stop();
        emit signal_timeout_start (100);
        emit signal_disable_tab_kn(0, 1);
    }
}

void widget_pulse_outputs::slot_show_widget_pulse(){
    transmit = false;
    count_bar = 15;
    emit signal_bar(count_bar);
  //  clickLabel(1);
    if ( (ver_po[0] < 5 || type[0] == 1 || type[1] == 9) && client_addr != 0x30 && !servis_pass ){  //в режиме чтения
        ui->horizontalSlider->setTracking(false);
        ui->horizontalSlider->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->label_11->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_5->setEnabled(false);
        ui->spinBox_4->setEnabled(false);
        ui->pushButton_14->setEnabled(false);
        ui->pushButton_15->setEnabled(false);
        ui->pushButton_16->setEnabled(false);
        ui->dateTimeEdit->setEnabled(false);
        ui->pushButton_17->hide();
        ui->textEdit->setReadOnly(true);
        ui->textEdit_2->setReadOnly(true);
    }
    else {
        ui->label_10->setEnabled(true);
        ui->label_11->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->label_5->setEnabled(true);
        ui->pushButton_17->show();
    }
    if ( client_addr != 0x30 || !servis_pass ){  //в режиме чтения
        ui->spinBox_4->setEnabled(false);
        ui->pushButton_12->setEnabled(false);
        ui->pushButton_13->setEnabled(false);
        ui->pushButton_17->hide();
        ui->textEdit->setReadOnly(true);
        ui->textEdit_2->setReadOnly(true);
    }
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);
//    if ( client_addr == 0x30 ){
//        ui->pushButton_4->setEnabled(true);
//        ui->pushButton_5->setEnabled(true);
//    }
//    else{
//        ui->pushButton_4->setEnabled(false);
//        ui->pushButton_5->setEnabled(false);
//    }
}

void widget_pulse_outputs::slot_hide_widget_pulse(){
    //ui->textBrowser->setText("");
    //ui->textBrowser_2->setText("");
  //  hide();
    emit signal_bar(0);
    emit signal_min_window();
}

void widget_pulse_outputs::slot_disconnect(){
    tmr_t->stop();
    tmr_tout_pulse->stop();
    ui->textEdit->setText("");
    ui->textEdit_2->setText("");
    ui->horizontalSlider->setTracking(false);
    ui->horizontalSlider->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->label_10->setEnabled(false);
    ui->label_11->setEnabled(false);
    ui->label_14->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);
    ui->pushButton_14->setEnabled(false);
    ui->pushButton_15->setEnabled(false);
    ui->pushButton_16->setEnabled(false);
    ui->dateTimeEdit->setEnabled(false);
//    if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
//        ui->horizontalSlider->setEnabled(true);
//        ui->horizontalSlider->setTracking(true);
//        ui->pushButton_2->setEnabled(true);
//        ui->pushButton_3->setEnabled(true);
//    }
//    if ( client_addr == 0x30 ){
//        ui->pushButton->setEnabled(true);
//        ui->pushButton_4->setEnabled(true);
//        ui->pushButton_5->setEnabled(true);
//    }
}

void widget_pulse_outputs::slot_start_pulse(){
    transmit = true;
    emit signal_write_data_(QByteArray::fromHex("EF17"));
    disable_bn();
    count_tout = 0;
    transmit_next = 0;
    tmr_tout_pulse->start(3000);
}

void widget_pulse_outputs::slot_read_data_(QByteArray data){
    log_1 << "widget_pulse_output_пришёл ответ от счётчика";
    if (transmit){
        tmr_tout_pulse->stop();
        transmit = false;
        uint8_t buf_size = data.size();
        uint8_t * buf_start = (uint8_t *)data.data();
        uint8_t * buf = buf_start;
        if (buf_size < 1) {
            return;
        }
        uint8_t header = *buf++;
        if (header == 0xF5) {
            emit signal_disable_tab_kn(0, 1);
            if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
                ui->horizontalSlider->setEnabled(true);
                ui->horizontalSlider->setTracking(true);
                ui->pushButton_2->setEnabled(true);
                ui->pushButton_3->setEnabled(true);
                ui->spinBox_4->setEnabled(true);
                ui->pushButton_14->setEnabled(true);
                ui->pushButton_15->setEnabled(true);
                ui->pushButton_16->setEnabled(true);
                ui->dateTimeEdit->setEnabled(true);
            }
            if ( client_addr == 0x30 && servis_pass2 ){
                ui->spinBox_4->setEnabled(true);
                ui->pushButton_12->setEnabled(true);
                ui->pushButton_13->setEnabled(true);
                ui->pushButton_14->setEnabled(true);
                ui->pushButton_15->setEnabled(true);
                ui->pushButton_16->setEnabled(true);
                ui->dateTimeEdit->setEnabled(true);
                ui->textEdit->setReadOnly(false);
                ui->textEdit_2->setReadOnly(false);
            }
            if ( client_addr == 0x30 && servis_pass ){
                ui->spinBox_4->setEnabled(true);
                ui->pushButton_12->setEnabled(true);
                ui->pushButton_13->setEnabled(true);
                ui->pushButton_14->setEnabled(true);
                ui->pushButton_15->setEnabled(true);
                ui->pushButton_16->setEnabled(true);
                ui->dateTimeEdit->setEnabled(true);
            }
            if ( client_addr == 0x30 ){
                ui->pushButton->setEnabled(true);
                ui->pushButton_4->setEnabled(true);
                ui->pushButton_5->setEnabled(true);
                ui->pushButton_6->setEnabled(true);
                ui->pushButton_7->setEnabled(true);
                ui->pushButton_8->setEnabled(true);
                ui->pushButton_9->setEnabled(true);
                ui->pushButton_10->setEnabled(true);
                ui->pushButton_11->setEnabled(true);
            }
            count_bar = 100;
            emit signal_bar(count_bar);
        }
        if (header == 0xEF) {
            uint8_t sub_header = *buf++;
            switch (sub_header) {
            case 0x0C: {
                int time_correction  = *buf++;
                time_correction += (*buf++) << 8;
                time_correction += (*buf++) << 16;
                time_correction += (*buf++) << 24;
                log_1 << "time_correction" << time_correction;
                ui->spinBox_4->setValue((int)time_correction);
                emit signal_disable_tab_kn(0, 1);
                if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
                    ui->horizontalSlider->setEnabled(true);
                    ui->horizontalSlider->setTracking(true);
                    ui->pushButton_2->setEnabled(true);
                    ui->pushButton_3->setEnabled(true);
                    ui->spinBox_4->setEnabled(true);
                    ui->pushButton_14->setEnabled(true);
                    ui->pushButton_15->setEnabled(true);
                    ui->pushButton_16->setEnabled(true);
                    ui->dateTimeEdit->setEnabled(true);
                }
                if ( client_addr == 0x30 && servis_pass ){
                    ui->spinBox_4->setEnabled(true);
                    ui->pushButton_12->setEnabled(true);
                    ui->pushButton_13->setEnabled(true);
                    ui->pushButton_14->setEnabled(true);
                    ui->pushButton_15->setEnabled(true);
                    ui->pushButton_16->setEnabled(true);
                    ui->dateTimeEdit->setEnabled(true);
                }
                if ( client_addr == 0x30 && servis_pass2 ){
                    ui->spinBox_4->setEnabled(true);
                    ui->pushButton_12->setEnabled(true);
                    ui->pushButton_13->setEnabled(true);
                    ui->pushButton_14->setEnabled(true);
                    ui->pushButton_15->setEnabled(true);
                    ui->pushButton_16->setEnabled(true);
                    ui->dateTimeEdit->setEnabled(true);
                    ui->textEdit->setReadOnly(false);
                    ui->textEdit_2->setReadOnly(false);
                }
                if ( client_addr == 0x30 ){
                    ui->pushButton->setEnabled(true);
                    ui->pushButton_4->setEnabled(true);
                    ui->pushButton_5->setEnabled(true);
                    ui->pushButton_6->setEnabled(true);
                    ui->pushButton_7->setEnabled(true);
                    ui->pushButton_8->setEnabled(true);
                    ui->pushButton_9->setEnabled(true);
                    ui->pushButton_10->setEnabled(true);
                    ui->pushButton_11->setEnabled(true);
                }
                count_bar = 100;
                emit signal_bar(count_bar);
                break;
            }
                case 0x17: {
                    if (data.size() < 8) break;
                    uint32_t Pulse0_energy_type = *buf++;
                    uint32_t Pulse1_energy_type = *buf++;
                    uint32_t Pulse0_freq  = *buf++;
                    Pulse0_freq += (*buf++) << 8;
                    uint32_t Pulse1_freq  = *buf++;
                    Pulse1_freq += (*buf++) << 8;
                    ui->comboBox_ADE_Pulse0_Energy_type->setCurrentIndex(ui->comboBox_ADE_Pulse0_Energy_type->findData(Pulse0_energy_type));
                    ui->comboBox_ADE_Pulse1_Energy_type->setCurrentIndex(ui->comboBox_ADE_Pulse1_Energy_type->findData(Pulse1_energy_type));
                    QString str;
                    str = str.setNum(Pulse0_freq);
                    ui->textEdit->setText(str);
                    str = str.setNum(Pulse1_freq);
                    ui->textEdit_2->setText(str);
                    count_bar += 50;
                    emit signal_bar(count_bar);
                    transmit_next = 1;
                    transmit = true;
                    emit signal_write_data_(QByteArray::fromHex("ED4060030A03")); //Запрос состояния реле
                    count_tout = 0;
                    tmr_tout_pulse->start(3000);
                    break;
                }
                case 0x44: {
                //    log_1 << "transmittttttt2222222222222";
                    *buf++; *buf++;
                    uint32_t state_ant;
                    state_ant = *buf++; state_ant <<= 8;
                    state_ant+= *buf++;
                    if ( state_ant == 0) ui->horizontalSlider->setValue(0); //Вывод состояния внеш/внутр антенны счетчика
                    else ui->horizontalSlider->setValue(1);
                    if ( client_addr == 0x30 && servis_pass ){
                        ui->horizontalSlider->setEnabled(true);
                        ui->horizontalSlider->setTracking(true);
                        ui->pushButton_2->setEnabled(true);
                        ui->pushButton_3->setEnabled(true);
                        ui->spinBox_4->setEnabled(true);
                        ui->pushButton_12->setEnabled(true);
                        ui->pushButton_13->setEnabled(true);
                        ui->pushButton_14->setEnabled(true);
                        ui->pushButton_15->setEnabled(true);
                        ui->pushButton_16->setEnabled(true);
                        ui->dateTimeEdit->setEnabled(true);
                    }
                    if ( client_addr == 0x30 && servis_pass2 ){
                        ui->horizontalSlider->setEnabled(true);
                        ui->horizontalSlider->setTracking(true);
                        ui->pushButton_2->setEnabled(true);
                        ui->pushButton_3->setEnabled(true);
                        ui->spinBox_4->setEnabled(true);
                        ui->pushButton_12->setEnabled(true);
                        ui->pushButton_13->setEnabled(true);
                        ui->pushButton_14->setEnabled(true);
                        ui->pushButton_15->setEnabled(true);
                        ui->pushButton_16->setEnabled(true);
                        ui->dateTimeEdit->setEnabled(true);
                        ui->textEdit->setReadOnly(false);
                        ui->textEdit_2->setReadOnly(false);
                    }
                    if ( client_addr == 0x30 ){
                        ui->pushButton->setEnabled(true);
                        ui->pushButton_4->setEnabled(true);
                        ui->pushButton_5->setEnabled(true);
                        ui->pushButton_6->setEnabled(true);
                        ui->pushButton_7->setEnabled(true);
                        ui->pushButton_8->setEnabled(true);
                        ui->pushButton_9->setEnabled(true);
                        ui->pushButton_10->setEnabled(true);
                        ui->pushButton_11->setEnabled(true);
                    }
                   // count = 17;
                    tmr_tout_pulse->stop();
                    tmr_t->stop();
                    ant = 0;
                    emit signal_disable_tab_kn(0, 1);
                    count_bar = 100;
                    emit signal_bar(count_bar);
                    break;
                }
                default: break;
            }
        }
        else if (header == 0xED) {
            uint8_t sub_header = *buf++;
            switch (sub_header) {
                case 0x40: {
                    *buf++; *buf++; *buf++;
                    uint8_t sub_sub_header = *buf++;
                    if (sub_sub_header == 0x03){
                        *buf++;
                        uint8_t status_rele = *buf++;
                        if ( status_rele == 0x01 ){
                            ui->label_18->setText("Реле ВКЛЮЧЕНО");
                            ui->label_18->setStyleSheet("QLabel { background-color : #55ff7f; }");
                        }
                        else if ( status_rele == 0x02 ){
                            ui->label_18->setText("Реле ОТКЛЮЧЕНО");
                            ui->label_18->setStyleSheet("QLabel { background-color : #ffa2a4; }");
                        }
                        transmit_next = 2;
                        transmit = true;
                        emit signal_write_data_(QByteArray::fromHex("ED4060030A04")); //Запрос режима работы реле
                        count_tout = 0;
                        tmr_tout_pulse->start(3000);
                    }
                    else if (sub_sub_header == 0x04){
                        *buf++;
                        uint8_t reg_work = *buf++;
                        switch (reg_work) {
                            case 0x0: {
                                ui->radioButton->setChecked(true);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x01: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(true);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x02: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(true);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x03: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(true);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x04: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(true);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x05: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(true);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x06: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(true);
                                ui->radioButton_8->setChecked(false);break;
                            }
                            case 0x07: {
                                ui->radioButton->setChecked(false);
                                ui->radioButton_2->setChecked(false);
                                ui->radioButton_3->setChecked(false);
                                ui->radioButton_4->setChecked(false);
                                ui->radioButton_5->setChecked(false);
                                ui->radioButton_6->setChecked(false);
                                ui->radioButton_7->setChecked(false);
                                ui->radioButton_8->setChecked(true);break;
                            }
                        }
                        transmit_next = 3;
                        transmit = true;
                        emit signal_write_data_(QByteArray::fromHex("ED910003")); //Запрос максимума мощности
                        count_tout = 0;
                        tmr_tout_pulse->start(3000);
                    }
                    break;
                }
                case 0x91: {
                    *buf++;
                    uint8_t sub_sub_header = *buf++;
                    if (sub_sub_header == 0x03){

                        if ( *buf++ == 0x11 ) ui->spinBox->setValue((int)*buf++);
                        else {
                            uint32_t maxP  = *buf++ << 8;
                            maxP += *buf++;
                            ui->spinBox->setValue((int)maxP);
                        }
                        transmit_next = 4;
                        transmit = true;
                        emit signal_write_data_(QByteArray::fromHex("ED910006")); //Запрос времени до отключения
                        count_tout = 0;
                        tmr_tout_pulse->start(3000);
                    }
                    else if (sub_sub_header == 0x06){
                        if ( *buf++ == 0x11 ) ui->spinBox_2->setValue((int)*buf++);
                        else{
                            uint32_t t_do_otkl  = *buf++ << 8;
                            t_do_otkl += *buf++;
                            ui->spinBox_2->setValue((int)t_do_otkl);
                        }
                        transmit_next = 5;
                        transmit = true;
                        emit signal_write_data_(QByteArray::fromHex("ED910007")); //Запрос времени до включения
                        count_tout = 0;
                        tmr_tout_pulse->start(3000);
                    }
                    else if (sub_sub_header == 0x07){
                        if ( *buf++ == 0x11 ) ui->spinBox_3->setValue((int)*buf++);
                        else {
                            uint32_t t_do_vkl  = *buf++ << 8;
                            t_do_vkl += *buf++;
                            ui->spinBox_3->setValue((int)t_do_vkl);
                        }
                        emit signal_disable_tab_kn(0, 1);
                        if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
                            ui->horizontalSlider->setEnabled(true);
                            ui->horizontalSlider->setTracking(true);
                            ui->pushButton_2->setEnabled(true);
                            ui->pushButton_3->setEnabled(true);
                            ui->spinBox_4->setEnabled(true);
                            ui->pushButton_14->setEnabled(true);
                            ui->pushButton_15->setEnabled(true);
                            ui->pushButton_16->setEnabled(true);
                            ui->dateTimeEdit->setEnabled(true);
                        }
                        if ( client_addr == 0x30 && servis_pass ){
                            ui->spinBox_4->setEnabled(true);
                            ui->pushButton_12->setEnabled(true);
                            ui->pushButton_13->setEnabled(true);
                            ui->pushButton_14->setEnabled(true);
                            ui->pushButton_15->setEnabled(true);
                            ui->pushButton_16->setEnabled(true);
                            ui->dateTimeEdit->setEnabled(true);
                        }
                        if ( client_addr == 0x30 && servis_pass2 ){
                            ui->spinBox_4->setEnabled(true);
                            ui->pushButton_12->setEnabled(true);
                            ui->pushButton_13->setEnabled(true);
                            ui->pushButton_14->setEnabled(true);
                            ui->pushButton_15->setEnabled(true);
                            ui->pushButton_16->setEnabled(true);
                            ui->dateTimeEdit->setEnabled(true);
                            ui->textEdit->setReadOnly(false);
                            ui->textEdit_2->setReadOnly(false);
                        }
                        if ( client_addr == 0x30 ){
                            ui->pushButton->setEnabled(true);
                            ui->pushButton_4->setEnabled(true);
                            ui->pushButton_5->setEnabled(true);
                            ui->pushButton_6->setEnabled(true);
                            ui->pushButton_7->setEnabled(true);
                            ui->pushButton_8->setEnabled(true);
                            ui->pushButton_9->setEnabled(true);
                            ui->pushButton_10->setEnabled(true);
                            ui->pushButton_11->setEnabled(true);
                        }
                        count_bar = 100;
                        emit signal_bar(count_bar);
                    }
                    break;
                }
            }
        }
    }
}

void widget_pulse_outputs::on_pushButton_clicked(){
    emit signal_bar(0);
    QByteArray arr = QByteArray::fromHex("EF17000000000000000000000000000000000000000000000000");
    uint8_t * buf = (uint8_t *)arr.data();
    buf += 2;

    uint32_t Pulse0_energy_type = ui->comboBox_ADE_Pulse0_Energy_type->currentData().toUInt();
    uint32_t Pulse1_energy_type = ui->comboBox_ADE_Pulse1_Energy_type->currentData().toUInt();

    QString s = ui->textEdit->toPlainText();
    uint32_t Pulse0_freq = s.toInt();
    s = ui->textEdit_2->toPlainText();
    uint32_t Pulse1_freq = s.toInt();

    *buf++ = Pulse0_energy_type;
    *buf++ = Pulse1_energy_type;
    *buf++ = (Pulse0_freq >> 0) & 0xFF;
    *buf++ = (Pulse0_freq >> 8) & 0xFF;
    *buf++ = (Pulse1_freq >> 0) & 0xFF;
    *buf++ = (Pulse1_freq >> 8) & 0xFF;

    arr = arr.mid(0, buf - (uint8_t *)arr.data());

    pulse_write_bar = true;
    bn_click = true;
    transmit = true;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    emit signal_write_data_(arr);           //запись настроек импульсных выходов (светодиод, оптопара)
    emit signal_timeout_start(3000);
}

void widget_pulse_outputs::on_pushButton_2_clicked()
{
    transmit = true;
    emit signal_write_data_(QByteArray::fromHex("EF4405FFFFFF000000")); //Запрос: подключенна внутр. или внеш. антенна счётчика
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(3000);
}

void widget_pulse_outputs::on_pushButton_3_clicked()
{
    count_bar = 30;
    emit signal_bar(count_bar);
    QByteArray arr;
    transmit = true;
    disable_bn();
    ant = 1;
    int val = ui->horizontalSlider->value();
    if (val == 0){
        emit signal_write_data(QByteArray::fromHex("EF44C5FF0000000000")); //Переключение на встроенную антенну счётчика
    }
    if (val == 1){
        emit signal_write_data(QByteArray::fromHex("EF44C5FF0101000000")); //Переключение на внешнюю антенну счётчика
    }
    tmr_tout_pulse->start(1000);
}

void widget_pulse_outputs::on_pushButton_4_clicked()
{
    emit signal_dialog_low_pass();              //смена пароля низкого уровня безопасности
}

void widget_pulse_outputs::on_pushButton_5_clicked()
{
    emit signal_dialog_high_pass();             //смена пароля высокого уровня безопасности
}

void widget_pulse_outputs::on_pushButton_9_clicked()
{
    transmit = true;
    emit signal_write_data_(QByteArray::fromHex("ED4060030A031102")); //Команда: отключить реле
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_10_clicked()
{
    transmit = true;
    emit signal_write_data_(QByteArray::fromHex("ED4060030A031101")); //Команда: включить реле
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_11_clicked()
{
    int regim;
    if ( ui->radioButton->isChecked() ) regim = 0;
    else if ( ui->radioButton_2->isChecked() ) regim = 1;
    else if ( ui->radioButton_3->isChecked() ) regim = 2;
    else if ( ui->radioButton_4->isChecked() ) regim = 3;
    else if ( ui->radioButton_5->isChecked() ) regim = 4;
    else if ( ui->radioButton_6->isChecked() ) regim = 5;
    else if ( ui->radioButton_7->isChecked() ) regim = 6;
    else if ( ui->radioButton_8->isChecked() ) regim = 7;
    QByteArray arr = QByteArray::fromHex("ED4060030A0411");
    arr.append((char)regim);
    emit signal_write_data_(arr);                               //Команда: передать режим работы
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_6_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED91000312");
    uint32_t maxP = ui->spinBox->value();
    arr.append(maxP / 0x100);
    arr.append(maxP % 0x100);
    emit signal_write_data_(arr);                               //Команда: установить максимум мощности
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_7_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED91000612");
    int t_do_otkl = ui->spinBox_2->value();
    arr.append(t_do_otkl / 0x100);
    arr.append(t_do_otkl % 0x100);
    emit signal_write_data_(arr);                               //Команда: установить время до отключения
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_8_clicked()
{
    QByteArray arr = QByteArray::fromHex("ED91000712");
    int t_do_vkl = ui->spinBox_3->value();
    arr.append(t_do_vkl / 0x100);
    arr.append(t_do_vkl % 0x100);
    emit signal_write_data_(arr);                               //Команда: установить время до включения
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::disable_bn(){
    emit signal_disable_tab_kn(1, 1);
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setTracking(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_8->setEnabled(false);
    ui->pushButton_9->setEnabled(false);
    ui->pushButton_10->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_12->setEnabled(false);
    ui->pushButton_13->setEnabled(false);
}

void widget_pulse_outputs::on_pushButton_12_clicked()
{
    emit signal_write_data_(QByteArray::fromHex("EF0C"));
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_13_clicked()
{
    uint8_t resp_buffer[6];
    uint8_t * resp_data = resp_buffer;
    *resp_data++ = 0xEF;
    *resp_data++ = 0x0C;
    *resp_data++ = ((uint32_t)ui->spinBox_4->value() >>  0) & 0xFF;
    *resp_data++ = ((uint32_t)ui->spinBox_4->value() >>  8) & 0xFF;
    *resp_data++ = ((uint32_t)ui->spinBox_4->value() >> 16) & 0xFF;
    *resp_data++ = ((uint32_t)ui->spinBox_4->value() >> 24) & 0xFF;
    QByteArray arr;
    for (int n = 0; n < 6; ++n) {
        arr[n] = resp_buffer[n];
    }
    log_1 << "arr" << arr.toHex().toUpper();
    emit signal_write_data_(arr);
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_14_clicked()
{
    emit signal_write_data_PDU (QByteArray::fromHex("C001C100010000010000FF0200")); //Запрос системного времени счётчика
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
    tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::slot_data_PDU(QVariant(data)){
    if (transmit){
        tmr_tout_pulse->stop();
        transmit = false;
        count_bar = 100;
        emit signal_bar(count_bar);
        QByteArray arr;
        QVariantMap vm = data.toMap();
        if (vm.contains("date-time")) arr = QByteArray::fromHex(vm.value("date-time", "").toString().toLocal8Bit());
        COSEM_date_time_struct *cdt = (COSEM_date_time_struct *)arr.data();
        uint16_t y = (cdt->year_highbyte << 8) + cdt->year_lowbyte;
        QDateTime qdt(QDate(y, cdt->month, cdt->day_of_month),QTime(cdt->hour,cdt->minute,cdt->second));
        ui->dateTimeEdit->setDateTime(qdt);
        emit signal_disable_tab_kn(0, 1);
        if ( ver_po[0] > 4 && type[0] != 1 && type[1] != 9  && client_addr == 0x30 && servis_pass ){
            ui->horizontalSlider->setEnabled(true);
            ui->horizontalSlider->setTracking(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->spinBox_4->setEnabled(true);
            ui->pushButton_14->setEnabled(true);
            ui->pushButton_15->setEnabled(true);
            ui->pushButton_16->setEnabled(true);
            ui->dateTimeEdit->setEnabled(true);
        }
        if ( client_addr == 0x30 && servis_pass ){
            ui->spinBox_4->setEnabled(true);
            ui->pushButton_12->setEnabled(true);
            ui->pushButton_13->setEnabled(true);
            ui->pushButton_14->setEnabled(true);
            ui->pushButton_15->setEnabled(true);
            ui->pushButton_16->setEnabled(true);
            ui->dateTimeEdit->setEnabled(true);
        }
        if ( client_addr == 0x30 && servis_pass2 ){
            ui->spinBox_4->setEnabled(true);
            ui->pushButton_12->setEnabled(true);
            ui->pushButton_13->setEnabled(true);
            ui->pushButton_14->setEnabled(true);
            ui->pushButton_15->setEnabled(true);
            ui->pushButton_16->setEnabled(true);
            ui->dateTimeEdit->setEnabled(true);
            ui->textEdit->setReadOnly(false);
            ui->textEdit_2->setReadOnly(false);
        }
        if ( client_addr == 0x30 ){
            ui->pushButton->setEnabled(true);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
            ui->pushButton_6->setEnabled(true);
            ui->pushButton_7->setEnabled(true);
            ui->pushButton_8->setEnabled(true);
            ui->pushButton_9->setEnabled(true);
            ui->pushButton_10->setEnabled(true);
            ui->pushButton_11->setEnabled(true);
        }
        count_bar = 100;
        emit signal_bar(count_bar);
    }
}

void widget_pulse_outputs::on_pushButton_15_clicked()
{
    QDateTime d = ui->dateTimeEdit->dateTime();
    int dt = d.toTime_t() + d.offsetFromUtc();
    uint8_t resp_buffer[8];
    uint8_t * resp_data = resp_buffer;
    *resp_data++ = 0xF5;
    *resp_data++ = dt / 0x1000000;
    *resp_data++ = dt / 0x10000;
    *resp_data++ = dt / 0x100;
    *resp_data++ = dt % 0x100;
    *resp_data++ = 0x00;
    *resp_data++ = 0x00;
    *resp_data++ = 0x00;
    QByteArray arr;
    for (int n = 0; n < 8; ++n) {
        arr[n] = resp_buffer[n];
    }
    log_1 << "arr" << arr.toHex().toUpper();
    emit signal_write_data_(arr);
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
 //   tmr_tout_pulse->start(5000);
}

void widget_pulse_outputs::on_pushButton_16_clicked()
{
    uint dt = QDateTime::currentDateTime().offsetFromUtc();
    uint timestamp = dt + QDateTime::currentDateTime().toTime_t();

  //  log_1 << "tstamp" << timestamp;
    uint8_t resp_buffer[8];
    uint8_t * resp_data = resp_buffer;
    *resp_data++ = 0xF5;
    *resp_data++ = timestamp / 0x1000000;
    *resp_data++ = timestamp / 0x10000;
    *resp_data++ = timestamp / 0x100;
    *resp_data++ = timestamp % 0x100;
    *resp_data++ = 0x00;
    *resp_data++ = 0x00;
    *resp_data++ = 0x00;
    QByteArray arr;
    for (int n = 0; n < 8; ++n) {
        arr[n] = resp_buffer[n];
    }
 //   log_1 << "arr" << arr.toHex().toUpper();
    emit signal_write_data_(arr);
    transmit = true;
    count_tout = 0;
    disable_bn();
    count_bar = 30;
    emit signal_bar(count_bar);
}

void widget_pulse_outputs::on_pushButton_17_clicked()
{
    emit signal_show_form_log();
}
