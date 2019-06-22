/*
 * matrix.c
 *
 * Created: 2/21/2019 12:13:38 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#define ROW PORTB
#define COL PORTD
#define set(port,bit) port |= (1<<bit);
#define del(port,bit) port &= ~(1<<bit);

void init(){
	set(ROW, x);
	set(COL, y);
}
void setPointMatrix(uint8_t x, uint8_t y){
	set(ROW, x);
	set(COL, y);
}
void clrMatrix(){
	ROW = 0x00;
	COL = 0x00;
}
int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

