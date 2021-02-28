#include "widget_tarifs.h"
#include "ui_widget_tarifs.h"

#include <Logger/Logger.h>
#include <QJsonDocument>
#include <QVariantMap>

#include <QJsonObject>

#include <QTableView>
#include <QHeaderView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QDate>
#include <QTime>
#include <QScrollArea>

extern uint32_t client_addr;
extern int count_bar;

//#define TARIFF_electro5
#define TARIFF_ZONE_MAX (2*24)
#define TARIFF_TABLE_ITEMS (24 >> 1)
#define TARIFF_SPEC_DAYS (10)

#define DLMS_tariff_index_init_val (0xFF)

typedef struct {
    uint8_t year_highbyte;
    uint8_t year_lowbyte;
    uint8_t month;
    uint8_t day_of_month;
    uint8_t day_of_week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t hundredths_of_second;
    uint8_t deviation_highbyte;
    uint8_t deviation_lowbyte;
    uint8_t clock_status;
} COSEM_date_time_struct;

#pragma pack(push, 1)
typedef struct {
    uint8_t hh3 :2; //номер тарифа //half-hour полчаса
    uint8_t hh2 :2; //номер тарифа //half-hour полчаса
    uint8_t hh1 :2; //номер тарифа //half-hour полчаса
    uint8_t hh0 :2; //номер тарифа //half-hour полчаса
} TARIFF_2hour; // 2 часа
typedef struct {
    TARIFF_2hour h2[TARIFF_TABLE_ITEMS];
} TARIFF_TABLE;
//typedef uint8_t TARIFF_TABLE [TARIFF_TABLE_ITEMS * 4];
typedef struct {
    uint16_t flag : 2;
    uint16_t month: 6;
    uint16_t day  : 8;
} TARIFF_spec_day;
typedef struct {
    TARIFF_TABLE workday;
    TARIFF_TABLE day_off;
    TARIFF_TABLE tariff_special_1;
    TARIFF_TABLE tariff_special_2;
    uint8_t weekend_days;
    TARIFF_spec_day special_days_1[TARIFF_SPEC_DAYS];
    TARIFF_spec_day special_days_2[TARIFF_SPEC_DAYS];
} TARIFF_TABLE_EXT;
typedef enum {
    V5_TARIFF_HEADER_TYPE_work_day      = 0x1,  // тарифы рабочего дня
    V5_TARIFF_HEADER_TYPE_day_off       = 0x2,  // тарифы выходного дня
    V5_TARIFF_HEADER_TYPE_special_1     = 0x3,  // тарифы специальный 1
    V5_TARIFF_HEADER_TYPE_special_2     = 0x4,  // тарифы специальный 2
    V5_TARIFF_HEADER_TYPE_days_day_off  = 0x5,  // выходные дни
    V5_TARIFF_HEADER_TYPE_days_special_1= 0x6,  // специальные дни 1
    V5_TARIFF_HEADER_TYPE_days_special_2= 0x7,  // специальные дни 2
} V5_TARIFF_HEADER_TYPE;

typedef struct {
    uint8_t timestamp_flag : 1;
    uint8_t obis_C : 7; //param + phase
    uint8_t rezerv : 1;
    uint8_t obis_E : 3; //tariff
    uint8_t obis_B : 2; //channel = 0
    uint8_t obis_A : 1;
    uint8_t obis_D : 1; //cur = 0, intgr = 1
} PARAM_IDENTIFIER;

typedef struct {
    uint8_t EL_V5;
    uint8_t timeout_hi;
    uint8_t reserv     : 1;
    uint8_t need_send  : 1;
    uint8_t alignment  : 2;
    uint8_t timeout_lo : 4;
    PARAM_IDENTIFIER pi[4];
    uint8_t reserv1;
} V5_SET_PROFILE;

typedef struct {
    uint8_t mask_hi : 4;
    uint8_t header  : 4;
    uint8_t mask_lo;
} V5_TARIFF_HEADER;

typedef union {
    struct {
        uint8_t day_id:         6;
        uint8_t id_block:       2; // = 2
    } days;
    struct {
        uint8_t week_id:        6;
        uint8_t id_block:       2; // = 3
    } weeks;
    struct {
        uint8_t res:            4;
        uint8_t id_sub_block:   2; // = 1
        uint8_t id_block:       2; // = 1
    } seasons;
    struct {
        uint8_t res:            4;
        uint8_t id_sub_block:   2; // = 2
        uint8_t id_block:       2; // = 1
    } special_day;
    struct {
        uint8_t res:            4;
        uint8_t id_sub_block:   2; // = 3
        uint8_t id_block:       2; // = 1
    } activate;
    uint8_t data;
} TARIFF_header;

//zone:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    4бита - номер тарифа
//    11бит - время с начала суток в минутах когда начитается зона
typedef struct {
    uint16_t start_zone: 11;
    uint16_t tariff: 4;
    uint16_t next: 1;
} TARIFF_zone;

//week:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    7бит  - маска дней недели когда активено расписание данного дня (старший?младший - пн)
//    2бита - резерв
//    6бит  - id дня
typedef struct {
    uint16_t day_id: 6;
    uint16_t reserv: 2;
    uint16_t mask_week: 7;
    uint16_t next: 1;
} TARIFF_week;

//season:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    4бита - месяц
//    5бит  - число месяца
//    6бит  - id недели
typedef struct {
    uint16_t week_id: 6;
    uint16_t day: 5;
    uint16_t month: 4;
    uint16_t next: 1;
} TARIFF_season;

//special_day:
//    1бит  - 0-последняя зона, 1-далее будет еще зона
//    4бита - месяц
//    5бит  - число месяца
//    6бит  - id дня
typedef struct {
    uint16_t day_id: 6;
    uint16_t day: 5;
    uint16_t month: 4;
    uint16_t next: 1;
} TARIFF_special_day;

#pragma pack(pop)



