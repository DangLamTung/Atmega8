/*
 * adcAtmega8.cpp
 *
 * Created: 4/2/2019 10:07:14 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 10000000L
#define loop_until_bit_is_set(sfr,bit) do{}while(!bit_is_clear(sfr,bit))
uint16_t readADC(unsigned char adc_pin){
	ADMUX = adc_pin | (1<<REFS1) | (1<<REFS0);
	ADCSRA |= (1<<ADSC);
	loop_until_bit_is_set(ADCSRA,ADIF);
	return ADCW;
}
int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	
	TCCR0 = (1<<CS02); //set chia 8
	TCNT0 = 0;
	TIMSK = (1<<TOIE0);
	sei();



	ADCSRA = (1<<ADEN) | (1<<ADPS0)|(1<<ADPS2);
	ADMUX = (1<<REFS1) | (1<<REFS0);
	DDRB = 0xFF;
    while (1) 
    {
		TCNT0 = readADC(0);
		 
    }
}
ISR(TIMER0_OVF_vect){	
	PORTB ^= 1;
}
