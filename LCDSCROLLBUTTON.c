
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

#define _XTAL_FREQ 16000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define RS RB0
#define EN RB1
#define BUTTON RA0
#include <xc.h>

void lcd_enable()
{
    EN = 1;
    __delay_ms(1);
    EN =0;
}
void lcd_cmd(unsigned char cmd)
{
    RS=0;
    PORTB=(PORTB & 0X03)|(cmd & 0XF0);
    lcd_enable();
    PORTB=(PORTB & 0X03)|((cmd<<4) & 0XF0);
    lcd_enable();
}
void lcd_data(unsigned char data)
{
    RS=1;
    PORTB=(PORTB & 0X03)|(data & 0XF0);
    lcd_enable();
    PORTB =(PORTB & 0x03)|((data<<4) & 0XF0);
    lcd_enable();
}
void lcd_string(const char *d)
{
    while(*d)
    {
        lcd_data(*d++);
    }
}
void lcd_init()
{
    ADCON1 = 0x06;
    TRISB = 0x00;
    TRISA = 0x01;
    __delay_ms(2);
    lcd_cmd(0x02);
    lcd_cmd(0x28); 
    lcd_cmd(0x0C); 
    lcd_cmd(0x06); 
    lcd_cmd(0x01); 
    __delay_ms(2);
}
void main()
{
    
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("Valakkamungooo");
    while(1)
    {
        if(BUTTON==0)
        {
            __delay_ms(50);
            if(BUTTON == 0)
            {
                lcd_cmd(0X1C);
                while(BUTTON == 0);
            }
        }
    }
}
