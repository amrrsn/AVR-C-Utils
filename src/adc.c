#include "adc.h"

uint8_t adc_has_data(void) {
    return (ADCSRA & _BV(ADIF));
}

uint8_t adc_init(adc_config_t *config) {
    ADCSRA = (config->auto_trig_enable << ADATE) | (config->interrupt_enable << ADIE) | (config->prescaler << ADPS0);
    ADCSRB = (config->auto_trig_src << ADTS0) | (config->multiplex_enable << ACME);
    ADMUX = (config->refs << REFS0) | (config->left_adjust_result << ADLAR) | (config->channel << MUX0); // Set the ADC multiplexer register
    
    if (config->channel <= 5) {
        DIDR0 = _BV(config->channel); // Set the digital input disable register
    }

    ADCSRA |= _BV(ADEN) | _BV(ADSC); // Enable the ADC and start a conversion
    return SUCCESS;
}

uint16_t adc_read(void) {
    ADCSRA |= _BV(ADSC);  // Start the conversion
    while (!adc_has_data());    // Wait for the conversion to finish
    ADCSRA |= _BV(ADIF);  // Clear the interrupt flag

    // check the ADLAR bit in ADMUX to determine how to read the result
    if (ADMUX & _BV(ADLAR)) {
        return ADCH;
    }
    return ADC; // Return the result
}