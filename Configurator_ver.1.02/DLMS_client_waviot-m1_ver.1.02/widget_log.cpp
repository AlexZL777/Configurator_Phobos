#include "widget_log.h"
#include "ui_widget_log.h"
#include <interface.h>

#include <Logger/Logger.h>
#include <QJsonDocument>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QModelIndex>
#include <QLabel>
#include <math.h>

extern QByteArray sn;
uint32_t type_data;
extern int count_bar;
extern QDateTime qdt;
bool radio;
bool ts_meterings_LessThan(const QVariant &s1, const QVariant &s2);
bool ch_box_fl;

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

widget_log::widget_log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_log)
{
    ui->setupUi(this);

    tmr_t_out = new QTimer();
    connect(tmr_t_out, SIGNAL(timeout()), this, SLOT(timeout()));

    transmit = false;

    setLayout( &mainLayout );

    QGridLayout* gridLayout = new QGridLayout;
    mainLayout.addLayout( gridLayout );

    QLabel* label1 = new QLabel( trUtf8( "Выберите тип данных: " ) );
    label1->setAlignment( Qt::AlignRight );
    gridLayout->addWidget( label1, 0, 0 );

    combo->addItem("Месяцы", 1);
    combo->addItem("Сутки", 2);
    combo->addItem("Часы", 3);
    combo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gridLayout->addWidget( combo, 0, 1 );
    gridLayout->setAlignment(combo, Qt::AlignLeft);

    QPushButton* bn = new QPushButton( trUtf8( "Сохранить в xls" ) );
    connect( bn, SIGNAL( clicked() ), this, SLOT( slot_click_bn() ) );
    bn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gridLayout->addWidget( bn, 0, 2 );
    gridLayout->setAlignment( bn, Qt::AlignLeft);


    QLabel* label2 = new QLabel( trUtf8( "За какой промежуток времени считать данные: " ) );
    label2->setAlignment( Qt::AlignRight );
    gridLayout->addWidget( label2, 1, 0 );

    radio1->setText("все данные");    
    gridLayout->addWidget( radio1, 1, 1 );
    gridLayout->setAlignment( radio1, Qt::AlignLeft);

    gridLayout->addWidget( ch_box, 1, 2 );
    gridLayout->setAlignment( ch_box, Qt::AlignLeft);
    ch_box->setChecked(false);
    ch_box->hide();
    ch_box_fl = false;

    radio2->setText("выбрать промежуток времени");
    gridLayout->addWidget( radio2, 2, 1 );
    gridLayout->setAlignment( radio2, Qt::AlignLeft);

    QPushButton* bn_file = new QPushButton( trUtf8( "Загрузить из файла" ) );
    connect( bn_file, SIGNAL( clicked() ), this, SLOT( slot_click_bn_file() ) );
    bn_file->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    gridLayout->addWidget( bn_file, 2, 2 );
    gridLayout->setAlignment( bn_file, Qt::AlignLeft);
    bn_file->hide();

    connect(radio1, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    connect(radio2, SIGNAL(toggled(bool)), this, SLOT(slotRadioToggled(bool)));
    radio1->setChecked(true);
    radio = true;

    label3->setAlignment( Qt::AlignRight );
    gridLayout->addWidget( label3, 3, 0 );

    dt1->setCalendarPopup ( true );
    dt1->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    gridLayout->addWidget( dt1, 3, 1 );
    gridLayout->setAlignment( dt1, Qt::AlignLeft);

    label4->setAlignment( Qt::AlignRight );
    gridLayout->addWidget( label4, 4, 0 );

    dt2->setCalendarPopup ( true );
    dt2->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    gridLayout->addWidget( dt2, 4, 1 );
    gridLayout->setAlignment( dt2, Qt::AlignLeft);

    m_view_log = new QTableView;
    m_view_log->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );
    m_view_log->verticalHeader()->hide();
    m_view_log->setModel( m_model_log = new TModel_log );
    mainLayout.addWidget( m_view_log );

    n_set_data = -1;
    n_set_data_max = 0;
}

widget_log::~widget_log()
{
    delete ui;
}

bool widget_log::transmitt(){
    return transmit;
}

QList< QHash< int, QVariant > > TModel_log::return_m_data(){
    return m_data;
}

void widget_log::slot_click_bn_file(){
    type_data = combo->currentData().toUInt();
    QVariantMap vmap;
    QFile file("D:\\log_hour.txt");
    if ( file.open(QIODevice::ReadOnly) ){
        QByteArray arr;
        arr = file.readAll();
        file.close();
        QJsonDocument d = QJsonDocument::fromJson(arr);
        QVariant v = d.toVariant();
        vmap = v.toMap();
   //     log_1 << "vmap" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
        QVariantMap vm = path_report_history(vmap, 1);
   //     log_1 << "vm" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        ch_box_fl = ch_box->isChecked();
        m_model_log->insert_row( vm, time_from_form_min(), time_from_form_max());
    }
}

