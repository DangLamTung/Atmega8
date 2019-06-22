/*
 * thirdStep.cpp
 *
 * Created: 4/21/2019 12:41:08 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "i2c.h"
#include <stdlib.h>
#include <stdio.h>	
#include <math.h>

#define F_CPU 1000000UL

#define  WHO_AM_I 0x75
#define  SAMPLE_RATE 0x19
#define  PWR_MGMT_1 0x6B
#define  CONFIG 0x1A
#define  GYRO_CONFIG  0x1B 
#define  INIT_ENB 0x38
#define  ACCEL_XOUT_H 0x3B
#define  GYRO_ZOUT_L 0x48

#define  MPU_START 0x69
#define  inter 0x01
#define  gyro_con 0x18
#define  gyroXF 1
#define  sample_1khz 7
#define  reg1 0x68
#define  reg2 0x69
#define  PI 3.141592654
#define  RAD2DEC 57.29577951

double  accel_factor = 16384.0;
double  gyro_factor = 16.4;

uint8_t  ADDRESS  = 0x68;
double Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;
double pitch, roll;
double dt = 0.000512; // th?i gian l?y m?u, ?ã test b?ng timer
double alpha = 0.96;

double curentAngle;
void startTimer(){
	TCCR1A = (1<<COM1A1);
	TCCR1B = (1<<CS10);
}
float readDtime(){
	int temp;
	TCNT1 = 0x1FF;
	temp = TCNT1;
	TCCR1B = (0<<CS10);
	return temp/1000000.0;
}

void scanI2C(){
	uint8_t addr;
	init_I2C();
	for(addr = 0x00; addr < 0x80; addr++){
		if(TWI_start(addr,TW_WRITE)==0){
			uart_transmit_string("found a device at: ");
			uart_transmit_number(addr);
            ADDRESS = addr;
		}
		else{
			uart_transmit('.');
		}
		_delay_ms(10);
	}
}

void initMPU6050(){
	writeResgister(SAMPLE_RATE,sample_1khz, ADDRESS);
	writeResgister(CONFIG,gyroXF,ADDRESS);
	writeResgister(GYRO_CONFIG,gyro_con,ADDRESS);
	writeResgister(INIT_ENB,inter,ADDRESS);
	writeResgister(PWR_MGMT_1,inter,ADDRESS);
	uart_transmit_string("init MPU");
}

void MPU_Start_Loc()
{
	TWI_start(0x68,TW_WRITE);								/* I2C start with device write address */
	TWI_write(ACCEL_XOUT_H,0x68);							/* Write start location address from where to read */
	TWI_start(0x68,TW_READ);							/* I2C start with device read address */
}
void readMPURaw(){
    //startTimer();
	MPU_Start_Loc();
	Acc_x = (((int)TWI_readAck()<<8) | (int)TWI_readAck());
	Acc_y = (((int)TWI_readAck()<<8) | (int)TWI_readAck());
	Acc_z = (((int)TWI_readAck()<<8) | (int)TWI_readAck());
	Temperature = (((int)TWI_readAck()<<8) | (int)TWI_readAck());
	Gyro_x = (((int)TWI_readAck()<<8) | (int)TWI_readAck());
	Gyro_y = (((int)TWI_readAck()<<8) | (int)TWI_readAck());
	Gyro_z = (((int)TWI_readAck()<<8) | (int)TWI_readNack());
    
	TWI_stop();
	//dt = readDtime();
	Acc_x /= accel_factor;
	Acc_y /= accel_factor;
	Acc_z /= accel_factor;
	
	Gyro_x /= gyro_factor;
	Gyro_y /= gyro_factor;
	Gyro_z /= gyro_factor;
}

void processMPU()
{
	roll = atan2(Acc_y,Acc_z)*RAD2DEC;
	pitch = atan(-Acc_x/sqrt(Acc_y*Acc_y+Acc_z*Acc_z))*RAD2DEC;
}
double complemetary_filter(double curentAngle, double accel, double gyro){
	return alpha*(curentAngle + gyro*dt) + (1-alpha)*accel;
}
int main(void)
{

    uart_init();
	init_I2C();
	scanI2C();
	initMPU6050();
	
    while (1) 
    {
		readMPURaw();
		char buffer[20],temp[10];
		processMPU();
		
		
		
		dtostrf( curentAngle , 3, 2, temp );
		sprintf(buffer," %s\n",temp);
		uart_transmit_string(buffer);
		
		//uart_transmit_string("\n");
    }
}

