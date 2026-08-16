// pwm.h
#ifndef PWM_H
#define PWM_H

#include <xc.h>
#include <stdint.h>

void PWM1_Init(void);
void PWM1_SetDuty(uint16_t duty);   // duty de 0 a 1023 (10 bits)

#endif
