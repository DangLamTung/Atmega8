/*
 * i2cslave.cpp
 *
 * Created: 4/7/2019 4:05:19 PM
 * Author : PC
 */ 
#define F_CPU 8000000UL		/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include inbuilt defined Delay header file */
#include <stdio.h>		/* Include standard I/O header file */
#include <string.h>		/* Include string header file */
#include <avr/io.h>

#include "i2c.c"
#include "lcd.c"

int main(void)
{
	char buffer[10];
    int count = 0;
	init_LCD();
	I2C_Init();
    while (1) 
    {
		
    }
}

