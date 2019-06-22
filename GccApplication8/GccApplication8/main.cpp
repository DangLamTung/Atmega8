/*
 * GccApplication8.cpp
 *
 * Created: 4/1/2019 7:38:09 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 1000000UL
int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TCCR0 = (1<<CS00); //set chia 8
	TCNT0 = 0;
	TIMSK = (1<<TOIE0);
	OCR2 = 128;
	// set PWM for 50% duty cycle


	TCCR0 |= (1 << COM21);
	// set none-inverting mode

	TCCR0 |= (1 << WGM21) | (1 << WGM20);
	sei();
    while (1) 
    {
		for(int i = 0; i<255;i++){
			OCR2 = i;
			_delay_ms(100);
		}
		for(int i = 255; i>0;i--){
			OCR2 = i;
			_delay_ms(100);
		}
    }
}

ISR (INT0_vect ){
	PORTB ^=1;
}
