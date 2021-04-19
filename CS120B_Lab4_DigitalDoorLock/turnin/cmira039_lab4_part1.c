/*	Author: Carlos Miranda cmira039@ucr.edu
 *  Partner(s) Name: n/a
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ToggleLightType { INIT, TURN_ON, WAIT0, TURN_OFF, WAIT1} LIGHT_TYPE;

void tickLight()
{
	switch(LIGHT_TYPE)
	{
		case INIT:
		LIGHT_TYPE = TURN_ON;
		break;
		
		case TURN_ON:
		if(PINA)
		{
			LIGHT_TYPE = TURN_ON;
		}
		else
		{
			LIGHT_TYPE = WAIT0;
		}
		break;
		
		case WAIT0:
		if(!PINA)
		{
			LIGHT_TYPE = WAIT0;
		}
		else
		{
			LIGHT_TYPE = TURN_OFF;
		}
		break;
		
		case TURN_OFF:
		if(PINA)
		{
			LIGHT_TYPE = TURN_OFF;
		}
		else
		{
			LIGHT_TYPE = WAIT1;
		}
		break;
		
		case WAIT1:
		if(!PINA)
		{
			LIGHT_TYPE = WAIT1;
		}
		else
		{
			LIGHT_TYPE = TURN_ON;
		}
		break;
		
		default:
		LIGHT_TYPE = INIT;
	}
	
	switch(LIGHT_TYPE)
	{
		case INIT:
		break;
		
		case TURN_ON:
		PORTB = 0x01;
		break;
		
		case WAIT0:
		break;
		
		case TURN_OFF:
		PORTB = 0x02;
		break;
		
		case WAIT1:
		break;
		
		default:
		LIGHT_TYPE = INIT;
	}
}
	

int main(void) 
{
	
	//Inputs
	DDRA = 0x00; PORTA = 0xFF; 
	
	//Outputs
	DDRB = 0xFF; PORTC = 0x00; 
	
	PORTB = 0x00;
	LIGHT_TYPE = INIT;
	
	while(1) 
	{
		tickLight();
	}
	return 1;
}
	



