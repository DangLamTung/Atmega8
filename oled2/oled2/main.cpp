/*
 * oled2.cpp
 *
 * Created: 5/15/2019 3:56:17 PM
 * Author : PC
 */ 

#include "lcd.h"
#include "i2c.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define F_CPU 8000000UL
#define DS1307 0x68

#define TW_WRITE 0
#define TW_READ 1
int game_mode = 0;
uint8_t sec,min,hour,day,date,month,year;
char buffer [10];

ISR (INT0_vect)
{
	PORTB ^= (1 << PB5);
	pos-=3;
	// 	else
	// 	mode = 1;

}

void init_button(){
	/* Ng?t pin change */
	DDRB |= (1 << PORTB5);
	PORTB |= (1<<PORTB5);
	
	
	
	DDRD &= ~(1 << DDD4);         // Clear the PB0 pin
	// PB0 (PCINT0 pin) is now an input

	PORTD |= (1 << PORTD4);        // turn On the Pull-up
	// PB0 is now an input with pull-up enabled
	/* Ng?t ngoài */
	EICRA |= (1 << ISC00)|(1<<ISC01);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0);    // set PCINT0 to trigger an interrupt on state change

	sei();// set PCINT0 to trigger an interrupt on state change



	          // turn on interrupts

}

void end_game(){
	lcd_charMode(DOUBLESIZE);
	lcd_gotoxy(0,1);
	lcd_puts("   Game  \r\n   Over ");
	lcd_charMode(NORMALSIZE);
	lcd_gotoxy(3,6);
	lcd_puts("* Press reset *");
	lcd_display();
}
int main(void){
	lcd_init(LCD_DISP_ON);    // init lcd and turn on
	
	//lcd_puts("Hello World");  // put string from RAM to display (TEXTMODE) or buffer (GRAPHICMODE)
	lcd_gotoxy(0,2);          // set cursor to first column at line 3

	init_button();
	for(;;){
		
		//lcd_sleep(1000);
		delete_ball(5,pos);
		delete_column(30,doc);
		lcd_display();
		/*lcd_gotoxy(0,0); */
		pos+=1;
		if(pos < 5 || pos > 60){
			end_game();
			break;
		}
		player(pos);
		draw_column(30,doc-3);
		lcd_display();
		//_delay_ms(50);
		doc-=3;
		
		if(doc == 5 && ((pos<25)||(pos>35))){
			end_game();
			break;
		}
		
		
		
	}
	return 0;
}