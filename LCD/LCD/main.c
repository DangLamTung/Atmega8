
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

#define RS 2
#define RW 3
#define EN 4
#define CTRL  PORTD
#define DATA_RES PORTB
#define DATA_CTRL DDRB
#define DATA_IN PINB
#define DATA_OUT PORTB

#define bit_is_clear(sfr,bit) (!(_SFR_BYTE(sfr) & _BV(bit)))
#define set(port, bit) port |= (1<<bit);
#define del(port, bit) port &= ~(1<<bit);

void writeLCD(uint8_t chr){
	DATA_OUT = chr;
	set(CTRL,EN);
	del(CTRL,EN);
	
}
void waitLCD(){
	while(1){
		del(CTRL,EN);
		del(CTRL,RS);
		set(CTRL,RW);
		
		DATA_CTRL = 0xFF;
		DATA_OUT = 0xFF;
		set(CTRL,EN);
		
		DATA_CTRL = 0x00;
		if(bit_is_clear(DATA_IN,7))break;
	}
	del(CTRL,EN);
	del(CTRL,RW);
	DATA_CTRL = 0xFF;
}
void init_lcd(){
	DATA_CTRL = 0xFF;
	DATA_RES = 0xFF;
	//set function
	del(CTRL, RS);
	del(CTRL, RW);
	del(CTRL, EN);
	
	writeLCD(0x38);
	waitLCD();
	//control
	del(CTRL,RS);
	writeLCD(0x0E);//set con tr? và không nháy
	waitLCD();
	//entry mode set
	del(CTRL,RS);
	writeLCD(0x06);//không t?ng shift
	waitLCD();
}
void home_lcd(){
	del(CTRL,RS);
	writeLCD(0x02);
	waitLCD();
}
void move_lcd(uint8_t x, uint8_t y){
	uint8_t ad;
	ad = 64*(y-1) + (x-1) +0x80;
	del(CTRL,RS);
	writeLCD(ad);
	waitLCD();
}

void clr_lcd(){
	del(CTRL, RS);
	writeLCD(0x01);
	waitLCD();
}

void putchar_lcd(uint8_t chr){
	set(CTRL,RS);
	writeLCD(chr);
	waitLCD();
}

void printLCD(char *str, unsigned char len){
	unsigned char i;
	for(i = 0; i<len;i++){
		if(str[i]>0) putchar_lcd(str[i]);
		else putchar_lcd(' ');
	}
	
}
int main(void)
{
    /* Replace with your application code */
	init_lcd();
	clr_lcd();
	printLCD("1", 2);
	while(1){

	};
}

