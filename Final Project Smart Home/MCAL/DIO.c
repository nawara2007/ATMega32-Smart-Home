/*
 * DIO.c
 *
 * Created: 8/17/2026 11:35:44 PM
 *  Author: mohamed nawara
 */ 
#include "DIO.h"
void DIO_voidSetPortDirection(u8 Copy_u8PORT, u8 Copy_u8Direction)
{
	if (Copy_u8PORT < 4)
	{
		switch (Copy_u8PORT)
		{
			case 0:
				DDRA = Copy_u8Direction;
			break;
			case 1:
				DDRB = Copy_u8Direction;
			break;
			case 2:
				DDRC = Copy_u8Direction;
			break;
			case 3:
				DDRD = Copy_u8Direction;
			break;													
		}
	}
}

void DIO_voidTogglePortValue(u8 Copy_u8PORT)
{
	if (Copy_u8PORT < 4)
	{
		switch (Copy_u8PORT)
		{
			case 0:
			PORTA = ~PORTA;
			break;
			case 1:
			PORTB = ~PORTB;
			break;
			case 2:
			PORTC = ~PORTC;
			break;
			case 3:
			PORTD = ~PORTD;
			break;
		}
	}
}

void DIO_voidSetPortValue(u8 Copy_u8PORT, u8 Copy_u8Value)/*Write*/
{
	if (Copy_u8PORT < 4)
	{
		switch (Copy_u8PORT)
		{
			case 0:
				PORTA = Copy_u8Value;
			break;
			case 1:
				PORTB = Copy_u8Value;
			break;
			case 2:
				PORTC = Copy_u8Value;
			break;
			case 3:
				PORTD = Copy_u8Value;
			break;
		}
	}
}

u8 DIO_u8GetPortValue(u8 Copy_u8PORT)/*Read*/
{
	if (Copy_u8PORT < 4)
	{
		switch (Copy_u8PORT)
		{
			case 0:
				return PINA;
			case 1:
				return PINB;
			case 2:
				return PINC;
			case 3:
				return PIND;
		}
	}
}

void DIO_voidSetPinDirection(u8 Copy_u8PORT, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
		if(Copy_u8PORT < 4)
		{
			if(Copy_u8Pin < 8)
			{
				switch (Copy_u8PORT)
				{
					case 0:
						if(Copy_u8Direction)
							SET_BIT(DDRA, Copy_u8Pin);
						else
							CLR_BIT(DDRA, Copy_u8Pin);
					break;
					case 1:
						if(Copy_u8Direction)
							SET_BIT(DDRB, Copy_u8Pin);
						else
							CLR_BIT(DDRB, Copy_u8Pin);
					break;
					case 2:
						if(Copy_u8Direction)
							SET_BIT(DDRC, Copy_u8Pin);
						else
							CLR_BIT(DDRC, Copy_u8Pin);
					break;
					case 3:
						if(Copy_u8Direction)
							SET_BIT(DDRD, Copy_u8Pin);
						else
							CLR_BIT(DDRD, Copy_u8Pin);
					break;																								
				}
							
			}					
		}
}

void DIO_voidSetPinValue(u8 Copy_u8PORT, u8 Copy_u8Pin, u8 Copy_u8Value)/*Write*/
{
	if(Copy_u8PORT < 4)
	{
		if(Copy_u8Pin < 8)
		{
			switch (Copy_u8PORT)
			{
				case 0:
				if(Copy_u8Value)
					SET_BIT(PORTA, Copy_u8Pin);
				else
					CLR_BIT(PORTA, Copy_u8Pin);
				break;
				case 1:
				if(Copy_u8Value)
					SET_BIT(PORTB, Copy_u8Pin);
				else
					CLR_BIT(PORTB, Copy_u8Pin);
				break;
				case 2:
				if(Copy_u8Value)
					SET_BIT(PORTC, Copy_u8Pin);
				else
					CLR_BIT(PORTC, Copy_u8Pin);
				break;
				case 3:
				if(Copy_u8Value)
					SET_BIT(PORTD, Copy_u8Pin);
				else
					CLR_BIT(PORTD, Copy_u8Pin);
				break;
			}
		
		}
	}
}


u8 DIO_u8GetPinValue(u8 Copy_u8PORT, u8 Copy_u8Pin) /*Read*/
{
	if (Copy_u8PORT < 4)
	{
		if(Copy_u8Pin < 8)
		{	
			switch (Copy_u8PORT)
			{
				case 0:
					return GET_BIT(PINA,Copy_u8Pin);
				case 1:
					return GET_BIT(PINB,Copy_u8Pin);
				case 2:
					return GET_BIT(PINC,Copy_u8Pin);
				case 3:
					return GET_BIT(PIND,Copy_u8Pin);
			}
		}
	}
}

void DIO_voidTogglePinValue(u8 Copy_u8PORT, u8 Copy_u8Pin)
{
	if(Copy_u8PORT < 4)
	{
		if(Copy_u8Pin < 8)
		{
			switch (Copy_u8PORT)
			{
				case 0:
					TOGGLE_BIT(PORTA, Copy_u8Pin);
				break;
				case 1:
					TOGGLE_BIT(PORTB, Copy_u8Pin);
				break;
				case 2:
					TOGGLE_BIT(PORTC, Copy_u8Pin);
				break;
				case 3:
					TOGGLE_BIT(PORTD, Copy_u8Pin);
				break;
			}
			
		}
	}
}