widget_tarifs::widget_tarifs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_tarifs)
{
    ui->setupUi(this);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setLayout( &mainLayout );

    QLabel* label1 = new QLabel( trUtf8( "Управление тарифным расписанием" ) );
    label1->setAlignment( Qt::AlignCenter );
    QFont font = label1->font();
    font.setPixelSize(14);
    label1->setFont(font);
    mainLayout.addWidget( label1 );

    QGridLayout* pLayout = new QGridLayout;
    pLayout->setAlignment( Qt::AlignCenter );
    mainLayout.addLayout( pLayout );

    QLabel* label2 = new QLabel( trUtf8( "Дата активации: " ) );
    label2->setAlignment( Qt::AlignCenter );
    pLayout->addWidget( label2, 0, 0 );

    QLineEdit* lineEdit = new QLineEdit( trUtf8( "01.01.2019" ) );
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment( Qt::AlignLeft );
    lineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    pLayout->addWidget( lineEdit, 0, 1 );

    QLabel* label3 = new QLabel( trUtf8( "Активно" ) );
    label3->setAlignment( Qt::AlignCenter );
    label3->setStyleSheet("color: red");
    pLayout->addWidget( label3, 0, 2 );

    QGridLayout* panelLayout = new QGridLayout;
    mainLayout.addLayout( panelLayout );

    QPushButton* bn_add_syt = new QPushButton( trUtf8( "Добавить новый суточный профиль" ) );
    connect( bn_add_syt, SIGNAL( clicked() ), SLOT( onAppend_syt() ) );
    panelLayout->addWidget( bn_add_syt, 0, 0 );

    QPushButton* bn_Remove_syt = new QPushButton( trUtf8( "Удалить выделенный суточный профиль" ) );
    connect( bn_Remove_syt, SIGNAL( clicked() ), this, SLOT( slot_click_Remove_syt() ) );
    panelLayout->addWidget( bn_Remove_syt, 0, 1 );

    QPushButton* bn_add_week = new QPushButton( trUtf8( "Добавить новый сезонный недельный профиль" ) );
    connect( bn_add_week, SIGNAL( clicked() ), SLOT( onAppend_week() ) );
    panelLayout->addWidget( bn_add_week, 1, 0 );

    QPushButton* bn_Remove_week = new QPushButton( trUtf8( "Удалить недельный профиль на активной вкладке" ) );
    connect( bn_Remove_week, SIGNAL( clicked() ), this, SLOT( slot_click_Remove_season() ) );
    panelLayout->addWidget( bn_Remove_week, 1, 1 );

    QPushButton* bn_add_sp_day = new QPushButton( trUtf8( "Добавить новую дату особого суточного профиля" ) );
    connect( bn_add_sp_day, SIGNAL( clicked() ), SLOT( onAppend_spec() ) );
    panelLayout->addWidget( bn_add_sp_day, 2, 0 );

    QPushButton* bn_Remove_sp_day = new QPushButton( trUtf8( "Удалить выделенную дату особого суточного профиля" ) );
    connect( bn_Remove_sp_day, SIGNAL( clicked() ), this, SLOT( slot_click_Remove_spec() ) );
    panelLayout->addWidget( bn_Remove_sp_day, 2, 1 );

    connect( bn_write_counter, SIGNAL( clicked() ), SLOT( write_to_counter() ) );
    panelLayout->addWidget( bn_write_counter, 3, 0, 3, 2 );
    bn_write_counter->setEnabled(false);

    QLabel* label4 = new QLabel();
    label4->setAlignment( Qt::AlignRight );
    label4->setPixmap( QPixmap( ":/png/yellow.png" ) );
    panelLayout->addWidget( label4, 1, 2 );

    QLabel* label5 = new QLabel( trUtf8( "- дневной тариф (1)" ) );
  // label3->setAlignment( Qt::AlignCenter );
  //  label3->setStyleSheet("color: red");
    panelLayout->addWidget( label5, 1, 3 );

    QLabel* label6 = new QLabel();
    label6->setAlignment( Qt::AlignRight );
    label6->setPixmap( QPixmap( ":/png/blue.png" ) );
    panelLayout->addWidget( label6, 1, 4 );

    QLabel* label7 = new QLabel( trUtf8( "- ночной тариф (2)" ) );
  //  label7->setAlignment( Qt::AlignRight );
    panelLayout->addWidget( label7, 1, 5 );

    QLabel* label8 = new QLabel();
    label8->setAlignment( Qt::AlignRight );
    label8->setPixmap( QPixmap( ":/png/green.png" ) );
    panelLayout->addWidget( label8, 2, 2 );

    QLabel* label9 = new QLabel( trUtf8( "- пиковый тариф (3)" ) );
  // label3->setAlignment( Qt::AlignCenter );
  //  label3->setStyleSheet("color: red");
    panelLayout->addWidget( label9, 2, 3 );

    QLabel* label10 = new QLabel();
    label10->setAlignment( Qt::AlignRight );
    label10->setPixmap( QPixmap( ":/png/red.png" ) );
    panelLayout->addWidget( label10, 2, 4 );

    QLabel* label11 = new QLabel( trUtf8( "- второй пиковый тариф (4)" ) );
  // label3->setAlignment( Qt::AlignCenter );
  //  label3->setStyleSheet("color: red");
    panelLayout->addWidget( label11, 2, 5 );

    QPushButton* bn_safe = new QPushButton( trUtf8( "Сохранить" ) );
    connect( bn_safe, SIGNAL( clicked() ), SLOT( slot_save() ) );
    panelLayout->addWidget( bn_safe, 0, 6 );

    QPushButton* bn_open = new QPushButton( trUtf8( "Открыть" ) );
    connect( bn_open, SIGNAL( clicked() ), SLOT( slot_open() ) );
    panelLayout->addWidget( bn_open, 1, 6 );

    QVBoxLayout *sLayout = new QVBoxLayout();

    QLabel* label12 = new QLabel( trUtf8( "Суточные профили тарифного расписания" ) );
    label12->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label12 );

    m_view = new QTableView;
    m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_view->setModel( m_model = new TModel );
    sLayout->addWidget( m_view );

    QLabel* label13 = new QLabel( trUtf8( "Сезонный недельный профиль тарифного расписания" ) );
    label13->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label13 );

    for (int n = 0; n < 64; ++n) {
        m_view_seasons[n] = new QTableView;
        m_view_seasons[n]->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
        m_view_seasons[n]->setModel( m_model_seasons[n] = new TModel_s );
        connect(m_model_seasons[n],SIGNAL(change_data(QModelIndex, int)), this, SLOT(slot_change_data(QModelIndex, int)));
    }

    w[0].setLayout( &seasonLayouts[0] );
    tab_w.addTab( &w[0], " " );
    sLayout->addWidget( &tab_w );

    QLabel* label14 = new QLabel( trUtf8( "Тарифное расписание особых дат" ) );
    label14->setAlignment( Qt::AlignLeft );
    sLayout->addWidget( label14 );

    m_view_special = new QTableView;
    m_view_special->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_special->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_view_special->setModel( m_model_special = new TModel_special );
    sLayout->addWidget( m_view_special );
    connect(m_model_special,SIGNAL(change_data(QModelIndex, int)), this, SLOT(slot_change_data_spec(QModelIndex, int)));

    connect( m_model, SIGNAL( profile_break() ), this, SLOT( slot_profile_break() ) );
    connect( m_model, SIGNAL( signal_change_profile(QHash< int, QVariant >) ), this, SLOT( slot_change_profile(QHash< int, QVariant >) ) );
    connect(m_view,SIGNAL(clicked(QModelIndex)), m_model, SLOT(slot_click(QModelIndex)));
    connect(m_view, SIGNAL(itemActivated (QTableViewItem *)), this, SLOT(on_tableWidget_itemClicked(QTableViewItem *)) );

    tmr_tout = new QTimer();
    connect(tmr_tout, SIGNAL(timeout()), this, SLOT(timeout()));

    QWidget *workSpace = new QWidget();
    workSpace->setLayout( sLayout );
    QSize AdjustSize = workSpace->size()*2.5;
    AdjustSize.height();
    workSpace->setMinimumSize(AdjustSize);
    QScrollArea * scrollArea =  new  QScrollArea;
    scrollArea->setWidget(workSpace);

    mainLayout.addWidget( scrollArea );
}

widget_tarifs::~widget_tarifs()
{
    delete ui;
}

bool widget_tarifs::transmitt(){
    return transmit;
}

