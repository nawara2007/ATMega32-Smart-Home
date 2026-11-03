/*
 * Flame.c
 *
 * Created: 9/18/2026 9:01:39 PM
 *  Author: mohamed nawara
 */ 

#include "Flame.h"

static Flame_INT_Number = 0;
void Flame_init(u8 Copy_u8INT_Number, void (*Copy_pvoidCallBack)(void))
{
	Flame_INT_Number = Copy_u8INT_Number;
	switch (Flame_INT_Number)
	{
		case EXT_INT0_ID:
			DIO_voidSetPinDirection(PORTD_ID, PIN2, PIN_INPUT);
			break;
		case EXT_INT1_ID:
			DIO_voidSetPinDirection(PORTD_ID, PIN3, PIN_INPUT);
		break;
		case EXT_INT2_ID:
			DIO_voidSetPinDirection(PORTB_ID, PIN2, PIN_INPUT);
		break;
	}
	
	EXTI_voidInit(Copy_u8INT_Number, RISING_EDGE);
	EXTI_voidSetCallBack(Copy_pvoidCallBack, Copy_u8INT_Number);
	EXTI_voidEnableInterrupt(Copy_u8INT_Number);
	EXTI_voidGlobalINT_Enable();
}

u8 FLAME_PinState()
{
	switch (Flame_INT_Number)
	{
		case EXT_INT0_ID:
			return DIO_u8GetPinValue(PORTD_ID, PIN2);
		case EXT_INT1_ID:
			return DIO_u8GetPinValue(PORTD_ID, PIN3);
		case EXT_INT2_ID:
			return DIO_u8GetPinValue(PORTB_ID, PIN2);
	}
}
