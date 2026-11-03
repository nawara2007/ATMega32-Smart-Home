/*
 * LDR.c
 *
 * Created: 9/18/2026 7:56:47 PM
 *  Author: mohamed nawara
 */ 

#include "LDR.h"

static u8 LDR_Channel = 0;

void LDR_init(u8 channel_num)
{
	DIO_voidSetPinDirection(PORTA_ID, channel_num, PIN_INPUT);
	ADC_voidInit();
	LDR_Channel = channel_num;
}

u8 LDR_u8GetPrecent()
{
	u16 raw_result = ADC_u16GetResultSync(LDR_Channel);
	u8 precentage =  (u8) ((  raw_result - 1) * 0.146412) + 1;
	
	return precentage;
}