void widget_tarifs::slot_save(){
    QVariantMap vmap_days;
    int n_days = m_model->count_days();
    QHash< int, QVariant > data_days;
    for (int n = 0; n < n_days; ++n) {
        data_days = m_model->data_hash(n);
        QVariantMap day;
        int n_data = 0;
        for (int i = 2; i < 25; ++i) {
            if (data_days[i] != data_days[i-1] ){
                day.insert( QString::number( (i - 1) * 60 ), data_days[i].toInt() - 1 );
            }
            else n_data++;
        }
        if (data_days[1].toInt() != data_days[24].toInt()){
            day.insert( QString::number(0), data_days[1].toInt() - 1 );
        }
        else n_data++;
        if ( n_data >= 24 ){
            day.insert( QString::number( 0 ), data_days[1].toInt() - 1 );
        }
        vmap_days.insert(QString::number(data_days[0].toInt() - 1), day);
    }
    QVariantMap vmap_weeks;
    int n_weeks = tab_w.count();
    QList< QHash< int, QVariant > > data_weeks;
    for (int n = 0; n < n_weeks; ++n) {
        data_weeks = m_model_seasons[n]->data_list();
        int week[] = {-1,-1,-1,-1,-1,-1,-1};
        QHash< int, QVariant > day;
        for (int i = 0; i < 7; ++i) {
            day = data_weeks.at(i);
            week[i] = day[0].toInt() - 1;
        }
        QVariantList vlweek;
        for (int i = 0; i < 7; ++i) {
            vlweek << week[i];
        }
        vmap_weeks.insert(QString::number(n), vlweek);
    }
    QVariantMap vmap_seasons;
    int n_seasons = n_weeks;
    for (int n = 0; n < n_seasons; ++n) {
        int t = (tab_w.tabText(n).mid(3, 2) + tab_w.tabText(n).mid(0, 2)).toInt();
        QString s;
        s = s.setNum(t);
        vmap_seasons.insert( s, n);
    }
    QVariantMap vmap_special_days;
    int n_spec_days = m_model_special->count_days();
    QHash< int, QVariant > data_spec_days;
    for (int n = 0; n < n_spec_days; ++n) {
        data_spec_days = m_model_special->data_hash(n);
        int t = (data_spec_days[0].toString().mid(3, 2) + data_spec_days[0].toString().mid(0, 2)).toInt();
        QString s;
        s = s.setNum(t);
        vmap_special_days.insert(s, data_spec_days[1].toInt() - 1);
    }
    QVariantMap vmap;
    if (!vmap_days.isEmpty()) {
        vmap.insert("days", vmap_days);
    }
    if (!vmap_weeks.isEmpty()) {
        vmap.insert("weeks", vmap_weeks);
    }
    if (!vmap_seasons.isEmpty()) {
        vmap.insert("seasons", vmap_seasons);
    }
    if (!vmap_special_days.isEmpty()) {
        vmap.insert("special_days", vmap_special_days);
    }
    QFileDialog dialog(this);
    QString str = dialog.getSaveFileName(this, "Сохранить в файл", "C:", "*.json");
    QFile jsonFile(str);
    if ( jsonFile.open(QFile::WriteOnly) ){
        jsonFile.write(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
        jsonFile.close();
    }
}

void widget_tarifs::slot_open(){
    QFileDialog dialog(this);
    QString str = dialog.getOpenFileName(this, "Открыть файл", "", "*.json");
    QFile jsonFile(str);
    QVariantMap vm;
    if ( jsonFile.open(QFile::ReadOnly) ){
        vm = QJsonDocument().fromJson(jsonFile.readAll()).toVariant().toMap();
        jsonFile.close();
        QVariantMap vm1 = vm;
        slot_disconnect();
        for (int n = tab_w.count() -1 ; n >= 0; n--) {
            tab_w.removeTab(n);
        }
        if (vm.contains("seasons")){
            vm = vm.value("seasons", QVariantMap()).toMap();
            qty_seasons = 0;
            foreach(const QString& key, vm.keys()) {
                QString value = vm[key].toString();
                seasons[qty_seasons][0] = key;
                seasons[qty_seasons][1] = value;
                qty_seasons++;
            }
        }
        vm = vm1;
        if (vm.contains("weeks")){
            vm = vm.value("weeks", QVariantMap()).toMap();
            qty_weeks = 0;
            foreach(const QString& key, vm.keys()) {
                weeks[qty_weeks][0] = key;
                QVariantList list = vm[key].toList();
                for (int i = 0; i < list.size(); ++i) {
                    int temp = list.at(i).toInt() + 1;
                    weeks[qty_weeks][i+1] = QString::number(temp);
                }
                qty_weeks++;
            }
        }
        vm = vm1;
        if (vm.contains("days")){
            vm = vm.value("days", QVariantMap()).toMap();
            qty_days = 0;
            int k = 0;
            foreach(const QString& key, vm.keys()) {
                k = 0;
                int temp = key.toInt() + 1;
                days[qty_days][k][0] = QString::number(temp);
                QVariantMap vm_value = vm[key].toMap();
                foreach(const QString& key1, vm_value.keys()){
                    QString value = vm_value[key1].toString();
                    int i = key1.toInt();
                    i = i / 60;
                    QString str;
                    str = str.setNum(i);
                    days[qty_days][k][2] = str;
                    days[qty_days][k][3] = value;
                    k++;
                }
                days[qty_days][0][1] = QString::number(k);
                qty_days++;
            }
            m_model->appendData( qty_seasons, seasons, qty_weeks, weeks, qty_days, days );
            seasons_view(qty_seasons);
            for (int n = 0; n < qty_seasons; ++n) {
                m_model_seasons[n]->appendData( n, qty_seasons, seasons, qty_weeks, weeks, qty_days, days );
            }
        }
        vm = vm1;
        if (vm.contains("special_days")){
            vm = vm.value("special_days", QVariantMap()).toMap();
            qty_special_days = 0;
            foreach(const QString& key, vm.keys()) {
                int temp = vm[key].toInt() + 1;
                QString value = QString::number(temp);
                special_days[qty_special_days][0] = key;
                special_days[qty_special_days][1] = value;
                qty_special_days++;
            }
            m_model_special->appendData( qty_special_days, special_days, qty_days, days );
        }
    }
}

void widget_tarifs::timeout(){
    transmit = true;
    emit signal_write_data (QByteArray::fromHex("51"));
    if (count_tout < 2){
        count_tout++;
        tmr_tout->start(3000);
    }
    else if ( count_tout == 2 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(3000);
    }
    else if ( count_tout == 3 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(6000);
    }
    else if ( count_tout == 4 ) {
        count_tout++;
        emit signal_on_pushButton_connect_clicked(true);
        tmr_tout->start(12000);
    }
    else if ( count_tout > 4 ) {
        transmit = false;
        tmr_tout->stop();
        emit signal_timeout_start (100);
        emit signal_disable_tab_kn(0, 4);
    }
}

void widget_tarifs::slot_disconnect(){
    m_model->removeData();
    for (int n = 0; n < tab_w.count(); ++n) {
        m_model_seasons[n]->removeData();
    }
    m_model_special->removeData();
}

void TModel::removeData(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}

void TModel_special::removeData(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}

void widget_tarifs::slot_click_Remove_spec(){
    QItemSelectionModel* selectModel = m_view_special->selectionModel();
    if (selectModel->hasSelection()){
        int index = selectModel->selectedRows().first().row();
        m_model_special->removeSelected(index);
    }
}

void TModel_special::removeSelected(int indexrow) {
    QModelIndex index;
    beginRemoveRows(index, indexrow, indexrow);
    m_data.removeAt(indexrow);
    endRemoveRows();
}

void widget_tarifs::slot_click_Remove_season(){
    if ( tab_w.count() > 1 ) {
        int cur_index = tab_w.currentIndex();
        int count_index = tab_w.count();
        if (cur_index == count_index-1){
            seasonLayouts[cur_index].removeWidget( m_view_seasons[cur_index] );
            m_model_seasons[cur_index]->removeData();
            seasonLayouts[cur_index].update();
            w[cur_index].update();
            tab_w.removeTab(cur_index);
            tab_w.setCurrentIndex(cur_index-1);
        }
        else{
            for (int n = cur_index; n < count_index-1; ++n) {
                seasonLayouts[n].removeWidget( m_view_seasons[n] );
                m_model_seasons[n]->copyto( m_model_seasons[n+1]->copyfrom() );
                seasonLayouts[n].addWidget( m_view_seasons[n] );
                seasonLayouts[n].update();
                w[n].update();
                QString str = tab_w.tabText(n+1);
                tab_w.insertTab( n, &w[n], str );
                if (n >= count_index - 2){
                    m_model_seasons[n+1]->removeData();
                    seasonLayouts[n+1].removeWidget(m_view_seasons[n+1]);
                    seasonLayouts[n+1].update();
                    w[n+1].update();
                    tab_w.removeTab(n + 1);
                }
            }
        }
    }
    else {

    }
}

QList< QHash< int, QVariant > > TModel_s::copyfrom(){
    return m_data;
}

void TModel_s::copyto(QList< QHash< int, QVariant > > m_data1){
//    for (int n = m_data.count(); n > -1 ; n--) {
//        beginRemoveRows(QModelIndex(), n, n);
//        m_data.removeAt(n);
//        endRemoveRows();
//    }
    m_data.clear();
    m_data = m_data1;
}

void TModel_s::removeData(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
  //  m_data.clear();
}

void widget_tarifs::slot_change_profile(QHash< int, QVariant > data){
    for (int n = 0; n < tab_w.count(); ++n) {
        m_model_seasons[n]->change_profile(data);
    }
    m_model_special->change_profile(data);
}

void TModel_s::change_profile(QHash< int, QVariant > data){
    DData data1;
    for (int n = 0; n < m_data.count(); ++n) {
        data1 = m_data.at(n);
        if (data1[0] == data[0]){
            layoutAboutToBeChanged();
            m_data.replace(n, data);
            layoutChanged();
        }
    }
}

void TModel_special::change_profile(QHash< int, QVariant > data){
    DData data1;
    for (int n = 0; n < m_data.count(); ++n) {
        data1 = m_data.at(n);
        if (data1[1] == data[0]){
            for (int i = 2; i < 26; ++i) {
                data1[i] = data[i-1];
            }
            layoutAboutToBeChanged();
            m_data.replace(n, data1);
            layoutChanged();
        }
    }
}

void widget_tarifs::slot_profile_break(){
    emit signal_profile_break();
}

QHash< int, QVariant > TModel::data_hash(int row){
    return m_data.at(row);
}

QHash< int, QVariant > TModel_special::data_hash(int row){
    return m_data.at(row);
}

int TModel::count_days(){
    return m_data.count();
}

int TModel_special::count_days(){
    return m_data.count();
}

QList< QHash< int, QVariant > > TModel_s::data_list(){
    return m_data;
}

QVariant widget_tarifs::write_to_counter(){
    QVariantMap vmap_days;
    int n_days = m_model->count_days();
    QHash< int, QVariant > data_days;
    for (int n = 0; n < n_days; ++n) {
        data_days = m_model->data_hash(n);
        QVariantMap day;
        int n_data = 0;
        for (int i = 2; i < 25; ++i) {
            if (data_days[i] != data_days[i-1] ){
                day.insert( QString::number( (i - 1) * 60 ), data_days[i].toInt() - 1 );
            }
            else n_data++;
        }
        if (data_days[1].toInt() != data_days[24].toInt()){
            day.insert( QString::number(0), data_days[1].toInt() - 1 );
        }
        else n_data++;
        if ( n_data >= 24 ){
            day.insert( QString::number( 0 ), data_days[1].toInt() - 1 );
        }
        vmap_days.insert(QString::number(data_days[0].toInt() - 1), day);
    }
 //   log_1 << qPrintable(QJsonDocument::fromVariant(vmap_days).toJson(QJsonDocument::Indented));
    QVariantMap vmap_weeks;
    int n_weeks = tab_w.count();
    QList< QHash< int, QVariant > > data_weeks;
    for (int n = 0; n < n_weeks; ++n) {
        data_weeks = m_model_seasons[n]->data_list();
        int week[] = {-1,-1,-1,-1,-1,-1,-1};
        QHash< int, QVariant > day;
        for (int i = 0; i < 7; ++i) {
            day = data_weeks.at(i);
            week[i] = day[0].toInt() - 1;
        }
        QVariantList vlweek;
        for (int i = 0; i < 7; ++i) {
            vlweek << week[i];
        }
        vmap_weeks.insert(QString::number(n), vlweek);
    }
 //   log_1 << qPrintable(QJsonDocument::fromVariant(vmap_weeks).toJson(QJsonDocument::Indented));
    QVariantMap vmap_seasons;
    int n_seasons = n_weeks;
    for (int n = 0; n < n_seasons; ++n) {
        int t = (tab_w.tabText(n).mid(3, 2) + tab_w.tabText(n).mid(0, 2)).toInt();
        QString s;
        s = s.setNum(t);
        vmap_seasons.insert( s, n);
    }
  //  log_1 << qPrintable(QJsonDocument::fromVariant(vmap_seasons).toJson(QJsonDocument::Indented));
    QVariantMap vmap_special_days;
    int n_spec_days = m_model_special->count_days();
    QHash< int, QVariant > data_spec_days;
    for (int n = 0; n < n_spec_days; ++n) {
        data_spec_days = m_model_special->data_hash(n);
        int t = (data_spec_days[0].toString().mid(3, 2) + data_spec_days[0].toString().mid(0, 2)).toInt();
        QString s;
        s = s.setNum(t);
        vmap_special_days.insert(s, data_spec_days[1].toInt() - 1);
    }
  //  log_1 << qPrintable(QJsonDocument::fromVariant(vmap_special_days).toJson(QJsonDocument::Indented));
    QVariantMap vmap;
    if (!vmap_days.isEmpty()) {
        vmap.insert("days", vmap_days);
    }
    if (!vmap_weeks.isEmpty()) {
        vmap.insert("weeks", vmap_weeks);
    }
    if (!vmap_seasons.isEmpty()) {
        vmap.insert("seasons", vmap_seasons);
    }
    if (!vmap_special_days.isEmpty()) {
        vmap.insert("special_days", vmap_special_days);
    }
    log_1 << "vmap" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
 //   log_1 << tariff_json_pack(vmap).toHex().toUpper();
    transmit = true;
    emit signal_write_data(tariff_json_pack(vmap));
    count_tout = 0;
    tmr_tout->start(3000);
    count_bar = 34;
    emit signal_bar(count_bar);
}

QString TModel_special::get_date(int row){
    DData data = m_data.at(row);
    return data[0].toString();
}

void widget_tarifs::slot_change_data(QModelIndex index, int value){
    if (m_model->test_profil(value)){
        QHash< int, QVariant > data = m_model->copyhash_season(value);
        m_model_seasons[tab_w.currentIndex()]->changeRow(index, data);
        m_model_seasons[tab_w.currentIndex()]->emit_change(index, value);
    }
}

void TModel_s::emit_change(QModelIndex index, int value){
    m_data[  Row( index.row() ) ][ Column( index.column() ) ] = value;
    emit dataChanged( index, index );
}

bool TModel::test_profil(int profil){
    DData data;
    for (int n = 0; n < m_data.count(); ++n) {
        data = m_data.at(n);
        if (data[0].toInt() == profil) return true;
    }
    return false;
}

void widget_tarifs::slot_change_data_spec(QModelIndex index, int value){
    if (m_model->test_profil(value)){
        QHash< int, QVariant > data = m_model->copyhash_spec_withDate(m_model_special->get_date(index.row()), value, index);
        if (data.isEmpty()) return;
        m_model_special->changeRow(index, data);
    }

}

void TModel_s::changeRow(QModelIndex index, QHash< int, QVariant > data){
    layoutAboutToBeChanged();
    m_data.replace(index.row(), data);
    layoutChanged();
}

void TModel_special::changeRow(QModelIndex index, QHash< int, QVariant > data){
    layoutAboutToBeChanged();
    m_data.replace(index.row(), data);
    layoutChanged();
}

void TModel::slot_click(QModelIndex index){
    if (index.column() > 0){
        int d = data(index, Qt::DisplayRole).toInt();
        if (++d > 4) d = 1;
        DData data;
        data = m_data.at(index.row());
        data[index.column()] = d;
        layoutAboutToBeChanged();
        m_data.replace(index.row(), data);
        layoutChanged();
        emit signal_change_profile(data);
    }
}

void widget_tarifs::onAppend_syt() {
    m_model->appendRow();
}

void widget_tarifs::onAppend_week() {
    int n_tab = tab_w.count();
    if ( n_tab < 64){
        emit signal_dial_date_season();
    }
}

void widget_tarifs::slot_date_season(QDate date, QHash<int,int> profils){
    QDateTime qdt(date);
    int n_tab = tab_w.count();
    QList< QHash< int, QVariant > > m_data = m_model->copydata(profils);
    seasonLayouts[n_tab].removeWidget(m_view_seasons[n_tab]);
    m_model_seasons[n_tab]->removeData();
    m_model_seasons[n_tab]->appendweek(m_data);
    seasonLayouts[n_tab].addWidget( m_view_seasons[n_tab], 0, 0 );
    w[n_tab].setLayout( &seasonLayouts[n_tab] );

    tab_w.addTab( &w[n_tab], qdt.toString("dd.MM") );

//    QList< QHash< int, QVariant > > m_data = m_model->copydata(profils);
//    m_model_seasons[n_tab-1]->appendweek(m_data);
//    seasonLayouts[n_tab-1].addWidget( m_view_seasons[n_tab-1], 0, 0 );
//    w[n_tab-1].setLayout( &seasonLayouts[n_tab-1] );

//    tab_w.addTab( &w[n_tab-1], qdt.toString("dd.MM") );

  //  tab_w.currentWidget().Text();
}

void widget_tarifs::onAppend_spec() {
    emit signal_date_spec();
}

void widget_tarifs::slot_date_spec(int profil, QDate date){
    QDateTime qdt(date);
    QString str = qdt.toString("dd.MM");
    if (m_model_special->test_data_spec(str)){
        emit signal_error_data_spec();
        return;
    }
    QHash< int, QVariant > data = m_model->copyhash_spec(profil, date);
    if (data.isEmpty()){
        emit signal_err_profil_spec();
        return;
    }
    else m_model_special->appendRow(data);
}

bool TModel_special::test_data_spec(QString date){
    DData data;
    for (int n = 0; n < m_data.count(); ++n) {
        data = m_data.at(n);
    //    log_1 << data[0].toString() << date;
        if (data[0].toString() == date) return true;
    }
    return false;
}

QList< QHash< int, QVariant > > TModel::copydata(QHash<int,int> profils){
    DData data;
    Data m_data1;
    for (int n = 0; n < 7; ++n) {
        for (int i = 0; i < m_data.count(); ++i) {
            data = m_data.at(i);
            if (data[0] == profils[n]){
                m_data1.append( data );
            }
        }
    }
    return m_data1;
}

void widget_tarifs::slot_test_profils_seasons(QHash<int,int> profils, QDate date){
    QDateTime qdt(date);
    QString str = qdt.toString("dd.MM");
    for (int n = 0; n < tab_w.count(); ++n) {
        if (tab_w.tabText(n) == str){
            emit signal_error_data_seasons();
            return;
        }
    }
    if (m_model->test_profils_seasons(profils)){
        emit signal_error_profils_seasons();
        return;
    }
    slot_date_season(date, profils);
}

bool TModel::test_profils_seasons(QHash<int, int> profils){
    DData data;
    for (int i = 0; i < 7; ++i) {
        bool fl = false;
        for (int n = 0; n < m_data.count(); ++n) {
            data = m_data.at(n);
            if (profils[i] == data[0].toInt()){
                fl = true;
                break;
            }
        }
        if (!fl){
            return true;
        }
    }
    return false;
}

QHash< int, QVariant > TModel::copyhash_spec(int profil, QDate date){
    QDateTime qdt(date);
    DData data;
    DData data1;
    bool fl = false;
    for (int i = 0; i < m_data.count(); ++i) {
        data = m_data.at(i);
        if (data[0].toInt() == profil){
            data1[0] = qdt.toString("dd.MM");
            for (int n = 0; n < 25; ++n) {
                data1[n+1] = data[n];
            }
        }
    }
    return data1;
}

QHash< int, QVariant > TModel::copyhash_spec_withDate(QString date, int profil, QModelIndex index){
    DData data;
    int row = -1;
    for (int n = 0; n < m_data.count(); ++n) {
        data = m_data.at(n);
        if (data[0].toInt() == profil){
            row = n;
        }
    }
    if (row == -1){
        data.clear();
        return data;
    }
    data = m_data.at(row);
    DData data1;
    data1[0] = date;
    for (int n = 0; n < 25; ++n) {
        data1[n+1] = data[n];
    }
 //   m_data[ index.row() ][ Column( index.column() ) ] = profil;
 //   emit dataChanged( index, index );
    return data1;
}

QHash< int, QVariant > TModel::copyhash_season(int value){
    DData data;
    for (int n = 0; n < m_data.count(); ++n) {
         data = m_data.at(n);
         if (data[0].toInt() == value) return data;
    }
}

void TModel_s::appendweek(QList< QHash< int, QVariant > > m_data1){
    DData data;
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
    for (int n = 0; n < 7; ++n) {
        data = m_data1.at(n);
        m_data.append( data );
        beginInsertRows( QModelIndex(), n, n );
        endInsertRows();
    }
}

void TModel::appendRow(){
    DData data;
    int row = m_data.count();
    for (int i = 0; i < 64; ++i) {
        bool fl = false;
        for (int n = 0; n < row; ++n) {
            data = m_data.at(n);
            if (data[0] == i+1) fl = true;
        }
        if (!fl){
            data[0] = i+1;
            for (int k = 1; k < 25; ++k) {
                data[k] = 1;
            }

            beginInsertRows( QModelIndex(), row, row );
            m_data.append( data );
            endInsertRows();
            return;
        }
    }
}

void TModel_special::appendRow(QHash< int, QVariant > data){
    int row = m_data.count();
    m_data.append( data );
    beginInsertRows( QModelIndex(), row, row );
    endInsertRows();
}

void widget_tarifs::slot_tariff_json_unpack (QByteArray tariff){
    if (transmit){
        transmit = false;
        count_bar += 34;
        emit signal_bar(count_bar);
        QVariantMap vm = tariff_json_unpack(tariff);
        QVariantMap vm1 = vm;
        log_1 << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        if (vm.contains("seasons")){
            vm = vm.value("seasons", QVariantMap()).toMap();
         //   log_1 << "json" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            qty_seasons = 0;
            foreach(const QString& key, vm.keys()) {
                QString value = vm[key].toString();
                seasons[qty_seasons][0] = key;
                seasons[qty_seasons][1] = value;
                qty_seasons++;
          //      log_1 << "seasons" << seasons[qty_seasons][0] << ", Value = " << seasons[qty_seasons][1];
            }
       //     log_1 << "qty_seasons" << QString::number(qty_seasons);
        }
        count_bar += 10;
        emit signal_bar(count_bar);
        vm = vm1;
        if (vm.contains("weeks")){
            vm = vm.value("weeks", QVariantMap()).toMap();
          //  log_1 << "json" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            qty_weeks = 0;
            foreach(const QString& key, vm.keys()) {
                weeks[qty_weeks][0] = key;
        //        log_1 << "weeks[qty_weeks][0]" << weeks[qty_weeks][0];
                QVariantList list = vm[key].toList();
                for (int i = 0; i < list.size(); ++i) {
                    int temp = list.at(i).toInt() + 1;
                    weeks[qty_weeks][i+1] = QString::number(temp);
                //    log_1 << "list.at(i)" << list.at(i).toString();
              //      log_1 << "weeks" << weeks[qty_weeks][i+1] << qty_weeks << i+1;
                }
                qty_weeks++;
          //      log_1 << "qty_weeks" << QString::number(qty_weeks);
            }
        }
        count_bar += 10;
        emit signal_bar(count_bar);
        vm = vm1;
        if (vm.contains("days")){
            vm = vm.value("days", QVariantMap()).toMap();
        //    log_1 << "json" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            qty_days = 0;
            int k = 0;
            foreach(const QString& key, vm.keys()) {
                k = 0;
                int temp = key.toInt() + 1;
                days[qty_days][k][0] = QString::number(temp);
          //      log_1 << "days[qty_days][k][0]" << days[qty_days][k][0] << qty_days << k;
                QVariantMap vm_value = vm[key].toMap();
         //       log_1 << "json" << qPrintable(QJsonDocument::fromVariant(vm_value).toJson(QJsonDocument::Indented));
                foreach(const QString& key1, vm_value.keys()){
                    QString value = vm_value[key1].toString();
                    int i = key1.toInt();
                    i = i / 60;
                    QString str;
                    str = str.setNum(i);
                    days[qty_days][k][2] = str;
                    days[qty_days][k][3] = value;
         //           log_1 << days[qty_days][k][2] << days[qty_days][k][3] << QString::number(k);
                    k++;
                }
                days[qty_days][0][1] = QString::number(k);
             //   log_1 << "days[qty_days][k][1]" << days[qty_days][k][1];
                qty_days++;
        //        log_1 << "qty_days" << QString::number(qty_days) << "\n";

            }
            m_model->appendData( qty_seasons, seasons, qty_weeks, weeks, qty_days, days );
            seasons_view(qty_seasons);
            for (int n = 0; n < qty_seasons; ++n) {
                m_model_seasons[n]->appendData( n, qty_seasons, seasons, qty_weeks, weeks, qty_days, days );
            }
        }
        count_bar += 12;
        emit signal_bar(count_bar);
        vm = vm1;
        if (vm.contains("special_days")){
            vm = vm.value("special_days", QVariantMap()).toMap();
        //    log_1 << "json" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            qty_special_days = 0;
            foreach(const QString& key, vm.keys()) {
                int temp = vm[key].toInt() + 1;
                QString value = QString::number(temp);
                special_days[qty_special_days][0] = key;
                special_days[qty_special_days][1] = value;
                qty_special_days++;
             //   log_1 << "special_days" << key << ", Value = " << value;
            }
        //    log_1 << "qty_special_days" << QString::number(qty_special_days);
            m_model_special->appendData( qty_special_days, special_days, qty_days, days );
        }
        tmr_tout->stop();
        emit signal_disable_tab_kn(0, 4);
    }
}

void TModel_special::appendData( int qty_special_days, QString special_days[100][2], int qty_days, QString days[100][100][4] ) {
    DData data;
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
  //  m_data.clear();
    //цикл по каждому специальному дню
    for (int n = 0; n < qty_special_days; n++) {
        for (int k = 0; k < qty_days; k++) {
            if ( special_days[ n ][ 1 ] == days[ k ][ 0 ][ 0 ] ){
                data.clear();
                int date = special_days[ n ][ 0 ].toInt();
                int d = date % 100;
                QString str_d;
                if ( d < 10 ){
                    str_d = str_d.setNum(d);
                    str_d = "0" + str_d;
                }
                else str_d = str_d.setNum(d);
                date = date / 100;
                QString str_m;
                if ( date < 10 ){
                    str_m = str_m.setNum(date);
                    str_m = "0" + str_m;
                }
                else str_m = str_m.setNum(date);
                str_m = str_d + "." + str_m;
                data[ 0 ] = str_m;
                data[ 1 ] = days[k][0][0];
                int buf_days[100];
                int buf_tarif[100];
                for(int i = 0; i < days[k][0][1].toInt(); ++i)
                {
                    buf_days[i] = days[k][i][2].toInt();
                    buf_tarif[i] = days[k][i][3].toInt() + 1;
                }

                //сортировка времени по возростанию
                for(int i = 1; i < days[k][0][1].toInt(); ++i)
                {
                    for(int r = 0; r < days[k][0][1].toInt() - i; r++)
                    {
                        if(buf_days[r] > buf_days[r+1])
                        {
                            // Обмен местами
                            int temp = buf_days[r];
                            int temp1 = buf_tarif[r];
                            buf_days[r] = buf_days[r+1];
                            buf_tarif[r] = buf_tarif[r+1];
                            buf_days[r+1] = temp;
                            buf_tarif[r+1] = temp1;
                        }
                    }
                }
                //цикл по (времени + тарифу) внутри каждого типа дня
                for(int i = 0; i < days[k][0][1].toInt(); ++i){
                    if (i < days[k][0][1].toInt() - 1){
                        for(int n = buf_days[i]; n < buf_days[i+1]; ++n){
                            data[ n + 2 ] = buf_tarif[i];
                        }
                    }
                    else {
                        for(int n = buf_days[days[k][0][1].toInt() - 1]; n < 24; ++n){
                            data[ n + 2 ] = buf_tarif[i];
                        }
                        for(int n = 0; n < buf_days[0]; ++n){
                            data[ n + 2 ] = buf_tarif[i];
                        }
                    }
                }
                int row = m_data.count();
                m_data.append( data );
                beginInsertRows( QModelIndex(), row, row );
                endInsertRows();
            }
        }
    }
}

void TModel::appendData( int qty_seasons, QString seasons[100][2], int qty_weeks, QString weeks[100][8], int qty_days, QString days[100][100][4] ) {
    DData data;
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
    for (int l = 0; l < qty_days; l++) {
        data.clear();
        data[ 0 ] = days[l][0][0];
        int buf_days[100];
        int buf_tarif[100];
        for(int i = 0; i < days[l][0][1].toInt(); ++i)
        {
            buf_days[i] = days[l][i][2].toInt();
            buf_tarif[i] = days[l][i][3].toInt() + 1;
        }

        //сортировка времени по возростанию
        for(int i = 1; i < days[l][0][1].toInt(); ++i)
        {
            for(int r = 0; r < days[l][0][1].toInt() - i; r++)
            {
                if(buf_days[r] > buf_days[r+1])
                {
                    // Обмен местами
                    int temp = buf_days[r];
                    int temp1 = buf_tarif[r];
                    buf_days[r] = buf_days[r+1];
                    buf_tarif[r] = buf_tarif[r+1];
                    buf_days[r+1] = temp;
                    buf_tarif[r+1] = temp1;
                }
            }
        }
        //цикл по (времени + тарифу) внутри каждого типа дня
        for(int i = 0; i < days[l][0][1].toInt(); ++i){
            if (i < days[l][0][1].toInt() - 1){
                for(int n = buf_days[i]; n < buf_days[i+1]; ++n){
                    data[ n + 1 ] = buf_tarif[i];
                }
            }
            else {
                for(int n = buf_days[days[l][0][1].toInt() - 1]; n < 24; ++n){
                    data[ n + 1 ] = buf_tarif[i];
                }
                for(int n = 0; n < buf_days[0]; ++n){
                    data[ n + 1 ] = buf_tarif[i];
                }
            }
        }
        int row = m_data.count();
        beginInsertRows( QModelIndex(), row, row );
        m_data.append( data );
        endInsertRows();
    }
}

void widget_tarifs::seasons_view(int qty_seasons){
    for (int n = 0; n < qty_seasons; ++n) {
        seasonLayouts[n].addWidget( m_view_seasons[n], 0, 0 );
        w[n].setLayout( &seasonLayouts[n] );
        widg[n] = m_view_seasons[n];
        del = false;
        //вывод в таблицу даты сезона
        int date = seasons[ n ][ 0 ].toInt();
        int d = date % 100;
        QString str_d;
        if ( d < 10 ){
            str_d = str_d.setNum(d);
            str_d = "0" + str_d;
        }
        else str_d = str_d.setNum(d);
        date = date / 100;
        QString str_m;
        if ( date < 10 ){
            str_m = str_m.setNum(date);
            str_m = "0" + str_m;
        }
        else str_m = str_m.setNum(date);
        str_m = str_d + "." + str_m;
        tab_w.addTab( &w[n], str_m );
    }
}

void TModel_s::appendData( int n_tab, int qty_seasons, QString seasons[100][2], int qty_weeks, QString weeks[100][8], int qty_days, QString days[100][100][4] ) {
    DData data;
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
    //цикл по каждому типу недели в сезоне
    for (int k = 0; k < qty_weeks; k++) {
        if ( weeks[k][0] == seasons[ n_tab ][ 1 ] ){
            //цикл по каждому типу дня в неделе
            for (int v = 1; v < 8; v++) {
                for (int l = 0; l < qty_days; l++) {
                    if ( weeks[k][v] == days[l][0][0] ){
                        data.clear();
                        data[ 0 ] = days[l][0][0];
                        int buf_days[100];
                        int buf_tarif[100];
                        for(int i = 0; i < days[l][0][1].toInt(); ++i)
                        {
                            buf_days[i] = days[l][i][2].toInt();
                            buf_tarif[i] = days[l][i][3].toInt() + 1;
                        }
                        //сортировка
                        for(int i = 1; i < days[l][0][1].toInt(); ++i)
                        {
                            for(int r = 0; r < days[l][0][1].toInt() - i; r++)
                            {
                                if(buf_days[r] > buf_days[r+1])
                                {
                                    // Обмен местами
                                    int temp = buf_days[r];
                                    int temp1 = buf_tarif[r];
                                    buf_days[r] = buf_days[r+1];
                                    buf_tarif[r] = buf_tarif[r+1];
                                    buf_days[r+1] = temp;
                                    buf_tarif[r+1] = temp1;
                                }
                            }
                        }
                        //цикл по (времени + тарифу) внутри каждого типа дня
                        for(int i = 0; i < days[l][0][1].toInt(); ++i){
                            if (i < days[l][0][1].toInt() - 1){
                                for(int m = buf_days[i]; m < buf_days[i+1]; ++m){
                                    data[ m + 1 ] = buf_tarif[i];
                                }
                            }
                            else {
                                for(int m = buf_days[days[l][0][1].toInt() - 1]; m < 24; ++m){
                                    data[ m + 1 ] = buf_tarif[i];
                                }
                                for(int m = 0; m < buf_days[0]; ++m){
                                    data[ m + 1 ] = buf_tarif[i];
                                }
                            }
                        }
                        int row = m_data.count();
                        beginInsertRows( QModelIndex(), row, row );
                        m_data.append( data );
                        endInsertRows();
                    }
                }
            }
        }
    }

}

// ********************************************************************************
TModel_special::TModel_special( QObject* parent ) : QAbstractTableModel( parent ) {
}

int TModel_special::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}

