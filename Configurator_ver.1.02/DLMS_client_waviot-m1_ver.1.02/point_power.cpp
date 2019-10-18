#include "point_power.h"
#include "ui_point_power.h"

#include <Logger/Logger.h>

#include <QtMath>
#include <QPalette>

extern float powCoefA;
extern float powCoefB;
extern float powCoefC;
extern float angl_AC;
extern float angl_AB;
extern float angl_BC;

int w, h, wmid, hmid, r, context, ri, ctx, angl;
float angleValue, angleLabel, x, y;

point_power::point_power(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::point_power)
{
    ui->setupUi(this);
}

point_power::~point_power()
{
    delete ui;
}

void point_power::slot_hide_point_power(){
    hide();
}

void point_power::slot_show_point_power(){
    show();
}

void point_power::slot_repaint(){
    repaint();
}

void point_power::paintEvent(QPaintEvent *event)
{
    float angleValue, angleLabel, x, y, w, h, wmid, hmid, r, context, ri, ctx, angl;
    Q_UNUSED(event);
    QPainter painter(this); // Создаём объект отрисовщика

    w = this->width();
    h = this->height();
    wmid = w / 2;
    hmid = h / 2;
    r = wmid;
    if (hmid < wmid) {
        r = hmid;
    }
    r *= 0.8;
    ri = r * 0.7;

    painter.setFont(QFont("Arial", 8, QFont::Bold));//  ctx.font = "15px Arial";

    //Окружность
    painter.drawEllipse(wmid-r, hmid-r, r*2, r*2);

    //горизонтальная линия
    painter.drawLine(wmid - r, hmid, wmid + r, hmid);

    //вертикальная линия
    painter.drawLine(wmid, hmid - r, wmid, hmid + r);

    //риски и надписи по кругу
    for (angleValue = 0; angleValue < 360; angleValue += 30) {
        x = qCos(angleValue / 180 * M_PI);
        y = -qSin(angleValue / 180 * M_PI);

        painter.drawLine(wmid + x * r * 1.05, hmid + y * r * 1.05, wmid + x * r * 0.95, hmid + y * r * 0.95);

        if (angleValue >= 90) {
            angleLabel = angleValue - 90;
        } else {
            angleLabel = angleValue + 270;
        }

        if (angleLabel) {
            angleLabel = 360 - angleLabel;
        }
        QString s;
        if (angleLabel == 0){
            painter.drawText(wmid + x * (r * 1.12) - 2, hmid + y * (r * 1.12) + (10 / 2), s.setNum(angleLabel));
        }
        else {
            painter.drawText(wmid + x * (r * 1.12) - 10, hmid + y * (r * 1.12) + (10 / 2), s.setNum(angleLabel));
        }
    }

    // A
    angl = 0;
    draw_arrow(painter, "Va", QColor ("#BFBF00"), r, angl, wmid, hmid);
    draw_arrow(painter, "Ia", QColor ("#BFBF00"), ri, angl + powCoefA, wmid, hmid);
    // B
    angl = angl_AB;
    draw_arrow(painter, "Vb", QColor ("#00BF00"), r, angl, wmid, hmid);
    draw_arrow(painter, "Ib", QColor ("#00BF00"), ri, angl + powCoefB, wmid, hmid);
    // C
    angl = angl_AB + angl_BC;
    draw_arrow(painter, "Vc", QColor ("#FF0000"), r, angl, wmid, hmid);
    draw_arrow(painter, "Ic", QColor ("#FF0000"), ri, angl + powCoefC, wmid, hmid);
}

void point_power::draw_arrow(QPainter &painter, QString txt, QColor style, float r, float angl, float wmid, float hmid) {
    float x, y;
    angl = 90 - angl;

    x = qCos(angl / 180 * M_PI);
    y = -qSin(angl / 180 * M_PI);

    painter.setPen(QPen(style, 0.5, Qt::SolidLine, Qt::RoundCap));

    painter.drawLine(wmid, hmid, wmid + x * r, hmid + y * r);
    float x1 = x;
    float y1 = y;
    x = qCos((angl - 1.5) / 180 * M_PI);
    y = -qSin((angl - 1.5) / 180 * M_PI);
    painter.drawLine(wmid + x1 * r, hmid + y1 * r, wmid + x * r * 0.95, hmid + y * r * 0.95);
    x1 = x;
    y1 = y;
    x = qCos((angl + 1.5) / 180 * M_PI);
    y = -qSin((angl + 1.5) / 180 * M_PI);
    painter.drawLine(wmid + x1 * r * 0.95, hmid + y1 * r * 0.95, wmid + x * r * 0.95, hmid + y * r * 0.95);
    x1 = x;
    y1 = y;
    x = qCos(angl / 180 * M_PI);
    y = -qSin(angl / 180 * M_PI);
    painter.drawLine(wmid + x1 * r * 0.95, hmid + y1 * r * 0.95, wmid + x * r, hmid + y * r);

    painter.setPen(QPen(Qt::NoPen));
    painter.drawRect(wmid + x * (r * 0.5) -10, hmid + y * (r * 0.5) - (12 / 2), 10, 12);

    painter.setPen(QPen(Qt::black, 0.2, Qt::SolidLine, Qt::RoundCap));
    painter.drawText(wmid + x * (r * 0.5) - 10, hmid + y * (r * 0.5) + (10 / 2), txt);
}
