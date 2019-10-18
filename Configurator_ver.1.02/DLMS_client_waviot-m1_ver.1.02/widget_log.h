#ifndef WIDGET_LOG_H
#define WIDGET_LOG_H

#include <QWidget>
#include <QTableView>
#include <QAbstractTableModel>
#include <QGridLayout>
#include <QComboBox>
#include <QTimer>
#include <QLabel>
#include <QRadioButton>
#include <QDateTimeEdit>
#include "xlsxdocument.h"
#include "xlsxformat.h"
#include <QFileDialog>
#include <qcheckbox.h>

class TModel_log;

namespace Ui {
class widget_log;
}

class widget_log : public QWidget
{
    Q_OBJECT
    QTimer *tmr_t_out;
public:
    explicit widget_log(QWidget *parent = nullptr);
    ~widget_log();
    QVBoxLayout mainLayout;
    QTableView* m_view_log;
    TModel_log* m_model_log;
    QComboBox* combo = new QComboBox();
    QRadioButton* radio1 = new QRadioButton();
    QRadioButton* radio2 = new QRadioButton();
    QLabel* label3 = new QLabel( trUtf8( "от: " ) );
    QLabel* label4 = new QLabel( trUtf8( "до: " ) );
    QDateTimeEdit* dt1 = new QDateTimeEdit(QDateTime::currentDateTime());
    QDateTimeEdit* dt2 = new QDateTimeEdit(QDateTime::currentDateTime());
    QCheckBox *ch_box = new QCheckBox( trUtf8( "оригинальные данные" ) );
    bool transmit = false;
    void parse_arch(QByteArray);
    void parse_data_arch(QByteArray);
    void set_request_data(uint32_t, uint32_t, uint32_t);
    int n_set_data;
    uint32_t n_set_data_max;
    int n_set_buf[10000];
    uint32_t type_;
    int progresbar;
    int intermediate;
    int dec_intermediate;
    bool fl_intermediate;
    QVariantList vl;
    QVariantMap vmap_month;
    QVariantMap vmap_day;
    QVariantMap vmap_hour;
    QVariantMap vmap_day_mod;
    QVariantMap vmap_hour_mod;
    int time_from_form_min();
    int time_from_form_max();
    int count_tout;
    int type_data_hour;
    QVariantMap path_report_history(QVariantMap, bool);
    QVariantMap path_report_history_hour(QVariantMap, QVariantMap);
    QVariantMap orig_data(QVariantMap);
    void read_log_event(QByteArray);
    bool transmitt();
    void data_arch(QVariantList);
  //  OBIS obis(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F);
  //  OBIS obis(uint8_t C, uint8_t D, uint8_t E);
//    bool ts_meterings_LessThan(const QVariant &s1, const QVariant &s2);
private:
    Ui::widget_log *ui;
signals:
    void signal_write_data(QByteArray);
    void signal_bar(int);
    void signal_timeout_start(int);
    void signal_timeout_stop();
    void signal_disable_tab_kn(bool, int);
    void signal_on_pushButton_connect_clicked(bool);
public slots:
    void slot_read_log();
    void slot_log_read(QByteArray);
    void slot_disconnect();
    void slot_stop_read_log();
    void slot_log_event_empty_arr();
    void slot_view_log();
private slots:
    void on_pushButton_clicked();
    void timeout();
    void slotRadioToggled(bool);
    void slot_click_bn();
    void slot_click_bn_xls_mod();
    void slot_click_bn_file();
};

class TModel_log : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_log( QObject* parent = nullptr );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void insert_row(QVariantMap, int, int);
    void insert_row_data(QVariantMap);
    void removeTable();
    void clear_m_data();
    QList< QHash< int, QVariant > >return_m_data();
//    void appendData(int qty_seasons, QString seasons[100][2], int qty_weeks, QString weeks[100][8], int qty_days, QString days[100][100][4] );
//    void appendRow();
//    void removeSelected( int );
//    QList< QHash< int, QVariant > > copydata(QHash<int,int>);
//    QHash< int, QVariant > copyhash_spec(int, QDate date);
//    QHash< int, QVariant > copyhash_spec_withDate(QString, int, QModelIndex);
//    QHash< int, QVariant > copyhash_season(int row);
//    QHash< int, QVariant > data_hash(int);
//    int count_days();
//    bool test_profils_seasons(QHash<int,int>);
//    bool test_profil(int);
//    int index_m_model(int);
signals:
//    void profile_break();
//    void signal_change_profile(QHash< int, QVariant >);
public slots:

 //   void on_tableWidget_itemClicked(QTableViewItem* item);
 //  void slot_click(QModelIndex);

private:
    enum Column {
        c0,
        c1,
        c2,
        c3,
        c4,
        c5,
        c6,
        c7,
        c8,
        c9,
        c10,
        c11,
        c12,
        c13,
        c14,
        c15,
        c16,
        c17,
        c18,
        c19,
        c20,
        c21,
        c22,
        c23,
        c24
    };

    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;

};

#endif // WIDGET_LOG_H
