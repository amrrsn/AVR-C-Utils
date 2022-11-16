#pragma once

#ifndef PARITY_NONE
#define PARITY_NONE 0x00
#endif

#ifndef PARITY_EVEN
#define PARITY_EVEN 0x02
#endif

#ifndef PARITY_ODD
#define PARITY_ODD 0x03
#endif

#ifndef STOP_BITS_1
#define STOP_BITS_1 0x00
#endif

#ifndef STOP_BITS_2
#define STOP_BITS_2 0x01
#endif

#ifndef UART_BAUD_SELECT
#define UART_BAUD_SELECT(baudrate, f_cpu) ((f_cpu) / ((baudrate)*16L) - 1)
#endif

#ifndef UART_BAUD_SELECT_DOUBLE_SPEED
#define UART_BAUD_SELECT_DOUBLE_SPEED(baudrate, f_cpu) ((f_cpu) / ((baudrate)*8L) - 1)
#endif

#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE 128
#endif

#ifndef UART_TX_BUFFER_SIZE
#define UART_TX_BUFFER_SIZE 128
#endif

#ifndef UART_RX_BUFFER_MASK
#define UART_RX_BUFFER_MASK (UART_RX_BUFFER_SIZE - 1)
#endif

#ifndef UART_TX_BUFFER_MASK
#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE - 1)
#endif

#ifndef UART_RX_INTERRUPT
#define UART_RX_INTERRUPT USART_RX_vect
#endif

#ifndef UART_TX_INTERRUPT
#define UART_TX_INTERRUPT USART_TX_vect
#endif

#ifndef UART_UDRE_INTERRUPT
#define UART_UDRE_INTERRUPT USART_UDRE_vect
#endif

#ifndef UART_NEW_RX_TAIL
#define UART_NEW_RX_TAIL(rx_tail) ((rx_tail + 1) & UART_RX_BUFFER_MASK)
#endif

#ifndef UART_NEW_RX_HEAD
#define UART_NEW_RX_HEAD(rx_head) ((rx_head + 1) & UART_RX_BUFFER_MASK)
#endif

#ifndef UART_NEW_TX_TAIL
#define UART_NEW_TX_TAIL(tx_tail) ((tx_tail + 1) & UART_TX_BUFFER_MASK)
#endif

#ifndef UART_NEW_TX_HEAD
#define UART_NEW_TX_HEAD(tx_head) ((tx_head + 1) & UART_TX_BUFFER_MASK)
#endif

// rx errors
#ifndef UART_RX_ERROR_OVERFLOW
#define UART_RX_ERROR_OVERFLOW 0x01
#endif

#ifndef UART_RX_ERROR_NONE
#define UART_RX_ERROR_NONE 0x00
#endif
