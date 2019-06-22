/*
 * interrupt.cpp
 *
 * Created: 4/11/2019 12:28:41 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
int main(){
DDRB = 0xFF;         //PB as output
PORTB= 0x00;         //keep all LEDs off

while(1)
{
	PORTB &= 0xFF;       //turn LED off
	_delay_ms(1000);   //wait for half second
	PORTB |= 0x00;       //turn LED on
	_delay_ms(1000);   //wait for half second
}
}

