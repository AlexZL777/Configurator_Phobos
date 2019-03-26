#ifndef _DLMS_CRC_H_
#define _DLMS_CRC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t DLMS_crc_byte(uint16_t crc, uint8_t c);
uint16_t DLMS_crc_buff(uint8_t *data, uint32_t data_len);

#ifdef __cplusplus
}
#endif

#endif // _DLMS_HDLC_H_
