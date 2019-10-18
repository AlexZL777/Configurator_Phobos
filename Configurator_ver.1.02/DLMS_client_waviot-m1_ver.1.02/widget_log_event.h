#ifndef WIDGET_LOG_EVENT_H
#define WIDGET_LOG_EVENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTimer>
//#include <interface.h>
//#include <widget_log.h>
//#include "DLMS_obis_pack.h"
#include <QTableView>
#include <QAbstractTableModel>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxworksheet.h"

class TModel_U;
class TModel_I;
class TModel_rele;
class TModel_prog;
class TModel_ext;
class TModel_com;
class TModel_access;
class TModel_diagnos;
class TModel_tg_pow;


namespace Ui {
class widget_log_event;
}

class widget_log_event : public QWidget
{
    Q_OBJECT
    QTimer *tmr_t_out;

public:
    explicit widget_log_event(QWidget *parent = nullptr);
    ~widget_log_event();

    QTableView* m_view_U;
    TModel_U* m_model_U;
    QTableView* m_view_I;
    TModel_I* m_model_I;
    QTableView* m_view_rele;
    TModel_rele* m_model_rele;
    QTableView* m_view_prog;
    TModel_prog* m_model_prog;
    QTableView* m_view_ext;
    TModel_ext* m_model_ext;
    QTableView* m_view_com;
    TModel_com* m_model_com;
    QTableView* m_view_access;
    TModel_access* m_model_access;
    QTableView* m_view_diagnos;
    TModel_diagnos* m_model_diagnos;
    QTableView* m_view_tg_pow;
    TModel_tg_pow* m_model_tg_pow;
    QVBoxLayout mainLayout;

    QComboBox* combo = new QComboBox();
    QRadioButton* radio1 = new QRadioButton();
    QRadioButton* radio2 = new QRadioButton();
    QLabel* label = new QLabel( trUtf8( "События, связанные с напряжением:" ) );
    QLabel* label2 = new QLabel( trUtf8( "События, связанные с током:" ) );
    QLabel* label3 = new QLabel( trUtf8( "События, связанные с вкл./выкл. счётчика, коммутации реле нагрузки:" ) );
    QLabel* label4 = new QLabel( trUtf8( "События программирования параметров счётчика:" ) );
    QLabel* label5 = new QLabel( trUtf8( "События внешних воздействий:" ) );
    QLabel* label6 = new QLabel( trUtf8( "Коммуникационные события:" ) );
    QLabel* label7 = new QLabel( trUtf8( "События контроля доступа:" ) );
    QLabel* label8 = new QLabel( trUtf8( "Журнал самодиагностики:" ) );
    QLabel* label9 = new QLabel( trUtf8( "Превышение реактивной мощности (тангенса сети):" ) );
    bool radio;
    bool transmit = false;
    uint32_t type;
    int n_set_data;
    uint32_t n_set_data_max;
    int n_set_buf[10000];
    int progresbar;
    int intermediate;
    int dec_intermediate;
    bool fl_intermediate;
    QVariantList vl;
    QVariantMap vmap_U, vmap_I, vmap_rele, vmap_prog, vmap_ext, vmap_com, vmap_access, vmap_diagnos, vmap_tg_pow;
    void parse_arch(QByteArray);
    void parse_data_arch(QByteArray);
    void set_request_data(uint32_t, uint32_t, uint32_t);
    void data_arch(uint32_t, uint32_t, uint16_t, uint8_t, bool);
    uint type_data;
    bool all_data;
    int count_view;
    bool transmitt();
    int count_tout;
   // void title(QXlsx::Document);
    //QXlsx::Document xlsx;
 //   OBIS obis(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F);
 //   OBIS obis(uint8_t C, uint8_t D, uint8_t E);

private:
    Ui::widget_log_event *ui;
signals:
    void signal_write_data(QByteArray);
    void signal_bar(int);
    void signal_timeout_start(int);
    void signal_timeout_stop();
    void signal_disable_tab_kn(bool, int);
    void signal_on_pushButton_connect_clicked(bool);
private slots:
    void timeout();
    void slotRadioToggled(bool);
    void slotCombo(int);
    void slot_click_bn();
public slots:
    void slot_log_event_read(QByteArray);
    void slot_log_event_empty_arr();
    void slot_stop_read_log_event();
    void slot_disconnect();
    void slot_read_log_event();
    void slot_view_log_event();
};

class TModel_U : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_U( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_I : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_I( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_rele : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_rele( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_prog : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_prog( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    uint time_start;
    uint time_end;
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
    Data m_data_prev;
};

class TModel_ext : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_ext( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_com : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_com( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_access : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_access( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_diagnos : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_diagnos( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

class TModel_tg_pow : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_tg_pow( QObject* parent = nullptr );
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;
    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap, int);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
private:
    enum Column {
        c0,
        c1,
        c2
    };
    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;
};

#endif // WIDGET_LOG_EVENT_H
