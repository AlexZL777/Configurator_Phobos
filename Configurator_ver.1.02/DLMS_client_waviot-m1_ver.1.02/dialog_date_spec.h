#ifndef DIALOG_DATE_SPEC_H
#define DIALOG_DATE_SPEC_H

#include <QDialog>

namespace Ui {
class Dialog_date_spec;
}

class Dialog_date_spec : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_date_spec(QWidget *parent = nullptr);
    ~Dialog_date_spec();
    QDate getData();
    int getprofile();
signals:
    void signal_date_season();
    void applied();
private:
    Ui::Dialog_date_spec *ui;
};

#endif // DIALOG_DATE_SPEC_H
