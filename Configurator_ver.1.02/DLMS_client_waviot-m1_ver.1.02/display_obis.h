#ifndef DISPLAY_OBIS_H
#define DISPLAY_OBIS_H

#include <QObject>

class display_obis : public QObject
{
    Q_OBJECT
public:
    explicit display_obis(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DISPLAY_OBIS_H