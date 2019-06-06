#include "widget_log_event.h"
#include "ui_widget_log_event.h"

#include <Logger/Logger.h>
#include <interface.h>
#include <QPushButton>
#include <QJsonDocument>
#include <QTableView>
#include <QHeaderView>
#include <QSpacerItem>
#include <QScrollArea>

extern int count_bar;

typedef enum {
    DLMS_ARCH_event_U       = 0,
    DLMS_ARCH_event_I       = 1,
    DLMS_ARCH_event_rele    = 2,
    DLMS_ARCH_event_prog    = 3,
    DLMS_ARCH_event_ext     = 4,
    DLMS_ARCH_event_com     = 5,
    DLMS_ARCH_event_access  = 6,
    DLMS_ARCH_event_diagnos = 7,
    DLMS_ARCH_event_tg_pow  = 8,
    DLMS_ARCH_event_quality = 9,
    DLMS_ARCH_event_IO      =10,
    DLMS_ARCH_telesignaling =11,
    DLMS_ARCH_profile_year  =12,
    DLMS_ARCH_profile_month =13,
    DLMS_ARCH_profile_day   =14,
    DLMS_ARCH_profile_hour  =15,
    DLMS_ARCH_profile_set   =16,
    DLMS_ARCH_profile_NONE =255,
} DLMS_ARCH_index;

widget_log_event::widget_log_event(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_log_event)
{
    ui->setupUi(this);

    transmit = false;

    tmr_t_out = new QTimer();
    connect(tmr_t_out, SIGNAL(timeout()), this, SLOT(timeout()));
    setLayout( &mainLayout );

    radio1->setText("считать все журналы событий");
    mainLayout.addWidget( radio1  );
    mainLayout.setAlignment( radio1, Qt::AlignCenter);
    radio2->setText("выбрать журнал событий для считывания");
    mainLayout.addWidget( radio2 );
    mainLayout.setAlignment( radio2, Qt::AlignCenter);
    connect(radio1, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(radio2, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));


    combo->addItem("События, связанные с напряжением", 1);
    combo->addItem("События, связанные с током", 2);
    combo->addItem("События, связанные с вкл./выкл. счётчика, коммутации реле нагрузки", 3);
    combo->addItem("События программирования параметров счётчика", 4);
    combo->addItem("События внешних воздействий", 5);
    combo->addItem("Коммуникационные события", 6);
    combo->addItem("События контроля доступа", 7);
    combo->addItem("Журнал самодиагностики", 8);
    combo->addItem("Превышение реактивной мощности (тангенса сети)", 9);
    combo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    type_data = combo->currentData().toUInt();
    mainLayout.addWidget( combo );
    mainLayout.setAlignment(combo, Qt::AlignCenter);

    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCombo(int)));

    QVBoxLayout *sLayout = new QVBoxLayout();

    label->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label );
 //   label->hide();

    m_view_U = new QTableView;
    m_view_U->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
  //  m_view_U->resizeColumnsToContents();
    m_view_U->verticalHeader()->hide();
    m_view_U->setModel( m_model_U = new TModel_U );
    sLayout->addWidget( m_view_U );
 //   m_view_U->hide();

    label2->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label2 );
//    label2->hide();

    m_view_I = new QTableView;
    m_view_I->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_I->verticalHeader()->hide();
    m_view_I->setModel( m_model_I = new TModel_I );
    sLayout->addWidget( m_view_I );
 //   m_view_I->hide();

    label3->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label3 );
//    label3->hide();

    m_view_rele = new QTableView;
    m_view_rele->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_rele->verticalHeader()->hide();
    m_view_rele->setModel( m_model_rele = new TModel_rele );
    sLayout->addWidget( m_view_rele );
//    m_view_rele->hide();

    label4->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label4 );
 //   label4->hide();

    m_view_prog = new QTableView;
    m_view_prog->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_prog->verticalHeader()->hide();
    m_view_prog->setModel( m_model_prog = new TModel_prog );
    sLayout->addWidget( m_view_prog );
//    m_view_prog->hide();

    label5->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label5 );
 //   label5->hide();

    m_view_ext = new QTableView;
    m_view_ext->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_ext->verticalHeader()->hide();
    m_view_ext->setModel( m_model_ext = new TModel_ext );
    sLayout->addWidget( m_view_ext );
//    m_view_ext->hide();

    label6->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label6 );
 //   label6->hide();

    m_view_com = new QTableView;
    m_view_com->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_com->verticalHeader()->hide();
    m_view_com->setModel( m_model_com = new TModel_com );
    sLayout->addWidget( m_view_com );
//    m_view_com->hide();

    label7->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label7 );
//    label7->hide();

    m_view_access = new QTableView;
    m_view_access->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_access->verticalHeader()->hide();
    m_view_access->setModel( m_model_access = new TModel_access );
    sLayout->addWidget( m_view_access );
  //  m_view_access->hide();

    label8->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label8 );
//    label8->hide();

    m_view_diagnos = new QTableView;
    m_view_diagnos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );

    m_view_diagnos->verticalHeader()->hide();
    m_view_diagnos->setModel( m_model_diagnos = new TModel_diagnos );
    sLayout->addWidget( m_view_diagnos );
 //   m_view_diagnos->hide();

    label9->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label9 );
  //  label9->hide();

    m_view_tg_pow = new QTableView;
    m_view_tg_pow->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_tg_pow->verticalHeader()->hide();
    m_view_tg_pow->setModel( m_model_tg_pow = new TModel_tg_pow );
    sLayout->addWidget( m_view_tg_pow );
 //   m_view_tg_pow->hide();

 //   sLayout->setMargin(0);
 //   sLayout->setSpacing(0);
 //   sLayout->setSizeConstraint(QLayout::SetMaximumSize);
 //  sLayout->setGeometry();

    QWidget *workSpace = new QWidget();
    workSpace->setLayout( sLayout );
    QSize AdjustSize = workSpace->size()*1.5;
    AdjustSize.height();
    workSpace->setMinimumSize(AdjustSize);
    QScrollArea * scrollArea =  new  QScrollArea;
    scrollArea->setWidget(workSpace);

    mainLayout.addWidget( scrollArea );
    radio1->setChecked(true);
    radio = true;
  //  mainLayout.addStretch();

    n_set_data = -1;
    n_set_data_max = 0;
}

widget_log_event::~widget_log_event()
{
    delete ui;
}

bool widget_log_event::transmitt(){
    return transmit;
}

