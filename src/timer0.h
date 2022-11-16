#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "generic_defines.h"

uint8_t timer0_init(uint8_t tccr0a, uint8_t tccr0b, uint8_t ocr0a, uint8_t ocr0b);

uint8_t timer0_init(uint8_t tccr0a, uint8_t tccr0b, uint8_t ocr0a, uint8_t ocr0b) {
    TCCR0A = tccr0a;    // Set the timer control registers
    TCCR0B = tccr0b;    // Set the timer control registers
    
    OCR0A = ocr0a;  // Set the output compare registers
    OCR0B = ocr0b;  // Set the output compare registers

    DDRD |= _BV(DDD5) | _BV(DDD6);  // Set PD5 and PD6 to output
    return 0;
}