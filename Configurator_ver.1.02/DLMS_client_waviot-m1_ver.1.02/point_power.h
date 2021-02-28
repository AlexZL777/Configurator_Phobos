#ifndef POINT_POWER_H
#define POINT_POWER_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class point_power;
}

class point_power : public QWidget
{
    Q_OBJECT

public:
    explicit point_power(QWidget *parent = nullptr);
    ~point_power();

protected:
    void paintEvent(QPaintEvent *event);
    void draw_arrow(QPainter &painter, QString txt, QColor style, float r, float angl, float wmid, float hmid);

public slots:
    void slot_show_point_power();
    void slot_hide_point_power();
    void slot_repaint();
private:
    Ui::point_power *ui;
};

#endif // POINT_POWER_H
