/*
 * GccApplication1.c
 *
 * Created: 2/17/2019 5:54:42 PM
 * Author : PC
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
volatile uint8_t portbhistory = 0xFF;  

ISR (INT0_vect)
{

		PORTB ^= (1 << PB5);
	
	
}




int main(void)
{
	 DDRB |= (1 << PORTB5);
	 PORTB |= (1<<PORTB5);
	 
	 
	 
	 DDRD &= ~(1 << DDD4);         // Clear the PB0 pin
    // PB0 (PCINT0 pin) is now an input

    PORTD |= (1 << PORTD4);        // turn On the Pull-up
    // PB0 is now an input with pull-up enabled
    /* Ng?t ngoài */
    EICRA |= (1 << ISC00)|(1<<ISC01);    // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);    // set PCINT0 to trigger an interrupt on state change 

    sei();
	 while(1)
	 {
		 /*main program loop here */
	 }
}

