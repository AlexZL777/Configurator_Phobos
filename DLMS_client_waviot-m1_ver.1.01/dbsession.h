#ifndef DBSESSION_H
#define DBSESSION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlResult>
#include <QtSql/QSqlError>

#include "send_packet_model.h"

#define LINE_SIZE   128


#define RFL_FULL_ERASE_CMD                      (1<<5)
#define RFL_WRITE_HEADER_CMD                    (2<<5)
#define RFL_WRITE_CMD                           (3<<5)
#define RFL_READ_CURRENT_FIRMWARE_CRC_CMD       (4<<5)
#define RFL_CHECK_IF_CRC_OK_CMD                 (5<<5)
#define RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD      (6<<5)
#define RFL_READ_EXT_FLASH_CRC                  (7<<5)

#define RFL_ERR_NO_ERR  0
#define RFL_ERR_INDEX_MISSED  0x80

class DBsession
{
public:

    struct rfl_binary_part
    {
        quint32 address;
        QByteArray data;
    };

    DBsession(const QString& sname = "session.db3");
    ~DBsession();
    void transaction();
    void commit();
    void insertPacket(SEND_PACKET_model & pkt);
    void markAllPackets(PACKET_STATE state, quint32 modem_id, quint32 packet_id_from, quint32 packet_id_to);
    QList<quint32> getModemsList();
    SEND_PACKET_model getPacket(quint32 modem_id, qint32 packet_id = -1);
    qint32 getTotalCount(quint32 modem_id = 0);
    qint32 getTotalCountDelivered(quint32 modem_id = 0);
    qint32 getSessionDataLength();
    bool make_dl_send_session(const QList<quint32> & modems, const QList<QByteArray> & payloads);
    bool make_clear_flash_session(const QList<quint32> & modems);
    bool make_flash_session(const QString & binary_filename, const QList<quint32> & modems, quint16 ver = 1, quint16 subver = 0, quint32 offset = 0, qint32 check_crc = -1);
    bool make_diff_flash_session(const QString & new_binary_filename, const QString & old_binary_filename, const QList<quint32> & modems, quint16 ver = 1, quint16 subver = 0, quint32 offset = 0);
    bool make_check_flash_session(const QString &new_binary_filename, const QList<quint32> & modems, quint32 start, quint32 end);
private:

    bool peek_to_next_diff(const QByteArray &new_ba, const QByteArray &old_ba, quint32 &pos);
    QByteArray peek_to_end_of_block(const QByteArray &new_ba, const QByteArray &old_ba, quint32 &pos);


    QSqlDatabase _db;
};

#endif // DBSESSION_H
