/*
 * lcd.h
 *
 * Created: 4/5/2019 8:21:04 PM
 *  Author: PC
 */ 


#ifndef LCD_H_
#define LCD_H_
char read2Nib();
void write2Nib(uint8_t chr);
void write8bit(uint8_t chr);
void wait_LCD();
void init_LCD();
void clr_LCD();
void home_LCD();
void move_LCD(uint8_t y, uint8_t x);
void putchar_LCD(uint8_t chr);
void print_LCD(char*str, unsigned char len);

#define EN 2
#define RW 1
#define RS 0

#define ctrl PORTB
#define ddr_ctrl DDRB
#define data_o PORTB
#define data_i PINB
#define ddr_data DDRB




#endif /* LCD_H_ */