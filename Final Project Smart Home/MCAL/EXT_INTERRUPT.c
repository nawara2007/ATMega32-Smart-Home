/*
 * interrupt.c
 *
 * Created: 9/3/2026 10:40:16 PM
 *  Author: mohamed nawara
 */

#include "EXT_INTERRUPT.h"


void EXTI_voidGlobalINT_Enable()
{
	SET_BIT(SREG,SREG_I);
}

void EXTI_voidGlobalINT_Disable()
{
	CLR_BIT(SREG,SREG_I);
}
  
void EXTI_voidInit(u8 Copy_u8INT_Number, u8 Copy_u8Sense_Control)
{
	switch(Copy_u8INT_Number)
	{
		case EXT_INT0_ID:
			switch (Copy_u8Sense_Control)
			{
				case LOW_LEVEL:
					CLR_BIT(MCUCR,MCUCR_ISC00);
					CLR_BIT(MCUCR,MCUCR_ISC01);
				break;
				case LOGICAL_CHANGE:
					SET_BIT(MCUCR,MCUCR_ISC00);
					CLR_BIT(MCUCR,MCUCR_ISC01);
				break;
				case FALLNG_EDGE:
					CLR_BIT(MCUCR,MCUCR_ISC00);
					SET_BIT(MCUCR,MCUCR_ISC01);
				break;
				case RISING_EDGE:
					SET_BIT(MCUCR,MCUCR_ISC00);
					SET_BIT(MCUCR,MCUCR_ISC01);
				break;
			}
		break;
		case EXT_INT1_ID:
		switch(Copy_u8Sense_Control)
		{
			case LOW_LEVEL:
				CLR_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
			case LOGICAL_CHANGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				CLR_BIT(MCUCR,MCUCR_ISC11);
			break;
			case FALLNG_EDGE:
				CLR_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
			break;
			case RISING_EDGE:
				SET_BIT(MCUCR,MCUCR_ISC10);
				SET_BIT(MCUCR,MCUCR_ISC11);
			break;
		}
		break;
		case EXT_INT2_ID:
		switch (Copy_u8Sense_Control)
		{
			case FALLNG_EDGE:
				CLR_BIT(MCUCSR,MCUCSR_ISC2);
			break;
			case RISING_EDGE:
				SET_BIT(MCUCSR,MCUCSR_ISC2);
			break;
		}
		break;
	}

}

void EXTI_voidDisableInterrupt(u8 Copy_u8INT_Number)
{
	switch(Copy_u8INT_Number)
	{
		case EXT_INT0_ID:
			CLR_BIT(GICR,GICR_INT0);
		break;
		case EXT_INT1_ID:
			CLR_BIT(GICR,GICR_INT1);
		break;
		case EXT_INT2_ID:
			CLR_BIT(GICR,GICR_INT2);
		break;
	}
}

void EXTI_voidEnableInterrupt(u8 Copy_u8INT_Number)
{
	switch(Copy_u8INT_Number)
	{
		case EXT_INT0_ID:
			SET_BIT(GICR,GICR_INT0);
		break;
		case EXT_INT1_ID:
			SET_BIT(GICR,GICR_INT1);
		break;
		case EXT_INT2_ID:
			SET_BIT(GICR,GICR_INT2);
		break;
	}
}

u8   EXTI_u8GetFlag(u8 Copy_u8INT_Number)
{
	switch(Copy_u8INT_Number)
	{
		case EXT_INT0_ID:
			return GET_BIT(GIFR,GIFR_INT0);
		case EXT_INT1_ID:
			return GET_BIT(GIFR,GIFR_INT1);
		case EXT_INT2_ID:
			return GET_BIT(GIFR,GIFR_INT2);
		default: 
			return 0;
	}
}

static void (*EXTI_pvoidCallBack[3])(void) = {NULL};
 	 
void EXTI_voidSetCallBack( void (*Copy_pvoidCallBack)(void) , u8 Copy_u8INT_Number )
{
	if (Copy_pvoidCallBack != NULL && Copy_u8INT_Number < 3)
	{
		EXTI_pvoidCallBack[Copy_u8INT_Number] = Copy_pvoidCallBack;
	}
}

ISR(INT0_vect)
{
	if(EXTI_pvoidCallBack[0] != NULL)
	{
		EXTI_pvoidCallBack[0]();
	}
}

ISR(INT1_vect)
{
	if(EXTI_pvoidCallBack[1] != NULL)
	{
		EXTI_pvoidCallBack[1]();
	}
}

ISR(INT2_vect)
{
	if(EXTI_pvoidCallBack[2] != NULL)
	{
		EXTI_pvoidCallBack[2]();
	}
}