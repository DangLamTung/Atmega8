/*
 * GccApplication2.c
 *
 * Created: 2/19/2019 8:04:37 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
int main(){
	DDRB = 0xFF;
	while(1){
	PORTB = 0B00000100;
	_delay_ms(1000);
	PORTB = 0B00000000;
	_delay_ms(1000);
	}
	return 0;
}