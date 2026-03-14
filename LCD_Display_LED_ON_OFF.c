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
#pragma config CP = OFF        

#define RS RB0
#define EN RB1
#define LED RA0
#define BUTTON RA1
#define BUZZER RA2

#include <xc.h>

void lcd_enable()
{
    EN = 1;
    __delay_ms(1);
    EN = 0;
}
void lcd_cmd(unsigned char cmd)
{
    RS =0;
    PORTB =(PORTB & 0X03) | (cmd & 0XF0);
    lcd_enable();
    PORTB = (PORTB & 0X03) | ((cmd<<4) & 0XF0);
    lcd_enable();
}
void lcd_data(unsigned char data)
{
    RS =1;
    PORTB = (PORTB & 0X03) |(data & 0XF0);
    lcd_enable();
    PORTB =(PORTB & 0X03) |((data<<4) & 0XF0);
    lcd_enable();
}
void lcd_string(const char *a)
{
    while(*a)
    {
        lcd_data(*a++);
    }
}
void lcd_init()
{
    TRISB = 0x00;
    __delay_ms(20);
    lcd_cmd(0x02);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}
int main(void) 
{
    TRISA0 = 0;
    TRISA1 = 1;
    TRISA2 = 0;
    ADCON1 =0x06;
    lcd_init();
    
    LED = 0;
    lcd_cmd(0X80);
    lcd_string("LED OFF");
    
    while(1)
    {
        if(BUTTON == 1)
        {
            __delay_ms(20);
            LED = !LED;
            lcd_cmd(0X01);
            if(LED ==1)
            {
                BUZZER =1;
                lcd_cmd(0X80);
                lcd_string("LED ON...");
            }
            else
            {
                BUZZER =0;
                lcd_cmd(0X80);
                lcd_string("LED OFF...");
            }
            while(BUTTON ==1);
        }
    } 
}
