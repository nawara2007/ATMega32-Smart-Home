/*
 * LED.c
 *
 * Created: 8/18/2026 2:01:42 AM
 *  Author: mohamed nawara
 */ 
#include "LED.h"

void led_init(u8 port_id, u8 pin_name)
{
	DIO_voidSetPinDirection(port_id, pin_name, PIN_OUTPUT);
}

void led_on(u8 port_id, u8 pin_name)
{
	DIO_voidSetPinValue(port_id, pin_name, PIN_HIGH);
}

void led_off(u8 port_id, u8 pin_name)
{
	DIO_voidSetPinValue(port_id, pin_name, PIN_LOW);
}

void led_toggle(u8 port_id, u8 pin_name)
{
	DIO_voidTogglePinValue(port_id, pin_name);
}
