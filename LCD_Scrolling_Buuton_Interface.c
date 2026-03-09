
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define RS RB0
#define BUTTON RC0
#define E RB1
#define LCD_PORT PORTD
#define _XTAL_FREQ 16000000
#include <xc.h>
void lcd_cmd(unsigned char cmd)
{
    RS =0;
    LCD_PORT =cmd;
    E=1;
    __delay_ms(1);
    E=0;   
}
void lcd_data(unsigned char data)
{
    RS=1;
    LCD_PORT = data;
    E =1;
    __delay_ms(1);
    E=0;
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
    __delay_ms(10);
    lcd_cmd(0X38);
    lcd_cmd(0X0C);
    lcd_cmd(0X06);
    lcd_cmd(0X01);
}

int main(void)
{
    TRISB = 0;
    TRISD = 0;
    TRISC0 = 1;
    PORTB = 0;
    PORTD = 0;
    lcd_init();
    lcd_cmd(0x80);
    lcd_string("Kaalai Vanakkam");
    while(1)
    {
        if(BUTTON == 0)    
        {
            __delay_ms(50); 
            lcd_cmd(0x1C);  
            while(BUTTON == 0);
        }
    }
}
