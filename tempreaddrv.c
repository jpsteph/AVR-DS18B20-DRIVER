/*
 * tempreaddr.c
 *
 * Created: 12/28/2022 3:52:24 PM
 *  Author: jpsteph
 */ 

#include <string.h>
#include <stdlib.h>
#include "uart.h"
#include "ds18b20.h"
#include "onewire.h"
#include <avr/io.h>
#include "clock.h"
#include <util/delay.h>

void getTemp(uint8_t output)
{
	int temp;
	float tempf;
	
	//port b pin 6
	ds18b20convert( &PORTB, &DDRB, &PINB, ( 1 << 5 ), NULL );
	_delay_ms(10);
	ds18b20read( &PORTB, &DDRB, &PINB, ( 1 << 5 ), NULL, &temp );
	
	//turning to float and dividing by 16 to get temp in C
	tempf = ((float) temp) / 16;
	
	if(output)
	{
		USART_Transmit_Float(tempf);
	}
}