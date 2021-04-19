/*	Author: Carlos Miranda cmira039@ucr.edu
 *  Partner(s) Name: n/a
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum CounterType { INIT, WAIT_MAIN, INC, DEC, RESET, WAIT_INC, WAIT_DEC, WAIT_RESET} COUNTER_TYPE;
unsigned char TEMPC = 0x00;

unsigned char isA0()
{
	return PINA & 0x01;
}

unsigned char isA1()
{
	return PINA & 0x02;
}

void tickCounter()
{
	switch(COUNTER_TYPE)
	{
		case INIT:
		COUNTER_TYPE = WAIT_MAIN;
		break;
		
		case WAIT_MAIN:
		if(!isA0() && !isA1())
		{
			COUNTER_TYPE = WAIT_MAIN;
		}
		else if(isA0() && !isA1())
		{
			COUNTER_TYPE = INC;
		}
		else if(!isA0() && isA1())
		{
			COUNTER_TYPE = DEC;
		}
		else if(isA0() && isA1()){
			COUNTER_TYPE = RESET;
		}
		break;
		
		case INC:
		if(isA0() && isA1())
		{
			COUNTER_TYPE = RESET;
			break;
		} 
		COUNTER_TYPE = WAIT_INC;
		break;
		
		case WAIT_INC:
		if(isA0() && isA1())
		{
			COUNTER_TYPE = RESET;
		} 
		else if(isA0() && !isA1())
		{
			COUNTER_TYPE = WAIT_INC;
		}
		else{
			COUNTER_TYPE = WAIT_MAIN;
		}	
		break;
		
		case DEC:
		if(isA0() && isA1())
		{
			COUNTER_TYPE = RESET;
			break;
		} 
		COUNTER_TYPE = WAIT_DEC;
		break;

		case WAIT_DEC:
		if(isA0() && isA1())
		{
			COUNTER_TYPE = RESET;
		} 
		else if(!isA0() && isA1())
		{
			COUNTER_TYPE = WAIT_DEC;
		}
		else {
			COUNTER_TYPE = WAIT_MAIN;
		}
		break;
		
		case RESET:
		COUNTER_TYPE = WAIT_RESET;
		break;
		
		case WAIT_RESET:
		if(isA0() && isA1())
		{
			COUNTER_TYPE = WAIT_RESET;
		}
		else
		{
			COUNTER_TYPE = WAIT_MAIN;
		}
		break;
		
		default:
		COUNTER_TYPE = INIT;
		break;
	}
	
	switch(COUNTER_TYPE)
	{
		case INIT:
		TEMPC = 0x07;
		PORTC = TEMPC;
		break;
		
		case WAIT_MAIN:
		break;
		
		case INC:
		if(TEMPC < 0x09)
		{
			TEMPC = TEMPC + 1;
			PORTC = TEMPC;
		}
		break;
		
		case WAIT_INC:
		break;
		
		case DEC:
		if(TEMPC > 0x00)
		{
			TEMPC = TEMPC - 1;
			PORTC = TEMPC;
		}
		break;

		case WAIT_DEC:
		break;
		
		case RESET:
		TEMPC = 0x00;
		PORTC = TEMPC;
		break;
		
		case WAIT_RESET:
		break;
		
		default:
		break;
	}
	
}
	

int main(void) 
{
	
	//Inputs
	DDRA = 0x00; PORTA = 0xFF; 
	
	//Outputs
	DDRC = 0xFF; PORTC = 0x00; 
	
	COUNTER_TYPE = INIT;
	
	TEMPC = 0x07;
	PORTC = TEMPC;	
	while(1) 
	{
		tickCounter();
	}
	return 1;
}
	



