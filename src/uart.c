#include "uart.h"

uint8_t uart_init(uint16_t baudrate, uint8_t parityMode, uint8_t stopBitNum, uint8_t numDataBits, uint8_t asyncDoubleTransmitSpeed, uint8_t multiProcCom) {
    uart_tx_head = 0;
    uart_tx_tail = 0;
    uart_rx_head = 0;
    uart_rx_tail = 0;
    uart_rx_error = UART_RX_ERROR_NONE;
    uart_udre_callback = NULL;
    
    // Set baud rate
    UBRR0H = (uint8_t)(baudrate>>8);
    UBRR0L = (uint8_t)(baudrate);

    UCSR0A = 0x00; // Clear the status register

    if (asyncDoubleTransmitSpeed) {
        UCSR0A |= _BV(U2X0);    // Set the double transmit speed bit
    } if (multiProcCom) {
        UCSR0A |= _BV(MPCM0);   // Set the multi-processor communication bit
    }
    
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); // Enable receiver and transmitter
    UCSR0B |= _BV(UDRIE0);  // Enable the data register empty interrupt
    UCSR0B |= _BV(TXCIE0);  // Enable the transmit complete interrupt
    UCSR0B |= _BV(RXCIE0);  // Enable the receive complete interrupt
    
    UCSR0C = 0x00;  // Clear the control register
    UCSR0C = (parityMode << UPM00) | (stopBitNum << USBS0); // Set the parity mode and stop bit number
    switch (numDataBits) {
        case 5:
            break;
        case 6:
            UCSR0C |= _BV(UCSZ00);
            break;
        case 7:
            UCSR0C |= _BV(UCSZ01);
            break;
        case 8:
            UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
            break;
        case 9:
            UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);
            UCSR0B |= _BV(UCSZ02);
            break;
        default:
            return FAILURE;
    }
    
    return SUCCESS;
}

uint8_t uart_has_data(void) {
    return uart_rx_head != uart_rx_tail;
}

uint8_t uart_getchar(void) {
    while (!uart_has_data()); // Wait for data to be received

    uart_rx_tail = UART_NEW_RX_TAIL(uart_rx_tail);
    uint8_t data = uart_rx_buffer[uart_rx_tail];
    return data;
}

uint8_t uart_send_byte(uint8_t data) {
    uint8_t new_head = UART_NEW_TX_HEAD(uart_tx_head);

    while (new_head == uart_tx_tail); // Wait for space in the buffer
    
    uart_tx_head = new_head;
    uart_tx_buffer[uart_tx_head] = data;
    UCSR0B |= _BV(UDRIE0);  // Enable the data register empty interrupt

    return SUCCESS;
}

uint8_t uart_send(char* data, uint16_t length, callback_t callback) {
    uint8_t i;
    uart_udre_callback = callback;
    for (i = 0; i < length; i++) {
        if (uart_send_byte(data[i]) == FAILURE) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

ISR(UART_UDRE_INTERRUPT) {
    if (uart_tx_head != uart_tx_tail) {
        uart_tx_tail = UART_NEW_TX_TAIL(uart_tx_tail);
        UDR0 = uart_tx_buffer[uart_tx_tail];
    } else {
        UCSR0B &= ~_BV(UDRIE0); // Disable the data register empty interrupt
        // Call the callback function
        if (uart_udre_callback != NULL) {
            uart_udre_callback();
        }
    }
}

ISR(UART_TX_INTERRUPT) {
    UCSR0A |= _BV(TXC0); // Clear the transmission complete flag
}

ISR(UART_RX_INTERRUPT) {
    uint8_t data = UDR0;
    uint8_t new_head = UART_NEW_RX_HEAD(uart_rx_head);
    if (new_head != uart_rx_tail) {
        uart_rx_head = new_head;
        uart_rx_buffer[uart_rx_head] = data;
        uart_rx_error = UART_RX_ERROR_NONE;
    } else {
        uart_rx_error = UART_RX_ERROR_OVERFLOW; // Buffer is full
    }
}