#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <avr/delay.h>
#include "lcd.c"

#define F_CPU 80000000UL
#define sbi(port,bit) port |= (1<<bit)
#define cbi(port,bit) port &= ~(1<<bit)
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

void TWI_Start(){ TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);}
void TWI_Startr(){ TWCR = (1<<TWINT)|(1<<TWEN);}
void TWI_Stop(){
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(TWCR&(1<<TWSTO));
}

void waitI2C() { while (!(TWCR & (1<<TWINT)));}
uint8_t get_i2c_status() {return (TWSR & 0xF8); }
void I2C_Init()			/* I2C initialize function */
{
	TWSR = 0x00;
	TWBR = 32;
}

uint8_t readI2C(char address){
	uint8_t status;
	TWI_Start();
	waitI2C();
	if (get_i2c_status() != 0x08) return 0;//send connect status
	waitI2C();
	TWDR = address;
	TWCR = (1<<TWINT)|(1<<TWEN);
	waitI2C();
	status = get_i2c_status();
	if(status == 0x40)
	return 1;
	if(status == 0x48)
	return 2;
	return 3;
}
uint8_t readI2Crepeat(char address){
	uint8_t status;
	TWI_Startr();
	waitI2C();
	if (get_i2c_status() != 0x08) return 0;//send connect status
	waitI2C();
	TWDR = address;
	TWCR = (1<<TWINT)|(1<<TWEN);
	waitI2C();
	status = get_i2c_status();
	if(status == 0x40)
	return 1;
	if(status == 0x48)
	return 2;
	return 3;
}
uint8_t writeI2C(char data){
	uint8_t status;
	TWI_Start();
	waitI2C();
	if (get_i2c_status() != 0x08) return 0;//send connect status
	waitI2C();
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	waitI2C();
	status = get_i2c_status();
	if(status == 0x40)
	return 1;
	if(status == 0x48)
	return 2;
	return 3;
}
char readI2CAck(){
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	waitI2C();
	return TWDR;
}
char readI2CNack(){
	TWCR = (1<<TWEN)|(1<<TWINT);
	waitI2C();
	return TWDR;
}
void I2C_Slave_Init(uint8_t slave_address)
{
	TWAR=slave_address;		/* Assign Address in TWI address register */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI, Enable ack generation */
}

int8_t I2C_Slave_Listen()
{
	while(1)
	{
		uint8_t status;			/* Declare variable */
		while(!(TWCR&(1<<TWINT)));	/* Wait to be addressed */
		status=TWSR&0xF8;		/* Read TWI status register */
		if(status==0x60||status==0x68)	/* Own SLA+W received &ack returned */
		return 0;			/* Return 0 to indicate ack returned */
		if(status==0xA8||status==0xB0)	/* Own SLA+R received &ack returned */
		return 1;			/* Return 0 to indicate ack returned */
		if(status==0x70||status==0x78)	/* General call received &ack returned */
		return 2;			/* Return 1 to indicate ack returned */
		else
		continue;			/* Else continue */
	}
}

int8_t I2C_Slave_Transmit(char data)
{
	uint8_t status;
	TWDR=data;			/* Write data to TWDR to be transmitted */
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);/* Enable TWI & clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0xA0)		/* Check for STOP/REPEATED START received */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}
	if(status==0xB8)		/* Check for data transmitted &ack received */
	return 0;			/* If yes then return 0 */
	if(status==0xC0)		/* Check for data transmitted &nack received */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -2 */
		return -2;
	}
	if(status==0xC8)		/* Last byte transmitted with ack received */
	return -3;			/* If yes then return -3 */
	else			/* else return -4 */
	return -4;
}

char I2C_Slave_Receive()
{
	uint8_t status;		/* Declare variable */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI & generation of ack */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x80||status==0x90)/* Check for data received &ack returned */
	return TWDR;		/* If yes then return received data */

	/* Check for data received, nack returned & switched to not addressed slave mode */
	if(status==0x88||status==0x98)
	return TWDR;		/* If yes then return received data */
	if(status==0xA0)		/* Check wether STOP/REPEATED START */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}
	else
	return -2;			/* Else return -2 */
}