/*
 * uart.h
 *
 * Created: 4/21/2019 12:42:08 AM
 *  Author: PC
 */ 

#include <stdlib.h>
#ifndef UART_H_
#define UART_H_
void uart_init(){
	UBRR0H = 0;
	UBRR0L = 12;
	
	UCSR0A = (1<<U2X0);
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

void uart_transmit(char data){
	while(!(UCSR0A|(1<<UDRE0)));
	UDR0 = data;
}

void uart_transmit_string(char* data)
{
	int i=0;
	while (data[i]!=0)
	{
		uart_transmit(data[i]);						/* Send each char of string till the NULL */
		i++;
	}
}

void uart_transmit_number(uint8_t num){
	char temp[2];
	itoa(num,temp,16);
	for(int i = 0 ;i < 2 ; i++){
		uart_transmit(temp[i]);
	}
}



#endif /* UART_H_ */