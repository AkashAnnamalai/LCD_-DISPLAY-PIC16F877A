#include <xc.h>

#define _XTAL_FREQ 16000000

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define RS RB0
#define E  RB1

void lcd_cmd(unsigned char cmd)
{
    RS = 0;
    PORTD = cmd;
    E = 1;
    __delay_ms(2);
    E = 0;
}

void lcd_data(unsigned char data)
{
    RS = 1;
    PORTD = data;
    E = 1;
    __delay_ms(2);
    E = 0;
}

void lcd_string(const char *c)
{
    while(*c)
    {
        lcd_data(*c++);
    }
}

void lcd_init()
{
    __delay_ms(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

void lcd_number(int num)
{
    lcd_data((num/100)+'0');
    lcd_data(((num/10)%10)+'0');
    lcd_data((num%10)+'0');
}

void main()
{
    TRISB = 0x00;
    TRISD = 0x00;
    TRISC = 0x01;

    PORTB = 0;
    PORTD = 0;

    lcd_init();

    int count = 0;

    lcd_cmd(0x80);
    lcd_string("Button Count:");

    while(1)
    {
        if(RC0 == 0)
        {
            __delay_ms(50);

            if(RC0 == 0)
            {
                count++;
                lcd_cmd(0xC0);   
                lcd_number(count);
                while(RC0 == 0);
            }
        }
    }
}
