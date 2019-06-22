/*
 * uart.cpp
 *
 * Created: 4/18/2019 8:11:36 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL
#define baud 9600
#define uart_baud F_CPU/16/baud - 1

void uart_init(){
  UBRR0H =0x00;//(unsigned char)  ( uValue>> 8);  // 0x00
  UBRR0L =0x0C;//(unsigned char) uValue;  // 0x0C
  // enabling TX & RX
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0A = (1<<UDRE0)|(1<<U2X0);
  UCSR0C =  (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stop
	}

void uart_transmit(char data){
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

void uart_transmit_string( char* data,int length){
	for (int i = 0 ; i < length; i++){
		uart_transmit(data[i]);
	}
}
int main(void)
{
	char test [10] = "hello   ";
	uart_init();
    
    while (1) 
    {
		for(char i = 32; i<128;i++){
			uart_transmit(i);
			_delay_ms(100);
		}
	}
}

