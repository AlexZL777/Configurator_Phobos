#include "dbsession.h"
#include <QFile>
#include <QDebug>


#pragma pack(push, 1)
typedef struct {
  uint16_t      ver;
  uint16_t      ver_ext;
  uint32_t      start_add;
  uint32_t      end_add;
  uint16_t      crc;
  uint16_t      reserved[2];
  uint16_t      crc_of_this_struct;
} soft_update;
#pragma pack(pop)

uint16_t CRC_calc(uint8_t *start, uint8_t *end)
{
  uint16_t crc = 0x0;

  uint8_t  *data;
  //uint32_t tmp_add;
  //uint32_t i = 0;
  //static uint8_t buf[256];
  //uint32_t delta = ((uint32_t)end) - ((uint32_t)start);
  for (data = start; data < end; data++)
  {
    crc  = (crc >> 8) | (crc << 8);
    crc ^= *data;
    //tmp_add = (uint32_t)data;

    //buf[tmp_add%256] = *data;

    //if((((uint32_t)data)%256) == 0)
    //{
    //   i++;
    //}
    crc ^= (crc & 0xff) >> 4;
    crc ^= crc << 12;
    crc ^= (crc & 0xff) << 5;
  }
  return crc;
}




DBsession::DBsession(const QString& sname)
{
    bool e = QFile::exists(sname);
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(sname);
    if(!_db.open())
    {
        qDebug() << "Database open error!\n";
        return;
    }
    if(!e)
    {
        QSqlQuery conquery(_db);
        _db.transaction();
        if(!conquery.exec("CREATE TABLE packets "
                      "(id INT NOT NULL UNIQUE PRIMARY KEY, "
                      "modem_id INT NOT NULL, "
                      "packet_id INT NOT NULL, "
                      "system INT NOT NULL DEFAULT 0, "
                      "no_ack INT NOT NULL DEFAULT 0, "
                      "payload BLOB NOT NULL, "
                      "exec_key BLOB NOT NULL DEFAULT 0, "
                      "state INT NOT NULL)")) qDebug() << conquery.lastError().text();

        if(!conquery.exec("CREATE INDEX type_idx ON packets "
                      "(modem_id)")) qDebug() << conquery.lastError().text();
        _db.commit();
    }
}

DBsession::~DBsession()
{
    _db.close();
    QSqlDatabase::removeDatabase("QSQLITE");

}

void DBsession::insertPacket(SEND_PACKET_model & pkt)
{
    QSqlQuery query(_db);
    if(pkt.packet_id == -1)
    {
        QString q = "SELECT packet_id FROM packets WHERE modem_id=? ORDER BY id DESC LIMIT 1";
        query.prepare(q);
        query.addBindValue(pkt.modem_id);
        if (!query.exec())
        {
            qDebug() << query.lastError().text();
            return;
        }
        if (query.next())
        {
            pkt.packet_id = query.value(0).toInt() + 1;
        }
        else pkt.packet_id = 0;
    }

    QString q("INSERT OR REPLACE INTO packets (id, modem_id, packet_id, payload, system, no_ack, exec_key, state) VALUES "
         "(?,?,?,?,?,?,?,?) ");
     query.prepare(q);
     query.addBindValue(qint64(pkt.modem_id*4294967296 + pkt.packet_id));
     query.addBindValue(pkt.modem_id);
     query.addBindValue(pkt.packet_id);
     query.addBindValue(pkt.payload);
     query.addBindValue(pkt.system);
     query.addBindValue(pkt.noack);
     query.addBindValue(pkt.exec_key);
     query.addBindValue((quint32)pkt.state);
     if (!query.exec()) qDebug() << query.lastError().text();

}

void DBsession::markAllPackets(PACKET_STATE state, quint32 modem_id, quint32 packet_id_from, quint32 packet_id_to)
{
    QSqlQuery query(_db);

     QString q("UPDATE packets SET state=? WHERE modem_id=? AND packet_id>=? AND packet_id<=?");

     query.prepare(q);
     query.addBindValue((quint32)state);
     query.addBindValue(modem_id);
     query.addBindValue(packet_id_from);
     query.addBindValue(packet_id_to);
     if (!query.exec()) qDebug() << query.lastError().text();
}

