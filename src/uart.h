#pragma once

#include <avr/interrupt.h>
#include "generic_defines.h"
#include "uart_defines.h"

// bit fields for uart configuration
typedef struct {
    uint16_t baud_rate : 12;
    uint16_t stop_bits : 1;
    uint16_t parity : 2;
    uint16_t data_bits : 4;
    uint16_t double_speed : 1;
    uint16_t multi_proc : 1;
} uart_config_t;

uint8_t uart_init(uart_config_t* config);
uint8_t uart_send(char* data, uint16_t length, callback_t callback);
uint8_t uart_has_data(void);
uint8_t uart_getchar(void);
ISR(UART_TX_INTERRUPT); // Transmit interrupt
ISR(UART_RX_INTERRUPT); // Receive interrupt
ISR(UART_UDRE_INTERRUPT); // Data register empty interrupt

static volatile uint8_t uart_tx_buffer[UART_TX_BUFFER_SIZE];
static volatile uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t uart_tx_head;
static volatile uint8_t uart_tx_tail;
static volatile uint8_t uart_rx_head;
static volatile uint8_t uart_rx_tail;
static volatile uint8_t uart_rx_error;

static volatile callback_t uart_udre_callback;
