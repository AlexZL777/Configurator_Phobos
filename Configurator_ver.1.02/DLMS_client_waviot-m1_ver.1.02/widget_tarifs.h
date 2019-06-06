#ifndef WIDGET_TARIFS_H
#define WIDGET_TARIFS_H

#include <QWidget>
#include <QAbstractTableModel>
#include <QVariant>
#include <QTabWidget>
#include <QGridLayout>
#include <QTableView>
#include <QDate>
#include <QTimer>
#include <QPushButton>

class QTableView;
class QLineEdit;

class TModel;
class TModel_s;
class TModel_special;

namespace Ui {
class widget_tarifs;
}

class widget_tarifs : public QWidget
{
    Q_OBJECT
    QTimer *tmr_tout;
public:
    explicit widget_tarifs(QWidget *parent = nullptr);
    ~widget_tarifs();
    bool transmit = false;
    QByteArray tariff_json_pack(QVariantMap);
    QPushButton* bn_write_counter = new QPushButton( trUtf8( "Записать тарифное расписание в счётчик" ) );
    void TARIFF_block_to_u8(void *b, uint8_t *first, uint8_t *second);
    void TARIFF_block_from_u8(void *b, uint8_t first, uint8_t second);
    uint8_t DLMS_tariff_test_buf(uint8_t* buff, uint16_t buff_len);
    QVariantMap tariff_json_unpack(QByteArray);
    int qty_seasons = 0;
    QString seasons[100][2];
    int qty_weeks = 0;
    QString weeks[100][8];
    int qty_days = 0;
    QString days[100][100][4];
    int qty_special_days = 0;
    QString special_days[100][2];
  //  QHash<int,QVariant> m_seasons;
    bool del = false;
    QVBoxLayout mainLayout;
    QTabWidget tab_w;
    QWidget w[64];
    QGridLayout seasonLayouts[64];
    void seasons_view(int qty_seasons);
    QTableView* m_view;
    QTableView* m_view_seasons[64];
    QTableView* m_view_special;
    TModel* m_model;
    TModel_s* m_model_seasons[64];
    TModel_special* m_model_special;
    QHash <int, QWidget*> widg;
    void test_day_del(QString g);
    int count_tout;
    bool transmitt();
signals:
    void signal_write_data(QByteArray data);
    void signal_dial_date_season();
    void signal_date_spec();
    void signal_bar(int data);
    void signal_write_data_PDU(QByteArray);
    void signal_profile_break();
    void signal_error_profils_seasons();
    void signal_err_profil_spec();
    void signal_error_data_spec();
    void signal_error_data_seasons();
    void signal_err_del_profil();
    void signal_timeout_start(int);
    void signal_disable_tab_kn(bool, int);
    void signal_on_pushButton_connect_clicked(bool);
public slots:
    void slot_disconnect();
    void onAppend_syt();
    void onAppend_week();
    void onAppend_spec();
    QVariant write_to_counter();
    void slot_click_Remove_syt();
    void slot_click_Remove_season();
    void slot_click_Remove_spec();
    void slot_read_tarifs();
    void slot_tariff_json_unpack(QByteArray);
    void slot_date_season(QDate, QHash<int,int>);
    void slot_date_spec(int, QDate);
    void slot_change_data(QModelIndex, int);
    void slot_change_data_spec(QModelIndex, int);
    void slot_profile_break();
    void slot_change_profile(QHash< int, QVariant >);
    void slot_test_profils_seasons(QHash<int,int>, QDate);
    void timeout();
private:
    Ui::widget_tarifs *ui;
};

class TModel : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel( QObject* parent = nullptr );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void appendData(int qty_seasons, QString seasons[100][2], int qty_weeks, QString weeks[100][8], int qty_days, QString days[100][100][4] );
    void appendRow();
    void removeSelected( int );
    QList< QHash< int, QVariant > > copydata(QHash<int,int>);
    QHash< int, QVariant > copyhash_spec(int, QDate date);
    QHash< int, QVariant > copyhash_spec_withDate(QString, int, QModelIndex);
    QHash< int, QVariant > copyhash_season(int row);
    QHash< int, QVariant > data_hash(int);
    int count_days();
    bool test_profils_seasons(QHash<int,int>);
    bool test_profil(int);
    int index_m_model(int);
    void removeData();
signals:
    void profile_break();
    void signal_change_profile(QHash< int, QVariant >);
public slots:

 //   void on_tableWidget_itemClicked(QTableViewItem* item);
    void slot_click(QModelIndex);

private:
    enum Column {
        c = 0,
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
        c23
    };

    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;

};

class TModel_s : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_s( QObject* parent = nullptr );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void appendData(int n_tab, int qty_seasons, QString seasons[100][2], int qty_weeks, QString weeks[100][8], int qty_days, QString days[100][100][4] );
    void appendweek(QList< QHash< int, QVariant > >);
    //   void removeSelected(int);
    void changeRow(QModelIndex, QHash< int, QVariant >);
    QList< QHash< int, QVariant > > data_list();
    QList< QHash< int, QVariant > > copyfrom();
    void copyto(QList< QHash< int, QVariant > >);
    void change_profile(QHash< int, QVariant >);
    bool test_profil_seasons(int);
    void removeData();
    void emit_change(QModelIndex , int);
 //   void copy(QStandardItemModel* from, QStandardItemModel* to);
signals:
    void change_data(QModelIndex, int);
public slots:

 //   void on_tableWidget_itemClicked(QTableViewItem* item);
  //  void slot_click(QModelIndex);

private:
    enum Column {
        c,
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
        c23
    };

    enum Row {
        pn,
        vt,
        sr,
        ch,
        pt,
        sb,
        vs
    };

    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;

};

class TModel_special : public QAbstractTableModel {
    Q_OBJECT
public:
    TModel_special( QObject* parent = nullptr );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    bool setData( const QModelIndex& index, const QVariant& value, int role );
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    Qt::ItemFlags flags( const QModelIndex& index ) const;

    void appendRow(QHash< int, QVariant >);
    void appendData( int qty_special_days, QString special_days[100][2], int qty_days, QString days[100][100][4] );
    QHash< int, QVariant > data_hash(int);
    int count_days();
    QString get_date(int);
    void changeRow(QModelIndex, QHash< int, QVariant >);
    void change_profile(QHash< int, QVariant >);
    bool test_data_spec(QString);
    bool test_profil_spec(int);
    void removeSelected(int);
    void removeData();
signals:
    void change_data(QModelIndex, int);
public slots:

 //   void on_tableWidget_itemClicked(QTableViewItem* item);
  //  void slot_click(QModelIndex);

private:
    enum Column {
        d,
        c,
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
        c23
    };

    typedef QHash< int, QVariant > DData;
    typedef QList<DData > Data;
    Data m_data;

};

#endif // WIDGET_TARIFS_H
