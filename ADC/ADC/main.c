/*
 * ADC.c
 *
 * Created: 2/20/2019 1:10:44 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define ADC_THRESHOLD	512
#define LED_PIN PB0
uint16_t readADC(uint8_t adc_pin){
	ADMUX &= 0xf0;
	ADMUX |= adc_pin;
	ADCSRA |= _BV(ADSC);
	while(ADCSRA & _BV(ADSC));
	
	return ADC;
}
uint8_t dec2bcd(uint8_t dec)
{
	uint8_t result = 0;
	int shift = 0;

	while (dec)
	{
		result +=  (dec % 10) << shift;
		dec = dec / 10;
		shift += 4;
	}
	return result;
}

int main(void)
{
    /* Replace with your application code */
	ADCSRA |= (1<<ADEN);
    DDRB |= 0xFF;
	//PORTB = 0B00000001;
    while (1) 
    {
		PORTB = dec2bcd(readADC(0));
		
    }
}