QList<quint32> DBsession::getModemsList()
{
    QList<quint32> mlist;
    QSqlQuery query(_db);
    QString q = "SELECT DISTINCT modem_id FROM packets";
    if (!query.exec(q))
    {
        qDebug() << query.lastError().text();
        return mlist;
    }
    while(query.next())
    {
        mlist.append(query.value(0).toInt());
    }
    return mlist;
}

SEND_PACKET_model DBsession::getPacket(quint32 modem_id, qint32 packet_id)
{
    SEND_PACKET_model pkt;

    QSqlQuery query(_db);
    if(pkt.packet_id == -1)
    {
        QString q = "SELECT packet_id, payload, system, no_ack, exec_key, state FROM packets WHERE modem_id=? AND state<3 ORDER BY id  LIMIT 1";
        query.prepare(q);
        query.addBindValue(modem_id);
        if (!query.exec())
        {
            qDebug() << query.lastError().text();
            pkt.result = DB_ERR;
            return pkt;
        }
        if (query.next())
        {
            pkt.modem_id = modem_id;
            pkt.packet_id = query.value(0).toInt();
            pkt.payload = query.value(1).toByteArray();
            pkt.system = query.value(2).toInt();
            pkt.noack = query.value(3).toInt();
            pkt.exec_key = query.value(4).toByteArray();
            pkt.state = (PACKET_STATE)query.value(5).toInt();
            pkt.result = SUCCESS;
        }
        else
        {
            pkt.modem_id = 0;
            pkt.result = NO_ENTRY;
        }
    }
    return pkt;
}

qint32 DBsession::getTotalCount(quint32 modem_id)
{
    QSqlQuery query(_db);
    if(modem_id == 0)
    {
        QString q = "SELECT count(*) FROM packets";
        query.prepare(q);
    }
    else
    {
        QString q = "SELECT count(*) FROM packets WHERE modem_id=?";
        query.prepare(q);
        query.addBindValue(modem_id);
    }
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return -1;
    }
    if(query.next())
    {
        qint32 num = query.value(0).toInt();
        return num;
    }
    return -1;
}



qint32 DBsession::getTotalCountDelivered(quint32 modem_id)
{
    QSqlQuery query(_db);
    if(modem_id == 0)
    {
        QString q = "SELECT count(*) FROM packets WHERE state=3";
        query.prepare(q);
    }
    else
    {
        QString q = "SELECT count(*) FROM packets WHERE modem_id=? AND state=3";
        query.prepare(q);
        query.addBindValue(modem_id);
    }
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return -1;
    }
    if(query.next())
    {
        qint32 num = query.value(0).toInt();
        return num;
    }
    return -1;
}

qint32 DBsession::getSessionDataLength()
{
    quint32 length = 0;
    QSqlQuery query(_db);
    QString q = "SELECT length(payload) FROM packets";
    query.prepare(q);

    if (!query.exec())
    {
        qDebug() << query.lastError().text();
        return -1;
    }

    while(query.next())
    {
        length += query.value(0).toInt();
    }
    return length;
}

void DBsession::transaction()
{
    _db.transaction();
}

void DBsession::commit()
{
    _db.commit();
}

bool DBsession::make_clear_flash_session(const QList<quint32> & modems)
{
    transaction();


    //Reset index
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD5;
        pkt.exec_key[0] = 0xD5;
        pkt.exec_key[1] = 0;
        pkt.packet_id = 0;
        insertPacket(pkt);
    }

    //Full erase
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = 0;
        pkt.payload[2] = 1;
        pkt.payload[3] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = 1;
        insertPacket(pkt);
    }
    commit();
    return true;
}


