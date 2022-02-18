/*
 * SPI with MAX7221 and 7-Segment.c
 *
 * Created: 2/17/2022 11:16:40 PM
 * Author :HABEBA HAMADA
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "spi.h"
#include "BIT Macros.h"

//Definition for Master initializing 
#define  DATA_ORDER     0
#define  CLOCK_POLARITY 0
#define  CLOCK_PHASE    0
#define  CLOCK_RATE     4
#define  SPEED_DOUBLE   0

//Definition for MAX7221 Commands
#define MODE_REGISTER_ADD       0x09
#define SCANlIMIT_REGISTER_ADD  0x0B
#define SHUTdOWN_REGISTER_ADD   0x0C
#define INTENSITY_REGISTER_ADD  0x0A

//Definition for MAX7221 Digits
#define DIGIT_ONE      0X01
#define DIGIT_TWO      0X02
#define DIGIT_THREE    0X03
#define DIGIT_FOUR     0X04


void MAX7221SEND(unsigned char Command,unsigned char Data)
{
	CLEAR_BIT(SPI_Port,SS);
	
	SPI_Master_WRITE(Command);
	
	SPI_Master_WRITE(Data);
	SET_BIT(SPI_Port,SS);
	
}
int main(void)
{
	char count=0;
    SPI_INTMASTER(DATA_ORDER,CLOCK_POLARITY,CLOCK_PHASE,CLOCK_RATE,SPEED_DOUBLE);
	
	MAX7221SEND(MODE_REGISTER_ADD,0xFF);
	MAX7221SEND(SCANlIMIT_REGISTER_ADD,0x03);
	MAX7221SEND(SHUTdOWN_REGISTER_ADD,0x01);
	MAX7221SEND(INTENSITY_REGISTER_ADD,0x09);
    while (1) 
    {
		MAX7221SEND(DIGIT_ONE,count/1000);
		MAX7221SEND(DIGIT_TWO,(count%1000)/100);
		MAX7221SEND(DIGIT_THREE,(count%100)/10);
		MAX7221SEND(DIGIT_FOUR,count%10);
		_delay_ms(1000);
		count+=1;
		if(count>=9999) count=0;
    }
}

