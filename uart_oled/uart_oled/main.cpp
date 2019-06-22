/*
 * uart_oled.cpp
 *
 * Created: 5/21/2019 5:25:01 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <stdlib.h>
#include "i2c.h"
#include "lcd.h"
volatile char value;
ISR(USART_RX_vect){
	value = UDR0;             //read UART register into value
	lcd_puts((char*)value);
}
int main(void)
{
	lcd_init(LCD_DISP_ON);    // init lcd and turn on
	lcd_clrscr();
	lcd_set_contrast(0x00);

	uart_init();
    /* Replace with your application code */
    while (1) 
    {
		lcd_puts((char*)value);
    }
}

