#ifndef DIALOG_INSERT_DATA_SEASON_H
#define DIALOG_INSERT_DATA_SEASON_H

#include <QWidget>

namespace Ui {
class dialog_insert_data_season;
}

class dialog_insert_data_season : public QWidget
{
    Q_OBJECT

public:
    explicit dialog_insert_data_season(QWidget *parent = nullptr);
    ~dialog_insert_data_season();

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialog_insert_data_season *ui;
};

#endif // DIALOG_INSERT_DATA_SEASON_H
