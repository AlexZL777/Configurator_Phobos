#ifndef FORM_LOG_H
#define FORM_LOG_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class Form_log;
}

class Form_log : public QWidget
{
    Q_OBJECT

public:
    explicit Form_log(QWidget *parent = nullptr);
    ~Form_log();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form_log *ui;

public slots:
    void slot_log(QString);
};

#endif // FORM_LOG_H