int TModel_special::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 26;
}

QVariant TModel_special::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if (role == Qt::BackgroundRole){
        if (index.column() > 1){
            int d = m_data[ index.row() ][ Column( index.column() ) ].toInt();
            switch (d) {
            case 1:
                return QVariant(QBrush(Qt::yellow));
            case 2:
                return QVariant(QBrush(Qt::blue));
            case 3:
                return QVariant(QBrush(Qt::green));
            case 4:
                return QVariant(QBrush(Qt::red));
            }
        }


    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}

bool TModel_special::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if (role != Qt::BackgroundRole){
        emit change_data(index, value.toInt());
        return true;
    }
}

QVariant TModel_special::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return "   ";
    }

    switch( section ) {
    case d:
        return "Дата";
    case c:
        return "№ профиля\\часы";
    case c0:
        return "0";
    case c1:
        return "1";
    case c2:
        return "2";
    case c3:
        return "3";
    case c4:
        return "4";
    case c5:
        return "5";
    case c6:
        return "6";
    case c7:
        return "7";
    case c8:
        return "8";
    case c9:
        return "9";
    case c10:
        return "10";
    case c11:
        return "11";
    case c12:
        return "12";
    case c13:
        return "13";
    case c14:
        return "14";
    case c15:
        return "15";
    case c16:
        return "16";
    case c17:
        return "17";
    case c18:
        return "18";
    case c19:
        return "19";
    case c20:
        return "20";
    case c21:
        return "21";
    case c22:
        return "22";
    case c23:
        return "23";
    }
    return QVariant();
}

