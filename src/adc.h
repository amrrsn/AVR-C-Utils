#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "generic_defines.h"
#include "adc_defines.h"

// bit fields for adc configuration
typedef struct {
    uint8_t auto_trig_enable : 1;
    uint8_t auto_trig_src : 3;
    uint8_t interrupt_enable : 1;
    uint8_t prescaler : 3;
    uint8_t multiplex_enable : 1;
    uint8_t refs : 2;
    uint8_t left_adjust_result : 1;
    uint8_t channel : 4;
} adc_config_t;

uint8_t adc_has_data(void);
uint8_t adc_init(adc_config_t *config);
uint16_t adc_read(void);
