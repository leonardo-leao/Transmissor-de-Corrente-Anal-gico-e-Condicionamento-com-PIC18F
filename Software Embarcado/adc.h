#ifndef ADC_H
#define ADC_H

#define _XTAL_FREQ 8000000UL   // Oscilador interno a 8 MHz

#include <xc.h>
#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t canal);

#endif
