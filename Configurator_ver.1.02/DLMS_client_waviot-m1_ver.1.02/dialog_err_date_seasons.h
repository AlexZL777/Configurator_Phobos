#ifndef DIALOG_ERR_DATE_SEASONS_H
#define DIALOG_ERR_DATE_SEASONS_H

#include <QDialog>

namespace Ui {
class Dialog_err_date_seasons;
}

class Dialog_err_date_seasons : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_err_date_seasons(QWidget *parent = nullptr);
    ~Dialog_err_date_seasons();

private:
    Ui::Dialog_err_date_seasons *ui;
};

#endif // DIALOG_ERR_DATE_SEASONS_H
