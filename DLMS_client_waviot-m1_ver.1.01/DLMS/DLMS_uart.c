#include "DLMS_uart.h"

#include "xbuf.h"
#include "DLMS_HDLC.h"
#include "DLMS_PDU.h"
#include "opto_uart.h"
#include "rs485_uart.h"
#include "main.h"

#define DIRECT_OPTO

uint8_t rx_buf[160];
uint8_t tx_buf[160];

UART_X_BUF joint_UART_rx;
UART_X_BUF joint_UART_tx;

HDLC_BUF joint_hdlc_buf;

extern void NOP_Delay_ms(uint32_t val);

uint8_t joint_UART_is_empty(void){
	return xbuf_is_empty(&joint_UART_rx);
}

uint8_t joint_UART_get(void){
	return xbuf_get(&joint_UART_rx);
}

void set_baud_opto_uart(uint8_t speed_byte)
{
    if (speed_byte == 0) {
        OPTO_UART_set_baud_parity(300);
    } else
    if (speed_byte == 5) {
        OPTO_UART_set_baud_no_parity(9600);
    }
}

void wait_opto_10mc(uint8_t delay)
{
    NOP_Delay_ms(delay * 10);
}

void DLMS_uart_init()
{
    xbuf_init(&joint_UART_rx, rx_buf, sizeof(rx_buf));
    xbuf_init(&joint_UART_tx, tx_buf, sizeof(tx_buf));
    
    RS485_UART_init();
    OPTO_UART_init();
#ifdef DIRECT_OPTO
    set_baud_opto_uart(5);
	DLMS_HDLC_Init(&joint_hdlc_buf);
#else
    set_baud_opto_uart(0);
    DLMS_IEC61107_Init(&joint_hdlc_buf);
#endif
    joint_hdlc_buf.tx = RS485_UART_send;
}

void DLMS_uart_deinit()
{
    OPTO_UART_deinit();
    RS485_UART_deinit();
}

void DLMS_uart_dispatcher()
{
    while (!joint_UART_is_empty()) {
        uint8_t c = joint_UART_get();
        switch (joint_UART_tx.hw_id) {
        case 1: {
            joint_hdlc_buf.tx = OPTO_UART_send;
            joint_hdlc_buf.waiting_10mc = wait_opto_10mc;
            joint_hdlc_buf.set_baud = set_baud_opto_uart;
            break;
        }
        case 2: {
            joint_hdlc_buf.tx = RS485_UART_send;
            joint_hdlc_buf.waiting_10mc = 0;
            joint_hdlc_buf.set_baud  = 0;
            break;
        }
        default: break;
        }
        if (!joint_hdlc_buf.IEC61107_is_use) {
            DLMS_HDLC_MAC_LLC_parser(&joint_hdlc_buf, c, UART_HDLC_MAC_controller, DLMS_PDU_controller, ELECTRO5_HDLC_PDU_controller);
        } else {
            if (joint_hdlc_buf.IEC61107_now) {
                c &= 0x7F;
            }
            DLMS_IEC61107_parser(&joint_hdlc_buf, c, UART_HDLC_MAC_controller, DLMS_PDU_controller, ELECTRO5_HDLC_PDU_controller);
        }
    }
    DLMS_HDLC_Dispatcher(&joint_hdlc_buf, HAL_GetTick());
}

void MODEM_DLMS_UART_send(uint8_t data)
{
    xbuf_send(&joint_UART_tx, data);
}

void MODEM_DLMS_init()
{
    joint_hdlc_buf.IEC61107_is_use = 0;
    joint_hdlc_buf.tx = MODEM_DLMS_UART_send;
    joint_hdlc_buf.timeout_connect = HDLC_TIMEOUT_CONNECT_RADIO;
    joint_UART_tx.wr = 0;
    joint_UART_tx.rd = 0;
}
