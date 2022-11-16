#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "generic_defines.h"

#define MOSI PB3
#define SCK PB5
#define SS PB2
#define MISO PB4
#define SPI_DDR DDRB
#define SPI_PORT PORTB

uint8_t spi_init(uint8_t spcr, uint8_t spsr, uint8_t spdr, uint8_t interrupt);
uint8_t spi_transmit_blocking(uint8_t data);

uint8_t spi_init(uint8_t spcr, uint8_t spsr, uint8_t spdr, uint8_t interrupt) {
    // Set MISO as input
    SPI_DDR &= ~_BV(MISO);
    SPCR = spcr;
    SPSR = spsr;
    SPDR = spdr;

    // Set MOSI, SCK and SS as output
    SPI_DDR |= _BV(MOSI) | _BV(SCK) | _BV(SS);

    if (interrupt) {
        // Enable SPI interrupt
        SPCR |= _BV(SPIE);
        // Enable global interrupt
        sei();
    }
    return 0;
}

uint8_t spi_transmit_blocking(uint8_t data) {
    // Start transmission
    SPDR = data;
    // Wait for transmission complete
    while (!(SPSR & _BV(SPIF)));
    return 0;
}