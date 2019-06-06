#ifndef DIALOG_ERROR_PROFILS_SEASONS_H
#define DIALOG_ERROR_PROFILS_SEASONS_H

#include <QDialog>

namespace Ui {
class Dialog_error_profils_seasons;
}

class Dialog_error_profils_seasons : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_error_profils_seasons(QWidget *parent = nullptr);
    ~Dialog_error_profils_seasons();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_error_profils_seasons *ui;
};

#endif // DIALOG_ERROR_PROFILS_SEASONS_H
