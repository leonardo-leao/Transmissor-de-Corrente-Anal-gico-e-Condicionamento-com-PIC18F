// pwm.c
#include "pwm.h"

void PWM1_Init(void)
{
    // CCP1 (RC2) como sa�da
    TRISCbits.TRISC2 = 0;

    // Período do PWM (~5 kHz com Fosc = 8 MHz e prescaler = 4)
    // f_pwm = Fosc / (4 * Prescaler * (PR2 + 1))
    // 5000 = 8e6 / (4 * 4 * (PR2 + 1))  => PR2 ? 99
    PR2 = 99;

    // Timer2: prescaler 1:4
    T2CONbits.T2CKPS = 0b01;
    T2CONbits.TMR2ON = 1;       // liga Timer2

    // CCP1 em modo PWM
    CCP1CONbits.CCP1M = 0b1100;
}

// duty de 0 a 1023 (10 bits)
void PWM1_SetDuty(uint16_t duty)
{
    // 1. Limitar a entrada entre 0 e 1023
    if (duty > 1023) duty = 1023;

    // 2. Processar o duty conforme a fórmula:
    // novoDuty = 0.7370 * duty + 80
     //Usando ponto fixo: (duty * 7370) / 10000 + 80

    uint32_t temp = (uint32_t)duty * 6569UL;   // multiplicação em 32 bits
    uint16_t novoDuty = (uint16_t)(temp / 10000UL) + 233;
    
    if (novoDuty > 905) novoDuty = 905;


    // 3. Carregar o valor processado no módulo PWM
    CCPR1L = novoDuty >> 2;              // 8 bits mais altos
    CCP1CONbits.DC1B = novoDuty & 0x03;  // 2 bits baixos
}