Qt::ItemFlags TModel_special::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
        if ( index.column() > 1){
            flags |= Qt::ItemIsEditable;
            flags |= Qt::ItemIsSelectable;
        }
        if ( index.column() == 0){
            flags |= Qt::ItemIsEditable;
            flags |= Qt::ItemIsEnabled;
        }
        if ( index.column() == 1){
            flags |= Qt::ItemIsEditable;
            flags |= Qt::ItemIsEnabled;
        }
    }
    return flags;
}
//*********************************************************************

// ********************************************************************************
TModel_s::TModel_s( QObject* parent ) : QAbstractTableModel( parent ) {
}

int TModel_s::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}

int TModel_s::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 25;
}

QVariant TModel_s::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if (role == Qt::BackgroundRole){
        if (index.column() > 0){
            int d = m_data[ Row( index.row() ) ][ Column( index.column() ) ].toInt();
            switch (d) {
            case 1:
                return QVariant(QBrush(Qt::yellow));
            case 2:
                return QVariant(QBrush(Qt::blue));
            case 3:
                return QVariant(QBrush(Qt::green));
            case 4:
                return QVariant(QBrush(Qt::red));
            }
        }
    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ Row( index.row() ) ][ Column( index.column() ) ];
    }
}

bool TModel_s::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if (role != Qt::BackgroundRole){
        emit change_data(index, value.toInt());
        return true;
    }
}

