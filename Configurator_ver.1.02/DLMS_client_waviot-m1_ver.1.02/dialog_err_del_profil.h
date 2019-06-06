#ifndef DIALOG_ERR_DEL_PROFIL_H
#define DIALOG_ERR_DEL_PROFIL_H

#include <QDialog>

namespace Ui {
class Dialog_err_del_profil;
}

class Dialog_err_del_profil : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_err_del_profil(QWidget *parent = nullptr);
    ~Dialog_err_del_profil();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_err_del_profil *ui;
};

#endif // DIALOG_ERR_DEL_PROFIL_H
