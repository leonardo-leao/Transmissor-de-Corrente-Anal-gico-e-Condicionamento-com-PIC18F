// adc.c
#include "adc.h"

void ADC_Init(void)
{
    CMCON = 0x07;
    
    ADCON1 = 0b00001110;

    // ADCON2:
    // ADFM = 1 (resultado a direita, 10 bits)
    // ACQT2:0 = 010 (Tacq = 4 TAD)
    // ADCS2:0 = 110 (Fosc/64)
    ADCON2 = 0b10010110;

    // Seleciona canal 0 (AN0) e liga o ADC
    ADCON0 = 0b00000001;   // CHS3:0 = 0000, ADON = 1

    // RA0 como entrada
    TRISAbits.TRISA0 = 1;
}

uint16_t ADC_Read(uint8_t canal)
{
    // Limpa seleçãoo de canal, preservando ADON
    ADCON0 &= 0b11000001;
    ADCON0 |= (canal << 2);      // coloca canal em CHS3:0

    __delay_us(10);              // tempo de aquisição

    ADCON0bits.GO_DONE = 1;      // inicia conversão
    while (ADCON0bits.GO_DONE);  // espera terminar

    return ((ADRESH << 8) | ADRESL);  // 10 bits
}
