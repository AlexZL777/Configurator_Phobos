#ifndef _DLMS_AES_H_
#define _DLMS_AES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void DLMS_Aes1Encrypt(const uint8_t *data, const uint8_t *key, uint8_t *data_out);

#ifdef __cplusplus
}
#endif

#endif // _EXCHANGE_UART_H_
