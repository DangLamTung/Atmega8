/*
 * I2Catmega8.cpp
 *
 * Created: 4/5/2019 2:09:54 PM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <lcd.h>
#define sbi(port,bit) port |= (1<<bit)
#define cbi(port,bit) port &= ~(1<<bit)
void TWI_Start(){ TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);}
void TWI_Startr(){ TWCR = (1<<TWINT)|(1<<TWEN);}
void TWI_Stop(){ 
  TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    while(TWCR&(1<<TWSTO));
  }
  
void waitI2C() { while (!(TWCR & (1<<TWINT)));}
uint8_t get_i2c_status() {return (TWSR & 0xF8); }
void I2C_Init()     /* I2C initialize function */
{
  
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

int main(void)
{
    /* Replace with your application code */
  init_lcd();
  clr_lcd();
  
  putchar_lcd('1');
    while (1) 
    {
    }
}
