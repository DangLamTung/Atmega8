/*
 * lcd.h
 *
 * Created: 2/20/2019 2:57:28 PM
 *  Author: PC
 */ 


#ifndef LCD_H_
#define LCD_H_
void readLCD();
void writeLCD(uint8_t chr);
void waitLCD();
void init_lcd();
void home_lcd();
void move_lcd(uint8_t x, uint8_t y);
void clr_lcd();
void putchar_lcd(uint8_t chr);
void printLCD(char *str, unsigned char len);
#endif /* LCD_H_ */