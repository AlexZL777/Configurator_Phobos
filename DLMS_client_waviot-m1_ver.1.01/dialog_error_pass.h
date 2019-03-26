#ifndef DIALOG_ERROR_PASS_H
#define DIALOG_ERROR_PASS_H

#include <QDialog>

namespace Ui {
class Dialog_error_pass;
}

class Dialog_error_pass : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_error_pass(QWidget *parent = nullptr);
    ~Dialog_error_pass();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_error_pass *ui;
};

#endif // DIALOG_ERROR_PASS_H
