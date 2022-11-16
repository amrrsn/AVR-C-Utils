#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "generic_defines.h"
#include "uart_defines.h"

uint8_t uart_init(uint16_t baudrate, uint8_t parityMode, uint8_t stopBitNum, uint8_t numDataBits, uint8_t asyncDoubleTransmitSpeed, uint8_t multiProcCom);
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
