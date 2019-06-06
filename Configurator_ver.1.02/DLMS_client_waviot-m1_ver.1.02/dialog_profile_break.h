#ifndef DIALOG_PROFILE_BREAK_H
#define DIALOG_PROFILE_BREAK_H

#include <QDialog>

namespace Ui {
class Dialog_profile_break;
}

class Dialog_profile_break : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_profile_break(QWidget *parent = nullptr);
    ~Dialog_profile_break();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_profile_break *ui;
};

#endif // DIALOG_PROFILE_BREAK_H
