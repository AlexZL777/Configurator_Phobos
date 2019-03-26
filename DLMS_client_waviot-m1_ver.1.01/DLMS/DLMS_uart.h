#ifndef _DLMS_UART_H_
#define _DLMS_UART_H_

#include "DLMS_HDLC.h"

#ifdef __cplusplus
extern "C" {
#endif

void DLMS_uart_init();
void DLMS_uart_deinit();
void DLMS_uart_dispatcher();

void MODEM_DLMS_UART_send(uint8_t data);
void MODEM_DLMS_init();

    
#ifdef __cplusplus
}
#endif

#endif // _DLMS_RADIO_H_
