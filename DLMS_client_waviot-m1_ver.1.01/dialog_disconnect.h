#ifndef DIALOG_DISCONNECT_H
#define DIALOG_DISCONNECT_H

#include <QDialog>

namespace Ui {
class Dialog_disconnect;
}

class Dialog_disconnect : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_disconnect(QWidget *parent = nullptr);
    ~Dialog_disconnect();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_disconnect *ui;
};

#endif // DIALOG_DISCONNECT_H
