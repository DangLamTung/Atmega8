/*
 * timer.cpp
 *
 * Created: 2/27/2019 10:21:45 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL
int main(void)
{
	PORTB = 0xFF;
	DDRB = 0x00;
	
	
	TCCR1A = (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS10);
	
	OCR1A = 15000;
	OCR1B = 7000;
	ICR1 = 65536;
	

	sei();
    /* Replace with your application code */
    while (1) 
    {
		for(int i = 0; i<65536; i++){
			OCR1A = i;
			_delay_ms(1);
		}
		for(int i = 65536; i>0; i--){
			OCR1A = i;
			_delay_ms(10);
		}
    }
}
