
#include <avr/io.h>
#include <util/delay.h>
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

#define sbi(sfr,bit) sfr|=_BV(bit)
#define cbi(sfr,bit) sfr&=~(_BV(bit))
#define bit_is_clear(sfr,bit) (!(_SFR_BYTE(sfr) & _BV(bit)))

#define EN 2
#define RW 1
#define RS 0

#define ctrl PORTB
#define ddr_ctrl DDRB
#define data_o PORTB
#define data_i PINB
#define ddr_data DDRB

char read2Nib(){
	char h,l;
	data_o &= 0x0F;
	h = data_o & 0xF0;
	cbi(ctrl,EN);
	sbi(ctrl,EN);
	l = data_o & 0xF0;
	cbi(ctrl,EN);
	l >>= 4;
	return (h|l);
}
void write2Nib(uint8_t chr){
	uint8_t h, l, temp;
	temp = data_o & 0x0F;
	
	h = chr & 0xF0;
	l = (chr<<4)& 0xF0;
	
	data_o = (h|temp);
	sbi(ctrl,EN);
	cbi(ctrl,EN);
	
	data_o = (l|temp);
	sbi(ctrl,EN);
	cbi(ctrl,EN);
}

void wait_LCD(){
	_delay_ms(1);
}

void init_LCD(){
	ddr_ctrl = 0xFF;
	ddr_data = 0xFF;
	
	cbi(ctrl,RS);
	cbi(ctrl,RW);
	cbi(ctrl,EN);
	
	sbi(ctrl,EN);
	sbi(data_o,5); // 101
	cbi(ctrl,EN);
	
	wait_LCD();
	write2Nib(0x28);//4bit
	wait_LCD();
	//hi?n control
	cbi(ctrl,RS);
	write2Nib(0x0E);
	wait_LCD();
	//Entry mode
	cbi(ctrl,RS);
	write2Nib(0x06);
	wait_LCD();
}

void home_LCD(){
	cbi(ctrl,RS);
	write2Nib(0x02);
	wait_LCD();
}
void move_LCD(uint8_t y, uint8_t x){
	uint8_t ad;
	ad = 64*(y-1)+(x-1)+0x80;
	cbi(ctrl,RS);
	
	write2Nib(ad);
	wait_LCD();
}
void clr_LCD(){
	cbi(ctrl,RS);
	write2Nib(0x01);
	wait_LCD();
}

void putchar_LCD(uint8_t chr){
	sbi(ctrl,RS);//data
	write2Nib(chr);
	wait_LCD();
}
void print_LCD(char*str,unsigned char len){
	unsigned char i;
	for(i=0;i<len;i++){
		if(str[i]>0){putchar_LCD(str[i]);
		}
		else{ putchar_LCD(' ');}
	}
}