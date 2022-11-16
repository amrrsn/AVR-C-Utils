#pragma once

#include <avr/interrupt.h>
#include "generic_defines.h"
#include "adc_defines.h"

typedef struct {
    uint8_t auto_trigger : 1;
    uint8_t trigger_src : 3;
    uint8_t interrupt : 1;
    uint8_t prescaler : 3;
    uint8_t multiplex_enable : 1;
    uint8_t ref : 2;
    uint8_t left_adjust : 1;
    uint8_t channel : 4;
} adc_config_t;

uint8_t adc_has_data(void);
uint8_t adc_init(adc_config_t *config);
uint16_t adc_read(void);
