#ifndef DIALOG_INSERT_DATE_SEASON_H
#define DIALOG_INSERT_DATE_SEASON_H

#include <QDialog>

namespace Ui {
class Dialog_insert_date_season;
}

class Dialog_insert_date_season : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_insert_date_season(QWidget *parent = nullptr);
    ~Dialog_insert_date_season();
    QDate getData();
    QHash<int,int> getprofile();
signals:
    void signal_date_season();
    void applied();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Dialog_insert_date_season *ui;

};

#endif // DIALOG_INSERT_DATE_SEASON_H
