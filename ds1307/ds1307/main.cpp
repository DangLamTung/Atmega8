/*
 * ds1307.cpp
 *
 * Created: 4/11/2019 11:44:10 PM
 * Author : PC
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL  // 1 MHz
#include <util/delay.h>

#include <avr/interrupt.h>
#include <util/twi.h>

#define SLAVE_ADDRESS (0x68)

uint8_t value; // contains the received value

uint8_t ongoing_transmission = 0;

// interrupt routine for the timer0 overflow interrupt
ISR(TWI_vect)
{
	// react on TWI status and handle different cases
	uint8_t status = TWSR & 0xFC; // mask-out the prescaler bits
	switch(status)
	{
		case TW_START:  // start transmitted
		ongoing_transmission = 1;
		// write SLA+R, SLA=0x01
		TWDR = (SLAVE_ADDRESS << 1) | 0x01;
		TWCR &= ~((1<<TWSTA)); // clear TWSTA
		break;
		
		case TW_MR_SLA_ACK: // SLA+R transmitted, ACK received
		TWCR &= ~((1<<TWSTA) | (1<<TWSTO));
		break;
		
		case TW_MR_DATA_ACK: // data received, ACK returned
		ongoing_transmission = 0;
		value = TWDR;
		TWCR |= (1<<TWSTO);  // write stop bit
		TWCR &= ~(1<<TWSTA); // clear start bit
		break;
	}
	TWCR |=   (1<<TWINT);  // hand over to TWI hardware
}

int main(void)
{
	// TWI setup
	sei(); // enable global interrupt
	// TWI-ENable , TWI Interrupt Enable
	TWCR |= (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
    TWBR = 32;
	
	
	
	for (;;) // infinite main loop
	{
		// initiate new transmission if
		//    no transmission is in progress
		if (!ongoing_transmission) TWCR |= (1<<TWSTA);
		
	}
}

