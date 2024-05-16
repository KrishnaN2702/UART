
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



void rec_init();
unsigned char rec_val;

void main()
{
    rec_init();
    
    while (1)
    {
           if (PIR1 & 0x20)  //to enable RCIF for who data is transmiting or not
           {
            rec_val = RCREG; //transmited data
            switch (rec_val) //enable switches
            {
            case 'A':
                PORTD = 0x02; //0000 0010  rd1=1 and rd4=0
                break;

            case 'B':
                PORTD = 0x10; //0001 0000  rd4=1 and rd1=0
                break;

            case 'C':
                PORTD = 0x12; //0001 0010  rd4=1 and rd1=1
                break;

            case 'D':
                PORTD = 0x00; //0000 0000 rd4=0 and rd1 =0
                break;
            }
        }
    }
    
}

void rec_init()
{
    TRISD = 0x00;  // rd1 and rd4 are connected to a led as an output
    TRISC = 0xC0;  // 1100 0000 bit7 and 6 where 1 to enable rx and tx since for serial port
    TXSTA = 0x20;  // 0010 0000 bit 5 is 1 for transmit enable
    RCSTA = 0x90;  // 1001 0000  here bit 4 and 7 are 1 since SPEN IS 1 for rx and tx enable in serial port and CREN is for continuous receive enable
    SPBRG = 0x09;  // 0000 1001 calculate baud rate per sec for 9600 is fosc/64*9600-1 = 6000000/614000=9.7
}
