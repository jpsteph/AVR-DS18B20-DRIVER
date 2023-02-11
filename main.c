/*
 * Uart Test.c
 *
 * Created: 12/19/2022 10:28:18 PM
 * Author : jpsteph
 */ 

#include <avr/io.h>
#include "uart.h"
#include "clock.h"                                           
#include <util/delay.h>
#include <string.h>
#include "tempreaddrv.h"
#include <stdint.h>

#define BAUDRATE 9600

#define BUFSIZE 100

#define VCC 6 //PB6
#define GND 6 //PE6
#define LED 7 //PC7

#define INITSENS()  DDRB |= (1 << VCC);\
					PORTB |= (1 << VCC);\
					DDRE |= (1 << GND);\
					PORTE &= ~(1 << GND);\
					DDRC |= (1 << LED);\
					PORTC &= ~(1 << LED);

#define BLINKLED() PORTC |= (1 << LED);\
					_delay_ms(50);\
					PORTC &= ~(1 << LED);\
					_delay_ms(50);


int main(void)
{
	
	INITSENS();
	USART_Init( BAUDRATE );
	
	char rxbuffer[BUFSIZE];
	int filledbuffsize;
	uint8_t flag;
	
	//USART cmds
	char tempcmd[]= "tmpi";
	char identitycmd[] = "envirocntrl";
	
    while (1) 
    {
	
		filledbuffsize = USART_Receive_String(rxbuffer);
		
		USART_Transmit_String2(rxbuffer, filledbuffsize);
		
		flag = USART_cmd(rxbuffer, tempcmd, strlen(tempcmd));
	
		if(flag) 
		{
			BLINKLED();
			
			getTemp();
			flag = 0;
		}
		
		flag = USART_cmd(rxbuffer, identitycmd, strlen(identitycmd));
		
		if(flag)
		{
			for(uint8_t i=0; i < 20; i++)
			{
				BLINKLED();
			}
			USART_Transmit_String("Environmental Chamber Control Device");
			flag = 0;
			
		}
		   
    }
}