QVariant TModel_s::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        switch( section ) {
        case pn:
            return "ПН";
        case vt:
            return "ВТ";
        case sr:
            return "СР";
        case ch:
            return "ЧТ";
        case pt:
            return "ПТ";
        case sb:
            return "СБ";
        case vs:
            return "ВС";
        default: return QVariant();
        }
    }
    if( orientation == Qt::Horizontal ) {
        switch( section ) {
        case c:
            return "№ профиля\\часы";
        case c0:
            return "0";
        case c1:
            return "1";
        case c2:
            return "2";
        case c3:
            return "3";
        case c4:
            return "4";
        case c5:
            return "5";
        case c6:
            return "6";
        case c7:
            return "7";
        case c8:
            return "8";
        case c9:
            return "9";
        case c10:
            return "10";
        case c11:
            return "11";
        case c12:
            return "12";
        case c13:
            return "13";
        case c14:
            return "14";
        case c15:
            return "15";
        case c16:
            return "16";
        case c17:
            return "17";
        case c18:
            return "18";
        case c19:
            return "19";
        case c20:
            return "20";
        case c21:
            return "21";
        case c22:
            return "22";
        case c23:
            return "23";
        }
    }
    return QVariant();
}

Qt::ItemFlags TModel_s::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
        if ( index.column() == 0){
            flags |= Qt::ItemIsEditable;
            flags |= Qt::ItemIsEnabled;
        }
    }
    return flags;
}
//*********************************************************************

// ********************************************************************************
TModel::TModel( QObject* parent ) : QAbstractTableModel( parent ) {
}

int TModel::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}

int TModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 25;
}

QVariant TModel::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
    if (role == Qt::BackgroundRole){
        if (index.column() > 0){
            int d = m_data[ index.row() ][ Column( index.column() ) ].toInt();
            switch (d) {
            case 1:
                return QVariant(QBrush(Qt::yellow));
            case 2:
                return QVariant(QBrush(Qt::blue));
            case 3:
                return QVariant(QBrush(Qt::green));
            case 4:
                return QVariant(QBrush(Qt::red));
            }
        }


    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}

bool TModel::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        if ( value.toInt() < 65 ){
            DData data;
            for (int i = 0; i < m_data.count(); ++i) {
                data = m_data.at(i);
                if ( value == data[0] ){
                    emit profile_break();
                    return true;
                }
            }
            m_data[ index.row() ][ Column( index.column() ) ] = value;
            emit dataChanged( index, index );
            return true;
        }
        else return true;
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}