bool DBsession::make_flash_session(const QString & binary_filename, const QList<quint32> & modems, quint16 ver, quint16 subver, quint32 offset, qint32 check_crc)
{
    QFile inFile(binary_filename);
    if(!inFile.open(QIODevice::ReadOnly)) return -1;
    QByteArray ba = inFile.readAll();
    inFile.close();
    quint16 index = 1;
    transaction();

    //prepare header
    QByteArray arr_header((int)(sizeof(soft_update)), 0);
    soft_update * su = (soft_update *)arr_header.data();
    su->ver = ver;
    su->ver_ext = subver;
    su->start_add = offset;
    su->end_add = su->start_add + ba.size();
    su->crc = CRC_calc((uint8_t *)ba.data(), (uint8_t *)ba.data() + ba.size());
    su->reserved[0] = 0;
    su->reserved[1] = 0;
    su->crc_of_this_struct = CRC_calc((uint8_t *)su, (uint8_t *)(&su->crc_of_this_struct));


    //Reset index
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD5;
        pkt.exec_key[0] = 0xD5;
        pkt.exec_key[1] = 0;
        pkt.packet_id = 0;
        insertPacket(pkt);
    }

    if(check_crc >= 0)
    {
        //check current firmware CRC
        for(const auto modem:modems)
        {
                SEND_PACKET_model pkt;
                pkt.modem_id = modem;
                pkt.payload[0] = 0xD4;
                pkt.payload[1] = (index>>8)&0xff;
                pkt.payload[2] = index&0xff;
                pkt.payload[3] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
                pkt.payload[4] = (su->start_add>>16)&0xff;
                pkt.payload[5] = (su->start_add>>8)&0xff;
                pkt.payload[6] = (su->start_add)&0xff;
                pkt.payload[7] = (su->end_add>>16)&0xff;
                pkt.payload[8] = (su->end_add>>8)&0xff;
                pkt.payload[9] = (su->end_add)&0xff;
                pkt.exec_key[0] = 0xD4;
                pkt.exec_key[1] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
                pkt.exec_key[2] = (((quint32)check_crc)>>8)&0xff;
                pkt.exec_key[3] = (((quint32)check_crc))&0xff;
                pkt.packet_id = index;
                insertPacket(pkt);
        }
        index++;
    }

    //Full erase
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    index++;

    //Write header
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_WRITE_HEADER_CMD;
        pkt.payload.append(arr_header);
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_WRITE_HEADER_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);

    }
    index++;

    quint32 address = 0;

    //Write all lines
    for(uint i = 0; i < ba.size()/LINE_SIZE; i++)
    {
        QByteArray line;
        //address = i*LINE_SIZE;
        line[0] = 0xD4;
        line[1] = (index>>8)&0xff;
        line[2] = index&0xff;
        line[3] = RFL_WRITE_CMD  + ((address>>16)&0x1f);
        line[4] = (address>>8)&0xff;
        line[5] = address&0xff;
        line.append(ba.mid(i*LINE_SIZE, LINE_SIZE));
        for(const auto modem:modems)
        {
            SEND_PACKET_model pkt;
            pkt.modem_id = modem;
            pkt.payload = line;
            insertPacket(pkt);
            pkt.packet_id = index;
        }
        address += LINE_SIZE;
        index++;
    }

    //Write tail
    if(ba.size()%LINE_SIZE)
    {
        QByteArray line;
        line[0] = 0xD4;
        line[1] = (index>>8)&0xff;
        line[2] = index&0xff;
        //address = ba.size()/LINE_SIZE*LINE_SIZE;
        line[3] = RFL_WRITE_CMD  + ((address>>16)&0x0f);
        line[4] = (address>>8)&0xff;
        line[5] = address&0xff;
        line.append(ba.mid(address, ba.size()%LINE_SIZE));
        for(const auto modem:modems)
        {
            SEND_PACKET_model pkt;
            pkt.modem_id = modem;
            pkt.payload = line;
            pkt.packet_id = index;
            insertPacket(pkt);
        }
        index++;
    }

    //Check CRC and reboot
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    commit();
    return true;
}

