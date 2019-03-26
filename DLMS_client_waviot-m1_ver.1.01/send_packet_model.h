#ifndef SEND_PACKET_MODEL
#define SEND_PACKET_MODEL
#include <QByteArray>

enum PACKET_STATE
{
    CREATED = 0,
    QUEUED  = 1,
    INPROCESS = 2,
    DELIVERED = 3,
    LOST = 4,
    WAITFOREXEC = 5
};

enum DB_RESULT
{
    SUCCESS,
    DB_ERR,
    NO_ENTRY
};


struct SEND_PACKET_model
{
    quint32 modem_id;
    qint32 packet_id = -1;
    QByteArray payload;
    bool system = false;
    bool noack = false;
    QByteArray exec_key = QByteArray("0");
    PACKET_STATE state = CREATED;
    DB_RESULT result;
};

#endif // SEND_PACKET_MODEL