QVariant TModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }
    if( orientation == Qt::Vertical ) {
        return "   ";
    }
    switch( section ) {
    case c:
        return "№ профиля\\часы";
    case c0:
        return "0";
    case c1:
        return "1";
    case c2:
        return "2";
    case c3:
        return "3";
    case c4:
        return "4";
    case c5:
        return "5";
    case c6:
        return "6";
    case c7:
        return "7";
    case c8:
        return "8";
    case c9:
        return "9";
    case c10:
        return "10";
    case c11:
        return "11";
    case c12:
        return "12";
    case c13:
        return "13";
    case c14:
        return "14";
    case c15:
        return "15";
    case c16:
        return "16";
    case c17:
        return "17";
    case c18:
        return "18";
    case c19:
        return "19";
    case c20:
        return "20";
    case c21:
        return "21";
    case c22:
        return "22";
    case c23:
        return "23";
    }
    return QVariant();
}

Qt::ItemFlags TModel::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
        if ( index.column() > 0){
            flags |= Qt::ItemIsEditable;
            flags |= Qt::ItemIsSelectable;
        }
        if ( index.column() == 0){
            flags |= Qt::ItemIsEditable;
            flags |= Qt::ItemIsEnabled;
        }
    }
    return flags;
}
//*********************************************************************

void widget_tarifs::slot_click_Remove_syt(){
    QItemSelectionModel* selectModel = m_view->selectionModel();
    if ( !selectModel->selectedRows().isEmpty() ) {
        if (selectModel->hasSelection()){
            int index = selectModel->selectedRows().first().row();
            int profil = m_model->index_m_model(index);
            for (int n = 0; n < tab_w.count(); ++n) {
                if (m_model_seasons[n]->test_profil_seasons(profil)){
                    emit signal_err_del_profil();
                    return;
                }
            }
            if (m_model_special->test_profil_spec(profil)){
                emit signal_err_del_profil();
                return;
            }
            m_model->removeSelected(index);
        }
    }
}

bool TModel_s::test_profil_seasons(int profil){
    DData data;
    for (int n = 0; n < m_data.count(); ++n) {
        data = m_data.at(n);
        if (data[0].toInt() == profil) return true;
    }
    return false;
}

bool TModel_special::test_profil_spec(int profil){
    DData data;
    for (int n = 0; n < m_data.count(); ++n) {
        data = m_data.at(n);
        if (data[1].toInt() == profil) return true;
    }
    return false;
}

int TModel::index_m_model(int index){
    DData data = m_data.at(index);
    return data[0].toInt();
}

void widget_tarifs::test_day_del(QString g){

}

void TModel::removeSelected(int indexrow) {
    QModelIndex index;
    beginRemoveRows(index, indexrow, indexrow);
    m_data.removeAt(indexrow);
    endRemoveRows();
}

void widget_tarifs::slot_read_tarifs(){
    if (client_addr == 0x30) bn_write_counter->setEnabled(true);
    else bn_write_counter->setEnabled(false);
    transmit = true;
    emit signal_write_data (QByteArray::fromHex("51"));
    count_tout = 0;
    tmr_tout->start(3000);
    count_bar = 34;
    emit signal_bar(count_bar);
}

QByteArray widget_tarifs::tariff_json_pack(QVariantMap vmap_tariff)
{
    QByteArray tt;
    QVariantMap vmap_days = vmap_tariff.value("days", "").toMap();
//    log_1 << qPrintable(QJsonDocument::fromVariant(vmap_days).toJson(QJsonDocument::Indented));
    QMap<int, QVariantMap> md;
    for (QVariantMap::iterator iter = vmap_days.begin(); iter != vmap_days.end(); ++iter) {
        md.insert(iter.key().toInt(), iter.value().toMap());
    }
    for (QMap<int, QVariantMap>::iterator iter = md.begin(); iter != md.end(); ++iter) {
        TARIFF_header th;
        th.days.id_block = 2;
        th.days.day_id = iter.key();
        tt.append((char)(*(char*)&th));
        QVariantMap vmap_day = iter.value();
        QMap<int,int> m;
        for (QVariantMap::iterator iter_day = vmap_day.begin(); iter_day != vmap_day.end(); ++iter_day) {
            m.insert(iter_day.key().toInt(), iter_day.value().toInt());
        }
        for (QMap<int,int>::iterator iter_day = m.begin(); iter_day != m.end(); ++iter_day) {
            TARIFF_zone tz;
            tz.start_zone = iter_day.key();
            tz.tariff = iter_day.value();
            tz.next = (iter_day+1 != m.end());
            uint8_t d1;
            uint8_t d2;
            TARIFF_block_to_u8(&tz, &d1, &d2);
            tt.append((char)d1);
            tt.append((char)d2);
        }
    }
    QVariantMap vmap_weeks = vmap_tariff.value("weeks", "").toMap();
//    log_1 << qPrintable(QJsonDocument::fromVariant(vmap_weeks).toJson(QJsonDocument::Indented));
    md.clear();
    QMap<int, QVariantList> mweek;
    for (QVariantMap::iterator iter = vmap_weeks.begin(); iter != vmap_weeks.end(); ++iter) {
        mweek.insert(iter.key().toInt(), iter.value().toList());
//        md.insert(iter.key().toInt(), iter.value().toMap());
    }
    for (QMap<int, QVariantList>::iterator iter = mweek.begin(); iter != mweek.end(); ++iter) {
        TARIFF_header th;
        th.weeks.id_block = 3;
        th.weeks.week_id = iter.key();
        tt.append((char)(*(char*)&th));
        QVariantList vlist_day = iter.value();
        while (vlist_day.size() < 7) {
            vlist_day.append(0);
        }
        QMap<int,int> m;
        for (int i = 0; i < 7; ++i) {
            if (vlist_day.at(i).toString().isEmpty()) continue;
            int val_day = vlist_day.at(i).toInt();
            int mask = 1 << i;
            for (int j = i+1; j < 7; ++j) {
                if (vlist_day.at(j).toString().isEmpty()) continue;
                if (val_day == vlist_day.at(j).toInt()) {
                    mask += 1 << j;
                    vlist_day[j] = QVariant();
                }
            }
            m.insert(mask, val_day);
        }
//        for (QVariantMap::iterator iter_day = vmap_day.begin(); iter_day != vmap_day.end(); ++iter_day) {
//            m.insert(iter_day.key().toInt(), iter_day.value().toInt());
//        }
        for (QMap<int,int>::iterator iter_week = m.begin(); iter_week != m.end(); ++iter_week) {
            TARIFF_week tw;
            tw.reserv = 0;
            tw.mask_week = iter_week.key();
            tw.day_id = iter_week.value();
            tw.next = (iter_week+1 != m.end());
            uint8_t d1;
            uint8_t d2;
            TARIFF_block_to_u8(&tw, &d1, &d2);
            tt.append((char)d1);
            tt.append((char)d2);
        }
    }

    QVariantMap vmap_seasons = vmap_tariff.value("seasons", "").toMap();
//    log_1 << qPrintable(QJsonDocument::fromVariant(vmap_seasons).toJson(QJsonDocument::Indented));
    {
        TARIFF_header th;
        th.seasons.id_block = 1;
        th.seasons.id_sub_block = 1;
        th.seasons.res = 0;
        tt.append((char)(*(char*)&th));
    }
    QMap<int,int> m;
    for (QVariantMap::iterator iter = vmap_seasons.begin(); iter != vmap_seasons.end(); ++iter) {
        m.insert(iter.key().toInt(), iter.value().toInt());
    }
    for (QMap<int,int>::iterator iter_season = m.begin(); iter_season != m.end(); ++iter_season) {
        TARIFF_season ts;
        ts.month = iter_season.key() / 100;
        ts.day = iter_season.key() % 100;
        ts.week_id = iter_season.value();
        ts.next = (iter_season+1 != m.end());
        uint8_t d1;
        uint8_t d2;
        TARIFF_block_to_u8(&ts, &d1, &d2);
        tt.append((char)d1);
        tt.append((char)d2);
    }

    QVariantMap special_days = vmap_tariff.value("special_days", "").toMap();
    if (!special_days.isEmpty()) {
//    log_1 << qPrintable(QJsonDocument::fromVariant(special_days).toJson(QJsonDocument::Indented));
        {
            TARIFF_header th;
            th.special_day.id_block = 1;
            th.special_day.id_sub_block = 2;
            th.special_day.res = 0;
            tt.append((char)(*(char*)&th));
        }
        m.clear();
        for (QVariantMap::iterator iter = special_days.begin(); iter != special_days.end(); ++iter) {
            m.insert(iter.key().toInt(), iter.value().toInt());
        }
        for (QMap<int,int>::iterator iter_special_days = m.begin(); iter_special_days != m.end(); ++iter_special_days) {
    //        log_1 << iter_special_days.key() << iter_special_days.value();
            TARIFF_special_day tsd;
            tsd.month = iter_special_days.key() / 100;
            tsd.day = iter_special_days.key() % 100;
            tsd.day_id = iter_special_days.value();
            tsd.next = (iter_special_days+1 != m.end());
            uint8_t d1;
            uint8_t d2;
            TARIFF_block_to_u8(&tsd, &d1, &d2);
            tt.append((char)d1);
            tt.append((char)d2);
        }
    }
    uint32_t activate = vmap_tariff.value("activate", "").toUInt();
    if (activate) {
        {
            TARIFF_header th;
            th.activate.id_block = 1;
            th.activate.id_sub_block = 3;
            th.activate.res = 0;
            tt.append((char)(*(char*)&th));

        }
        tt.append((char)((activate >> 0) & 0xFF));
        tt.append((char)((activate >> 8) & 0xFF));
        tt.append((char)((activate >>16) & 0xFF));
        tt.append((char)((activate >>24) & 0xFF));
    }
    uint8_t res = DLMS_tariff_test_buf((uint8_t*)tt.data(), tt.size());
    tt.prepend(0x51);
    log_1 << "pack" << res << tt.toHex().toUpper();
    if (!res) return tt;
//    518000008181A40D64841800C0 8101 8604 7800 504580
 //   return (QByteArray::fromHex("518000008181A40D64841800C08101A6047800504580"));
    return QByteArray();
}

