
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

unsigned char switchValue;  // Declare switchValue as a variable

void init();

void main()
{
    init();
    while(1)
    {
        switchValue = PORTB & 0xF0;
        switch(switchValue)
        {
    case 0xE0: //case 1 0xE0
        TXREG = 'A';  // need to transmit A to slave 
        PORTD = 0x02; // LED blinking code for 'A'
        break;

    case 0xD0://case 1 0xD0
        TXREG = 'B';// need to transmit A to slave 
        PORTD = 0x10; // LED blinking code for 'B'
        break;

    case 0xB0://case 1 0xB0
        TXREG = 'C';// need to transmit A to slave 
        PORTD = 0x12; // LED blinking code for 'C'
        break;

    case 0x70://case 1 0x70
        TXREG = 'D';// need to transmit A to slave 
        PORTD = 0x00; // LED blinking code for 'D'
        break;
                
        }
        __delay_ms(100);
    }
}

void init()
{
    TRISB = 0xF0;   // 1111 0000  enable the switches d4,d5,d6,d7
    OPTION_REG = 0x7F; // Enable the pull-up register by setting bit 7 to 0
    TRISC = 0xC0; // 1100 0000 here tx is rc6 is 1 and rc7 rx is 1 in serial port
    RCSTA = 0x90; // 1001 0000  Bit7 makes Serial port enabled and bit 4 is 1 for continuous receive enable bit
    TXSTA = 0x20; // 0010 0000 bit 5 is 1 for enable transmit
    SPBRG = 0x09; // 0000 1001 calculate baud rate per sec for 9600 is fosc/64*9600-1 = 6000000/614000=9.7
}
