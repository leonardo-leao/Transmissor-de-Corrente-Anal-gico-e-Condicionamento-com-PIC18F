// main.c
#include <xc.h>
#include <stdint.h>
#include "adc.h"
#include "pwm.h"

// PIC18F4520 Configuration Bit Settings

// CONFIG1H
#pragma config OSC  = INTIO67   // Oscilador interno, RA6/RA7 como I/O
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor desabilitado
#pragma config IESO  = OFF      // Switchover int/externo desabilitado

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer desabilitado
#pragma config BOREN = OFF      // Brown-out Reset desabilitado
#pragma config BORV = 3         // (tanto faz se BOREN = OFF)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog desabilitado
#pragma config WDTPS = 32768    // (n�o importa com WDT = OFF)

// CONFIG3H
#pragma config PBADEN = OFF     // PORTB digital no reset
#pragma config LPT1OSC = OFF
#pragma config MCLRE = ON       // MCLR habilitado

// CONFIG4L
#pragma config STVREN = ON
#pragma config LVP   = OFF      // Programa��o em baixa tens�o OFF
#pragma config XINST = OFF      // Instru��es estendidas OFF


// Frequência do oscilador interno que vamos usar (8 MHz)
#define _XTAL_FREQ 1000000UL   // 1 MHz

static void OSC_Init(void)
{
    // Seleciona 1 MHz no oscilador interno
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF0 = 0;   // IRCF = 100 -> 1 MHz

    // Seleciona o oscilador interno como clock do sistema
    OSCCONbits.SCS1 = 1;
    OSCCONbits.SCS0 = 0;    // SCS = 10 -> clock vem do oscilador interno
}

//=====================================================================

void main(void)
{
    OSC_Init();     // configura oscilador interno em 8 MHz
    ADC_Init();     // inicializa ADC (AN0)
    PWM1_Init();    // inicializa PWM (CCP1 em RC2)

    while (1)
    {
        uint16_t valorADC = ADC_Read(0);   // leitura AN0 (0?1023)
        PWM1_SetDuty(valorADC);            // joga diretamente no PWM

        __delay_ms(1);
    }
}
