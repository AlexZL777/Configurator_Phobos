#ifndef WIDGET_UPDATE_FW_H
#define WIDGET_UPDATE_FW_H

#include <stdint.h>
#include <QWidget>
#include <QTimer>
#include <QMap>

namespace Ui {
class widget_update_fw;
}

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

class widget_update_fw : public QWidget
{
    Q_OBJECT

public:
    explicit widget_update_fw(QWidget *parent = 0);
    ~widget_update_fw();

    QByteArray wbin;
    uint32_t block_index;
    QTimer * timer_fw;

    bool is_connected;

    int use_auto_update;
    QList<SEND_PACKET_model> cur_packets_list;
    int curr_index;
    uint8_t dev_HW_id;
    uint8_t sw;

    QMap<QString, QString> fw_map;
    void add_text_log(QString str_log);
    void search_fw(QString path);
protected:
    bool send_block();
    void file_fw_update_read_data(QByteArray data);
    QList<SEND_PACKET_model> make_diff_flash_session(QByteArray new_ba, QByteArray old_ba, const QList<quint32> &modems = (QList<quint32>() << 1), quint16 ver = 1, quint16 subver = 0, quint32 offset = 0x08000000 + 0x1000);
    QList<SEND_PACKET_model> make_flash_session(QByteArray ba, const QList<quint32> &modems = (QList<quint32>() << 1), quint16 ver = 1, quint16 subver = 0, quint32 offset = 0x08000000 + 0x1000, qint32 check_crc = 0x1FFFFFFF);
private slots:
    void on_pushButton_file_fw_update_clicked();
    void on_pushButton_auto_update_clicked();
private:
    Ui::widget_update_fw *ui;
signals:
    void signal_write_data(QByteArray data);
    void signal_disconnect();
public slots:
    void slot_read_data(QByteArray data);
    void slot_disconnect();
    void slot_start_fw(QString fileName);
protected slots:
    void slot_timer_fw();
};

#endif // WIDGET_UPDATE_FW_H