bool DBsession::make_diff_flash_session(const QString &new_binary_filename, const QString &old_binary_filename, const QList<quint32> &modems, quint16 ver, quint16 subver, quint32 offset)
{
    QFile newFile(new_binary_filename);
    if(!newFile.open(QIODevice::ReadOnly)) return -1;
    QByteArray new_ba = newFile.readAll();
    newFile.close();
    QFile oldFile(old_binary_filename);
    if(!oldFile.open(QIODevice::ReadOnly)) return -1;
    QByteArray old_ba = oldFile.readAll();
    oldFile.close();

    QList<rfl_binary_part> parts;

    quint32 pos = 0;

    while(pos < new_ba.size())
    {
        rfl_binary_part part;
        if(!peek_to_next_diff(new_ba, old_ba, pos)) break;;
        part.address = pos;
        part.data = peek_to_end_of_block(new_ba, old_ba, pos);
        parts.append(part);
    }


    quint16 index = 1;
    transaction();

    //prepare header
    QByteArray arr_header((int)(sizeof(soft_update)), 0);
    soft_update * su = (soft_update *)arr_header.data();
    su->ver = ver;
    su->ver_ext = subver;
    su->start_add = offset;
    su->end_add = su->start_add + new_ba.size();
    su->crc = CRC_calc((uint8_t *)new_ba.data(), (uint8_t *)(&(new_ba.data()[new_ba.size()])));
    su->reserved[0] = 0;
    su->reserved[1] = 0;
    su->crc_of_this_struct = CRC_calc((uint8_t *)su, (uint8_t *)(&su->crc_of_this_struct));



    quint16 old_crc = CRC_calc((uint8_t *)old_ba.data(), (uint8_t *)(&(old_ba.data()[old_ba.size()])));

    //Reset index
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD5;
        pkt.exec_key[0] = 0xD5;
        pkt.exec_key[1] = 0;
        pkt.packet_id = 0;
        insertPacket(pkt);
    }

    //check current firmware CRC
    for(const auto modem:modems)
    {

        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
        pkt.payload[4] = (su->start_add>>16)&0xff;
        pkt.payload[5] = (su->start_add>>8)&0xff;
        pkt.payload[6] = (su->start_add)&0xff;
        pkt.payload[7] = (su->end_add>>16)&0xff;
        pkt.payload[8] = (su->end_add>>8)&0xff;
        pkt.payload[9] = (su->end_add)&0xff;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_READ_CURRENT_FIRMWARE_CRC_CMD;
        pkt.exec_key[2] = (((quint32)old_crc)>>8)&0xff;
        pkt.exec_key[3] = (((quint32)old_crc))&0xff;
        pkt.packet_id = index;
        insertPacket(pkt);


    }
    index++;

    //Full erase
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_FULL_ERASE_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    index++;

    //Write header
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_WRITE_HEADER_CMD;
        pkt.payload.append(arr_header);
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_WRITE_HEADER_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);

    }
    index++;

    for(const auto & part:parts)
    {
        quint32 address = part.address;
        //Write all lines
        for(uint i = 0; i < part.data.size()/LINE_SIZE; i++)
        {
            QByteArray line;
            //address = i*LINE_SIZE;
            line[0] = 0xD4;
            line[1] = (index>>8)&0xff;
            line[2] = index&0xff;
            line[3] = RFL_WRITE_CMD  + ((address>>16)&0x1f);
            line[4] = (address>>8)&0xff;
            line[5] = address&0xff;
            line.append(part.data.mid(i*LINE_SIZE, LINE_SIZE));
            for(const auto modem:modems)
            {
                SEND_PACKET_model pkt;
                pkt.modem_id = modem;
                pkt.payload = line;
                insertPacket(pkt);
                pkt.packet_id = index;
            }
            address += LINE_SIZE;
            index++;
        }

        //Write tail
        if(part.data.size()%LINE_SIZE)
        {
            QByteArray line;
            line[0] = 0xD4;
            line[1] = (index>>8)&0xff;
            line[2] = index&0xff;
            //address = part.data.size()/LINE_SIZE*LINE_SIZE;
            line[3] = RFL_WRITE_CMD  + ((address>>16)&0x0f);
            line[4] = (address>>8)&0xff;
            line[5] = address&0xff;
            line.append(part.data.mid(address - part.address, part.data.size()%LINE_SIZE));
            for(const auto modem:modems)
            {
                SEND_PACKET_model pkt;
                pkt.modem_id = modem;
                pkt.payload = line;
                pkt.packet_id = index;
                insertPacket(pkt);
            }
            index++;
        }
    }

    //Write last one byte
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        quint32 address = new_ba.size() - 1;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_WRITE_CMD  + ((address>>16)&0x0f);
        pkt.payload[4] = (address>>8)&0xff;
        pkt.payload[5] = address&0xff;
        pkt.payload[6] = 0xff;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
     index++;

    //Check CRC and reboot
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = (index>>8)&0xff;
        pkt.payload[2] = index&0xff;
        pkt.payload[3] = RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_CHECK_IF_CRC_OK_AND_REBOOT_CMD;
        pkt.exec_key[2] = 0;
        pkt.packet_id = index;
        insertPacket(pkt);
    }
    commit();
    return true;
}

