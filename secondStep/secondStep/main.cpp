/*
 * secondStep.cpp
 *
 * Created: 4/19/2019 9:19:24 AM
 * Author : PC
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <util/twi.h>
#include <stdlib.h>
#include "i2c.h"
#include "lcd.h"
/****************************/
#define  F_CPU 8000000UL
#define loop_until_bit_is_set(sfr,bit) do { } while (bit_is_clear(sfr, bit))

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


uint8_t sec,min,hour,day,date,month,year;
int i,x,y,x_old,y_old,speedX,speedY,player1,score1 = 0;
int player_speed = 3;
int player_size = 10;

char buff[1];

volatile uint8_t doc;
volatile uint8_t pos = 30;

volatile uint8_t portbhistory = 0xFF; 
volatile uint8_t game_mode = 0;
volatile uint8_t start_game = 0;
volatile uint8_t mode = 0;

void delete_ball(uint8_t x, uint8_t y);
ISR (INT0_vect)
{
	
	if(game_mode == 1)
	player1 += player_speed;
    if(game_mode == 2)
	pos -= 10;
	delete_ball(5,pos);
}
ISR (INT1_vect)
{
	if(game_mode == 1)
	player1 -= player_speed;
 	else
    game_mode = 2;
}

ISR (PCINT2_vect)
{

	/*if( (PIND & (1 << PIND4)) == 1 ){*/
		//PORTB ^= (1 << PB5);
	   if(game_mode == 0){
	      game_mode = 1;
	   }
	  
// 	   if(game_mode == 1){
// 		   if(start_game == 1){
// 			   start_game = 0;
// 			   game_mode = 0;
// 		   }
// 		   else{
// 			   start_game = 1;
// 		   }
// 	   }
//  	    else
//  	      game_mode = 0;
	  
}
ISR(USART_RX_vect){
	value = UDR0;             //read UART register into value
}
void ds1307_read(){
	sec = ds1307_read_sec(0x00);
	hour = ds1307_read_reg(0x02);
	min = ds1307_read_sec(0x01);
	
	day = ds1307_read_reg(0x04);
	month = ds1307_read_reg(0x05);
	year = ds1307_read_reg(0x06);
}
void draw_field(){
	lcd_fillRect(63,0, 64, 10,WHITE);
	lcd_fillRect(63,15, 64, 25,WHITE);
	lcd_fillRect(63,30, 64, 40,WHITE);
	lcd_fillRect(63,45, 64, 55,WHITE);
}
void clr(){
	lcd_fillRect(0,0, 128, 10,BLACK);
}
void move_ball(int speedX, int speedY,int x, int y){
	 //lcd_gotoxy(3,6);
	 lcd_fillCircle(x,y,3,WHITE);
	 //lcd_display();

}

void delete_move(int posX, int p_speed,int player_size){
	lcd_fillRect(0,0, 3, 63,BLACK);
}
void player_move(int posX, int p_speed,int player_size){
	lcd_fillRect(0,posX - player_size/2, 3, posX + player_size/2,WHITE);
}
void intro(){
	lcd_charMode(DOUBLESIZE);
	lcd_gotoxy(0,1);
	lcd_puts("   Pong  \r\n   Game");
	lcd_charMode(NORMALSIZE);
	lcd_gotoxy(3,6);
	lcd_puts("* Press start *");
	lcd_display();
}

void intro1(){
	lcd_charMode(DOUBLESIZE);
	lcd_gotoxy(0,1);
	lcd_puts("   Flappy  \r\n   Bird");
	lcd_charMode(NORMALSIZE);
	lcd_gotoxy(3,6);
	lcd_puts("* Press start *");
	lcd_display();
}

