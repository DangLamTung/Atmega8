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