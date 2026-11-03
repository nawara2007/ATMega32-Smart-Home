/*
 * Buzzer.c
 *
 * Created: 9/18/2026 8:25:04 PM
 *  Author: mohamed nawara
 */ 
#include "Buzzer.h"

static u8 Buzzer_port = 0;
static u8 Buzzer_pin = 0;

void BUZZER_init(u8 copy_port_id, u8 copy_pin_id)
{
	Buzzer_port = copy_port_id;
	Buzzer_pin = copy_pin_id;
	
	DIO_voidSetPinDirection(Buzzer_port, Buzzer_pin, PIN_OUTPUT);
	DIO_voidSetPinValue(Buzzer_port, Buzzer_pin, PIN_LOW);
}

void BUZZER_ON()
{
	DIO_voidSetPinValue(Buzzer_port, Buzzer_pin, PIN_HIGH);
}

void BUZZER_OFF()
{
	DIO_voidSetPinValue(Buzzer_port, Buzzer_pin, PIN_LOW);
}