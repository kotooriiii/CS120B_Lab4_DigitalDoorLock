/*	Author: Carlos Miranda cmira039@ucr.edu
 *  Partner(s) Name: n/a
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ComboLockType { INIT, WAIT, P, UNLOCK, LOCK }LOCK_TYPE;

unsigned char TEMPB = 0x00;
unsigned char CODE[8] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01, 0x00};
unsigned char INDEX = 0x00;

unsigned char isOnlyA7()
{
	return PINA == 0x80;
}

unsigned char isOnlyA2()
{
	return PINA == 0x04;
}

unsigned char isOnlyA0()
{
	return PINA == 0x01;
}

unsigned char isOnlyA1()
{
	return PINA == 0x02;
}


unsigned char isValidOption()
{
	
	unsigned char isAllowed = 0x00;
	switch(INDEX)
	{
		case 0x00:
		if(PINA == CODE[0])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[1])
		{
			INDEX = INDEX + 1;
						isAllowed = 0x01;

		}
		else 
		{
		}
		break;
		
		case 0x01:
		if(PINA == CODE[1])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[2])
		{
			INDEX = INDEX + 1;
						isAllowed = 0x01;

		}
		else 
		{
		}
		break;
		
		case 0x02:
		if(PINA == CODE[2])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[3])
		{
			INDEX = INDEX + 1;
						isAllowed = 0x01;

		}
		else 
		{
		}
		break;
		
		case 0x03:
		if(PINA == CODE[3])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[4])
		{
			INDEX = INDEX + 1;
						isAllowed = 0x01;

		}
		else 
		{
		}
		break;

		case 0x04:
			if(PINA == CODE[4])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[5])
		{
			INDEX = INDEX + 1;
						isAllowed = 0x01;

		}
		else 
		{
		}
		break;
		
		case 0x05:
		if(PINA == CODE[5])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[6])
		{
			INDEX = INDEX + 1;
						isAllowed = 0x01;

		}
		else 
		{
		}
		break;
		
		case 0x06:
		if(PINA == CODE[6])
		{
			isAllowed = 0x01;
		}
		else if(PINA == CODE[7])
		{
			INDEX = INDEX + 1;
			isAllowed = 0x01;

		}
		else 
		{
		}
		break;
		
		default:
		break;
	}
	
	return isAllowed;
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
			LOCK_TYPE = P;
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
		
		case P:
		if(INDEX == 0x07)
		{
INDEX = 0x00;
LOCK_TYPE = UNLOCK;			
	} else if (!isValidOption()) {
		LOCK_TYPE = WAIT;
	} else {
		LOCK_TYPE = P;
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
		
		case P:
		break;
		
		case UNLOCK:
		if(TEMPB)
		{
			TEMPB = 0x00;
		}
		else 
		{
			TEMPB = 0x01;
		}
		
		PORTB = TEMPB;	
		break;
		
		case LOCK:
		TEMPB = 0x00;
		PORTB = TEMPB;
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
	