void widget_log_event::slotCombo(int index){
    type_data = combo->currentData().toUInt();
    m_view_U->hide();
    label->hide();
    m_view_I->hide();
    label2->hide();
    m_view_rele->hide();
    label3->hide();
    m_view_prog->hide();
    label4->hide();
    m_view_ext->hide();
    label5->hide();
    m_view_com->hide();
    label6->hide();
    m_view_access->hide();
    label7->hide();
    m_view_diagnos->hide();
    label8->hide();
    m_view_tg_pow->hide();
    label9->hide();
    switch (type_data) {
        case 1: { //event_U
            label->show();
            m_view_U->show();
            m_view_U->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 2: { //event_I
            label2->show();
            m_view_I->show();
            m_view_I->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 3: { //event_rele
            label3->show();
            m_view_rele->show();
            m_view_rele->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 4: { //event_prog
            label4->show();
            m_view_prog->show();
            m_view_prog->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 5: { //event_ext
            label5->show();
            m_view_ext->show();
            m_view_ext->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 6: { //event_com
            label6->show();
            m_view_com->show();
            m_view_com->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 7: { //event_access
            label7->show();
            m_view_access->show();
            m_view_access->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 8: { //event_diagnos
            label8->show();
            m_view_diagnos->show();
            m_view_diagnos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        case 9: { //event_tg_pow
            label9->show();
            m_view_tg_pow->show();
            m_view_tg_pow->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
        }
        default: {
            transmit = false;
            break;
        }
    }
}

void widget_log_event::slotRadioToggled(bool value){
    if (!value) return;
    m_model_U->removeTable();
    m_model_I->removeTable();
    m_model_rele->removeTable();
    m_model_prog->removeTable();
    m_model_ext->removeTable();
    m_model_com->removeTable();
    m_model_access->removeTable();
    m_model_diagnos->removeTable();
    m_model_tg_pow->removeTable();
    if ( radio1->isChecked()) {
        radio = true;
        combo->hide();
        label->show();
        m_view_U->show();
        m_view_U->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label2->show();
        m_view_I->show();
        m_view_I->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label3->show();
        m_view_rele->show();
        m_view_rele->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label4->show();
        m_view_prog->show();
        m_view_prog->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label5->show();
        m_view_ext->show();
        m_view_ext->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label6->show();
        m_view_com->show();
        m_view_com->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label7->show();
        m_view_access->show();
        m_view_access->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label8->show();
        m_view_diagnos->show();
        m_view_diagnos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        label9->show();
        m_view_tg_pow->show();
        m_view_tg_pow->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    }
    else if ( radio2->isChecked()) {
        radio = false;
        combo->show();
        m_view_U->hide();
        label->hide();
        m_view_I->hide();
        label2->hide();
        m_view_rele->hide();
        label3->hide();
        m_view_prog->hide();
        label4->hide();
        m_view_ext->hide();
        label5->hide();
        m_view_com->hide();
        label6->hide();
        m_view_access->hide();
        label7->hide();
        m_view_diagnos->hide();
        label8->hide();
        m_view_tg_pow->hide();
        label9->hide();
        switch (type_data) {
            case 1: { //event_U
                label->show();
                m_view_U->show();
                m_view_U->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 2: { //event_I
                label2->show();
                m_view_I->show();
                m_view_I->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 3: { //event_rele
                label3->show();
                m_view_rele->show();
                m_view_rele->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 4: { //event_prog
                label4->show();
                m_view_prog->show();
                m_view_prog->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 5: { //event_ext
                label5->show();
                m_view_ext->show();
                m_view_ext->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 6: { //event_com
                label6->show();
                m_view_com->show();
                m_view_com->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 7: { //event_access
                label7->show();
                m_view_access->show();
                m_view_access->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 8: { //event_diagnos
                label8->show();
                m_view_diagnos->show();
                m_view_diagnos->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            case 9: { //event_tg_pow
                label9->show();
                m_view_tg_pow->show();
                m_view_tg_pow->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );break;
            }
            default: {
                transmit = false;
                break;
            }
        }

    }
}

void widget_log_event::slot_read_log_event(){
    if (n_set_data > -1 && n_set_data_max > 0) {
        count_tout = 0;
        tmr_t_out->start(3000);
        set_request_data( type, (uint32_t)n_set_data, n_set_data_max);
    }
    else{
        count_tout = 0;
        transmit = true;
        n_set_data = -1;
        n_set_data_max = 0;
        radio1->setEnabled(false);
        radio2->setEnabled(false);
        combo->setEnabled(false);
        m_model_U->removeTable();
        m_model_I->removeTable();
        m_model_rele->removeTable();
        m_model_prog->removeTable();
        m_model_ext->removeTable();
        m_model_com->removeTable();
        m_model_access->removeTable();
        m_model_diagnos->removeTable();
        m_model_tg_pow->removeTable();
        if (radio){
            all_data = true;
            emit signal_write_data(QByteArray::fromHex("EF0F00"));
            count_view = 0;
        }
        else{
            all_data = false;
            type_data = combo->currentData().toUInt();
            switch (type_data) {
                case 1: { //event_U
                    emit signal_write_data(QByteArray::fromHex("EF0F00"));break;
                }
                case 2: { //event_I
                    emit signal_write_data(QByteArray::fromHex("EF0F01"));break;
                }
                case 3: { //event_rele
                    emit signal_write_data(QByteArray::fromHex("EF0F02"));break;
                }
                case 4: { //event_prog
                    emit signal_write_data(QByteArray::fromHex("EF0F03"));break;
                }
                case 5: { //event_ext
                    emit signal_write_data(QByteArray::fromHex("EF0F04"));break;
                }
                case 6: { //event_com
                    emit signal_write_data(QByteArray::fromHex("EF0F05"));break;
                }
                case 7: { //event_access
                    emit signal_write_data(QByteArray::fromHex("EF0F06"));break;
                }
                case 8: { //event_diagnos
                    emit signal_write_data(QByteArray::fromHex("EF0F07"));break;
                }
                case 9: { //event_tg_pow
                    emit signal_write_data(QByteArray::fromHex("EF0F08"));break;
                }
                default: {
                    transmit = false;
                    break;
                }
            }
        }
    }
}

void widget_log_event::slot_log_event_read(QByteArray data){
    if (transmit){
        transmit = false;
    //    log_1 << "data_log" << data.toHex().toUpper();
        uint8_t * buf_start = (uint8_t *)data.data();
        uint8_t * buf = buf_start;
        uint8_t header = *buf++;
        if (header == 0xEF) parse_arch(data);
        else {
            parse_data_arch(data);
        }
    }
}

void widget_log_event::slot_log_event_empty_arr(){
    if (transmit){
        transmit = false;
        Parser_ul_event ul_event;
        count_tout = 0;
        data_arch(0, 0, 0, 0, 0);
    }
}

OBIS obis(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F)
{
    OBIS obis;
    obis.A = A;
    obis.B = B;
    obis.C = C;
    obis.D = D;
    obis.E = E;
    obis.F = F;
    return obis;
}

OBIS obis(uint8_t C, uint8_t D, uint8_t E)
{
    return obis( 0, 0, C, D, E, 255 );
}

void widget_log_event::set_request_data(uint32_t type, uint32_t index, uint32_t data_max){
    QByteArray arr = QByteArray(127+2, 0);
    uint8_t * drbuffer_head = (uint8_t *)arr.data();
    *drbuffer_head++ = 0xEF;
    *drbuffer_head++ = 0x10;
    uint32_t val = type;    //тип архива
    *drbuffer_head++ = (val >> 0) & 0xFF;
    val = (uint32_t)n_set_buf[data_max - index]; //индекс записи
    log_1 << "val" << val;
    val = val << 4;
    *drbuffer_head++ = (val >> 8) & 0xFF;
    *drbuffer_head++ = (val >> 0) & 0xFF;
    arr = arr.mid(0, drbuffer_head - (uint8_t *)arr.data());
    transmit = true;
    emit signal_write_data(arr);
    tmr_t_out->start(1000);
    emit signal_timeout_start(5000);
}

void widget_log_event::slot_disconnect(){
    tmr_t_out->stop();
    n_set_data = -1;
    n_set_data_max = 0;
    m_model_U->removeTable();
    m_model_I->removeTable();
    m_model_rele->removeTable();
    m_model_prog->removeTable();
    m_model_ext->removeTable();
    m_model_com->removeTable();
    m_model_access->removeTable();
    m_model_diagnos->removeTable();
    m_model_tg_pow->removeTable();
    m_model_U->clear_m_data();
    m_model_I->clear_m_data();
    m_model_rele->clear_m_data();
    m_model_prog->clear_m_data();
    m_model_ext->clear_m_data();
    m_model_com->clear_m_data();
    m_model_access->clear_m_data();
    m_model_diagnos->clear_m_data();
    m_model_tg_pow->clear_m_data();
    vmap_U.clear();
    vmap_I.clear();
    vmap_rele.clear();
    vmap_prog.clear();
    vmap_ext.clear();
    vmap_com.clear();
    vmap_access.clear();
    vmap_diagnos.clear();
    vmap_tg_pow.clear();
    radio1->setEnabled(true);
    radio2->setEnabled(true);
    combo->setEnabled(true);
}

void widget_log_event::parse_arch(QByteArray arr){
    uint8_t * buf_start = (uint8_t *)arr.data();
    uint8_t * buf = buf_start;
    uint8_t header = *buf++;
    int buf_size = arr.size();
    switch (header) {
        case 0xEF: {
            uint8_t sub_header = *buf++;
            switch (sub_header) {
                case 0x0F: { // arch index
                    if (buf_size < 20) {
                        QVariantMap vmap;
                        uint16_t val16;
                        val16 = *buf++;
                        vmap.insert("index", val16);
                        type = val16;
                        val16 = *buf++;
                        vmap.insert("rec_size", val16);
                        val16 = *buf++; val16 <<= 8; val16 += *buf++;
                        vmap.insert("count_max", val16);
                        uint16_t count_max = val16;
                        val16 = *buf++; val16 <<= 8; val16 += *buf++;
                        vmap.insert("index_send", val16);
                        val16 = *buf++; val16 <<= 8; val16 += *buf++;
                        vmap.insert("index_head", val16);
                        uint16_t index_head = val16;
                        val16 = *buf++; val16 <<= 8; val16 += *buf++;
                        vmap.insert("index_last", val16);
                        val16 = *buf++; val16 <<= 8; val16 += *buf++;
                        vmap.insert("sec_before_send_max", val16);
                        val16 = *buf++; val16 <<= 8; val16 += *buf++;
                        vmap.insert("sec_before_send", val16);
                        log_1 << "111" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
                        n_set_data = count_max-1;
                        n_set_data_max = count_max-1;
                    //    log_1 << "n_set_data" << n_set_data;
                    //    log_1 << "index_head" << index_head;
                        uint16_t index_head_t = index_head;
                        for (int n = 0; n < index_head; ++n) {
                            n_set_buf[n] = --index_head_t;
                            log_1 << "n" << n << n_set_buf[n];
                        }
                        uint16_t count_max_t = count_max;
                        for (int n = index_head; n < count_max; ++n) {
                            n_set_buf[n] = --count_max_t;
                          //  log_1 << "n" << n << n_set_buf[n];
                        }
                        set_request_data(type, (uint32_t)n_set_data, n_set_data_max);
                        progresbar = 100/n_set_data_max;
                        if (progresbar < 1){
                            intermediate = n_set_data_max/100 + 1;
                            dec_intermediate = intermediate;
                            fl_intermediate = true;
                            count_bar = 100 - (n_set_data_max/intermediate);
                           // log_1 << (n_set_data%100)/intermediate << intermediate << dec_intermediate;
                        }
                        else {
                            fl_intermediate = false;
                            count_bar = 100 - (progresbar*n_set_data_max);
                        }
                        vl.clear();
                    } else {
                        QVariantList vlist;
                        while (buf - buf_start + 8 < buf_size) {
                            QVariantMap vmap;
                            uint16_t val16;
                            val16 = *buf++;
                            vmap.insert("index", val16);
                            val16 = *buf++;
                            vmap.insert("rec_size", val16);
                            val16 = *buf++; val16 <<= 8; val16 += *buf++;
                            vmap.insert("count_max", val16);
                            val16 = *buf++; val16 <<= 8; val16 += *buf++;
                            vmap.insert("index_send", val16);
                            val16 = *buf++; val16 <<= 8; val16 += *buf++;
                            vmap.insert("index_head", val16);
                            vlist.append(vmap);
                        }
                     //   log_1 << "222" << qPrintable(QJsonDocument::fromVariant(vlist).toJson(QJsonDocument::Indented));
                    }
                    break;
                }
            }
        }
    }
}

void widget_log_event::parse_data_arch(QByteArray data){
    count_tout = 0;
//    if (buf_size < 1 + 2 + 1 + 4) {
//        break;
//    }
    int buf_size = data.size();
    uint8_t * buf_start = (uint8_t *)data.data();
    uint8_t * buf = buf_start;
    buf++;
    uint16_t index_send;
    uint16_t index_head;
    index_send = *buf++;
    index_send <<= 4;
    index_head = *buf++;
    index_send += (index_head >> 4) & 0xF;
    index_head &= 0xF;
    uint8_t profile_event = *buf++;
    uint32_t timework;
    timework = *buf++; timework <<= 8;
    timework+= *buf++; timework <<= 8;
    timework+= *buf++; timework <<= 8;
    timework+= *buf++;
    uint32_t timestamp_first = 0;
    Parser_ul_event ul_event;
    switch (profile_event) {
    case DLMS_ARCH_event_U: {
        while (buf - buf_start + 5 <= buf_size) {
            uint32_t timestamp;
            timestamp = *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++;
            uint8_t event = *buf++;
            uint16_t  U = *buf++;  U <<= 8;  U += *buf++;
            uint16_t dU = *buf++; dU <<= 8; dU += *buf++;
            if (!timestamp_first) timestamp_first = timestamp;
            ul_event.ts = timestamp;
            ul_event.work = timework + (timestamp - timestamp_first);
            ul_event.event = event;
            ul_event.obis = obis(99, 98, profile_event);
            ul_event.event_ext.insert(obis(12, 7, 0), U);
            ul_event.event_ext.insert(obis(12, 7, 4), dU);
            ul_event.index = index_send++;
            ul_event.index_ext = index_head;
        }
    //    log_1 << buf - buf_start + 5 << buf_size;
        break;
    }
    case DLMS_ARCH_event_I:
    case DLMS_ARCH_event_rele:
    case DLMS_ARCH_event_ext:
    case DLMS_ARCH_event_access:
    case DLMS_ARCH_event_diagnos:
    case DLMS_ARCH_event_tg_pow:
    case DLMS_ARCH_event_quality: {
        while (buf - buf_start + 5 <= buf_size) {
            uint32_t timestamp;
            timestamp = *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++;
            uint8_t event = *buf++;
            if (!timestamp_first) timestamp_first = timestamp;
            ul_event.ts = timestamp;
            ul_event.work = timework + (timestamp - timestamp_first);
            ul_event.event = event;
            ul_event.obis = obis(99, 98, profile_event);
            ul_event.index = index_send++;
            ul_event.index_ext = index_head;
        //    res_ul.ul_events << ul_event;
        }
        break;
    }
    case DLMS_ARCH_event_IO: {
        while (buf - buf_start + 5 <= buf_size) {
            uint32_t timestamp;
            timestamp = *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++;
            uint16_t state = *buf++; state <<= 8;
            state += *buf++;
            if (!timestamp_first) timestamp_first = timestamp;
            ul_event.ts = timestamp;
            ul_event.work = timework + (timestamp - timestamp_first);
            ul_event.event = 0;
            ul_event.obis = obis(99, 98, profile_event);
            ul_event.event_ext.insert(obis(96, 3, 0), state);
            ul_event.index = index_send++;
            ul_event.index_ext = index_head;
        //    res_ul.ul_events << ul_event;
        }
        break;
    }
    case DLMS_ARCH_event_prog: {
        while (buf - buf_start + 5 <= buf_size) {
            uint32_t timestamp;
            timestamp = *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++;
            uint8_t event = *buf++;
            uint8_t res = *buf++;
            if (!timestamp_first) timestamp_first = timestamp;
            ul_event.ts = timestamp;
            ul_event.work = timework + (timestamp - timestamp_first);
            ul_event.event = event;
            ul_event.obis = obis(99, 98, profile_event);
            ul_event.event_ext.insert(obis(96, 12, 4), res);
            ul_event.index = index_send++;
            ul_event.index_ext = index_head;
        //    res_ul.ul_events << ul_event;
        }
        break;
    }
    case DLMS_ARCH_event_com:
    case DLMS_ARCH_telesignaling: {
        while (buf - buf_start + 5 <= buf_size) {
            uint32_t timestamp;
            timestamp = *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++;
            uint8_t event = *buf++;
            uint8_t channel = *buf++;
            uint8_t addr = *buf++;
            if (!timestamp_first) timestamp_first = timestamp;
            ul_event.ts = timestamp;
            ul_event.work = timework + (timestamp - timestamp_first);
            ul_event.event = event;
            ul_event.obis = obis(99, 98, profile_event);
            if (profile_event == DLMS_ARCH_event_com) {
                ul_event.event_ext.insert(obis(96, 12, 4), channel);
                ul_event.event_ext.insert(obis(96, 12, 6), addr);
            }
            if (profile_event == DLMS_ARCH_telesignaling) {
                ul_event.event_ext.insert(obis(96, 12, 2), channel); // Срабатывание силового реле
                ul_event.event_ext.insert(obis(96, 12, 4), addr); // Внешних воздействий
            }
            ul_event.index = index_send++;
            ul_event.index_ext = index_head;
      //       res_ul.ul_events << ul_event;
        }
        break;
    }
    default: {
        break;
    }
    }
    data_arch(ul_event.ts, ul_event.work, ul_event.index, ul_event.event, 1);
}

void widget_log_event::data_arch(uint32_t ts, uint32_t work, uint16_t index, uint8_t event, bool emp){
    tmr_t_out->stop();
    if (emp){
        QVariantMap vm;
        vm.insert("ts", ts);
        vm.insert("work", work);
        vm.insert("event", event);
        //  vm.insert("obis", ul_event.obis);
        //   log_1 << ul_event.obis.A << ul_event.obis.B << ul_event.obis.C << ul_event.obis.D << ul_event.obis.E << ul_event.obis.F;
        //  vm.insert("event_ext", ul_event.event_ext);
        vm.insert("index", index);
     //   vm.insert("index_ext", ul_event.index_ext);
        // vm.insert("type", type);
        //   log_1 << "1111111" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        //  res_ul.ul_events << ul_event;
        vl << vm;
    }
    QVariantMap vmap;
    vmap.insert("meterings", vl);
    //  log_1 << "1111111" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
    emit signal_bar(count_bar);
    if (fl_intermediate){
        if (--dec_intermediate == 0){
            dec_intermediate = intermediate;
            count_bar++;
        }
    }
    else count_bar += progresbar;
    n_set_data--;
    if (n_set_data > -1){
        set_request_data( type, (uint32_t)n_set_data, n_set_data_max);
    }
    else {
        tmr_t_out->stop();
        n_set_data = -1;
        n_set_data_max = 0;
        emit signal_timeout_stop();
     //   m_model_log->insert_row( path_report_history(vmap), time_from_form_min(), time_from_form_max());
        QByteArray arr = QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented);
        log_1 << qPrintable(QJsonDocument::fromVariant(vl).toJson(QJsonDocument::Indented));
        transmit = false;
        if (all_data){
            transmit = true;
            switch (count_view) {
                case 0: { //event_U
                    m_model_U->insert_row( vmap, 0, 0 );
                    vmap_U = vmap;
                    m_view_U->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F01"));
                    count_view = 1;
                    break;
                }
                case 1: { //event_I
                    m_model_I->insert_row( vmap, 0, 0 );
                    vmap_I = vmap;
                    m_view_I->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F02"));
                    count_view = 2;
                    break;
                }
                case 2: { //event_rele
                    m_model_rele->insert_row( vmap, 0, 0 );
                    vmap_rele = vmap;
                    m_view_rele->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F03"));
                    count_view = 3;
                    break;
                }
                case 3: { //event_prog
                    m_model_prog->insert_row( vmap, 0, 0 );
                    vmap_prog = vmap;
                    m_view_prog->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F04"));
                    count_view = 4;
                    break;
                }
                case 4: { //event_ext
                    m_model_ext->insert_row( vmap, 0, 0 );
                    vmap_ext = vmap;
                    m_view_ext->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F05"));
                    count_view = 5;
                    break;
                }
                case 5: { //event_com
                    m_model_com->insert_row( vmap, 0, 0 );
                    vmap_com = vmap;
                    m_view_com->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F06"));
                    count_view = 6;
                    break;
                }
                case 6: { //event_access
                    m_model_access->insert_row( vmap, 0, 0 );
                    vmap_access = vmap;
                    m_view_access->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F07"));
                    count_view = 7;
                    break;
                }
                case 7: { //event_diagnos
                    m_model_diagnos->insert_row( vmap, 0, 0 );
                    vmap_diagnos = vmap;
                    m_view_diagnos->resizeColumnsToContents();
                    emit signal_write_data(QByteArray::fromHex("EF0F08"));
                    count_view = 8;
                    break;
                }
                case 8: { //event_tg_pow
                    m_model_tg_pow->insert_row( vmap, 0, 0 );
                    vmap_tg_pow = vmap;
                    m_view_tg_pow->resizeColumnsToContents();
                    radio1->setEnabled(true);
                    radio2->setEnabled(true);
                    combo->setEnabled(true);
                    break;
                }
                default: {
                    transmit = false;
                    break;
                }
            }
        }
        else{
            switch (type_data) {
                case 1: { //event_U
                    m_model_U->insert_row( vmap, 0, 0 );
                    vmap_U = vmap;
                    m_view_U->resizeColumnsToContents();break;
                }
                case 2: { //event_I
                    m_model_I->insert_row( vmap, 0, 0 );
                    vmap_I = vmap;
                    m_view_I->resizeColumnsToContents();break;
                }
                case 3: { //event_rele
                    m_model_rele->insert_row( vmap, 0, 0 );
                    vmap_rele = vmap;
                    m_view_rele->resizeColumnsToContents();break;
                }
                case 4: { //event_prog
                    m_model_prog->insert_row( vmap, 0, 0 );
                    vmap_prog = vmap;
                    m_view_prog->resizeColumnsToContents();break;
                }
                case 5: { //event_ext
                    m_model_ext->insert_row( vmap, 0, 0 );
                    vmap_prog = vmap;
                    m_view_ext->resizeColumnsToContents();break;
                }
                case 6: { //event_com
                    m_model_com->insert_row( vmap, 0, 0 );
                    vmap_com = vmap;
                    m_view_com->resizeColumnsToContents();break;
                }
                case 7: { //event_access
                    m_model_access->insert_row( vmap, 0, 0 );
                    vmap_access = vmap;
                    m_view_access->resizeColumnsToContents();break;
                }
                case 8: { //event_diagnos
                    m_model_diagnos->insert_row( vmap, 0, 0 );
                    vmap_diagnos = vmap;
                    m_view_diagnos->resizeColumnsToContents();break;
                }
                case 9: { //event_tg_pow
                    m_model_tg_pow->insert_row( vmap, 0, 0 );
                    vmap_tg_pow = vmap;
                    m_view_tg_pow->resizeColumnsToContents();break;
                }
            }
            radio1->setEnabled(true);
            radio2->setEnabled(true);
            combo->setEnabled(true);
        }
        emit signal_disable_tab_kn(0, 6);
    //     log_1 << qPrintable(arr);
     //  QFile file("logg.txt");
    //    if ( file.open(QIODevice::WriteOnly) ){
          //  QDataStream out(&file);
          //  out << vmap;
      //      file.write(arr);
     //       file.close();
     //   }
    //                QFile file1("logg.txt");
    //                if ( file1.open(QIODevice::ReadOnly) ){
    //                    QDataStream out(&file1);
    //                    out >> vmap;
    //                    file1.close();
    //                }
    }
}

void widget_log_event::slot_view_log_event(){
    if (radio){
        log_1 << "hhhhhh";
        m_model_U->insert_row( vmap_U, 0, 0 );
        m_view_U->resizeColumnsToContents();
        m_model_I->insert_row( vmap_I, 0, 0 );
        m_view_I->resizeColumnsToContents();
        m_model_rele->insert_row( vmap_rele, 0, 0 );
        m_view_rele->resizeColumnsToContents();
        m_model_prog->insert_row( vmap_prog, 0, 0 );
        m_view_prog->resizeColumnsToContents();
        m_model_ext->insert_row( vmap_ext, 0, 0 );
        m_view_ext->resizeColumnsToContents();
        m_model_com->insert_row( vmap_com, 0, 0 );
        m_view_com->resizeColumnsToContents();
        m_model_access->insert_row( vmap_access, 0, 0 );
        m_view_access->resizeColumnsToContents();
        m_model_diagnos->insert_row( vmap_diagnos, 0, 0 );
        m_view_diagnos->resizeColumnsToContents();
        m_model_tg_pow->insert_row( vmap_tg_pow, 0, 0 );
        m_view_tg_pow->resizeColumnsToContents();
    }
    else {
        type_data = combo->currentData().toUInt();
        switch (type_data) {
            case 1: { //event_U
                m_model_U->insert_row( vmap_U, 0, 0 );
                m_view_U->resizeColumnsToContents();break;
            }
            case 2: { //event_I
                m_model_I->insert_row( vmap_I, 0, 0 );
                m_view_I->resizeColumnsToContents();break;
            }
            case 3: { //event_rele
                m_model_rele->insert_row( vmap_rele, 0, 0 );
                m_view_rele->resizeColumnsToContents();break;
            }
            case 4: { //event_prog
                m_model_prog->insert_row( vmap_prog, 0, 0 );
                m_view_prog->resizeColumnsToContents();break;
            }
            case 5: { //event_ext
                m_model_ext->insert_row( vmap_ext, 0, 0 );
                m_view_ext->resizeColumnsToContents();break;
            }
            case 6: { //event_com
                m_model_com->insert_row( vmap_com, 0, 0 );
                m_view_com->resizeColumnsToContents();break;
            }
            case 7: { //event_access
                m_model_access->insert_row( vmap_access, 0, 0 );
                m_view_access->resizeColumnsToContents();break;
            }
            case 8: { //event_diagnos
                m_model_diagnos->insert_row( vmap_diagnos, 0, 0 );
                m_view_diagnos->resizeColumnsToContents();break;
            }
            case 9: { //event_tg_pow
                m_model_tg_pow->insert_row( vmap_tg_pow, 0, 0 );
                m_view_tg_pow->resizeColumnsToContents();break;
            }
        }
    }
}


void widget_log_event::slot_stop_read_log_event(){
    transmit = false;
    m_model_U->removeTable();
    m_model_I->removeTable();
    m_model_rele->removeTable();
    m_model_prog->removeTable();
    m_model_ext->removeTable();
    m_model_com->removeTable();
    m_model_access->removeTable();
    m_model_diagnos->removeTable();
    m_model_tg_pow->removeTable();
    tmr_t_out->stop();
    radio1->setEnabled(true);
    radio2->setEnabled(true);
    combo->setEnabled(true);
    n_set_data = -1;
    n_set_data_max = 0;
}

void widget_log_event::timeout(){
    log_1 << "count_tout" << count_tout;
    if (count_tout < 2){
        count_tout++;
        tmr_t_out->start(3000);
        set_request_data( type, (uint32_t)n_set_data, n_set_data_max);
    }
    else if ( count_tout == 2 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_t_out->start(3000);
    }
    else {
        transmit = false;
        tmr_t_out->stop();
        n_set_data = -1;
        n_set_data_max = 0;
        emit signal_timeout_start (100);
      //  emit signal_disable_tab_kn(0, 5);
    }
}

//********************************************************************************
void TModel_U::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
    }
}
void TModel_U::insert_row_data(QVariantMap vmap, int n){
    DData data;
  //  if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Фаза А - пропадание напряжения";break; }
        case 2: { data[2] = "Фаза А - восстановление напряжения";break; }
        case 3: { data[2] = "Фаза В - пропадание напряжения";break; }
        case 4: { data[2] = "Фаза В - восстановление напряжения";break; }
        case 5: { data[2] = "Фаза С - пропадание напряжения";break; }
        case 6: { data[2] = "Фаза С - восстановление напряжения";break; }
        case 7: { data[2] = "Превышение напряжения любой фазы";break; }
        case 8: { data[2] = "Окончание перенапряжения любой фазы";break; }
        case 9: { data[2] = "Низкое напряжение любой фазы - начало";break; }
        case 10: { data[2] = "Низкое напряжение любой фазы - окончание";break; }
        case 11: { data[2] = "Превышение коэффициента несимметрии напряжений по обратной последовательности - начало";break; }
        case 12: { data[2] = "Превышение коэффициента несимметрии напряжений по обратной последовательности - окончание";break; }
        case 13: { data[2] = "Фаза А - перенапряжение начало";break; }
        case 14: { data[2] = "Фаза А - перенапряжение окончание";break; }
        case 15: { data[2] = "Фаза В - перенапряжение начало";break; }
        case 16: { data[2] = "Фаза В - перенапряжение окончание";break; }
        case 17: { data[2] = "Фаза С - перенапряжение начало";break; }
        case 18: { data[2] = "Фаза С - перенапряжение окончание";break; }
        case 19: { data[2] = "Фаза А - провал начало";break; }
        case 20: { data[2] = "Фаза А - провал окончание";break; }
        case 21: { data[2] = "Фаза В - провал начало";break; }
        case 22: { data[2] = "Фаза В - провал окончание";break; }
        case 23: { data[2] = "Фаза С - провал начало";break; }
        case 24: { data[2] = "Фаза С - провал окончание";break; }
        case 25: { data[2] = "Неправильная последовательность фаз начало";break; }
        case 26: { data[2] = "Неправильная последовательность фаз окончание";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_U::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_U::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_I::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
      //  insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_I::insert_row_data(QVariantMap vmap, int n){
    DData data;
   // if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Фаза А - экспорт начало";break; }
        case 2: { data[2] = "Фаза А - экспорт окончание";break; }
        case 3: { data[2] = "Фаза В - экспорт начало";break; }
        case 4: { data[2] = "Фаза В - экспорт окончание";break; }
        case 5: { data[2] = "Фаза C - экспорт начало";break; }
        case 6: { data[2] = "Фаза C - экспорт окончание";break; }
        case 7: { data[2] = "Обрыв трансформатора тока фазы А";break; }
        case 8: { data[2] = "Восстановление трансформатора тока фазы А";break; }
        case 9: { data[2] = "Обрыв трансформатора тока фазы B";break; }
        case 10: { data[2] = "Восстановление трансформатора тока фазы B";break; }
        case 11: { data[2] = "Обрыв трансформатора тока фазы C";break; }
        case 12: { data[2] = "Восстановление трансформатора тока фазы C";break; }
        case 13: { data[2] = "Разбаланс токов - начало";break; }
        case 14: { data[2] = "Разбаланс токов - окончание";break; }
        case 15: { data[2] = "Замыкание трансформатора тока — начало";break; }
        case 16: { data[2] = "Замыкание трансформатора тока — окончание";break; }
        case 17: { data[2] = "Превышение тока любой фазы – начало";break; }
        case 18: { data[2] = "Превышение тока любой фазы – окончание";break; }
        case 19: { data[2] = "Фаза А - наличие тока при отсутствии напряжения начало";break; }
        case 20: { data[2] = "Фаза А - наличие тока при отсутствии напряжения окончание";break; }
        case 21: { data[2] = "Фаза В - наличие тока при отсутствии напряжения начало";break; }
        case 22: { data[2] = "Фаза В - наличие тока при отсутствии напряжения окончание";break; }
        case 23: { data[2] = "Фаза С - наличие тока при отсутствии напряжения начало";break; }
        case 24: { data[2] = "Фаза С - наличие тока при отсутствии напряжения окончание";break; }
        case 25: { data[2] = "Фаза А - превышение максимального тока начало";break; }
        case 26: { data[2] = "Фаза А - превышение максимального тока окончание";break; }
        case 27: { data[2] = "Фаза B - превышение максимального тока начало";break; }
        case 28: { data[2] = "Фаза B - превышение максимального тока окончание";break; }
        case 29: { data[2] = "Фаза C - превышение максимального тока начало";break; }
        case 30: { data[2] = "Фаза C - превышение максимального тока окончание";break; }
        case 31: { data[2] = "Наличие тока при отсутствии напряжения (обрыв нейтрали) ";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_I::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_I::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_rele::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
       // insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_rele::insert_row_data(QVariantMap vmap, int n){
    DData data;
   // if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Выключение питания счетчика";break; }
        case 2: { data[2] = "Включение питания счетчика";break; }
        case 3: { data[2] = "Выключение абонента дистанционное";break; }
        case 4: { data[2] = "Включение абонента дистанционное";break; }
        case 5: { data[2] = "Получение разрешения на включение абоненту";break; }
        case 6: { data[2] = "Выключение реле нагрузки абонентом";break; }
        case 7: { data[2] = "Включение реле нагрузки абонентом";break; }
        case 8: { data[2] = "Выключение локальное по превышению лимита мощности";break; }
        case 9: { data[2] = "Выключение локальное по превышению максимального тока";break; }
        case 10: { data[2] = "Выключение локальное при воздействии магнитного поля";break; }
        case 11: { data[2] = "Выключение локальное по превышению напряжения";break; }
        case 12: { data[2] = "Включение локальное при возвращение напряжения в норму";break; }
        case 13: { data[2] = "Выключение локальное по наличию тока при отсутствии напряжения";break; }
        case 14: { data[2] = "Выключение локальное по разбалансу токов";break; }
        case 15: { data[2] = "Выключение локальное по температуре";break; }
        case 16: { data[2] = "Включение резервного питания";break; }
        case 17: { data[2] = "Отключение резервного питания";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_rele::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_rele::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_prog::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
       // insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_prog::insert_row_data(QVariantMap vmap, int n){
    DData data;
  //  if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Изменение адреса или скорости обмена RS-485-1";break; }
        case 2: { data[2] = "Изменение адреса или скорости обмена RS-485-2";break; }
        case 3: { data[2] = "Установка времени";break; }
        case 4: { data[2] = "Изменение параметров перехода на летнее время";break; }
        case 5: { data[2] = "Изменение сезонного профиля тарифного расписания (ТР)";break; }
        case 6: { data[2] = "Изменение недельного профиля ТР";break; }
        case 7: { data[2] = "Изменение суточного профиля ТР";break; }
        case 8: { data[2] = "Изменение даты активации ТР";break; }
        case 9: { data[2] = "Активация ТР";break; }
        case 10: { data[2] = "Изменение  расчетного дня/часа (РДЧ)";break; }
        case 11: { data[2] = "Изменение режима индикации (параметры)";break; }
        case 12: { data[2] = "Изменение режима индикации (автопереключение)";break; }
        case 13: { data[2] = "Изменение пароля низкой секретности (на чтение)";break; }
        case 14: { data[2] = "Изменение пароля высокой секретности (на запись)";break; }
        case 15: { data[2] = "Изменение данных точки учета ";break; }
        case 16: { data[2] = "Изменение коэффициента трансформации по току";break; }
        case 17: { data[2] = "Изменение коэффициента трансформации по напряжению";break; }
        case 18: { data[2] = "Изменение параметров линии для вычисления потерь в ЛЭП";break; }
        case 19: { data[2] = "Изменение лимита мощности для отключения";break; }
        case 20: { data[2] = "Изменение интервала времени на отключение по мощности";break; }
        case 21: { data[2] = "Изменение интервала времени на отключение по превышению максимального тока";break; }
        case 22: { data[2] = "Изменение интервала времени на отключение по максимальному напряжению";break; }
        case 23: { data[2] = "Изменение интервала времени на отключение по воздействию магнитного поля";break; }
        case 24: { data[2] = "Изменение порога для фиксации перерыва в питании";break; }
        case 25: { data[2] = "Изменение порога для фиксации перенапряжения";break; }
        case 26: { data[2] = "Изменение порога для фиксации провала напряжения";break; }
        case 27: { data[2] = "Изменение порога для фиксации превышения тангенса";break; }
        case 28: { data[2] = "Изменение порога для фиксации  коэффициента несимметрии напряжений";break; }
        case 29: { data[2] = "Изменение согласованного напряжения";break; }
        case 30: { data[2] = "Изменение интервала интегрирования пиковой мощности";break; }
        case 31: { data[2] = "Изменение периода захвата профиля 1";break; }
        case 32: { data[2] = "Изменение периода захвата профиля 2";break; }
        case 33: { data[2] = "Изменение режима подсветки LCD";break; }
        case 34: { data[2] = "Изменение режима телеметрии";break; }
        case 35: { data[2] = "Очистка месячного журнала";break; }
        case 36: { data[2] = "Очистка суточного журнала";break; }
        case 37: { data[2] = "Очистка журнала напряжения";break; }
        case 38: { data[2] = "Очистка журнала тока";break; }
        case 39: { data[2] = "Очистка журнала вкл/выкл";break; }
        case 40: { data[2] = "Очистка журнала внешних воздействий";break; }
        case 41: { data[2] = "Очистка журнала соединений";break; }
        case 42: { data[2] = "Очистка журнала несанкционированного доступа";break; }
        case 43: { data[2] = "Очистка журнала качества сети";break; }
        case 44: { data[2] = "Очистка журнала тангенса";break; }
        case 45: { data[2] = "Очистка журнала входов/выходов";break; }
        case 46: { data[2] = "Очистка профиля 1";break; }
        case 47: { data[2] = "Очистка профиля 2";break; }
        case 48: { data[2] = "Очистка профиля 3";break; }
        case 49: { data[2] = "Изменение таблицы специальных дней";break; }
        case 50: { data[2] = "Изменение режима управления реле";break; }
        case 51: { data[2] = "Фиксация показаний в месячном журнале";break; }
        case 52: { data[2] = "Изменение режима инициативного выхода";break; }
        case 53: { data[2] = "Изменение одноадресного ключа шифрования для низкой секретности";break; }
        case 54: { data[2] = "Изменение широковещательного ключа шифрования для низкой секретности";break; }
        case 55: { data[2] = "Изменение одноадресного ключа шифрования для высокой секретности";break; }
        case 56: { data[2] = "Изменение широковещательного ключа шифрования для высокой секретности";break; }
        case 57: { data[2] = "Изменение ключа аутентификации для высокой секретности";break; }
        case 58: { data[2] = "Изменение мастер-ключа";break; }
        case 59: { data[2] = "Изменение уровня безопасности для низкой секретности";break; }
        case 60: { data[2] = "Изменение уровня безопасности для низкой секретности";break; }
        case 61: { data[2] = "Изменение номера дистанционного дисплея";break; }
        case 62: { data[2] = "Изменение режима учета активной энергии";break; }
        case 63: { data[2] = "Установка времени по GPS/ГЛОНАСС";break; }
        case 64: { data[2] = "Изменение режима отключения по обрыву нейтрали";break; }
        case 65: { data[2] = "Обновление ПО";break; }
        case 66: { data[2] = "Изменение режима отключения по разбалансу токов";break; }
        case 67: { data[2] = "Изменение режима отключения по температуре";break; }
        case 68: { data[2] = "Коррекция времени";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_prog::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_prog::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_ext::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
      //  insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_ext::insert_row_data(QVariantMap vmap, int n){
    DData data;
   // if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Магнитное поле - начало";break; }
        case 2: { data[2] = "Магнитное поле - окончание";break; }
        case 3: { data[2] = "Срабатывание электронной пломбы крышки клеммников начало";break; }
        case 4: { data[2] = "Срабатывание электронной пломбы корпуса начало";break; }
        case 131: { data[2] = "Срабатывание электронной пломбы крышки клеммников окончание";break; }
        case 132: { data[2] = "Срабатывание электронной пломбы корпуса окончание";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_ext::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_ext::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_com::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
      //  insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_com::insert_row_data(QVariantMap vmap, int n){
    DData data;
 //   if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Разорвано соединение (интерфейс)";break; }
        case 2: { data[2] = "Установлено соединение (интерфейс)";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_com::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_com::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_access::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
     //   insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_access::insert_row_data(QVariantMap vmap, int n){
    DData data;
    //if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Попытка несанкционированного доступа (интерфейс)";break; }
        case 2: { data[2] = "Нарушение требований протокола";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_access::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_access::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_diagnos::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
      //  insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_diagnos::insert_row_data(QVariantMap vmap, int n){
    DData data;
    //if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Инициализация счетчика";break; }
        case 2: { data[2] = "Измерительный блок — ошибка";break; }
        case 3: { data[2] = "Измерительный блок — норма";break; }
        case 4: { data[2] = "Вычислительный блок — ошибка";break; }
        case 5: { data[2] = "Часы реального времени — ошибка";break; }
        case 6: { data[2] = "Часы реального времени — норма";break; }
        case 7: { data[2] = "Блок питания - ошибка";break; }
        case 8: { data[2] = "Блок питания - норма";break; }
        case 9: { data[2] = "Дисплей — ошибка";break; }
        case 10: { data[2] = "Дисплей — норма";break; }
        case 11: { data[2] = "Блок памяти — ошибка";break; }
        case 12: { data[2] = "Блок памяти - норма";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_diagnos::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_diagnos::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

//********************************************************************************
void TModel_tg_pow::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    QVariantList vlist = vmap["meterings"].toList();
    for (int n = 0; n < vlist.count(); ++n) {
        QVariantMap v = vlist.at(n).toMap();
        if (v.contains("ts")){
            int ts = v["ts"].toInt();
            if ( ts > 1533070800 ){
                insert_row_data(vlist.at(n).toMap(), vlist.count() - n - 1);
            }
        }
      //  insert_row_data(vlist.at(n).toMap());
    }
}
void TModel_tg_pow::insert_row_data(QVariantMap vmap, int n){
    DData data;
    //if (vmap.contains("index")) data[0] = vmap["index"];
    data[0] = n;
    if (vmap.contains("ts")){
        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[1] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    int ev = 0;
    if (vmap.contains("event")) ev = vmap["event"].toInt();
    switch (ev) {
        case 1: { data[2] = "Превышение установленного порога - начало";break; }
        case 2: { data[2] = "Превышение установленного порога - окончание";break; }
    }
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}
void TModel_tg_pow::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}
void TModel_tg_pow::clear_m_data(){
    m_data.clear();
}
//********************************************************************************

// ********************************************************************************
TModel_U::TModel_U( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_U::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_U::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_U::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_U::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_U::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return "   ";
    }

    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }

    return QVariant();
}
Qt::ItemFlags TModel_U::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_I::TModel_I( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_I::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_I::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_I::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_I::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_I::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_I::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_rele::TModel_rele( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_rele::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_rele::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_rele::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_rele::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_rele::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_rele::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_prog::TModel_prog( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_prog::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_prog::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_prog::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_prog::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_prog::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_prog::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_ext::TModel_ext( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_ext::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_ext::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_ext::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_ext::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_ext::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_ext::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_com::TModel_com( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_com::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_com::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_com::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_com::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_com::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_com::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_access::TModel_access( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_access::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_access::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_access::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_access::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_access::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_access::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_diagnos::TModel_diagnos( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_diagnos::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_diagnos::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_diagnos::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_diagnos::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_diagnos::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_diagnos::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************

// ********************************************************************************
TModel_tg_pow::TModel_tg_pow( QObject* parent ) : QAbstractTableModel( parent ) {
}
int TModel_tg_pow::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}
int TModel_tg_pow::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 3;
}
QVariant TModel_tg_pow::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}
bool TModel_tg_pow::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}
QVariant TModel_tg_pow::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c0:
        return "№ п/п";
    case c1:
        return "Время";
    case c2:
        return "Cобытие";
    }
    return QVariant();
}
Qt::ItemFlags TModel_tg_pow::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************************
