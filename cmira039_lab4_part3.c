/*	Author: Carlos Miranda cmira039@ucr.edu
 *  Partner(s) Name: n/a
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ComboLockType { INIT, WAIT, P1, P2, P3, UNLOCK, LOCK }LOCK_TYPE;

unsigned char isOnlyA7()
{
	return PINA == 0x80;
}

unsigned char isOnlyA2()
{
	return PINA == 0x04;
}

unsigned char isOnlyA1()
{
	return PINA == 0x02;
}

void tickComboLock()
{
	switch(LOCK_TYPE)
	{
		case INIT:
		LOCK_TYPE = WAIT;
		break;
		
		case WAIT:
		if(isOnlyA2())
		{
			LOCK_TYPE = P1;
		}
		else if(isOnlyA7())
		{
			LOCK_TYPE = LOCK;
		}
		else
		{
			LOCK_TYPE = WAIT;
		}
		break;
		
		case P1:
		if(isOnlyA2())
		{
			LOCK_TYPE = P1;
		}
		//else if(isOnlyA1())
	//	{
	//		LOCK_TYPE = UNLOCK;
	//	}
		else if(PINA == 0x00)
		{
			LOCK_TYPE = P2;
		}
		else 
		{
			LOCK_TYPE = WAIT;
		}
		break;
		
		case P2:
		if(PINA == 0x00)
		{
			LOCK_TYPE = UNLOCK;
		}
		else if(isOnlyA1())
		{
			LOCK_TYPE = UNLOCK;
		}
		else{
			LOCK_TYPE = WAIT;
		}	
		break;
		
		case UNLOCK:
		if(isOnlyA1())
		{
			LOCK_TYPE = UNLOCK;
		}
		else 
		{
			LOCK_TYPE = WAIT;
		}
		break;
		
		case LOCK:
		if(isOnlyA7())
		{
			LOCK_TYPE = LOCK;
		}
		else
		{
			LOCK_TYPE = WAIT;
		}
		break;
		
		default:
		LOCK_TYPE = INIT;
		break;
	}
	
	switch(LOCK_TYPE)
	{
		case INIT:
		break;
		
		case WAIT:
		break;
		
		case P1:
		break;
		
		case UNLOCK:
		PORTB = 0x01;
		break;
		
		case LOCK:
		PORTB = 0x00;
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
	DDRB = 0xFF; PORTB = 0x00; 
	
	LOCK_TYPE = INIT;
	
	while(1) 
	{
		tickComboLock();
	}
	return 1;
}
	


