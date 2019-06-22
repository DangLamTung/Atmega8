/*
 * i2cReal.cpp
 *
 * Created: 4/11/2019 12:25:43 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#define F_CPU 10000000UL
uint8_t slave_address = 0x01;

ISR(TWI_vect){
	uint8_t status = TWSR & 0xFC;
	switch(status){
		case TW_ST_SLA_ACK:
		     TWDR = 123;
			 TWCR =(1<<TWEN);
			 TWCR &= ~((1<<TWEA)|(1<<TWSTO));
		     break;
		case TW_ST_LAST_DATA:
		     TWCR |= (1<<TWEA);
		break;
	}
	TWCR |= (1<<TWINT);
	}


int main(void)
{
	sei();
	
	TWAR |= (slave_address <<1)|0x01; 
	TWCR |= (1<<TWEA)|(1<<TWEN)|(1<<TWIE); //ENABLE, B?T NG?T
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