void end_game(){
	lcd_charMode(DOUBLESIZE);
	lcd_gotoxy(0,1);
	lcd_puts("   Game  \r\n   Over ");
	lcd_charMode(NORMALSIZE);
	lcd_gotoxy(3,6);
	lcd_puts("* Press reset *");
	lcd_display();
}
void opening(){
	lcd_charMode(DOUBLESIZE);
	lcd_gotoxy(0,1);
	lcd_puts(" Clock 1.0 ");
	lcd_charMode(NORMALSIZE);
	//lcd_gotoxy(3,6);
	//lcd_puts("* Press start *");
	lcd_display();
}
void condition(){
	if(player1>60 ){
		
		player_speed*=-1;
	}
	if(player1<10 ){
		
		player_speed*=-1;
	}
	if(x>127 ){
		
		speedX*=-1;
	}
	if(y >55){
		speedY*=-1;
	}
	if(x<10){
		speedX*=-1;
		if((y<player1 + player_size/2+5) &&y>(player1 - player_size/2 + 5)){
		}
		else{
			score1++;
		}
	}
	if(y<10){
		speedY*=-1;
	}
	x+=speedX;
	y+=speedY ;
	//player1 += speedX;
	move_ball(3, 3,x,y);
	player_move(player1, 4,10);
	
	
	char temp[3];
	lcd_gotoxy(3,10);
	itoa(score1,temp,10);
	lcd_puts(temp);
}
void init_button(){
	/* Ng?t pin change */
	DDRD &= ~(1 << DDD4); 

	PORTD |= (1 << PORTD4);       

	PCICR |= (1 << PCIE2);     // set PCIE0 to enable PCMSK0 scan
	PCMSK2 |= (1 << PCINT20);   // set PCINT0 to trigger an interrupt on state change
	
    /* Ng?t ngoài */
	EICRA |= (1 << ISC00)|(1<<ISC01);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0);     // Turns on INT0
	
	EICRA |= (1 << ISC10)|(1<<ISC11);    // set INT1 to trigger on ANY logic change
	EIMSK |= (1 << INT1);     // Turns on INT1
	buff[0] = '0';
	sei();                    // turn on interrupts

}
void show_time(){
	  ds1307_read();
	  lcd_gotoxy(5,5);
   	  char temp[2];
				
	  lcd_puts("Time:");
	  if(hour<10){
		lcd_puts(buff);
	  }
	  itoa(hour,temp,10);
	  lcd_puts(temp);
	  lcd_puts(":");
	  if(min<10){
		lcd_puts(buff);
	  }
	  itoa(min,temp,10);
	  lcd_puts(temp);
	  lcd_puts(":");
	  itoa(sec,temp,10);
	  if(sec<10){
		lcd_puts(buff);
	  }
	  lcd_puts(temp);
}
void draw_column(int x,int y ){
	lcd_fillRect(y,0, y+4, x,WHITE);
	lcd_fillRect(y ,x+10, y+4,60 ,WHITE);
	// 	lcd_fillRect(63,15, 64, 25,WHITE);
	// 	lcd_fillRect(63,30, 64, 40,WHITE);
	// 	lcd_fillRect(63,45, 64, 55,WHITE);
}
void delete_column(int x,int y ){
	lcd_fillRect(y,0, y+4, x,BLACK);
	lcd_fillRect(y ,x+10, y+4,60 ,BLACK);
	// 	lcd_fillRect(63,15, 64, 25,WHITE);
	// 	lcd_fillRect(63,30, 64, 40,WHITE);
	// 	lcd_fillRect(63,45, 64, 55,WHITE);
}
void run_column(){
	doc = 100;
	while(doc>=10){
		//lcd_sleep(1000);
		delete_column(30,doc);
		lcd_display();
		/*lcd_gotoxy(0,0); */
		draw_column(30,doc-3);
		lcd_display();
		//_delay_ms(50);
		doc-=10;
	}
}


void move_ball(uint8_t x, uint8_t y){

	lcd_fillCircle(x,y,3,WHITE);

}
void delete_ball(uint8_t x, uint8_t y){
	//lcd_gotoxy(3,6);
	lcd_fillCircle(x,y,3,BLACK);
	//lcd_display();
}
void player(uint8_t pos){
	move_ball(5, pos);
	// 	lcd_display();
	// 	delete_ball(5, pos);
	//delete_ball(10,30);
}
void flappy_bird(){
	 doc = 100;
	 pos = 30;
	for(;;){
		
		
		delete_ball(5,pos);
		delete_column(30,doc);
		lcd_display();
		/*lcd_gotoxy(0,0); */
		pos+=1;
		if(pos < 5 || pos > 60){
			end_game();
			break;
		}
		player(pos);
		draw_column(30,doc-3);
		lcd_display();
		//_delay_ms(50);
		doc-=3;		
		if(doc == 5 && ((pos<25)||(pos>35))){
			end_game();
			break;
	    }
			
	
  }
}
void ping_pong(){
	  lcd_home();
	  while(1){
	  delete_ball(x,y);
	  delete_move(player1, 4,10);
	 
	  draw_field();
	  condition();
	   if(score1 > 10){
		   end_game();
		   break;
	   }
	  lcd_display();
	  }
}
int main(void)
{
	

	init_button();
    //ds1307_writeaddr();
	
 	lcd_init(LCD_DISP_ON);    // init lcd and turn on
	lcd_clrscr();
    lcd_set_contrast(0x00);

    uart_init();
	
	 x = y = 10;
	 player1 = 11;
	 speedX = 3;
	 speedY = 3;
	 while(1){
     if(game_mode == 0){
	     opening();
		 //lcd_clrscr();
		 //_delay_ms(1000);
		 show_time();
		 lcd_sleep(1000);
		 //lcd_clrscr();
     }
	
		  
	
	//uart_transmit(' ');
	 else{
		
        while (game_mode == 1) 
        {
			lcd_clrscr();
			intro();
			/*_delay_ms(1000);*/
			lcd_clrscr();
		    ping_pong();
			game_mode = 0;
			score1 = 0; 
			break;
       }
	   while (game_mode == 2)
	   {
		   lcd_clrscr();
		   intro1();
		   /*_delay_ms(1000);*/
		   lcd_clrscr();
		   flappy_bird();
		   game_mode = 0;
		   break;
	   }
	   _delay_ms(2000);
	   lcd_clrscr();
	   
	  }
	 }
}
