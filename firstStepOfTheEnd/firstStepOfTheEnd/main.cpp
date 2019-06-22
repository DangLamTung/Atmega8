/*
 * firstStepOfTheEnd.cpp
 *
 * Created: 4/18/2019 4:19:58 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#define  F_CPU 10000000UL
#define loop_until_bit_is_set(sfr,bit) do { } while (bit_is_clear(sfr, bit))
uint16_t ADC_data = 1000;
void init_ADC(){
	ADMUX = (1<<REFS0)|(1<<MUX1)|(1<<MUX0)|(1<<ADLAR);//2.56 VREF, ADC3
	ADCSRA = (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);//enable adc, enable interrupt adc
	
}
void uart_init(){
	UBRRH = 0;
	UBRRL = 12;
	
	UCSRA = (1<<U2X);
	
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
}

void uart_transmit(char data){
	while(!(UCSRA&(1<<UDRE)));
	UDR = data;
}

uint16_t readADC(){	
	uint16_t high, low;
	ADCSRA |= (1<<ADSC);
	loop_until_bit_is_set(ADCSRA,ADIF); 
	low = ADCL;
	high = ADCH;
	high <<=2;
	
	return high|low;
}
int main(void)
{
	init_ADC();
	uart_init();
    char temp[4];
	//sei();
	while(1){
	ADC_data = readADC();
    itoa(ADC_data, temp,10);
	for(int i = 0; i <4;i++){
		uart_transmit(temp[i]);
	}
    uart_transmit(' ');
	}
}

