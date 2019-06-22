/*
 * GccApplication4.cpp
 *
 * Created: 3/7/2019 10:12:20 PM
 * Author : PC
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRB |= (1<<6);
    while (1) 
    {
		PORTB |= (1<<6);
		_delay_ms(1000);
		PORTB &= ~(1<<6);
		_delay_ms(1000);
    }
}