void widget_log::slot_click_bn(){

    QXlsx::Document xlsx;
    for (int col=1; col<26; ++col){
        switch( col ) {
            case 1:
                xlsx.write(1, col, "счётчик");
                break;
            case 2:
                xlsx.write(1, col, "профиль");
                break;
            case 3:
                xlsx.write(1, col, "index");
                break;
            case 4:
                xlsx.write(1, col, "время счётчика");
                break;
            case 5:
                xlsx.write(1, col, "Pmax, Вт");
                break;
            case 6:
                xlsx.write(1, col, "A+Tсум, кВт⋅ч");
                break;
            case 7:
                xlsx.write(1, col, "А+Т1, кВт⋅ч");
                break;
            case 8:
                xlsx.write(1, col, "А+Т2, кВт⋅ч");
                break;
            case 9:
                xlsx.write(1, col, "А+Т3, кВт⋅ч");
                break;
            case 10:
                xlsx.write(1, col, "А+Т4, кВт⋅ч");
                break;
            case 11:
                xlsx.write(1, col, "А-Тсум, кВт⋅ч");
                break;
            case 12:
                xlsx.write(1, col, "А-Т1, кВт⋅ч");
                break;
            case 13:
                xlsx.write(1, col, "А-Т2, кВт⋅ч");
                break;
            case 14:
                xlsx.write(1, col, "А-Т3, кВт⋅ч");
                break;
            case 15:
                xlsx.write(1, col, "А-Т4, кВт⋅ч");
                break;
            case 16:
                xlsx.write(1, col, "R+Tсум, квар⋅ч");
                break;
            case 17:
                xlsx.write(1, col, "R+T1, квар⋅ч");
                break;
            case 18:
                xlsx.write(1, col, "R+T2, квар⋅ч");
                break;
            case 19:
                xlsx.write(1, col, "R+T3, квар⋅ч");
                break;
            case 20:
                xlsx.write(1, col, "R+T4, квар⋅ч");
                break;
            case 21:
                xlsx.write(1, col, "R-Tсум, квар⋅ч");
                break;
            case 22:
                xlsx.write(1, col, "R-T1, квар⋅ч");
                break;
            case 23:
                xlsx.write(1, col, "R-T2, квар⋅ч");
                break;
            case 24:
                xlsx.write(1, col, "R-T3, квар⋅ч");
                break;
            case 25:
                xlsx.write(1, col, "R-T4, квар⋅ч");
                break;
        }
    }
    QList< QHash< int, QVariant > > m_data = m_model_log->return_m_data();
    for (int row = 2; row < m_data.count() + 2; ++row) {
        for (int col = 1; col<26; ++col) {
            QHash< int, QVariant > data_row = m_data.at(row - 2);
            if ( col == 1 ) xlsx.write(row, col, data_row[col - 1].toInt());
            if ( col == 3 ){
                if ( !data_row[col-1].isNull() ) xlsx.write(row, col, data_row[col - 1].toInt());
            }
            if ( col == 2 || col == 4 ) xlsx.write(row, col, data_row[col - 1]);
            if ( col > 4 ){
                if ( !data_row[col-1].isNull() ) xlsx.write(row, col, data_row[col - 1].toDouble());
            }
        }
    }
    QFileDialog dialog(this);
    QString str = dialog.getSaveFileName(this, "Save file", "C:", "*.xlsx");
    xlsx.saveAs(str);
//    QVariantMap vmap;
//    QFile file1("logg.txt");
//    if ( file1.open(QIODevice::ReadOnly) ){
//        QByteArray arr;
//        arr = file1.readAll();
//        file1.close();
//        QJsonDocument d = QJsonDocument::fromJson(arr);
//        QVariant v = d.toVariant();
//        vmap = v.toMap();
//    //    log_1 << "111" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
//        QVariantList vlist = vmap["meterings"].toList();
//        QVariantMap vm;
//        QVariantList vlist2;
//        for (int n = 0; n < vlist.count(); ++n) {
//            for (int i = 0; i < vlist.count(); ++i) {
//                vm = vlist.at(i).toMap();
//                if (vm["index"].toInt() == n){
//                    vm.insert("index", n);
//                    if (vm.contains("profile")){
//                        if (vm["profile"].toString() == "1.0.99.1.0.255"){
//                            vm.insert("type", 15);
//                        }
//                        else if (vm["profile"].toString() == "1.0.98.2.0.255"){
//                            vm.insert("type", 14);
//                        }
//                        else if (vm["profile"].toString() == "1.0.98.1.0.255"){
//                            vm.insert("type", 13);
//                        }
//                    }
//                    if (vm.contains("1.0.0")){
//                        vm.insert("ts", vm["1.0.0"].toInt());
//                        vm.remove("1.0.0");
//                    }
//                    if (vm.contains("1.6.0")){
//                        vm.insert("1.0.1.6.0.255", vm["1.6.0"].toFloat()/1000);
//                        vm.remove("1.6.0");
//                    }
//                    if (vm.contains("1.8.0")){
//                        vm.insert("1.0.1.8.0.255", vm["1.8.0"].toFloat()/1000);
//                        vm.remove("1.8.0");
//                    }
//                    if (vm.contains("1.8.1")){
//                        vm.insert("1.0.1.8.1.255", vm["1.8.1"].toFloat()/1000);
//                        vm.remove("1.8.1");
//                    }
//                    if (vm.contains("1.8.2")){
//                        vm.insert("1.0.1.8.2.255", vm["1.8.2"].toFloat()/1000);
//                        vm.remove("1.8.2");
//                    }
//                    if (vm.contains("1.8.3")){
//                        vm.insert("1.0.1.8.3.255", vm["1.8.3"].toFloat()/1000);
//                        vm.remove("1.8.3");
//                    }
//                    if (vm.contains("1.8.4")){
//                        vm.insert("1.0.1.8.4.255", vm["1.8.4"].toFloat()/1000);
//                        vm.remove("1.8.4");
//                    }
//                    if (vm.contains("2.8.0")){
//                        vm.insert("2.0.2.8.0.255", vm["2.8.0"].toInt());
//                        vm.remove("2.8.0");
//                    }
//                    if (vm.contains("2.8.1")){
//                        vm.insert("2.0.2.8.1.255", vm["2.8.1"].toInt());
//                        vm.remove("2.8.1");
//                    }
//                    if (vm.contains("2.8.2")){
//                        vm.insert("2.0.2.8.2.255", vm["2.8.2"].toInt());
//                        vm.remove("2.8.2");
//                    }
//                    if (vm.contains("2.8.3")){
//                        vm.insert("2.0.2.8.3.255", vm["2.8.3"].toInt());
//                        vm.remove("2.8.3");
//                    }
//                    if (vm.contains("2.8.4")){
//                        vm.insert("2.0.2.8.4.255", vm["2.8.4"].toInt());
//                        vm.remove("2.8.4");
//                    }
//                    if (vm.contains("3.8.0")){
//                        vm.insert("2.0.3.8.0.255", vm["3.8.0"].toInt());
//                        vm.remove("3.8.0");
//                    }
//                    if (vm.contains("3.8.1")){
//                        vm.insert("2.0.3.8.1.255", vm["3.8.1"].toInt());
//                        vm.remove("3.8.1");
//                    }
//                    if (vm.contains("3.8.2")){
//                        vm.insert("2.0.3.8.2.255", vm["3.8.2"].toInt());
//                        vm.remove("3.8.2");
//                    }
//                    if (vm.contains("3.8.3")){
//                        vm.insert("2.0.3.8.3.255", vm["3.8.3"].toInt());
//                        vm.remove("3.8.3");
//                    }
//                    if (vm.contains("3.8.4")){
//                        vm.insert("2.0.3.8.4.255", vm["3.8.4"].toInt());
//                        vm.remove("3.8.4");
//                    }
//                    if (vm.contains("4.8.0")){
//                        vm.insert("2.0.4.8.0.255", vm["4.8.0"].toInt());
//                        vm.remove("4.8.0");
//                    }
//                    if (vm.contains("4.8.1")){
//                        vm.insert("2.0.4.8.1.255", vm["4.8.1"].toInt());
//                        vm.remove("4.8.1");
//                    }
//                    if (vm.contains("4.8.2")){
//                        vm.insert("2.0.4.8.2.255", vm["4.8.2"].toInt());
//                        vm.remove("4.8.2");
//                    }
//                    if (vm.contains("4.8.3")){
//                        vm.insert("2.0.4.8.3.255", vm["4.8.3"].toInt());
//                        vm.remove("4.8.3");
//                    }
//                    if (vm.contains("4.8.4")){
//                        vm.insert("2.0.4.8.4.255", vm["4.8.4"].toInt());
//                        vm.remove("4.8.4");
//                    }
//                //    log_1 << "vm" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
//                    vlist2 << vm;
//                    break;
//                }
//            }
//        }
//        vmap.insert("meterings", vlist2);
//     //   log_1 << "122" << qPrintable(QJsonDocument::fromVariant(vlist2).toJson(QJsonDocument::Indented));
//    }
//    m_model_log->insert_row( path_report_history(vmap, 0), time_from_form_min(), time_from_form_max());
}

void widget_log::slotRadioToggled(bool value){
    if (!value) return;
    if ( radio1->isChecked() ) {
        radio = true;
        label3->hide();
        dt1->hide();
        label4->hide();
        dt2->hide();
    }
    else if ( radio2->isChecked() ) {
        radio = false;
        label3->show();
        dt1->show();
        label4->show();
        dt2->show();
    }
}

void widget_log::timeout(){
    log_1 << "count_tout" << count_tout;
    if (count_tout < 2){
        count_tout++;
        tmr_t_out->start(3000);
        set_request_data( type, (uint32_t)n_set_data, n_set_data_max);
    }
    else if ( count_tout == 2 ) {
        count_tout++;
  //      log_1 << "signal_on_pushButton_connect_clicked";
        emit signal_on_pushButton_connect_clicked(true);
        tmr_t_out->start(3000);
    }
    else if ( count_tout > 2 ) {
        transmit = false;
        tmr_t_out->stop();
        n_set_data = -1;
        n_set_data_max = 0;
        emit signal_timeout_start (100);
      //  emit signal_disable_tab_kn(0, 5);
    }
}

void widget_log::slot_stop_read_log(){
    transmit = false;
    m_model_log->removeTable();
    tmr_t_out->stop();
    n_set_data = -1;
    n_set_data_max = 0;
}

void widget_log::slot_read_log(){
 //   log_1 << "n_set_data" << n_set_data << n_set_data_max;
    if (n_set_data > -1 && n_set_data_max > 0) {
        count_tout = 0;
        tmr_t_out->start(3000);
        set_request_data( type, (uint32_t)n_set_data, n_set_data_max);
    }
    else{
        count_tout = 0;
        m_model_log->removeTable();
        transmit = true;
        type_data = combo->currentData().toUInt();
        n_set_data = -1;
        n_set_data_max = 0;
        switch (type_data) {
            case 1: { //месяцы
                emit signal_write_data(QByteArray::fromHex("EF0F0D"));//0x0D - 13
                break;
            }
            case 2: { //сутки
                emit signal_write_data(QByteArray::fromHex("EF0F0E"));//0x0E - 14
                break;
            }
            case 3: { //часы
                emit signal_write_data(QByteArray::fromHex("EF0F0F"));//0x0F - 15
                type_data_hour = 1;
                break;
            }
        }
     //   emit signal_timeout_start(5000);
        count_tout = 0;
    }
}

void TModel_log::removeTable(){
    for (int n = m_data.count(); n > -1 ; n--) {
        beginRemoveRows(QModelIndex(), n, n);
        m_data.removeAt(n);
        endRemoveRows();
    }
}