bool DBsession::make_check_flash_session(const QString &binary_filename, const QList<quint32> & modems, quint32 start, quint32 end)
{


    QFile inFile(binary_filename);
    if(!inFile.open(QIODevice::ReadOnly)) return -1;
    QByteArray ba = inFile.readAll();
    inFile.close();
    transaction();

    //Reset index
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD5;
        pkt.exec_key[0] = 0xD5;
        pkt.exec_key[1] = 0;
        pkt.packet_id = 0;
        insertPacket(pkt);
    }

    uint16_t crc  = CRC_calc((uint8_t *)(&(ba.data()[start])), (uint8_t *)(&(ba.data()[end])));
    qDebug() << QString("CRC is %1").arg(crc, 0, 16);
    //Read CRC
    //Check CRC
    for(const auto modem:modems)
    {
        SEND_PACKET_model pkt;
        pkt.modem_id = modem;
        pkt.payload[0] = 0xD4;
        pkt.payload[1] = 0;
        pkt.payload[2] = 1;
        pkt.payload[3] = RFL_READ_EXT_FLASH_CRC;
        pkt.payload[4] = (end>>16)&0xff;
        pkt.payload[5] = (end>>8)&0xff;
        pkt.payload[6] = (end>>0)&0xff;
        pkt.exec_key[0] = 0xD4;
        pkt.exec_key[1] = RFL_READ_EXT_FLASH_CRC;
        pkt.exec_key[2] = (crc>>8)&0xff;
        pkt.exec_key[3] = (crc)&0xff;
        pkt.packet_id = 1;
        insertPacket(pkt);
    }
    commit();
    return true;
}

bool DBsession::peek_to_next_diff(const QByteArray &new_ba, const QByteArray &old_ba, quint32 &pos)
{
    while((pos < new_ba.size()) && (pos < old_ba.size()))
    {
        if(new_ba[pos] != old_ba[pos]) break;
        pos++;
    }
    if((pos >= new_ba.size()) || (pos >= old_ba.size())) return false;

    return true;
}

#define RFL_MIN_HOLE_LEN 32
QByteArray DBsession::peek_to_end_of_block(const QByteArray &new_ba, const QByteArray &old_ba, quint32 &pos)
{
    quint32 hole = 0;
    quint32 start_pos = pos;
    while(pos < new_ba.size())
    {
        if((old_ba.size() >= pos) && (new_ba[pos] == old_ba[pos]))
        {
            if(++hole >= RFL_MIN_HOLE_LEN)
            {
                pos -= RFL_MIN_HOLE_LEN;
                pos++;
                return new_ba.mid(start_pos, pos - start_pos);
            }
        }
        else
        {
            hole = 0;
        }
        pos++;
    }

    return new_ba.right(pos - start_pos);
}

