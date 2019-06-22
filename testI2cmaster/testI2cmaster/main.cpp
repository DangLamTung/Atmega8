/*
 * testI2cmaster.cpp
 *
 * Created: 4/7/2019 2:31:25 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include "i2c.c"
#include "lcd.c"
#include "stdint.h"
#include "stdio.h"

#define slave_read_addr 0x20
#define slave_write_addr 0x21
#define count 10
#define F_CPU 80000000UL
int main(void)
{
	char buffer[10];
	init_LCD();
	I2C_Init();
    clr_LCD();
	home_LCD();
	move_LCD(1,5);
	print_LCD("Hello World",16);
    while (1) 
    {
		move_LCD(2,1);
		print_LCD("sending:",8);
		readI2C(slave_write_addr);
		waitI2C();
		for(int i = 0; i<count; i++){
		writeI2C(i);
		_delay_ms(500);
		}
		
		}
		 TWI_Stop();		/* Stop I2C */
}


