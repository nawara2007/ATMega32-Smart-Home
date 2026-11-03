/*
 * LM35.c
 *
 * Created: 9/18/2026 11:00:15 PM
 *  Author: mohamed nawara
 */

#include "LM35.h"

static u8 LM35_Channel = 0;

void LM35_init(u8 channel_num)
{
	DIO_voidSetPinDirection(PORTA_ID, channel_num, PIN_INPUT);
	ADC_voidInit();
	LM35_Channel = channel_num;
}

u16 LM35_u16getCelsius()
{
	u16 raw_result = ADC_u16GetResultSync(LM35_Channel);
	u16 Celsius = raw_result * 0.48828125 + 0.5;
	return Celsius;
}
