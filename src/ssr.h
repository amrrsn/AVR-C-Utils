#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "spi.h"
#include "generic_defines.h"

#define RCLK_PIN PD2
#define RCLOCK_DDR DDRD
#define RCLOCK_PORT PORTD

#define SER_PIN PD10
#define SER_DDR DDRD
#define SER_PORT PORTD

uint8_t ssr_init();
uint8_t ssr_write(uint8_t data);

uint8_t ssr_init() {
    // Set RCLK as output
    RCLOCK_DDR |= _BV(RCLK_PIN);

    uint8_t spcr0 = _BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(CPOL) | _BV(CPHA); // Enable SPI, Master, set clock rate fck/64, set clock polarity high, set clock phase leading edge
    spi_init(spcr0, 0x00, 0x00, FALSE);
    return 0;
}

uint8_t ssr_write(uint8_t data) {
    spi_transmit_blocking(data);
    uint8_t ignored = SPDR; // Read SPDR to clear SPIF flag

    // Set RCLK high
    RCLOCK_PORT |= _BV(RCLK_PIN);
    // Set RCLK low
    RCLOCK_PORT &= ~_BV(RCLK_PIN);
    return 0;
}