QVariantMap widget_tarifs::tariff_json_unpack (QByteArray tariff){
    log_1 << "unpack" << tariff.toHex().toUpper();
    tariff = tariff.mid(1);
    QVariantMap vmap;
    QVariantMap vmap_days;
    QVariantMap vmap_weeks;
    QVariantMap vmap_seasons;
    QVariantMap vmap_special_days;
    uint32_t activate = 0;
    int index = 0;
    for (;;) {
        if (index >= tariff.size()) {
            break;
        }
    //    log_1 << QByteArray(&tariff.data()[index], tariff.size() - index).toHex().toUpper();
        TARIFF_header th;
        *((uint8_t*)&th) = (uint8_t)(tariff.data()[index]); index++;
   //     log_1 << th.activate.id_block << th.activate.id_sub_block;
        switch (th.activate.id_block) {
        case 2: { // days
            QVariantMap day;
            for (;;) {
                TARIFF_zone tz;
                TARIFF_block_from_u8(&tz, (uint8_t)(tariff.data()[index]), (uint8_t)(tariff.data()[index+1])); index+=2;
                day.insert(QString::number(tz.start_zone), tz.tariff);
                if (!tz.next) break;
            }
            vmap_days.insert(QString::number(th.days.day_id), day);
            break;
        }
        case 3: { // weeks
            int16_t week[] = {-1,-1,-1,-1,-1,-1,-1};
//            QVariantMap week;
            for (;;) {
                TARIFF_week tz;
                TARIFF_block_from_u8(&tz, (uint8_t)(tariff.data()[index]), (uint8_t)(tariff.data()[index+1])); index+=2;
                for (int i = 0; i < 7; ++i) {
                    uint8_t shift_weekday = 1<<i;
                    if ((tz.mask_week & shift_weekday)) { //  && week[i] == -1
                        week[i] = tz.day_id;
                    }
                }
//                week.insert(QString::number(tz.mask_week), tz.day_id);
                if (!tz.next) break;
            }
            QVariantList vlweek;
            for (int i = 0; i < 7; ++i) {
                vlweek << week[i];
            }
            vmap_weeks.insert(QString::number(th.weeks.week_id), vlweek);
//            vmap_weeks.insert(QString::number(th.weeks.week_id), week);
            break;
        }
        case 1: { // ext
            switch (th.activate.id_sub_block) {
            case 1: { // seasons
                for (;;) {
                    TARIFF_season tz;
                    TARIFF_block_from_u8(&tz, (uint8_t)(tariff.data()[index]), (uint8_t)(tariff.data()[index+1])); index+=2;
                    vmap_seasons.insert(QString::number(tz.month * 100 + tz.day), tz.week_id);
                    if (!tz.next) break;
                }
                break;
            }
            case 2: { // special_day
                for (;;) {
                    TARIFF_special_day tz;
                    TARIFF_block_from_u8(&tz, (uint8_t)(tariff.data()[index]), (uint8_t)(tariff.data()[index+1])); index+=2;
                    vmap_special_days.insert(QString::number(tz.month * 100 + tz.day), tz.day_id);
                    if (!tz.next) break;
                }
                break;
            }
            case 3: { // activate
                activate = 0;
                activate += ((uint32_t)(tariff.data()[index++])) << 0;
                activate += ((uint32_t)(tariff.data()[index++])) << 8;
                activate += ((uint32_t)(tariff.data()[index++])) <<16;
                activate += ((uint32_t)(tariff.data()[index++])) <<24;
                break;
            }
            case 0: {
//                log_1 << "error TARIFF_sub_header";
//                break;
                return QVariantMap();
            }
            }
            break;
        }
        default: {
 //           log_1 << "error TARIFF_header";
 //           break;
            return QVariantMap();
        }
        }
    }
    if (!vmap_days.isEmpty()) {
        vmap.insert("days", vmap_days);
    }
    if (!vmap_weeks.isEmpty()) {
        vmap.insert("weeks", vmap_weeks);
    }
    if (!vmap_seasons.isEmpty()) {
        vmap.insert("seasons", vmap_seasons);
    }
    if (!vmap_special_days.isEmpty()) {
        vmap.insert("special_days", vmap_special_days);
    }
    if (activate) {
        vmap.insert("activate", activate);
    }
    return vmap;
}

void widget_tarifs::TARIFF_block_to_u8(void *b, uint8_t *first, uint8_t *second)
{
    if (!first || !second || !b) return;
    (*first) = *((uint8_t *)b + 1);
    (*second) = *((uint8_t *)b + 0);
}

uint8_t widget_tarifs::DLMS_tariff_test_buf(uint8_t* buff, uint16_t buff_len)
{
    uint8_t * tt = buff;
    uint16_t index = 0;
    uint8_t day_ids[64];
    uint8_t week_ids[64];
    uint8_t day_ids_index = 0;
    uint8_t week_ids_index = 0;
    memset(day_ids,  DLMS_tariff_index_init_val, sizeof(day_ids));
    memset(week_ids, DLMS_tariff_index_init_val, sizeof(week_ids));
    while (index < buff_len - 1) {
        TARIFF_header th;
        *((uint8_t*)&th) = tt[index];
        index++;
        switch (th.activate.id_block) {
        case 2: { // days
            day_ids[day_ids_index++] = th.days.day_id;
            TARIFF_zone tz;
            while (index < buff_len - 1) {
                TARIFF_block_from_u8(&tz, tt[index], tt[index+1]); index += 2;
                if (tz.start_zone >= 60*24) return 0x21;
                if (tz.tariff >= 4) return 0x22;
                if (!tz.next) break;
            }
            break;
        }
        case 3: { // weeks
            week_ids[week_ids_index++] = th.weeks.week_id;
            uint8_t mask_week = 0x7F;
            TARIFF_week tw;
            while (index < buff_len - 1) {
                TARIFF_block_from_u8(&tw, tt[index], tt[index+1]); index += 2;
                if (tw.reserv) return 0x31;
                mask_week ^= tw.mask_week;
                {
                    uint8_t flag = 0;
                    for (uint8_t i = 0; i < day_ids_index; ++i) {
                        if (day_ids[i] == tw.day_id) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) return 0x32;
                }
                if (!tw.next) break;
            }
            if (mask_week) return 0x33;
            break;
        }
        case 1: { // ext
            switch (th.activate.id_sub_block) {
            case 1: { // seasons
                if (th.seasons.res) return 0x91;
                TARIFF_season ts;
                while (index < buff_len - 1) {
                    TARIFF_block_from_u8(&ts, tt[index], tt[index+1]); index += 2;
                    if (ts.day > 31 || !ts.day) return 0x92;
                    if (ts.month > 12 || !ts.month) return 0x93;
                    {
                        uint8_t flag = 0;
                        for (uint8_t i = 0; i < week_ids_index; ++i) {
                            if (week_ids[i] == ts.week_id) {
                                flag = 1;
                                break;
                            }
                        }
                        if (!flag) return 0x94;
                    }
                    if (!ts.next) break;
                }
                break;
            }
            case 2: { // special_day
                if (th.special_day.res) return 0xA1;
                TARIFF_special_day tsd;
                while (index < buff_len - 1) {
                    TARIFF_block_from_u8(&tsd, tt[index], tt[index+1]); index += 2;
                    if (tsd.day > 31 || !tsd.day) return 0xA2;
                    if (tsd.month > 12 || !tsd.month) return 0xA3;
                    {
                        uint8_t flag = 0;
                        for (uint8_t i = 0; i < day_ids_index; ++i) {
                            if (day_ids[i] == tsd.day_id) {
                                flag = 1;
                                break;
                            }
                        }
                        if (!flag) return 0xA4;
                    }
                    if (!tsd.next) break;
                }
                break;
            }
            case 3: {
                if (th.activate.res) return 0xB1;
                index += 4;
                break;
            }
            default: return 0xC1;
            }
            break;
        }
        default:
            return 0x01;
        }
    }
    return 0;
}

void widget_tarifs::TARIFF_block_from_u8(void *b, uint8_t first, uint8_t second)
{
    if (!b) return;
    *((uint8_t *)b + 1) = first;
    *((uint8_t *)b + 0) = second;
}