void widget_log::slot_log_read(QByteArray data){
  //  log_1 << "12345676788990";
    if (transmit){
        transmit = false;
     //   log_1 << "data_log" << data.toHex().toUpper();
        uint8_t * buf_start = (uint8_t *)data.data();
        uint8_t * buf = buf_start;
        uint8_t header = *buf++;
        if (header == 0xEF) parse_arch(data);
        else {
            parse_data_arch(data);
        }
    }
}

void widget_log::set_request_data(uint32_t type, uint32_t index, uint32_t data_max){

    QByteArray arr = QByteArray(127+2, 0);
    uint8_t * drbuffer_head = (uint8_t *)arr.data();
    *drbuffer_head++ = 0xEF;
    *drbuffer_head++ = 0x10;
    uint32_t val = type; //тип архива
    *drbuffer_head++ = (val >> 0) & 0xFF;
    val = (uint32_t)n_set_buf[data_max - index];//индекс записи
    val = val << 4;
    *drbuffer_head++ = (val >> 8) & 0xFF;
    *drbuffer_head++ = (val >> 0) & 0xFF;
    arr = arr.mid(0, drbuffer_head - (uint8_t *)arr.data());
    log_1 << "tx_electro5" << arr.toHex().toUpper();
    transmit = true;
    emit signal_write_data(arr);
    tmr_t_out->start(3000);
  //  emit signal_timeout_start(5000);
}

void widget_log::slot_disconnect(){
    tmr_t_out->stop();
    n_set_data = -1;
    n_set_data_max = 0;
    m_model_log->removeTable();
    m_model_log->clear_m_data();
    vmap_month.clear();
    vmap_day.clear();
    vmap_hour.clear();
}

void TModel_log::clear_m_data(){
    m_data.clear();
}

// ********************************************************************************
TModel_log::TModel_log( QObject* parent ) : QAbstractTableModel( parent ) {
}

int TModel_log::rowCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return m_data.count();
}

int TModel_log::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent )
    return 25;
}

QVariant TModel_log::data( const QModelIndex& index, int role ) const {
    if( !index.isValid() ||
        m_data.count() <= index.row() ||
        ( role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::BackgroundRole) ) {
        return QVariant();
    }
//    if (role == Qt::BackgroundRole){
//        if (index.column() > 0){
//            int d = m_data[ index.row() ][ Column( index.column() ) ].toInt();
//            switch (d) {
//            case 1:
//                return QVariant(QBrush(Qt::yellow));
//            case 2:
//                return QVariant(QBrush(Qt::blue));
//            case 3:
//                return QVariant(QBrush(Qt::green));
//            case 4:
//                return QVariant(QBrush(Qt::red));
//            }
//        }
//    }
    if( role == Qt::DisplayRole || role == Qt::EditRole ) {
        return m_data[ index.row() ][ Column( index.column() ) ];
    }
}

bool TModel_log::setData( const QModelIndex& index, const QVariant& value, int role ) {
    if( !index.isValid() || role != Qt::EditRole || m_data.count() <= index.row() ) {
        return false;
    }
    if ( index.column() == 0 && ( role == Qt::DisplayRole || role == Qt::EditRole ) ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
//        if ( value.toInt() < 65 ){
//            DData data;
//            for (int i = 0; i < m_data.count(); ++i) {
//                data = m_data.at(i);
//                if ( value == data[0] ){
//                    emit profile_break();
//                    return true;
//                }
//            }
//            m_data[ index.row() ][ Column( index.column() ) ] = value;
//            emit dataChanged( index, index );
//            return true;
//        }
//        else return true;
    }
    else if ( role != Qt::BackgroundRole ){
        m_data[ index.row() ][ Column( index.column() ) ] = value;
        emit dataChanged( index, index );
    }
    return true;
}

QVariant TModel_log::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return "   ";
    }

    switch( section ) {
    case c0:
        return "счётчик";
    case c1:
        return "   профиль   ";
    case c2:
        return "index";
    case c3:
        return "время счётчика";
    case c4:
        return "Pmax, Вт";
    case c5:
        return "A+Tсум, кВт⋅ч";
    case c6:
        return "А+Т1, кВт⋅ч";
    case c7:
        return "А+Т2, кВт⋅ч";
    case c8:
        return "А+Т3, кВт⋅ч";
    case c9:
        return "А+Т4, кВт⋅ч";
    case c10:
        return "А-Тсум, кВт⋅ч";
    case c11:
        return "А-Т1, кВт⋅ч";
    case c12:
        return "А-Т2, кВт⋅ч";
    case c13:
        return "А-Т3, кВт⋅ч";
    case c14:
        return "А-Т4, кВт⋅ч";
    case c15:
        return "R+Tсум, квар⋅ч";
    case c16:
        return "R+T1, квар⋅ч";
    case c17:
        return "R+T2, квар⋅ч";
    case c18:
        return "R+T3, квар⋅ч";
    case c19:
        return "R+T4, квар⋅ч";
    case c20:
        return "R-Tсум, квар⋅ч";
    case c21:
        return "R-T1, квар⋅ч";
    case c22:
        return "R-T2, квар⋅ч";
    case c23:
        return "R-T3, квар⋅ч";
    case c24:
        return "R-T4, квар⋅ч";
    }

    return QVariant();
}

Qt::ItemFlags TModel_log::flags( const QModelIndex& index ) const {
    Qt::ItemFlags flags = QAbstractTableModel::flags( index );
    if( index.isValid() ) {
        flags = nullptr;
    }
    return flags;
}
//*********************************************************************

