/*
 * LCD.h
 *
 * Created: 2/20/2019 4:43:11 PM
 *  Author: PC
 */ 

char Read2Nib();
void Write8Bit(uint8_t chr);
void Write2Nib(uint8_t chr);
void wait_LCD();
void init_LCD();
void home_LCD();
void move_LCD(uint8_t y,uint8_t x);
void clr_LCD();
void putChar_LCD(uint8_t chr);
void print_LCD(char* str, unsigned char len);
