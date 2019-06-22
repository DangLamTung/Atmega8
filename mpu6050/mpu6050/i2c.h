/*
 * i2c.h
 *
 * Created: 4/21/2019 12:42:53 AM
 *  Author: PC
 */ 

#include <util/twi.h>
#ifndef I2C_H_
#define I2C_H_
uint8_t init_I2C(){
	TWBR = 2;
	return true;
}

uint8_t TWI_start(uint8_t address, uint8_t TWI_type){
	uint8_t status;
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	
	status = TWSR & 0xF8;
	if((status != TW_START) & (status != TW_REP_START)){
		return 1;
	}
	//get device
	TWDR = (address<<1)|TWI_type;
	TWCR = (1<<TWINT)|(1<<TWEN);
	//wait
	while (!(TWCR & (1<<TWINT)));
	
	status = TWSR & 0xF8;
	if((status != TW_MR_SLA_ACK)&(status != TW_MT_SLA_ACK)){
		return 2;
	}
	return 0;
}
void TWI_stop(void){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while(TWCR &(1<<TWINT));
}
uint8_t TWI_write(uint8_t byte,uint8_t address){
	uint8_t status;
	
	TWDR = byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	
	while(!(TWCR&(1<<TWINT)));
	
	status = TWSR &0xF8;
	if(status != TW_MT_DATA_ACK){
		uart_transmit_string("sent data, NOT ack \n");
		return 1;
	}
	return 0;
}
uint8_t TWI_readAck(){
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	
	return TWDR;
}
uint8_t TWI_readNack(){
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR &(1<<TWINT)));
	return TWDR;
}

uint8_t readResgister(char reg,uint8_t address){
	TWI_start(address, TW_WRITE);
	TWI_write(reg,address);
	TWI_stop();
	
	TWI_start(address,TW_READ);
	char ret = TWI_readNack();
	TWI_stop();
	return ret;
}

void writeResgister(char reg, char value,uint8_t address){
	TWI_start(address,TW_WRITE);
	TWI_write(reg,address);
	TWI_write(value,address);
	TWI_stop();
}




#endif /* I2C_H_ */