void widget_log::parse_arch(QByteArray arr){

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
                    //    log_1 << "111" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
                        n_set_data = count_max-1;
                        n_set_data_max = count_max-1;
                        uint16_t index_head_t = index_head;
                        for (int n = 0; n < index_head; ++n) {
                            n_set_buf[n] = --index_head_t;
                         //   log_1 << "n" << n << n_set_buf[n];
                        }
                        uint16_t count_max_t = count_max;
                        for (int n = index_head; n < count_max; ++n) {
                            n_set_buf[n] = --count_max_t;
                         //   log_1 << "n" << n << n_set_buf[n];
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

void widget_log::parse_data_arch(QByteArray arr){
    count_tout = 0;
 //   log_1 << "count_tout" << count_tout;
    uint8_t * buf_start = (uint8_t *)arr.data();
    uint8_t * buf = buf_start;
    uint8_t header = *buf++;
    int buf_size = arr.size();
    switch (header) {
        case 0x42: // COSEM профиль u32
        case 0x44: // COSEM суточные u32
        case 0x46: // COSEM месячные u32
        case 0x48: // COSEM годовые u32
        case 0x4A: // COSEM настраиваемый u32
        {
            if (buf_size < 1 + 2 + 4) {
    //            vmap_packet.insert("error", "no header data");
                break;
            }
            Parser_ul_data ul_data;
            ul_data.index = *buf++;
            ul_data.index <<= 4;
            ul_data.index_ext = *buf++;
            ul_data.index += (ul_data.index_ext >> 4) & 0xF;
            ul_data.index_ext &= 0xF;
            uint32_t timestamp;
            timestamp = *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++; timestamp <<= 8;
            timestamp+= *buf++;
            ul_data.ts = timestamp;
            while (buf - buf_start + 6 <= buf_size) {
                OBIS obis;
                buf += ElectroGet_OBIS(buf, &obis);
                uint32_t val;
                if (buf - buf_start + 4 > buf_size) break;
                val = *buf++; val <<= 8;
                val+= *buf++; val <<= 8;
                val+= *buf++; val <<= 8;
                val+= *buf++;
                if (obis.D == 7) {
                    int32_t ival = *(int32_t*)&val;
                    ul_data.data.insert(obis, ((double)ival)/1000);
                } else if (obis.D == 3) {
                    ul_data.data.insert(obis, val);
                } else {
                    ul_data.data.insert(obis, ((double)val)/1000);
                }
            }
            QVariantMap vmap_data;
            vmap_data.insert("ts", ul_data.ts);
            vmap_data.insert("index", ul_data.index);
          //  vmap_data.insert("index_ext", ul_data.index_ext);
            vmap_data.insert("type", type);
            for (QMap<OBIS_cpp, QVariant>::iterator iter = ul_data.data.begin(); iter != ul_data.data.end(); ++iter) {
                OBIS_cpp obis_cpp = iter.key();
                QVariant val = iter.value();
                vmap_data.insert(obis_cpp.toString(), val);
            }
            vl << vmap_data;
          //  log_1 << "1111111" << qPrintable(QJsonDocument::fromVariant(vl).toJson(QJsonDocument::Indented));
            data_arch(vl);
            break;
        }
    }
}

void widget_log::slot_log_event_empty_arr(){
    if (transmit){
        transmit = false;
        count_tout = 0;
        data_arch(vl);
    }
}

void widget_log::data_arch(QVariantList vl_){
    QVariantMap vmap;
    vmap.insert("meterings", vl_);
 //   log_1 << "333333" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
    tmr_t_out->stop();
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
        if (type_data == 3 && type_data_hour == 1){
            vmap_hour = vmap;

            emit signal_write_data(QByteArray::fromHex("EF0F0E"));//0x0E - 14
            type_data_hour = 2;
            transmit = true;
            tmr_t_out->start(3000);
        //    emit signal_timeout_start(5000);
            count_tout = 0;
        }
        else if (type_data == 3 && type_data_hour == 2){
            type_data_hour = 0;
        //    log_1 << "1111111" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
            QVariantMap vm;
            ch_box_fl = ch_box->isChecked();
            if (!ch_box_fl) vm = path_report_history_hour(vmap, vmap_hour);
            else vm = orig_data(vmap_hour);
          //  log_1 << "2222222" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            m_model_log->insert_row( vm, time_from_form_min(), time_from_form_max());
            vmap_hour.clear();
            vmap_hour = vm;
        }
        else if (type_data == 2) {
         //   log_1 << "1111112" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
            QVariantMap vm;
            ch_box_fl = ch_box->isChecked();
            if (!ch_box_fl) vm = path_report_history(vmap, 0);
            else vm = orig_data(vmap);
            m_model_log->insert_row( vm, time_from_form_min(), time_from_form_max());
            vmap_day.clear();
            vmap_day = vm;
        }
        else {
          //  log_1 << "1111111" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
            QVariantMap vm;
            ch_box_fl = ch_box->isChecked();
            if (!ch_box_fl) vm = path_report_history(vmap, 0);
            else vm = orig_data(vmap);
            log_1 << "2222222" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            m_model_log->insert_row( vm, time_from_form_min(), time_from_form_max());
            vmap_month.clear();
            vmap_month = vm;
        }
        emit signal_disable_tab_kn(0, 5);
    }

//        QByteArray arr = QJsonDocument::fromVariant(vmap/*path_report_history(vmap)*/).toJson(QJsonDocument::Indented);
//        if (type_data == 1 ){
//            QFile file("log_month.txt");
//            if ( file.open(QIODevice::WriteOnly) ){
//                file.write(arr);
//                file.close();
//            }
//        }
//        else if (type_data == 2 ){
//            QFile file("log_day.txt");
//            if ( file.open(QIODevice::WriteOnly) ){
//                file.write(arr);
//                file.close();
//            }
//        }
//        else if (type_data == 3 ){
//            QFile file("log_hour.txt");
//            if ( file.open(QIODevice::WriteOnly) ){
//                file.write(arr);
//                file.close();
//            }
//        }
     //   m_model_log->insert_row( vmap/*path_report_history(vmap)*/, time_from_form_min(), time_from_form_max());

//                QFile file1("logg.txt");
//                if ( file1.open(QIODevice::ReadOnly) ){
//                      QDataStream out(&file1);
//                      out >> vmap;
//                      file1.close();
//                }
       //     }
      //  }
}

QVariantMap widget_log::orig_data(QVariantMap vmap){
    QVariantList vlist = vmap["meterings"].toList();
    QVariantMap vm;
    QVariantList vlist2;
    double t1, t2, t3, t4, r1, r2, r3, r4;
    for (int n = 0; n < vlist.count(); ++n) {
        for (int i = 0; i < vlist.count(); ++i) {
            vm = vlist.at(i).toMap();
            if (vm["index"].toInt() == n){
                log_1 << "vm1" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
                vm.insert("index", n);
                if (vm.contains("ts")){
                    vm.insert("1.0.0", vm["ts"].toInt());
                    vm.remove("ts");
                }
                if (vm.contains("1.0.1.6.0.255")){
                    vm.insert("1.6.0", vm["1.0.1.6.0.255"].toDouble()*1000);
                    vm.remove("1.0.1.6.0.255");
                }
                t1 = 0; t2 = 0; t3 = 0; t4 = 0;
                if (vm.contains("1.0.1.8.1.2551")){
                    t1 = vm["1.0.1.8.1.255"].toDouble()*1000;
                    vm.insert("1.8.1", t1);
                    vm.remove("1.0.1.8.1.255");
                }
                if (vm.contains("1.0.1.8.2.255")){
                    t2 = vm["1.0.1.8.2.255"].toDouble()*1000;
                    vm.insert("1.8.2", t2);
                    vm.remove("1.0.1.8.2.255");
                }
                if (vm.contains("1.0.1.8.3.255")){
                    t3 = vm["1.0.1.8.3.255"].toDouble()*1000;
                    vm.insert("1.8.3", t3);
                    vm.remove("1.0.1.8.3.255");
                }
                if (vm.contains("1.0.1.8.4.255")){
                    t4 = vm["1.0.1.8.4.255"].toDouble()*1000;
                    vm.insert("1.8.4", t4);
                    vm.remove("1.0.1.8.4.255");
                }
                if (vm.contains("1.0.1.8.0.255")){
                    vm.insert("1.8.0", vm["1.0.1.8.0.255"].toDouble()*1000);
                    vm.remove("1.0.1.8.0.255");
                }
                else {
                    vm.insert("1.8.0", t1 + t2 + t3 + t4 );
                    vm.remove("1.0.1.8.0.255");
                }
                t1 = 0; t2 = 0; t3 = 0; t4 = 0;
                if (vm.contains("1.0.2.8.1.255")){
                    t1 = vm["1.0.2.8.1.255"].toDouble()*1000;
                    vm.insert("2.8.1", t1);
                    vm.remove("1.0.2.8.1.255");
                }
                if (vm.contains("1.0.2.8.2.255")){
                    t2 = vm["1.0.2.8.2.255"].toDouble()*1000;
                    vm.insert("2.8.2", t2);
                    vm.remove("1.0.2.8.2.255");
                }
                if (vm.contains("1.0.2.8.3.255")){
                    t3 = vm["1.0.2.8.3.255"].toDouble()*1000;
                    vm.insert("2.8.3", t3);
                    vm.remove("1.0.2.8.3.255");
                }
                if (vm.contains("1.0.2.8.4.255")){
                    t4 = vm["1.0.2.8.4.255"].toDouble()*1000;
                    vm.insert("2.8.4", t4);
                    vm.remove("1.0.2.8.4.255");
                }
                if (vm.contains("1.0.2.8.0.255")){
                    vm.insert("2.8.0", vm["1.0.2.8.0.255"].toDouble()*1000);
                    vm.remove("1.0.2.8.0.255");
                }
                else {
                    vm.insert("2.8.0", t1 + t2 + t3 + t4 );
                    vm.remove("1.0.2.8.0.255");
                }
                r1 = 0; r2 = 0; r3 = 0; r4 = 0;
                if (vm.contains("1.0.3.8.1.255")){
                    r1 = vm["1.0.3.8.1.255"].toDouble()*1000;
                    vm.insert("3.8.1", r1);
                    vm.remove("1.0.3.8.1.255");
                }
                if (vm.contains("1.0.3.8.2.255")){
                    r2 = vm["1.0.3.8.2.255"].toDouble()*1000;
                    vm.insert("3.8.2", r2);
                    vm.remove("1.0.3.8.2.255");
                }
                if (vm.contains("1.0.3.8.3.255")){
                    r3 = vm["1.0.3.8.3.255"].toDouble()*1000;
                    vm.insert("3.8.3", r3);
                    vm.remove("1.0.3.8.3.255");
                }
                if (vm.contains("1.0.3.8.4.255")){
                    r4 = vm["1.0.3.8.4.255"].toDouble()*1000;
                    vm.insert("3.8.4", r4);
                    vm.remove("1.0.3.8.4.255");
                }
                if (vm.contains("1.0.3.8.0.255")){
                    vm.insert("3.8.0", vm["1.0.3.8.0.255"].toDouble()*1000);
                    vm.remove("1.0.3.8.0.255");
                }
                else {
                    vm.insert("3.8.0", r1 + r2 + r3 + r4 );
                    vm.remove("1.0.3.8.0.255");
                }
                r1 = 0; r2 = 0; r3 = 0; r4 = 0;
                if (vm.contains("1.0.4.8.1.255")){
                    r1 = vm["1.0.4.8.1.255"].toDouble()*1000;
                    vm.insert("4.8.1", r1);
                    vm.remove("1.0.4.8.1.255");
                }
                if (vm.contains("1.0.4.8.2.25")){
                    r2 = vm["1.0.4.8.2.25"].toDouble()*1000;
                    vm.insert("4.8.2", r2);
                    vm.remove("1.0.4.8.2.25");
                }
                if (vm.contains("1.0.4.8.3.255")){
                    r3 = vm["1.0.4.8.3.255"].toDouble()*1000;
                    vm.insert("4.8.3", r3);
                    vm.remove("1.0.4.8.3.255");
                }
                if (vm.contains("1.0.4.8.4.255")){
                    r4 = vm["1.0.4.8.4.255"].toDouble()*1000;
                    vm.insert("4.8.4", r4);
                    vm.remove("1.0.4.8.4.255");
                }
                if (vm.contains("1.0.4.8.0.255")){
                    vm.insert("4.8.0", vm["1.0.4.8.0.255"].toDouble()*1000);
                    vm.remove("1.0.4.8.0.255");
                }
                else {
                    vm.insert("4.8.0", r1 + r2 + r3 + r4 );
                    vm.remove("1.0.4.8.0.255");
                }
                log_1 << "vm2" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
                vlist2 << vm;
                break;
            }
        }
    }
    for (int n = 0; n < vlist2.count()/2; ++n) {
        vlist2.swap(n, vlist2.count()-n-1);
    }
    vmap.insert("meterings", vlist2);
    return vmap;
}

int widget_log::time_from_form_min(){
    QDateTime d = dt1->dateTime();
    return d.toTime_t() + d.offsetFromUtc();
}

int widget_log::time_from_form_max(){
    QDateTime d = dt2->dateTime();
    return d.toTime_t() + d.offsetFromUtc();
}

void widget_log::slot_view_log(){

    type_data = combo->currentData().toUInt();
    ch_box_fl = ch_box->isChecked();
    if ( type_data == 1 ){
        m_model_log->insert_row( vmap_month/*path_report_history(vmap)*/, time_from_form_min(), time_from_form_max());
    }
    if ( type_data == 2 ){
        m_model_log->insert_row( vmap_day/*path_report_history(vmap)*/, time_from_form_min(), time_from_form_max());
    }
    if ( type_data == 3 ){
        m_model_log->insert_row( vmap_hour/*path_report_history(vmap)*/, time_from_form_min(), time_from_form_max());
    }
}

void TModel_log::insert_row(QVariantMap vmap, int date_form_min, int date_form_max){
    removeTable();
    QDateTime dt;
  //  uint idt = dt.currentDateTime().toUTC().toLocalTime().toTime_t();
    uint iqdt = qdt.toTime_t() + 10800;
 //   log_1 << "dt" << idt << iqdt;
    QVariantList vlist = vmap["meterings"].toList();
//    for (int n = 0; n < vlist.count()/2; ++n) {
//        vlist.swap(n, vlist.count()-n-1);
//    }
  //  log_1 << "222" << qPrintable(QJsonDocument::fromVariant(vlist).toJson(QJsonDocument::Indented));
    QVariantMap v;
    if ( radio ){
        for (int n = 0; n < vlist.count(); ++n) {
            v = vlist.at(n).toMap();
            if (v.contains("1.0.0")){
                uint ts = v["1.0.0"].toUInt();
                if (!ch_box_fl){
                    if ( ts > 1533070800 && ts < iqdt){
                        insert_row_data(v);
                    }
                }
                else insert_row_data(v);

            }
//            if (v.contains("ts")){
//                uint ts = v["ts"].toUInt();
//                if ( ts > 1533070800 && ts < iqdt){
//                    insert_row_data(v);
//                }
//            }
        }
    }
    else {
        for (int n = 0; n < vlist.count(); ++n) {
            v = vlist.at(n).toMap();
            if (v.contains("1.0.0")){
                uint ts = v["1.0.0"].toUInt();
                if (!ch_box_fl){
                    if ( ts >= date_form_min && ts <= date_form_max && ts > 1533070800  && ts < iqdt ){
                        insert_row_data(v);
                    }
                }
                else insert_row_data(v);
            }
//            if (v.contains("ts")){
//                uint ts = v["ts"].toUInt();
//                if ( ts >= date_form_min && ts <= date_form_max && ts > 1533070800  && ts < iqdt ){
//                    insert_row_data(v);
//                }
//            }
        }
    }
}

//void TModel_log::insert_row_data(QVariantMap vmap){
//    DData data;
//    double t1, t2, t3, t4, r1, r2, r3, r4;
//    data[0] = sn.toUpper();
//    switch (type_data) {
//        case 1: { //месяцы
//            data[1] = "1.0.98.1.0.255";
//            break;
//        }
//        case 2: { //сутки
//            data[1] = "1.0.98.2.0.255";
//            break;
//        }
//        case 3: { //часы
//            data[1] = "1.0.99.1.0.255";
//            break;
//        }
//    }
//    if (vmap.contains("index")) data[2] = vmap["index"];
//    if (vmap.contains("ts")){
//        QDateTime date = QDateTime::fromTime_t(vmap["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
//   //     log_1 << "date" << vmap["1.0.0"].toUInt() << date;
//        data[3] = date.toString("dd.MM.yyyy hh:mm:ss");
//    }
//    if (vmap.contains("1.0.1.6.0.255")) data[4] = vmap["1.0.1.6.0.255"].toDouble();
// //   else data[4] = 0;
//    if (vmap.contains("1.0.1.8.1.255")){
//        t1 = vmap["1.0.1.8.1.255"].toDouble();
//       // t1 = t1 / 1000;
//    //    int t1b = t1 - t1a;
//        data[6] = QString::number(t1);
//    }
//    else{
//        t1 = 0;
//     //   data[6] = 0;
//    }
//    if (vmap.contains("1.0.1.8.2.255")){
//        t2 = vmap["1.0.1.8.2.255"].toDouble();
//       // t2 = t2 / 1000;
//        data[7] = QString::number(t2);
//    }
//    else{
//        t2 = 0;
//     //   data[7] = 0;
//    }
//    if (vmap.contains("1.0.1.8.3.255")){
//        t3 = vmap["1.0.1.8.3.255"].toDouble();
//      //  t3 = t3 / 1000;
//        data[8] = QString::number(t3);
//    }
//    else{
//        t3 = 0;
//     //   data[8] = 0;
//    }
//    if (vmap.contains("1.0.1.8.4.255")){
//        t4 = vmap["1.0.1.8.4.255"].toDouble();
//     //   t4 = t4 / 1000;
//        data[9] = QString::number(t4);
//    }
//    else{
//        t4 = 0;
//      //  data[9] = 0;
//    }
//    data[5] = QString::number(t1 + t2 + t3 + t4);
//    if (vmap.contains("1.0.2.8.1.255")){
//        t1 = vmap["1.0.2.8.1.255"].toDouble();
//     //   t1 = t1 / 1000;
//        data[11] = QString::number(t1);
//    }
//    else{
//        t1 = 0;
//      //  data[11] = 0;
//    }
//    if (vmap.contains("1.0.2.8.2.255")){
//        t2 = vmap["1.0.2.8.2.255"].toDouble();
//     //  t2 = t2 / 1000;
//        data[12] = QString::number(t2);
//    }
//    else{
//        t2 = 0;
//      // data[12] = 0;
//    }
//    if (vmap.contains("1.0.2.8.3.255")){
//        t3 = vmap["1.0.2.8.3.255"].toDouble();
//     //   t3 = t3 / 1000;
//        data[13] = QString::number(t3);
//    }
//    else{
//        t3 = 0;
//      //  data[13] = 0;
//    }
//    if (vmap.contains("1.0.2.8.4.255")){
//        t4 = vmap["1.0.2.8.4.255"].toDouble();
//      //  t4 = t4 / 1000;
//        data[14] = QString::number(t4);
//    }
//    else{
//        t4 = 0;
//      //  data[14] = 0;
//    }
//    data[10] = QString::number(t1 + t2 + t3 + t4);
//    if (vmap.contains("1.0.3.8.1.255")){
//        r1 = vmap["1.0.3.8.1.255"].toDouble();
//     //   r1 = r1 / 1000;
//        data[16] = QString::number(r1);
//    }
//    else{
//        r1 = 0;
//     //  data[16] = 0;
//    }
//    if (vmap.contains("1.0.3.8.2.255")){
//        r2 = vmap["1.0.3.8.2.255"].toDouble();
//     //   r2 = r2 / 1000;
//        data[17] = QString::number(r2);
//    }
//    else{
//        r2 = 0;
//      //  data[17] = 0;
//    }
//    if (vmap.contains("1.0.3.8.3.255")){
//        r3 = vmap["1.0.3.8.3.255"].toDouble();
//     //   r3 = r3 / 1000;
//        data[18] = QString::number(r3);
//    }
//    else{
//        r3 = 0;
//     //   data[18] = 0;
//    }
//    if (vmap.contains("1.0.3.8.4.255")){
//        r4 = vmap["1.0.3.8.4.255"].toDouble();
//     //   r4 = r4 / 1000;
//        data[19] = QString::number(r4);
//    }
//    else{
//        r4 = 0;
//      //  data[19] = 0;
//    }
//    data[15] = QString::number(r1 + r2 + r3 + r4);
//    if (vmap.contains("1.0.4.8.1.255")){
//        r1 = vmap["1.0.4.8.1.255"].toDouble();
//     //   r1 = r1 / 1000;
//        data[21] = QString::number(r1);
//    }
//    else{
//        r1 = 0;
//        data[21] = 0;
//    }
//    if (vmap.contains("1.0.4.8.2.255")){
//        r2 = vmap["1.0.4.8.2.255"].toDouble();
//    //    r2 = r2 / 1000;
//        data[22] = QString::number(r2);
//    }
//    else{
//        r2 = 0;
//        data[22] = 0;
//    }
//    if (vmap.contains("1.0.4.8.3.255")){
//        r3 = vmap["1.0.4.8.3.255"].toDouble();
//    //    r3 = r3 / 1000;
//        data[23] = QString::number(r3);
//    }
//    else{
//        r3 = 0;
//        data[23] = 0;
//    }
//    if (vmap.contains("1.0.4.8.4.255")){
//        r4 = vmap["1.0.4.8.4.255"].toDouble();
//    //    r4 = r4 / 1000;
//        data[24] = QString::number(r4);
//    }
//    else{
//        r4 = 0;
//        data[24] = 0;
//    }
//    data[20] = QString::number(r1 + r2 + r3 + r4);
//    int row = m_data.count();
//    beginInsertRows( QModelIndex(), row, row );
//    m_data.append( data );
//    endInsertRows();
//}

void TModel_log::insert_row_data(QVariantMap vmap){
  //  log_1 << "vmap" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
    DData data;
    double t1, t2, t3, t4, r1, r2, r3, r4;
    data[0] = sn.toUpper();
    switch (type_data) {
        case 1: { //месяцы
            data[1] = "1.0.98.1.0.255";
            break;
        }
        case 2: { //сутки
            data[1] = "1.0.98.2.0.255";
            break;
        }
        case 3: { //часы
            data[1] = "1.0.99.1.0.255";
            break;
        }
    }
    if (vmap.contains("index")) data[2] = vmap["index"];
    if (vmap.contains("1.0.0")){
        QDateTime date = QDateTime::fromTime_t(vmap["1.0.0"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
        data[3] = date.toString("dd.MM.yyyy hh:mm:ss");
    }
    if (vmap.contains("1.6.0")) data[4] = vmap["1.6.0"];
 //   else data[4] = 0;
    if (vmap.contains("1.8.1")){
        t1 = vmap["1.8.1"].toDouble();
        t1 = t1 / 1000;
    //    int t1b = t1 - t1a;
        data[6] = QString::number(t1);
    }
    else{
        t1 = 0;
     //   data[6] = 0;
    }
    if (vmap.contains("1.8.2")){
        t2 = vmap["1.8.2"].toDouble();
        t2 = t2 / 1000;
        data[7] = QString::number(t2);
    }
    else{
        t2 = 0;
     //   data[7] = 0;
    }
    if (vmap.contains("1.8.3")){
        t3 = vmap["1.8.3"].toDouble();
        t3 = t3 / 1000;
        data[8] = QString::number(t3);
    }
    else{
        t3 = 0;
     //   data[8] = 0;
    }
    if (vmap.contains("1.8.4")){
        t4 = vmap["1.8.4"].toDouble();
        t4 = t4 / 1000;
        data[9] = QString::number(t4);
    }
    else{
        t4 = 0;
      //  data[9] = 0;
    }
    if (t1 == 0 && t2 == 0 && t3 == 0 && t4 == 0){
        if (vmap.contains("1.8.0")) data[5] = QString::number(vmap["1.8.0"].toDouble()/1000);
    }
    else data[5] = QString::number(t1 + t2 + t3 + t4);
    if (vmap.contains("2.8.1")){
        t1 = vmap["2.8.1"].toDouble();
        t1 = t1 / 1000;
        data[11] = QString::number(t1);
    }
    else{
        t1 = 0;
      //  data[11] = 0;
    }
    if (vmap.contains("2.8.2")){
        t2 = vmap["2.8.2"].toDouble();
        t2 = t2 / 1000;
        data[12] = QString::number(t2);
    }
    else{
        t2 = 0;
      // data[12] = 0;
    }
    if (vmap.contains("2.8.3")){
        t3 = vmap["2.8.3"].toDouble();
        t3 = t3 / 1000;
        data[13] = QString::number(t3);
    }
    else{
        t3 = 0;
      //  data[13] = 0;
    }
    if (vmap.contains("2.8.4")){
        t4 = vmap["2.8.4"].toDouble();
        t4 = t4 / 1000;
        data[14] = QString::number(t4);
    }
    else{
        t4 = 0;
      //  data[14] = 0;
    }
    if (t1 == 0 && t2 == 0 && t3 == 0 && t4 == 0){
        if (vmap.contains("2.8.0")) data[10] = QString::number(vmap["2.8.0"].toDouble()/1000);
    }
    else data[10] = QString::number(t1 + t2 + t3 + t4);
    if (vmap.contains("3.8.1")){
        r1 = vmap["3.8.1"].toDouble();
        r1 = r1 / 1000;
        data[16] = QString::number(r1);
    }
    else{
        r1 = 0;
     //  data[16] = 0;
    }
    if (vmap.contains("3.8.2")){
        r2 = vmap["3.8.2"].toDouble();
        r2 = r2 / 1000;
        data[17] = QString::number(r2);
    }
    else{
        r2 = 0;
      //  data[17] = 0;
    }
    if (vmap.contains("3.8.3")){
        r3 = vmap["3.8.3"].toDouble();
        r3 = r3 / 1000;
        data[18] = QString::number(r3);
    }
    else{
        r3 = 0;
     //   data[18] = 0;
    }
    if (vmap.contains("3.8.4")){
        r4 = vmap["3.8.4"].toDouble();
        r4 = r4 / 1000;
        data[19] = QString::number(r4);
    }
    else{
        r4 = 0;
      //  data[19] = 0;
    }
    if (r1 == 0 && r2 == 0 && r3 == 0 && r4 == 0){
        if (vmap.contains("3.8.0")) data[15] = QString::number(vmap["3.8.0"].toDouble()/1000);
    }
    else data[15] = QString::number(r1 + r2 + r3 + r4);
    if (vmap.contains("4.8.1")){
        r1 = vmap["4.8.1"].toDouble();
        r1 = r1 / 1000;
        data[21] = QString::number(r1);
    }
    else{
        r1 = 0;
        data[21] = 0;
    }
    if (vmap.contains("4.8.2")){
        r2 = vmap["4.8.2"].toDouble();
        r2 = r2 / 1000;
        data[22] = QString::number(r2);
    }
    else{
        r2 = 0;
        data[22] = 0;
    }
    if (vmap.contains("4.8.3")){
        r3 = vmap["4.8.3"].toDouble();
        r3 = r3 / 1000;
        data[23] = QString::number(r3);
    }
    else{
        r3 = 0;
        data[23] = 0;
    }
    if (vmap.contains("4.8.4")){
        r4 = vmap["4.8.4"].toDouble();
        r4 = r4 / 1000;
        data[24] = QString::number(r4);
    }
    else{
        r4 = 0;
        data[24] = 0;
    }
    if (r1 == 0 && r2 == 0 && r3 == 0 && r4 == 0){
        if (vmap.contains("4.8.0")) data[20] = QString::number(vmap["4.8.0"].toDouble()/1000);
    }
    else data[20] = QString::number(r1 + r2 + r3 + r4);
    int row = m_data.count();
    beginInsertRows( QModelIndex(), row, row );
    m_data.append( data );
    endInsertRows();
}

void widget_log::on_pushButton_clicked()
{
  //  set_request_data();
}

QVariantMap widget_log::path_report_history_hour(QVariantMap req, QVariantMap vmap_hour){
    QVariantMap vmap;
    QVariantList vl = req["meterings"].toList();
 //   log_1 << "day" << qPrintable(QJsonDocument::fromVariant(req).toJson(QJsonDocument::Indented));
    QVariantList vl_hour = vmap_hour["meterings"].toList();
 //   log_1 << "hour" << qPrintable(QJsonDocument::fromVariant(vmap_hour).toJson(QJsonDocument::Indented));
    for (int n = 0; n < vl_hour.count(); ++n) {
        vl.append(vl_hour.at(n));
    }
 //   log_1 << "all 1" << qPrintable(QJsonDocument::fromVariant(vl).toJson(QJsonDocument::Indented));
//    return vmap;
    //сортировка времени по возростанию
    for ( int i = 1; i < vl.count(); ++i )
    {
        for (int r = 0; r < vl.count() - i; r++)
        {
            QVariantMap vm1 = vl.at(r).toMap();
            QVariantMap vm2 = vl.at(r+1).toMap();
            int v1 = 0, v2 = 0;
            if ( vm1.contains("ts") ) v1 = vm1.value( "ts", QVariantMap() ).toInt();
            if ( vm2.contains("ts") ) v2 = vm2.value( "ts", QVariantMap() ).toInt();
            if ( v1 > v2 )
            {
                // Обмен местами
                vl.replace(r, vm2);
                vl.replace(r+1, vm1);
            }
        }
    }
    vmap.insert("meterings", vl);
    log_1 << "all 2" << qPrintable(QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented));
    QByteArray arr = QJsonDocument::fromVariant(vmap).toJson(QJsonDocument::Indented);
    QFile file("D:\\log_hour.txt");
    if ( file.open(QIODevice::WriteOnly) ){
        file.write(arr);
        file.close();
    }
    return /*vmap;*/ path_report_history(vmap, 1);
}

QVariantMap widget_log::path_report_history(QVariantMap req, bool fl_hour)
{
    auto type_to_obis = [] (uint32_t type, uint32_t ts) -> QString {
        switch (type) {
        case DLMS_ARCH_profile_year:    return "1.0.94.7.8.255"; //годовые
        case DLMS_ARCH_profile_month:   return "1.0.98.1.0.255"; //месячные
        case DLMS_ARCH_profile_day:     return "1.0.98.2.0.255"; //суточные
        case DLMS_ARCH_profile_hour:    return "1.0.99.1.0.255"; //часовой
        case DLMS_ARCH_profile_set:     return "1.0.94.7.5.255"; //настраиваемый
        case 0x40: return "1.0.94.7.0.255"; //мгновенные
        case 0x32:
        case 0x42: return "1.0.99.1.0.255"; //часовой
        case 0x31: if (ts % (60*60*24)) break; else return "1.0.98.2.0.255"; //суточные
        case 0x44: return "1.0.98.2.0.255"; //суточные
        case 0x46: return "1.0.98.1.0.255"; //месячные
        case 0x48: return "1.0.94.7.8.255"; //годовые
        case 0x4A: return "1.0.94.7.5.255"; //настраиваемый
        };
        return "1.0.94.7.0.255";
    };

    auto round_D7_out = [] (double val) -> double {
        double out = val * 1000;
        int64_t out_int = out;
        out = out_int;
        return out / 1000;
    };

    bool is_E0_only = false;
    QMap<uint16_t, double> vals;
  //  log_1 << "123" << qPrintable(QJsonDocument::fromVariant(req).toJson(QJsonDocument::Indented));
    QVariantList vlist = req["meterings"].toList();
  //  log_1 << "124" << qPrintable(QJsonDocument::fromVariant(vlist).toJson(QJsonDocument::Indented));
 //   log_1 << "www" << vlist.count();
    QVariantList meterings;
    QVariantMap tsm_hour;
    QVariantMap tsm_day;
    QVariantMap tsm_other;
    QVariantMap tsm_last;
    if (!fl_hour){
        for (int n = 0; n < vlist.count()/2; ++n) {
            vlist.swap(n, vlist.count()-n-1);
        }
    }
    foreach (QVariant v, vlist) {
        QVariantMap vm = v.toMap();

    //    QDateTime date2 = QDateTime::fromTime_t(vm["ts"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
    //    vm.insert("sts", date2.toString("dd.MM.yyyy hh:mm:ss"));
    //    log_1 << "start" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        uint type_rec = vm["type"].toUInt();
     //   uint type_rec_temp = type_rec;
     //   if (type_data == 3) type_rec = 15;
   //     log_1 << "type_rec" << type_rec;
        uint ts = vm.value("ts", 0).toUInt();
        if ( ts < 1533070800 ) continue;
   //     log_1 << "ts" << ts;
        if (type_rec == DLMS_ARCH_profile_hour) {
           // log_1 << "bbbbbbbb" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
            if (vm.contains("1.0.1.8.0.255") || vm.contains("1.0.2.8.0.255") || vm.contains("1.0.3.8.0.255") || vm.contains("1.0.4.8.0.255")) {
                is_E0_only = true;
            }
            if (vm.contains("1.0.1.8.1.255") || vm.contains("1.0.2.8.1.255") || vm.contains("1.0.3.8.1.255") || vm.contains("1.0.4.8.1.255") ||
                vm.contains("1.0.1.8.2.255") || vm.contains("1.0.2.8.2.255") || vm.contains("1.0.3.8.2.255") || vm.contains("1.0.4.8.2.255") ||
                vm.contains("1.0.1.8.3.255") || vm.contains("1.0.2.8.3.255") || vm.contains("1.0.3.8.3.255") || vm.contains("1.0.4.8.3.255") ||
                vm.contains("1.0.1.8.4.255") || vm.contains("1.0.2.8.4.255") || vm.contains("1.0.3.8.4.255") || vm.contains("1.0.4.8.4.255")) {
                is_E0_only = false;
            }
     //       log_1 << "is_E0_only" << is_E0_only;
     //       if (!is_E0_only) log_1 << "bbbbbbbb" << qPrintable(QJsonDocument::fromVariant(vm).toJson(QJsonDocument::Indented));
        }
        QVariantMap ts_meterings;
        for (QVariantMap::iterator iter = vm.begin(); iter != vm.end(); ++iter) {
            QRegExp obis_rx("1.0.(\\d+).(\\d+).(\\d+).255");
            if (!obis_rx.indexIn(iter.key(), 0)) {
                uint8_t C = obis_rx.cap(1).toInt();
                uint8_t D = obis_rx.cap(2).toInt();
                uint8_t E = obis_rx.cap(3).toInt();
                QString obis_out_str;
                obis_out_str = QString("%1.%2.%3").arg(C).arg(D).arg(E);
                double value = iter.value().toDouble();
                if ((C % 20) <= 10 && C <= 80) {
                    value *= 1000;
                }
                if (D != 8) {
                    ts_meterings.insert(obis_out_str, round_D7_out(value));
                } else {
              //      log_1 << "C D E" << C << D << E;
                    if (type_rec == DLMS_ARCH_profile_hour) {
                        uint32_t v256 = value;
                        v256 /= 256;
                  //      log_1 << "value" << value << "v256" << v256;
                        uint32_t vram = vals.value((C << 4) + E);
                        vram /= 256;
                  //      log_1 << "vals.value" << vals.value((C << 4) + E) << "vram" << vram;
                        if (v256 <= vram && C >= 3) { // fix R in 0x43
                   //         log_1 << "continue1";
                            continue;
                        }
                        if (value <= vals.value((C << 4) + E)) {
                   //         log_1 << "continue2";
                            continue;
                        }
                    }
                //    log_1 << "vals.insert" << (C << 4) + E << value;
                    vals.insert((C << 4) + E, value);
                    if (type_rec == 0x40) {
                        ts_meterings.insert(obis_out_str, round_D7_out(value));
                    }
                }
            }
         //   log_1 << "vals" << vals;
        }
        if (!is_E0_only || type_rec == DLMS_ARCH_profile_day || type_rec == DLMS_ARCH_profile_month || type_rec == DLMS_ARCH_profile_year) {
            vals.insert(0x10, vals.value(0x11, 0) + vals.value(0x12, 0) + vals.value(0x13, 0) + vals.value(0x14, 0));
            vals.insert(0x20, vals.value(0x21, 0) + vals.value(0x22, 0) + vals.value(0x23, 0) + vals.value(0x24, 0));
            vals.insert(0x30, vals.value(0x31, 0) + vals.value(0x32, 0) + vals.value(0x33, 0) + vals.value(0x34, 0));
            vals.insert(0x40, vals.value(0x41, 0) + vals.value(0x42, 0) + vals.value(0x43, 0) + vals.value(0x44, 0));
        }
        if (type_rec == DLMS_ARCH_profile_hour || type_rec == DLMS_ARCH_profile_day || type_rec == DLMS_ARCH_profile_month || type_rec == DLMS_ARCH_profile_year) {
            for (int C = 1; C <= 4; ++C) {
                for (int E = 0; E <= 4; ++E) {
                    if (is_E0_only && E && type_rec == DLMS_ARCH_profile_hour) continue;
                    ts_meterings.insert(QString("%1.8.%2").arg(C).arg(E), (uint32_t)(vals.value((C << 4) + E, 0)+0.5));
                }
            }
         //   log_1 << "ts_meterings.insert" << qPrintable(QJsonDocument::fromVariant(ts_meterings).toJson(QJsonDocument::Indented));
        }

        ts_meterings.insert("1.0.0", ((uint32_t)(ts/60)) * 60);
        ts_meterings.insert("ts_get", vm.value("ts_get", 0).toInt());
        ts_meterings.insert("index", vm.value("index", 0).toInt());
        ts_meterings.insert("profile", type_to_obis(vm.value("type", 0).toInt(), vm.value("ts", 0).toInt()));
        ts_meterings.insert("type", type_rec);
     //   QDateTime date1 = QDateTime::fromTime_t(((uint32_t)(ts/60)) * 60).toTimeSpec(Qt::OffsetFromUTC);
     //   ts_meterings.insert("0.0.0", date1.toString("dd.MM.yyyy hh:mm:ss"));
     //   log_1 << "ts_meterings" << qPrintable(QJsonDocument::fromVariant(ts_meterings).toJson(QJsonDocument::Indented));

        int prof_index = vm.value("index", 0).toInt();
   //     log_1 << "prof_index" << prof_index;
        if (type_rec == DLMS_ARCH_profile_hour && tsm_hour.contains("profile")) {
            int prof_index_last = tsm_hour.value("index", 0).toInt();
     //       log_1 << "prof_index_last" << prof_index_last;
            if (prof_index_last + 1 == prof_index) {
                uint32_t ts = ts_meterings.value("1.0.0").toUInt();
     //           log_1 << "ts" << ts;
                QVariantMap ts_meterings_tmp = ts_meterings;
                ts_meterings_tmp.remove("index");
     //           log_1 << "ts_meterings_tmp" << qPrintable(QJsonDocument::fromVariant(ts_meterings_tmp).toJson(QJsonDocument::Indented));
                uint32_t ts_hour_last = tsm_hour.value("1.0.0").toUInt();
     //           log_1 << "ts_hour_last" << ts_hour_last;
                uint32_t t_period = 60*60;
                while (ts - ts_hour_last > t_period && meterings.size() < 10000) {
     //               log_1 << "ts" << ts << "ts_hour_last" << ts_hour_last << "t_period" << t_period << "meterings.size()" << meterings.size();
                    ts_hour_last /= t_period;
     //               log_1 << "ts_hour_last /= t_period" << ts_hour_last;
                    ts_hour_last ++;
     //               log_1 << "ts_hour_last ++" << ts_hour_last;
                    ts_hour_last *= t_period;
     //               log_1 << "ts_hour_last *= t_period" << ts_hour_last;
                    ts_meterings_tmp.insert("1.0.0", ts_hour_last);
     //               QDateTime date = QDateTime::fromTime_t(ts_hour_last).toTimeSpec(Qt::OffsetFromUTC);
     //               ts_meterings_tmp.insert("0.0.0", date.toString("dd.MM.yyyy hh:mm:ss"));
                    meterings.prepend(ts_meterings_tmp);
                    ts_meterings_tmp.insert("1.6.0", 0);
                    ts_meterings.insert("1.6.0", 0);
                }
             //   log_1 << "ts_meterings_tmp" << qPrintable(QJsonDocument::fromVariant(meterings).toJson(QJsonDocument::Indented));
            }
         //   QDateTime date = QDateTime::fromTime_t(ts_meterings["1.0.0"].toUInt()).toTimeSpec(Qt::OffsetFromUTC);
         //   log_1 << date.toString("dd.MM.yyyy hh:mm:ss");
         //   ts_meterings.insert("0.0.0", date.toString("dd.MM.yyyy hh:mm:ss"));
        //    log_1 << "ts_meterings2" << qPrintable(QJsonDocument::fromVariant(ts_meterings).toJson(QJsonDocument::Indented));
        }
        if (type_rec == DLMS_ARCH_profile_day && tsm_day.contains("profile")) {
            int prof_index_last = tsm_day.value("index", 0).toInt();
            if (prof_index_last + 1 == prof_index) {
                uint32_t ts = ts_meterings.value("1.0.0").toUInt();
                QVariantMap ts_meterings_tmp = ts_meterings;
                ts_meterings_tmp.remove("index");
                uint32_t ts_hour_last = tsm_day.value("1.0.0").toUInt();
                uint32_t t_period = 60*60*24;
                while (ts - ts_hour_last > t_period && meterings.size() < 5000) {
                    ts_hour_last /= t_period;
                    ts_hour_last ++;
                    ts_hour_last *= t_period;
                    ts_meterings_tmp.insert("1.0.0", ts_hour_last);
                    meterings.prepend(ts_meterings_tmp);
                    ts_meterings_tmp.insert("1.6.0", 0);
                    ts_meterings.insert("1.6.0", 0);
                }
            }
        }

        tsm_last = ts_meterings;
        switch (type_rec) {
        case DLMS_ARCH_profile_hour: tsm_hour = tsm_last; break;
        case DLMS_ARCH_profile_day:  tsm_day = tsm_last; break;
        default: tsm_other = tsm_last;
        }

        meterings.prepend(ts_meterings);
    }
    QVariantList meterings_tmp = meterings;
 //   meterings.clear();
//    foreach (QVariant var, meterings_tmp) {
//        uint32_t ts = var.toMap().value("1.0.0", 0xFFFFFFFF).toUInt();
  //      if (ts < qitems.value("timefrom", 0).toUInt()) continue;
  //      if (ts > qitems.value("timeto", QDateTime::currentDateTime().toTime_t() + 60*60*24).toUInt()) continue;
//        meterings.append(var);
//    }
 //   log_1 << "abc1" << qPrintable(QJsonDocument::fromVariant(meterings).toJson(QJsonDocument::Indented));
    qSort(meterings.begin(), meterings.end(), ts_meterings_LessThan);
  //  log_1 << "abc2" << qPrintable(QJsonDocument::fromVariant(meterings).toJson(QJsonDocument::Indented));
    if (fl_hour){
        QVariantMap temp;
        for (int i = 0; i < meterings.size(); i++)
        {
            temp = meterings.at(i).toMap();
            if ( temp.contains("type") ) {
                if ( temp.value( "type", QVariantMap() ).toInt() == 14){
                    meterings.removeAt(i);
                    i--;
                }
            }
        }
    }
    QVariantMap vout_data;
    vout_data.insert("meterings", meterings);

 //   log_1 << "abc" << qPrintable(QJsonDocument::fromVariant(meterings).toJson(QJsonDocument::Indented));
    return vout_data;
}

bool ts_meterings_LessThan(const QVariant &s1, const QVariant &s2)
{
    uint32_t s1val = s1.toMap().value("1.0.0").toUInt();
    uint32_t s2val = s2.toMap().value("1.0.0").toUInt();
    if (s1val != s2val) {
        return s1val > s2val;
    }
    QString s1pr = s1.toMap().value("profile").toString();
    QString s2pr = s2.toMap().value("profile").toString();
    return s1pr > s2pr;
}
